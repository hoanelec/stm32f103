#include "infraredSensor.h"
TIM_HandleTypeDef htimer;
void Delay_us(uint16_t time) {
	/* change your code here for the Delay_us in microseconds */
	__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
	while ((__HAL_TIM_GET_COUNTER(&htimer)) < time)
		;  // wait for the counter to reach the us input in the parameter
}

void Timer_1us_Init(uint8_t _freq, TIM_HandleTypeDef _htim,
		TIM_TypeDef *_Instance) {
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
void SendPart(uint8_t _part) {
	for (int i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(GPIOB, IR_ou, GPIO_PIN_SET);
		__HAL_TIM_SET_COUNTER(&htimer, 0);
		while ((uint16_t) __HAL_TIM_GET_COUNTER(&htimer) < 562)
			;  // 562.5µs
		HAL_GPIO_WritePin(GPIOB, IR_ou, GPIO_PIN_RESET);

		__HAL_TIM_SET_COUNTER(&htimer, 0);

		uint8_t bit = (_part >> i) & 0x01;
		if (bit) {
			while ((uint16_t) __HAL_TIM_GET_COUNTER(&htimer) < 1687)
				;  //1.6875ms
		} else {
			while ((uint16_t) __HAL_TIM_GET_COUNTER(&htimer) < 562)
				;
		}

	}
}
uint32_t NEC_Infrared_Send_Data(uint8_t address, uint8_t data) {
	if (HAL_GPIO_ReadPin(GPIOB, IR_in))
		return IR_SEND_FAIL;
	//START CONDITION
	//generate 9ms high pulse
	//generate 4ms low pulse
	HAL_GPIO_WritePin(GPIOB, IR_ou, GPIO_PIN_SET);
	__HAL_TIM_SET_COUNTER(&htimer, 0);
	while ((uint16_t) __HAL_TIM_GET_COUNTER(&htimer) < 9000)
		;
	HAL_GPIO_WritePin(GPIOB, IR_ou, GPIO_PIN_RESET);
	__HAL_TIM_SET_COUNTER(&htimer, 0);
	while ((uint16_t) __HAL_TIM_GET_COUNTER(&htimer) < 4500)
		;

	//START SENDING
	SendPart(address);	//Send address
	SendPart(~address);	//Send inverted address
	SendPart(data);	//Send data
	SendPart(~data);	//Send inverted data

	//STOP MESSAGE
	//a final 562.5µs pulse burst to signify the end of message transmission
	HAL_GPIO_WritePin(GPIOB, IR_ou, GPIO_PIN_SET);
	__HAL_TIM_SET_COUNTER(&htimer, 0);
	while ((uint16_t) __HAL_TIM_GET_COUNTER(&htimer) < 562)
		;
	HAL_GPIO_WritePin(GPIOB, IR_ou, GPIO_PIN_RESET);
	return IR_SEND_OK;
}
uint8_t NEC_Infrared_get_Data(uint32_t frame) {
	if (frame == 0)
		return IR_RECEIVE_FAIL;
	return ((frame>>8)&0xff) ;
}
uint32_t NEC_Infrared_Read_specify(uint8_t address) {
	uint32_t code = 0;
	uint16_t cnt_val = 0;
	if (HAL_GPIO_ReadPin(GPIOB, IR_in)) {
		HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_SET);

		__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
		while (HAL_GPIO_ReadPin(GPIOB, IR_in))
			;

		HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_RESET);
		cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
		if (cnt_val > 7000 && cnt_val < 10000) {
			//checked 9ms high pulse
			__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
			while (!HAL_GPIO_ReadPin(GPIOB, IR_in))
				;  //wait for 4.5ms
			cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
			HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_SET);

			if (cnt_val > 4000 && cnt_val < 6000) {
				for (int i = 0; i < 32; i++) {
					if(i==8)
					{
						if((code>>24) != address)
							return IR_RECEIVE_FAIL;
					}
					while ((HAL_GPIO_ReadPin(GPIOB, IR_in)))
						; // wait for pin to go low..
					__HAL_TIM_SET_COUNTER(&htimer, 0); // set the counter value a 0
					HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer,
							GPIO_PIN_RESET);
					while (!(HAL_GPIO_ReadPin(GPIOB, IR_in)))
						;  //wait for pin to go high this is 562.5us high
					HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer,
							GPIO_PIN_SET);
					cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
					if (cnt_val > 1550 && cnt_val < 1700) {
						// Logical '1' – a 562.5µs pulse burst followed by a 1.6875ms space, with a total transmit time of 2.25ms
						code |= (1UL << (31 - i));   // write 1
					} else if (cnt_val > 500 && cnt_val < 600) {
						//Logical '0' – a 562.5µs pulse burst followed by a 562.5µs space, with a total transmit time of 1.125m
						code &= ~(1UL << (31 - i));
					} else
						return IR_RECEIVE_FAIL;  // unknown signal

				}
				while (!HAL_GPIO_ReadPin(GPIOB, IR_in))
					;
				__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
				HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_SET);
				while (HAL_GPIO_ReadPin(GPIOB, IR_in))
					;  //end of message
				cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
				HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_RESET);
				if (cnt_val > 550 && cnt_val < 650) // end conversion
					return code;
			}
		}
	}
	return code;
}
uint32_t NEC_Infrared_Read() {
	uint32_t code = 0;
	uint16_t cnt_val = 0;
	if (HAL_GPIO_ReadPin(GPIOB, IR_in)) {
		HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_SET);

		__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
		while (HAL_GPIO_ReadPin(GPIOB, IR_in))
			;

		HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_RESET);
		cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
		if (cnt_val > 7000 && cnt_val < 10000) {
			//checked 9ms high pulse
			__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
			while (!HAL_GPIO_ReadPin(GPIOB, IR_in))
				;  //wait for 4.5ms
			cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
			HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_SET);

			if (cnt_val > 4000 && cnt_val < 6000) {
				for (int i = 0; i < 32; i++) {
					while ((HAL_GPIO_ReadPin(GPIOB, IR_in)))
						; // wait for pin to go low..
					__HAL_TIM_SET_COUNTER(&htimer, 0); // set the counter value a 0
					HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer,
							GPIO_PIN_RESET);
					while (!(HAL_GPIO_ReadPin(GPIOB, IR_in)))
						;  //wait for pin to go high this is 562.5us high
					HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer,
							GPIO_PIN_SET);
					cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
					if (cnt_val > 1550 && cnt_val < 1700) {
						// Logical '1' – a 562.5µs pulse burst followed by a 1.6875ms space, with a total transmit time of 2.25ms
						code |= (1UL << (31 - i));   // write 1
					} else if (cnt_val > 500 && cnt_val < 600) {
						//Logical '0' – a 562.5µs pulse burst followed by a 562.5µs space, with a total transmit time of 1.125m
						code &= ~(1UL << (31 - i));
					} else
						return 0;  // unknown signal

				}
				while (!HAL_GPIO_ReadPin(GPIOB, IR_in))
					;
				__HAL_TIM_SET_COUNTER(&htimer, 0);  // set the counter value a 0
				HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_SET);
				while (HAL_GPIO_ReadPin(GPIOB, IR_in))
					;  //end of message
				cnt_val = (uint16_t) __HAL_TIM_GET_COUNTER(&htimer);
				HAL_GPIO_WritePin(GPIOB, IR_in_detect_analyer, GPIO_PIN_RESET);
				if (cnt_val > 550 && cnt_val < 650) // end conversion
					return code;
			}
		}
	}
	return code;
}
