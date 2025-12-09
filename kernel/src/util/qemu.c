#include "qemu.h"
#include "arch/x86/io.h"
#include <stdint.h>

void qemu_exit(uint8_t code)
{
    x86_outb(0xf4, code);
}
