#include "hal/cpu.h"
#include "hal/hal.h"
#include "util/log.h"
#include <stdint.h>

uint64_t kernel_stack_top = 0;

void kstart()
{
    __asm__ volatile("movq %%rsp, %0" : "=r"(kernel_stack_top));

    hal_early_init();
    hal_base_init();

    log_info("Welcome to Zeronix!");

    halt_loop();
}
