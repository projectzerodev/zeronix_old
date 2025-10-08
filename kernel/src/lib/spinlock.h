#pragma once
#include <stdatomic.h>

/**
 * @brief Type representing a simple spinlock.
 */
typedef atomic_flag spinlock_t;

/**
 * @brief Initialize a spinlock.
 *
 * @param lock Pointer to the spinlock to initialize.
 */
void spinlock_init(spinlock_t *lock);

/**
 * @brief Acquire a spinlock, spinning until it becomes available.
 *
 * @param lock Pointer to the spinlock to acquire.
 */
void spinlock_acquire(spinlock_t *lock);

/**
 * @brief Release a previously acquired spinlock.
 *
 * @param lock Pointer to the spinlock to release.
 */
void spinlock_release(spinlock_t *lock);
