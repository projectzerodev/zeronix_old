#include "arch.h"
#include "arch/amd64/exceptions/exceptions.h"
#include "arch/amd64/gdt/gdt.h"
#include "arch/amd64/idt/idt.h"
#include "arch/amd64/isr/isr.h"
#include "core/stdio.h"
#include "devices/uart16550/uart.h"
#include "graphics/terminal.h"
#include "hal/cpu.h"
#include "limine.h"
#include "utils/log.h"

__attribute__((used, section(".limine_requests"))) static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests"))) volatile struct limine_framebuffer_request
    framebuffer_request = {.id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

__attribute__((used, section(".limine_requests_"
                             "start"))) static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end"))) static volatile LIMINE_REQUESTS_END_MARKER;

void arch_early_init()
{
    asm("cli");
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        halt_loop();
    }

    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    {
        halt_loop();
    }

    _uart_init();
    terminal_dimensions_t term_dimensions =
        _term_init(framebuffer_request.response->framebuffers[0]);
    _stdio_init();
    log_info("Initialized terminal (%i columns, %i rows)", term_dimensions.columns,
             term_dimensions.rows);
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
    log_info("Registered Exception Handlers");

    volatile int *ptr = NULL;
    *ptr              = 1234;
}
