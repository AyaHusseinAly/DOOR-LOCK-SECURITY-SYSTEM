/*
 * keypad.c
 *
 *  Created on: Sep 21, 2018
 *      Author: Aya Hussein
 */


#include "keypad.h"
/*keypad col is connected to PORTA first 4 are for rows and second for col*/

/*a FN to implement the number into the right key on keypad*/
#if(N_COL==4)
static unsigned char keypad4x4(unsigned char key);
#elif (N_COL==3)
static unsigned char keypad4x3(unsigned char key);
#endif


#if(N_COL==3)
static unsigned char keypad4x3(unsigned char key){
	switch (key)	{
	case 10: return '*'; // ASCII Code of =
			 break;
	case 11: return 0;
			 break;
	case 12: return '#'; // ASCII Code of +
			 break;

	default :
		return key;
		break;

	}
}



#elif(N_COL==4)
	static unsigned char keypad4x4(unsigned char key){

		switch (key)
		{
		case 1:
			return 7;
			break;

		case 2:
			return 8;
			break;

		case 3:
			return 9;
			break;
		case 4:
			return '%'; // ASCII Code of %
			break;
		case 5:
			return 4;
			break;

		case 6:
			return 5;
			break;

		case 7:
			return 6;
			break;

		case 8:
			return '*'; /* ASCII Code of '*' */
			break;
		case 9:
			return 1;
			break;

		case 10:
			return 2;
			break;

		case 11:
			return 3;
			break;
		case 12:
			return '-'; /* ASCII Code of '-' */
			break;
		case 14:
			return 0;
			break;

		case 15: return '='; /* ASCII Code of '=' */
				break;
		case 16: return '+'; /* ASCII Code of '+' */
				break;
		default :
			return key;
			break;


		}

	}

#endif



unsigned char get_key(void){
		unsigned char row,col;
		while(1){
			for(col=0;col<N_COL;col++){
				keypad_PORT_DIR=(0b00010000<<col);
				keypad_OUT_PORT=~(0b00010000<<col);
				for(row=0;row<N_ROW; row++){

					if(!(keypad_IN_PORT &(1<<row))){
#if(N_COL == 4)
						return keypad4x4(row*N_COL+col+1);
#elif(N_COL == 3)
						return keypad4x3(row*N_COL+col+1);
#endif
					}
				}

			}
		}
}


