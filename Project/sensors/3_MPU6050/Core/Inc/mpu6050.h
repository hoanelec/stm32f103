#ifndef MPU6050_H
#define MPU6050_H
#include "main.h"
#define MPU6050_ADDRESS	0x68

#define MPU6050_CLOCK_INTERNAL          0x00
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_CLOCK_PLL_YGYRO         0x02
#define MPU6050_CLOCK_PLL_ZGYRO         0x03
#define MPU6050_CLOCK_PLL_EXT32K        0x04
#define MPU6050_CLOCK_PLL_EXT19M        0x05
#define MPU6050_CLOCK_KEEP_RESET        0x07

#define MPU6050_GYRO_FS_SEL_250			0x00
#define MPU6050_GYRO_FS_SEL_500			0x01
#define MPU6050_GYRO_FS_SEL_1000		0x10
#define MPU6050_GYRO_FS_SEL_2000		0x11

#define MPU6050_ACCL_AFS_SEL_2G			0x00
#define MPU6050_ACCL_AFS_SEL_4G			0x01
#define MPU6050_ACCL_AFS_SEL_8G			0x10
#define MPU6050_ACCL_AFS_SEL_16G		0x11

#define MPU6050_RA_GYR_CONF			0x1B
#define MPU6050_RA_ACC_CONF			0x1C

#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C


#define MPU6050_PWR1_DEVICE_RESET_BIT   7
#define MPU6050_PWR1_SLEEP_BIT          6
#define MPU6050_PWR1_CYCLE_BIT          5
#define MPU6050_PWR1_TEMP_DIS_BIT       3
#define MPU6050_PWR1_CLKSEL_BIT         2
#define MPU6050_PWR1_CLKSEL_LENGTH      3

#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2

#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40

#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48

#define MPU6050_RA_WHO_AM_I	0x75
#define MPU6050_RA_WHO_AM_I_SIZE 1


void initI2C(I2C_HandleTypeDef _hi2c);
void setClockSource(uint8_t sourse);
void setSeepEnable(uint8_t permit);
void setFullScaleGyroRange(uint8_t range);
void setFullScaleAccelRange(uint8_t range);
uint8_t deviceIsAvailable();
void initialize();
void getMotion6(int16_t *ax, int16_t *ay, int16_t *az,int16_t *gx, int16_t *gy,int16_t *gz);
#endif
