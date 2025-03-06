#include "Flash.h"

//xoa 1 page, truyen vao dia chi page muon xoa
void FLASH_ERASE(uint32_t address){
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef ERASE_Init_Struct;
	ERASE_Init_Struct.Banks = 1;
	ERASE_Init_Struct.NbPages = 1;
	ERASE_Init_Struct.PageAddress = address;
	ERASE_Init_Struct.TypeErase = FLASH_TYPEERASE_PAGES;
	uint32_t Nothing;
	HAL_FLASHEx_Erase(&ERASE_Init_Struct,&Nothing);
	HAL_FLASH_Lock();
}

//LUU 1 KI TU VAO FLASH
//truyen vao ham (dia chi flash, gia tri muon luu)
void FLASH_WRITE_Int(uint32_t address,int value){
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address,value);
	HAL_FLASH_Lock();
}

//GHI FLOAT VAO FLASH
//truyen vao ham (dia chi flash, gia tri muon luu)
void FLASH_WRITE_Float(uint32_t address,float value){
	HAL_FLASH_Unlock();
	uint8_t data[4];
	*(float*)data = value;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,address,*(uint32_t *)data);
	HAL_FLASH_Lock();
}

//GHI MANG
//khoi tao mang trong main.c, truyen vao ham (dia chi flash, mang, do dai muon luu)
void FLASH_WRITE_Array(uint32_t address,uint8_t *array, uint16_t lengh){
	HAL_FLASH_Unlock();
	uint16_t *pt = (uint16_t*)array;
	for(uint16_t i=0;i<(lengh+1)/2;i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,address + 2*i,*pt);
		pt++;
	}
	HAL_FLASH_Lock();
}

//DOC 1 KI TU TU FLASH
//truyen vao ham (dia chi flash)
int FLASH_READ_Int(uint32_t address){
	return *(__IO uint16_t *)(address);
}

//DOC FLOAT TU  FLASH
//truyen vao ham (dia chi flash)
float FLASH_READ_Float(uint32_t address){
	uint32_t data = *(__IO uint16_t *)(address);
	return *(float*)(data);
}
//khoi tao mang trong main.c, truyen vao ham (dia chi flash, mang, do dai muon doc)
void FLASH_READ_Array(uint32_t address,uint8_t *array, uint16_t lengh){
	uint16_t *pt = (uint16_t*)array;
	for(uint16_t i=0;i<(lengh+1)/2;i++){
		*pt = *(__IO uint16_t *)(address + 2*i);
		pt++;
	}
}