#include "HardwareSerial.h"

#if defined(HAS_KINETISK_UART3) && !defined(SERIAL4_DISABLE)

HardwareSerial4 Serial4;

void serialEvent4() __attribute__((weak));
void serialEvent4() {}

#endif
