#include <errno.h>

extern unsigned long _ebss;

char *__brkval = (char *)&_ebss; // TODO: put heap into OCRAM, not DTCM
#define STACK_MARGIN  8192


void * _sbrk(int incr)
{
        char *prev, *stack;

        prev = __brkval;
        if (incr != 0) {
                __asm__ volatile("mov %0, sp" : "=r" (stack) ::);
                if (prev + incr >= stack - STACK_MARGIN) {
                        errno = ENOMEM;
                        return (void *)-1;
                }
                __brkval = prev + incr;
        }
        return prev;
}

