#pragma once
#include <stdint.h>

#define UART_COM1_BASE  0x3F8 // COM1
#define UART_DLL        0x00  // divisor latch low
#define UART_DLM        0x01  // divisor latch high
#define UART_IER        0x01  // interrupt enable register
#define UART_IIR        0x02  // interrupt identification register (read); aliased with FCR (write)
#define UART_FCR        0x02  // FIFO control register (write-only)
#define UART_LCR        0x03  // line control register (frame format and DLAB control)
#define UART_MCR        0x04  // modem control register (RS-232 signal control)
#define UART_LSR        0x05  // line status register (transmit/receive readiness)
#define UART_MSR        0x06  // modem status register (input status from modem)
#define UART_SCR        0x07  // scratch register (general-purpose storage)
#define UART_THR        0x00  // transmit holding register (accessed when DLAB=0 in LCR)

void uart_init(void);
void uart_putchar(char c);
int uart_puts(const char *s);