#include "test.h"

#ifdef UNIT_TEST_ENABLED
#include "util/log.h"
#include <stddef.h>
#include <stdint.h>

extern const test_case_t __start_testcases[];
extern const test_case_t __end_testcases[];

void test_run_single(test_result_t *result, const test_case_t *tc)
{
    result->name    = tc->name;
    result->group   = tc->group;
    result->failed  = false;
    result->skipped = false;
    result->reason  = NULL;

    tc->func(result);

    if (result->skipped)
    {
        log_test("\033[94mSKIP\033[0m: %s (%s): %s", result->name, result->group,
                 result->reason ? result->reason : "Reason is Unknown");
        return;
    }
    if (result->failed)
    {
        log_test("\033[91mFAIL\033[0m: %s (%s): %s", result->name, result->group,
                 result->reason ? result->reason : "Reason is Unknown");
        return;
    }
    else
    {
        log_test("\033[92mPASS\033[0m: %s (%s)", result->name, result->group);
        return;
    }
}

void test_run_all()
{
    uint32_t total   = 0;
    uint32_t failed  = 0;
    uint32_t skipped = 0;

    const test_case_t *tc = __start_testcases;
    test_result_t result  = {0};

    for (; tc < __end_testcases; ++tc)
    {
        test_run_single(&result, tc);
        if (result.failed)
        {
            failed++;
        }
        if (result.skipped)
        {
            skipped++;
        }
        total++;
    }

    log_test("Executed %i tests (%i passed, %i failed, %i skipped)", total, total - failed, failed,
             skipped);
}

#endif
