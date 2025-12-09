#pragma once

/**
 * @brief Architeture-generic function for halting the system.
 */
void halt();

/**
 * @brief Runs `halt` forever.
 *
 * Typically used when waiting for a new interrupt.
 */
void halt_loop();

/**
 * @brief Architeture-generic function for disabling interrupts.
 */
void disable_interrupts();

/**
 * @brief Architeture-generic function for enabling interrupts.
 */
void enable_interrupts();
