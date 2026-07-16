#include "ds18b20.h"

/* Lenh ROM va Function chuan cua DS18B20 (xem datasheet Maxim/Dallas) */
#define DS18B20_CMD_SKIP_ROM        0xCC
#define DS18B20_CMD_CONVERT_T       0x44
#define DS18B20_CMD_READ_SCRATCHPAD 0xBE

/* Da thuc CRC8 chuan Dallas/Maxim: x^8 + x^5 + x^4 + 1 */
static uint8_t crc8_dallas(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;

    for (uint8_t i = 0; i < len; i++) {
        uint8_t inbyte = data[i];
        for (uint8_t b = 0; b < 8; b++) {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) {
                crc ^= 0x8C;
            }
            inbyte >>= 1;
        }
    }
    return crc;
}

uint8_t DS18B20_Init(DS18B20_t *dev, GPIO_TypeDef *port, uint16_t pin)
{
    BSP_OneWire_Init(&dev->bus, port, pin);
    return BSP_OneWire_Reset(&dev->bus); /* 1 = phat hien thiet bi tren bus */
}

uint8_t DS18B20_StartConversion(DS18B20_t *dev)
{
    if (!BSP_OneWire_Reset(&dev->bus)) {
        return 0; /* Khong co thiet bi phan hoi */
    }

    BSP_OneWire_WriteByte(&dev->bus, DS18B20_CMD_SKIP_ROM);
    BSP_OneWire_WriteByte(&dev->bus, DS18B20_CMD_CONVERT_T);

    return 1;
    /* Sau khi goi ham nay: doi >=750ms (che do 12-bit mac dinh)
     * roi moi goi DS18B20_ReadTemperature() */
}

uint8_t DS18B20_ReadTemperature(DS18B20_t *dev, float *temperature)
{
    uint8_t scratchpad[9];

    if (!BSP_OneWire_Reset(&dev->bus)) {
        return 0;
    }

    BSP_OneWire_WriteByte(&dev->bus, DS18B20_CMD_SKIP_ROM);
    BSP_OneWire_WriteByte(&dev->bus, DS18B20_CMD_READ_SCRATCHPAD);

    for (uint8_t i = 0; i < 9; i++) {
        scratchpad[i] = BSP_OneWire_ReadByte(&dev->bus);
    }

    /* Kiem tra CRC8 tren 8 byte dau, so voi byte thu 9 (CRC nhan duoc) */
    if (crc8_dallas(scratchpad, 8) != scratchpad[8]) {
        return 0; /* Du lieu loi - nhieu tren bus hoac tiep xuc kem */
    }

    int16_t raw = (int16_t)((scratchpad[1] << 8) | scratchpad[0]);
    *temperature = (float)raw * 0.0625f; /* Do phan giai 12-bit: 1 LSB = 0.0625 C */

    return 1;
}
