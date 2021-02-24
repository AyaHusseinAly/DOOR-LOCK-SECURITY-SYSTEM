/*
 * keypad.h
 *
 *  Created on: Sep 21, 2018
 *      Author: Aya Hussein
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define N_COL 3
#define N_ROW 4

#include "uc_config.h"

#define keypad_OUT_PORT PORTA
#define keypad_IN_PORT PINA
#define keypad_PORT_DIR DDRA

unsigned char get_key(void);


#endif /* KEYPAD_H_ */
