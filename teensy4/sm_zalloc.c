/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

void *sm_zalloc_pool(struct smalloc_pool *spool, size_t n)
{
	void *r = sm_malloc_pool(spool, n);
	if (r) memset(r, 0, n);
	return r;
}

void *sm_zalloc(size_t n)
{
	return sm_zalloc_pool(&smalloc_curr_pool, n);
}
