#include "mpu6050.h"
#include "I2C.h"
I2C_HandleTypeDef hi2cx;
extern UART_HandleTypeDef huart1;
void initI2C(I2C_HandleTypeDef _hi2c) {
	hi2cx = _hi2c;
}
void setClockSource(uint8_t sourse) {
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, sourse,MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, 200, hi2cx);
}
<<<<<<< HEAD
void setSampleRate(uint8_t _smprtDiv)
=======
void setSleepEnable(uint8_t permit)
>>>>>>> 8121561a1ff12e5ce55577bf8bd42b5600f67899
{
	i2cWriteByte(MPU6050_ADDRESS, MPU6050_RA_SMPRT_DIV, _smprtDiv, 200, hi2cx);
}
void setSleepEnable(uint8_t permit) {
	i2cWriteBit(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, permit,MPU6050_PWR1_SLEEP_BIT, 200, hi2cx);
}
void setFullScaleGyroRange(uint8_t range) {
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_GYR_CONF, range,MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, 200, hi2cx);
}
uint8_t getScaleGyroRange() {
	return i2cReadBits(MPU6050_ADDRESS, MPU6050_RA_GYR_CONF,MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, 200, hi2cx);
}
void setFullScaleAccelRange(uint8_t range) {
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_ACC_CONF, range,MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, 200, hi2cx);
}
uint8_t getScaleAccelRange() {
	return i2cReadBits(MPU6050_ADDRESS, MPU6050_RA_ACC_CONF,MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, 200, hi2cx);
}
<<<<<<< HEAD
uint8_t getRegGYRO_CONFIG() {
	return i2cReadByte(MPU6050_ADDRESS, MPU6050_RA_GYR_CONF, 200, hi2cx);
}
uint8_t getRegACCEL_CONFIG() {
	return i2cReadByte(MPU6050_ADDRESS, MPU6050_RA_ACC_CONF, 200, hi2cx);
}
/**\brief	 : Temperature measurements are written to these registers at the Sample Rate as defined in Register 25
  *  TEMP_OUT_H[15:8] and TEMP_OUT_L[7:0]
  *  return Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
  * */
float getTemperature()
{
	i2cReadBytes(MPU6050_ADDRESS,MPU6050_RA_TEMP_OUT_H , 2, i2cBuffer, 1000, hi2cx);
	return ((int16_t)(i2cBuffer[0]<<8)|i2cBuffer[1])/340+36.53;
}
uint8_t deviceIsAvailable() {
	uint8_t dByte = i2cReadByte(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, 1000,
			hi2cx);
	if (dByte == MPU6050_ADDRESS)
=======
/**\brief
  *  SMPRT_DIV[7:0]
  *  Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
  * We will going to set the accelerometer output rate 1KHz
  *
  *
  */
void setSampleRate(void)
{
	i2cWriteBits(MPU6050_ADDRESS, MPU6050_RA_SMPRT_DIV, 0x07, MPU6050_RA_SMPRT_DIV_BIT, MPU6050_RA_SMPRT_DIV_LENGHT, 200, hi2cx);
}
uint8_t deviceIsAvailable()
{
	uint8_t dByte = i2cReadByte(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, 1000, hi2cx);
	//	HAL_I2C_Mem_Write(&hi2cx, MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I,MPU6050_RA_WHO_AM_I_SIZE , &dByte, 1, 1000);
	if(dByte == MPU6050_ADDRESS)
>>>>>>> 8121561a1ff12e5ce55577bf8bd42b5600f67899
		return 1;
	else
		return 0;
}

void initialize() {
	setClockSource(MPU6050_CLOCK_PLL_XGYRO);
	setSleepEnable(0);
<<<<<<< HEAD
	setSampleRate(0x07);
=======
	//	HAL_I2C_Mem_Write(&hi2cx, MPU6050_ADDRESS, 0x19, 1, 0x07, 1, 1000);
>>>>>>> 8121561a1ff12e5ce55577bf8bd42b5600f67899
	setFullScaleGyroRange(MPU6050_GYRO_FS_SEL_250);
	setSampleRate();
	setFullScaleAccelRange(MPU6050_ACCL_AFS_SEL_2G);
}
<<<<<<< HEAD
void getMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy,
		int16_t *gz) {
	i2cReadBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, 6, i2cBuffer, 1000,hi2cx);
	*ax = (int16_t) (i2cBuffer[0] << 8) | i2cBuffer[1];
	*ay = (int16_t) (i2cBuffer[2] << 8) | i2cBuffer[3];
	*az = (int16_t) (i2cBuffer[4] << 8) | i2cBuffer[5];
	i2cReadBytes(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, 6, i2cBuffer, 1000,hi2cx);
	*gx = (int16_t) (i2cBuffer[0] << 8) | i2cBuffer[1];
	*gy = (int16_t) (i2cBuffer[2] << 8) | i2cBuffer[3];
	*gz = (int16_t) (i2cBuffer[4] << 8) | i2cBuffer[5];
=======
void getMotion6(int16_t *ax, int16_t *ay, int16_t *az,int16_t *gx, int16_t *gy,int16_t *gz)
{
	i2cReadBytes(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H,6 , i2cBuffer, 2000, hi2cx);
	*ax = (int16_t)(i2cBuffer[0] << 8 )| i2cBuffer[1];
	*ay = (int16_t)(i2cBuffer[2]<<8 )| i2cBuffer[3];
	*az = (int16_t)(i2cBuffer[4]<<8 )| i2cBuffer[5];
	i2cReadBytes(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H,6 , i2cBuffer, 2000, hi2cx);
	*gx = (int16_t)(i2cBuffer[0] << 8 )| i2cBuffer[1];
	*gy = (int16_t)(i2cBuffer[2]<<8 )| i2cBuffer[3];
	*gz = (int16_t)(i2cBuffer[4]<<8 )| i2cBuffer[5];

>>>>>>> 8121561a1ff12e5ce55577bf8bd42b5600f67899
}

