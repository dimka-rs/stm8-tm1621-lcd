#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "spi.h"
#include "stdio.h" //sdcc, not standard
#include "ds3231.h"

/* declare private functions */


void main(void){
    ClockInit();
    GpioInit();
    UartInit();
    I2CInit();

    printf("\r\nCompiled: %s %s\r\n", __DATE__, __TIME__);
/*
    printf("SDCC: %d.%d.%d rev %d\r\n", __SDCC_VERSION_MAJOR,
        __SDCC_VERSION_MINOR, __SDCC_VERSION_PATCH, __SDCC_REVISION);
*/

    #define BUF_SIZE 3
    uint8_t buf[BUF_SIZE];

//#define SETTIME
#ifdef SETTIME

    buf[0] = (__TIME__[6] - '0')*16 + (__TIME__[7] - '0');
    buf[1] = (__TIME__[3] - '0')*16 + (__TIME__[4] - '0');
    buf[2] = (__TIME__[0] - '0')*16 + (__TIME__[1] - '0');
    printf("Start: %02X:%02X:%02X\r\n", buf[2], buf[1], buf[0]);
    I2CWrite(DS3231_ADDR, DS3231_SECONDS, buf, BUF_SIZE);
#endif

    //LCD
    enum
    {
        CMD_SIZE_BITS = 12,
        CMD_SIZE_BYTES = CMD_SIZE_BITS / 8 + 1,
        DATA_SIZE_BITS = (9 + 16*8),
        DATA_SIZE_BYTES = DATA_SIZE_BITS / 8 + 1,
    };
    uint8_t lcd_on[CMD_SIZE_BYTES] = {0x80, 0x60};
    uint8_t lcd_en[CMD_SIZE_BYTES] = {0x80, 0x20};
    // 9 bits command+addr followed by 16 bytes of data
    // total 18 bytes, but 137 bits
    uint8_t data[DATA_SIZE_BYTES];

    while(1)
    {
        I2CRead(DS3231_ADDR, DS3231_SECONDS, buf, BUF_SIZE);

        for(int8_t i = BUF_SIZE - 1; i >= 0; i--)
        {
            printf("%02X ", buf[i]);
        }
        printf("\r\n");

        for(uint8_t i = 0; i < DATA_SIZE_BYTES; i++)
        {
            data[i] = buf[0]; //fill data with seconds
        }
        data[0] = 0xA0; //cmd write + addr
        data[1] &= 0x7E; //clear msb, it is address lsb
        SPISend(lcd_on, CMD_SIZE_BITS);
        SPISend(lcd_en, CMD_SIZE_BITS);
        SPISend(data, DATA_SIZE_BITS);

        // delay about 1 s
        for(volatile uint32_t d = 0; d < 80000; d++);
    }



}

int putchar (int c)
{
    // this implementation is SDCC 3.8 specific
    // see sdcc stdio.h for details
    UART1->DR = (uint8_t) c;
    while (!(UART1->SR & UART1_FLAG_TXE));
    return c;
}

/***********************************************************************/


// This is called by some of the SPL files on error.
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  (void)file;
  (void)line;

  /* User can add their own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
