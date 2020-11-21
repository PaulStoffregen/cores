// This header file is in the public domain.

#if defined( ARDUINO_TEENSY36 )
#define TEENSY_MODEL "Teensy 3.6"
#elif defined( ARDUINO_TEENSY35 )
#define TEENSY_MODEL "Teensy 3.5"
#elif defined ( ARDUINO_TEENSY32 )
#define TEENSY_MODEL "Teensy 3.2"
#elif defined ( ARDUINO_TEENSY30 )
#define TEENSY_MODEL "Teensy 3.0"
#elif defined ( ARDUINO_TEENSYLC )
#define TEENSY_MODEL "Teensy LC"
#endif
