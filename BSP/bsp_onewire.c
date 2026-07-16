#include "bsp_onewire.h"

/* ------------------------------------------------------------------------
 * DWT cycle counter - tao delay micro giay chinh xac, khong chiem Timer.
 * Chi can khoi tao 1 lan cho toan he thong.
 * ------------------------------------------------------------------------ */
static uint8_t dwt_initialized = 0;

static void DWT_Delay_Init(void)
{
    if (dwt_initialized) {
        return;
    }
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL  |= DWT_CTRL_CYCCNTENA_Msk;
    dwt_initialized = 1;
}

static inline void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (SystemCoreClock / 1000000U);
    while ((DWT->CYCCNT - start) < ticks) {
        /* busy wait */
    }
}

/* ------------------------------------------------------------------------
 * Dieu khien muc dien ap tren chan - pin luon o Output Open-Drain,
 * "release" nghia la tha noi (keo len muc cao qua dien tro pull-up ngoai),
 * khong bao gio doi GPIO mode.
 * ------------------------------------------------------------------------ */
static inline void pin_low(BSP_OneWire_t *ow)
{
    HAL_GPIO_WritePin(ow->port, ow->pin, GPIO_PIN_RESET);
}

static inline void pin_release(BSP_OneWire_t *ow)
{
    HAL_GPIO_WritePin(ow->port, ow->pin, GPIO_PIN_SET);
}

static inline uint8_t pin_read(BSP_OneWire_t *ow)
{
    return (HAL_GPIO_ReadPin(ow->port, ow->pin) == GPIO_PIN_SET) ? 1 : 0;
}

/* ------------------------------------------------------------------------
 * API cong khai
 * ------------------------------------------------------------------------ */
void BSP_OneWire_Init(BSP_OneWire_t *ow, GPIO_TypeDef *port, uint16_t pin)
{
    ow->port = port;
    ow->pin  = pin;

    DWT_Delay_Init();

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin   = pin;
    gpio.Mode  = GPIO_MODE_OUTPUT_OD;   /* Open-drain - bat buoc cho 1-Wire */
    gpio.Pull  = GPIO_NOPULL;           /* Dung dien tro ngoai 4.7k, khong dung pull-up noi */
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(port, &gpio);

    pin_release(ow); /* Bus idle = muc cao */
}

uint8_t BSP_OneWire_Reset(BSP_OneWire_t *ow)
{
    uint8_t presence;

    pin_low(ow);
    delay_us(480);       /* Xung reset toi thieu 480us */

    pin_release(ow);
    delay_us(70);        /* Doi thiet bi keo xuong bao presence */

    presence = (pin_read(ow) == 0) ? 1 : 0; /* Thiet bi keo low = co mat */

    delay_us(410);       /* Hoan tat slot reset toi thieu 480us con lai */

    return presence;
}

void BSP_OneWire_WriteBit(BSP_OneWire_t *ow, uint8_t bit)
{
    if (bit) {
        pin_low(ow);
        delay_us(6);
        pin_release(ow);
        delay_us(64);
    } else {
        pin_low(ow);
        delay_us(60);
        pin_release(ow);
        delay_us(10);
    }
}

uint8_t BSP_OneWire_ReadBit(BSP_OneWire_t *ow)
{
    uint8_t bit;

    pin_low(ow);
    delay_us(2);
    pin_release(ow);
    delay_us(10);

    bit = pin_read(ow);

    delay_us(50); /* Hoan tat slot doc toi thieu ~60us */

    return bit;
}

void BSP_OneWire_WriteByte(BSP_OneWire_t *ow, uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++) {
        BSP_OneWire_WriteBit(ow, byte & 0x01);
        byte >>= 1; /* 1-Wire truyen LSB truoc */
    }
}

uint8_t BSP_OneWire_ReadByte(BSP_OneWire_t *ow)
{
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; i++) {
        byte >>= 1;
        if (BSP_OneWire_ReadBit(ow)) {
            byte |= 0x80;
        }
    }

    return byte;
}
