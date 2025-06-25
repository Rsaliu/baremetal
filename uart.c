#include "uart.h"
#include "rcc.h"
#include <stdint.h>
#include <gpio.h>
#include <stm32f3x.h>

static const uint32_t SystemCoreClock = 8000000; // Assuming a system clock of 8 MHz, adjust as necessary
void uart_init(UART_TypeDef *uart, uint32_t baudrate){
    // Enable the UART clock
    if (uart == UART1) {
        RCC->APB2ENR |= (1 << 14); // Enable UART1 clock
        RCC->AHBENR |= GPIOC_ENABLE; // Enable GPIOC clock for UART1
        GPIOC->AFRL |= (0x7 << 16); // set alterate function for PC4 to TX
        GPIOC->AFRL |= (0x7 << 20); // set alternate function for PC5 to RX
        GPIOC->MODER |= (ALTERNATE_FUNCTION << 8); // Set PC4 as alternate function (TX)
        GPIOC->MODER |= (ALTERNATE_FUNCTION << 10); // Set PC5 as alternate function (RX)
    } else if (uart == UART2) {
        RCC->APB1ENR |= (1 << 17); // Enable UART2 clock
        RCC->AHBENR |= GPIOA_ENABLE; // Enable GPIOA clock for UART2
        GPIOA->AFRL |= (0x7 << 8); // set alternate function for PA2 to TX
        GPIOA->AFRL |= (0x7 << 12); // set alternate function for PA3 to RX
        GPIOA->MODER |= (ALTERNATE_FUNCTION << 4); // Set PA2 as alternate function (TX)
        GPIOA->MODER |= (ALTERNATE_FUNCTION << 6); // Set PA3 as alternate function (RX)
    } else if (uart == UART3) {
        RCC->APB1ENR |= (1 << 18); // Enable UART3 clock
        RCC->AHBENR |= GPIOB_ENABLE; // Enable GPIOB clock for UART3
        GPIOB->AFRH |= (0x7 << 8); // set alternate function for PB10 to TX
        GPIOB->AFRH |= (0x7 << 12); // set alternate function for PB11 to RX
        GPIOB->MODER |= (ALTERNATE_FUNCTION << 20); // Set PB10 as alternate function (TX)
        GPIOB->MODER |= (ALTERNATE_FUNCTION << 22); // Set PB11 as alternate function (RX)
    }else;

    // Set the baud rate
    uart->BRR = SystemCoreClock / baudrate;

    // Configure the control registers
    uart->CR1 = 0; // Reset CR1
    uart->CR2 = 0; // Reset CR2
    uart->CR3 = 0; // Reset CR3

    // Enable the UART
    uart->CR1 |= 1; // UE bit in CR1 to enable the USART
    uart->CR1 |= (3 << 3); // TE & RE bits in CR1 to enable transmitter
}
void uart_send(UART_TypeDef *uart, uint8_t data){
    // Wait until the transmit data register is empty
    uart_disable_rx(uart); // Ensure RX is disabled
    uart_enable_tx(uart);
    while (!(uart->ISR & (1 << 7))); // TXE bit in ISR

    // Write the data to the transmit data register
    uart->TDR = data;
}
char uart_receive(UART_TypeDef *uart){
    // Wait until the receive data register is not empty
    uart_disable_tx(uart); // Ensure TX is disabled
    uart_enable_rx(uart); // Ensure RX is enabled
    while (!(uart->ISR & (1 << 5))); // RXNE bit in ISR
    return uart->RDR;
}
void uart_enable_interrupt(UART_TypeDef *uart, uint32_t interrupt){
    // Enable the specified interrupt
    if (interrupt & (1 << 0)) { // TXEIE
        uart->CR1 |= (1 << 7);
    }
    if (interrupt & (1 << 1)) { // TCIE
        uart->CR1 |= (1 << 6);
    }
    if (interrupt & (1 << 2)) { // RXNEIE
        uart->CR1 |= (1 << 5);
    }
    if (interrupt & (1 << 3)) { // IDLEIE
        uart->CR1 |= (1 << 4);
    }
}
void uart_disable_interrupt(UART_TypeDef *uart, uint32_t interrupt){
    // Disable the specified interrupt
    if (interrupt & (1 << 0)) { // TXEIE
        uart->CR1 &= ~(1 << 7);
    }
    if (interrupt & (1 << 1)) { // TCIE
        uart->CR1 &= ~(1 << 6);
    }
    if (interrupt & (1 << 2)) { // RXNEIE
        uart->CR1 &= ~(1 << 5);
    }
    if (interrupt & (1 << 3)) { // IDLEIE
        uart->CR1 &= ~(1 << 4);
    }
}
void uart_clear_interrupt(UART_TypeDef *uart, uint32_t interrupt){
    // Clear the specified interrupt
    if (interrupt & (1 << 0)) { // TXE
        uart->ICR |= (1 << 7); // Clear TXE flag
    }
    if (interrupt & (1 << 1)) { // TC
        uart->ICR |= (1 << 6); // Clear TC flag
    }
    if (interrupt & (1 << 2)) { // RXNE
        uart->ICR |= (1 << 5); // Clear RXNE flag
    }
    if (interrupt & (1 << 3)) { // IDLE
        uart->ICR |= (1 << 4); // Clear IDLE flag
    }
}
void uart_set_baudrate(UART_TypeDef *uart, uint32_t baudrate){
    // Set the baud rate
    uart->BRR = SystemCoreClock / baudrate;
}
void uart_set_parity(UART_TypeDef *uart, uint32_t parity){
    // Set the parity mode
    if (parity == 0) { // No parity
        uart->CR1 &= ~(1 << 10); // PCE bit in CR1
    } else if (parity == 1) { // Even parity
        uart->CR1 |= (1 << 10); // PCE bit in CR1
        uart->CR1 &= ~(1 << 9); // PS bit in CR1
    } else if (parity == 2) { // Odd parity
        uart->CR1 |= (1 << 10); // PCE bit in CR1
        uart->CR1 |= (1 << 9); // PS bit in CR1
    }
}
void uart_set_stop_bits(UART_TypeDef *uart, uint32_t stop_bits){
    // Set the number of stop bits
    if (stop_bits == 1) {
        uart->CR2 &= ~(3 << 12); // Clear STOP bits in CR2
    } else if (stop_bits == 2) {
        uart->CR2 |= (2 << 12); // Set STOP bits to 2
    } else if (stop_bits == 0.5) {
        uart->CR2 |= (1 << 12); // Set STOP bits to 0.5
    } else if (stop_bits == 1.5) {
        uart->CR2 |= (3 << 12); // Set STOP bits to 1.5
    }
}
void uart_set_word_length(UART_TypeDef *uart, uint32_t word_length){
    // Set the word length
    if (word_length == 8) {
        uart->CR1 &= ~(1 << 12); // M0 bit in CR1
        uart->CR1 &= ~(1 << 28); // M1 bit in CR1
    } else if (word_length == 9) {
        uart->CR1 |= (1 << 12); // M0 bit in CR1
        uart->CR1 &= ~(1 << 28); // M1 bit in CR1
    } else if (word_length == 7) {
        uart->CR1 &= ~(1 << 12); // M0 bit in CR1
        uart->CR1 |= (1 << 28); // M1 bit in CR1
    }
}
void uart_enable(UART_TypeDef *uart){
    // Enable the UART
    uart->CR1 |= (1 << 13); // UE bit in CR1 to enable the USART
}
void uart_disable(UART_TypeDef *uart){
    // Disable the UART
    uart->CR1 &= ~(1 << 13); // UE bit in CR1 to disable the USART
}
void uart_set_flow_control(UART_TypeDef *uart, uint32_t flow_control){
    // Set the flow control mode
    if (flow_control == 0) { // No flow control
        uart->CR3 &= ~(1 << 8); // CTSE bit in CR3
        uart->CR3 &= ~(1 << 9); // RTSE bit in CR3
    } else if (flow_control == 1) { // RTS flow control
        uart->CR3 |= (1 << 8); // CTSE bit in CR3
        uart->CR3 &= ~(1 << 9); // RTSE bit in CR3
    } else if (flow_control == 2) { // CTS flow control
        uart->CR3 &= ~(1 << 8); // CTSE bit in CR3
        uart->CR3 |= (1 << 9); // RTSE bit in CR3
    } else if (flow_control == 3) { // RTS and CTS flow control
        uart->CR3 |= (1 << 8); // CTSE bit in CR3
        uart->CR3 |= (1 << 9); // RTSE bit in CR3
    }
}
void uart_set_mode(UART_TypeDef *uart, uint32_t mode){
    // Set the mode (transmit, receive, or both)
    if (mode == 0) { // Transmit only
        uart->CR1 |= (1 << 3); // TE bit in CR1
        uart->CR1 &= ~(1 << 2); // RE bit in CR1
    } else if (mode == 1) { // Receive only
        uart->CR1 &= ~(1 << 3); // TE bit in CR1
        uart->CR1 |= (1 << 2); // RE bit in CR1
    } else if (mode == 2) { // Transmit and receive
        uart->CR1 |= (1 << 3); // TE bit in CR1
        uart->CR1 |= (1 << 2); // RE bit in CR1
    }
}
void uart_set_rx_timeout(UART_TypeDef *uart, uint32_t timeout){
    // Set the receiver timeout value
    uart->RTOR = timeout; // Set the receiver timeout register
}
void uart_enable_rx(UART_TypeDef *uart){
    // Enable the receiver
    uart->CR1 |= (1 << 2); // RE bit in CR1 to enable the receiver
}
void uart_disable_rx(UART_TypeDef *uart){
    // Disable the receiver
    uart->CR1 &= ~(1 << 2); // RE bit in CR1 to disable the receiver
}
void uart_enable_tx(UART_TypeDef *uart){
    // Enable the transmitter
    uart->CR1 |= (1 << 3); // TE bit in CR1 to enable the transmitter
}
void uart_disable_tx(UART_TypeDef *uart){
    // Disable the transmitter
    uart->CR1 &= ~(1 << 3); // TE bit in CR1 to disable the transmitter
}