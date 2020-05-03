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

/* 3 bits command mode followed by 9 bit of command body */
/* 0x 100 0000 0001 X */
uint8_t sys_en[CMD_SIZE_BYTES] = {0x80, 0x20};
/* 0x 100 0000 0000 X */
uint8_t sys_dis[CMD_SIZE_BYTES] = {0x80, 0x00};
/* 0b 100 0000 0010 X */
uint8_t lcd_off[CMD_SIZE_BYTES] = {0x80, 0x40};
/* 0b 100 0000 0011 X */
uint8_t lcd_on[CMD_SIZE_BYTES] = {0x80, 0x60};
/* 0b 100 0010 abXc X
 * ab = 00: 2 commons
 * ab = 01: 3 commons
 * ab = 10: 4 commons
 * c = 0: 1/2 bias
 * c = 1: 1/3 bias
 */
uint8_t lcd_bias[CMD_SIZE_BYTES] = {0x85, 0x00};
/* 3 bits write mode, 6 bits address, followed by data in 4 bits chunks
 * 0b 101 AAAAAA DDDD DDDD ....
 */
uint8_t mem_addr[MEM_ADDR_BYTES] = {0xA0, 0x00};


#endif /* _TM1621_INTERNAL_H_ */