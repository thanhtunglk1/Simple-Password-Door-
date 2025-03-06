/*START_KEYPAD_H
 *
 * Created: 8/10/2024 7:24:55 PM
 *  Author: NGUYEN THANH TUNG
 */ 
#ifndef _KEYPAD_H
#define _KEYPAD_H

/*-----------------------------------------------------------------
DECRIPTION: THIS FUNCTION SCAN ROW OF MATRIX KEY (TOP -> BOTTOM), RETURN KEY STATUS 
AND KEY_CODE OF THE BUTTON THAT YOU PRESS IN VARIABLE "key"

HOW TO USE: 'variable' 	= 	SCANKEY(); 
	RETURN:	Key value/KEY_UNPRESS/KEY_ERROR -> 'variable'
*/

/*INCLUDE----------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/*PORT*/
#define KEYPAD_PORT	GPIOA

/*ROW OUTPUT PUSH_PULL(SCAN)-------------------------------------------------*/ 
//ROW_1 is TOP
#define	ROW_1	GPIO_PIN_3
#define	ROW_2	GPIO_PIN_2
#define ROW_3	GPIO_PIN_1
#define ROW_4	GPIO_PIN_4 

/*COL INPUT PULL_UP(READ)--------------------------------------------------*/
//COL_1 is TOP
#define COL_1	GPIO_PIN_5
#define COL_2	GPIO_PIN_6
#define COL_3	GPIO_PIN_7


/*KEY_STATUS_RETURN------------------------------------------------*/
//#define KEY_SUCCESS	0x00
#define KEY_UNPRESS	0xFD
//#define KEY_STUCK		0xFE
#define KEY_ERROR		0xFF

#define Stucktime		3000
/*KEY CODE---------------------------------------------------*/
static uint8_t Data[4][3] = {{'7','8','9'},
														 {'4','5','6'},
														 {'1','2','3'},
														 {'*','0','#'}};

														 /*PROTOTYPE*/
/*-------------------------------------------------------------------
Decription	: SCAN MATRIX KEY, RETURN KEY STATUS AND KEYCODE 
	THAT YOY PRESS IN MATRIX KEY
	
@bief [in]	:	/none/

@bief	[out]	:	key  
	(KEY_CODE of the key you press in matrix key)
	
@return			:	KEY_VALUE	or	KEY_UNPRESS(0xFD)		or	KEY_ERROR(0xFE)
	(KEY STATUS)
*/
uint8_t SCANKEY(void);
														 
#endif
//END _KEYPAD_H