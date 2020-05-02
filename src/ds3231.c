#include "stm8s.h"
#include "ds3231_internal.h"
#include "ds3231.h"
#include "i2c.h"
#include "stdio.h"

void DS3231_GetTime(uint8_t *buf, uint8_t size)
{
    I2CRead(DS3231_ADDR, DS3231_SECONDS, buf, size);
    /*
    for(int8_t i = BUF_SIZE - 1; i >= 0; i--)
        printf("%02X ", buf[i]);

    printf("\r\n");
    */
}

void DS3231_SetTime(uint8_t *buf, uint8_t size)
{
//#define SETTIME
#ifdef SETTIME

    buf[0] = (__TIME__[6] - '0')*16 + (__TIME__[7] - '0');
    buf[1] = (__TIME__[3] - '0')*16 + (__TIME__[4] - '0');
    buf[2] = (__TIME__[0] - '0')*16 + (__TIME__[1] - '0');
//    printf("Start: %02X:%02X:%02X\r\n", buf[2], buf[1], buf[0]);
    I2CWrite(DS3231_ADDR, DS3231_SECONDS, buf, size);
#endif
}
