
#include <Arduino.h>
#include "HardwareSerial.h"
#ifdef HAS_KINETISK_UART3
void serialEvent4() __attribute__((weak));
void serialEvent4() {}		// No use calling this so disable if called...
uint8_t _serialEvent4_default PROGMEM = 1;
#endif