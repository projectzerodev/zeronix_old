#pragma once
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

/**
 * @brief Loads the Interrupt Descriptor Table.
 *
 * Sets all vectors to point to their corresponding entry in the ISR stub table and loads the IDT.
 */
void amd64_idt_init();

/**
 * @brief Sets an entry in the IDT.
 *
 * @param index The index of the entry.
 * @param base The base pointer of the function.
 * @param selector The selector thats used.
 * @param flags Raw IDT entry flags.
 *
 * @note Do not call this directly for registering handlers. Instead use
 * `amd64_isr_register_handler`.
 */
void amd64_idt_set_gate(uint8_t index, void *base, uint16_t selector, uint8_t flags);

/**
 * @brief Enables an interrupt gate.
 *
 * @param interrupt The index of the entry to enable.
 */
void amd64_idt_gate_enable(int interrupt);

/**
 * @brief Disables an interrupt gate.
 *
 * @param interrupt The index of the entry to disable.
 */
void amd64_idt_gate_disable(int interrupt);
