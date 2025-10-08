#pragma once
#include "limine.h"
#include <stddef.h>

/**
 * @brief Sets up the terminal using the given framebuffer.
 *
 * This function initializes the terminal so text can be drawn to the screen
 * through the framebuffer provided.
 *
 * @param framebuffer_request Pointer to the Limine framebuffer request.
 *
 * @warning if `framebuffer_request` is NULL or it doesn't contain any
 *          framebuffers the system will halt.
 */
void _tty_init(volatile struct limine_framebuffer_request *framebuffer_request);

/**
 * @brief Writes data to the terminal.
 *
 * This function sends the contents of the buffer `buf` to the terminal
 * for display. Only the first `len` bytes of the buffer are written.
 *
 * @param buf Pointer to the buffer containing the data to write.
 * @param len Number of bytes from `buf` to write to the terminal.
 *
 * @warning Behavior is undefined if `buf` is NULL or `len` exceeds
 *          the actual buffer size.
 *
 * @warning Behavior is undefined if the terminal hasn't been
 *          initialized using `_tty_init`
 */
void _tty_write(const char *buf, size_t len);
