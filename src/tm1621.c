#include "stm8s.h"
#include "tm1621_internal.h"
#include "tm1621.h"
#include "gpio_names.h"

static uint8_t table[] =
{
/*  48 0  49 1  50 2  51 3  52 4  53 5  54 6  55 7  56 8  57 9 */
    0x7D, 0x60, 0x3E, 0x7A, 0x63, 0x5B, 0x5F, 0x70, 0x7F, 0x7B,
/*  65 A  66 B  67 C  68 D  69 E  70 F*/
    0x77, 0x4F, 0x1D, 0x6E, 0x1F, 0x17
};

static inline void
delay()
{
    for(volatile uint8_t i = 0; i < 20; i++);
}

static void
TM1621_Send(uint8_t * data, uint8_t size)
{
    uint8_t cur_byte, last_byte, num_bits, last_bits;

    last_byte = size / 8;
    last_bits = size % 8;

    if (last_bits != 0)
        last_byte += 1;

    if (last_bits == 0)
        last_bits = 8;

    for (uint8_t idx = 0; idx < last_byte; idx++)
    {
        cur_byte = data[idx];
        if (idx == last_byte - 1)
            num_bits = last_bits;
        else
            num_bits = 8;

        /* Send current byte */
        for(uint8_t bit = 0; bit < num_bits; bit++)
        {
            /* Set data line */
            if(cur_byte & 0x80)
                GPIO_WriteHigh(SPI_PORT, SPI_MOSI);
            else
                GPIO_WriteLow(SPI_PORT, SPI_MOSI);

            /* Latch on rising edge */
            GPIO_WriteHigh(SPI_PORT, SPI_SCK);
            delay();
            GPIO_WriteLow(SPI_PORT, SPI_SCK);
            delay();

            cur_byte = cur_byte << 1;
        }
    }
}

void TM1621_PrintStr(uint8_t *buf, uint8_t size)
{
    uint8_t lcd_buf[6];

    if (size > 6)
        size = 6;

    for (uint8_t i = 0; i < size; i++)
    {
        lcd_buf[size - i - 1] = 0;
        if (buf[i] >= '0' && buf[i] <= '9')
            lcd_buf[size - i - 1] = table[buf[i] - '0'];
    }
    TM1621_PrintRaw(lcd_buf, size);
}

void TM1621_PrintHex(uint8_t *buf, uint8_t size)
{
    uint8_t lcd_buf[6];

    if (size > 3)
        size = 3;

    for (uint8_t i = 0; i < size; i++)
    {
        lcd_buf[(size * 2 - 1) - (2 * i)] = table[(buf[i] & 0xF0) >> 4];
        lcd_buf[(size * 2 - 1) - (2 * i + 1)] = table[buf[i] & 0x0F];
    }
    TM1621_PrintRaw(lcd_buf, size * 2);
}

void TM1621_PrintRaw(uint8_t *buf, uint8_t size)
{
    GPIO_WriteLow(SPI_PORT, SPI_CS);
    TM1621_Send(lcd_on, CMD_SIZE_BITS);
    GPIO_WriteHigh(SPI_PORT, SPI_CS);

    GPIO_WriteLow(SPI_PORT, SPI_CS);
    TM1621_Send(sys_en, CMD_SIZE_BITS);
    GPIO_WriteHigh(SPI_PORT, SPI_CS);

    GPIO_WriteLow(SPI_PORT, SPI_CS);
    TM1621_Send(lcd_bias, CMD_SIZE_BITS);
    GPIO_WriteHigh(SPI_PORT, SPI_CS);

    GPIO_WriteLow(SPI_PORT, SPI_CS);
    TM1621_Send(mem_addr, MEM_ADDR_BITS);
    TM1621_Send(buf, size * 8);
    GPIO_WriteHigh(SPI_PORT, SPI_CS);
}