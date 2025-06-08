#include "test.h"
#include "test_framework.h"

#define TEST_POOL_CAPACITY 10

TestStats g_test_stats = {0};

void
test_lc_pool_init(void)
{
    ListTestFixture fixture = {0};

    TEST_BEGIN("test_lc_pool_init");
    setup_list_fixture(&fixture);
    TEST_DUMP_POOL_STATE(&fixture.pool);
    TEST_ASSERT(dsa_lc_pool_init(&fixture.pool, TEST_POOL_CAPACITY) == EXIT_SUCCESS, "Pool initialization failed");
    TEST_DUMP_POOL_STATE(&fixture.pool);
    verify_list_state(&fixture.list, 0, fixture.capacity);
    teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	TEST_DUMP_POOL_STATE(&fixture.pool);
	TEST_ASSERT(dsa_lc_pool_init(NULL, TEST_POOL_CAPACITY) == EXIT_FAILURE, "Pool initialization should fail with NULL pool");
	TEST_DUMP_POOL_STATE(&fixture.pool);
	teardown_list_fixture(&fixture);

    TEST_END();
}

void
test_lc_init(void)
{
    ListTestFixture fixture = {0};
}

int
main(void)
{
    TEST_SUITE_BEGIN("List Cursor Tests");
    
    test_lc_pool_init();
    
    TEST_SUITE_END();
    
    return g_test_stats.failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
