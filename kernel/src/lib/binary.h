#pragma once

#define FLAG_SET(x, flag)   x |= (flag)
#define FLAG_UNSET(x, flag) x &= ~(flag)

#define BIT_GET(x, bit) (((x) >> (bit)) & 1)
