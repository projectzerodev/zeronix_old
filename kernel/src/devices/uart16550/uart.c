#include "devices/uart16550/uart.h"
#include "core/spinlock.h"
#include "hal/io.h"

static uint16_t uart_base = UART_COM1_BASE;
static spinlock_t uart_lock;

// https://en.wikipedia.org/wiki/16550_UART
// https://wiki.osdev.org/UART
// https://wiki.osdev.org/Serial_Ports
void uart_init(void)
{
    spinlock_init(&uart_lock);
    // disable all UART interrupts to prevent unsolicited IRQs during setup
    outb(uart_base + UART_IER, 0x00); // IER=0x00: all interrupt sources disabled
    // enable DLAB to access baud rate divisor latche
    outb(uart_base + UART_LCR, 0x80); // LCR=0x80: DLAB=1 (bit 7), no frame changes yet
    // program baud rate divisor for 115200 baud (divisor=1 with 1.8432 MHz clock)
    outb(uart_base + UART_DLL, 0x01); // DLL=0x01: low byte of divisor (LSB=1)
    outb(uart_base + UART_DLM, 0x00); // DLM=0x00: high byte of divisor (MSB=0)
    // disable DLAB and configure frame: 8 data bits, no parity, 1 stop bit (8N1)
    outb(uart_base + UART_LCR,
         0x03); // LCR=0x03: DLAB=0, bits 1-0=11 (8 bits), bits 6-5=00 (1 stop)
    // enable and reset TX/RX FIFOs (16-byte each), set trigger to 14 bytes
    outb(uart_base + UART_FCR,
         0xC7); // FCR=0xC7: bits 7-6=11 (reset FIFOs), bits 2-0=111 (enable + 14-byte trigger)
    // configure modem control lines: Enable RTS/DTR, set OUT2 for potential IRQ routing
    outb(uart_base + UART_MCR,
         0x0B); // MCR=0x0B: bits 3=1 (OUT2), 1=1 (RTS), 0=1 (DTR); no loopback
    // verify transmitter is ready (poll THRE bit in LSR)
    if ((inb(uart_base + UART_LSR) & 0x20) == 0) // LSR & 0x20: Check bit 5 (THRE=1 for empty)
    {
        while (1)
            ;
    }
}

void uart_putchar(char c)
{
    spinlock_acquire(&uart_lock);
    while ((inb(uart_base + UART_LSR) & 0x20) == 0)
        ;
    outb(uart_base + UART_THR, (uint8_t)c);
    spinlock_release(&uart_lock);
}

int uart_puts(const char *s)
{
    if (!s)
        return -1;
    spinlock_acquire(&uart_lock);
    while (*s)
    {
        uart_putchar(*s++);
    }
    uart_putchar('\r');
    uart_putchar('\n');
    spinlock_release(&uart_lock);
    return 0;
}
