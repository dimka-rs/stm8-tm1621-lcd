#include "stm8s.h"
#include "uart.h"

void UartInit() {
    UartDeinit();
    /* Tx/Rx baud rate = f MASTER / UART_DIV
    * 115200 = 2 * 10^6 / x
    * x = 17.36 = 0x11
    */
    UART1->BRR2 = 0x01;
    UART1->BRR1 = 0x01;
    UART1->CR2 |= UART1_CR2_TEN | UART1_CR2_REN;
    UART1->CR1 &= (uint8_t)(~UART1_CR1_UARTD);

}

void UartDeinit() {
    UART1->CR1 = UART1_CR1_RESET_VALUE;
    UART1->CR2 = UART1_CR2_RESET_VALUE;
    UART1->CR3 = UART1_CR3_RESET_VALUE;
    UART1->CR4 = UART1_CR4_RESET_VALUE;
    UART1->CR5 = UART1_CR5_RESET_VALUE;

    UART1->CR1 |= UART1_CR1_UARTD;
}