#pragma once
#include <stdint.h>

#define TEST_SECTION __attribute__((section(".testcases"), used))

typedef struct
{
    const char *name;
    const char *group;
    bool failed;
    bool skipped;

    const char *reason;
    const char *file;
    uint32_t line;
} test_result_t;

typedef void (*test_func_t)(test_result_t *result);

typedef struct
{
    const char *name;
    const char *group;
    test_func_t func;
} test_case_t;

#define TEST(GROUP, NAME, BODY)                                                                    \
    static void __test_func_##NAME(test_result_t *result);                                         \
    static const test_case_t __test_case_##NAME TEST_SECTION = {                                   \
        .name = #NAME, .group = #GROUP, .func = __test_func_##NAME};                               \
    static void __test_func_##NAME(test_result_t *result) BODY

void test_run_all();
