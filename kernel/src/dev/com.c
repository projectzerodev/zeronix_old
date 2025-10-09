#include "com.h"
#include "drivers/uart16550/uart16550.h"

void _com_init()
{
    _uart16550_init();
}

void _com_write(const char *buf, size_t len)
{
    _uart16550_write(buf, len);
}
