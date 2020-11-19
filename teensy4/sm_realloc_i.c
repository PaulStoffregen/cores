/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

/*
 * Please do NOT use this function directly or rely on it's presence.
 * It may go away in future SMalloc versions, or it's calling
 * signature may change. It is internal function, hence "_i" suffix.
 */
void *sm_realloc_pool_i(struct smalloc_pool *spool, void *p, size_t n, int nomove)
{
	struct smalloc_hdr *basehdr, *shdr, *dhdr;
	void *r;
	char *s;
	int found;
	size_t rsz, usz, x;
	uintptr_t tag;

	if (!smalloc_verify_pool(spool)) {
		errno = EINVAL;
		return NULL;
	}

	if (!p) return sm_malloc_pool(spool, n);
	if (!n && p) {
		sm_free_pool(spool, p);
		return NULL;
	}

	/* determine user size */
	shdr = USER_TO_HEADER(p);
	if (!smalloc_is_alloc(spool, shdr)) smalloc_UB(spool, p);
	usz = shdr->usz;
	rsz = shdr->rsz;

	/* newsize is lesser than allocated - truncate */
	if (n <= usz) {
		if (spool->do_zero) memset(p + n, 0, shdr->rsz - n);
		s = CHAR_PTR(HEADER_TO_USER(shdr));
		s += usz;
		memset(s, 0, HEADER_SZ);
		if (spool->do_zero) memset(s+HEADER_SZ, 0, rsz - usz);
		shdr->rsz = (n%HEADER_SZ)?(((n/HEADER_SZ)+1)*HEADER_SZ):n;
		shdr->usz = n;
		shdr->tag = tag = smalloc_mktag(shdr);
		s = CHAR_PTR(HEADER_TO_USER(shdr));
		s += shdr->usz;
		for (x = 0; x < sizeof(struct smalloc_hdr); x += sizeof(uintptr_t)) {
			tag = smalloc_uinthash(tag);
			memcpy(s+x, &tag, sizeof(uintptr_t));
		}
		memset(s+x, 0xff, shdr->rsz - shdr->usz);
		return p;
	}

	/* newsize is bigger than allocated, but there is free room - modify */
	if (n > usz && n <= rsz) {
		if (spool->do_zero) {
			s = CHAR_PTR(HEADER_TO_USER(shdr));
			s += usz;
			memset(s, 0, HEADER_SZ);
		}
		shdr->usz = n;
		shdr->tag = tag = smalloc_mktag(shdr);
		s = CHAR_PTR(HEADER_TO_USER(shdr));
		s += shdr->usz;
		for (x = 0; x < sizeof(struct smalloc_hdr); x += sizeof(uintptr_t)) {
			tag = smalloc_uinthash(tag);
			memcpy(s+x, &tag, sizeof(uintptr_t));
		}
		memset(s+x, 0xff, shdr->rsz - shdr->usz);
		return p;
	}

	/* newsize is bigger, larger than rsz but there are free blocks beyond - extend */
	basehdr = spool->pool; dhdr = shdr+(rsz/HEADER_SZ); found = 0;
	while (CHAR_PTR(dhdr)-CHAR_PTR(basehdr) < spool->pool_size) {
		x = CHAR_PTR(dhdr)-CHAR_PTR(shdr);
		if (smalloc_is_alloc(spool, dhdr))
			goto allocblock;
		if (n + HEADER_SZ <= x) {
			x -= HEADER_SZ;
			found = 1;
			goto outfound;
		}
		dhdr++;
	}

outfound:
	/* write new numbers of same allocation */
	if (found) {
		if (spool->do_zero) {
			s = CHAR_PTR(HEADER_TO_USER(shdr));
			s += usz;
			memset(s, 0, HEADER_SZ);
			memset(s+HEADER_SZ, 0, rsz - usz);
		}
		shdr->rsz = x;
		shdr->usz = n;
		shdr->tag = tag = smalloc_mktag(shdr);
		s = CHAR_PTR(HEADER_TO_USER(shdr));
		s += shdr->usz;
		for (x = 0; x < sizeof(struct smalloc_hdr); x += sizeof(uintptr_t)) {
			tag = smalloc_uinthash(tag);
			memcpy(s+x, &tag, sizeof(uintptr_t));
		}
		memset(s+x, 0xff, shdr->rsz - shdr->usz);
		return p;
	}

allocblock:
	/* newsize is bigger than allocated and no free space - move */
	if (nomove) {
		/* fail if user asked */
		errno = ERANGE;
		return NULL;
	}
	r = sm_malloc_pool(spool, n);
	if (!r) return NULL;
	memcpy(r, p, usz);
	sm_free_pool(spool, p);

	return r;
}
