#ifndef LIST_CURSOR_H  
#define LIST_CURSOR_H 

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"

#define LC_POOL_SIZE 256

typedef struct dsa_LCNode
{
	void *data;
	struct dsa_LCNode *next;
} dsa_LCNode;

typedef struct dsa_LCPool
{
	dsa_LCNode pool[LC_POOL_SIZE];
	dsa_LCNode *ptr;
} dsa_LCPool;

typedef struct dsa_LC
{
	dsa_LCNode *head;
	dsa_LCPool *pool; 
} dsa_LC;

i8 dsa_lc_pool_init(dsa_LCPool * const pool);
i8 dsa_lc_init(dsa_LC * const list, dsa_LCPool * const pool);
i8 dsa_lc_push_front(dsa_LC * const list, void * const data);
i8 dsa_lc_push_back(dsa_LC * const list, void * const data);
i8 dsa_lc_pop_front(dsa_LC * const list, void ** const data);
i8 dsa_lc_pop_back(dsa_LC * const list, void ** const data);
i8 dsa_lc_peek_front(dsa_LC * const list, void ** const data);
i8 dsa_lc_peek_back(dsa_LC * const list, void ** const data);
i8 dsa_lc_is_empty(dsa_LC * const list);

#endif
