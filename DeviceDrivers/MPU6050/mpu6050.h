#ifndef MPU6050_H
#define MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* MPU6050 I2C Address */
#define MPU6050_ADDR           (0x68 << 1)

/* Registers */
#define MPU6050_SMPLRT_DIV     0x19
#define MPU6050_CONFIG         0x1A
#define MPU6050_GYRO_CONFIG    0x1B
#define MPU6050_ACCEL_CONFIG   0x1C

#define MPU6050_ACCEL_XOUT_H   0x3B
#define MPU6050_TEMP_OUT_H     0x41
#define MPU6050_GYRO_XOUT_H    0x43

#define MPU6050_PWR_MGMT_1     0x6B
#define MPU6050_WHO_AM_I       0x75

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

bool MPU6050_Init(void);

bool MPU6050_ReadAccel(MPU6050_Data_t *data);

bool MPU6050_ReadGyro(MPU6050_Data_t *data);

bool MPU6050_ReadAll(MPU6050_Data_t *data);

#ifdef __cplusplus
}
#endif

#endif
