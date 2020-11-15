/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

static int smalloc_check_bounds(struct smalloc_pool *spool, struct smalloc_hdr *shdr)
{
	if (!spool) return 0;
	if (CHAR_PTR(shdr) >= CHAR_PTR(spool->pool)
	&& CHAR_PTR(shdr) <= (CHAR_PTR(spool->pool)+spool->pool_size))
		return 1;
	return 0;
}

static int smalloc_valid_tag(struct smalloc_hdr *shdr)
{
	char *s;
	uintptr_t r = smalloc_mktag(shdr);
	size_t x;

	if (shdr->tag == r) {
		s = CHAR_PTR(HEADER_TO_USER(shdr));
		s += shdr->usz;
		for (x = 0; x < sizeof(struct smalloc_hdr); x += sizeof(uintptr_t)) {
			r = smalloc_uinthash(r);
			if (memcmp(s+x, &r, sizeof(uintptr_t)) != 0) return 0;
		}
		s += x; x = 0;
		while (x < shdr->rsz - shdr->usz) {
			if (s[x] != '\xFF') return 0;
			x++;
		}
		return 1;
	}
	return 0;
}

static void smalloc_do_crash(struct smalloc_pool *spool, const void *p)
{
	char *c = NULL;
	*c = 'X';
}

smalloc_ub_handler smalloc_UB = smalloc_do_crash;

void sm_set_ub_handler(smalloc_ub_handler handler)
{
	if (!handler) smalloc_UB = smalloc_do_crash;
	else smalloc_UB = handler;
}

int smalloc_is_alloc(struct smalloc_pool *spool, struct smalloc_hdr *shdr)
{
	if (!smalloc_check_bounds(spool, shdr)) return 0;
	if (shdr->rsz == 0) return 0;
	if (shdr->rsz > SIZE_MAX) return 0;
	if (shdr->usz > SIZE_MAX) return 0;
	if (shdr->usz > shdr->rsz) return 0;
	if (shdr->rsz % HEADER_SZ) return 0;
	if (!smalloc_valid_tag(shdr)) return 0;
	return 1;
}
