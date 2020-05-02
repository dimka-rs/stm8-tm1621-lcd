#include "stm8s.h"
#include "tm1621_internal.h"
#include "tm1621.h"
#include "spi.h"
#include "gpio_names.h"


void TM1621_Print(uint8_t *buf, uint8_t size)
{
        GPIO_WriteLow(SPI_PORT, SPI_CS);
        SPISend(lcd_on, CMD_SIZE_BITS);
        GPIO_WriteHigh(SPI_PORT, SPI_CS);

        GPIO_WriteLow(SPI_PORT, SPI_CS);
        SPISend(lcd_en, CMD_SIZE_BITS);
        GPIO_WriteHigh(SPI_PORT, SPI_CS);

        GPIO_WriteLow(SPI_PORT, SPI_CS);
        SPISend(mem_addr, MEM_ADDR_BITS);
        SPISend(buf, DATA_SIZE_BITS);
        GPIO_WriteHigh(SPI_PORT, SPI_CS);
}