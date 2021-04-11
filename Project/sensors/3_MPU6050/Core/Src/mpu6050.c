	#include "mpu6050.h"
#include "I2C.h"
I2C_HandleTypeDef hi2cx;
void initI2C(I2C_HandleTypeDef _hi2c)
{
	hi2cx = _hi2c;
}
void setClockSource(uint8_t sourse)
{
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, sourse, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, 200, hi2cx);
}
void setSeepEnable(uint8_t permit)
{
	i2cWriteBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, permit, MPU6050_PWR1_SLEEP_BIT, 200, hi2cx);
}
void setFullScaleGyroRange(uint8_t range)
{
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_GYR_CONF, range, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, 200, hi2cx);
}
void setFullScaleAccelRange(uint8_t range)
{
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_ACC_CONF, range, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, 200, hi2cx);
}
uint8_t deviceIsAvailable()
{
	uint8_t dByte = i2cReadByte(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, 1000, hi2cx);
//	HAL_I2C_Mem_Write(&hi2cx, MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I,MPU6050_RA_WHO_AM_I_SIZE , &dByte, 1, 1000);
	if(dByte == MPU6050_ADDRESS)
		return 1;
	else return 0;
}
void initialize()
{
	setClockSource(MPU6050_CLOCK_PLL_XGYRO);
	setSeepEnable(0);
	setFullScaleGyroRange(MPU6050_GYRO_FS_SEL_250);
	setFullScaleAccelRange(MPU6050_ACCL_AFS_SEL_2G);
}
void getMotion6(int16_t *ax, int16_t *ay, int16_t *az,int16_t *gx, int16_t *gy,int16_t *gz)
{
	i2cReadBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H,14 , i2cBuffer, 2000, hi2cx);
    *ax = (int16_t)(i2cBuffer[0] << 8 )| i2cBuffer[1];
	*ay = (int16_t)(i2cBuffer[2]<<8 )| i2cBuffer[3];
	*az = (int16_t)(i2cBuffer[4]<<8 )| i2cBuffer[5];
	//i2cBuffer[6] i2cBuffer[7] temperature
	*gx = (int16_t)(i2cBuffer[8]<<8 )| i2cBuffer[9];
	*gy = (int16_t)(i2cBuffer[10]<<8 )| i2cBuffer[11];
	*gz = (int16_t)(i2cBuffer[12]<<8 )| i2cBuffer[13];

}
