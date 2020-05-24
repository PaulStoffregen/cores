
#include <Arduino.h>
#include "HardwareSerial.h"
#if defined(HAS_KINETISK_UART5) || defined (HAS_KINETISK_LPUART0)
void serialEvent6() __attribute__((weak));
void serialEvent6() {}		// No use calling this so disable if called...
uint8_t _serialEvent6_default PROGMEM = 1;
#endif