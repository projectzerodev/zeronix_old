#include "hal/cpu.h"
#include "hal/hal.h"
#include "util/log.h"

void kstart()
{
    hal_early_init();
    hal_base_init();

    log_info("Welcome to Zeronix!");

    halt_loop();
}
