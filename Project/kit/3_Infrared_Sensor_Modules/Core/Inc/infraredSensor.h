#ifndef INFRARED_H
#define INFRARED_H
#include "main.h"
#define IR_in GPIO_PIN_0
#define IR_in_detect_analyer GPIO_PIN_1
#define IR_ou GPIO_PIN_3
#define IR_out_detect_analyer GPIO_PIN_4
#define IR_SEND_OK 1
#define IR_SEND_FAIL 0
#define IR_RECEIVE_FAIL 0
void Timer_1us_Init(uint8_t _freq, TIM_HandleTypeDef _htim,
		TIM_TypeDef *_Instance);
void Delay_us(uint16_t time) ;
void SendPart(uint8_t _part) ;
uint32_t NEC_Infrared_Send_Data(uint8_t address, uint8_t data) ;
uint8_t NEC_Infrared_get_Data(uint32_t frame) ;
uint32_t NEC_Infrared_Read() ;
uint32_t NEC_Infrared_Read_specify(uint8_t address) ;
#endif
