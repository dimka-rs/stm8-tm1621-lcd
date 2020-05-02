#ifndef _TM1621_INTERNAL_H_
#define _TM1621_INTERNAL_H_

//LCD
enum
{
    CMD_SIZE_BITS = 12,
    CMD_SIZE_BYTES = CMD_SIZE_BITS / 8 + 1,
    MEM_ADDR_BITS = 9,
    MEM_ADDR_BYTES = MEM_ADDR_BITS / 8 + 1,
    DATA_SIZE_BITS = 32*4,
    DATA_SIZE_BYTES = DATA_SIZE_BITS / 8 + 1,
};

uint8_t lcd_on[CMD_SIZE_BYTES] = {0x80, 0x60};
uint8_t lcd_en[CMD_SIZE_BYTES] = {0x80, 0x20};
uint8_t mem_addr[MEM_ADDR_BYTES] = {0b10100000, 0};
// 9 bits command+addr followed by 16 bytes of data
// total 18 bytes, but 137 bits

#endif /* _TM1621_INTERNAL_H_ */