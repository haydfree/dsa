#include "list_cursor.h"

i8
dsa_lc_get_head(const dsa_LC * const lc, const dsa_LCNode * node)
{
	i8 ret = EXIT_FAILURE;

	GUARD_NULL(lc);
	GUARD_NON_NULL(node);

	node = &lc[lc->head];
	GUARD_NULL(node);

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
	GUARD_FAILURE(dsa_lc_get_head(lc, tmp));	
	GUARD_NULL(tmp);

	node->next = tmp->index;
	lc->head = node->index;

	ret = EXIT_SUCCESS;
cleanup:
	return ret;
}
