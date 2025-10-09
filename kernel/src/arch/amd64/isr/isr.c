#include "isr.h"
#include "arch/amd64/idt/idt.h"
#include "core/panic.h"
#include "hal/cpu.h"
#include "util/log.h"
#include <stddef.h>
#include <stdint.h>

amd64_isr_handler_fn isr_handlers[IDT_MAX_DESCRIPTORS];

void amd64_isr_init()
{
    for (uint16_t v = 0; v < IDT_MAX_DESCRIPTORS; v++)
    {
        amd64_idt_gate_enable(v);
    }

    log_debug("Initialized ISR");
}

void isr_handler(void *context)
{
    amd64_interrupt_frame_t *registers = context;

    if (isr_handlers[registers->interrupt] != NULL)
    {
        isr_handlers[registers->interrupt](registers);
    }
    else if (registers->interrupt >= 32)
    {
        log_warn("Unhandled interrupt: %i", registers->interrupt);
    }
    else
    {
        panic(registers);
        halt_loop();
    }
}

void amd64_isr_register_handler(int interrupt, amd64_isr_handler_fn handler)
{
    isr_handlers[interrupt] = handler;
    amd64_idt_gate_enable(interrupt);
    log_debug("ISR handler registered for interrupt 0x%02X", interrupt);
}
