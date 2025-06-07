#include "test.h"

void
test_lc_pool_init(void)
{
	dsa_LCPool pool = {0};
	assert(dsa_lc_pool_init(&pool) == EXIT_SUCCESS);
	assert(dsa_lc_pool_init(NULL) == EXIT_FAILURE);
	assert(pool.ptr == pool.pool);
}

void
test_lc_init(void)
{
	dsa_LCPool pool = {0};
	dsa_LC list = {0};

	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(dsa_lc_init(NULL, NULL) == EXIT_FAILURE);
	assert(pool.ptr == pool.pool);
	assert(pool.pool[0].data == NULL);
	assert(pool.pool[0].next== NULL);
	assert(sizeof(pool.pool) == LC_POOL_SIZE * sizeof(dsa_LCNode));
}

void
test_lc_push_front(void)
{
	dsa_LCPool pool = {0};
	dsa_LC list = {0};

	assert(dsa_lc_init(&list, &pool) == EXIT_SUCCESS);
	assert(pool.ptr == pool.pool);
	assert(pool.pool[0].data == NULL);
	assert(pool.pool[0].next== NULL);
	assert(dsa_lc_push_front(&list, (void *)1) == EXIT_SUCCESS);
	assert(pool.ptr == pool.pool + 1);
	assert(pool.pool[0].data == (void *)1);
	assert(pool.pool[0].next == NULL);
}

int
main(void)
{
	test_lc_init();
	test_lc_push_front();
	printf("All tests passed!\n");
	return 0;
}
