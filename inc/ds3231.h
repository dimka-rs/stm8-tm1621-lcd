#ifndef _DS3231_H_
#define _DS3231_H_

void DS3231_GetTime(uint8_t *buf, uint8_t size);
void DS3231_SetTime(uint8_t *buf, uint8_t size);
void DS3231_GetTemp(int8_t *val, uint8_t *frac);

#endif