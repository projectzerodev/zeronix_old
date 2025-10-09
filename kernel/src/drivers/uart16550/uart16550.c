#include "uart16550.h"
#include "arch/x86/io.h"
#include "lib/spinlock.h"

// amd64-only uart 16550 implementation

static uint16_t uart_base = UART_COM1_BASE;
static spinlock_t uart_lock;

void _uart16550_init()
{
    spinlock_init(&uart_lock);

    // Disable interrupts
    x86_outb(uart_base + UART_REG_IER, 0x00);

    // Enable DLAB to set baud rate divisor
    x86_outb(uart_base + UART_REG_LCR, UART_LCR_DLAB);

    // Set divisor (115200 baud)
    x86_outb(uart_base + UART_REG_DLL, UART_DIVISOR_LSB);
    x86_outb(uart_base + UART_REG_DLM, UART_DIVISOR_MSB);

    // Disable DLAB + set frame format (8N1)
    x86_outb(uart_base + UART_REG_LCR, UART_LCR_8N1);

    // Enable and clear FIFOs, set trigger to 14 bytes
    x86_outb(uart_base + UART_REG_FCR,
             UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RX | UART_FCR_CLEAR_TX | UART_FCR_TRIGGER_14B);

    // Modem control: enable RTS, DTR, and OUT2
    x86_outb(uart_base + UART_REG_MCR, UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2);

    // Wait until transmitter ready (THRE)
    while ((x86_inb(uart_base + UART_REG_LSR) & UART_LSR_THRE) == 0)
        ;
}

void _uart16550_putc(char c)
{
    spinlock_acquire(&uart_lock);

    // Wait for transmit holding register empty
    while ((x86_inb(uart_base + UART_REG_LSR) & UART_LSR_THRE) == 0)
        ;

    x86_outb(uart_base + UART_REG_THR, (uint8_t)c);

    spinlock_release(&uart_lock);
}

int _uart16550_write(const char *buf, size_t len)
{
    if (!buf)
        return -1;

    for (size_t i = 0; i < len; i++)
        _uart16550_putc(buf[i]);

    return 0;
}
