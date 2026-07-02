#include "app.h"
#include "debug.h"
#include "mpu6050.h"
#include "main.h"
#include <stdio.h>
void App_Init(void)
{
    LOG_INFO("==================================");
    LOG_INFO("Automotive ECU Boot");
    LOG_INFO("System Init");
    LOG_INFO("UART Initialized");
    LOG_INFO("==================================");

    if (MPU6050_Init())
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

	static MPU6050_Data_t imu;

	if (MPU6050_ReadAll(&imu))
	{
	    char str[128];

	    sprintf(str,
	            "AX=%d AY=%d AZ=%d GX=%d GY=%d GZ=%d",
	            imu.AccelX,
	            imu.AccelY,
	            imu.AccelZ,
	            imu.GyroX,
	            imu.GyroY,
	            imu.GyroZ);

	    LOG_INFO(str);

	    HAL_Delay(500);
	}

}
