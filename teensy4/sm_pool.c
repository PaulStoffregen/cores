/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

struct smalloc_pool smalloc_curr_pool;

int smalloc_verify_pool(struct smalloc_pool *spool)
{
	if (!spool->pool || !spool->pool_size) return 0;
	if (spool->pool_size % HEADER_SZ) return 0;
	return 1;
}

int sm_align_pool(struct smalloc_pool *spool)
{
	size_t x;

	if (smalloc_verify_pool(spool)) return 1;

	x = spool->pool_size % HEADER_SZ;
	if (x) spool->pool_size -= x;
	if (spool->pool_size <= MIN_POOL_SZ) {
		errno = ENOSPC;
		return 0;
	}

	return 1;
}

int sm_set_pool(struct smalloc_pool *spool, void *new_pool, size_t new_pool_size, int do_zero, smalloc_oom_handler oom_handler)
{
	if (!spool) {
		errno = EINVAL;
		return 0;
	}

	if (!new_pool || !new_pool_size) {
		if (smalloc_verify_pool(spool)) {
			if (spool->do_zero) memset(spool->pool, 0, spool->pool_size);
			memset(spool, 0, sizeof(struct smalloc_pool));
			return 1;
		}

		errno = EINVAL;
		return 0;
	}

	spool->pool = new_pool;
	spool->pool_size = new_pool_size;
	spool->oomfn = oom_handler;
	if (!sm_align_pool(spool)) return 0;

	if (do_zero) {
		spool->do_zero = do_zero;
		memset(spool->pool, 0, spool->pool_size);
	}

	return 1;
}

int sm_set_default_pool(void *new_pool, size_t new_pool_size, int do_zero, smalloc_oom_handler oom_handler)
{
	return sm_set_pool(&smalloc_curr_pool, new_pool, new_pool_size, do_zero, oom_handler);
}

int sm_release_pool(struct smalloc_pool *spool)
{
	return sm_set_pool(spool, NULL, 0, 0, NULL);
}

int sm_release_default_pool(void)
{
	return sm_release_pool(&smalloc_curr_pool);
}
