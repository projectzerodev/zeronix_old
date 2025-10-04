#include "panic.h"
#include "arch/amd64/isr/isr.h"
#include "hal/cpu.h"
#include "utils/log.h"

void panic(registers_t *registers)
{
    log_fatal("Panic!");
    halt_loop();
}
