/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

void *sm_malloc_pool(struct smalloc_pool *spool, size_t n)
{
	struct smalloc_hdr *basehdr, *shdr, *dhdr;
	char *s;
	int found;
	size_t x;

again:	if (!smalloc_verify_pool(spool)) {
		errno = EINVAL;
		return NULL;
	}

	if (n == 0) n++; /* return a block successfully */
	if (n > SIZE_MAX
	|| n > (spool->pool_size - HEADER_SZ)) goto oom;

	shdr = basehdr = spool->pool;
	while (CHAR_PTR(shdr)-CHAR_PTR(basehdr) < spool->pool_size) {
		/*
		 * Already allocated block.
		 * Skip it by jumping over it.
		 */
		if (smalloc_is_alloc(spool, shdr)) {
			s = CHAR_PTR(HEADER_TO_USER(shdr));
			s += shdr->rsz + HEADER_SZ;
			shdr = HEADER_PTR(s);
			continue;
		}
		/*
		 * Free blocks ahead!
		 * Do a second search over them to find out if they're
		 * really large enough to fit the new allocation.
		 */
		else {
			dhdr = shdr; found = 0;
			while (CHAR_PTR(dhdr)-CHAR_PTR(basehdr) < spool->pool_size) {
				/* pre calculate free block size */
				x = CHAR_PTR(dhdr)-CHAR_PTR(shdr);
				/*
				 * ugh, found next allocated block.
				 * skip this candidate then.
				 */
				if (smalloc_is_alloc(spool, dhdr))
					goto allocblock;
				/*
				 * did not see allocated block yet,
				 * but this free block is of enough size
				 * - finally, use it.
				 */
				if (n + HEADER_SZ <= x) {
					x -= HEADER_SZ;
					found = 1;
					goto outfound;
				}
				dhdr++;
			}

outfound:		if (found) {
				uintptr_t tag;
				/* allocate and return this block */
				shdr->rsz = x;
				shdr->usz = n;
				shdr->tag = tag = smalloc_mktag(shdr);
				if (spool->do_zero) memset(HEADER_TO_USER(shdr), 0, shdr->rsz);
				s = CHAR_PTR(HEADER_TO_USER(shdr));
				s += shdr->usz;
				for (x = 0;
				x < sizeof(struct smalloc_hdr);
				x += sizeof(uintptr_t)) {
					tag = smalloc_uinthash(tag);
					memcpy(s+x, &tag, sizeof(uintptr_t));
				}
				memset(s+x, 0xff, shdr->rsz - shdr->usz);
				return HEADER_TO_USER(shdr);
			}

			/* continue first search for next free block */
allocblock:		shdr = dhdr;
			continue;
		}

		shdr++;
	}

oom:	if (spool->oomfn) {
		x = spool->oomfn(spool, n);
		if (x > spool->pool_size) {
			spool->pool_size = x;
			if (sm_align_pool(spool)) goto again;
		}
	}

	errno = ENOMEM;
	return NULL;
}

void *sm_malloc(size_t n)
{
	return sm_malloc_pool(&smalloc_curr_pool, n);
}
