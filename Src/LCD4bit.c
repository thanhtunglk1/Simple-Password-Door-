/*PARAMETER*/
#include "LCD4bit.h"
void LCD_WRITE(uint8_t data){
	//Ghi du lieu 4bit ra LCD 
	HAL_GPIO_WritePin(LCD_GPIO,LCD_D4,(data>>0)&0x01);
	HAL_GPIO_WritePin(LCD_GPIO,LCD_D5,(data>>1)&0x01);
	HAL_GPIO_WritePin(LCD_GPIO,LCD_D6,(data>>2)&0x01);
	HAL_GPIO_WritePin(LCD_GPIO,LCD_D7,(data>>3)&0x01);
	
	//Tao xung canh xuong chan E
	HAL_GPIO_WritePin(LCD_GPIO,LCD_E,1);
	HAL_Delay(1); //delay 1ms
	HAL_GPIO_WritePin(LCD_GPIO,LCD_E,0);
}

// DIEU CHINH LCD/XUAT DU LIEU RA LCD
void LCD_SEND(uint8_t Reg,uint8_t data){
						//CMD_REG  0	// 8bit cmd
						//DATA_RED 1	// 8bit data
	HAL_GPIO_WritePin(LCD_GPIO,LCD_RS,Reg);
	LCD_WRITE(data>>4); //xuat 4bit cao
	LCD_WRITE(data);		//xuat 4bit thap
}

// TAO NGUON LCD
void LCD_Init(void){
//	HAL_GPIO_WritePin(LCD_GPIO,LCD_RW, 0);// CAU HINH LCD MODE XUAT Data
	LCD_SEND(CMD_REG,LCD_KhoiTao1); 			//KHOI TAO BAN DAU LCD
	LCD_SEND(CMD_REG,LCD_KhoiTao2);				//KHOI TAO LCD
	LCD_SEND(CMD_REG,LCD_4bit);						//MODE 4BIT, 2 HANG 5X7
	LCD_SEND(CMD_REG,LCD_Clear_No_Point);	//HIEN LCD, TAT CON TRO
	LCD_SEND(CMD_REG,LCD_INC_Point);			//TANG CON TRO
	LCD_SEND(CMD_REG,LCD_Clear);					//XOA MAN HINH
}

// Xoa man hinh LCD
void LCD_CLEAR_SCREEN(){
	LCD_SEND(CMD_REG,LCD_Clear);					//XOA MAN HINH
}

void LCD_ROW_COL(uint8_t hang,uint8_t cot){
							// hang [1;2] , cot [0;15] 
	if(hang == 1) LCD_SEND(CMD_REG,0x80 + cot); //dich toi vi tri hang 1 LCD
	else if(hang == 2) LCD_SEND(CMD_REG,0xC0 + cot); //dich toi vi tri hang 2 LCD 
}

//Xuat chuoi ki tu ra LCD
void LCD_WRITE_STRING(char* string){
	for(uint8_t i=0; i< strlen(string);i++){
		LCD_SEND(DATA_REG,string[i]);
	}
}

//Xuat 1 so ra LCD
void LCD_WRITE_NUMBER(int NUMBER){
	char buffer[8];
	sprintf(buffer,"%d",NUMBER);
	LCD_WRITE_STRING(buffer	);
}

void LCD_WRITE_ASCCI(uint8_t data){
	LCD_SEND(DATA_REG,data);
}