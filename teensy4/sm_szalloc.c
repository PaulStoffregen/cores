/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

size_t sm_szalloc_pool(struct smalloc_pool *spool, const void *p)
{
	struct smalloc_hdr *shdr;

	if (!smalloc_verify_pool(spool)) {
		errno = EINVAL;
		return ((size_t)-1);
	}

	if (!p) return 0;

	shdr = USER_TO_HEADER(p);
	if (smalloc_is_alloc(spool, shdr)) return shdr->usz;
	smalloc_UB(spool, p);
	return 0;
}

size_t sm_szalloc(const void *p)
{
	return sm_szalloc_pool(&smalloc_curr_pool, p);
}
