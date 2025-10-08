#pragma once

static void halt()
{
    __asm__ volatile("hlt");
}

static void halt_loop()
{
    for (;;)
    {
        halt();
    }
}
