#include "bsp_uart.h"
#include "usart.h"

void BSP_UART_Send(const uint8_t *data, uint16_t len)
{
    HAL_UART_Transmit(&huart1,
                      (uint8_t *)data,
                      len,
                      HAL_MAX_DELAY);
}
