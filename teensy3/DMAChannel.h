#ifndef DMAChannel_h_
#define DMAChannel_h_

#include "kinetis.h"

// This code is a work-in-progress.  It's incomplete and not usable yet...
//
// http://forum.pjrc.com/threads/25778-Could-there-be-something-like-an-ISR-template-function/page3


// known libraries with DMA usage (in need of porting to this new scheme):
//
// https://github.com/PaulStoffregen/Audio
// https://github.com/PaulStoffregen/OctoWS2811
// https://github.com/pedvide/ADC
// https://github.com/duff2013/SerialEvent
// https://github.com/pixelmatix/SmartMatrix
// https://github.com/crteensy/DmaSpi

#ifdef __cplusplus

#define DMACHANNEL_HAS_BEGIN
#define DMACHANNEL_HAS_BOOLEAN_CTOR

class DMABaseClass {
public:
	typedef struct __attribute__((packed)) {
		volatile const void * volatile SADDR;
		int16_t SOFF;
		union { uint16_t ATTR;
			struct { uint8_t ATTR_DST; uint8_t ATTR_SRC; }; };
		union { uint32_t NBYTES; uint32_t NBYTES_MLNO;
			uint32_t NBYTES_MLOFFNO; uint32_t NBYTES_MLOFFYES; };
		int32_t SLAST;
		volatile void * volatile DADDR;
		int16_t DOFF;
		union { volatile uint16_t CITER;
			volatile uint16_t CITER_ELINKYES; volatile uint16_t CITER_ELINKNO; };
		int32_t DLASTSGA;
		volatile uint16_t CSR;
		union { volatile uint16_t BITER;
			volatile uint16_t BITER_ELINKYES; volatile uint16_t BITER_ELINKNO; };
	} TCD_t;
	TCD_t *TCD;

	/***************************************/
	/**    Data Transfer                  **/
	/***************************************/

	// Use a single variable as the data source.  Typically a register
	// for receiving data from one of the hardware peripherals is used.
	void source(volatile const signed char &p) { source(*(volatile const uint8_t *)&p); }
	void source(volatile const unsigned char &p) {
		TCD->SADDR = &p;
		TCD->SOFF = 0;
		TCD->ATTR_SRC = 0;
		if ((uint32_t)&p < 0x40000000 || TCD->NBYTES == 0) TCD->NBYTES = 1;
		TCD->SLAST = 0;
	}
	void source(volatile const signed short &p) { source(*(volatile const uint16_t *)&p); }
	void source(volatile const unsigned short &p) {
		TCD->SADDR = &p;
		TCD->SOFF = 0;
		TCD->ATTR_SRC = 1;
		if ((uint32_t)&p < 0x40000000 || TCD->NBYTES == 0) TCD->NBYTES = 2;
		TCD->SLAST = 0;
	}
	void source(volatile const signed int &p) { source(*(volatile const uint32_t *)&p); }
	void source(volatile const unsigned int &p) { source(*(volatile const uint32_t *)&p); }
	void source(volatile const signed long &p) { source(*(volatile const uint32_t *)&p); }
	void source(volatile const unsigned long &p) {
		TCD->SADDR = &p;
		TCD->SOFF = 0;
		TCD->ATTR_SRC = 2;
		if ((uint32_t)&p < 0x40000000 || TCD->NBYTES == 0) TCD->NBYTES = 4;
		TCD->SLAST = 0;
	}

	// Use a buffer (array of data) as the data source.  Typically a
	// buffer for transmitting data is used.
	void sourceBuffer(volatile const signed char p[], unsigned int len) {
		sourceBuffer((volatile const uint8_t *)p, len); }
	void sourceBuffer(volatile const unsigned char p[], unsigned int len) {
		TCD->SADDR = p;
		TCD->SOFF = 1;
		TCD->ATTR_SRC = 0;
		TCD->NBYTES = 1;
		TCD->SLAST = -len;
		TCD->BITER = len;
		TCD->CITER = len;
	}
	void sourceBuffer(volatile const signed short p[], unsigned int len) {
		sourceBuffer((volatile const uint16_t *)p, len); }
	void sourceBuffer(volatile const unsigned short p[], unsigned int len) {
		TCD->SADDR = p;
		TCD->SOFF = 2;
		TCD->ATTR_SRC = 1;
		TCD->NBYTES = 2;
		TCD->SLAST = -len;
		TCD->BITER = len / 2;
		TCD->CITER = len / 2;
	}
	void sourceBuffer(volatile const signed int p[], unsigned int len) {
		sourceBuffer((volatile const uint32_t *)p, len); }
	void sourceBuffer(volatile const unsigned int p[], unsigned int len) {
		sourceBuffer((volatile const uint32_t *)p, len); }
	void sourceBuffer(volatile const signed long p[], unsigned int len) {
		sourceBuffer((volatile const uint32_t *)p, len); }
	void sourceBuffer(volatile const unsigned long p[], unsigned int len) {
		TCD->SADDR = p;
		TCD->SOFF = 4;
		TCD->ATTR_SRC = 2;
		TCD->NBYTES = 4;
		TCD->SLAST = -len;
		TCD->BITER = len / 4;
		TCD->CITER = len / 4;
	}

	// Use a circular buffer as the data source
	void sourceCircular(volatile const signed char p[], unsigned int len) {
		sourceCircular((volatile const uint8_t *)p, len); }
	void sourceCircular(volatile const unsigned char p[], unsigned int len) {
		TCD->SADDR = p;
		TCD->SOFF = 1;
		TCD->ATTR_SRC = ((31 - __builtin_clz(len)) << 3);
		TCD->NBYTES = 1;
		TCD->SLAST = 0;
		TCD->BITER = len;
		TCD->CITER = len;
	}
	void sourceCircular(volatile const signed short p[], unsigned int len) {
		sourceCircular((volatile const uint16_t *)p, len); }
	void sourceCircular(volatile const unsigned short p[], unsigned int len) {
		TCD->SADDR = p;
		TCD->SOFF = 2;
		TCD->ATTR_SRC = ((31 - __builtin_clz(len)) << 3) | 1;
		TCD->NBYTES = 2;
		TCD->SLAST = 0;
		TCD->BITER = len / 2;
		TCD->CITER = len / 2;
	}
	void sourceCircular(volatile const signed int p[], unsigned int len) {
		sourceCircular((volatile const uint32_t *)p, len); }
	void sourceCircular(volatile const unsigned int p[], unsigned int len) {
		sourceCircular((volatile const uint32_t *)p, len); }
	void sourceCircular(volatile const signed long p[], unsigned int len) {
		sourceCircular((volatile const uint32_t *)p, len); }
	void sourceCircular(volatile const unsigned long p[], unsigned int len) {
		TCD->SADDR = p;
		TCD->SOFF = 4;
		TCD->ATTR_SRC = ((31 - __builtin_clz(len)) << 3) | 2;
		TCD->NBYTES = 4;
		TCD->SLAST = 0;
		TCD->BITER = len / 4;
		TCD->CITER = len / 4;
	}

	// Use a single variable as the data destination.  Typically a register
	// for transmitting data to one of the hardware peripherals is used.
	void destination(volatile signed char &p) { destination(*(volatile uint8_t *)&p); }
	void destination(volatile unsigned char &p) {
		TCD->DADDR = &p;
		TCD->DOFF = 0;
		TCD->ATTR_DST = 0;
		if ((uint32_t)&p < 0x40000000 || TCD->NBYTES == 0) TCD->NBYTES = 1;
		TCD->DLASTSGA = 0;
	}
	void destination(volatile signed short &p) { destination(*(volatile uint16_t *)&p); }
	void destination(volatile unsigned short &p) {
		TCD->DADDR = &p;
		TCD->DOFF = 0;
		TCD->ATTR_DST = 1;
		if ((uint32_t)&p < 0x40000000 || TCD->NBYTES == 0) TCD->NBYTES = 2;
		TCD->DLASTSGA = 0;
	}
	void destination(volatile signed int &p) { destination(*(volatile uint32_t *)&p); }
	void destination(volatile unsigned int &p) { destination(*(volatile uint32_t *)&p); }
	void destination(volatile signed long &p) { destination(*(volatile uint32_t *)&p); }
	void destination(volatile unsigned long &p) {
		TCD->DADDR = &p;
		TCD->DOFF = 0;
		TCD->ATTR_DST = 2;
		if ((uint32_t)&p < 0x40000000 || TCD->NBYTES == 0) TCD->NBYTES = 4;
		TCD->DLASTSGA = 0;
	}

	// Use a buffer (array of data) as the data destination.  Typically a
	// buffer for receiving data is used.
	void destinationBuffer(volatile signed char p[], unsigned int len) {
		destinationBuffer((volatile uint8_t *)p, len); }
	void destinationBuffer(volatile unsigned char p[], unsigned int len) {
		TCD->DADDR = p;
		TCD->DOFF = 1;
		TCD->ATTR_DST = 0;
		TCD->NBYTES = 1;
		TCD->DLASTSGA = -len;
		TCD->BITER = len;
		TCD->CITER = len;
	}
	void destinationBuffer(volatile signed short p[], unsigned int len) {
		destinationBuffer((volatile uint16_t *)p, len); }
	void destinationBuffer(volatile unsigned short p[], unsigned int len) {
		TCD->DADDR = p;
		TCD->DOFF = 2;
		TCD->ATTR_DST = 1;
		TCD->NBYTES = 2;
		TCD->DLASTSGA = -len;
		TCD->BITER = len / 2;
		TCD->CITER = len / 2;
	}
	void destinationBuffer(volatile signed int p[], unsigned int len) {
		destinationBuffer((volatile uint32_t *)p, len); }
	void destinationBuffer(volatile unsigned int p[], unsigned int len) {
		destinationBuffer((volatile uint32_t *)p, len); }
	void destinationBuffer(volatile signed long p[], unsigned int len) {
		destinationBuffer((volatile uint32_t *)p, len); }
	void destinationBuffer(volatile unsigned long p[], unsigned int len) {
		TCD->DADDR = p;
		TCD->DOFF = 4;
		TCD->ATTR_DST = 2;
		TCD->NBYTES = 4;
		TCD->DLASTSGA = -len;
		TCD->BITER = len / 4;
		TCD->CITER = len / 4;
	}

	// Use a circular buffer as the data destination
	void destinationCircular(volatile signed char p[], unsigned int len) {
		destinationCircular((volatile uint8_t *)p, len); }
	void destinationCircular(volatile unsigned char p[], unsigned int len) {
		TCD->DADDR = p;
		TCD->DOFF = 1;
		TCD->ATTR_DST = ((31 - __builtin_clz(len)) << 3);
		TCD->NBYTES = 1;
		TCD->DLASTSGA = 0;
		TCD->BITER = len;
		TCD->CITER = len;
	}
	void destinationCircular(volatile signed short p[], unsigned int len) {
		destinationCircular((volatile uint16_t *)p, len); }
	void destinationCircular(volatile unsigned short p[], unsigned int len) {
		TCD->DADDR = p;
		TCD->DOFF = 2;
		TCD->ATTR_DST = ((31 - __builtin_clz(len)) << 3) | 1;
		TCD->NBYTES = 2;
		TCD->DLASTSGA = 0;
		TCD->BITER = len / 2;
		TCD->CITER = len / 2;
	}
	void destinationCircular(volatile signed int p[], unsigned int len) {
		destinationCircular((volatile uint32_t *)p, len); }
	void destinationCircular(volatile unsigned int p[], unsigned int len) {
		destinationCircular((volatile uint32_t *)p, len); }
	void destinationCircular(volatile signed long p[], unsigned int len) {
		destinationCircular((volatile uint32_t *)p, len); }
	void destinationCircular(volatile unsigned long p[], unsigned int len) {
		TCD->DADDR = p;
		TCD->DOFF = 4;
		TCD->ATTR_DST = ((31 - __builtin_clz(len)) << 3) | 2;
		TCD->NBYTES = 4;
		TCD->DLASTSGA = 0;
		TCD->BITER = len / 4;
		TCD->CITER = len / 4;
	}

	/*************************************************/
	/**    Quantity of Data to Transfer             **/
	/*************************************************/

	// Set the data size used for each triggered transfer
	void transferSize(unsigned int len) {
		if (len == 4) {
			TCD->NBYTES = 4;
			if (TCD->SOFF != 0) TCD->SOFF = 4;
			if (TCD->DOFF != 0) TCD->DOFF = 4;
			TCD->ATTR = (TCD->ATTR & 0xF8F8) | 0x0202;
		} else if (len == 2) {
			TCD->NBYTES = 2;
			if (TCD->SOFF != 0) TCD->SOFF = 2;
			if (TCD->DOFF != 0) TCD->DOFF = 2;
			TCD->ATTR = (TCD->ATTR & 0xF8F8) | 0x0101;
		} else {
			TCD->NBYTES = 1;
			if (TCD->SOFF != 0) TCD->SOFF = 1;
			if (TCD->DOFF != 0) TCD->DOFF = 1;
			TCD->ATTR = TCD->ATTR & 0xF8F8;
		}
	}

	// Set the number of transfers (number of triggers until complete)
	void transferCount(unsigned int len) {
		if (len > 32767) return;
		if (len >= 512) {
			TCD->BITER = len;
			TCD->CITER = len;
		} else {
			TCD->BITER = (TCD->BITER & 0xFE00) | len;
			TCD->CITER = (TCD->CITER & 0xFE00) | len;
		}
	}

	/*************************************************/
	/**    Special Options / Features               **/
	/*************************************************/

	void interruptAtCompletion(void) {
		TCD->CSR |= DMA_TCD_CSR_INTMAJOR;
	}

	void interruptAtHalf(void) {
		TCD->CSR |= DMA_TCD_CSR_INTHALF;
	}

	void disableOnCompletion(void) {
		TCD->CSR |= DMA_TCD_CSR_DREQ;
	}

	void replaceSettingsOnCompletion(const DMABaseClass &settings) {
		TCD->DLASTSGA = (int32_t)(settings.TCD);
		TCD->CSR &= ~DMA_TCD_CSR_DONE;
		TCD->CSR |= DMA_TCD_CSR_ESG;
	}

protected:
	// users should not be able to create instances of DMABaseClass, which
	// require the inheriting class to initialize the TCD pointer.
	DMABaseClass() {}

	static inline void copy_tcd(TCD_t *dst, const TCD_t *src) {
		const uint32_t *p = (const uint32_t *)src;
		uint32_t *q = (uint32_t *)dst;
		uint32_t t1, t2, t3, t4;
		t1 = *p++; t2 = *p++; t3 = *p++; t4 = *p++;
		*q++ = t1; *q++ = t2; *q++ = t3; *q++ = t4;
		t1 = *p++; t2 = *p++; t3 = *p++; t4 = *p++;
		*q++ = t1; *q++ = t2; *q++ = t3; *q++ = t4;
	}
};


// DMASetting represents settings stored only in memory, which can be
// applied to any DMA channel.

class DMASetting : public DMABaseClass {
public:
	DMASetting() {
		TCD = &tcddata;
	}
	DMASetting(const DMASetting &c) {
		TCD = &tcddata;
		*this = c;
	}
	DMASetting(const DMABaseClass &c) {
		TCD = &tcddata;
		*this = c;
	}
	DMASetting & operator = (const DMABaseClass &rhs) {
		copy_tcd(TCD, rhs.TCD);
		return *this;
	}
private:
	TCD_t tcddata __attribute__((aligned(32)));
};


// DMAChannel reprents an actual DMA channel and its current settings

class DMAChannel : public DMABaseClass {
public:
	/*************************************************/
	/**    Channel Allocation                       **/
	/*************************************************/

	DMAChannel() {
		begin();
	}
	DMAChannel(const DMAChannel &c) {
		TCD = c.TCD;
		channel = c.channel;
	}
	DMAChannel(const DMASetting &c) {
		begin();
		copy_tcd(TCD, c.TCD);
	}
	DMAChannel(bool allocate) {
		if (allocate) begin();
	}
	DMAChannel & operator = (const DMAChannel &rhs) {
		if (channel != rhs.channel) {
			release();
			TCD = rhs.TCD;
			channel = rhs.channel;
		}
		return *this;
	}
	DMAChannel & operator = (const DMASetting &rhs) {
		copy_tcd(TCD, rhs.TCD);
		return *this;
	}
	~DMAChannel() {
		release();
	}
	void begin(bool force_initialization = false);
private:
	void release(void);

public:
	/***************************************/
	/**    Triggering                     **/
	/***************************************/

	// Triggers cause the DMA channel to actually move data.  Each
	// trigger moves a single data unit, which is typically 8, 16 or
	// 32 bits.  If a channel is configured for 200 transfers

	// Use a hardware trigger to make the DMA channel run
	void triggerAtHardwareEvent(uint8_t source) {
		volatile uint8_t *mux;
		mux = (volatile uint8_t *)&(DMAMUX0_CHCFG0) + channel;
		*mux = 0;
		*mux = (source & 63) | DMAMUX_ENABLE;
	}

	// Use another DMA channel as the trigger, causing this
	// channel to trigger after each transfer is makes, except
	// the its last transfer.  This effectively makes the 2
	// channels run in parallel until the last transfer
	void triggerAtTransfersOf(DMABaseClass &ch) {
		ch.TCD->BITER = (ch.TCD->BITER & ~DMA_TCD_BITER_ELINKYES_LINKCH_MASK)
		  | DMA_TCD_BITER_ELINKYES_LINKCH(channel) | DMA_TCD_BITER_ELINKYES_ELINK;
		ch.TCD->CITER = ch.TCD->BITER ;
	}

	// Use another DMA channel as the trigger, causing this
	// channel to trigger when the other channel completes.
	void triggerAtCompletionOf(DMABaseClass &ch) {
		ch.TCD->CSR = (ch.TCD->CSR & ~(DMA_TCD_CSR_MAJORLINKCH_MASK|DMA_TCD_CSR_DONE))
		  | DMA_TCD_CSR_MAJORLINKCH(channel) | DMA_TCD_CSR_MAJORELINK;
	}

	// Cause this DMA channel to be continuously triggered, so
	// it will move data as rapidly as possible, without waiting.
	// Normally this would be used with disableOnCompletion().
	void triggerContinuously(void) {
		volatile uint8_t *mux = (volatile uint8_t *)&DMAMUX0_CHCFG0;
		mux[channel] = 0;
#if DMAMUX_NUM_SOURCE_ALWAYS >= DMA_NUM_CHANNELS
		mux[channel] = DMAMUX_SOURCE_ALWAYS0 + channel;	
#else
		// search for an unused "always on" source
		unsigned int i = DMAMUX_SOURCE_ALWAYS0;
		for (i = DMAMUX_SOURCE_ALWAYS0;
		  i < DMAMUX_SOURCE_ALWAYS0 + DMAMUX_NUM_SOURCE_ALWAYS; i++) {
			unsigned int ch;
			for (ch=0; ch < DMA_NUM_CHANNELS; ch++) {
				if (mux[ch] == i) break;
			}
			if (ch >= DMA_NUM_CHANNELS) {
				mux[channel] = (i | DMAMUX_ENABLE);
				return;
			}
		}
#endif
	}

	// Manually trigger the DMA channel.
	void triggerManual(void) {
		DMA_SSRT = channel;
	}


	/***************************************/
	/**    Interrupts                     **/
	/***************************************/

	// An interrupt routine can be run when the DMA channel completes
	// the entire transfer, and also optionally when half of the
	// transfer is completed.
	void attachInterrupt(void (*isr)(void)) {
		_VectorsRam[channel + IRQ_DMA_CH0 + 16] = isr;
		NVIC_ENABLE_IRQ(IRQ_DMA_CH0 + channel);
	}

	void detachInterrupt(void) {
		NVIC_DISABLE_IRQ(IRQ_DMA_CH0 + channel);
	}

	void clearInterrupt(void) {
		DMA_CINT = channel;
	}


	/***************************************/
	/**    Enable / Disable               **/
	/***************************************/

	void enable(void) {
		DMA_SERQ = channel;
	}
	void disable(void) {
		DMA_CERQ = channel;
	}

	/***************************************/
	/**    Status                         **/
	/***************************************/

	bool complete(void) {
		if (TCD->CSR & DMA_TCD_CSR_DONE) return true;
		return false;
	}
	void clearComplete(void) {
		DMA_CDNE = channel;
	}
	bool error(void) {
		if (DMA_ERR & (1<<channel)) return true;
		return false;
	}
	void clearError(void) {
		DMA_CERR = channel;
	}
	void * sourceAddress(void) {
		return (void *)(TCD->SADDR);
	}
	void * destinationAddress(void) {
		return (void *)(TCD->DADDR);
	}

	/***************************************/
	/**    Direct Hardware Access         **/
	/***************************************/

	// For complex and unusual configurations not possible with the above
	// functions, the Transfer Control Descriptor (TCD) and channel number
	// can be used directly.  This leads to less portable and less readable
	// code, but direct control of all parameters is possible.
	uint8_t channel;
	// TCD is accessible due to inheritance from DMABaseClass

/* usage cases:

************************
OctoWS2811:
************************

        // enable clocks to the DMA controller and DMAMUX
        SIM_SCGC7 |= SIM_SCGC7_DMA;
        SIM_SCGC6 |= SIM_SCGC6_DMAMUX;
        DMA_CR = 0;
        DMA_CERQ = 1;
        DMA_CERQ = 2;
        DMA_CERQ = 3;

        // DMA channel #1 sets WS2811 high at the beginning of each cycle
         DMA_TCD1_SADDR = &ones;
         DMA_TCD1_SOFF = 0;
         DMA_TCD1_ATTR = DMA_TCD_ATTR_SSIZE(0) | DMA_TCD_ATTR_DSIZE(0);
         DMA_TCD1_NBYTES_MLNO = 1;
         DMA_TCD1_SLAST = 0;
         DMA_TCD1_DADDR = &GPIOD_PSOR;
         DMA_TCD1_DOFF = 0;
         DMA_TCD1_CITER_ELINKNO = bufsize;
         DMA_TCD1_DLASTSGA = 0;
         DMA_TCD1_CSR = DMA_TCD_CSR_DREQ;
         DMA_TCD1_BITER_ELINKNO = bufsize;
	dma1.source(ones);
	dma1.destination(GPIOD_PSOR);
	dma1.size(1);
	dma1.count(bufsize);
	dma1.disableOnCompletion();

        // DMA channel #2 writes the pixel data at 20% of the cycle
         DMA_TCD2_SADDR = frameBuffer;
         DMA_TCD2_SOFF = 1;
         DMA_TCD2_ATTR = DMA_TCD_ATTR_SSIZE(0) | DMA_TCD_ATTR_DSIZE(0);
         DMA_TCD2_NBYTES_MLNO = 1;
         DMA_TCD2_SLAST = -bufsize;
         DMA_TCD2_DADDR = &GPIOD_PDOR;
         DMA_TCD2_DOFF = 0;
         DMA_TCD2_CITER_ELINKNO = bufsize;
         DMA_TCD2_DLASTSGA = 0;
         DMA_TCD2_CSR = DMA_TCD_CSR_DREQ;
         DMA_TCD2_BITER_ELINKNO = bufsize;
	dma2.source(frameBuffer, sizeof(frameBuffer));
	dma2.destination(GPIOD_PDOR);
	dma2.size(1);
	dma2.count(bufsize);
	dma2.disableOnCompletion();

        // DMA channel #3 clear all the pins low at 48% of the cycle
        DMA_TCD3_SADDR = &ones;
        DMA_TCD3_SOFF = 0;
        DMA_TCD3_ATTR = DMA_TCD_ATTR_SSIZE(0) | DMA_TCD_ATTR_DSIZE(0);
        DMA_TCD3_NBYTES_MLNO = 1;
        DMA_TCD3_SLAST = 0;
        DMA_TCD3_DADDR = &GPIOD_PCOR;
        DMA_TCD3_DOFF = 0;
        DMA_TCD3_CITER_ELINKNO = bufsize;
        DMA_TCD3_DLASTSGA = 0;
        DMA_TCD3_CSR = DMA_TCD_CSR_DREQ | DMA_TCD_CSR_INTMAJOR;
        DMA_TCD3_BITER_ELINKNO = bufsize;
	dma3.source(ones);
	dma3.destination(GPIOD_PCOR);
	dma3.size(1);
	dma3.count(bufsize);
	dma3.disableOnCompletion();

************************
Audio, DAC
************************

        DMA_CR = 0;
        DMA_TCD4_SADDR = dac_buffer;
        DMA_TCD4_SOFF = 2;
        DMA_TCD4_ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
        DMA_TCD4_NBYTES_MLNO = 2;
        DMA_TCD4_SLAST = -sizeof(dac_buffer);
        DMA_TCD4_DADDR = &DAC0_DAT0L;
        DMA_TCD4_DOFF = 0;
        DMA_TCD4_CITER_ELINKNO = sizeof(dac_buffer) / 2;
        DMA_TCD4_DLASTSGA = 0;
        DMA_TCD4_BITER_ELINKNO = sizeof(dac_buffer) / 2;
        DMA_TCD4_CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;
        DMAMUX0_CHCFG4 = DMAMUX_DISABLE;
        DMAMUX0_CHCFG4 = DMAMUX_SOURCE_PDB | DMAMUX_ENABLE;

************************
Audio, I2S
************************

        DMA_CR = 0;
        DMA_TCD0_SADDR = i2s_tx_buffer;
        DMA_TCD0_SOFF = 2;
        DMA_TCD0_ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
        DMA_TCD0_NBYTES_MLNO = 2;
        DMA_TCD0_SLAST = -sizeof(i2s_tx_buffer);
        DMA_TCD0_DADDR = &I2S0_TDR0;
        DMA_TCD0_DOFF = 0;
        DMA_TCD0_CITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
        DMA_TCD0_DLASTSGA = 0;
        DMA_TCD0_BITER_ELINKNO = sizeof(i2s_tx_buffer) / 2;
        DMA_TCD0_CSR = DMA_TCD_CSR_INTHALF | DMA_TCD_CSR_INTMAJOR;

        DMAMUX0_CHCFG0 = DMAMUX_DISABLE;
        DMAMUX0_CHCFG0 = DMAMUX_SOURCE_I2S0_TX | DMAMUX_ENABLE;

************************
ADC lib, Pedro Villanueva
************************

    DMA_CR = 0; // normal mode of operation

    *DMAMUX0_CHCFG = DMAMUX_DISABLE; // disable before changing

    *DMA_TCD_ATTR = DMA_TCD_ATTR_SSIZE(DMA_TCD_ATTR_SIZE_16BIT) |
                  DMA_TCD_ATTR_DSIZE(DMA_TCD_ATTR_SIZE_16BIT) |
                  DMA_TCD_ATTR_DMOD(4); // src and dst data is 16 bit (2 bytes), buffer size 2^^4 bytes = 8 values
    *DMA_TCD_NBYTES_MLNO = 2; // Minor Byte Transfer Count 2 bytes = 16 bits (we transfer 2 bytes each minor loop)

    *DMA_TCD_SADDR = ADC_RA; // source address
    *DMA_TCD_SOFF = 0; // don't change the address when minor loop finishes
    *DMA_TCD_SLAST = 0; // don't change src address after major loop completes

    *DMA_TCD_DADDR = elems; // destination address
    *DMA_TCD_DOFF = 2; // increment 2 bytes each minor loop
    *DMA_TCD_DLASTSGA = 0; // modulus feature takes care of going back to first element

    *DMA_TCD_CITER_ELINKNO = 1; // Current Major Iteration Count with channel linking disabled
    *DMA_TCD_BITER_ELINKNO = 1; // Starting Major Iteration Count with channel linking disabled

    *DMA_TCD_CSR = DMA_TCD_CSR_INTMAJOR; // Control and status: interrupt when major counter is complete

    DMA_CERQ = DMA_CERQ_CERQ(DMA_channel); // clear all past request
    DMA_CINT = DMA_channel; // clear interrupts

    uint8_t DMAMUX_SOURCE_ADC = DMAMUX_SOURCE_ADC0;
    if(ADC_number==1){
        DMAMUX_SOURCE_ADC = DMAMUX_SOURCE_ADC1;
    }
    *DMAMUX0_CHCFG = DMAMUX_SOURCE_ADC | DMAMUX_ENABLE; // enable mux and set channel DMA_channel to ADC0

    DMA_SERQ = DMA_SERQ_SERQ(DMA_channel); // enable DMA request
    NVIC_ENABLE_IRQ(IRQ_DMA_CH); // enable interrupts

************************
SmartMatrix
************************

    // enable minor loop mapping so addresses can get reset after minor loops
    DMA_CR = 1 << 7;

    // DMA channel #0 - on latch rising edge, read address from fixed address temporary buffer, and output address on GPIO
    // using combo of writes to set+clear registers, to only modify the address pins and not other GPIO pins
    // address temporary buffer is refreshed before each DMA trigger (by DMA channel #2)
    // only use single major loop, never disable channel
#define ADDRESS_ARRAY_REGISTERS_TO_UPDATE   2
    DMA_TCD0_SADDR = &gpiosync.gpio_pcor;
    DMA_TCD0_SOFF = (int)&gpiosync.gpio_psor - (int)&gpiosync.gpio_pcor;
    DMA_TCD0_SLAST = (ADDRESS_ARRAY_REGISTERS_TO_UPDATE * ((int)&ADDX_GPIO_CLEAR_REGISTER - (int)&ADDX_GPIO_SET_REGISTER));
    DMA_TCD0_ATTR = DMA_TCD_ATTR_SSIZE(2) | DMA_TCD_ATTR_DSIZE(2);
    // Destination Minor Loop Offset Enabled - transfer appropriate number of bytes per minor loop, and put DADDR back to original value when minor loop is complete
    // Source Minor Loop Offset Enabled - source buffer is same size and offset as destination so values reset after each minor loop
    DMA_TCD0_NBYTES_MLOFFYES = DMA_TCD_NBYTES_SMLOE | DMA_TCD_NBYTES_DMLOE |
                               ((ADDRESS_ARRAY_REGISTERS_TO_UPDATE * ((int)&ADDX_GPIO_CLEAR_REGISTER - (int)&ADDX_GPIO_SET_REGISTER)) << 10) |
                               (ADDRESS_ARRAY_REGISTERS_TO_UPDATE * sizeof(gpiosync.gpio_psor));
    // start on higher value of two registers, and make offset decrement to avoid negative number in NBYTES_MLOFFYES (TODO: can switch order by masking negative offset)
    DMA_TCD0_DADDR = &ADDX_GPIO_CLEAR_REGISTER;
    // update destination address so the second update per minor loop is ADDX_GPIO_SET_REGISTER
    DMA_TCD0_DOFF = (int)&ADDX_GPIO_SET_REGISTER - (int)&ADDX_GPIO_CLEAR_REGISTER;
    DMA_TCD0_DLASTSGA = (ADDRESS_ARRAY_REGISTERS_TO_UPDATE * ((int)&ADDX_GPIO_CLEAR_REGISTER - (int)&ADDX_GPIO_SET_REGISTER));
    // single major loop
    DMA_TCD0_CITER_ELINKNO = 1;
    DMA_TCD0_BITER_ELINKNO = 1;
    // link channel 1, enable major channel-to-channel linking, don't clear enable on major loop complete
    DMA_TCD0_CSR = (1 << 8) | (1 << 5);
    DMAMUX0_CHCFG0 = DMAMUX_SOURCE_LATCH_RISING_EDGE | DMAMUX_ENABLE;

    // DMA channel #1 - copy address values from current position in array to buffer to temporarily hold row values for the next timer cycle
    // only use single major loop, never disable channel
    DMA_TCD1_SADDR = &matrixUpdateBlocks[0][0].addressValues;
    DMA_TCD1_SOFF = sizeof(uint16_t);
    DMA_TCD1_SLAST = sizeof(matrixUpdateBlock) - (ADDRESS_ARRAY_REGISTERS_TO_UPDATE * sizeof(uint16_t));
    DMA_TCD1_ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
    // 16-bit = 2 bytes transferred
    // transfer two 16-bit values, reset destination address back after each minor loop
    DMA_TCD1_NBYTES_MLOFFNO = (ADDRESS_ARRAY_REGISTERS_TO_UPDATE * sizeof(uint16_t));
    // start with the register that's the highest location in memory and make offset decrement to avoid negative number in NBYTES_MLOFFYES register (TODO: can switch order by masking negative offset)
    DMA_TCD1_DADDR = &gpiosync.gpio_pcor;
    DMA_TCD1_DOFF = (int)&gpiosync.gpio_psor - (int)&gpiosync.gpio_pcor;
    DMA_TCD1_DLASTSGA = (ADDRESS_ARRAY_REGISTERS_TO_UPDATE * ((int)&gpiosync.gpio_pcor - (int)&gpiosync.gpio_psor));
    // no minor loop linking, single major loop, single minor loop, don't clear enable after major loop complete
    DMA_TCD1_CITER_ELINKNO = 1;
    DMA_TCD1_BITER_ELINKNO = 1;
    DMA_TCD1_CSR = 0;

    // DMA channel #2 - on latch falling edge, load FTM1_CV1 and FTM1_MOD with with next values from current block
    // only use single major loop, never disable channel
    // link to channel 3 when complete
#define TIMER_REGISTERS_TO_UPDATE   2
    DMA_TCD2_SADDR = &matrixUpdateBlocks[0][0].timerValues.timer_oe;
    DMA_TCD2_SOFF = sizeof(uint16_t);
    DMA_TCD2_SLAST = sizeof(matrixUpdateBlock) - (TIMER_REGISTERS_TO_UPDATE * sizeof(uint16_t));
    DMA_TCD2_ATTR = DMA_TCD_ATTR_SSIZE(1) | DMA_TCD_ATTR_DSIZE(1);
    // 16-bit = 2 bytes transferred
    DMA_TCD2_NBYTES_MLOFFNO = TIMER_REGISTERS_TO_UPDATE * sizeof(uint16_t);
    DMA_TCD2_DADDR = &FTM1_C1V;
    DMA_TCD2_DOFF = (int)&FTM1_MOD - (int)&FTM1_C1V;
    DMA_TCD2_DLASTSGA = TIMER_REGISTERS_TO_UPDATE * ((int)&FTM1_C1V - (int)&FTM1_MOD);
    // no minor loop linking, single major loop
    DMA_TCD2_CITER_ELINKNO = 1;
    DMA_TCD2_BITER_ELINKNO = 1;
    // link channel 3, enable major channel-to-channel linking, don't clear enable after major loop complete
    DMA_TCD2_CSR = (3 << 8) | (1 << 5);
    DMAMUX0_CHCFG2 = DMAMUX_SOURCE_LATCH_FALLING_EDGE | DMAMUX_ENABLE;

#define DMA_TCD_MLOFF_MASK  (0x3FFFFC00)

    // DMA channel #3 - repeatedly load gpio_array into GPIOD_PDOR, stop and int on major loop complete
    DMA_TCD3_SADDR = matrixUpdateData[0][0];
    DMA_TCD3_SOFF = sizeof(matrixUpdateData[0][0]) / 2;
    // SADDR will get updated by ISR, no need to set SLAST
    DMA_TCD3_SLAST = 0;
    DMA_TCD3_ATTR = DMA_TCD_ATTR_SSIZE(0) | DMA_TCD_ATTR_DSIZE(0);
    // after each minor loop, set source to point back to the beginning of this set of data,
    // but advance by 1 byte to get the next significant bits data
    DMA_TCD3_NBYTES_MLOFFYES = DMA_TCD_NBYTES_SMLOE |
                               (((1 - sizeof(matrixUpdateData[0])) << 10) & DMA_TCD_MLOFF_MASK) |
                               (MATRIX_WIDTH * DMA_UPDATES_PER_CLOCK);
    DMA_TCD3_DADDR = &GPIOD_PDOR;
    DMA_TCD3_DOFF = 0;
    DMA_TCD3_DLASTSGA = 0;
    DMA_TCD3_CITER_ELINKNO = LATCHES_PER_ROW;
    DMA_TCD3_BITER_ELINKNO = LATCHES_PER_ROW;
    // int after major loop is complete
    DMA_TCD3_CSR = DMA_TCD_CSR_INTMAJOR;
    // for debugging - enable bandwidth control (space out GPIO updates so they can be seen easier on a low-bandwidth logic analyzer)
    //DMA_TCD3_CSR |= (0x02 << 14);

    // enable a done interrupt when all DMA operations are complete
    NVIC_ENABLE_IRQ(IRQ_DMA_CH3);

    // enable additional dma interrupt used as software interrupt
    NVIC_SET_PRIORITY(IRQ_DMA_CH1, 0xFF); // 0xFF = lowest priority
    NVIC_ENABLE_IRQ(IRQ_DMA_CH1);

    // enable channels 0, 1, 2, 3
    DMA_ERQ = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

    // at the end after everything is set up: enable timer from system clock, with appropriate prescale
    FTM1_SC = FTM_SC_CLKS(1) | FTM_SC_PS(LATCH_TIMER_PRESCALE);


*/


};

// arrange the relative priority of 2 or more DMA channels
void DMAPriorityOrder(DMAChannel &ch1, DMAChannel &ch2);
void DMAPriorityOrder(DMAChannel &ch1, DMAChannel &ch2, DMAChannel &ch3);
void DMAPriorityOrder(DMAChannel &ch1, DMAChannel &ch2, DMAChannel &ch3, DMAChannel &ch4);



extern "C" {
#endif
extern uint16_t dma_channel_allocated_mask;
#ifdef __cplusplus
}
#endif



#endif
