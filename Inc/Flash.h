/*START_LCD4BIT
 *
 * Created: 8/10/2024 7:24:55 PM
 *  Author: NGUYEN THANH TUNG
 */ 
#ifndef __FLASH_H_
#define __FLASH_H_

#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdio.h"

void FLASH_ERASE(uint32_t address);

void FLASH_WRITE_Int(uint32_t address,int value);
void FLASH_WRITE_Float(uint32_t address,float value);
void FLASH_WRITE_Array(uint32_t address,uint8_t *array, uint16_t lengh);

int FLASH_READ_Int(uint32_t address);
float FLASH_READ_Float(uint32_t address);
void FLASH_READ_Array(uint32_t address,uint8_t *array, uint16_t lengh);

#endif
