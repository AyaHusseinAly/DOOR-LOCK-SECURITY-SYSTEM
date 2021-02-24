/*
 * UART.h
 *
 *  Created on: Oct 3, 2018
 *      Author: Aya Hussein
 */

#ifndef UART_H_
#define UART_H_


#include "uc_config.h"

#define BAUD 9600

void UART_init(void);
unsigned char UART_ReceiveByte(void);
void UART_SendByte(unsigned char DATA);
void UART_sendString(const unsigned char*str);
void UART_receiveString(unsigned char*str);

#endif /* UART_H_ */
