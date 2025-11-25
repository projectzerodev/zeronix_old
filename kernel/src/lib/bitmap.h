#pragma once
#include <stdint.h>

/**
 * @brief Clears the specified bit in a bitmap.
 *
 * @param bitmap Pointer to the bitmap.
 * @param bit The bit to clear.
 */
void bitmap_clear(uint8_t *bitmap, uint64_t bit);

/**
 * @brief Sets the specified bit in a bitmap.
 *
 * @param bitmap Pointer to the bitmap.
 * @param bit The bit to set.
 */
void bitmap_set(uint8_t *bitmap, uint64_t bit);

/**
 * @brief Gets the specified bit in a bitmap.
 *
 * @param bitmap Pointer to the bitmap.
 * @param bit The bit to get.
 */
uint8_t bitmap_get(uint8_t *bitmap, uint64_t bit);
