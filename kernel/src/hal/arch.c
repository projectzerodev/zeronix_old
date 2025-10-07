#include "arch.h"
#include "arch/amd64/exceptions/exceptions.h"
#include "arch/amd64/gdt/gdt.h"
#include "arch/amd64/idt/idt.h"
#include "arch/amd64/isr/isr.h"
#include "boot/boot.h"
#include "core/stdio.h"
#include "devices/pic8259/pic8259.h"
#include "devices/pit8253/pit8253.h"
#include "devices/uart16550/uart.h"
#include "graphics/terminal.h"
#include "hal/cpu.h"
#include "limine.h"
#include "utils/log.h"

void arch_early_init()
{
    disable_interrupts();
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        halt_loop();
    }

    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    {
        halt_loop();
    }

    terminal_dimensions_t terminal_dimensions;

    _uart_init();
    _term_init(framebuffer_request.response->framebuffers[0], &terminal_dimensions);
    _stdio_init();
    log_info("Initialized terminal (%i columns, %i rows)", terminal_dimensions.columns,
             terminal_dimensions.rows);
}

void arch_base_init()
{
    amd64_gdt_init();
    log_info("Initialized GDT");
    amd64_idt_init();
    log_info("Initialized IDT");
    amd64_isr_init();
    log_info("Initialized ISR");
    amd64_exceptions_init();
    log_info("Initialized exception handlers");
    pic8259_init();
    log_info("Initialized PIC");
    pit8253_init();
    log_info("Initialized PIT");
    enable_interrupts();
}
