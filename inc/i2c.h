#ifndef _I2C_H_
#define _I2C_H_

void I2CInit();
void I2CDeinit();
uint8_t I2CRead(uint8_t slave, uint8_t addr, uint8_t * buffer, uint8_t size);
void I2CWrite(uint8_t slave, uint8_t addr, uint8_t * buffer, uint8_t size);

#endif