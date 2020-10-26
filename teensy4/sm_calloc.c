/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

void *sm_calloc_pool(struct smalloc_pool *spool, size_t x, size_t y)
{
	return sm_zalloc_pool(spool, x * y);
}

void *sm_calloc(size_t x, size_t y)
{
	return sm_calloc_pool(&smalloc_curr_pool, x, y);
}
