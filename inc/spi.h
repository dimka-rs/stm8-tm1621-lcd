#ifndef _SPI_H_
#define _SPI_H_

void SPIInit();
void SPISend(uint8_t * data, uint8_t size);
inline void delay();

#endif