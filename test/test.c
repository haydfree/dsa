#include "test.h"
#include "test_framework.h"

#define TEST_POOL_CAPACITY 10

TestStats g_test_stats = {0};

void
test_lc_push_front_basic(void)
{
    ListTestFixture fixture;
    i32 data1 = 1;
    i32 data2 = 2;

    TEST_BEGIN("test_lc_push_front_basic");
    
    setup_list_fixture(&fixture);
    
    
    TEST_ASSERT(dsa_lc_push_front(&fixture.list, (void*)&data1) == EXIT_SUCCESS,
                "Failed to push first element");
    TEST_ASSERT_NOT_NULL(fixture.list.head, "Head should not be NULL after push");
    verify_node_data(fixture.list.head, &data1);
    TEST_ASSERT_NULL(fixture.list.head->next, "First node should not have next");
    verify_list_state(&fixture.list, 1, fixture.capacity - 1);
    
    TEST_ASSERT(dsa_lc_push_front(&fixture.list, (void*)&data2) == EXIT_SUCCESS,
                "Failed to push second element");
    TEST_ASSERT_NOT_NULL(fixture.list.head, "Head should not be NULL after second push");
    verify_node_data(fixture.list.head, &data2);
    TEST_ASSERT_NOT_NULL(fixture.list.head->next, "Second node should have next");
    verify_node_data(fixture.list.head->next, &data1);
    verify_list_state(&fixture.list, 2, fixture.capacity - 2);
    
    TEST_ASSERT(dsa_lc_push_front(NULL, NULL) == EXIT_FAILURE,
                "Should fail with NULL list");
    TEST_ASSERT(dsa_lc_push_front(&fixture.list, NULL) == EXIT_FAILURE,
                "Should fail with NULL data");
    
    teardown_list_fixture(&fixture);
    TEST_END();
}

void
test_lc_push_front_edge_cases(void)
{
    ListTestFixture fixture;
    i32 data = 0;
    u32 i = 0;

    TEST_BEGIN("test_lc_push_front_edge_cases");
    
    setup_list_fixture(&fixture);
    
    data = 1;
    TEST_INFO("%s", "Testing push to empty list");
    TEST_ASSERT(dsa_lc_push_front(&fixture.list, (void*)&data) == EXIT_SUCCESS,
                "Failed to push to empty list");
    verify_list_state(&fixture.list, 1, fixture.capacity - 1);
    TEST_DUMP_LIST_STATE(&fixture.list);
    
    TEST_LOOP_BEGIN(fill_list, fixture.capacity - 1);
    for (; i < fixture.capacity - 1; i++) 
    {
        TEST_LOOP_ITER(fill_list, i);
        TEST_INFO("Pushing element %u of %u", i + 1, fixture.capacity - 1);
        TEST_DUMP_LIST_STATE(&fixture.list);
        
        TEST_ASSERT(dsa_lc_push_front(&fixture.list, (void*)&data) == EXIT_SUCCESS,
                    "Failed to push to non-full list");
        
        TEST_DUMP_LIST_STATE(&fixture.list);
    }
    TEST_LOOP_END(fill_list);
    
    verify_list_state(&fixture.list, fixture.capacity, 0);
    TEST_INFO("%s", "Testing push to full list (should fail)");
    TEST_DUMP_LIST_STATE(&fixture.list);
    
    TEST_ASSERT(dsa_lc_push_front(&fixture.list, (void*)&data) == EXIT_FAILURE,
                "Should fail to push to full list");
    
    teardown_list_fixture(&fixture);
    TEST_END();
}

int
main(void)
{
    TEST_SUITE_BEGIN("List Cursor Tests");
    
    test_lc_push_front_basic();
    test_lc_push_front_edge_cases();
    
    TEST_SUITE_END();
    
    return g_test_stats.failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
