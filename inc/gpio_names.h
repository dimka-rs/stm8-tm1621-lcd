#ifndef _GPIO_NAMES_H
#define _GPIO_NAMES_H

/*
 * PD5 - UART1_TX
 * PD6 - UART1_RX
 */
#define UART_PORT (GPIOD)
#define UART_TX  (1 << 5)
#define UART_RX  (1 << 6)

/*
 * PB5 - I2C_SDA
 * PB4 - I2C_SCL
 */
#define I2C_PORT (GPIOB)
#define I2C_SDA  (1 << 5)
#define I2C_SCL  (1 << 4)

/*
 * PC4 - SPI_CS
 * PC5 - SPI_SCK
 * PC6 - SPI_MOSI
 * PC7 - SPI_MISO
 */
#define SPI_PORT (GPIOC)
#define SPI_CS   (1 << 4)
#define SPI_SCK  (1 << 5)
#define SPI_MOSI (1 << 6)

/*
 * PD1 - SYS_SWIM
 */

#endif /* _GPIO_NAMES_H */