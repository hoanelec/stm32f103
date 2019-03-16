#include "stm32f1xx_hal.h"
#include "dwt_stm32_delay.h"
#define  RS GPIO_PIN_0
#define  EN GPIO_PIN_1
#define  D4 GPIO_PIN_2
#define  D5 GPIO_PIN_3
#define  D6 GPIO_PIN_4
#define  D7 GPIO_PIN_5
#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#include <stdint.h>
//LCD Functions Developed by electroSome
//HAL_GPIO_WritePin(GPIOA,D4_Pin,1);
extern uint32_t SystemCoreClock;
 
void DWT_Init(void) 
{
  if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) 
  {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }
}
 
uint32_t DWT_Get(void)
{
  return DWT->CYCCNT;
}
 
__inline
uint8_t DWT_Compare(int32_t tp)
{
  return (((int32_t)DWT_Get() - tp) < 0);
}
 
void DWT_Delay(uint32_t us) // microseconds
{
  int32_t tp = DWT_Get() + us * (SystemCoreClock/1000000);
  while (DWT_Compare(tp));
}
void Lcd_Port(char a)
{
	if(a & 1)
		HAL_GPIO_WritePin(GPIOA,D4,1);
	else
		HAL_GPIO_WritePin(GPIOA,D4,0);

	if(a & 2)
		HAL_GPIO_WritePin(GPIOA,D5,1);
	else
		HAL_GPIO_WritePin(GPIOA,D5,0);

	if(a & 4)
		HAL_GPIO_WritePin(GPIOA,D6,1);
	else
		HAL_GPIO_WritePin(GPIOA,D6,0);

	if(a & 8)
		HAL_GPIO_WritePin(GPIOA,D7,1);
	else
		HAL_GPIO_WritePin(GPIOA,D7,0);
}
void Lcd_Cmd(char a)
{
	HAL_GPIO_WritePin(GPIOA,RS,0);             // => RS = 0
	Lcd_Port(a);
	HAL_GPIO_WritePin(GPIOA,EN,1);             // => E = 1
  HAL_Delay(4);
  HAL_GPIO_WritePin(GPIOA,EN,0);             // => E = 0
}

void Lcd_Clear()
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}

void Lcd_Init()
{
  Lcd_Port(0x00);
   HAL_Delay(20);
  Lcd_Cmd(0x03);
	HAL_Delay(5);
  Lcd_Cmd(0x03);
	HAL_Delay(11);
  Lcd_Cmd(0x03);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}
void Lcd_Write_Char(char a)
{
	//DWT_Init();
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
  HAL_GPIO_WritePin(GPIOA,RS,1);             // => RS = 1
   Lcd_Port(y>>4);             //Data transfer
   HAL_GPIO_WritePin(GPIOA,EN,1);
   HAL_Delay(1);
   HAL_GPIO_WritePin(GPIOA,EN,0);
   Lcd_Port(temp);
   HAL_GPIO_WritePin(GPIOA,EN,1);
   HAL_Delay(1);
   HAL_GPIO_WritePin(GPIOA,EN,0);
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x08);
}