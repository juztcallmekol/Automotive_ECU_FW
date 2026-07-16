#include "rte_signal_if.h"
#include "ds18b20.h"      /* Chi file nay trong toan bo project duoc phep include ds18b20.h */
#include "board.h"

/* Bien noi bo - Application khong bao gio thay duoc kieu DS18B20_t */
static DS18B20_t s_engine_temp_sensor;
static uint8_t   s_sensor_ok = 0;

void RTE_Init(void)
{
    s_sensor_ok = DS18B20_Init(&s_engine_temp_sensor,
                                BOARD_DS18B20_PORT,
                                BOARD_DS18B20_PIN);

    /* TODO: khoi tao cac RTE signal khac o day (get_distance, get_speed...) */
}

void RTE_StartTempConversion(void)
{
    if (!s_sensor_ok) {
        return;
    }
    DS18B20_StartConversion(&s_engine_temp_sensor);
}

float RTE_ReadTempResult(void)
{
    float temperature = -999.0f;

    if (!s_sensor_ok) {
        return temperature;
    }

    if (!DS18B20_ReadTemperature(&s_engine_temp_sensor, &temperature)) {
        return -999.0f;
    }

    return temperature;
}
