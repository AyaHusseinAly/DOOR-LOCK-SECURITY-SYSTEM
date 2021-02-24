/*
 * UART.c
 *
 *  Created on: Oct 3, 2018
 *      Author: Aya Hussein
 */


#include "UART.h"

#define UBRR (F_CPU/(8UL*BAUD)-1)

void UART_init(void){
	UCSRC &=!(1<<UMSEL);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC |=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UCSRC|=(1<<UPM1);/*Even parity*/

	UCSRA = (1<<U2X);
	UBRRL= UBRR;
	UBRRH= (UBRR>>8);
}

unsigned char UART_ReceiveByte(void){

while(!(UCSRA&(1<<RXC)));
	return UDR;
}

void UART_SendByte(unsigned char DATA){
/*	UDR=DATA;
	while(!(UCSRA&(1<<TXC)));
    UCSRA|=(1<<TXC); //CLEAR the flag by writing logic 1
*/


     while(!(UCSRA&(1<<UDRE)));
     UDR=DATA;

}

void UART_sendString(const unsigned char*str){
	unsigned char i=0;
	while(str[i]!='\0'){
		UART_SendByte(str[i]);
		i++;
	}
}

/*you can also send length of the str instead of special char like $*/
void UART_receiveString(unsigned char*str){
	unsigned char i=0;
	str[i]=UART_ReceiveByte();
		while(str[i]!='$'){
			i++;
			str[i]=UART_ReceiveByte();

		}
		str[i] = '\0';
}
