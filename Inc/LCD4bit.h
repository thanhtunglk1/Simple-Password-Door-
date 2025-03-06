/*START_LCD4BIT
 *
 * Created: 8/10/2024 7:24:55 PM
 *  Author: NGUYEN THANH TUNG
 */
#ifndef __LCD4bit_H_
#define __LCD4bit_H_

/*INCLUDE*/
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"

/*DEFINE*/
#define LCD_GPIO	GPIOB

#define LCD_RS		GPIO_PIN_0
//#define LCD_RW		GPIO_PIN_1
#define LCD_E			GPIO_PIN_1

#define LCD_D4		GPIO_PIN_15
#define LCD_D5		GPIO_PIN_14
#define LCD_D6		GPIO_PIN_13
#define LCD_D7		GPIO_PIN_12

#define CMD_REG		0
#define	DATA_REG	1

#define LCD_KhoiTao1				0x33
#define LCD_KhoiTao2				0x32
#define	LCD_4bit						0x28
#define	LCD_Clear_No_Point	0x0C
#define LCD_INC_Point				0x06
#define	LCD_Clear						0x01

/*PROTOTYPE*/
void LCD_WRITE(uint8_t data);
void LCD_SEND(uint8_t Reg,uint8_t data); //CAU HINH (CMD_REG) 
																				 //HOAC XUAT MA HEX(DATA_REG) RA LCD
void LCD_Init(void);//KHOI TAO LCD
void LCD_CLEAR_SCREEN(); //XOA MAN HINH
void LCD_ROW_COL(uint8_t hang,uint8_t cot);
void LCD_WRITE_STRING(char* string); //XUAT CHUOI KI TU
void LCD_WRITE_NUMBER(int NUMBER);	 //XUAT SO
void LCD_WRITE_ASCCI(uint8_t data);
#endif
//END_LCD4BIT