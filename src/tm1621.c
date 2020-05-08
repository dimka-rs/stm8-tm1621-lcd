#include "stm8s.h"
#include "tm1621_internal.h"
#include "tm1621.h"
#include "gpio_names.h"

/* Segments map
 * -a-
 * f b
 * -g-
 * e c
 * -d-
 *
 * bit 7 - dot or bat
 *
 * bit 6 - c
 * bit 5 - b
 * bit 4 - a
 *
 * bit 3 - d
 * bit 2 - e
 * bit 1 - g
 * bit 0 - f
 */

static uint8_t table[] =
{
/*  32 0  33 !  34 "  35 #  36 $  37 %  38 &  39 ' */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  40 (  41 )  42 *  43 +  44 ,  45 -  46 .  47 / */
    0x00, 0x00, 0x33, 0x00, 0x00, 0x02, 0x00, 0x00,
/*  48 0  49 1  50 2  51 3  52 4  53 5  54 6  55 7 */
    0x7D, 0x60, 0x3E, 0x7A, 0x63, 0x5B, 0x5F, 0x70,
/*  56 8  57 9  58 :  59 ;  60 <  61 =  62 >  63 ? */
    0x7F, 0x7B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  64 @  65 A  66 B  67 C  68 D  69 E  70 F  71 G */
    0x00, 0x77, 0x4F, 0x1D, 0x6E, 0x1F, 0x17, 0x00,
/*  72 H  73 I  74 J  75 K  76 L  77 M  78 N  79 O */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  80 P  81 Q  82 R  83 S  84 T  85 U  86 V  87 W */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/*  88 X  89 Y  90 Z  91 [  92 \  93 ]  94 ^  95 _*/
    0x00, 0x00, 0x00, 0x1D, 0x00, 0x78, 0x10, 0x08,
};

static uint8_t lcd_buf[6];

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
            if (cur_byte & 0x80)
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
    if (size > 6)
        size = 6;

    for (uint8_t i = 0; i < size; i++)
    {
        lcd_buf[size - i - 1] = 0;
        if (buf[i] >= 32 && buf[i] <= 95)
            lcd_buf[size - i - 1] = table[buf[i] - 32];
        else
            lcd_buf[size - i - 1] = 0;
    }
    TM1621_PrintRaw(lcd_buf, size);
}

void TM1621_PrintHex(uint8_t *buf, uint8_t size)
{
    uint8_t idx;
    if (size > 3)
        size = 3;

    for (uint8_t i = 0; i < size; i++)
    {
        idx = (buf[i] & 0xF0) >> 4;
        if (idx >= 10)
            idx = 'A' + idx - 32;
        else
            idx = '0' + idx - 32;

        lcd_buf[(size * 2 - 1) - (2 * i)] = table[idx];

        idx = buf[i] & 0x0F;
        if (idx >= 10)
            idx = 'A' + idx - 32;
        else
            idx = '0' + idx - 32;

        lcd_buf[(size * 2 - 1) - (2 * i + 1)] = table[idx];
    }
    TM1621_PrintRaw(lcd_buf, size * 2);
}

void TM1621_PrintDec(int32_t val)
{
    if (val > 999999 || val < -99999)
    {
        for (int i = 0; i < 6; i++)
            lcd_buf[i] = table['-' - 32];
    }
    TM1621_PrintRaw(lcd_buf, 6);
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