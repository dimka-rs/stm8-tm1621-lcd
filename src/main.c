#include "stm8s.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "stdio.h" //sdcc, not standard
#include "ds3231.h"
#include "tm1621.h"

/* declare private functions */

void delay1s()
{
    for(volatile uint32_t d = 0; d < 80000; d++);
}

void Init_HW()
{
    ClockInit();
    GpioInit();
    UartInit();
    I2CInit();
}

void main(void){
    enum {
        RTC_BUF_SIZE = 3,
        LCD_BUF_SIZE = 6,
    };
    uint8_t rtc_buf[RTC_BUF_SIZE];
    uint8_t lcd_buf[LCD_BUF_SIZE];
    uint8_t pattern = 0;
    uint8_t counter = 0;

    Init_HW();

/*
    printf("\r\nCompiled: %s %s\r\n", __DATE__, __TIME__);
    printf("SDCC: %d.%d.%d rev %d\r\n", __SDCC_VERSION_MAJOR,
        __SDCC_VERSION_MINOR, __SDCC_VERSION_PATCH, __SDCC_REVISION);
*/


    while(1)
    {
        DS3231_GetTime(rtc_buf, RTC_BUF_SIZE);

#if 0
        /* Generate test pattern */
        if (counter++ > 8)
            counter = 0;

        if (counter == 8)
            pattern = 0;
        else
            pattern = 1 << counter;

        for(uint8_t i = 0; i < LCD_BUF_SIZE; i++)
            lcd_buf[i] = pattern;

        TM1621_PrintRaw(lcd_buf, LCD_BUF_SIZE);
#else
        TM1621_Print("012345", 6);
        delay1s();
        TM1621_Print("123456", 6);
        delay1s();
        TM1621_Print("234567", 6);
        delay1s();
        TM1621_Print("345678", 6);
        delay1s();
        TM1621_Print("456789", 6);
        delay1s();
        TM1621_Print("567890", 6);
        delay1s();
        TM1621_Print("678901", 6);
        delay1s();
        TM1621_Print("789012", 6);
        delay1s();
        TM1621_Print("890123", 6);
        delay1s();
        TM1621_Print("901234", 6);
        delay1s();
#endif
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
