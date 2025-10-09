#include "serial.h"
#include "drivers/uart16550/uart16550.h"

void _serial_init()
{
    _uart16550_init();
}

void _serial_write(const char *buf, size_t len)
{
    _uart16550_write(buf, len);
}
