#ifndef __7SEG8LED_H
#define __7SEG8LED_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
#define A_Pin GPIO_PIN_0
#define A_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_1
#define B_GPIO_Port GPIOA
#define C_Pin GPIO_PIN_2
#define C_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_3
#define D_GPIO_Port GPIOA
#define E_Pin GPIO_PIN_4
#define E_GPIO_Port GPIOA
#define F_Pin GPIO_PIN_5
#define F_GPIO_Port GPIOA
#define G_Pin GPIO_PIN_6
#define G_GPIO_Port GPIOA
#define H_Pin GPIO_PIN_7
#define H_GPIO_Port GPIOA

#define L1_Pin GPIO_PIN_0
#define L1_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_1
#define L2_GPIO_Port GPIOB
#define L3_Pin GPIO_PIN_3
#define L3_GPIO_Port GPIOB
#define L4_Pin GPIO_PIN_4
#define L4_GPIO_Port GPIOB
#define L5_Pin GPIO_PIN_5
#define L5_GPIO_Port GPIOB
#define L6_Pin GPIO_PIN_6
#define L6_GPIO_Port GPIOB
#define L7_Pin GPIO_PIN_7
#define L7_GPIO_Port GPIOB
#define L8_Pin GPIO_PIN_8
#define L8_GPIO_Port GPIOB
 void display7seg(uint8_t _led,uint8_t _number);
 void display7segShiftRL();

#ifdef __cplusplus
}
#endif

#endif
