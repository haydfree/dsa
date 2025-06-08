#include "list_cursor.h"

i8 
dsa_lc_pool_init(dsa_LCPool *pool, u32 capacity) 
{
    i8 ret = EXIT_FAILURE;
    u32 i = 0;
    
    GUARD_NULL(pool);
    GUARD_NON_POS(capacity);
    
    for (; i < capacity; i++) 
    {
        pool->nodes_start[i].data = NULL;
        pool->nodes_start[i].next = NULL;
        pool->nodes_start[i].is_used = FALSE;
    }
    pool->nodes_used = 0;
    pool->nodes_free = pool->capacity = capacity;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8 
dsa_lc_init(dsa_LC * const list, dsa_LCPool * const pool)
{
    i8 ret = EXIT_FAILURE;

    GUARD_NULL(list);
    GUARD_NULL(pool);

    list->pool = pool;
    list->head = NULL;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8 
dsa_lc_pool_find_free_node(const dsa_LCPool * const pool, const dsa_LCNode **dst)
{
    i8 ret = EXIT_FAILURE;
    u32 i = 0;

    GUARD_NULL(pool);
    GUARD_NULL(dst);
    GUARD_NON_NULL(*dst);

    for (; i < pool->capacity; i++) 
    {
        if (pool->nodes_start[i].is_used == FALSE) { *dst = &pool->nodes_start[i]; break; }
    }

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_push_front(dsa_LC * const list, void * const data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *new_node = NULL;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NON_POS(list->pool->nodes_free);

	// find first unused node
	GUARD_FAILURE(dsa_lc_pool_find_free_node(list->pool, (const dsa_LCNode**)&new_node));
	GUARD_NULL(new_node);

	new_node->data = data;
	new_node->is_used = TRUE;
	list->pool->nodes_free--;
	list->pool->nodes_used++;
	list->pool->nodes_end = new_node;

	// if head is NULL, push new node to head
	if (!list->head) { list->head = new_node; } 
	// if head is not NULL, push head to node->next and set head to new node
	else { new_node->next = list->head; list->head = new_node; }

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_push_back(dsa_LC * const list, void * const data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *new_node = NULL, *cur = NULL;
    u32 i;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NON_POS(list->pool->nodes_free);

    /* Find first unused node */
    for (i = 0; i < list->pool->capacity; ++i) {
        if (!list->pool->nodes_start[i].is_used) {
            new_node = &list->pool->nodes_start[i];
            break;
        }
    }
    GUARD_NULL(new_node);

    new_node->data = data;
    new_node->next = NULL;
    new_node->is_used = TRUE;
    list->pool->nodes_free--;
    list->pool->nodes_used++;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_node;
    }

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_pop_front(dsa_LC * const list, const void **data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *node = NULL;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NULL(list->head);

    node = list->head;
    *data = node->data;
    list->head = node->next;

    node->data = NULL;
    node->is_used = FALSE;
    list->pool->nodes_free++;
    list->pool->nodes_used--;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_find(const dsa_LC * const list, const void * const data, const dsa_LCNode **dst)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *node = NULL;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NULL(dst);
    GUARD_NULL(list->head);
    GUARD_NON_NULL(*dst);

    node = list->head;
    while (node != NULL)
    {
        if (node->data == data) { break; }
        node = node->next;
    }

    *dst = node;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_remove(dsa_LC * const list, dsa_LCNode * const node)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *cur = NULL;

    GUARD_NULL(list);
    GUARD_NULL(node);
    GUARD_NULL(list->head);

    if (list->head == node) {
        list->head = node->next;
    } else {
        cur = list->head;
        while (cur->next != NULL) {
            if (cur->next == node) {
                cur->next = node->next;
                break;
            }
            cur = cur->next;
        }
    }

    node->data = NULL;
    node->is_used = FALSE;
    list->pool->nodes_free++;
    list->pool->nodes_used--;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}
