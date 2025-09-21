#pragma once
#include <stdint.h>

#define UART_COM1_BASE  0x3F8
#define UART_DLL        0x00
#define UART_DLM        0x01
#define UART_IER        0x01
#define UART_IIR        0x02
#define UART_FCR        0x02
#define UART_LCR        0x03
#define UART_MCR        0x04
#define UART_LSR        0x05
#define UART_MSR        0x06
#define UART_SCR        0x07
#define UART_THR        0x00

void uart_init(void);
void uart_putchar(char c);
int uart_puts(const char *s);