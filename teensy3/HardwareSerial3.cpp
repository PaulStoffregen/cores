#include "HardwareSerial.h"

#ifndef SERIAL3_DISABLE
HardwareSerial3 Serial3;

void serialEvent3() __attribute__((weak));
void serialEvent3() {}
#endif
