#include "hal.h"
#include "boot/boot.h"
#include "dev/tty.h"
#include "hal/cpu.h"
#include "limine.h"
#include <stddef.h>

void hal_early_init()
{
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
    {
        halt_loop();
    }

    _tty_init(&framebuffer_request);
    _tty_write("Welcome to Zeronix\n", sizeof("Welcome to Zeronix\n"));
}
