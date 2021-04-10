#include "I2C.h"
#include "math.h"
void i2cReadBytes(uint8_t devAddr,uint8_t regAddr,uint16_t bytes,uint8_t *buffer,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	HAL_I2C_Mem_Read(&hi2c, devAddr<<1, regAddr, 1, buffer, bytes, 1000);
}
uint8_t i2cReadByte(uint8_t devAddr,uint8_t regAddr,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	uint8_t dByte;
	HAL_I2C_Mem_Read(&hi2c, devAddr<<1, regAddr, 1, &dByte, 1, timeout);
	return dByte;
}
void i2cWriteByte(uint8_t devAddr,uint8_t regAddr,uint8_t data,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	HAL_I2C_Mem_Write(&hi2c, devAddr<<1|1, regAddr, 1, &data, 1, timeout);
}
void i2cWriteBits(uint8_t devAddr,uint8_t regAddr,uint8_t data,uint8_t bitStart,uint8_t length,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	uint8_t dByte =  i2cReadByte(devAddr<<1, regAddr, timeout, hi2c);
	uint8_t bMask = ((1<<length)-1)<<(bitStart+1-length);// or bMask = (0xff>>(7-bitStart+bitStart-length+1)<<(bitStart-length+1)) &&0xff
	data <<=(bitStart-length +1);
	dByte &= bMask;
	dByte |= data;
	i2cWriteByte(devAddr, regAddr, dByte, timeout, hi2c);
}
void i2cWriteBit(uint8_t devAddr,uint8_t regAdd,uint8_t data,uint8_t bitIndex ,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	uint8_t dByte = i2cReadByte(devAddr, regAdd, timeout, hi2c);
	uint8_t bMask = ~(1<<bitIndex);
	data <<= bitIndex;
	dByte &= bMask;
	dByte |= data;
}
/*
uint8_t i2cReadWord(uint8_t devAddr,uint8_t regAddr,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
 uint8_t dByte;
 uint16_t dWord;
 dByte = i2cReadByte( devAddr, regAddr, timeout, hi2c);
 dWord = dByte<<8;
 dByte= i2cReadByte( devAddr, regAddr, &dByte, timeout, hi2c);
 dWord |=dByte;
 return dWord;
}*/

uint8_t i2cReadBit(uint8_t devAddr,uint8_t regAddr,uint8_t bitNum,uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	uint8_t dByte = i2cReadByte( devAddr, regAddr, timeout, hi2c);
	return  dByte&(1<<bitNum);
}
uint8_t i2cReadBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	uint8_t dByte = i2cReadByte( devAddr, regAddr, timeout, hi2c);
	uint8_t bMask = ((1<<length)-1)<<(bitStart+1-length);
	return (dByte&bMask)>>(bitStart+1-length);
}
/*
uint8_t i2cReadBitw(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t timeout,I2C_HandleTypeDef hi2c)
{
	uint16_t dt;
	uint16_t dWord = i2cReadWord( devAddr, regAddr, &dt, timeout, hi2c);
	*data = dt&(1<<bitNum);
	return dWord;
}*/
