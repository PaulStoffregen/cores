#ifndef WiringPrivate_h
#define WiringPrivate_h
#ifndef _STDIO_H_
#include <stdio.h>
#endif
#ifndef _STDARG_H
#include <stdarg.h>
#endif
#ifndef Wiring_h
#include "wiring.h"
#endif

#ifndef cbi
#define cbi(sfr, bit) ((sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) ((sfr) |= _BV(bit))
#endif

typedef void (*voidFuncPtr)(void);

#endif


