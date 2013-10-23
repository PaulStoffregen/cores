#ifndef pauls_ugly_debug_included_yadda_yadda__
#define pauls_ugly_debug_included_yadda_yadda__

//#define SPEW_ALL_THIS_CRAP_TO_THE_SERIAL_PORT

#ifdef SPEW_ALL_THIS_CRAP_TO_THE_SERIAL_PORT
#define BAUD_RATE 115200UL
#include <avr/pgmspace.h>
#define print(s)  print_P(PSTR(s))
#define print_hex(s, n) print_P_hex(PSTR(s), (n))
#define print_hex16(s, n) print_P_hex16(PSTR(s), (n))
#define print_hex32(s, n) print_P_hex32(PSTR(s), (n))
static void cout(char c) __attribute__((unused));
static void cout(char c)
{
	if (!(UCSR1B & (1<<TXEN1))) {
		UBRR1 = ((F_CPU / 8 + BAUD_RATE / 2) / BAUD_RATE - 1);
		UCSR1A = (1<<U2X1);
		UCSR1B = (1<<TXEN1);
	}
	while (!(UCSR1A & (1 << UDRE1))) ;
	UDR1 = c;
}
static void print_P(const char *str)  __attribute__((unused));
static void print_P(const char *str)
{
	char c;

	while (1) {
		c = pgm_read_byte(str++);
		if (!c) return;
		if (c == '\n') {
			cout('\r');
			cout('\n');
		} else {
			cout(c);
		}
	}
}
static void phex1(uint8_t n) __attribute__((unused));
static void phex1(uint8_t n)
{
	if (n < 10) cout(n + '0');
	else cout(n - 10 + 'A');
}
static void phex(uint8_t n)  __attribute__((unused));
static void phex(uint8_t n)
{
	phex1(n >> 4);
	phex1(n & 15);
}
static void phex16(uint16_t n)  __attribute__((unused));
static void phex16(uint16_t n)
{
	phex(n >> 8);
	phex(n & 255);
}
static void phex32(uint32_t n)  __attribute__((unused));
static void phex32(uint32_t n)
{
	phex(n >> 24);
	phex(n >> 16);
	phex(n >> 8);
	phex(n & 255);
}
static void print_P_hex(const char *s, uint8_t n)  __attribute__((unused));
static void print_P_hex(const char *s, uint8_t n)
{
        print_P(s);
        phex(n);
        cout('\r');
        cout('\n');
}
static void print_P_hex16(const char *s, uint16_t n) __attribute__((unused));
static void print_P_hex16(const char *s, uint16_t n)
{
        print_P(s);
        phex16(n);
        cout('\r');
        cout('\n');
}
static void print_P_hex32(const char *s, uint32_t n) __attribute__((unused));
static void print_P_hex32(const char *s, uint32_t n)
{
        print_P(s);
        phex32(n);
        cout('\r');
        cout('\n');
}

#else // do not SPEW_ALL_THIS_CRAP_TO_THE_SERIAL_PORT
#define cout(c)
#define print(s)
#define phex1(n)
#define phex(n)
#define phex16(n)
#define phex32(n)
#define print_hex(s, n)
#define print_hex16(s, n)
#define print_hex32(s, n)
#endif
#endif
