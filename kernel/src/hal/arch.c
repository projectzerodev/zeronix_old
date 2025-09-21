#include "arch.h"
#include "arch/amd64/gdt.h"
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
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        halt_loop();
    }

    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    {
        halt_loop();
    }

    _term_init(framebuffer_request.response->framebuffers[0]);
    log_info("Initialized terminal");
}

void arch_base_init()
{
    amd64_gdt_init();
    log_info("Initialized GDT");
}
