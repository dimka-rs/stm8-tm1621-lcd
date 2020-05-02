#include "stm8s.h"
#include "gpio.h"
#include "gpio_names.h"

void GpioInit()
{
    GPIO_Init(SPI_PORT, SPI_CS,   GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(SPI_PORT, SPI_SCK,  GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(SPI_PORT, SPI_MOSI, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(I2C_PORT, I2C_SCL,  GPIO_MODE_OUT_PP_HIGH_SLOW);

#if 0
    for (uint8_t i = 0; i < 10; i++)
    {
        // toggle clock to reset any strange slave state //
        GPIO_WriteReverse(I2C_PORT, I2C_SCL);
        // delay around 5 us //
        for(volatile uint8_t j = 0; j < 10; j++);
    }
#endif

}
