#ifndef I2C_H
#define I2C_H
#include "main.h"

#define BUFFER_LENGTH 32
uint8_t i2cBuffer[BUFFER_LENGTH];
uint8_t i2cReadByte(uint8_t devAddr,uint8_t regAddr,uint16_t timeout,I2C_HandleTypeDef hi2c);
void i2cReadBytes(uint8_t devAddr,uint8_t regAddr,uint16_t bytes,uint8_t *buffer,uint16_t timeout,I2C_HandleTypeDef hi2c);
void i2cWriteByte(uint8_t devAddr,uint8_t regAddr,uint8_t data,uint16_t timeout,I2C_HandleTypeDef hi2c);
uint8_t i2cReadBit(uint8_t devAddr,uint8_t regAddr,uint8_t bitNum,uint16_t timeout,I2C_HandleTypeDef hi2c);
uint8_t i2cReadBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t timeout,I2C_HandleTypeDef hi2c);
void i2cWriteBits(uint8_t devAddr,uint8_t regAddr,uint8_t data,uint8_t bitStart,uint8_t length,uint16_t timeout,I2C_HandleTypeDef hi2c);
void i2cWriteBit(uint8_t devAddr,uint8_t regAdd,uint8_t data,uint8_t bitIndex ,uint16_t timeout,I2C_HandleTypeDef hi2c);
#endif
