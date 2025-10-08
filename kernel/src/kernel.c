void kstart()
{
    for (;;)
    {
        __asm__ volatile("hlt");
    }
}
