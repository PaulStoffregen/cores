
#include <Arduino.h>
#include "HardwareSerial.h"
void serialEvent6() __attribute__((weak));
void serialEvent6() {}		// No use calling this so disable if called...
uint8_t _serialEvent6_default PROGMEM = 1;
