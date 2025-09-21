#include "hal/arch.h"
#include "hal/cpu.h"
#include "utils/log.h"

void kstart()
{
    arch_early_init();
    arch_base_init();

    log_info("Welcome to Zeronix");
    log_info("Kernel built on %s", __DATE__);

    halt_loop();
}
