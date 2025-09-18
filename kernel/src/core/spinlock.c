#include "spinlock.h"

void spinlock_init(spinlock_t *lock) {
    atomic_flag_clear(lock);
}

void spinlock_aquire(spinlock_t *lock) {
    while (atomic_flag_test_and_set(lock)) {
        __asm__ __volatile__("pause");
    }
}

void spinlock_release(spinlock_t *lock) {
    atomic_flag_clear(lock);
}
