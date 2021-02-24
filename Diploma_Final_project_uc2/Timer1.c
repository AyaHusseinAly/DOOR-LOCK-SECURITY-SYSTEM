/*
 * Timer1.c
 *
 *  Created on: Oct 20, 2016
 *      Author: Aya Hussein
 */

#include "Timer1.h"

unsigned char flag;
unsigned char tick=0;

void Timer1_init(unsigned short  CMP_Value){
	////mode_4
	flag=0;
	TCCR1A =(1<<FOC1A);
	TCCR1B=(1<<CS12)|(1<<CS10)|(1<<WGM12); //1024 prescalar then every count = 1 msec
	SREG |=(1<<7);
	TIMSK |=(1<<OCIE1A);
	TCNT1=0;

	OCR1A=CMP_Value;

}

void Timer1_stop(void)
{
	TCCR1A =0;
	TCCR1B=0;
	TIMSK =0;
	TCNT1=0;
	flag=0;
}

ISR(TIMER1_COMPA_vect){
	tick++;
	if(tick==TICK_NO){
		tick=0;
		flag=1;
	}
}
