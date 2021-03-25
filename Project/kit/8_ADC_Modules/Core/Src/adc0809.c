#include "adc0809.h"
uint8_t Read_ADC_PIN(void)
{
  unsigned char dat;
  dat=0;

  if(HAL_GPIO_ReadPin(O7_GPIO_Port, GPIO_PIN_7)) dat|=0x80;
  if(HAL_GPIO_ReadPin(O6_GPIO_Port, GPIO_PIN_6)) dat|=0x40;
  if(HAL_GPIO_ReadPin(O5_GPIO_Port, GPIO_PIN_5)) dat|=0x20;
  if(HAL_GPIO_ReadPin(O4_GPIO_Port, GPIO_PIN_4)) dat|=0x10;
  if(HAL_GPIO_ReadPin(O3_GPIO_Port, GPIO_PIN_3)) dat|=0x08;
  if(HAL_GPIO_ReadPin(O2_GPIO_Port, GPIO_PIN_2)) dat|=0x04;
  if(HAL_GPIO_ReadPin(O1_GPIO_Port, GPIO_PIN_1)) dat|=0x02;
  if(HAL_GPIO_ReadPin(O0_GPIO_Port, GPIO_PIN_0)) dat|=0x01;

  return(dat);
}
uint8_t ADC0809_Read(uint8_t _channel)
{
	//select channel
	HAL_GPIO_WritePin(ADD_A_GPIO_Port, ADD_A_Pin, _channel&0x01);
	HAL_GPIO_WritePin(ADD_B_GPIO_Port, ADD_B_Pin, _channel&0x02);
	HAL_GPIO_WritePin(ADD_C_GPIO_Port, ADD_C_Pin, _channel&0x04);

	HAL_GPIO_WritePin(ALE_GPIO_Port, ALE_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(START_GPIO_Port, START_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(ALE_GPIO_Port, ALE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(START_GPIO_Port, START_Pin, GPIO_PIN_RESET);
	while(HAL_GPIO_ReadPin(EOC_GPIO_Port, EOC_Pin));
	while(!HAL_GPIO_ReadPin(EOC_GPIO_Port, EOC_Pin));
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
	uint8_t result = Read_ADC_PIN();
	HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);

	return result;

}
