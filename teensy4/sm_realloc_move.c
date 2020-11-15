/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

void *sm_realloc_move_pool(struct smalloc_pool *spool, void *p, size_t n)
{
	return sm_realloc_pool_i(spool, p, n, 1);
}

void *sm_realloc_move(void *p, size_t n)
{
	return sm_realloc_pool_i(&smalloc_curr_pool, p, n, 1);
}
