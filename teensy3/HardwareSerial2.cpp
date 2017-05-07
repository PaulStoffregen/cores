#include "HardwareSerial.h"

#ifndef SERIAL2_DISABLE
HardwareSerial2 Serial2;

void serialEvent2() __attribute__((weak));
void serialEvent2() {}
#endif
