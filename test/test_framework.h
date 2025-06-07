#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "list_cursor.h"

typedef struct ListTestFixture 
{
    dsa_LCNode nodes[10]; 
    dsa_LCPool pool;
    dsa_LC list;
    u32 capacity;
} ListTestFixture;

typedef struct TestStats 
{
    u32 total_tests;
    u32 passed_tests;
    u32 failed_tests;
    char current_test[256];
    ListTestFixture *current_fixture;
} TestStats;

extern TestStats g_test_stats;

/* Debug Levels - Control how much debug output you want */
#define TEST_DEBUG_NONE  0  /* No debug output */
#define TEST_DEBUG_ERROR 1  /* Only errors */
#define TEST_DEBUG_INFO  2  /* Errors + important info */
#define TEST_DEBUG_TRACE 3  /* Everything, including loop iterations */

#define TEST_DEBUG_LEVEL TEST_DEBUG_TRACE

#define TEST_DEBUG_PRINT(level, fmt, ...) do { \
    if (level <= TEST_DEBUG_LEVEL) { \
        printf("[%s:%d] " fmt "\n", __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__); \
    } \
} while(0)

#define TEST_ERROR(fmt, ...) TEST_DEBUG_PRINT(TEST_DEBUG_ERROR, "ERROR: " fmt __VA_OPT__(,) __VA_ARGS__)
#define TEST_INFO(fmt, ...)  TEST_DEBUG_PRINT(TEST_DEBUG_INFO,  "INFO: " fmt __VA_OPT__(,) __VA_ARGS__)
#define TEST_TRACE(fmt, ...) TEST_DEBUG_PRINT(TEST_DEBUG_TRACE, "TRACE: " fmt __VA_OPT__(,) __VA_ARGS__)

#define TEST_LOOP_BEGIN(iter_name, max_iter) \
do { \
    TEST_INFO("%s", "Starting loop"); \
} while(0)

#define TEST_LOOP_ITER(iter_name, current) \
do { \
    TEST_TRACE("%s", "Loop iteration"); \
} while(0)

#define TEST_LOOP_END(iter_name) \
do { \
    TEST_INFO("%s", "Completed loop"); \
} while(0)

#define TEST_DUMP_LIST_STATE(list) \
do { \
    TEST_INFO("%s", "List state:"); \
    TEST_INFO("%s", "  Head: "); \
    TEST_INFO("%s", "  Pool: "); \
    if ((list)->pool) { \
        TEST_INFO("%s", "  Pool capacity: "); \
        TEST_INFO("%s", "  Pool used: "); \
        TEST_INFO("%s", "  Pool free: "); \
    } \
} while(0)

#define TEST_DUMP_NODE(node) \
do { \
    TEST_INFO("%s", "Node state:"); \
    TEST_INFO("%s", "  Address: "); \
    TEST_INFO("%s", "  Data: "); \
    TEST_INFO("%s", "  Next: "); \
} while(0)

#define TEST_BEGIN(name) \
do { \
    strncpy(g_test_stats.current_test, name, sizeof(g_test_stats.current_test) - 1); \
    g_test_stats.total_tests++; \
    printf("Running test: %s\n", name); \
} while(0)

#define TEST_END() \
do { \
    printf("Test %s: PASSED\n", g_test_stats.current_test); \
    g_test_stats.passed_tests++; \
} while(0)

#define TEST_FAIL(msg) \
do { \
    printf("Test %s: FAILED - %s\n", g_test_stats.current_test, msg); \
    g_test_stats.failed_tests++; \
    return; \
} while(0)

#define TEST_ASSERT(cond, msg) \
do { \
    if (!(cond)) { \
        TEST_ERROR("%s", "Assertion failed"); \
        if (g_test_stats.current_fixture) { \
            TEST_DUMP_LIST_STATE(&g_test_stats.current_fixture->list); \
        } \
        TEST_FAIL(msg); \
    } \
} while(0)

#define TEST_ASSERT_EQ(actual, expected, msg) \
do { \
    if ((actual) != (expected)) { \
        TEST_ERROR("%s", "Assertion failed - values not equal"); \
        TEST_FAIL(msg); \
    } \
} while(0)

#define TEST_ASSERT_NULL(ptr, msg) \
do { \
    if ((ptr) != NULL) { \
        TEST_ERROR("%s", "Assertion failed - expected NULL"); \
        TEST_FAIL(msg); \
    } \
} while(0)

#define TEST_ASSERT_NOT_NULL(ptr, msg) \
do { \
    if ((ptr) == NULL) { \
        TEST_ERROR("%s", "Assertion failed - expected non-NULL"); \
        TEST_FAIL(msg); \
    } \
} while(0)

#define TEST_SUITE_BEGIN(name) \
do { \
    printf("\n=== Test Suite: %s ===\n", name); \
} while(0)

#define TEST_SUITE_END() \
do { \
    printf("\nTest Suite Summary:\n"); \
    printf("Total Tests: %u\n", g_test_stats.total_tests); \
    printf("Passed: %u\n", g_test_stats.passed_tests); \
    printf("Failed: %u\n", g_test_stats.failed_tests); \
} while(0)

static inline void
setup_list_fixture(ListTestFixture* fixture)
{
    ZERO_MEM(fixture, sizeof(*fixture));
    fixture->capacity = sizeof(fixture->nodes) / sizeof(fixture->nodes[0]);
    fixture->pool.nodes = fixture->nodes;
    g_test_stats.current_fixture = fixture;
    TEST_INFO("%s", "Setting up list fixture");
    TEST_ASSERT(dsa_lc_pool_init(&fixture->pool, fixture->capacity) == EXIT_SUCCESS, 
                "Failed to initialize pool");
    TEST_ASSERT(dsa_lc_init(&fixture->list, &fixture->pool) == EXIT_SUCCESS,
                "Failed to initialize list");
}

static inline void
teardown_list_fixture(ListTestFixture* fixture)
{
    TEST_INFO("%s", "Tearing down list fixture");
    TEST_DUMP_LIST_STATE(&fixture->list);
    g_test_stats.current_fixture = NULL;
}

static inline void
verify_list_state(const dsa_LC* list, u32 expected_used, u32 expected_free)
{
    TEST_ASSERT(list->pool->nodes_used == expected_used, 
                "Incorrect number of used nodes");
    TEST_ASSERT(list->pool->nodes_free == expected_free,
                "Incorrect number of free nodes");
}

static inline void
verify_node_data(const dsa_LCNode* node, const void* expected_data)
{
    TEST_ASSERT_NOT_NULL(node, "Node is NULL");
    TEST_ASSERT_EQ(node->data, expected_data, "Node data mismatch");
}

#endif
