#include "list_cursor.h"

i8
dsa_lc_get_head(const dsa_LC * const lc, const dsa_LCNode **dst)
{
	i8 ret = EXIT_FAILURE;

	GUARD_NULL(lc);
	GUARD_NON_NULL(*dst);

	*dst = &(lc->pool[lc->head]);
	GUARD_NULL(*dst);

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}

i8 
dsa_lc_get_tail(const dsa_LC * const lc, const dsa_LCNode **dst)
{	
	i8 ret = EXIT_FAILURE;
	const dsa_LCNode *tmp = NULL, * const pool = lc->pool;

	GUARD_NULL(lc);
	GUARD_NON_NULL(*dst);
	GUARD_FAILURE(dsa_lc_get_head(lc, &tmp));
	GUARD_NULL(tmp);

	while (tmp->next->used) { tmp = tmp->next; }
	*dst = tmp;

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}

i8
dsa_lc_push_front(dsa_LC * const lc, dsa_LCNode * const node)
{
	i8 ret = EXIT_FAILURE;	
	const dsa_LCNode *tmp = NULL;

	GUARD_NULL(lc);
	GUARD_NULL(node);
	GUARD_FAILURE(dsa_lc_get_head(lc, &tmp));	
	GUARD_NULL(tmp);

	node->next = tmp->index;
	lc->head = node->index;

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}

i8
dsa_lc_print(const dsa_LC * const lc)
{
	i8 ret = EXIT_FAILURE;
	u32 idx = 0, size = 0;
	
	size = lc->size;
	for (; idx < size; idx++)
	{
		GUARD_NON_POS(printf("node: data: %p, index: %d, next: %d, used: %d\n", lc->pool[idx].data, lc->pool[idx].index, lc->pool[idx].next, (i8)lc->pool[idx].used));
	}
	printf("head: %d\n", lc->head);
	printf("size: %d\n", lc->size);

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}
