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
    SPIInit();

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
    #define CMD_SIZE 2
    uint8_t cmd[CMD_SIZE] = {0xA0, 0x60};
    #define DATA_SIZE 8
    uint8_t data[DATA_SIZE] = {0xA0, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};

    while(1)
    {
        I2CRead(DS3231_ADDR, DS3231_SECONDS, buf, BUF_SIZE);

        for(int8_t i = BUF_SIZE - 1; i >= 0; i--)
        {
            printf("%02X ", buf[i]);
        }
        printf("\r\n");


        SPISend(cmd, CMD_SIZE);
        SPISend(data, DATA_SIZE);

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
