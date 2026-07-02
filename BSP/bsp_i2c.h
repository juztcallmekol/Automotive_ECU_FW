#ifndef BSP_I2C_H
#define BSP_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* Exported Functions ----------------------------------------------*/

HAL_StatusTypeDef BSP_I2C_Write(
        uint16_t DevAddr,
        uint8_t RegAddr,
        const uint8_t *data,
        uint16_t len);

HAL_StatusTypeDef BSP_I2C_Read(
        uint16_t DevAddr,
        uint8_t RegAddr,
        uint8_t *data,
        uint16_t len);

#ifdef __cplusplus
}
#endif

#endif
