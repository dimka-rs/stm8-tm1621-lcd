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

/*
 * PC4 - SPI_CS
 * PC5 - SPI_SCK
 * PC6 - SPI_MOSI
 * PC7 - SPI_MISO
 */
#define SPI_PORT (GPIOC)
#define SPI_CS   (1 << 4)

 /*
 * PD1 - SYS_SWIM
 */


#endif
