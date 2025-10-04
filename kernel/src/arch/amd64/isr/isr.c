#include "isr.h"
#include "core/panic.h"
#include "hal/cpu.h"
#include "utils/log.h"

void isr_handler(void *context)
{
    interrupt_frame_t *registers = context;

    if (registers->interrupt >= 32)
    {
        log_warn("Unhandled interrupt: %i", registers->interrupt);
    }
    else
    {
        panic("Unhandled Exception: 0x%x", registers->interrupt);
        halt_loop();
    }
}
