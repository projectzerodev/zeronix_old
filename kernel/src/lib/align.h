#pragma once

#define DIV_ROUND_UP(x, y) (((uint64_t)(x) + ((uint64_t)(y) - 1)) / (uint64_t)(y))
#define ALIGN_UP(x, y)     (DIV_ROUND_UP(x, y) * (uint64_t)(y))
#define ALIGN_DOWN(x, y)   (((uint64_t)(x) / (uint64_t)(y)) * (uint64_t)(y))

// Faster then above but only for the power of 2 thingys
#define ROUND_DOWN(n, a) ((n) & ~((a) - 1))
#define ROUND_UP(n, a)   (((n) + (a) - 1) & ~((a) - 1))
