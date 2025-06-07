#include "list_cursor.h"

i8
dsa_lc_init(dsa_LCPool * const pool)
{
    i8 ret = EXIT_FAILURE;

    GUARD_NULL(pool);

    pool->ptr = pool->pool;

    ret = EXIT_SUCCESS;
cleanup:
    return ret;
}
