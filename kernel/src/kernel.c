#include "hal/cpu.h"
#include "hal/hal.h"
#include "test/test.h"
#include "util/log.h"

void kstart()
{
    hal_early_init();
    hal_base_init();

    log_info("Welcome to Zeronix!");

    test_run_all();

    halt_loop();
}

TEST(sample_tests, sample, { result->failed = false; })
