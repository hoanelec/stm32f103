#ifndef ADC0809_H
#define ADC0809_H
#include "main.h"
//digital outputs
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
//channel selections
#define ADD_A_Pin GPIO_PIN_0
#define ADD_A_GPIO_Port GPIOB
#define ADD_B_Pin GPIO_PIN_1
#define ADD_B_GPIO_Port GPIOB
#define ADD_C_Pin GPIO_PIN_3
#define ADD_C_GPIO_Port GPIOB
//condition pins
#define CLK_Pin GPIO_PIN_5
#define CLK_GPIO_Port GPIOB
#define START_Pin GPIO_PIN_6
#define START_GPIO_Port GPIOB
#define EOC_Pin GPIO_PIN_7
#define EOC_GPIO_Port GPIOB
#define ALE_Pin GPIO_PIN_8
#define ALE_GPIO_Port GPIOB
#define OE_Pin GPIO_PIN_9
#define OE_GPIO_Port GPIOB
uint8_t Read_ADC_PIN(void);
uint8_t ADC0809_Read(uint8_t _channel);
#endif
