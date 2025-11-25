#pragma once
#include <stdint.h>

/**
 * @brief Outputs data to a port.
 *
 * @param port The port.
 * @param val The data.
 */
static void x86_outb(uint16_t port, uint8_t val)
{
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

/**
 * @brief Inputs data from a port.
 *
 * @param port The port.
 * @return The data.
 */
static uint8_t x86_inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/**
 * @brief Waits for a bit.
 *
 * @warning Don't use this unless you are completely sure its the right choice.
 */
static void x86_iowait()
{
    // Write to an unused port
    x86_outb(0x80, 0);
}
