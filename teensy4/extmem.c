/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// External memory allocation functions.  Attempt to use external memory,
// but automatically fall back to internal RAM if external RAM can't be used.

#include <stdlib.h>
#include "smalloc.h"
#include "wiring.h"

#if defined(ARDUINO_TEENSY41)
// Teensy 4.1 external RAM address range is 0x70000000 to 0x7FFFFFFF
#define HAS_EXTRAM
#define IS_EXTMEM(addr) (((uint32_t)(addr) >> 28) == 7)
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
#ifdef HAS_EXTRAM
	// Note: It is assumed that the pool was created with do_zero set to true
	void *ptr = sm_malloc_pool(&extmem_smalloc_pool, nmemb*size);
	if (ptr) return ptr;
#endif
	return calloc(nmemb, size);
}

void *extmem_realloc(void *ptr, size_t size)
{
#ifdef HAS_EXTRAM
	if (IS_EXTMEM(ptr) || ptr == NULL) {
		return sm_realloc_pool(&extmem_smalloc_pool, ptr, size);
	}
#endif
	return realloc(ptr, size);
}
