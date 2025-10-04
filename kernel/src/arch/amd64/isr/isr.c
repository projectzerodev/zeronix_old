#include "isr.h"
#include "core/panic.h"
#include "utils/log.h"

void isr_handler(void *context)
{
    registers_t *registers = context;

    if (registers->interrupt >= 32)
    {
        log_warn("Unhandled interrupt: %i", registers->interrupt);
    }
    else
    {
        panic(registers);
    }
    // halt_loop();
}
