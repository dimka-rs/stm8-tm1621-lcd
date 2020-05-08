#ifndef _TM1621_H_
#define _TM1621_H_

void TM1621_PrintDec(int32_t val);
void TM1621_PrintHex(uint8_t *buf, uint8_t size);
void TM1621_PrintStr(uint8_t *buf, uint8_t size);
void TM1621_PrintRaw(uint8_t *buf, uint8_t size);

#endif /* _TM1621_H_ */