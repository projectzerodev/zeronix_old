#include "hal.h"
#include "arch/amd64/exceptions/exceptions.h"
#include "arch/amd64/gdt/gdt.h"
#include "arch/amd64/idt/idt.h"
#include "arch/amd64/isr/isr.h"
#include "boot/boot.h"
#include "dev/tty.h"
#include "hal/cpu.h"
#include "limine.h"
#include "util/kprintf.h"
#include <stddef.h>

void hal_early_init()
{
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        halt_loop();
    }

    _tty_init(&framebuffer_request);
    _kprintf_init();
}

void hal_base_init()
{
    amd64_gdt_init();
    amd64_idt_init();
    amd64_isr_init();
    amd64_exceptions_init();
}
