#include "hal.h"
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
    kprintf("Welcome to Zeronix\n");
}
