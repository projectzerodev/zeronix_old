#include "hal.h"
#include "arch/amd64/exceptions/exceptions.h"
#include "arch/amd64/gdt/gdt.h"
#include "arch/amd64/idt/idt.h"
#include "arch/amd64/isr/isr.h"
#include "arch/amd64/paging/paging.h"
#include "arch/amd64/pic/pic.h"
#include "arch/amd64/pit/pit.h"
#include "boot/boot.h"
#include "dev/term.h"
#include "hal/cpu.h"
#include "limine.h"
#include "mem/pmm.h"
#include "mem/vmm.h"
#include "util/kprintf.h"
#include "drivers/ps2/keyboard/keyboard.h"
#include <stddef.h>

void hal_early_init()
{
    disable_interrupts();
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        halt_loop();
    }

    _term_init(&framebuffer_request);
    _kprintf_init();
}

void hal_base_init()
{
    amd64_gdt_init();
    amd64_idt_init();
    amd64_isr_init();
    amd64_exceptions_init();
    amd64_pic_init();
    amd64_pit_init();
    pmm_init(&memmap_request, &hhdm_request);
    amd64_paging_init(&memmap_request);
    vmm_init();
    ps2_keyboard_init();
    enable_interrupts();
}
