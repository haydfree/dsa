#include "test.h"

void
test_lc_get_head(void)
{
	dsa_LC lc = {0};	
	dsa_LCNode head = {0}, *tmp = NULL;

	head.index = 69;
	head.used = TRUE;
	lc.head = head.index;

	assert(dsa_lc_get_head(&lc, &tmp) == EXIT_SUCCESS);
	assert(*tmp == head);
}

void
test_lc_get_tail(void)
{
	dsa_LC lc = {0};	
}

void 
test_lc_push_front(void)
{
	dsa_LC lc = {0};	

}

int
main(void)
{
	test_lc_get_head();
	test_lc_get_tail();

	printf("All tests passed!\n");
	return 0;
}
