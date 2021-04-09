#ifndef UART_H
#define UART_H
#include "main.h"
#include <string.h>
#include <stdio.h>
char uartBuffer[50];
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
void SendUnsignedNumber(uint32_t number,UART_HandleTypeDef _huart);
void SendConstChar(const char* constChar,UART_HandleTypeDef _huart);
void SendFloat(float num,UART_HandleTypeDef _huart);
void SendFloatLn(float num,UART_HandleTypeDef _huart);
#endif
