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

typedef struct dsa_LC
{
	dsa_LCNode *head;
} dsa_LC;

typedef struct dsa_LCPool
{
	dsa_LCNode pool[LC_POOL_SIZE];
	dsa_LCNode *ptr;
} dsa_LCPool;

i8 dsa_lc_init(dsa_LCPool * const pool);


#endif
