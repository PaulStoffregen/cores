#include "HardwareSerial.h"

#if (defined(HAS_KINETISK_UART5) || defined (HAS_KINETISK_LPUART0)) && !defined(SERIAL6_DISABLE)

HardwareSerial6 Serial6;

void serialEvent6() __attribute__((weak));
void serialEvent6() {}

#endif
