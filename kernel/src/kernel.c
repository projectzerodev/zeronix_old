#include "hal/cpu.h"
#include "hal/hal.h"
void kstart()
{
    hal_early_init();
    halt_loop();
}
