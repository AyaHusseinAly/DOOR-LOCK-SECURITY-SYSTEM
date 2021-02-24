/*
 * uc1.c
 *
 *  Created on: Oct 18, 2018
 *      Author: Aya Hussein
 */

#include "keypad.h"
#include "lcd.h"
#include "UART.h"

#define uc2_READY 'A'
#define Main_menu 'B'
#define NEW_PASS 'C'
#define PassSavedMsg 'D'
#define wrongOption 'E'
#define OpenDoorMode 'F'
#define GetPass 'G'
#define Warning 'H'
#define wrongPass 'I'

void display_main_menu(void);
void newPassword(void);
void getPassword(void);

int main(){

	UART_init();
	lcd_init();
	newPassword();

	while(1){

		switch( UART_ReceiveByte()){

		case Main_menu:
			display_main_menu();
			break;

		case NEW_PASS:
			newPassword();
			break;

		case PassSavedMsg:
			lcd_sendCommand(CLEAR_SCREEN);
			lcd_displayStringRowColumn(0,0,"New Pass Saved,");
			lcd_displayStringRowColumn(1,0,"Successfully");
			break;

		case GetPass:
			getPassword();
			break;

		case OpenDoorMode:
			lcd_sendCommand(CLEAR_SCREEN);
			lcd_displayStringRowColumn(1,0,"Door is Opening");
			break;

		case wrongOption:
			/*when user enter any key except '*' or '#'  in main menu mode*/
			lcd_sendCommand(CLEAR_SCREEN);
			lcd_displayStringRowColumn(0,0,"Undefined Choise");
			lcd_displayStringRowColumn(1,0,"Plz,Try Again");
			_delay_ms(1000);
			display_main_menu();
			break;

		case wrongPass:
					/*when user enter any key except '*' or '#'  in main menu mode*/
					lcd_sendCommand(CLEAR_SCREEN);
					lcd_displayStringRowColumn(0,0,"Wrong Password");
					lcd_displayStringRowColumn(1,0,"Plz,Try Again");
					/*_delay_ms(1000);
					getPassword();*/

					break;
		case Warning:
					/*used when wrong password entered 3 times*/
					lcd_sendCommand(CLEAR_SCREEN);
					lcd_displayStringRowColumn(1,0,"****WARNING****");
					break;
		default:
			break;
		}
	}

}

/*****************A FN to get the password once to be checked by uC2************************************************/
void getPassword(void){
	unsigned char i;
	lcd_sendCommand(CLEAR_SCREEN);
	lcd_displayStringRowColumn(0,0,"Enter Pass");
	lcd_goToRowColumn(1,0);

	for(i=0;i<5;i++){
		//while( UART_ReceiveByte != uc2_READY){}
		unsigned char key= get_key();
		UART_SendByte(key);
		lcd_displayChar('*');
		_delay_ms(350);
	}


}
/*****************A FN to get the new password twice for changing password******************************************/
void newPassword(void){
	unsigned char i;
	lcd_sendCommand(CLEAR_SCREEN);
	lcd_displayStringRowColumn(0,0,"Enter New Pass");
	lcd_goToRowColumn(1,0);

	for(i=0;i<5;i++){
		//while( UART_ReceiveByte != uc2_READY){}
		unsigned char key= get_key();
		UART_SendByte(key);
		lcd_displayChar('*');
		_delay_ms(300);
	}
	lcd_sendCommand(CLEAR_SCREEN);
	lcd_displayStringRowColumn(0,0,"Re-Enter Pass");
	lcd_goToRowColumn(1,0);

	for(i=0;i<5;i++){
		//while( UART_ReceiveByte != uc2_READY){}
		unsigned char key= get_key();
		UART_SendByte(key);
		lcd_displayChar('*');
		_delay_ms(300);
	}
}

/*****************a FN to display main menu and send the choice****************************************************/
void display_main_menu(void){
	lcd_sendCommand(CLEAR_SCREEN);
	lcd_displayStringRowColumn(0, 0,"Main Menu: ");
	lcd_displayStringRowColumn(1,0,"*: Open door");
	lcd_displayStringRowColumn(2, 0,"#: Change Pass");

	unsigned char key =get_key();
	UART_SendByte(key);
	_delay_ms(300);


}
