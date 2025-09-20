#include "arch/x86_64/gdt.h"
#include "graphics/terminal.h"
#include "hal/cpu.h"
#include "utils/autoconf.h"
#include "utils/log.h"
#include <flanterm.h>
#include <flanterm_backends/fb.h>
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

__attribute__((used, section(".limine_requests"))) static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests"))) static volatile struct limine_framebuffer_request
    framebuffer_request = {.id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

__attribute__((used, section(".limine_requests_"
                             "start"))) static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end"))) static volatile LIMINE_REQUESTS_END_MARKER;

void kmain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        halt_loop();
    }

    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        halt_loop();
    }

    _term_init(framebuffer_request.response->framebuffers[0]);
    info("Initialized terminal using framebuffer 0");

    amd64_gdt_init();
    info("Loaded GDT");

    info("Welcome to Zeronix!");

    halt_loop();
}
