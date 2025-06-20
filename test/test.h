#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list_cursor.h"
#include "defines.h"
#include "test_framework.h"

void test_lc_pool_init(void);
void test_lc_init(void);
void test_lc_find(void);
void test_lc_get_tail(void);
void test_lc_push_front(void);
void test_lc_push_back(void);

#endif
