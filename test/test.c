#include "test.h"
#include "test_framework.h"

#define TEST_POOL_CAPACITY 10

TestStats g_test_stats = {0};

static inline i8
fill_fixture_pool(ListTestFixture * const fixture)
{
	i8 ret = EXIT_FAILURE;
	u64 i = 0;

	GUARD_NULL(fixture);

	for (; i < TEST_POOL_CAPACITY; i++)
	{
		fixture->pool.nodes_start[i].data = (void*)(i + 1);
		fixture->pool.nodes_start[i].next = i < TEST_POOL_CAPACITY - 1 ? &fixture->pool.nodes_start[i + 1] : NULL;
		fixture->pool.nodes_start[i].is_used = TRUE;
	}
	fixture->pool.nodes_end = &fixture->pool.nodes_start[TEST_POOL_CAPACITY - 1];
	fixture->pool.nodes_free = 0;
	fixture->pool.nodes_used = TEST_POOL_CAPACITY;

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}

void
test_lc_pool_init(void)
{
    ListTestFixture fixture = {0};
    TEST_BEGIN("test_lc_pool_init");

    setup_list_fixture(&fixture);
    TEST_DUMP_POOL_STATE(&fixture.pool);
    TEST_ASSERT(dsa_lc_pool_init(&fixture.pool, TEST_POOL_CAPACITY) == EXIT_SUCCESS, "Pool initialization should succeed");
    TEST_DUMP_POOL_STATE(&fixture.pool);
    verify_list_state(&fixture.list, 0, fixture.capacity);
    teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	TEST_DUMP_POOL_STATE(&fixture.pool);
	TEST_ASSERT(dsa_lc_pool_init(NULL, TEST_POOL_CAPACITY) == EXIT_FAILURE, "Pool initialization should fail with NULL pool");
	TEST_DUMP_POOL_STATE(&fixture.pool);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	TEST_DUMP_POOL_STATE(&fixture.pool);
	TEST_ASSERT(dsa_lc_pool_init(&fixture.pool, 0) == EXIT_FAILURE, "Pool initialization should fail with 0 capacity");
	TEST_DUMP_POOL_STATE(&fixture.pool);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	fill_fixture_pool(&fixture);
	TEST_DUMP_POOL_STATE(&fixture.pool);
	TEST_ASSERT(dsa_lc_pool_init(&fixture.pool, TEST_POOL_CAPACITY) == EXIT_SUCCESS, "Pool initialization should succeed");
	TEST_DUMP_POOL_STATE(&fixture.pool);
	teardown_list_fixture(&fixture);

    TEST_END();
}

void
test_lc_init(void)
{
    ListTestFixture fixture = {0};
	TEST_BEGIN("test_lc_init");

	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_init(&fixture.list, (const dsa_LCPool*)&fixture.pool) == EXIT_SUCCESS, "List initialization should succeed with empty pool");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_init(NULL, (const dsa_LCPool*)&fixture.pool) == EXIT_FAILURE, "List initialization should fail with NULL list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_init(&fixture.list, NULL) == EXIT_FAILURE, "List initialization should fail with NULL pool");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	fill_fixture_pool(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_init(&fixture.list, (const dsa_LCPool*)&fixture.pool) == EXIT_SUCCESS, "List initialization should succeed with full pool");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	TEST_END();
}

int
main(void)
{
    TEST_SUITE_BEGIN("List Cursor Tests");
    
    test_lc_pool_init();
	test_lc_init();
    
    TEST_SUITE_END();
    
    return g_test_stats.failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
