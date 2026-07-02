#include "mpu6050.h"
#include "bsp_i2c.h"
#include "main.h"

#define MPU6050_ACCEL_SENS_2G      16384.0f
#define MPU6050_GYRO_SENS_250DPS   131.0f
#define MPU6050_CALIB_SAMPLES    1000U
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

/* Private Variables ---------------------------------------------------------*/

static MPU6050_Config_t gConfig =
{
    .AccelRange = MPU6050_ACCEL_2G,
    .GyroRange  = MPU6050_GYRO_250DPS,
    .SampleRate = 125
};

static MPU6050_Offset_t gOffset =
{
    .AccelX = 0.0f,
    .AccelY = 0.0f,
    .AccelZ = 0.0f,

    .GyroX  = 0.0f,
    .GyroY  = 0.0f,
    .GyroZ  = 0.0f
};


/* Public Functions ----------------------------------------------------------*/

MPU6050_Status_t MPU6050_Reset(void)
{
    MPU6050_Status_t status;

    status = MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x80);

    if(status != MPU6050_OK)
    {
        return status;
    }

    HAL_Delay(100);

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadWhoAmI(uint8_t *id)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I, id, 1);
}

MPU6050_Status_t MPU6050_Init(void)
{
    MPU6050_Status_t status;

    uint8_t id;

    status = MPU6050_Reset();

    if(status != MPU6050_OK)
    {
        return status;
    }

    status = MPU6050_ReadWhoAmI(&id);

    if(status != MPU6050_OK)
    {
        return status;
    }

    if(id != 0x70)
    {
        return MPU6050_ERROR_WHOAMI;
    }

    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x00);

    MPU6050_SetSampleRate(125);

    MPU6050_SetDLPF(6);

    MPU6050_SetAccelRange(MPU6050_ACCEL_2G);

    MPU6050_SetGyroRange(MPU6050_GYRO_250DPS);

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_SetAccelRange(MPU6050_AccelRange_t range)
{
    uint8_t reg = (uint8_t)range << 3;

    MPU6050_Status_t ret =
        MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, reg);

    if(ret == MPU6050_OK)
        gConfig.AccelRange = range;

    return ret;
}

MPU6050_Status_t MPU6050_SetGyroRange(MPU6050_GyroRange_t range)
{
    uint8_t reg = (uint8_t)range << 3;

    MPU6050_Status_t ret =
        MPU6050_WriteReg(MPU6050_GYRO_CONFIG, reg);

    if(ret == MPU6050_OK)
        gConfig.GyroRange = range;

    return ret;
}

MPU6050_Status_t MPU6050_SetDLPF(uint8_t dlpf)
{
    dlpf &= 0x07;

    return MPU6050_WriteReg(
            MPU6050_CONFIG,
            dlpf);
}

MPU6050_Status_t MPU6050_SetSampleRate(uint16_t sampleRate)
{
    if(sampleRate == 0)
        return MPU6050_ERROR_CONFIG;

    uint8_t div = 1000 / sampleRate - 1;

    return MPU6050_WriteReg(
            MPU6050_SMPLRT_DIV,
            div);
}

MPU6050_Status_t MPU6050_ReadAllScaled(
        MPU6050_ScaledData_t *data)
{
    MPU6050_RawData_t raw;

    MPU6050_Status_t ret =
            MPU6050_ReadRaw(&raw);

    if(ret != MPU6050_OK)
        return ret;

    data->AccelX_g =
            raw.AccelX / 16384.0f;

    data->AccelY_g =
            raw.AccelY / 16384.0f;

    data->AccelZ_g =
            raw.AccelZ / 16384.0f;

    data->GyroX_dps =
            raw.GyroX / 131.0f;

    data->GyroY_dps =
            raw.GyroY / 131.0f;

    data->GyroZ_dps =
            raw.GyroZ / 131.0f;

    data->Temperature_C =
            raw.Temperature / 340.0f + 36.53f;

    return MPU6050_OK;
}

MPU6050_Status_t MPU6050_ReadRaw(MPU6050_RawData_t *data)
{
    uint8_t buf[14];

    if (MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, buf, 14) != MPU6050_OK)
    {
        return MPU6050_ERROR_I2C;
    }

    data->AccelX = (int16_t)((buf[0] << 8) | buf[1]);
    data->AccelY = (int16_t)((buf[2] << 8) | buf[3]);
    data->AccelZ = (int16_t)((buf[4] << 8) | buf[5]);

    data->Temperature = (int16_t)((buf[6] << 8) | buf[7]);

    data->GyroX = (int16_t)((buf[8] << 8) | buf[9]);
    data->GyroY = (int16_t)((buf[10] << 8) | buf[11]);
    data->GyroZ = (int16_t)((buf[12] << 8) | buf[13]);

    return MPU6050_OK;
}

void MPU6050_GetOffset(MPU6050_Offset_t *offset)
{
    if (offset == NULL)
    {
        return;
    }

    *offset = gOffset;
}

void MPU6050_SetOffset(const MPU6050_Offset_t *offset)
{
    if (offset == NULL)
    {
        return;
    }

    gOffset = *offset;
}

MPU6050_Status_t MPU6050_Calibrate(void)
{
    MPU6050_RawData_t raw;

    int32_t ax = 0;
    int32_t ay = 0;
    int32_t az = 0;

    int32_t gx = 0;
    int32_t gy = 0;
    int32_t gz = 0;

    HAL_Delay(500);

    for(uint16_t i = 0; i < MPU6050_CALIB_SAMPLES; i++)
    {
        if(MPU6050_ReadRaw(&raw) != MPU6050_OK)
        {
            return MPU6050_ERROR_I2C;
        }

        ax += raw.AccelX;
        ay += raw.AccelY;
        az += raw.AccelZ;

        gx += raw.GyroX;
        gy += raw.GyroY;
        gz += raw.GyroZ;

        HAL_Delay(2);
    }

    gOffset.AccelX = (float)ax / MPU6050_CALIB_SAMPLES;
    gOffset.AccelY = (float)ay / MPU6050_CALIB_SAMPLES;
    gOffset.AccelZ = (float)az / MPU6050_CALIB_SAMPLES - 16384.0f;

    gOffset.GyroX = (float)gx / MPU6050_CALIB_SAMPLES;
    gOffset.GyroY = (float)gy / MPU6050_CALIB_SAMPLES;
    gOffset.GyroZ = (float)gz / MPU6050_CALIB_SAMPLES;

    return MPU6050_OK;
}


