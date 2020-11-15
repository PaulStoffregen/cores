/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#include "smalloc_i.h"

/* An adopted Jenkins one-at-a-time hash */
#define UIHOP(x, s) do {		\
		hash += (x >> s) & 0xff;\
		hash += hash << 10;	\
		hash ^= hash >> 6;	\
	} while (0)
uintptr_t smalloc_uinthash(uintptr_t x)
{
	uintptr_t hash = 0;

	UIHOP(x, 0);
	UIHOP(x, 8);
	UIHOP(x, 16);
	UIHOP(x, 24);

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return hash;
}
#undef UIHOP

uintptr_t smalloc_mktag(struct smalloc_hdr *shdr)
{
	uintptr_t r = smalloc_uinthash(PTR_UINT(shdr));
	r += shdr->rsz;
	r = smalloc_uinthash(r);
	r += shdr->usz;
	r = smalloc_uinthash(r);
	return r;
}
