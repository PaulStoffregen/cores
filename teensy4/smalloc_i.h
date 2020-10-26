/*
 * This file is a part of SMalloc.
 * SMalloc is MIT licensed.
 * Copyright (c) 2017 Andrey Rys.
 */

#ifndef _SMALLOC_I_H
#define _SMALLOC_I_H

#include "smalloc.h"
#include <string.h>
#include <limits.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

struct smalloc_hdr {
	size_t rsz; /* real allocated size with overhead (if any) */
	size_t usz; /* exact user size as reported by s_szalloc */
	uintptr_t tag; /* sum of all the above, hashed value */
};

#define HEADER_SZ (sizeof(struct smalloc_hdr))
#define MIN_POOL_SZ (HEADER_SZ*20)

#define VOID_PTR(p) ((void *)p)
#define CHAR_PTR(p) ((char *)p)
#define PTR_UINT(p) ((uintptr_t)VOID_PTR(p))
#define HEADER_PTR(p) ((struct smalloc_hdr *)p)
#define USER_TO_HEADER(p) (HEADER_PTR((CHAR_PTR(p)-HEADER_SZ)))
#define HEADER_TO_USER(p) (VOID_PTR((CHAR_PTR(p)+HEADER_SZ)))

extern smalloc_ub_handler smalloc_UB;

uintptr_t smalloc_uinthash(uintptr_t x);
uintptr_t smalloc_mktag(struct smalloc_hdr *shdr);
int smalloc_verify_pool(struct smalloc_pool *spool);
int smalloc_is_alloc(struct smalloc_pool *spool, struct smalloc_hdr *shdr);

void *sm_realloc_pool_i(struct smalloc_pool *spool, void *p, size_t n, int nomove);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
