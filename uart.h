#ifndef __UART_H__
#define __UART_H__
#include <stm32f3x.h>
#include <stdint.h>

#define UART1_BASE (APB2_BASE + 0x3800)
#define UART2_BASE (APB1_BASE + 0x4400)
#define UART3_BASE (APB1_BASE + 0x4800)
#define UART4_BASE (APB1_BASE + 0x4C00)
#define UART5_BASE (APB1_BASE + 0x5000)

typedef struct {
    volatile uint32_t CR1;      // Control register 1
    volatile uint32_t CR2;      // Control register 2
    volatile uint32_t CR3;      // Control register 3
    volatile uint32_t BRR;      // Baud rate register
    volatile uint32_t GTPR;     // Guard time and prescaler register
    volatile uint32_t RTOR;     // Receiver timeout register
    volatile uint32_t RQR;      // Request register
    volatile uint32_t ISR;      // Interrupt & status register
    volatile uint32_t ICR;      // Interrupt flag clear register
    volatile uint32_t RDR;      // Receive data register
    volatile uint32_t TDR;      // Transmit data register
} UART_TypeDef;
#define UART1 ((UART_TypeDef *) UART1_BASE)
#define UART2 ((UART_TypeDef *) UART2_BASE)
#define UART3 ((UART_TypeDef *) UART3_BASE)
#define UART4 ((UART_TypeDef *) UART4_BASE)
#define UART5 ((UART_TypeDef *) UART5_BASE)

// UART functionalities
void uart_init(UART_TypeDef *uart, uint32_t baudrate);
void uart_send(UART_TypeDef *uart, uint8_t data);
char uart_receive(UART_TypeDef *uart);
void uart_enable_interrupt(UART_TypeDef *uart, uint32_t interrupt);
void uart_disable_interrupt(UART_TypeDef *uart, uint32_t interrupt);
void uart_clear_interrupt(UART_TypeDef *uart, uint32_t interrupt);
void uart_set_baudrate(UART_TypeDef *uart, uint32_t baudrate);
void uart_set_parity(UART_TypeDef *uart, uint32_t parity);
void uart_set_stop_bits(UART_TypeDef *uart, uint32_t stop_bits);
void uart_set_word_length(UART_TypeDef *uart, uint32_t word_length);
void uart_enable(UART_TypeDef *uart);
void uart_disable(UART_TypeDef *uart);
void uart_set_flow_control(UART_TypeDef *uart, uint32_t flow_control);
void uart_set_mode(UART_TypeDef *uart, uint32_t mode);
void uart_set_rx_timeout(UART_TypeDef *uart, uint32_t timeout);
void uart_enable_rx(UART_TypeDef *uart);
void uart_disable_rx(UART_TypeDef *uart);
void uart_enable_tx(UART_TypeDef *uart);
void uart_disable_tx(UART_TypeDef *uart);

#endif