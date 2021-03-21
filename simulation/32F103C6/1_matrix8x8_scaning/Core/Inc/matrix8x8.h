#ifndef MATRIX8X8_H
#define MATRIX8X8_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif
#define R1_Pin GPIO_PIN_0
#define R1_GPIO_Port GPIOA
#define R2_Pin GPIO_PIN_1
#define R2_GPIO_Port GPIOA
#define R3_Pin GPIO_PIN_2
#define R3_GPIO_Port GPIOA
#define R4_Pin GPIO_PIN_3
#define R4_GPIO_Port GPIOA
#define R5_Pin GPIO_PIN_4
#define R5_GPIO_Port GPIOA
#define R6_Pin GPIO_PIN_5
#define R6_GPIO_Port GPIOA
#define R7_Pin GPIO_PIN_6
#define R7_GPIO_Port GPIOA
#define R8_Pin GPIO_PIN_7
#define R8_GPIO_Port GPIOA

#define C8_Pin GPIO_PIN_15
#define C8_GPIO_Port GPIOA
#define C7_Pin GPIO_PIN_3
#define C7_GPIO_Port GPIOB
#define C6_Pin GPIO_PIN_4
#define C6_GPIO_Port GPIOB
#define C5_Pin GPIO_PIN_5
#define C5_GPIO_Port GPIOB
#define C4_Pin GPIO_PIN_6
#define C4_GPIO_Port GPIOB
#define C3_Pin GPIO_PIN_7
#define C3_GPIO_Port GPIOB
#define C2_Pin GPIO_PIN_8
#define C2_GPIO_Port GPIOB
#define C1_Pin GPIO_PIN_9
#define C1_GPIO_Port GPIOB
void Matrix8x8_Display_Symbol(uint8_t _sym );
void Matrix8x8_ShiftRL(uint8_t _sym);
#ifdef __cplusplus
}
#endif

#endif
