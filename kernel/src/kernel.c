#include "hal/cpu.h"
#include "hal/hal.h"
#include "util/log.h"
#ifdef UNIT_TEST_ENABLED
#include "test/test.h"
#endif

void kstart()
{
    hal_early_init();
    hal_base_init();

    log_info("Welcome to Zeronix!");

#ifdef UNIT_TEST_ENABLED
    test_run_all();
#endif

    halt_loop();
}
