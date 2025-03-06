//START _KEYPAD_C
/*PARAMETER*/
#include "Keypad.h"
uint8_t SCANKEY(){
	uint32_t 	StuckButton = 0;
	
	  //SCAN ROW 1
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_4,GPIO_PIN_SET);
	//COL 1
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
		
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1)==1) 
		{
			return Data[0][0];
		}
		else return KEY_ERROR;
	}
	//COL 2
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2)) 
		{
			return Data[0][1];;
		}
		else return KEY_ERROR;
	}
	//COL 3
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3)) 
		{
			return Data[0][2];
		}
		else return KEY_ERROR;
	}
	
		  //SCAN ROW 2
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_1,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_4,GPIO_PIN_SET);
	//COL 1
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
		
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1)==1) 
		{
			return Data[1][0];
		}
		else return KEY_ERROR;
	}
	//COL 2
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2)) 
		{
			return Data[1][1];;
		}
		else return KEY_ERROR;
	}
	//COL 3
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3)) 
		{
			return Data[1][2];
		}
		else return KEY_ERROR;
	}
	

			  //SCAN ROW 3
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_1,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_4,GPIO_PIN_SET);
	//COL 1
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
		
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1)==1) 
		{
			return Data[2][0];
		}
		else return KEY_ERROR;
	}
	//COL 2
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2)) 
		{
			return Data[2][1];
		}
		else return KEY_ERROR;
	}
	//COL 3
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3)) 
		{
			return Data[2][2];
		}
		else return KEY_ERROR;
	}
	


			  //SCAN ROW 4
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_1,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEYPAD_PORT,ROW_4,GPIO_PIN_RESET);
	//COL 1
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
		
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_1)==1) 
		{
			return Data[3][0];
		}
		else return KEY_ERROR;
	}
	//COL 2
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_2)) 
		{
			return Data[3][1];
		}
		else return KEY_ERROR;
	}
	//COL 3
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0){
		HAL_Delay(20);
		StuckButton = HAL_GetTick();
		while((HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3) == 0)&(HAL_GetTick() - StuckButton < Stucktime));
	
	if(HAL_GPIO_ReadPin(KEYPAD_PORT, COL_3)) 
		{
			return Data[3][2];
		}
		else return KEY_ERROR;
	}
	
	return KEY_UNPRESS;
}

