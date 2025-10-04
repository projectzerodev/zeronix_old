#include "panic.h"
#include "core/stdio.h"
#include "hal/cpu.h"
#include <stdarg.h>

void panic(const char *msg, ...)
{
    kprintf("\n\x1b[93m### KERNEL PANIC ###\n");

    va_list args;
    va_start(args, msg);
    kprintf("\x1b[91m");
    kvprintf(msg, args);
    kprintf("\n");

    va_end(args);

    halt_loop();
}
