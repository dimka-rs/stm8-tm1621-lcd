#ifndef _MAIN_H_
#define _MAIN_H_

#include "stm8s.h"


/* GPIO Names */

/*
 * PD5 - UART1_TX
 * PD6 - UART1_RX
 */

/*
 * PB5 - I2C_SDA
 * PB4 - I2C_SCL
 */
#define I2C_PORT (GPIOB)
#define I2C_SCL (4)
#define I2C_SDA (5)

/*
 * PC5 - SPI_SCK
 * PC6 - SPI_MOSI
 * PC7 - SPI_MISO
 * PD1 - SYS_SWIM
 */


#endif
