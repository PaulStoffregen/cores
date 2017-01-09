//#define USB_SERIAL_PRIVATE_INCLUDE
//#include "usb_mass_storage_debug.h"


//#include "pauls_ugly_debug.h"

#include "core_pins.h" // for delayMicroseconds

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


#define SPI_PORT	PORTB
#define SPI_DDR		DDRB
#define SPI_SS_PIN	0
#define SPI_SCLK_PIN	1
#define SPI_MOSI_PIN	2
#define SPI_MISO_PIN	3


#define SD_CMD_GO_IDLE_STATE		0x4095
#define SD_CMD_SEND_OP_COND		0x41FF
#define SD_CMD_SEND_IF_COND		0x4887
#define SD_CMD_SEND_CSD			0x49FF
#define SD_CMD_STOP_TRANSMISSION	0x4CFF
#define SD_CMD_READ_SINGLE_BLOCK	0x51FF
#define SD_CMD_READ_MULTIPLE_BLOCK	0x52FF
#define SD_CMD_WRITE_SINGLE_BLOCK	0x58FF
#define SD_CMD_WRITE_MULTIPLE_BLOCK	0x59FF
#define SD_ACMD_SEND_OP_COND		0x69FF
#define SD_CMD_APP_CMD			0x77FF
#define SD_CMD_READ_OCR			0x7AFF


inline void spi_write(uint8_t val)  __attribute__((always_inline));
inline void spi_write(uint8_t val)
{
	SPDR = val;
	while ((SPSR & (1<<SPIF)) == 0) /*wait*/ ;
}
inline uint8_t spi_xfer(uint8_t val)  __attribute__((always_inline));
inline uint8_t spi_xfer(uint8_t val)
{
	SPDR = val;
	while ((SPSR & (1<<SPIF)) == 0) /*wait*/ ;
	return SPDR;
}
void spi_ignore_bytes(uint8_t count)
{
	do {
		spi_write(0xFF);
	} while (--count);
}
inline void spi_select(void)
{
	SPI_PORT &= ~(1<<SPI_SS_PIN);
}
inline void sd_deselect(void)
{
	SPI_PORT |= (1<<SPI_SS_PIN);
	spi_write(0xFF);
}
uint8_t sd_command(uint16_t cmd, uint32_t parm)
{
	uint8_t n, r;
	union {
		struct {
			unsigned b1:8;
			unsigned b2:8;
			unsigned b3:8;
			unsigned b4:8;
		} byte;
		long i;
	} in;


	in.i = parm;
	phex(cmd >> 8);
	phex(in.byte.b4);
	phex(in.byte.b3);
	phex(in.byte.b2);
	phex(in.byte.b1);
	phex(cmd);
	print("\n");

	spi_select();
	spi_write(cmd >> 8);
	spi_write(in.byte.b4);
	spi_write(in.byte.b3);
	spi_write(in.byte.b2);
	spi_write(in.byte.b1);
	SPI_PORT |= (1<<SPI_MISO_PIN);
	r = spi_xfer(cmd);
	for (n=0; n < 9; n++) {
		if (r != 0xFF) break;
		r = spi_xfer(0xFF);
	}
	SPI_PORT &= ~(1<<SPI_MISO_PIN);
	return r;
}

uint8_t sd_wait_data(void)
{
	uint16_t count=0;
	uint8_t r;

	do {
		r = spi_xfer(0xFF);
		//if (r != 0xFF) return r;
		if (r == 0xFE) return r;
	} while (count++ < 20000);
	return r;
}


#ifndef USBSTATE
#define USBSTATE
#endif


#define READ_ONLY 0
volatile uint8_t media_rdonly USBSTATE;

#define MEDIA_PRESENT_MASK		0x10

#define MEDIA_STATE_NOCARD		0x00
#define MEDIA_STATE_INITIALIZING	0x01
#define MEDIA_STATE_READY		0x12
#define MEDIA_STATE_BUSY		0x14	// TODO: implement this!!!
#define MEDIA_STATE_CLAIMED		0x80	// media is claimed
#define MEDIA_STATE_CLAIMED_STATUS	0x40	// claimed status reported
#define MEDIA_STATE_CLAIMED_SENSE	0x20	// claimed scsi sense sent
volatile uint8_t media_state USBSTATE;

#define MEDIA_TYPE_SDv1			0x00
#define MEDIA_TYPE_SDv2			0x01
#define MEDIA_TYPE_SDHC			0x02
uint8_t media_type USBSTATE;


void media_restart(void)
{
	SPI_PORT |= (1<<SPI_SS_PIN);
	SPI_DDR |= ((1<<SPI_SS_PIN) | (1<<SPI_SCLK_PIN) | (1<<SPI_MOSI_PIN));
	SPCR = (1<<SPE) | (1<<MSTR);	// 8 Mbit/sec
	SPSR = (1<<SPI2X);
}


void media_init(void)
{
	media_restart();
	// TODO: initialize to unlocked condition
	media_state = MEDIA_STATE_NOCARD;
	media_type = MEDIA_TYPE_SDv1;
	media_rdonly = READ_ONLY;
	media_poll();
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
		//_delay_ms(100);
		mstate = media_state;
		//print("mstate = ");
		//phex(mstate);
		//phex(MEDIA_STATE_CLAIMED|MEDIA_STATE_CLAIMED_STATUS|MEDIA_STATE_CLAIMED_SENSE);
		//print("\n");
	}
	// a brief delay is needed here... but why?
	delayMicroseconds(12500);
	print("Media released by user program\n");
	media_init();
	media_rdonly = read_only_mode;
}


void media_poll(void)
{
	uint8_t i, r, mstate;

	mstate = media_state;
	//print("poll ");
	//phex(mstate);
	//print("\n");
	if (mstate & MEDIA_STATE_CLAIMED) {
		// never access the SD card while it's claimed by the user program!
		return;
	} else if (mstate == MEDIA_STATE_NOCARD) {
		media_type = MEDIA_TYPE_SDv1;
		spi_select();
		for (i=0; i<10; i++) {
			spi_write(0xFF);
		}
		r = sd_command(SD_CMD_GO_IDLE_STATE, 0); // CMD0
		sd_deselect();
		phex(r);
		print("\n");
		if ((r & 0xFE) == 0) {
			r = sd_command(SD_CMD_SEND_IF_COND, 0x1AA);
			phex(r);
			if ((r & 0xFE) == 0) {
				spi_write(0xFF);
				spi_write(0xFF);
				r = spi_xfer(0xFF);
				i = spi_xfer(0xFF);
				 phex(r);
				 phex(i);
				 print("\n");
				if (r == 1 && i == 0xAA) {
					print("Card is version 2.0\n");
					media_type = MEDIA_TYPE_SDv2;
				}
			}
			sd_deselect();
			media_state = MEDIA_STATE_INITIALIZING;
		}
	} else {
		//r = sd_command(SD_CMD_SEND_OP_COND, 0); // CMD1
		r = sd_command(SD_CMD_SEND_OP_COND, media_type ? 0x40000000 : 0); // CMD1
		//sd_command(SD_CMD_APP_CMD, 0);
		//r = sd_command(SD_ACMD_SEND_OP_COND, media_type ? 0x40000000 : 0); // ACMD41
		if (r) {
			phex(r);
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			phex(spi_xfer(0xFF));
			print("\n");

		}
		sd_deselect();
		phex(r);
		print("\n");
		if (r == 0) {
			if (mstate == MEDIA_STATE_INITIALIZING && media_type) {
				r = sd_command(SD_CMD_READ_OCR, 0);
				phex(r);
				if (r == 0) {
					r = spi_xfer(0xFF);
					if (r & 0x40) {
						print("Card is SDHC\n");
						media_type = MEDIA_TYPE_SDHC;
					}
					spi_write(0xFF);
					spi_write(0xFF);
					spi_write(0xFF);
				}
				sd_deselect();
			}
			media_state = MEDIA_STATE_READY;
		} else if (r & 0x80) {
			media_state = MEDIA_STATE_NOCARD;
		}
	}
	//return media_state;
}

inline uint32_t media_size(void)
{
	uint8_t r;

	if (media_state != MEDIA_STATE_READY) return 1;
	r = sd_command(SD_CMD_SEND_CSD, 0);
	if (r) goto error;
	r = sd_wait_data();
	if (r != 0xFE) goto error;
	r = spi_xfer(0xFF) & 0xC0;
	if (r == 0) {
		uint8_t c1, c2, c3, mult;
		uint16_t c_size;
		// Version 1.0 (standard capacity, up to 2 gigbytes)
		spi_ignore_bytes(4);
		mult = spi_xfer(0xFF);	// READ_BL_LEN
		 //phex(mult);
		mult &= 0x0F;
		c1 = spi_xfer(0xFF);	// C_SIZE[12:11]
		c2 = spi_xfer(0xFF);	// C_SIZE[10:3]
		c3 = spi_xfer(0xFF);	// C_SIZE[2:0]
		 //phex(c1);
		 //phex(c2);
		 //phex(c3);
		c1 &= 0x03;
		c_size = ((c1 << 10) | (c2 << 2) | (c3 >> 6)) + 1;
		c1 = spi_xfer(0xFF);	// C_SIZE_MULT[2:1]
		c2 = spi_xfer(0xFF);	// C_SIZE_MULT[0]
		 //phex(c1);
		 //phex(c2);
		 //print("\n");
		c1 &= 0x03;
		c2 &= 0x80;
		c1 = (c1 << 1) | (c2 >> 7);
		mult = mult + c1 - 7;
		spi_ignore_bytes(8);
		sd_deselect();
		return ((uint32_t)c_size << mult);
	} else if (r == 0x40) {
		// Version 2.0 (high capacity, more than 2 gigbytes)
		uint8_t c1, c2, c3;
		uint32_t size;
		spi_ignore_bytes(6);
		c1 = spi_xfer(0xFF); // C_SIZE
		c2 = spi_xfer(0xFF); // C_SIZE
		c3 = spi_xfer(0xFF); // C_SIZE
		spi_ignore_bytes(9);
		//phex(c1);
		//phex(c2);
		//phex(c3);
		//print("\n");
		c1 &= 0x3F;
		size = (((uint32_t)c1 << 16) | ((uint16_t)c2 << 8) | c3) + 1;
		size <<= 10;
		sd_deselect();
		return size;
	} else {
		goto error; // unknown CSD_STRUCTURE
	}
error:
	sd_deselect();
	media_state = MEDIA_STATE_NOCARD;
	return 1;
}


uint8_t media_read_sector(uint32_t lba, uint8_t *buffer)
{
	uint8_t r, i, ret=0;

	while (!media_lock()) /*wait*/ ;
	if (media_type != MEDIA_TYPE_SDHC) lba = (lba << 9);
	r = sd_command(SD_CMD_READ_SINGLE_BLOCK, lba);
	if (r) {
		// TODO: check for errors...
		print("User Read Error, r=");
		phex(r);
		print("\n");
		goto done;
	}
	print("User Read OK, lba=");
	phex32(lba >> 9);
	print("\n");
	if (sd_wait_data() != 0xFE) {
		print("User Read Error, bad token\n");
		goto done;
	}
	for (i=0; i<64; i++) {
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
		*buffer++ = spi_xfer(0xFF);
	}
	ret = 1;
	spi_write(0xFF);	// ignore CRC
	spi_write(0xFF);
done:
	sd_deselect();
	media_unlock();
	return ret;
}


static void media_send_begin(uint32_t lba)
{
	uint8_t r;

	if (media_type != MEDIA_TYPE_SDHC) lba = (lba << 9);
	r = sd_command(SD_CMD_READ_MULTIPLE_BLOCK, lba);
	if (r) {
		// TODO: check for errors...
		print("Read Error, r=");
		phex(r);
		print("\n");
	} else {
		print("Read OK\n");
	}
}

static void media_send_chunk(uint32_t lba, uint8_t chunk)
{
	uint8_t i;

	if (chunk == 0) {
		i = sd_wait_data();
		//phex(i);
		if (i != 0xFE) {
			print("Read error, token=");
			phex(i);
			print("\n");
		}
	}

	for (i=0; i<8; i++) {
		// TODO: asm optimization
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
		UEDATX = spi_xfer(0xFF);
	}
	UEINTX = 0x3A;

	if (chunk == 7) {
		spi_write(0xFF);
		spi_write(0xFF);
	}
	//print(".");
}

static void media_send_end(void)
{
	//uint8_t r;

	/* r = */ sd_command(SD_CMD_STOP_TRANSMISSION, 0);
	// TODO: proper handling of stop transaction.....
	// but what is the proper way?	Older cards stop instantly,
	// but newer ones spew 1 or 2 bytes of garbage, then maybe
	// 0xFF's until the ok (0) response.  What a mess!
	spi_write(0xFF);
	spi_write(0xFF);
	spi_write(0xFF);
	spi_write(0xFF);
	spi_write(0xFF);
	spi_write(0xFF);
	spi_write(0xFF);
	spi_write(0xFF);
	//print("\rr=");
	//phex(r);
#if 0
	if (r) {
		print("Stop Transmission Error, r=");
		phex(r);
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		print("\n");
		// handle errors
	} else {
		print("Stop Transmission OK, r=");
		phex(r);
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		phex(spi_xfer(0xFF));
		print("\n");

	}
	do {
		r = spi_xfer(0xFF);
		//phex(r);
	} while (r == 0);
#endif
	sd_deselect();
	//print("\n");
}











uint8_t media_write_sector(uint32_t lba, const uint8_t *buffer)
{
	uint8_t r, i, ret=0;

	while (!media_lock()) /*wait*/ ;
	if (media_type != MEDIA_TYPE_SDHC) lba = (lba << 9);

	r = sd_command(SD_CMD_WRITE_SINGLE_BLOCK, lba);
	if (r) {
		// TODO: check for errors...
		print("User Write Error, r=");
		phex(r);
		print("\n");
		goto done;
	}
	print("User Write OK, lba=");
	phex32(lba >> 9);
	print("\n");
	spi_write(0xFE);  // start block token
	for (i=0; i<64; i++) {
		spi_write(*buffer++);
		spi_write(*buffer++);
		spi_write(*buffer++);
		spi_write(*buffer++);
		spi_write(*buffer++);
		spi_write(*buffer++);
		spi_write(*buffer++);
		spi_write(*buffer++);
	}
	spi_write(0xFF);	// CRC
	spi_write(0xFF);
	do {
		r = spi_xfer(0xFF);	// wait for busy
		//phex(r);
	} while (r != 0xFF);
	ret = 1;
done:
	sd_deselect();
	media_unlock();
	return ret;
}


static void media_receive_begin(uint32_t lba)
{
	uint8_t r;

	// TODO: check media_rdonly, return error is read only mode
	if (media_type != MEDIA_TYPE_SDHC) lba = (lba << 9);
	sd_command(SD_CMD_WRITE_MULTIPLE_BLOCK, lba);
	if (r) {
		// TODO: check for errors...
	}
}


static void media_receive_chunk(uint32_t lba, uint8_t chunk)
{
	uint8_t i, r;

	if (chunk == 0) {
		spi_write(0xFC);
	}
	for (i=0; i<8; i++) {
		// TODO: asm optimization
		spi_write(UEDATX);
		spi_write(UEDATX);
		spi_write(UEDATX);
		spi_write(UEDATX);
		spi_write(UEDATX);
		spi_write(UEDATX);
		spi_write(UEDATX);
		spi_write(UEDATX);
	}
	UEINTX = 0x6B;

	print(".");
	if (chunk == 7) {
		spi_write(0xFF);
		spi_write(0xFF);
		do {
			r = spi_xfer(0xFF);
			phex(r);
		} while (r != 0xFF);
	}
}

static void media_receive_end(void)
{
	uint8_t r;

	print("stop");
	spi_write(0xFD);
	spi_write(0xFF);
	do {
		// TODO: this can wait for a long time... would be
		// much better to create a busy media state and
		// return from the ISR, but then need to deal with
		// it everywhere else!
		r = spi_xfer(0xFF);
		phex(r);
	} while (r != 0xFF);

	sd_deselect();
	print("\n");
}


