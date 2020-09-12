
#include <Arduino.h>
#include "HardwareSerial.h"
void serialEvent8() __attribute__((weak));
void serialEvent8() {}		// No use calling this so disable if called...
uint8_t _serialEvent8_default PROGMEM = 1;
