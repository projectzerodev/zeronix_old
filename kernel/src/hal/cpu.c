#include "cpu.h"

void halt()
{
    __asm__ __volatile__("hlt");
}

void halt_loop()
{
    for (;;)
    {
        halt();
    }
}
