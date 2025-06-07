#include "list_cursor.h"

i8 dsa_lc_pool_init(dsa_LCPool *pool, u32 capacity) 
{
    i8 ret = EXIT_FAILURE;
    u32 i = 0;
    
    GUARD_NULL(pool);
    GUARD_NON_POS(capacity);
    
    for (; i < capacity; i++) 
    {
        pool->nodes[i].data = NULL;
        pool->nodes[i].next = NULL;
        pool->nodes[i].is_used = FALSE;
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
dsa_lc_push_front(dsa_LC * const list, void * const data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *tmp = NULL, *new_node = NULL;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NON_POS(list->pool->nodes_free);

    tmp = list->head;
    new_node = list->pool->nodes;
    new_node->data = data;
    new_node->next = tmp;
    new_node->is_used = TRUE;
    list->head = new_node;
    list->pool->nodes_free--;
    list->pool->nodes_used++;
    list->pool->nodes++;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_push_back(dsa_LC * const list, void * const data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *new_node = NULL;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NON_POS(list->pool->nodes_free);

    new_node = list->pool->nodes;
    new_node->data = data;
    new_node->next = NULL;
    new_node->is_used = TRUE;
    list->pool->nodes_free--;
    list->pool->nodes_used++;
    list->pool->nodes++;

    if (list->head == NULL) { list->head = new_node; }
    else { list->head->next = new_node; }

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_pop_front(dsa_LC * const list, const void **data)
{
    i8 ret = EXIT_FAILURE;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NON_NULL(*data);

    list->pool->nodes_free++;
    list->pool->nodes_used--;
    list->pool->nodes--;

    *data = list->head->data;
    list->head->data = NULL;
    list->head->is_used = FALSE;

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
dsa_lc_remove(dsa_LC * const list, const void * const data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *node = NULL;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NULL(list->head);
    GUARD_FAILURE(dsa_lc_find(list, data, (const dsa_LCNode**)&node));

    list->head = list->head->next;
    list->head->next = list->head->next->next;
    node->data = NULL;
    node->is_used = FALSE;
    list->pool->nodes_free++;
    list->pool->nodes_used--;
    list->pool->nodes--;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}
