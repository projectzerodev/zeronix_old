#include "isr.h"
#include "core/stdio.h"

void isr_handler(void *context)
{
    (void)context;
    kprintf(".");
    // halt_loop();
}
