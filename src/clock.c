#include "stm8s.h"

void ClockInit() {
	/* SYSCLK: 16/8 = 2 MHz, CPUCLK: 2/1 = 2 MHz */
	/* CPU DIV Masked cause high bit must be cleared, but it is set to distinguish
		system and CPU dividers
	*/
	CLK->CKDIVR |= (uint8_t) CLK_PRESCALER_HSIDIV8 | (CLK_PRESCALER_CPUDIV1 & 0x07);

}
