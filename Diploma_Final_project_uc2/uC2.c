/*
 * uc2.c
 *
 *  Created on: Oct 18, 2018
 *      Author: Aya Hussein
 */

#include "UART.h"
#include "Timer1.h"
#include "external_eeprom.h"
#include "i2c.h"
#include "lcd.h"
#include <string.h>

#define uc2_READY 'A'/*used to tell uC1 that uC2 is ready to receive data*/
#define Main_menu 'B'/*used to order uC1 to Enter the main menu mode*/
#define NEW_PASS 'C'/*used to order uC1 to call the newPassword FN (to save a new password)*/
#define PassSavedMsg 'D'/*used to order uC1 to print a confirmation msg when the new pass is re-entered correct*/
#define wrongOption 'E' /*used to order uC1 to print error msg if any key except {'#','*'}has been pressed in main menu view*/
#define OpenDoorMode 'F'/*used to order uC1 to print that door opening then return to main menu*/
#define GetPass 'G' /*used to order uC1 to get pass to check*/
#define Warning 'H'/*used when wrong password entered 3 times*/
#define wrongPass 'I'


void newPassword(void);
void openDoor(void);
void motor_stop(void);
void motor_clockwise(void);
void motor_antiClockwise(void);
unsigned char checkPassword(void); /******************to receive entered password and check it**************/
void BlockAllSystem(void);


int main(){

	UART_init();
	EEPROM_init();
	newPassword();

	DDRC|=(1<<PC2);//BUZZER
	PORTC&=~(1<<PC2);
	DDRC|=(1<<PC3);//LED
	PORTC&=~(1<<PC3);
	DDRD|=(1<<PD4)|(1<<PD5);//MOTOR
	motor_stop();

	while(1){

		unsigned char option= UART_ReceiveByte();
		unsigned char check;

		switch (option){

		case '*':

			while(1){
				UART_SendByte(GetPass);
				check=checkPassword();
				if (check=='T'){
					UART_SendByte(OpenDoorMode);
					openDoor();
					break;}
				/********************wrong pass but not reached 3 times then don't break; and get pass again**************/
				else if(check=='F'){
					UART_SendByte(wrongPass);
					_delay_ms(2000);

				}
				/****************wrong password for the third time then block system  and break;****************/
				else{
					UART_SendByte(Warning);
					BlockAllSystem();
					UART_SendByte(Main_menu);
					break;}
			}
			break;


		case'#':

			while(1){
				UART_SendByte(GetPass);
				check=checkPassword();
				if (check=='T'){
					UART_SendByte(NEW_PASS);
					newPassword();
					break;}
				/********************wrong pass but not reached 3 times**************/
				else if(check=='F'){
					UART_SendByte(wrongPass);
					_delay_ms(2000);


				}
				/****************wrong password for the third time****************/
				else{
					UART_SendByte(Warning);
					BlockAllSystem();
					UART_SendByte(Main_menu);
				break;}
			}
			break;
		default:
			UART_SendByte(wrongOption);
			break;


		}
	}
}


/***************a FN to check if password is correct whether for changing pass or opening door***********************/
unsigned char checkPassword(void){

	unsigned char i,j;
	unsigned char pass[5];
	unsigned char password[5];
	static unsigned char count=0 ;

	/************************receive 5 bytes of pass***************************************/
	for(i=0;i<5;i++){
		//UART_SendByte(uc2_READY);
		pass[i]= UART_ReceiveByte();
		_delay_ms(350);
	}
	/****************read saved password from the EEPROM*****************************/
	for(j=0;j<5;j++){
		unsigned short x=0x0311 +j;
		EEPROM_readByte(x,&password[j] );
		_delay_ms(10);
	}
	password[4]='\0';
	pass[4]='\0';
	/*********************check if entered password was correct**********************/
	if(!(strcmp(password,pass))){
		count=0;
		return 'T';
		
	}
	else{
		count++;
		if(count==3){
			count=0;
			return 0;

		}
		else {

			return 'F';
		}
	}

}
/*******************a FN to check if password is correct whether*************************************
 ********************at the begining or for changing pass case ***************************************/
void newPassword(void){
	unsigned char i,j,k;
	unsigned char pass[5];
	unsigned char password[5];


	for(i=0;i<5;i++){
		//UART_SendByte(uc2_READY);
		pass[i]= UART_ReceiveByte();
		_delay_ms(300);
	}
	pass[4]='\0';

	for(j=0;j<5;j++){
		//UART_SendByte(uc2_READY);
		password[j]= UART_ReceiveByte();
		_delay_ms(300);
	}
	password[4]='\0';

	if(!(strcmp(password,pass))){
		for(k=0;k<5;k++){
			unsigned short x=0x0311 +k;
			EEPROM_writeByte(x, password[k]);
			_delay_ms(10);
		}
		UART_SendByte(PassSavedMsg);
		_delay_ms(1000);
		UART_SendByte(Main_menu);

	}
	else{
		UART_SendByte(NEW_PASS);
		newPassword();
	}
}

void openDoor(void){
	motor_clockwise();
	Timer1_init(7500);
	while(!(flag==1)){}
	motor_stop();

	motor_antiClockwise();
	Timer1_init(7500);
	while(!(flag==1)){}
	motor_stop();
	Timer1_stop();
	UART_SendByte(Main_menu);

}

void BlockAllSystem(void){

	PORTC|=(1<<PC2); //Buzzer ON
	 Timer1_init(40000);

	while(!(flag==1)){
		/************FLASH LED*****************/
		PORTC|=(1<<PC3);
		_delay_ms(500);
		PORTC&=~(1<<PC3);
	}
	
	PORTC&=~(1<<PC2); //Buzzer OFF
	 Timer1_stop();

}


/*******************FN's used by Opening door FN******************************************/
void motor_clockwise(void){
	PORTD|=(1<<PD4);
	PORTD &=~(1<<PD5);
}

void motor_antiClockwise(void){
	PORTD &=~(1<<PD4);
	PORTD|=(1<<PD5);
}
void motor_stop(void){
	PORTD &=~(1<<PD4);
	PORTD &=~(1<<PD5);
}
