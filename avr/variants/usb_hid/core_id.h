#define CORE_TEENSY_HID
#define CORE_TEENSY_KEYBOARD
#define CORE_TEENSY_MOUSE
#if defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#define CORE_TEENSY_JOYSTICK
#endif
