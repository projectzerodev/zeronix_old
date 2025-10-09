#include "pit.h"
#include "../pic/pic.h"
#include "arch/amd64/isr/isr.h"
#include "arch/amd64/pic/pic.h"
#include "util/kprintf.h"
#include "util/log.h"
#include <stdint.h>

static uint64_t ticks;

static void amd64_pit_tick_handler(void *context);

void amd64_pit_init()
{
    amd64_isr_register_handler(32 + 0, amd64_pit_tick_handler);
    amd64_pic_unmask(0);
    log_debug("Initialized PIT");
}

static void amd64_pit_tick_handler(void *context)
{
    (void)context;
    ticks++;
    amd64_pic_send_eoi(0);
    kprintf(".");
}

uint64_t amd64_pit_get_ticks()
{
    return ticks;
}

void amd64_pit_set_ticks(uint64_t t)
{
    ticks = t;
}
