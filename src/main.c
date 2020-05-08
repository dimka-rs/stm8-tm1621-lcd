#include "stm8s.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "i2c.h"
#include "stdio.h" //sdcc, not standard
#include "ds3231.h"
#include "tm1621.h"

/* declare private functions */

void delay_s(uint8_t delay)
{
    while (delay-- > 0)
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
    uint8_t cnt = 0;
    uint8_t tmp;
    int8_t temp;

    Init_HW();

/*
    printf("\r\nCompiled: %s %s\r\n", __DATE__, __TIME__);
    printf("SDCC: %d.%d.%d rev %d\r\n", __SDCC_VERSION_MAJOR,
        __SDCC_VERSION_MINOR, __SDCC_VERSION_PATCH, __SDCC_REVISION);
*/


    while(1)
    {
        DS3231_GetTime(rtc_buf, RTC_BUF_SIZE);

        /* Mirror array so that is starts with hours */
        tmp = rtc_buf[0];
        rtc_buf[0] = rtc_buf[2];
        rtc_buf[2] = tmp;

        if (cnt < 10)
        {
            TM1621_PrintHex(rtc_buf, 3);
        }
        else
        {
            if (cnt >= 12)
                cnt = 0;
            temp = DS3231_GetTemp();
            if (temp > 99)
                temp = 99;
            if (temp < -99)
                temp = -99;

            if (temp < 0)
            {
                lcd_buf[0] = '-';
                temp = temp * -1;
            }
            else
            {
                lcd_buf[0] = ' ';
            }

            if (temp > 10)
                lcd_buf[1] = temp / 10 + '0';
            else
                lcd_buf[1] = ' ';

            lcd_buf[2] = temp % 10 + '0';

            lcd_buf[3] = ' ';
            lcd_buf[4] = '*';
            lcd_buf[5] = 'C';

            TM1621_PrintStr(lcd_buf, 6);
        }

        printf("Time: %02X:%02X:%02X\r\n", rtc_buf[0], rtc_buf[1], rtc_buf[2]);
        printf("Temp: %d C\r\n", DS3231_GetTemp());
        cnt++;
        delay_s(1);

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
        delay_s(1);
#endif

#if 0
        TM1621_PrintStr("012345", 6);
        delay_s(1);
        TM1621_PrintStr("123456", 6);
        delay_s(1);
        TM1621_PrintStr("234567", 6);
        delay_s(1);
        TM1621_PrintStr("345678", 6);
        delay_s(1);
        TM1621_PrintStr("456789", 6);
        delay_s(1);
        TM1621_PrintStr("567890", 6);
        delay_s(1);
        TM1621_PrintStr("678901", 6);
        delay_s(1);
        TM1621_PrintStr("789012", 6);
        delay_s(1);
        TM1621_PrintStr("890123", 6);
        delay_s(1);
        TM1621_PrintStr("901234", 6);
        delay_s(1);
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
