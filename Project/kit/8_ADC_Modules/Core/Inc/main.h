/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define O0_Pin GPIO_PIN_0
#define O0_GPIO_Port GPIOA
#define O1_Pin GPIO_PIN_1
#define O1_GPIO_Port GPIOA
#define O2_Pin GPIO_PIN_2
#define O2_GPIO_Port GPIOA
#define O3_Pin GPIO_PIN_3
#define O3_GPIO_Port GPIOA
#define O4_Pin GPIO_PIN_4
#define O4_GPIO_Port GPIOA
#define O5_Pin GPIO_PIN_5
#define O5_GPIO_Port GPIOA
#define O6_Pin GPIO_PIN_6
#define O6_GPIO_Port GPIOA
#define O7_Pin GPIO_PIN_7
#define O7_GPIO_Port GPIOA
#define ADD_A_Pin GPIO_PIN_0
#define ADD_A_GPIO_Port GPIOB
#define ADD_B_Pin GPIO_PIN_1
#define ADD_B_GPIO_Port GPIOB
#define ADD_C_Pin GPIO_PIN_3
#define ADD_C_GPIO_Port GPIOB
#define START_Pin GPIO_PIN_6
#define START_GPIO_Port GPIOB
#define EOC_Pin GPIO_PIN_7
#define EOC_GPIO_Port GPIOB
#define ALE_Pin GPIO_PIN_8
#define ALE_GPIO_Port GPIOB
#define OE_Pin GPIO_PIN_9
#define OE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
