#include "panic.h"
#include "core/stdio.h"
#include "hal/cpu.h"
#include <stdarg.h>

void panic_message(const char *msg, ...)
{
    kprintf("\n\x1b[93m### KERNEL PANIC ###\n");

    va_list args;
    va_start(args, msg);
    kprintf("\x1b[91m");
    kvprintf(msg, args);
    kprintf("\n");
    va_end(args);

    halt_loop();
}

void panic_interrupt(interrupt_frame_t *f)
{
    kprintf("\n\x1b[93m### KERNEL PANIC ###\n");
    if (!f)
        halt_loop();

    kprintf("\x1b[91mInterrupt: %lu   Error: %lx\x1b[0m\n", f->interrupt, f->error);

    kprintf("r15: %016lx  r14: %016lx  r13: %016lx\n", f->r15, f->r14, f->r13);
    kprintf("r12: %016lx  r11: %016lx  r10: %016lx\n", f->r12, f->r11, f->r10);
    kprintf("r9 : %016lx  r8 : %016lx  rbp: %016lx\n", f->r9, f->r8, f->rbp);
    kprintf("rdi: %016lx  rsi: %016lx  rdx: %016lx\n", f->rdi, f->rsi, f->rdx);
    kprintf("rcx: %016lx  rbx: %016lx  rax: %016lx\n", f->rcx, f->rbx, f->rax);

    kprintf("rip: %016lx  rsp: %016lx\n", f->rip, f->rsp);
    kprintf("cs:  %016lx  ss:  %016lx\n", f->cs, f->ss);
    kprintf("rflags: %016lx\n", f->rflags);

    halt_loop();
}
