#include "cpu.h"

void halt()
{
    asm("hlt");
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
    asm("cli");
}

void enable_interrupts()
{
    asm("sti");
}
