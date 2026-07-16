#ifndef BOARD_H
#define BOARD_H

#include "main.h"

/* ------------------------------------------------------------------------
 * Dinh nghia chan phan cung theo board - noi DUY NHAT ghi cu the
 * GPIOx/PIN cho tung thiet bi. BSP va DeviceDrivers KHONG duoc hardcode
 * chan truc tiep trong file .c cua no - luon nhan qua tham so tu day.
 * ------------------------------------------------------------------------ */

/* DS18B20 - cam bien nhiet do dong co */
#define BOARD_DS18B20_PORT   GPIOB
#define BOARD_DS18B20_PIN    GPIO_PIN_5

/* Vi du cac chan khac da co san trong project (giu nguyen, chi minh hoa) */
/* #define BOARD_I2C_PORT     GPIOB */
/* #define BOARD_UART_TX_PIN  GPIO_PIN_9 */

#endif /* BOARD_H */
