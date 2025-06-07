#include "test.h"

void
test_lc_init(void)
{
	dsa_LCPool pool = {0};

	assert(dsa_lc_init(&pool) == EXIT_SUCCESS);
	assert(dsa_lc_init(NULL) == EXIT_FAILURE);
	assert(pool.ptr == pool.pool);
	assert(pool.pool[0].data == NULL);
	assert(pool.pool[0].next== NULL);
	assert(sizeof(pool.pool) == LC_POOL_SIZE * sizeof(dsa_LCNode));
}

int
main(void)
{
	test_lc_init();
	printf("All tests passed!\n");
	return 0;
}
