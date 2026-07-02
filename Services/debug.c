#include "debug.h"
#include "bsp_uart.h"

#include <string.h>

static const char * const LogPrefix[] =
{
    "[INFO ] ",
    "[WARN ] ",
    "[ERROR] ",
    "[FATAL] "
};

void Debug_Log(DebugLevel_t level, const char *msg)
{
    if ((msg == NULL) || (level >= LOG_LEVEL_MAX))
    {
        return;
    }

    BSP_UART_Send((const uint8_t *)LogPrefix[level],
                  (uint16_t)strlen(LogPrefix[level]));

    BSP_UART_Send((const uint8_t *)msg,
                  (uint16_t)strlen(msg));

    BSP_UART_Send((const uint8_t *)"\r\n", 2U);
}
