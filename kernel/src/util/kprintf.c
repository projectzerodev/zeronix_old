#include "kprintf.h"
#include "dev/serial.h"
#include "dev/term.h"
#include "lib/spinlock.h"

#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS     1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS       1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS           0
#define NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS           1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS           1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS          1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS       0
#define NANOPRINTF_SNPRINTF_SAFE_TRIM_STRING_ON_OVERFLOW 1

#define NANOPRINTF_IMPLEMENTATION
#include <nanoprintf.h>

spinlock_t kprintf_lock;

void _kprintf_init()
{
    spinlock_init(&kprintf_lock);
}

int kprintf(const char *fmt, ...)
{
    spinlock_acquire(&kprintf_lock);
    char buf[1024];
    va_list args;

    va_start(args, format);
    int len = npf_vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    if (len < 0 || len >= (int)sizeof(buf))
    {
        return -1;
    }

    _term_write(buf, len);
    _serial_write(buf, len);

    spinlock_release(&kprintf_lock);

    return len;
}

int kvprintf(const char *fmt, va_list args)
{
    char buf[1024];

    int len = npf_vsnprintf(buf, sizeof(buf), fmt, args);

    if (len < 0 || len >= (int)sizeof(buf))
    {
        return -1;
    }

    _term_write(buf, len);
    _serial_write(buf, len);

    return len;
}
