#ifndef LIST_CURSOR_H  
#define LIST_CURSOR_H 

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

typedef struct dsa_LCNode {
	void *data;
	struct dsa_LCNode *next;
	b8 is_used;
} dsa_LCNode;

typedef struct dsa_LCPool {
	u32 nodes_used, nodes_free, capacity;
	dsa_LCNode *nodes_start, *nodes_end;
} dsa_LCPool;

typedef struct dsa_LC {
	dsa_LCNode *head;
	dsa_LCPool *pool;
} dsa_LC;

i8 dsa_lc_pool_init(dsa_LCPool * const pool, const u32 capacity);
i8 dsa_lc_init(dsa_LC * const list, dsa_LCPool * const pool);

i8 dsa_lc_pool_find_free_node(const dsa_LCPool * const pool, const dsa_LCNode **dst);
i8 dsa_lc_remove(dsa_LC * const list, dsa_LCNode * const node);
i8 dsa_lc_find(const dsa_LC * const list, const void * const data, const dsa_LCNode **dst);

i8 dsa_lc_push_front(dsa_LC * const list, void * const data);
i8 dsa_lc_push_back(dsa_LC * const list, void * const data);
i8 dsa_lc_pop_front(dsa_LC * const list, const void **data);

#endif
