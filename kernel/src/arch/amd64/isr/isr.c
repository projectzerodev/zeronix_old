#include "isr.h"
#include "core/panic.h"
#include "hal/cpu.h"
#include "utils/log.h"

void isr_handler(void *context)
{
    amd64_interrupt_frame_t *registers = context;

    if (registers->interrupt >= 32)
    {
        log_warn("Unhandled interrupt: %i", registers->interrupt);
    }
    else
    {
        panic(registers);
        halt_loop();
    }
}
