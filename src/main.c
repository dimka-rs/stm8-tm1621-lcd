#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "stdio.h" //sdcc, not standard
#include "ds3231.h"

/* declare private functions */


void main(void){
    ClockInit();
    GpioInit();
    UartInit();
/*
    printf("\r\nCompiled: %s %s\r\n", __DATE__, __TIME__);

    printf("SDCC: %d.%d.%d rev %d\r\n", __SDCC_VERSION_MAJOR,
        __SDCC_VERSION_MINOR, __SDCC_VERSION_PATCH, __SDCC_REVISION);
*/

    #define BUF_SIZE 7
    uint8_t buf[BUF_SIZE];
    I2CInit();
    while(1)
    {
        I2CRead(DS3231_ADDR, DS3231_SECONDS, buf, BUF_SIZE);

        for(uint8_t i = 0; i < BUF_SIZE; i++)
        {
            printf("0x%02X ", buf[i]);
        }
        printf("\r\n");

        // delay about 1 s
        for(volatile uint32_t i = 0; i < 100000; i++);
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
