#include "HardwareSerial.h"

#ifndef SERIAL1_DISABLE
HardwareSerial Serial1;

void serialEvent1() __attribute__((weak));
void serialEvent1() {}
#endif
