//#define USB_SERIAL_PRIVATE_INCLUDE
//#include "usb_mass_storage_debug.h"
//#include "flash.h"

//#include "pauls_ugly_debug.h"


inline uint32_t media_size(void);
void media_init(void);
uint8_t media_lock(void);
void media_unlock(void);
void media_poll(void);
static void media_send_begin(uint32_t lba);
static void media_send_chunk(uint32_t lba, uint8_t chunk);
static void media_send_end(void);
static void media_receive_begin(uint32_t lba);
static void media_receive_chunk(uint32_t lba, uint8_t chunk);
static void media_receive_end(void);



/**************************************************************************
 *
 *  Storage Media Access Functions
 *
 **************************************************************************/


#if defined(__AVR_ATmega32U4__)
#define LPM "lpm "
#define EPZ 0x3F
#define READ_ONLY 1
#elif defined(__AVR_AT90USB646__)
#define LPM "lpm "
#define EPZ 0x7E
#define READ_ONLY 0
#elif defined(__AVR_AT90USB1286__)
#define LPM "elpm "
#define EPZ 0xFE
#define READ_ONLY 0
#endif

#ifndef USBSTATE
#define USBSTATE
#endif

volatile uint8_t media_rdonly USBSTATE;

#define MEDIA_PRESENT_MASK              0x10

#define MEDIA_STATE_READY               0x12
#define MEDIA_STATE_CLAIMED             0x80    // media is claimed
#define MEDIA_STATE_CLAIMED_STATUS      0x40    // claimed status reported
#define MEDIA_STATE_CLAIMED_SENSE       0x20    // claimed scsi sense sent
volatile uint8_t media_state USBSTATE;

void media_restart(void)
{
}

void media_init(void)
{
	media_state = MEDIA_STATE_READY;
	media_rdonly = READ_ONLY;
}

void media_claim(void)
{
	if (media_state & MEDIA_STATE_CLAIMED) return;
	while (!media_lock()) /*wait*/ ;
	media_state = MEDIA_STATE_CLAIMED;
	print("Media claimed by user program\n");
	media_unlock();
}

void media_release(uint8_t read_only_mode)
{
	uint8_t mstate;

	mstate = media_state;
	if (!(mstate & MEDIA_STATE_CLAIMED)) return;
	print("Media release begin\n");
	while (mstate != (MEDIA_STATE_CLAIMED|MEDIA_STATE_CLAIMED_STATUS|MEDIA_STATE_CLAIMED_SENSE)) {
		if (!usb_configuration) break;
		// TODO: a timeout??
		mstate = media_state;
	}
	// a brief delay is needed here... but why?
	delayMicroseconds(12500);
	print("Media released by user program\n");
	media_state = MEDIA_STATE_READY;
#if READ_ONLY
	media_rdonly = READ_ONLY;
#else
	media_rdonly = read_only_mode;
#endif
}


void media_poll(void)
{
	if ((media_state & MEDIA_STATE_CLAIMED)) return;
	media_state = MEDIA_STATE_READY;
}



// return the number of 512 byte blocks, or 0 if the media is offline
//
inline uint32_t media_size(void)
{
	uint8_t r;
	asm volatile(
		"ldi %0, %1"				"\n\t"
		"subi %0, hi8(pm(__data_load_end))"	"\n"
		: "=d" (r) : "M" (EPZ - 1));
	return r;
}

// __data_load_start = 07A8
// end = 7E00, FC00, 1FC00

// pm(__data_load_start) = 3D4
// end = 3F00, 7E00, FE00

uint8_t media_read_sector(uint32_t lba, uint8_t *buffer)
{
	while (!media_lock()) /*wait*/ ;
	asm volatile(
		"clr	r30"				"\n\t"
		"ldi	r31, %0"			"\n\t"
		"sub	r31, %2"			"\n\t"
		"lsl	r31"				"\n\t"
#if defined(__AVR_AT90USB1286__)
		"adc	__zero_reg__, __zero_reg__"	"\n\t"
		"out	0x3B, __zero_reg__"		"\n\t"
		"clr	__zero_reg__"			"\n\t"
#endif
	"L_%=_looop:"					"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X+, __tmp_reg__"		"\n\t"
		"tst	r30"				"\n\t"
		"brne	L_%=_looop"			"\n\t"
		"sbrc	r31, 0"				"\n\t"
		"rjmp	L_%=_looop"			"\n\t"
		: : "M" (EPZ - 1), "x" (buffer), "r" ((uint8_t)lba)
		: "r0", "r30", "r31"
	);
	media_unlock();
	return 1;
}


static void media_send_begin(uint32_t lba)
{
}

static inline void media_send_chunk(uint32_t lba, uint8_t chunk)
{
	uint8_t addr = lba;
	asm volatile(
		"ldi	r31, %1"			"\n\t"
		"sub	r31, %3"			"\n\t"
		"lsl	r31"				"\n\t"
#if defined(__AVR_AT90USB1286__)
		"adc	__zero_reg__, __zero_reg__"	"\n\t"
		"out	0x3B, __zero_reg__"		"\n\t"
		"clr	__zero_reg__"			"\n\t"
#endif
		"mov	r30, %0"			"\n\t"
		"andi	r30, 7"				"\n\t"
		"swap	r30"				"\n\t"
		"lsl	r30"				"\n\t"
		"lsl	r30"				"\n\t"
		"adc	r31, __zero_reg__"		"\n\t"
		"ldi	%0, 8"				"\n\t"
	"L_%=_looop:"					"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		LPM	"__tmp_reg__, Z+"		"\n\t"
		"st	X, __tmp_reg__"			"\n\t"
		"subi	%0, 1"				"\n\t"
		"brne	L_%=_looop"			"\n\t"
		: "+d" (chunk)
		: "M" (EPZ - 1), "x" (&UEDATX), "r" (addr)
		: "r0", "r30", "r31"
	);
	UEINTX = 0x3A;
}


static void media_send_end(void)
{
}

uint8_t media_write_sector(uint32_t lba, const uint8_t *buffer)
{
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
	uint8_t addr = lba;
	uint8_t offset = 0;
	uint32_t a;

	while (!media_lock()) /*wait*/ ;
	a = ((uint32_t)(EPZ - 1 - addr) << 9);
	while (1) {
		do {
			uint16_t tmp = *buffer++;
			tmp |= (*buffer++ << 8);
			boot_flash_fill_temp_buffer(tmp, offset);
			offset += 2;
		} while (offset);
		print_hex32("writing flash address: ", a);
		asm volatile("clr r0 \n\tcom r0\n\tmov r1, r0\n\tcli");
		boot_flash_page_erase_and_write(a);
		asm volatile("sei\n\tclr __zero_reg__");
		if ((a & 256)) break;
		a |= 256;
	}
	media_unlock();
	return 1;
#else
	return 0;
#endif
}

static void media_receive_begin(uint32_t lba)
{
	// TODO: check media_rdonly, return error is read only mode
}

static void media_receive_chunk(uint32_t lba, uint8_t chunk)
{

#if 1
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
	uint8_t addr = lba;
	uint8_t i;
	uint8_t aa;
	uint32_t a;

	aa = chunk << 6;
	//print("fill tmp buffer @ ");
	//phex32(aa);
	//print("\n");
	for (i=0; i<32; i++) {
		uint16_t tmp;
		tmp = UEDATX;
		tmp |= (UEDATX << 8);
		//phex16(tmp);
		boot_flash_fill_temp_buffer(tmp, aa);
		aa += 2;
	}
	UEINTX = 0x6B;
	if ((chunk & 0x03) == 3) {
		a = ((uint32_t)(EPZ - 1 - addr) << 9) | ((uint16_t)(chunk & 4) << 6);
		//print("writing @ ");
		//phex32(a);
		//print("\n");
		asm volatile("clr r0 \n\tcom r0\n\tmov r1, r0");
		boot_flash_page_erase_and_write(a);
		asm volatile("clr __zero_reg__");
	}
#else
	UEINTX = 0x6B;
#endif
#endif
#if 0
	uint8_t addr = lba;
	asm volatile(
		"ldi	r18, 1"				"\n\t"
		"ldi	r19, 32"			"\n\t"
		"ldi	r31, %2"			"\n\t"
		"sub	r31, %3"			"\n\t"
		"mov	r30, %0"			"\n\t"
		"andi	r30, 7"				"\n\t"
		"swap	r30"				"\n\t"
		"lsl	r30"				"\n\t"
		"lsl	r30"				"\n\t"
		"rol	r31"				"\n\t"
		"rol	__zero_reg__"			"\n\t"
		"out	0x3B, __zero_reg__"		"\n\t"
	"L_%=_loooop:"					"\n\t"
		"ld	r0, X"				"\n\t"
		"ld	r1, X"				"\n\t"
		"call	0x1FF00"			"\n\t"
		"subi	r30, 254"			"\n\t"
		"subi	r19, 1"				"\n\t"
		"brne	L_%=_loooop"			"\n\t"
		"ldi	r18, 0x6B"			"\n\t"
		"sts	0x00E8, r18"			"\n\t"
		"mov	r18, %0"			"\n\t"
		"andi	r18, 3"				"\n\t"
		"cpi	r18, 3"				"\n\t"
		"brne	L_%=ennd"			"\n\t"
		"call	0x1FEB2"			"\n\t"
	"L_%=ennd:"					"\n\t"
		"clr	__zero_reg__"			"\n\t"
		: 
		: "r" (chunk), "x" (&UEDATX), "M" (EPZ - 1), "r" (addr)
		: "r0", "r18", "r19", "r30", "r31"
	);
#endif
}

static void media_receive_end(void)
{
}









