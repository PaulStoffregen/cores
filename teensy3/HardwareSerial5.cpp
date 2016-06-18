#include "HardwareSerial.h"

#ifdef HAS_KINETISK_UART4

HardwareSerial5 Serial5;

void serialEvent5() __attribute__((weak));
void serialEvent5() {}

#endif
