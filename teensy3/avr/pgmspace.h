#ifndef __PGMSPACE_H_
#define __PGMSPACE_H_ 1

#include <inttypes.h>

#define PROGMEM
#define PGM_P  const char *
#define PSTR(str) (str)

#define _SFR_BYTE(n) (n)

typedef void prog_void;
typedef char prog_char;
typedef unsigned char prog_uchar;
typedef int8_t prog_int8_t;
typedef uint8_t prog_uint8_t;
typedef int16_t prog_int16_t;
typedef uint16_t prog_uint16_t;
typedef int32_t prog_int32_t;
typedef uint32_t prog_uint32_t;

#define memchr_P(str, c, len) memchr((str), (c), (len))
#define memcmp_P(a, b, n) memcmp((a), (b), (n))
#define memcpy_P(dest, src, num) memcpy((dest), (src), (num))
#define memmem_P(a, alen, b, blen) memmem((a), (alen), (b), (blen))
#define memrchr_P(str, val, len) memrchr((str), (val), (len))
#define strcat_P(dest, src) strcat((dest), (src))
#define strchr_P(str, c) strchr((str), (c))
#define strchrnul_P(str, c) strchrnul((str), (c))
#define strcmp_P(a, b) strcmp((a), (b))
#define strcpy_P(dest, src) strcpy((dest), (src))
#define strcasecmp_P(a, b) strcasecmp((a), (b))
#define strcasestr_P(a, b) strcasestr((a), (b))
#define strlcat_P(dest, src, len) strlcat((dest), (src), (len))
#define strlcpy_P(dest, src, len) strlcpy((dest), (src), (len))
#define strlen_P(s) strlen((const char *)(s))
#define strnlen_P(str, len) strnlen((str), (len))
#define strncmp_P(a, b, n) strncmp((a), (b), (n))
#define strncasecmp_P(a, b, n) strncasecmp((a), (b), (n))
#define strncat_P(a, b, n) strncat((a), (b), (n))
#define strncpy_P(a, b, n) strncmp((a), (b), (n))
#define strpbrk_P(str, chrs) strpbrk((str), (chrs))
#define strrchr_P(str, c) strrchr((str), (c))
#define strsep_P(strp, delim) strsep((strp), (delim))
#define strspn_P(str, chrs) strspn((str), (chrs))
#define strstr_P(a, b) strstr((a), (b))
#define sprintf_P(s, ...) sprintf((s), __VA_ARGS__)
#define vfprintf_P(s, ...) vfprintf((s), __VA_ARGS__)
#define printf_P(...) printf(__VA_ARGS__)
#define snprintf_P(s, n, ...) ((s), (n), __VA_ARGS__)
#define vsprintf_P(s, ...) ((s),__VA_ARGS__)
#define vsnprintf_P(s, n, ...) ((s), (n),__VA_ARGS__)
#define fprintf_P(s, ...) ((s), __VA_ARGS__)

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))
#define pgm_read_float(addr) (*(const float *)(addr))

#define pgm_read_byte_near(addr) pgm_read_byte(addr)
#define pgm_read_word_near(addr) pgm_read_word(addr)
#define pgm_read_dword_near(addr) pgm_read_dword(addr)
#define pgm_read_float_near(addr) pgm_read_float(addr)
#define pgm_read_byte_far(addr) pgm_read_byte(addr)
#define pgm_read_word_far(addr) pgm_read_word(addr)
#define pgm_read_dword_far(addr) pgm_read_dword(addr)
#define pgm_read_float_far(addr) pgm_read_float(addr)

#endif
