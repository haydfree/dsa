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
dsa_lc_pool_find_free_node(const dsa_LCPool * const pool, const dsa_LCNode **dst)
{
    i8 ret = EXIT_FAILURE;
    u32 i = 0;

    GUARD_NULL(pool);
    GUARD_NULL(dst);
    GUARD_NON_NULL(*dst);

    for (; i < pool->capacity; i++) 
    {
        if (pool->nodes[i].is_used == FALSE) { *dst = &pool->nodes[i]; break; }
    }

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_push_front(dsa_LC * const list, void * const data)
{
    i8 ret = EXIT_FAILURE;
    dsa_LCNode *tmp = NULL, *new_node = NULL;
    u32 i;

    GUARD_NULL(list);
    GUARD_NULL(data);
    GUARD_NON_POS(list->pool->nodes_free);

    for (i = 0; i < list->pool->capacity; ++i) {
        if (!list->pool->nodes[i].is_used) {
            new_node = &list->pool->nodes[i];
            break;
        }
    }
    GUARD_NULL(new_node);

    tmp = list->head;
    new_node->data = data;
    new_node->next = tmp;
    new_node->is_used = TRUE;
    list->head = new_node;
    list->pool->nodes_free--;
    list->pool->nodes_used++;
    list->pool->free_nodes = &list->pool->nodes[i];

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
        if (!list->pool->nodes[i].is_used) {
            new_node = &list->pool->nodes[i];
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
