#include "cpu.h"

void halt()
{
    __asm__ volatile("hlt");
}

void halt_loop()
{
    for (;;)
    {
        halt();
    }
}

void disable_interrupts()
{
    __asm__ volatile("cli");
}

void enable_interrupts()
{
    __asm__ volatile("sti");
}
