/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define RS_Port GPIOA
#define EN_Port GPIOA
#define D4_Port GPIOA
#define D5_Port GPIOA
#define D6_Port GPIOA

#define D7_Port GPIOA
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LCD_Enable() {
	HAL_GPIO_WritePin(EN_Port, EN_Pin, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(EN_Port, EN_Pin, 0);
	HAL_Delay(1);
}

void LCD_Send4Bit(unsigned char Data) {
	HAL_GPIO_WritePin(D4_Port, D4_Pin, Data & 0x01);
	HAL_GPIO_WritePin(D5_Port, D5_Pin, (Data >> 1) & 0x01);
	HAL_GPIO_WritePin(D6_Port, D6_Pin, (Data >> 2) & 0x01);
	HAL_GPIO_WritePin(D7_Port, D7_Pin, (Data >> 3) & 0x01);
}

void LCD_SendCommand(unsigned char command) {
	LCD_Send4Bit(command >> 4);
	LCD_Enable();
	LCD_Send4Bit(command);
	LCD_Enable();
}

void LCD_Clear() {
	LCD_SendCommand(0x01);
	HAL_Delay(1);
}

void LCD_Init() {
	LCD_Send4Bit(0x00);
	HAL_GPIO_WritePin(RS_Port, RS_Pin, 0);
	LCD_Send4Bit(0x03);
	LCD_Enable();
	LCD_Enable();
	LCD_Enable();
	LCD_Send4Bit(0x02);
	LCD_Enable();
	LCD_SendCommand(0x28);
	LCD_SendCommand(0x0C);
	LCD_SendCommand(0x06);
	LCD_SendCommand(0x01);
}

void LCD_Gotoxy(unsigned char x, unsigned char y) {
	unsigned char address;
	if (y == 0)
		address = 0x80;
	else if (y == 1) {
		address = 0xc0;
	} else if (y == 2) {
		address = 0x94;
	} else
		address = 0xd4;
	address += x;
	LCD_SendCommand(address);
}

void LCD_PutChar(unsigned char Data) {
	HAL_GPIO_WritePin(RS_Port, RS_Pin, 1);
	LCD_SendCommand(Data);
	HAL_GPIO_WritePin(RS_Port, RS_Pin, 0);
}

void LCD_Puts(char *s) {
	while (*s) {
		LCD_PutChar(*s);
		s++;
	}
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	/* USER CODE BEGIN 2 */
	LCD_Init();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		LCD_Gotoxy(0, 0);
		LCD_Puts("0123456789111213");
		LCD_Gotoxy(0, 1);
		LCD_Puts("1415161718192021");
		HAL_Delay(1000);
		LCD_Clear();
		LCD_Gotoxy(1, 0);
		LCD_Puts("STM32-Bulebill");
		LCD_Gotoxy(1, 1);
		LCD_Puts("Parallel mode");
		HAL_Delay(1000);
		LCD_Clear();
		/*LCD 20x4*/
//		 LCD_Gotoxy(0, 0);
//		LCD_Puts("01234567891011213141");
//		LCD_Gotoxy(0, 1);
//		LCD_Puts("21222324252627282930");
//		LCD_Gotoxy(3, 2);
//		LCD_Puts("STM32-Bulebill");
//		LCD_Gotoxy(3, 3);
//		LCD_Puts("Parallel mode");
//		HAL_Delay(1000);
//		LCD_Clear();

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA,
	RS_Pin | EN_Pin | D4_Pin | D5_Pin | D6_Pin | D7_Pin,
	GPIO_PIN_RESET);

	/*Configure GPIO pins : RS_Pin EN_Pin D4_Pin D5_Pin
	 D6_Pin D7_Pin */
	GPIO_InitStruct.Pin = RS_Pin | EN_Pin | D4_Pin | D5_Pin | D6_Pin | D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
