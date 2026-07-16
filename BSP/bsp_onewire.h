#ifndef BSP_ONEWIRE_H
#define BSP_ONEWIRE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/*
 * BSP_OneWire - generic 1-Wire bus driver (bit-bang)
 * Vai trò trong kien truc: ECU Abstraction / protocol wrapper layer.
 * Khong biet gi ve DS18B20 hay bat ky thiet bi cu the nao - chi bit-bang
 * dung timing chuan 1-Wire. Thiet bi cu the (DS18B20...) nam o tang
 * DeviceDrivers (CDD), goi xuong day.
 *
 * YEU CAU PHAN CUNG:
 *  - Dien tro pull-up ngoai 4.7k tu chan DATA len VCC (bat buoc theo chuan 1-Wire)
 *  - Chan GPIO duoc cau hinh 1 lan duy nhat o che do Output Open-Drain,
 *    khong can doi mode qua lai Input/Output khi doc/ghi.
 */

typedef struct {
    GPIO_TypeDef *port;
    uint16_t      pin;
} BSP_OneWire_t;

/* Khoi tao bus: cau hinh GPIO Output Open-Drain, khoi tao DWT cycle counter
 * (goi 1 lan duy nhat cho toan he thong, an toan khi goi nhieu lan) */
void    BSP_OneWire_Init(BSP_OneWire_t *ow, GPIO_TypeDef *port, uint16_t pin);

/* Reset bus + doc xung presence. Tra ve 1 neu co thiet bi phan hoi, 0 neu khong */
uint8_t BSP_OneWire_Reset(BSP_OneWire_t *ow);

void    BSP_OneWire_WriteBit(BSP_OneWire_t *ow, uint8_t bit);
uint8_t BSP_OneWire_ReadBit(BSP_OneWire_t *ow);

void    BSP_OneWire_WriteByte(BSP_OneWire_t *ow, uint8_t byte);
uint8_t BSP_OneWire_ReadByte(BSP_OneWire_t *ow);

#ifdef __cplusplus
}
#endif

#endif /* BSP_ONEWIRE_H */
