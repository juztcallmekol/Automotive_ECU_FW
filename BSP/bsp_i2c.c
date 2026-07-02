#include "bsp_i2c.h"
#include "i2c.h"

#define I2C_TIMEOUT_MS    100U

HAL_StatusTypeDef BSP_I2C_Write(
        uint16_t DevAddr,
        uint8_t RegAddr,
        const uint8_t *data,
        uint16_t len)
{
    return HAL_I2C_Mem_Write(
            &hi2c1,
            DevAddr,
            RegAddr,
            I2C_MEMADD_SIZE_8BIT,
            (uint8_t *)data,
            len,
            I2C_TIMEOUT_MS);
}

HAL_StatusTypeDef BSP_I2C_Read(
        uint16_t DevAddr,
        uint8_t RegAddr,
        uint8_t *data,
        uint16_t len)
{
    return HAL_I2C_Mem_Read(
            &hi2c1,
            DevAddr,
            RegAddr,
            I2C_MEMADD_SIZE_8BIT,
            data,
            len,
            I2C_TIMEOUT_MS);
}
