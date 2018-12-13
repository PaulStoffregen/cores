#define PRINT_DEBUG_STUFF

#ifdef PRINT_DEBUG_STUFF
#define printf_init() printf_debug_init()
#define printf(...) printf_debug(__VA_ARGS__)
void print_debug_init(void);
void printf_debug(const char *format, ...);

#else
#define printf_init()
#define printf(...)

#endif
