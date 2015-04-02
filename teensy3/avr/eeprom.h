#ifndef _AVR_EEPROM_H_
#define _AVR_EEPROM_H_ 1

#include <stddef.h>
#include <stdint.h>

#include "avr_functions.h"

#if defined(__MK20DX128__) || defined(__MK20DX256__)
  #define E2END 0x7FF
#elif defined(__MKL26Z64__)
  #define E2END 0x7F
#else
  #define E2END 0
#endif

#endif
