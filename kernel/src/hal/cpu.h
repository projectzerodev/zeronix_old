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

static void disable_interrupts()
{
    __asm__ volatile("cli");
}

static void enable_interrupts()
{
    __asm__ volatile("sti");
}
