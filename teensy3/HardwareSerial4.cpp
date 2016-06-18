#include "HardwareSerial.h"

#ifdef HAS_KINETISK_UART3

HardwareSerial4 Serial4;

void serialEvent4() __attribute__((weak));
void serialEvent4() {}

#endif
