#include "main.h"
#include "stm8s_spi.h"
#include "stm8s_gpio.h"
#include "spi.h"

void SPIInit()
{
    SPI_Init(SPI_FIRSTBIT_MSB,
            SPI_BAUDRATEPRESCALER_8,
            SPI_MODE_MASTER,
            SPI_CLOCKPOLARITY_HIGH,
            SPI_CLOCKPHASE_2EDGE,
            SPI_DATADIRECTION_1LINE_TX,
            SPI_NSS_SOFT,
            0);
}

void SPISend(uint8_t * data, uint8_t size)
{
    uint8_t tx;
    GPIO_WriteLow(SPI_PORT, SPI_CS);
    delay();
    for(uint8_t byte = 0; byte < size; byte++)
    {
        tx = data[byte];
        for(uint8_t bit = 0; bit < 8; bit++)
        {
            if(tx & 0x80)
            {
                GPIO_WriteHigh(SPI_PORT, SPI_MOSI);
            } else {
                GPIO_WriteHigh(SPI_PORT, SPI_MOSI);
            }
            GPIO_WriteLow(SPI_PORT, SPI_SCK);
            delay();
            GPIO_WriteHigh(SPI_PORT, SPI_SCK);
            delay();
            tx = tx << 1;
        }
    }
    GPIO_WriteHigh(SPI_PORT, SPI_CS);
}

inline void delay()
{
    for(volatile uint8_t i = 0; i < 10; i++);
}
