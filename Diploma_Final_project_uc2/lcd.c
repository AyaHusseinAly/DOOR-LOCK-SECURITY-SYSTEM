/*
 * lcd.c
 *
 *  Created on: Sep 24, 2018
 *      Author: Aya Hussein
 */

#include "lcd.h"

void lcd_init(void){
	LCD_CTRL_PORT_DIR|=(1<<RS);
	LCD_CTRL_PORT_DIR|=(1<<RW);
	LCD_CTRL_PORT_DIR|=(1<<E);


#if(USED_MODE==8)
	LCD_DATA_PORT_DIR=0xFF;
	lcd_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);

#elif(USED_MODE==4)
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR=0xF0;
	#elif
	LCD_DATA_PORT_DIR=0x0F;
	#endif
	lcd_sendCommand(FOUR_BITS_DATA_MODE);
	lcd_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
#endif

	lcd_sendCommand(CURSOR_OFF);
	lcd_sendCommand(CLEAR_SCREEN);
}


void lcd_sendCommand(unsigned char command){
	LCD_CTRL_PORT&=~(1<<RS);
	LCD_CTRL_PORT&=~(1<<RW);
	_delay_ms(1);
	LCD_CTRL_PORT|=(1<<E);
	_delay_ms(1);

#if(USED_MODE==8)
	LCD_DATA_PORT=command;
	_delay_ms(1);
	LCD_CTRL_PORT&=~(1<<E); //clear en
	_delay_ms(1);
#elif(USED_MODE==4)
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(command&0xF0);
	#elif
	LCD_DATA_PORT=(LCD_DATA_PORT&0xF0)|((command&0xF0)>>4); /*Because we want to insert the last 4 bits of command with the first 4 bits in port*/
	#endif

	/*least 4 bits of command*/
		_delay_ms(1);
		LCD_CTRL_PORT&=~(1<<E); //clear en
		_delay_ms(1);
		LCD_CTRL_PORT|=(1<<E);//set en to send the rest of the data
		_delay_us(1);
		#ifdef UPPER_PORT_PINS
		LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((command&0x0F)<<4);
		#elif
		LCD_DATA_PORT=(LCD_DATA_PORT&0xF0)|(command&0x0F);
		#endif
		_delay_ms(1);
		LCD_CTRL_PORT&=~(1<<E); //clear en
		_delay_ms(1);
#endif






}


void lcd_displayChar(unsigned char data){
	LCD_CTRL_PORT|=(1<<RS);
	LCD_CTRL_PORT&=~(1<<RW);
	_delay_ms(1);
	LCD_CTRL_PORT|=(1<<E);
	_delay_ms(1);

#if(USED_MODE==8)
	LCD_DATA_PORT=data;
	_delay_ms(1);
	LCD_CTRL_PORT&=~(1<<E); //clear en
	_delay_ms(1);
#elif(USED_MODE==4)
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|(data&0xF0);
	#elif
	LCD_DATA_PORT=(LCD_DATA_PORT&0xF0)|((data&0xF0)>>4); /*Because we want to insert the last 4 bits of command with the first 4 bits in port*/
	#endif

	/*least 4 bits of data*/
	_delay_us(1);
	LCD_CTRL_PORT&=~(1<<E); //clear en
	_delay_ms(1);
	LCD_CTRL_PORT|=(1<<E);//set en to send the rest of the data
	_delay_ms(1);

	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT=(LCD_DATA_PORT&0x0F)|((data&0x0F)<<4);
	#elif
	LCD_DATA_PORT=(LCD_DATA_PORT&0xF0)|(data&0x0F);
	#endif
	_delay_ms(1);
	LCD_CTRL_PORT&=~(1<<E); //clear en
	_delay_ms(1);
#endif





}


void lcd_displayString(unsigned char *str){
	int i;
	for(i=0;str[i]!='\0';i++){
		lcd_displayChar(str[i]);}
}


void lcd_goToRowColumn(unsigned char row, unsigned char col){
	unsigned char command;
	switch(row){
	case 0: command= col|0x80;
		lcd_sendCommand(command);
		break;
	case 1:
		command=0x40+col;
		command|=0x80;
	    lcd_sendCommand(command);
	    break;
	case 2:
		command=0x10+col;
		command|=0x80;
	    lcd_sendCommand(command);
		break;
	case 3:
		command=0x50+col;
		command|=0x80;
		lcd_sendCommand(command);
		break;
	}


	}


void lcd_displayStringRowColumn(unsigned char row, unsigned char col,unsigned char *str){

	lcd_goToRowColumn(row,col);
	lcd_displayString(str);

}

void lcd_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   lcd_displayString(buff);
}
