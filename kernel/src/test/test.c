#include "test.h"
#include "util/kprintf.h"

#ifdef UNIT_TEST_ENABLED
#include "util/log.h"
#include <stddef.h>
#include <stdint.h>

extern const test_case_t __start_testcases[];
extern const test_case_t __end_testcases[];

void test_run_single(test_result_t *result, const test_case_t *tc)
{
    result->name   = tc->name;
    result->group  = tc->group;
    result->failed = false;
    result->reason = NULL;

    kprintf("%s:%s ... ", tc->group, tc->name);
    tc->func(result);
    kprintf(" %s\n", result->failed ? "FAILED" : "ok");
}

void test_run_all()
{
    uint32_t total = (uint32_t)(__end_testcases - __start_testcases);
    kprintf("running %u %s\n", total, total > 1 ? "tests" : "test");

    uint32_t failed = 0;

    const test_case_t *tc = __start_testcases;
    test_result_t result  = {0};

    for (; tc < __end_testcases; ++tc)
    {
        test_run_single(&result, tc);
        if (result.failed)
        {
            failed++;
        }
    }

    kprintf("test result: %s. %u passed; %u failed", failed ? "FAILED" : "ok", total - failed,
            failed);
}

#endif
