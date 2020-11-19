// External memory allocation functions.  Attempt to use external memory,
// but automatically fall back to internal RAM if external RAM can't be used.

#include <stdlib.h>
#include "smalloc.h"
#include "wiring.h"

#if defined(ARDUINO_TEENSY41)
// Teensy 4.1 external RAM address range is 0x70000000 to 0x7FFFFFFF
#define HAS_EXTRAM
#define IS_EXTMEM(addr) (((uint32_t)ptr >> 28) == 7)
#endif


void *extmem_malloc(size_t size)
{
#ifdef HAS_EXTRAM
	void *ptr = sm_malloc_pool(&extmem_smalloc_pool, size);
	if (ptr) return ptr;
#endif
	return malloc(size);
}

void extmem_free(void *ptr)
{
#ifdef HAS_EXTRAM
	if (IS_EXTMEM(ptr)) {
		sm_free_pool(&extmem_smalloc_pool, ptr);
		return;
	}
#endif
	free(ptr);
}

void *extmem_calloc(size_t nmemb, size_t size)
{
	return extmem_malloc(nmemb * size);
}

void *extmem_realloc(void *ptr, size_t size)
{
#ifdef HAS_EXTRAM
	if (IS_EXTMEM(ptr)) {
		return sm_realloc_pool(&extmem_smalloc_pool, ptr, size);
	}
#endif
	return realloc(ptr, size);
}


