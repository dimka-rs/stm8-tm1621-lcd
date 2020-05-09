#ifndef _TM1621_H_
#define _TM1621_H_

void TM1621_PrintDec(int32_t val);
void TM1621_PrintHex(uint8_t *buf, uint8_t size);
void TM1621_PrintStr(uint8_t *buf, uint8_t size);
void TM1621_PrintRaw(uint8_t *buf, uint8_t size);
void TM1621_DotBat(uint8_t val);

enum
{
    TM1621_DOTBAT_CLEAR = 0,
    TM1621_DOTBAT_BATTOP = 1,
    TM1621_DOTBAT_BATMED = 2,
    TM1621_DOTBAT_BATLOW = 4,
    TM1621_DOTBAT_DOT3 = 8,
    TM1621_DOTBAT_DOT4 = 16,
    TM1621_DOTBAT_DOT5 = 32,
};

#endif /* _TM1621_H_ */
