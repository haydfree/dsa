#ifndef LIST_CURSOR_H  
#define LIST_CURSOR_H 

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

#define MAX_LCNODES 256

typedef struct dsa_LCNode
{
	void *data;
	i32 index, next;
	b8 used;
} dsa_LCNode;

typedef struct dsa_LC
{
	struct dsa_LCNode nodes[MAX_LCNODES];
	i32 head;
} dsa_LC;

i8 dsa_lc_push_front(dsa_LC * const lc, dsa_LCNode * const node);
i8 dsa_lc_push_back(dsa_LC * const lc, dsa_LCNode * const node);
i8 dsa_lc_pop_front(dsa_LC * const lc);
i8 dsa_lc_pop_back(dsa_LC * const lc);
i8 dsa_lc_get_next(const dsa_LC * const lc, const dsa_LCNode * const node, const dsa_LCNode *dst);
i8 dsa_lc_get_prev(const dsa_LC * const lc, const dsa_LCNode * const node, const dsa_LCNode *dst);
i8 dsa_lc_get_head(const dsa_LC * const lc, const dsa_LCNode *dst);
i8 dsa_lc_clear(dsa_LC * const lc);

#endif
