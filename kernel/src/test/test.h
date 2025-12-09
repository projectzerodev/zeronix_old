#pragma once
#include <stdint.h>

#ifdef UNIT_TEST_ENABLED

#define TEST_SECTION __attribute__((section(".testcases"), used))

/**
 * @brief Representing a test result
 */
typedef struct
{
    const char *name;
    const char *group;
    bool failed;

    const char *reason;
    const char *file;
    uint32_t line;
} test_result_t;

/**
 * @brief Representing a test function
 */
typedef void (*test_func_t)(test_result_t *result);

/**
 * @brief Representing a test case.
 */
typedef struct
{
    const char *name;
    const char *group;
    test_func_t func;
} test_case_t;

/**
 * @brief Macro for easily defining a test case.
 */
#define TEST(GROUP, NAME, BODY)                                                                    \
    static void __test_func_##NAME(test_result_t *result);                                         \
    static const test_case_t __test_case_##NAME TEST_SECTION = {                                   \
        .name = #NAME, .group = #GROUP, .func = __test_func_##NAME};                               \
    static void __test_func_##NAME(test_result_t *result) BODY

/**
 * @brief Runs every test (if `UNIT_TEST_ENABLED` is defined).
 */
void test_run_all();

// === Basic Testing Things ===

#define ASSERT_TRUE(expr)                                                                          \
    do                                                                                             \
    {                                                                                              \
        if (!(expr))                                                                               \
        {                                                                                          \
            (result)->failed = true;                                                               \
            (result)->file   = __FILE__;                                                           \
            (result)->line   = __LINE__;                                                           \
            return;                                                                                \
        }                                                                                          \
    } while (0)

#define ASSERT_EQ(a, b) ASSERT_TRUE(((a) == (b)))
#define ASSERT_NE(a, b) ASSERT_TRUE(((a) != (b)))

#else /* UNIT_TEST_ENABLED is not defined */

#define TEST(GROUP, NAME, BODY)

#define test_run_all(...)                                                                          \
    do                                                                                             \
    {                                                                                              \
    } while (0)

#endif /* UNIT_TEST_ENABLED */
