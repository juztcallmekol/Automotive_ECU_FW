#include "app.h"
#include "debug.h"
#include "mpu6050.h"
#include "main.h"
#include <stdio.h>
#include "i2c.h"
void App_Init(void)
{
    LOG_INFO("==================================");
    LOG_INFO("Automotive ECU Boot");
    LOG_INFO("System Init");
    LOG_INFO("UART Initialized");
    LOG_INFO("==================================");


    if (HAL_I2C_IsDeviceReady(&hi2c1, MPU6050_I2C_ADDR, 3, 100) == HAL_OK)
    {
        LOG_INFO("MPU6050 Found");
    }
    else
    {
        LOG_ERROR("MPU6050 Not Found");
    }

    uint8_t id = 0;
    char str[32];

    if (MPU6050_ReadWhoAmI(&id) == MPU6050_OK)
    {
        sprintf(str, "WHO_AM_I = 0x%02X", id);
        LOG_INFO(str);
    }
    else
    {
        LOG_ERROR("WHO_AM_I Read Error");
    }


    if (MPU6050_Init() == MPU6050_OK)
    {
        LOG_INFO("MPU6050 Init OK");
    }
    else
    {
        LOG_ERROR("MPU6050 Init Fail");
    }
}

void App_Run(void)
{

	static MPU6050_ScaledData_t imu;

	if(MPU6050_ReadAllScaled(&imu) == MPU6050_OK)
	{
	    char str[128];

	    sprintf(str,
	    		"AX=%.2fg AY=%.2fg AZ=%.2fg "
	    		        "GX=%.2fdps GY=%.2fdps GZ=%.2fdps",
	            imu.AccelX_g,
	            imu.AccelY_g,
	            imu.AccelZ_g,
	            imu.GyroX_dps,
	            imu.GyroY_dps,
	            imu.GyroZ_dps);

	    LOG_INFO(str);

	    HAL_Delay(500);
	}
	else
	{
		LOG_ERROR("Read IMU Fail");
	}
	HAL_Delay(200);

}
