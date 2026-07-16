#ifndef DS18B20_H
#define DS18B20_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_onewire.h"

/*
 * DS18B20 - Complex Device Driver (CDD)
 * Bien lenh cu the cua DS18B20 thanh API don gian cho tang tren
 * (RTE / Application). Khong truy cap GPIO truc tiep - luon di qua BSP_OneWire.
 *
 * LUU Y: gia su chi co 1 thiet bi DS18B20 tren bus (dung lenh Skip ROM 0xCC).
 * Neu can nhieu cam bien tren cung 1 bus, phai bo sung doc dia chi ROM
 * (Search ROM) - ngoai pham vi ban toi gian nay.
 */

typedef struct {
    BSP_OneWire_t bus;
} DS18B20_t;

/* Khoi tao + kiem tra co thiet bi tren bus khong.
 * Tra ve 1 neu tim thay thiet bi, 0 neu khong (kiem tra day/dien tro pull-up) */
uint8_t DS18B20_Init(DS18B20_t *dev, GPIO_TypeDef *port, uint16_t pin);

/* Bat dau chuyen doi nhiet do. Sau khi goi ham nay, PHAI doi toi thieu 750ms
 * (do phan giai mac dinh 12-bit) truoc khi goi DS18B20_ReadTemperature() */
uint8_t DS18B20_StartConversion(DS18B20_t *dev);

/* Doc ket qua nhiet do da chuyen doi xong (don vi do C).
 * Tra ve 1 neu doc thanh cong (CRC hop le), 0 neu loi */
uint8_t DS18B20_ReadTemperature(DS18B20_t *dev, float *temperature);

#ifdef __cplusplus
}
#endif

#endif /* DS18B20_H */
