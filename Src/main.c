/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "LCD4bit.h"
#include "Keypad.h"
#include "Flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CLOCK_SYSTEM 8000000U
#define ADDRESS_PASS_STORAGE 0x800FC00 //PAGE 63 FLASH

/*DEFINE*/
#define CORRECT_P	0x00
#define INCORRECT_P	0xFF
#define NOTHING	0xFE
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */
RTC_TimeTypeDef TIME_RTC;
RTC_DateTypeDef DATE_RTC;
uint8_t Count_Wrong = 0; 
uint8_t pass[8] = {'1','2','3','4','5','6','7','8'};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//bao loi de phim
void LCD_ERROR_ANOUNCE(){
	LCD_CLEAR_SCREEN();
	LCD_ROW_COL(1,2);
	LCD_WRITE_STRING("DO NOT HOLD");
	LCD_ROW_COL(2,2);
	LCD_WRITE_STRING("THE BUTTON");
	HAL_Delay(1500);
	LCD_CLEAR_SCREEN();
}

void SET_PASS_DEFAUT(){
	FLASH_ERASE(ADDRESS_PASS_STORAGE);
	FLASH_WRITE_Array(ADDRESS_PASS_STORAGE,pass,8);
}


//ham doc password
void ENTER_PASS(){
	uint8_t i=0;
	uint8_t password = KEY_UNPRESS;
	LCD_WRITE_STRING("ENTER PASSWORD");
	while(i<8){
		while(password == KEY_UNPRESS){
			 password = SCANKEY();
		}
		
		switch(password){
			case '*':
				i--;
				if(i<0) i=0;
				LCD_ROW_COL(2,i);
				LCD_WRITE_STRING(" ");
				password = KEY_UNPRESS;
				HAL_Delay(300);
				break;
			case KEY_ERROR: 
				LCD_ERROR_ANOUNCE();
				LCD_WRITE_STRING("ENTER PASSWORD");
				password = KEY_UNPRESS;
				i=0;
				break;
			default:
				pass[i]= password;
				LCD_ROW_COL(2,i);
				LCD_WRITE_ASCCI(password);
				password = KEY_UNPRESS;
				i++;
				HAL_Delay(300);
				break;
		}
	}
}

//kiem tra pass
uint8_t CHECK_PASS(){
	uint8_t LOOP;
	uint8_t pass_stogare[8]={0};
	uint8_t RIGHT = 0;
	LCD_CLEAR_SCREEN();
	ENTER_PASS();
	FLASH_READ_Array(ADDRESS_PASS_STORAGE,pass_stogare,8);
	if(Count_Wrong < 3){
			for(uint8_t k=0;k<8;k++){
				if(pass[k]== pass_stogare[k]) RIGHT++;
			}
			if(RIGHT==8){
						Count_Wrong = 0;
						return CORRECT_P; 
					}
				else{
						Count_Wrong++;
						return INCORRECT_P;
				}		
	}
	else{		
			Count_Wrong++;
			LCD_CLEAR_SCREEN();
			LCD_ROW_COL(1,2);
			LCD_WRITE_STRING("TRYING AFTER");
			LOOP = (Count_Wrong - 3)*5;
			while(LOOP !=0){
				LCD_ROW_COL(2,6);
				LCD_WRITE_NUMBER(LOOP);
				HAL_Delay(1000);
				LOOP=LOOP-1;
				LCD_ROW_COL(2,7);
				LCD_WRITE_STRING(" ");
			}
	}
	return NOTHING;
}
//dieu khien relay
void OPEN_DOOR(){
	uint8_t LOOP = 10;
	switch(CHECK_PASS()){
		case CORRECT_P:
			LCD_CLEAR_SCREEN();
			LCD_ROW_COL(1,2);
			LCD_WRITE_STRING("PASSWORD");
			LCD_ROW_COL(2,2);
			LCD_WRITE_STRING("CORRECT");
			HAL_Delay(800);
			LCD_CLEAR_SCREEN();
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
			LCD_ROW_COL(1,2);
			LCD_WRITE_STRING("DOOR OPEN");
			LCD_ROW_COL(2,2);
			while(LOOP !=0 ){
				LCD_ROW_COL(2,6);
				LCD_WRITE_NUMBER(LOOP);
				HAL_Delay(1000);
				LOOP=LOOP-1;
				LCD_ROW_COL(2,7);
				LCD_WRITE_STRING(" ");
			}
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			break;
		case INCORRECT_P:
			LCD_CLEAR_SCREEN();
			LCD_ROW_COL(1,2);
			LCD_WRITE_STRING("PASSWORD");
			LCD_ROW_COL(2,2);
			LCD_WRITE_STRING("INCORRECT");
			HAL_Delay(800);
			break;
		default: break;
	}
}

void CHANGE_PASS(){
	uint8_t RIGHT = 0;
	uint8_t pass_second[8] = {0};
	switch(CHECK_PASS()){
		case CORRECT_P:
			LCD_CLEAR_SCREEN();
			LCD_ROW_COL(1,0);
			LCD_WRITE_STRING("CHANGE PASSWORD");
			HAL_Delay(800);
			CHECK_PASS();
			for(uint8_t k=0;k<8;k++){
				pass_second[k] = pass[k];
			}
			LCD_CLEAR_SCREEN();
			LCD_ROW_COL(1,0);
			LCD_WRITE_STRING("ONE MORE TIME");
			HAL_Delay(800);
			CHECK_PASS();
			LCD_CLEAR_SCREEN();
			for(uint8_t i=0;i<8;i++){
				if(pass_second[i] == pass[i]) RIGHT++;
			}
			if(RIGHT==8){
				Count_Wrong = 0;
				FLASH_ERASE(ADDRESS_PASS_STORAGE);
				FLASH_WRITE_Array(ADDRESS_PASS_STORAGE,pass,8);
/*				for(uint8_t z=0;z<8;z++){
					pass_second[z]=pass[z];
			}*/
				LCD_ROW_COL(1,2);
				LCD_WRITE_STRING("PASS CHANGE");
				LCD_ROW_COL(2,2);
				LCD_WRITE_STRING("SUCCESS");
				HAL_Delay(800);		
				LCD_CLEAR_SCREEN();	
			}
				else{
				LCD_ROW_COL(1,2);
				LCD_WRITE_STRING("PASSWORD");
				LCD_ROW_COL(2,2);
				LCD_WRITE_STRING("NOT MATCH");
				HAL_Delay(800);	
				LCD_CLEAR_SCREEN();	
				}
			Count_Wrong = 0;
			break;
		case INCORRECT_P:
			LCD_CLEAR_SCREEN();
			LCD_ROW_COL(1,2);
			LCD_WRITE_STRING("PASSWORD");
			LCD_ROW_COL(2,2);
			LCD_WRITE_STRING("INCORRECT");
			HAL_Delay(800);
			break;
		default: break;
	}
}

void LCD_Inf(){
	LCD_ROW_COL(1,1);
	LCD_WRITE_STRING("BTL EE3003 DT01");
	LCD_ROW_COL(2,2);
	LCD_WRITE_STRING("CUA PASSWORD");
}

void TIME_DATE(){
	char TIME_DATE[14]={0};
	uint16_t i=10;
	LCD_CLEAR_SCREEN();
	while(i!=0){
		HAL_RTC_GetTime(&hrtc,&TIME_RTC,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&DATE_RTC,RTC_FORMAT_BIN);
		sprintf(TIME_DATE,"TIME: %d:%d:%d",TIME_RTC.Hours,TIME_RTC.Minutes,TIME_RTC.Seconds);
		LCD_ROW_COL(1,0);
		LCD_WRITE_STRING(TIME_DATE);
		sprintf(TIME_DATE,"DATE: %d-%d-20%d",
		DATE_RTC.Date,DATE_RTC.Month,DATE_RTC.Year);
		LCD_ROW_COL(2,0);
		LCD_WRITE_STRING(TIME_DATE);
		HAL_Delay(1000);
		i--;
	}

	LCD_CLEAR_SCREEN();
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	SET_PASS_DEFAUT();
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
  while (1)
  {
		switch(SCANKEY()){
			case '*': OPEN_DOOR();
								break;
			case '#': CHANGE_PASS();
								break;
			case '0': TIME_DATE();
								break;
			case KEY_ERROR: LCD_ERROR_ANOUNCE();
								break;
			default	: LCD_Inf();
								break;
		}
		HAL_Delay(50);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x10;
  sTime.Minutes = 0x1;
  sTime.Seconds = 0x45;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
  DateToUpdate.Month = RTC_MONTH_AUGUST;
  DateToUpdate.Date = 0x20;
  DateToUpdate.Year = 0x24;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB12 PB13
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
