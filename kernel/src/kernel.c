#include "hal/arch.h"
#include "hal/cpu.h"
#include "stddef.h"
#include "utils/log.h"

void kstart()
{
    arch_early_init();
    arch_base_init();

    log_info("Welcome to Zeronix");
    log_info("Kernel built on %s", __DATE__);

    int *ptr = NULL;
    *ptr     = 1234;

    halt_loop();
}
