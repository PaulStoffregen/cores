// uncommenting the line below will enable the debug printf statements in cores\teensy4
// by default it will print to the Serial4 TX pin at baud rate of 115200
//#define PRINT_DEBUG_STUFF

// uncommenting the line below will switch to doing outputs to USB Serial or SEREMU instead of Serial4
// However some of the earlier print statements that happen before USB is initialized will be lost
// if you need those outputs, better to use Serial 4.
//#define PRINT_DEBUG_USING_USB // if both defined will try to direct stuff out USB Serial or SEREMU

#ifdef PRINT_DEBUG_STUFF
// defining printf this way breaks things like Serial.printf() in C++ :(
#define printf(...) printf_debug(__VA_ARGS__)
#ifdef __cplusplus
extern "C" {
#endif
void printf_debug_init(void);
void printf_debug(const char *format, ...);
#ifdef __cplusplus
}
#endif

#else
#define printf_init()
#define printf(...)
#define printf_debug_init()

#endif
