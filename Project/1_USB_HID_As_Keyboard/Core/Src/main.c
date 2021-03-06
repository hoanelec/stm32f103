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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
#define PRESS_SIZE 8
#define KeyIDLE	'I'
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
extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t press_report[PRESS_SIZE] = { 0 };
typedef struct {
	uint8_t MODIFIER;
	uint8_t RESERVED;
	uint8_t KEYCODE1;
	uint8_t KEYCODE2;
	uint8_t KEYCODE3;
	uint8_t KEYCODE4;
	uint8_t KEYCODE5;
	uint8_t KEYCODE6;
} keyboardHID;
keyboardHID keyboardhid = { 0, 0, 0, 0, 0, 0, 0, 0 };

char key[16] = { '1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C',
		'*', '0', '#', 'D' };
GPIO_TypeDef *gpio;
uint16_t row_gpio[4] = { GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4 }; //output
uint16_t col_gpio[4] = { GPIO_PIN_3, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_0 };
uint8_t flag = 0;
uint32_t debounceTime = 200;
uint32_t timerTick;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char KeypadRead() {
	uint8_t pin_temp;
	for (uint8_t i = 0; i < 4; i++) {
		for (int g = 0; g < 4; g++) {
			if (g != i) {
				HAL_GPIO_WritePin(GPIOA, row_gpio[g], GPIO_PIN_SET);
			} else {
				HAL_GPIO_WritePin(GPIOA, row_gpio[g], GPIO_PIN_RESET);
				pin_temp = g;
			}
		}
		HAL_Delay(1);
		for (uint8_t j = 0; j < 4; j++) {
			if (HAL_GPIO_ReadPin(GPIOA, col_gpio[j]) == GPIO_PIN_RESET) {
				while (HAL_GPIO_ReadPin(GPIOA, col_gpio[j]) == GPIO_PIN_RESET)
					;
				HAL_GPIO_WritePin(GPIOA, row_gpio[pin_temp], GPIO_PIN_SET);
				HAL_Delay(1);
				if(HAL_GetTick()- timerTick > debounceTime)
				{
					timerTick = HAL_GetTick();
					return key[i * 4 + j];
				}
			}
		}
	}
	HAL_GPIO_WritePin(GPIOA, row_gpio[pin_temp], GPIO_PIN_SET);
	HAL_Delay(1);
	return KeyIDLE;
}
void BasicSimulation() {
	keyboardhid.MODIFIER = 0x02; //press 'left shift'
	keyboardhid.KEYCODE1 = 0x04; //press 'a'
	keyboardhid.KEYCODE2 = 0x05; //press 'b'
	USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof(keyboardhid));
	HAL_Delay(50);
	keyboardhid.MODIFIER = 0x00; // release
	keyboardhid.KEYCODE1 = 0x00; //release
	keyboardhid.KEYCODE2 = 0x00; //press 'a'
	USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof(keyboardhid));
	HAL_Delay(1000);
}

//void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
//{
//  /* Check the parameters */
//  assert_param(IS_GPIO_PIN(GPIO_Pin));
//  assert_param(IS_GPIO_PIN_ACTION(PinState));
//
//  if (PinState != GPIO_PIN_RESET)
//  {
//    GPIOx->BSRR = GPIO_Pin;
//  }
//  else
//  {
//    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16u;
//  }
//}
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
	MX_USB_DEVICE_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		//BasicSimulation();
		char keyval = KeypadRead();
		if (keyval != KeyIDLE) {
			flag = 1;
			switch (keyval) {
			case '0':
				keyboardhid.KEYCODE1 = 0x27;
				break;
			case '1':
				keyboardhid.KEYCODE1 = 0x1E;
				break;
			case '2':
				keyboardhid.KEYCODE1 = 0x1F;
				break;
			case '3':
				keyboardhid.KEYCODE1 = 0x20;
				break;
			case '4':
				keyboardhid.KEYCODE1 = 0x21;
				break;
			case '5':
				keyboardhid.KEYCODE1 = 0x22;
				break;
			case '6':
				keyboardhid.KEYCODE1 = 0x23;
				break;
			case '7':
				keyboardhid.KEYCODE1 = 0x24;
				break;
			case '8':
				keyboardhid.KEYCODE1 = 0x25;
				break;
			case '9':
				keyboardhid.KEYCODE1 = 0x26;
				break;
			case 'A':
				keyboardhid.MODIFIER = 0x02;
				keyboardhid.KEYCODE1 = 0x04;
				break;
			case 'B':
				keyboardhid.MODIFIER = 0x02;
				keyboardhid.KEYCODE1 = 0x05;
				break;
			case 'C':
				keyboardhid.MODIFIER = 0x02;
				keyboardhid.KEYCODE1 = 0x06;
				break;
			case 'D':
				keyboardhid.MODIFIER = 0x02;
				keyboardhid.KEYCODE1 = 0x07;
				break;
			case '*':
				keyboardhid.MODIFIER = 0x02;
				keyboardhid.KEYCODE1 = 0x25;
				break;
			case '#':
				keyboardhid.MODIFIER = 0x02;
				keyboardhid.KEYCODE1 = 0x20;
				break;
			}
			if (flag == 1) {
				USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid,sizeof(keyboardhid));
				HAL_Delay(50);
				keyboardhid.MODIFIER = 0x00; // release
				keyboardhid.KEYCODE1 = 0x00; //release
				USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid,sizeof(keyboardhid));
				flag = 0;
			}

		}
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
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
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
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : PA0 PA1 PA2 PA3 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PA4 PA5 PA6 PA7 */
	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
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
