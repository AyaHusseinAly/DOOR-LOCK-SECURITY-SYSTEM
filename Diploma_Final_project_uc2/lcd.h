/*
 * lcd.h
 *
 *  Created on: Sep 24, 2018
 *      Author: Aya Hussein
 */

#ifndef LCD_H_
#define LCD_H_

#include "uc_config.h"
/* LCD MODE */
#define USED_MODE 4
/*in case of 4 bits mode*/
#if(USED_MODE==4)
#define UPPER_PORT_PINS /*if you're using the lower pins of uc port then comment this line*/
#endif

/* LCD HW Pins */
#define RS PD4
#define RW PD5
#define E  PD6

#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC



/* LCD Commands */
#define CLEAR_SCREEN 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define FOUR_BITS_DATA_MODE 0x02
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define CURSOR_BLINK 0x0F
#define SET_CURSOR_LOCATION 0x80
#define SHIFT_DISPLAY_LEFT 0X18
#define SHIFT_DISPLAY_RIGHT 0X1C




void lcd_init(void);
void lcd_sendCommand(unsigned char command);
void lcd_displayChar(unsigned char data);
void lcd_displayString(unsigned char *str);
void lcd_goToRowColumn(unsigned char row, unsigned char col);
void lcd_displayStringRowColumn(unsigned char row, unsigned char col,unsigned char*str);
void lcd_intgerToString(int data);

#endif /* LCD_H_ */
