#include "test.h"

#define TEST_POOL_CAPACITY 10

void 
test_lc_pool_init(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	const u32 capacity = TEST_POOL_CAPACITY;

	pool.nodes = nodes;

	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(pool.nodes_used == 0);
	assert(pool.nodes_free == capacity);
	assert(pool.capacity == capacity);

	assert(dsa_lc_pool_init(NULL, 0) == EXIT_FAILURE);
}

void
test_lc_init(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	dsa_LC list = {0};
	const u32 capacity = TEST_POOL_CAPACITY;

	pool.nodes = nodes;

	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(list.head == NULL);
	assert(list.pool == &pool);

	assert(dsa_lc_init(NULL, NULL) == EXIT_FAILURE);
}

void
test_lc_push_front(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	dsa_LC list = {0};
	const u32 capacity = TEST_POOL_CAPACITY;
	i32 data = 0;

	pool.nodes = nodes;

	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(dsa_lc_push_front(&list, (void*)&data) == EXIT_SUCCESS);
	assert(list.head != NULL);
	assert(list.head->data == (void*)&data);
	assert(list.head->next == NULL);
	assert(list.pool->capacity == capacity);
	assert(list.pool->nodes_free == capacity - 1);
	assert(list.pool->nodes_used == 1);
	assert(list.pool->nodes == &nodes[1]);
	assert(list.pool->nodes-1 == &nodes[0]);

	assert(dsa_lc_push_front(&list, (void*)&data) == EXIT_SUCCESS);
	assert(list.head->next != NULL);
	assert(list.head->next->data == (void*)&data);
	assert(list.head->next->next == NULL);
	assert(list.pool->capacity == capacity);
	assert(list.pool->nodes_free == capacity - 2);
	assert(list.pool->nodes_used == 2);

	assert(dsa_lc_push_front(NULL, NULL) == EXIT_FAILURE);
}

void
test_lc_push_back(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	dsa_LC list = {0};
	const u32 capacity = TEST_POOL_CAPACITY;
	i32 data = 0;

	pool.nodes = nodes;

	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(dsa_lc_push_back(&list, (void*)&data) == EXIT_SUCCESS);
	assert(list.head != NULL);
	assert(list.head->data == (void*)&data);
	assert(list.head->next == NULL);
	assert(list.pool->capacity == capacity);
	assert(list.pool->nodes_free == capacity - 1);
	assert(list.pool->nodes_used == 1);
	assert(list.pool->nodes == &nodes[1]);
	assert(list.pool->nodes-1 == &nodes[0]);

	assert(dsa_lc_push_back(&list, (void*)&data) == EXIT_SUCCESS);
	assert(list.head->next != NULL);
	assert(list.head->next->data == (void*)&data);
	assert(list.head->next->next == NULL);
	assert(list.pool->capacity == capacity);
	assert(list.pool->nodes_free == capacity - 2);
	assert(list.pool->nodes_used == 2);

	assert(dsa_lc_push_back(NULL, NULL) == EXIT_FAILURE);
}

void
test_lc_pop_front(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	dsa_LC list = {0};
	const u32 capacity = TEST_POOL_CAPACITY;
	i32 data = 0;
	i32 *p_data = NULL;

	pool.nodes = nodes;
	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(dsa_lc_push_front(&list, (void*)&data) == EXIT_SUCCESS);

	assert(dsa_lc_pop_front(&list, (const void**)&p_data) == EXIT_SUCCESS);
	assert(list.head->data == NULL);
	assert(list.pool->nodes_free == capacity);
	assert(list.pool->nodes_used == 0);
}

void
test_lc_find(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	dsa_LC list = {0};
	const u32 capacity = TEST_POOL_CAPACITY;
	i32 data = 0;
	dsa_LCNode *p_node = NULL;

	pool.nodes = nodes;
	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(dsa_lc_push_front(&list, (void*)&data) == EXIT_SUCCESS);

	assert(dsa_lc_find(&list, (void*)&data, (const dsa_LCNode**)&p_node) == EXIT_SUCCESS);
	assert(p_node->data == (void*)&data);
	assert(p_node->next == NULL);
}

void
test_lc_remove(void)
{
	dsa_LCNode nodes[TEST_POOL_CAPACITY] = {0};
	dsa_LCPool pool = {0};
	dsa_LC list = {0};
	const u32 capacity = TEST_POOL_CAPACITY;
	i32 data = 0;

	pool.nodes = nodes;
	assert(dsa_lc_pool_init(&pool, capacity) == EXIT_SUCCESS);
	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(dsa_lc_push_front(&list, (void*)&data) == EXIT_SUCCESS);
	assert(list.head->data == (void*)&data);
	assert(list.head->next == NULL);
	assert(list.pool->nodes_free == capacity - 1);
	assert(list.pool->nodes_used == 1);
	assert(list.pool->nodes == &nodes[1]);
	assert(list.pool->nodes-1 == &nodes[0]);

	assert(dsa_lc_remove(&list, (void*)&data) == EXIT_SUCCESS);
	assert(list.head->data == NULL);
	assert(list.pool->nodes_free == capacity);
	assert(list.pool->nodes_used == 0);
}


int
main(void)
{
	test_lc_pool_init();
	test_lc_init();
	test_lc_push_front();
	test_lc_push_back();
	test_lc_find();

	printf("All tests passed!\n");
	return 0;
}
