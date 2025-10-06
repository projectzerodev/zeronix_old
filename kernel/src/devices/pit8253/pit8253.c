#include "pit8253.h"
#include "arch/amd64/isr/isr.h"
#include "devices/pic8259/pic8259.h"
#include <stdint.h>

static uint64_t ticks;

static void pit8253_tick_handler(void *context);

void pit8253_init()
{
    amd64_isr_register_handler(32 + 0, pit8253_tick_handler);
    pic8259_unmask(0);
}

static void pit8253_tick_handler(void *context)
{
    (void)context;
    ticks++;
    pic8259_send_eoi(0);
}

uint64_t pit8253_get_ticks()
{
    return ticks;
}

void pit8253_set_ticks(uint64_t t)
{
    ticks = t;
}
