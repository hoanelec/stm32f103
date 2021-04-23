#include "Uart.h"
void SendUnsignedNumber(uint32_t number,UART_HandleTypeDef _huart)
{
	memset(uartBuffer,0,50);
	uint8_t l = sprintf(uartBuffer,"%lu",number);
	HAL_UART_Transmit(&_huart, (uint8_t *)uartBuffer, l, 500);
}
void SendUnsignedNumberLn(uint32_t number,UART_HandleTypeDef _huart)
{
	memset(uartBuffer,0,50);
	uint8_t l = sprintf(uartBuffer,"%lu",number);
	HAL_UART_Transmit(&_huart, (uint8_t *)uartBuffer, l, 500);
	HAL_UART_Transmit(&_huart, (uint8_t *)"\n", 2, 50);

}
void SendConstChar(const char* constChar,UART_HandleTypeDef _huart)
{
	memset(uartBuffer,0,50);
	HAL_UART_Transmit(&_huart,(uint8_t *)constChar,strlen((const char*)constChar),200);
}
void SendConstCharLn(const char* constChar,UART_HandleTypeDef _huart)
{
	memset(uartBuffer,0,50);
	HAL_UART_Transmit(&_huart,(uint8_t *)constChar,strlen((const char*)constChar),200);
		HAL_UART_Transmit(&_huart, (uint8_t *)"\n", 2, 50);
}
void SendFloat(float num,UART_HandleTypeDef _huart)
{
	memset(uartBuffer,0,50);
	uint16_t intPart = (uint16_t)num;
	float  decPart  = (float )num - intPart;
	uint16_t decPart2 = (decPart*100)/10;
	sprintf(uartBuffer,"%d.%d",intPart,decPart2);
	HAL_UART_Transmit(&_huart, (uint8_t *)uartBuffer, sprintf(uartBuffer,"%d.%d",intPart,decPart2), 400);
}
void SendFloatLn(float num,UART_HandleTypeDef _huart)
{
	memset(uartBuffer,0,50);
	SendFloat(num,_huart);
	HAL_UART_Transmit(&_huart, (uint8_t *)"\n", 2, 50);
}
