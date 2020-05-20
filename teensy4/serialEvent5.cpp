
#include <Arduino.h>
#include "HardwareSerial.h"
void serialEvent5() __attribute__((weak));
void serialEvent5() {}		// No use calling this so disable if called...
uint8_t _serialEvent5_default PROGMEM = 1;
