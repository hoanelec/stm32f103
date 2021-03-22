#include "7seg8led.h"
uint16_t pinLedSelect[]={L1_Pin,L2_Pin,L3_Pin,L4_Pin,L5_Pin,L6_Pin,L7_Pin,L8_Pin};
uint16_t pinled7Seg[]={A_Pin,B_Pin,C_Pin,D_Pin,E_Pin,F_Pin,G_Pin,H_Pin};
uint8_t Cathode[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8_t CathodeWithDot[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};


void display7seg(uint8_t _led,uint8_t _number)
{
	HAL_GPIO_WritePin(GPIOB, pinLedSelect[_led], GPIO_PIN_SET);
	for(int i = 0; i< 8; i++)
	{
		uint8_t bit = (Cathode[_number]>>i)&0x01;
		HAL_GPIO_WritePin(GPIOA, pinled7Seg[i], (Cathode[_number]>>i)&0x01);
	}
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, pinLedSelect[_led], GPIO_PIN_RESET);

}
void display7segShiftRotateR()
{
	for(int i = 0 ; i < 8; i++)
	{
		for( int j = i;j<8;j++)
		{
			display7seg(j-i, j);
			HAL_Delay(10);
		}

		for(int k = i-1;k>=0;k--)
		{
			display7seg(8-k-1,i-k-1);
			HAL_Delay(10);
		}
	}
}
void display7segShiftR(uint8_t dig)
{
		for( int j = dig;j<8;j++)
		{
			display7seg(j-dig, j);
			HAL_Delay(10);
		}

		for(int k = dig-1;k>=0;k--)
		{
			display7seg(8-k-1,dig-k-1);
			HAL_Delay(10);
		}
}
