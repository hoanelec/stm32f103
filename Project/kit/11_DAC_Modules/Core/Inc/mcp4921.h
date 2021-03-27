#ifndef NCP4921_H
#define NCP4921_H
#include "main.h"
#define SCLK_soft_Pin GPIO_PIN_0
#define SCLK_soft_GPIO_Port GPIOA
#define MOSI_soft_Pin GPIO_PIN_1
#define MOSI_soft_GPIO_Port GPIOA
#define SS_soft_Pin GPIO_PIN_2
#define SS_soft_GPIO_Port GPIOA
void SPI_Soft_GPIO_Init();
void MCP4921_SPI_Soft_Send(uint16_t adc_val);
#endif
