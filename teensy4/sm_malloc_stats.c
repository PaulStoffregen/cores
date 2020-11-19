/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

int sm_malloc_stats_pool(struct smalloc_pool *spool, size_t *total, size_t *user, size_t *free, int *nr_blocks)
{
	struct smalloc_hdr *shdr, *basehdr;
	int r = 0;

	if (!smalloc_verify_pool(spool)) {
		errno = EINVAL;
		return -1;
	}

	if (!total && !user && !free && !nr_blocks) return 0;

	if (total) *total = 0;
	if (user) *user = 0;
	if (free) *free = 0;
	if (nr_blocks) *nr_blocks = 0;

	shdr = basehdr = spool->pool;
	while (CHAR_PTR(shdr)-CHAR_PTR(basehdr) < spool->pool_size) {
		if (smalloc_is_alloc(spool, shdr)) {
			if (total) *total += HEADER_SZ + shdr->rsz + HEADER_SZ;
			if (user) *user += shdr->usz;
			if (nr_blocks) *nr_blocks += 1;
			r = 1;
		}

		shdr++;
	}

	*free = spool->pool_size - *total;

	return r;
}

int sm_malloc_stats(size_t *total, size_t *user, size_t *free, int *nr_blocks)
{
	return sm_malloc_stats_pool(&smalloc_curr_pool, total, user, free, nr_blocks);
}
