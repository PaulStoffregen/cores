#include "HardwareSerial.h"

#if defined(HAS_KINETISK_UART4) && !defined(SERIAL5_DISABLE)

HardwareSerial5 Serial5;

void serialEvent5() __attribute__((weak));
void serialEvent5() {}

#endif
