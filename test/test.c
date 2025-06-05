#include "test.h"

void 
test_lc_push_front(void)
{
	dsa_LC lc = {0};	
	dsa_LCNode head = {0}, tmp = {0};
	head.next = -1;
	tmp.next = -1;
	lc.head = -1;

	assert(dsa_lc_push_front(&lc, &head) == EXIT_SUCCESS);
	assert(head.next == -1);
	assert(lc.head == head.index);
	assert(dsa_lc_push_front(&lc, &tmp) == EXIT_SUCCESS);
	assert(tmp.next == head.index);
	assert(lc.head == tmp.index);
}

int
main(void)
{
	test_lc_push_front();

	printf("All tests passed!\n");
	return 0;
}
