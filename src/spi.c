#include "main.h"
#include "stdio.h"
#include "stm8s_spi.h"
#include "stm8s_gpio.h"
#include "spi.h"

void SPISend(uint8_t * data, uint8_t size)
{
    uint8_t tx, byte_max, bits_max, last_bits;
    byte_max = 1 + size / 8;
    last_bits = size & 8;
    GPIO_WriteLow(SPI_PORT, SPI_CS);
    delay();
    for(uint8_t byte = 0; byte < byte_max; byte++)
    {
        tx = data[byte];
        if(byte == byte_max)
        {
            bits_max = last_bits;
        } else {
            bits_max = 8;
        }
        for(uint8_t bit = 0; bit < bits_max; bit++)
        {
            if(tx & 0x80)
            {
                GPIO_WriteHigh(SPI_PORT, SPI_MOSI);
            } else {
                GPIO_WriteLow(SPI_PORT, SPI_MOSI);
            }
            GPIO_WriteLow(SPI_PORT, SPI_SCK);
            delay();
            GPIO_WriteHigh(SPI_PORT, SPI_SCK);
            delay();
            tx = tx << 1;
        }
    }
    GPIO_WriteHigh(SPI_PORT, SPI_CS);
    delay();
}

inline void delay()
{
    for(volatile uint8_t i = 0; i < 20; i++);
}
