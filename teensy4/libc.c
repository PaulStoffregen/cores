#include <errno.h>
#include "debug/printf.h"

// from the linker script
extern unsigned long _edmamem;
extern unsigned long _emallocmem;

char *__brkval = (char *)&_edmamem;

void * _sbrk(int incr)
{
	char *prev;

	printf("sbrk incr = %d\n", incr);

	prev = __brkval;
	if (incr != 0) {
		if (prev + incr > (char *)&_emallocmem) {
			errno = ENOMEM;
			return (void *)-1;
		}
		__brkval = prev + incr;
	}
	return prev;
}

