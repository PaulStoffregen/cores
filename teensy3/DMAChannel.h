#ifndef DMAChannel_h_
#define DMAChannel_h_

#include "mk20dx128.h"

// This code is a work-in-progress.  It's incomplete and not usable yet...

#ifdef __cplusplus

class DMAChannel {
	typedef struct __attribute__((packed)) {
		volatile const void * volatile SADDR;
		int16_t SOFF;
		union { uint16_t ATTR; struct { uint8_t ATTR_DST; uint8_t ATTR_SRC; }; };
		uint32_t NBYTES;
		int32_t SLAST;
		volatile void * volatile DADDR;
		int16_t DOFF;
		volatile uint16_t CITER;
		int32_t DLASTSGA;
		volatile uint16_t CSR;
		volatile uint16_t BITER;
	} TCD_t;
public:
	// Constructor - allocates which DMA channel each object actually uses
	DMAChannel(uint8_t channelRequest=0);

	// Triggers cause the DMA channel to actually move data.
	//
	// Use a hardware trigger to make the DMA channel run
	void attachTrigger(uint8_t source) {
		volatile uint8_t *mux;
		mux = (volatile uint8_t *)&(DMAMUX0_CHCFG0) + channel;
		*mux = 0;
		*mux = source | DMAMUX_ENABLE;
	}
	// Use another DMA channel as the trigger, causing this
	// channel to trigger every time it triggers.  This
	// effectively makes the 2 channels run in parallel.
	void attachTrigger(DMAChannel &channel) {

	}
	// Use another DMA channel as the trigger, causing this
	// channel to trigger when it completes.
	void attachTriggerOnCompletion(DMAChannel &channel) {

	}

	// An interrupt routine can be run when the DMA channel completes
	// the entire transfer.
	void attachInterrupt(void (*isr)(void)) {
		_VectorsRam[channel + IRQ_DMA_CH0 + 16] = isr;
		NVIC_ENABLE_IRQ(IRQ_DMA_CH0 + channel);
	}

	// Use a single variable as the data source.  Typically a register
	// for receiving data from one of the hardware peripherals is used.
	void source(const signed char &p) { src(&p, 1); }
	void source(const unsigned char &p) { src(&p, 1); }
	void source(const signed short &p) { src(&p, 2); }
	void source(const unsigned short &p) { src(&p, 2); }
	void source(const signed int &p) { src(&p, 4); }
	void source(const unsigned int &p) { src(&p, 4); }
	void source(const signed long &p) { src(&p, 4); }
	void source(const unsigned long &p) { src(&p, 4); }

	// Use a buffer (array of data) as the data source.  Typically a
	// buffer for transmitting data is used.
	void sourceBuffer(const signed char p[], unsigned int len) { src(p, 1, len); }
	void sourceBuffer(const unsigned char p[], unsigned int len) { src(p, 1, len); }
	void sourceBuffer(const signed short p[], unsigned int len) { src(p, 2, len); }
	void sourceBuffer(const unsigned short p[], unsigned int len) { src(p, 2, len); }
	void sourceBuffer(const signed int p[], unsigned int len) { src(p, 4, len); }
	void sourceBuffer(const unsigned int p[], unsigned int len) { src(p, 4, len); }
	void sourceBuffer(const signed long p[], unsigned int len) { src(p, 4, len); }
	void sourceBuffer(const unsigned long p[], unsigned int len) { src(p, 4, len); }

	// Use a circular buffer as the data source
	void sourceCircular(const signed char p[], unsigned int len) { srcc(p, 1, len); }
	void sourceCircular(const unsigned char p[], unsigned int len) { srcc(p, 1, len); }
	void sourceCircular(const signed short p[], unsigned int len) { srcc(p, 2, len); }
	void sourceCircular(const unsigned short p[], unsigned int len) { srcc(p, 2, len); }
	void sourceCircular(const signed int p[], unsigned int len) { srcc(p, 4, len); }
	void sourceCircular(const unsigned int p[], unsigned int len) { srcc(p, 4, len); }
	void sourceCircular(const signed long p[], unsigned int len) { srcc(p, 4, len); }
	void sourceCircular(const unsigned long p[], unsigned int len) { srcc(p, 4, len); }


	// Use a single variable as the data destination.  Typically a register
	// for transmitting data to one of the hardware peripherals is used.
	void destination(signed char &p) { src(&p, 1); }
	void destination(unsigned char &p) { src(&p, 1); }
	void destination(signed short &p) { src(&p, 2); }
	void destination(unsigned short &p) { src(&p, 2); }
	void destination(signed int &p) { src(&p, 4); }
	void destination(unsigned int &p) { src(&p, 4); }
	void destination(signed long &p) { src(&p, 4); }
	void destination(unsigned long &p) { src(&p, 4); }

	// Use a buffer (array of data) as the data destination.  Typically a
	// buffer for receiving data is used.
	void destinationBuffer(signed char p[], unsigned int len) { src(p, 1, len); }
	void destinationBuffer(unsigned char p[], unsigned int len) { src(p, 1, len); }
	void destinationBuffer(signed short p[], unsigned int len) { src(p, 2, len); }
	void destinationBuffer(unsigned short p[], unsigned int len) { src(p, 2, len); }
	void destinationBuffer(signed int p[], unsigned int len) { src(p, 4, len); }
	void destinationBuffer(unsigned int p[], unsigned int len) { src(p, 4, len); }
	void destinationBuffer(signed long p[], unsigned int len) { src(p, 4, len); }
	void destinationBuffer(unsigned long p[], unsigned int len) { src(p, 4, len); }

	// Use a circular buffer as the data destination
	void destinationCircular(signed char p[], unsigned int len) { srcc(p, 1, len); }
	void destinationCircular(unsigned char p[], unsigned int len) { srcc(p, 1, len); }
	void destinationCircular(signed short p[], unsigned int len) { srcc(p, 2, len); }
	void destinationCircular(unsigned short p[], unsigned int len) { srcc(p, 2, len); }
	void destinationCircular(signed int p[], unsigned int len) { srcc(p, 4, len); }
	void destinationCircular(unsigned int p[], unsigned int len) { srcc(p, 4, len); }
	void destinationCircular(signed long p[], unsigned int len) { srcc(p, 4, len); }
	void destinationCircular(unsigned long p[], unsigned int len) { srcc(p, 4, len); }

	// TODO: explicit function for configuring transfer length....
	// should we try to automatically pick it up from the array lengths?

	// TODO: functions to configure major/minor loop
	//  option #1 - trigger moves 1 byte/word (minor=1, major=count)
	//  option #2 - trigger moves all data (minor=count, major=1)
	//  option ?? - more complex config, write TCD manually....

	// TODO: functions to set other options, functions to enable
	// manual start function, etc

	// TODO: "get" functions, to read important stuff, like SADDR & DADDR...

	// For complex and unusual configurations not possible with the above
	// functions, the Transfer Control Descriptor (TCD) and channel number
	// can be used directly.  This leads to less portable and less readable
	// code, but direct control of all parameters is possible.
	TCD_t &TCD;
	uint8_t channel;

protected:
	void src(const void *p, uint32_t size) {
		TCD.SADDR = p;
		TCD.SOFF = 0;
		if (size == 1) {
			TCD.ATTR_SRC = 0; // 8 bits
		} else if (size == 2) {
			TCD.ATTR_SRC = 1; // 16 bits
		} else {
			TCD.ATTR_SRC = 2; // 32 bits
		}
		//TCD.NBYTES = size;
		TCD.SLAST = 0;
	}
	void src(const void *p, uint32_t size, uint32_t len) {
		TCD.SADDR = p;
		TCD.SOFF = size;
		if (size == 1) {
			TCD.ATTR_SRC = 0; // 8 bits
		} else if (size == 2) {
			TCD.ATTR_SRC = 1; // 16 bits
		} else {
			TCD.ATTR_SRC = 2; // 32 bits
		}
		//TCD.NBYTES = size;
		TCD.SLAST = -len;
	}
	void srcc(const void *p, uint32_t size, uint32_t len) {
		TCD.SADDR = p;
		TCD.SOFF = size;
		if (size == 1) {
			TCD.ATTR_SRC = 0 | ((31 - __builtin_clz(len)) << 3); // 8 bits
		} else if (size == 2) {
			TCD.ATTR_SRC = 1 | ((31 - __builtin_clz(len)) << 3); // 16 bits
		} else {
			TCD.ATTR_SRC = 2 | ((31 - __builtin_clz(len)) << 3); // 32 bits
		}
		//TCD.NBYTES = size;
		TCD.SLAST = 0;
	}

	void dst(void *p, uint32_t size) {
		TCD.DADDR = p;
		TCD.DOFF = 0;
		if (size == 1) {
			TCD.ATTR_SRC = 0; // 8 bits
		} else if (size == 2) {
			TCD.ATTR_SRC = 1; // 16 bits
		} else {
			TCD.ATTR_SRC = 2; // 32 bits
		}
		//TCD.NBYTES = size;
		TCD.DLASTSGA = 0;
	}
	void dst(void *p, uint32_t size, uint32_t len) {
		TCD.DADDR = p;
		TCD.DOFF = size;
		if (size == 1) {
			TCD.ATTR_DST = 0; // 8 bits
		} else if (size == 2) {
			TCD.ATTR_DST = 1; // 16 bits
		} else {
			TCD.ATTR_DST = 2; // 32 bits
		}
		//TCD.NBYTES = size;
		TCD.DLASTSGA = -len;
	}
	void dstc(void *p, uint32_t size, uint32_t len) {
		TCD.DADDR = p;
		TCD.DOFF = size;
		if (size == 1) {
			TCD.ATTR_DST = 0 | ((31 - __builtin_clz(len)) << 3); // 8 bits
		} else if (size == 2) {
			TCD.ATTR_DST = 1 | ((31 - __builtin_clz(len)) << 3); // 16 bits
		} else {
			TCD.ATTR_DST = 2 | ((31 - __builtin_clz(len)) << 3); // 32 bits
		}
		//TCD.NBYTES = size;
		TCD.DLASTSGA = 0;
	}

};


extern "C" {
#endif
extern uint16_t dma_channel_allocated_mask;
#ifdef __cplusplus
}
#endif



#endif
