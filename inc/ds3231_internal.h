#ifndef _DS3231_INTERNAL_H_
#define _DS3231_INTERNAL_H_

/* slave address 1101 0000 */
#define DS3231_ADDR         0xD0

/* registers */
#define DS3231_SECONDS      0x00
#define DS3231_MINUTES      0x01
#define DS3231_HOURS        0x02
#define DS3231_DAY          0x03
#define DS3231_DATE         0x04
#define DS3231_MONTH        0x05
#define DS3231_YEAR         0x06
#define DS3231_A1_SECONDS   0x07
#define DS3231_A1_MINUTES   0x08
#define DS3231_A1_HOURS     0x09
#define DS3231_A1_DAY_DATE  0x0A
#define DS3231_A2_MINUTES   0x0B
#define DS3231_A2_HOURS     0x0C
#define DS3231_A2_DAY_DATE  0x0D
#define DS3231_CONTROL      0x0E
#define DS3231_CTRL_STATUS  0x0F
#define DS3231_AGING_OFFSET 0x10
#define DS3231_TEMP_MSB     0x11
#define DS3231_TEMP_LSB     0x12

#endif /* _DS3231__INTERNAL_H_ */