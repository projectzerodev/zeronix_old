#pragma once
#include <stdatomic.h>

typedef atomic_flag spinlock_t;

void spinlock_init(spinlock_t *lock);
void spinlock_aquire(spinlock_t *lock);
void spinlock_release(spinlock_t *lock);
