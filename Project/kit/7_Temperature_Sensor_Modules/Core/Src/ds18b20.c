/*
 * ds18b20.c
 *
 *  Created on: Mar 25, 2021
 *      Author: MICTEL
 */

#ifndef SRC_DS18B20_C_
#define SRC_DS18B20_C_
#include "main.h"
#include "ds18b20.h"
TIM_HandleTypeDef htimer;
void Delay_us(uint16_t time) {
	/* change your code here for the Delay_us in microseconds */
	__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
	while ((__HAL_TIM_GET_COUNTER(&htimer)) < time)
		;  // wait for the counter to reach the us input in the parameter
}

void Timer_1us_Init(uint8_t _freq, TIM_HandleTypeDef _htim,TIM_TypeDef* _Instance) {
	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	_htim.Instance = _Instance;
	_htim.Init.Prescaler = _freq - 1;
	_htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	_htim.Init.Period = 0xffff - 1;
	_htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	_htim.Init.RepetitionCounter = 0;
	_htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&_htim) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&_htim, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&_htim, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	htimer = _htim;
	HAL_TIM_Base_Start(&_htim);
}
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
uint8_t DS18B20_Start(void) {
	uint8_t Response = 0;
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set the pin as output
	HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0);  // pull the pin low
	Delay_us(480);   // Delay_us according to datasheet

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);    // set the pin as input
	Delay_us(80);    // Delay_us according to datasheet

	if (!(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)))
		Response = 1;    // if the pin is low i.e the presence pulse is detected
	else
		Response = -1;

	Delay_us(400); // 480 us Delay_us totally.

	return Response;
}

void DS18B20_Write(uint8_t data) {
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output

	for (int i = 0; i < 8; i++) {

		if ((data & (1 << i)) != 0)  // if the bit is high
				{
			// write 1

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0); // pull the pin LOW
			Delay_us(1);  // wait for 1 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
			Delay_us(50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0); // pull the pin LOW
			Delay_us(50);  // wait for 60 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
		}
	}
}

uint8_t DS18B20_Read(void) {
	uint8_t value = 0;

	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);

	for (int i = 0; i < 8; i++) {
		Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set as output

		HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, 0); // pull the data pin LOW
		Delay_us(1);  // wait for > 1us

		Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
		if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))  // if the pin is HIGH
				{
			value |= 1 << i;  // read = 1
		}
		Delay_us(50);  // wait for 60 us
	}
	return value;
}

#endif /* SRC_DS18B20_C_ */
