#ifndef MPU6050_H
#define MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* I2C Address */
#define MPU6050_I2C_ADDR      (0x68U << 1)

/* Registers */
#define MPU6050_SMPLRT_DIV        0x19
#define MPU6050_CONFIG            0x1A
#define MPU6050_GYRO_CONFIG       0x1B
#define MPU6050_ACCEL_CONFIG      0x1C

#define MPU6050_ACCEL_XOUT_H      0x3B
#define MPU6050_TEMP_OUT_H        0x41
#define MPU6050_GYRO_XOUT_H       0x43

#define MPU6050_PWR_MGMT_1        0x6B
#define MPU6050_WHO_AM_I          0x75

typedef enum
{
    MPU6050_OK = 0,
    MPU6050_ERROR_I2C,
    MPU6050_ERROR_TIMEOUT,
    MPU6050_ERROR_WHOAMI,
    MPU6050_ERROR_CONFIG
} MPU6050_Status_t;

typedef struct
{
    int16_t AccelX;
    int16_t AccelY;
    int16_t AccelZ;

    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;

    float Temperature;

} MPU6050_Data_t;

typedef struct
{
    float AccelX_g;
    float AccelY_g;
    float AccelZ_g;

    float GyroX_dps;
    float GyroY_dps;
    float GyroZ_dps;

    float Temperature_C;

} MPU6050_ScaledData_t;

/* Driver APIs */

MPU6050_Status_t MPU6050_Init(void);

MPU6050_Status_t MPU6050_SelfTest(void);

MPU6050_Status_t MPU6050_Calibrate(void);

MPU6050_Status_t MPU6050_ReadAccel(MPU6050_Data_t *data);

MPU6050_Status_t MPU6050_ReadGyro(MPU6050_Data_t *data);

MPU6050_Status_t MPU6050_ReadTemperature(MPU6050_Data_t *data);

MPU6050_Status_t MPU6050_ReadAll(MPU6050_Data_t *data);

MPU6050_Status_t MPU6050_ReadWhoAmI(uint8_t *id);

MPU6050_Status_t MPU6050_ReadAllScaled(
        MPU6050_ScaledData_t *data);

#ifdef __cplusplus
}
#endif

#endif
