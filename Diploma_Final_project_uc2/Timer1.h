/*
 * Timer1.h
 *
 *  Created on: Oct 20, 2016
 *      Author: Aya Hussein
 */

#ifndef TIMER1_H_
#define TIMER1_H_


#include "uc_config.h"

/*value to compare with*/
#define TICK_NO 2 /*rise the flag after how many ticks ?*/

extern unsigned char flag;

void Timer1_init(unsigned short  CMP_Value); /*CMP_Value is time by ms devided by TICK_NO which is defined by 2 here*/
void Timer1_stop(void);

#endif /* TIMER1_H_ */
