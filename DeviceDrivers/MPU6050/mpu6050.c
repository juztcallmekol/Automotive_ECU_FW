#include "mpu6050.h"
#include "bsp_i2c.h"
#include "main.h"

#define MPU6050_ACCEL_SENS_2G      16384.0f
#define MPU6050_GYRO_SENS_250DPS   131.0f
/* Private Functions ---------------------------------------------------------*/

static MPU6050_Status_t MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    if (BSP_I2C_Write(MPU6050_I2C_ADDR,
                      reg,
                      &data,
                      1) == HAL_OK)
    {
        return MPU6050_OK;
    }

    return MPU6050_ERROR_I2C;
}

static MPU6050_Status_t MPU6050_ReadReg(uint8_t reg,
                                        uint8_t *data,
                                        uint16_t len)
{
    if (BSP_I2C_Read(MPU6050_I2C_ADDR,
                     reg,
                     data,
                     len) == HAL_OK)
    {
        return MPU6050_OK;
    }

    return MPU6050_ERROR_I2C;
}

/* Public Functions ----------------------------------------------------------*/

MPU6050_Status_t MPU6050_ReadWhoAmI(uint8_t *id)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I, id, 1);
}

MPU6050_Status_t MPU6050_Init(void)
{
    uint8_t id;

    if (MPU6050_ReadWhoAmI(&id) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    if(id != 0x68 && id != 0x70)
    {
        return MPU6050_ERROR_WHOAMI;
    }

    if (MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x00) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    HAL_Delay(100);

    if (MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x07) != MPU6050_OK)
    {
        return MPU6050_ERROR_CONFIG;
    }

    if (MPU6050_WriteReg(MPU6050_CONFIG, 0x06) != MPU6050_OK)
    {
        return MPU6050_ERROR_CONFIG;
    }

    if (MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x00) != MPU6050_OK)
    {
        return MPU6050_ERROR_CONFIG;
    }

    if (MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x00) != MPU6050_OK)
    {
        return MPU6050_ERROR_CONFIG;
    }

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadAccel(MPU6050_Data_t *data)
{
    uint8_t buf[6];

    if (MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, buf, 6) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    data->AccelX = (int16_t)((buf[0] << 8) | buf[1]);
    data->AccelY = (int16_t)((buf[2] << 8) | buf[3]);
    data->AccelZ = (int16_t)((buf[4] << 8) | buf[5]);

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadGyro(MPU6050_Data_t *data)
{
    uint8_t buf[6];

    if (MPU6050_ReadReg(MPU6050_GYRO_XOUT_H, buf, 6) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    data->GyroX = (int16_t)((buf[0] << 8) | buf[1]);
    data->GyroY = (int16_t)((buf[2] << 8) | buf[3]);
    data->GyroZ = (int16_t)((buf[4] << 8) | buf[5]);

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadTemperature(MPU6050_Data_t *data)
{
    uint8_t buf[2];
    int16_t raw;

    if (MPU6050_ReadReg(MPU6050_TEMP_OUT_H, buf, 2) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    raw = (int16_t)((buf[0] << 8) | buf[1]);

    data->Temperature = ((float)raw / 340.0f) + 36.53f;

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadAll(MPU6050_Data_t *data)
{
    uint8_t buf[14];
    int16_t rawTemp;

    if (MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, buf, 14) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    data->AccelX = (int16_t)((buf[0] << 8) | buf[1]);
    data->AccelY = (int16_t)((buf[2] << 8) | buf[3]);
    data->AccelZ = (int16_t)((buf[4] << 8) | buf[5]);

    rawTemp = (int16_t)((buf[6] << 8) | buf[7]);
    data->Temperature = ((float)rawTemp / 340.0f) + 36.53f;

    data->GyroX = (int16_t)((buf[8] << 8) | buf[9]);
    data->GyroY = (int16_t)((buf[10] << 8) | buf[11]);
    data->GyroZ = (int16_t)((buf[12] << 8) | buf[13]);

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadAllScaled(
        MPU6050_ScaledData_t *data)
{
    MPU6050_Data_t raw;

    MPU6050_Status_t status =
            MPU6050_ReadAll(&raw);

    if(status != MPU6050_OK)
    {
        return status;
    }

    data->AccelX_g = raw.AccelX / MPU6050_ACCEL_SENS_2G;
    data->AccelY_g = raw.AccelY / MPU6050_ACCEL_SENS_2G;
    data->AccelZ_g = raw.AccelZ / MPU6050_ACCEL_SENS_2G;

    data->GyroX_dps = raw.GyroX / MPU6050_GYRO_SENS_250DPS;
    data->GyroY_dps = raw.GyroY / MPU6050_GYRO_SENS_250DPS;
    data->GyroZ_dps = raw.GyroZ / MPU6050_GYRO_SENS_250DPS;

    data->Temperature_C = raw.Temperature;

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_SelfTest(void)
{
    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_Calibrate(void)
{
    return MPU6050_OK;
}

