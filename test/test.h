#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list_cursor.h"

void test_lc_push_front(void);
void test_lc_push_back(void);
void test_lc_pop_front(void);
void test_lc_pop_back(void);
void test_lc_get_next(void);
void test_lc_get_prev(void);
void test_lc_get_head(void);
void test_lc_get_tail(void);
void test_lc_clear(void);

#endif
