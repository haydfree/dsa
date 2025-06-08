#include "test.h"
#include "test_framework.h"

#define TEST_POOL_CAPACITY 10
#ifndef __INT64_MIN__
#define __INT64_MIN__ -9,223,372,036,854,775,808
#endif

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

static inline i8
fill_fixture_list(ListTestFixture * const fixture)
{
	i8 ret = EXIT_FAILURE;

	GUARD_NULL(fixture);
	GUARD_FAILURE(fill_fixture_pool(fixture));

	fixture->list.head = &fixture->pool.nodes_start[0];
	fixture->list.pool = &fixture->pool;

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

void
test_lc_get_tail(void)
{
    ListTestFixture fixture = {0};
	dsa_LCNode *tail = NULL;
	TEST_BEGIN("test_lc_get_tail");

	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_get_tail(&fixture.list, (const dsa_LCNode**)&tail) == EXIT_FAILURE, "Getting tail should fail with empty list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	fill_fixture_list(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_get_tail(&fixture.list, (const dsa_LCNode**)&tail) == EXIT_SUCCESS, "Getting tail should succeed with full list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	fill_fixture_list(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_get_tail(NULL, (const dsa_LCNode**)&tail) == EXIT_FAILURE, "Getting tail should fail with NULL list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	setup_list_fixture(&fixture);
	fill_fixture_list(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_get_tail(&fixture.list, NULL) == EXIT_FAILURE, "Getting tail should fail with NULL tail");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	TEST_END();
}

void
test_lc_push_front(void)
{
    ListTestFixture fixture = {0};
	i64 data = 0;
	TEST_BEGIN("test_lc_push_front");

	// null list
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(NULL, (const void*)&fixture.pool.nodes_start[0]) == EXIT_FAILURE, "Pushing front should fail with NULL list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// empty list
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_SUCCESS, "Pushing front should succeed with empty list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// full list
	setup_list_fixture(&fixture);
	fill_fixture_list(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_FAILURE, "Pushing front should fail with full list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// null data
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, NULL) == EXIT_FAILURE, "Pushing front should fail with NULL data");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// max data
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0xFFFFFFFFFFFFFFFF) == EXIT_SUCCESS, "Pushing front should succeed with max data");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// max *data
	setup_list_fixture(&fixture);
	data = __INT64_MAX__;
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)&data) == EXIT_SUCCESS, "Pushing front should succeed with max *data");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// min data
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_SUCCESS, "Pushing front should succeed with min data");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// min *data
	setup_list_fixture(&fixture);
	data = __INT64_MIN__;
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)&data) == EXIT_SUCCESS, "Pushing front should succeed with min *data");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// null pool
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	fixture.list.pool = NULL;
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_FAILURE, "Pushing front should fail with NULL pool");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// empty pool
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_SUCCESS, "Pushing front should succeed with empty pool");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// full pool
	setup_list_fixture(&fixture);
	fill_fixture_pool(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_FAILURE, "Pushing front should fail with full pool");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// max nodes free
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	fixture.list.pool->nodes_free = __UINT32_MAX__;
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_SUCCESS, "Pushing front should succeed with max nodes free");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// zero nodes free
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	fixture.list.pool->nodes_free = 0;
	TEST_ASSERT(dsa_lc_push_front(&fixture.list, (const void*)0x01) == EXIT_FAILURE, "Pushing front should fail with zero nodes free");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	TEST_END();
}

void
test_lc_push_back(void)
{
    ListTestFixture fixture = {0};
	TEST_BEGIN("test_lc_push_back");

	// null list
	setup_list_fixture(&fixture);
	TEST_DUMP_LIST_STATE(&fixture.list);
	TEST_ASSERT(dsa_lc_push_back(NULL, (const void*)0x01) == EXIT_FAILURE, "Pushing back should fail with NULL list");
	TEST_DUMP_LIST_STATE(&fixture.list);
	teardown_list_fixture(&fixture);

	// empty list
	// full list
	// null data
	// max data
	// max *data
	// min data
	// min *data
	// null pool
	// empty pool
	// full pool
	// max nodes free
	// zero nodes free

	TEST_END();
}

int
main(void)
{
    TEST_SUITE_BEGIN("List Cursor Tests");
    
    test_lc_pool_init();
	test_lc_init();
	test_lc_get_tail();
	test_lc_push_front();
	test_lc_push_back();

    TEST_SUITE_END();
    
    return g_test_stats.failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
