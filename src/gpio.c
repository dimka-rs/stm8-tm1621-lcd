#include "main.h"

void GpioInit() {
	/* I2C */	
	GPIO_Init(I2C_PORT, I2C_SCL, GPIO_MODE_OUT_OD_HIZ_SLOW);
	GPIO_Init(I2C_PORT, I2C_SDA, GPIO_MODE_OUT_OD_HIZ_SLOW);

	for (uint8_t i = 0; i < 100; i++)
	{
		// toggle clock to reset any strange slave state //
		GPIO_WriteReverse(I2C_PORT, I2C_SCL);
		// delay around 5 us //
		for(volatile uint8_t j = 0; j < 10; j++);
	}

}
