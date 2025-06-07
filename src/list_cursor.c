#include "list_cursor.h"

i8
dsa_lc_pool_init(dsa_LCPool * const pool)
{
    i8 ret = EXIT_FAILURE;

    GUARD_NULL(pool);

    pool->ptr = pool->pool;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8
dsa_lc_init(dsa_LC * const list, dsa_LCPool * const pool)
{
    i8 ret = EXIT_FAILURE;

    GUARD_NULL(pool);

    list->head = NULL;
    list->pool = pool;
    pool->ptr = pool->pool;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}

i8 
dsa_lc_push_front(dsa_LC * const list, void * const data)
{
    i8 ret = EXIT_FAILURE;

    GUARD_NULL(list);
    GUARD_NULL(data);

    list->head = data;
    list->pool->ptr->data = data;
    list->pool->ptr++;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}
