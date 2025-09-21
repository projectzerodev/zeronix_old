#pragma once

#define asm(x) __asm__ __volatile__(x)

void halt();
void halt_loop();
void disable_interrupts();
void enable_interrupts();
