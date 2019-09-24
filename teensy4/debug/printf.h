// #define PRINT_DEBUG_STUFF

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
