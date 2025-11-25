#pragma once
#include <stdint.h>

/**
 * @brief Initializes the Programmable Interrupt Timer.
 *
 * Registers the IRQ handler for the PIT and unmasks it.
 */
void amd64_pit_init();

/**
 * @brief Get the current amount of ticks.
 *
 * @return The current amount of ticks.
 *
 * @warning Use the HPET for timing (if available).
 */
uint64_t amd64_pit_get_ticks();

/**
 * @brief Set the amount of ticks
 *
 * @param t THe amount of ticks.
 */
void amd64_pit_set_ticks(uint64_t t);
