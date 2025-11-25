#pragma once
#include <stdint.h>

/**
 * @brief Initializes the Programmable Interrupt Controller.
 *
 * @note This function leaves all IRQs masked.
 */
void amd64_pic_init();

/**
 * @brief Sets the entire PIC mask.
 *
 * @param new_mask The new mask.
 */
void amd64_pic_set_mask(uint16_t new_mask);

/**
 * @brief Sends an end-of-interrupt signal.
 *
 * @param irq The IRQ to end.
 */
void amd64_pic_send_eoi(int irq);

/**
 * @brief Masks the specified IRQ.
 *
 * @param irq The IRQ to mask.
 */
void amd64_pic_mask(int irq);

/**
 * @brief Unmasks the specified IRQ.
 *
 * @param irq The IRQ to unmask.
 */
void amd64_pic_unmask(int irq);
