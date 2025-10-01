#include "isr.h"
#include "core/stdio.h"
#include "hal/cpu.h"

void isr_handler(void *context)
{
    (void)context;
    kprintf("Interrupt");
    halt_loop();
}
