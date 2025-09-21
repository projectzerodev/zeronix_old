#include "devices/uart16650/uart.h"
#include "hal/io.h"
#include "core/spinlock.h"

static uint16_t uart_base = UART_COM1_BASE;
static spinlock_t uart_lock;

void uart_init(void)
{
    spinlock_init(&uart_lock);

    outb(uart_base + UART_IER, 0x00);
    outb(uart_base + UART_LCR, 0x80);
    outb(uart_base + UART_DLL, 0x01);
    outb(uart_base + UART_DLM, 0x00);
    outb(uart_base + UART_LCR, 0x03);
    outb(uart_base + UART_FCR, 0xC7);
    outb(uart_base + UART_MCR, 0x0B);
    if ((inb(uart_base + UART_LSR) & 0x20) == 0) 
    {
        while (1);
    }
}

void uart_putchar(char c)
{
    spinlock_aquire(&uart_lock);
    while ((inb(uart_base + UART_LSR) & 0x20) == 0);
    outb(uart_base + UART_THR, (uint8_t)c);
    spinlock_release(&uart_lock);
}

int uart_puts(const char *s)
{
    if (!s) return -1;
    spinlock_aquire(&uart_lock);
    while (*s) 
    {
        uart_putchar(*s++);
    }
    uart_putchar('\r');
    uart_putchar('\n');
    spinlock_release(&uart_lock);
    return 0;
}