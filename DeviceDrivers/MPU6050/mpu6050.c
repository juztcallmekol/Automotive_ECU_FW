#include "mpu6050.h"
#include "bsp_i2c.h"

static bool MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    return BSP_I2C_Write(MPU6050_ADDR,
                         reg,
                         &data,
                         1);
}

static bool MPU6050_ReadReg(uint8_t reg,
                            uint8_t *data,
                            uint16_t len)
{
    return BSP_I2C_Read(MPU6050_ADDR,
                        reg,
                        data,
                        len);
}

bool MPU6050_Init(void)
{
    uint8_t id;

    if(!MPU6050_ReadReg(MPU6050_WHO_AM_I, &id, 1))
        return false;

    if(id != 0x68)
        return false;

    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x00);

    HAL_Delay(100);

    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x07);

    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);

    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x00);

    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x00);

    return true;
}

bool MPU6050_ReadAccel(MPU6050_Data_t *data)
{
    uint8_t buf[6];

    if(!MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, buf, 6))
        return false;

    data->AccelX = (buf[0]<<8)|buf[1];
    data->AccelY = (buf[2]<<8)|buf[3];
    data->AccelZ = (buf[4]<<8)|buf[5];

    return true;
}

bool MPU6050_ReadGyro(MPU6050_Data_t *data)
{
    uint8_t buf[6];

    if(!MPU6050_ReadReg(MPU6050_GYRO_XOUT_H, buf, 6))
        return false;

    data->GyroX = (buf[0]<<8)|buf[1];
    data->GyroY = (buf[2]<<8)|buf[3];
    data->GyroZ = (buf[4]<<8)|buf[5];

    return true;
}

bool MPU6050_ReadAll(MPU6050_Data_t *data)
{
    uint8_t buf[14];

    if(!MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H, buf, 14))
        return false;

    data->AccelX = (buf[0]<<8)|buf[1];
    data->AccelY = (buf[2]<<8)|buf[3];
    data->AccelZ = (buf[4]<<8)|buf[5];

    int16_t temp = (buf[6]<<8)|buf[7];
    data->Temperature = temp / 340.0f + 36.53f;

    data->GyroX = (buf[8]<<8)|buf[9];
    data->GyroY = (buf[10]<<8)|buf[11];
    data->GyroZ = (buf[12]<<8)|buf[13];

    return true;
}
