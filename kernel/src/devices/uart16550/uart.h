#pragma once
#include <stddef.h>
#include <stdint.h>

// Base address for COM1
#define UART_COM1_BASE 0x3F8

// UART register offsets
#define UART_REG_DLL 0x00 // Divisor Latch Low (DLAB=1)
#define UART_REG_DLM 0x01 // Divisor Latch High (DLAB=1)
#define UART_REG_IER 0x01 // Interrupt Enable Register (DLAB=0)
#define UART_REG_IIR 0x02 // Interrupt Identification Register (read)
#define UART_REG_FCR 0x02 // FIFO Control Register (write)
#define UART_REG_LCR 0x03 // Line Control Register
#define UART_REG_MCR 0x04 // Modem Control Register
#define UART_REG_LSR 0x05 // Line Status Register
#define UART_REG_MSR 0x06 // Modem Status Register
#define UART_REG_SCR 0x07 // Scratch Register
#define UART_REG_THR 0x00 // Transmit Holding Register (DLAB=0)

// Useful bit masks
#define UART_LCR_DLAB        0x80 // Divisor Latch Access Bit
#define UART_LCR_8N1         0x03 // 8 bits, no parity, 1 stop bit
#define UART_FCR_ENABLE_FIFO 0x01
#define UART_FCR_CLEAR_RX    0x02
#define UART_FCR_CLEAR_TX    0x04
#define UART_FCR_TRIGGER_14B 0xC0 // (bits 7-6 = 11)
#define UART_MCR_DTR         0x01
#define UART_MCR_RTS         0x02
#define UART_MCR_OUT2        0x08
#define UART_LSR_THRE        0x20 // Transmit Holding Register Empty

// Default divisor for 115200 baud at 1.8432 MHz clock
#define UART_DIVISOR_LSB 0x01
#define UART_DIVISOR_MSB 0x00

void _uart_init();
void _uart_putc(char c);
int _uart_write(const char *buf, size_t len);
