/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>

// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(),
// usingInterrupt(), and SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// Uncomment this line to add detection of mismatched begin/end transactions.
// A mismatch occurs if other libraries fail to use SPI.endTransaction() for
// each SPI.beginTransaction().  Connect a LED to this pin.  The LED will turn
// on if any mismatch is ever detected.
//#define SPI_TRANSACTION_MISMATCH_LED 5

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR



/**********************************************************/
/*     32 bit Teensy 3.0 and 3.1			  */
/**********************************************************/

#define SPI_HAS_NOTUSINGINTERRUPT 1

class SPISettings {
public:
	SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
		if (__builtin_constant_p(clock)) {
			init_AlwaysInline(clock, bitOrder, dataMode);
		} else {
			init_MightInline(clock, bitOrder, dataMode);
		}
	}
	SPISettings() {
		init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
	}
private:
	void init_MightInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
		init_AlwaysInline(clock, bitOrder, dataMode);
	}
	void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
	  __attribute__((__always_inline__)) {
		uint32_t t, c = SPI_CTAR_FMSZ(7);
		if (bitOrder == LSBFIRST) c |= SPI_CTAR_LSBFE;
		if (__builtin_constant_p(clock)) {
			if	  (clock >= F_BUS / 2) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR
				  | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 3) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR
				  | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 4) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 5) {
				t = SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_DBR
				  | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 6) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 8) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
			} else if (clock >= F_BUS / 10) {
				t = SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 12) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
			} else if (clock >= F_BUS / 16) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2);
			} else if (clock >= F_BUS / 20) {
				t = SPI_CTAR_PBR(2) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(0);
			} else if (clock >= F_BUS / 24) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2);
			} else if (clock >= F_BUS / 32) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(4) | SPI_CTAR_CSSCK(3);
			} else if (clock >= F_BUS / 40) {
				t = SPI_CTAR_PBR(2) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2);
			} else if (clock >= F_BUS / 56) {
				t = SPI_CTAR_PBR(3) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2);
			} else if (clock >= F_BUS / 64) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(5) | SPI_CTAR_CSSCK(4);
			} else if (clock >= F_BUS / 96) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(5) | SPI_CTAR_CSSCK(4);
			} else if (clock >= F_BUS / 128) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(6) | SPI_CTAR_CSSCK(5);
			} else if (clock >= F_BUS / 192) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(6) | SPI_CTAR_CSSCK(5);
			} else if (clock >= F_BUS / 256) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(6);
			} else if (clock >= F_BUS / 384) {
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(6);
			} else if (clock >= F_BUS / 512) {
				t = SPI_CTAR_PBR(0) | SPI_CTAR_BR(8) | SPI_CTAR_CSSCK(7);
			} else if (clock >= F_BUS / 640) {
				t = SPI_CTAR_PBR(2) | SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(6);
			} else {	 /* F_BUS / 768 */
				t = SPI_CTAR_PBR(1) | SPI_CTAR_BR(8) | SPI_CTAR_CSSCK(7);
			}
		} else {
			for (uint32_t i=0; i<23; i++) {
				t = ctar_clock_table[i];
				if (clock >= F_BUS / ctar_div_table[i]) break;
			}
		}
		if (dataMode & 0x08) {
			c |= SPI_CTAR_CPOL;
		}
		if (dataMode & 0x04) {
			c |= SPI_CTAR_CPHA;
			t = (t & 0xFFFF0FFF) | ((t & 0xF000) >> 4);
		}
		ctar = c | t;
	}
	static const uint16_t ctar_div_table[23];
	static const uint32_t ctar_clock_table[23];
	uint32_t ctar;
	friend class SPIClass;
};



class SPIClass {
public:
	// Initialize the SPI library
	static void begin();

	// If SPI is to used from within an interrupt, this function registers
	// that interrupt with the SPI library, so beginTransaction() can
	// prevent conflicts.  The input interruptNumber is the number used
	// with attachInterrupt.  If SPI is used from a different interrupt
	// (eg, a timer), interruptNumber should be 255.
	static void usingInterrupt(uint8_t n) {
		if (n == 3 || n == 4 || n == 24 || n == 33) {
			usingInterrupt(IRQ_PORTA);
		} else if (n == 0 || n == 1 || (n >= 16 && n <= 19) || n == 25 || n == 32) {
			usingInterrupt(IRQ_PORTB);
		} else if ((n >= 9 && n <= 13) || n == 15 || n == 22 || n == 23
		  || (n >= 27 && n <= 30)) {
			usingInterrupt(IRQ_PORTC);
		} else if (n == 2 || (n >= 5 && n <= 8) || n == 14 || n == 20 || n == 21) {
			usingInterrupt(IRQ_PORTD);
		} else if (n == 26 || n == 31) {
			usingInterrupt(IRQ_PORTE);
		}
	}
	static void usingInterrupt(IRQ_NUMBER_t interruptName);
	static void notUsingInterrupt(IRQ_NUMBER_t interruptName);

	// Before using SPI.transfer() or asserting chip select pins,
	// this function is used to gain exclusive access to the SPI bus
	// and configure the correct settings.
	inline static void beginTransaction(SPISettings settings) {
		if (interruptMasksUsed) {
			if (interruptMasksUsed & 0x01) {
				interruptSave[0] = NVIC_ICER0 & interruptMask[0];
				NVIC_ICER0 = interruptSave[0];
			}
			#if NVIC_NUM_INTERRUPTS > 32
			if (interruptMasksUsed & 0x02) {
				interruptSave[1] = NVIC_ICER1 & interruptMask[1];
				NVIC_ICER1 = interruptSave[1];
			}
			#endif
			#if NVIC_NUM_INTERRUPTS > 64 && defined(NVIC_ISER2)
			if (interruptMasksUsed & 0x04) {
				interruptSave[2] = NVIC_ICER2 & interruptMask[2];
				NVIC_ICER2 = interruptSave[2];
			}
			#endif
			#if NVIC_NUM_INTERRUPTS > 96 && defined(NVIC_ISER3)
			if (interruptMasksUsed & 0x08) {
				interruptSave[3] = NVIC_ICER3 & interruptMask[3];
				NVIC_ICER3 = interruptSave[3];
			}
			#endif
		}
		#ifdef SPI_TRANSACTION_MISMATCH_LED
		if (inTransactionFlag) {
			pinMode(SPI_TRANSACTION_MISMATCH_LED, OUTPUT);
			digitalWrite(SPI_TRANSACTION_MISMATCH_LED, HIGH);
		}
		inTransactionFlag = 1;
		#endif
		if (SPI0_CTAR0 != settings.ctar) {
			SPI0_MCR = SPI_MCR_MDIS | SPI_MCR_HALT | SPI_MCR_PCSIS(0x1F);
			SPI0_CTAR0 = settings.ctar;
			SPI0_CTAR1 = settings.ctar| SPI_CTAR_FMSZ(8);
			SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_PCSIS(0x1F);
		}
	}

	// Write to the SPI bus (MOSI pin) and also receive (MISO pin)
	inline static uint8_t transfer(uint8_t data) {
		SPI0_SR = SPI_SR_TCF;
		SPI0_PUSHR = data;
		while (!(SPI0_SR & SPI_SR_TCF)) ; // wait
		return SPI0_POPR;
	}
	inline static uint8_t transfer16(uint16_t data) {
		SPI0_SR = SPI_SR_TCF;
		SPI0_PUSHR = data | SPI_PUSHR_CTAS(1);
		while (!(SPI0_SR & SPI_SR_TCF)) ; // wait
		return SPI0_POPR;
	}
	inline static void transfer(void *buf, size_t count) {
		if (count == 0) return;
		uint8_t *p = (uint8_t *)buf;
		SPDR = *p;
		while (--count > 0) {
			uint8_t out = *(p + 1);
			while (!(SPSR & _BV(SPIF))) ;
			uint8_t in = SPDR;
			SPDR = out;
			*p++ = in;
		}
		while (!(SPSR & _BV(SPIF))) ;
		*p = SPDR;
	}

	// After performing a group of transfers and releasing the chip select
	// signal, this function allows others to access the SPI bus
	inline static void endTransaction(void) {
		#ifdef SPI_TRANSACTION_MISMATCH_LED
		if (!inTransactionFlag) {
			pinMode(SPI_TRANSACTION_MISMATCH_LED, OUTPUT);
			digitalWrite(SPI_TRANSACTION_MISMATCH_LED, HIGH);
		}
		inTransactionFlag = 0;
		#endif
		if (interruptMasksUsed) {
			if (interruptMasksUsed & 0x01) {
				NVIC_ISER0 = interruptSave[0];
			}
			#if NVIC_NUM_INTERRUPTS > 32
			if (interruptMasksUsed & 0x02) {
				NVIC_ISER1 = interruptSave[1];
			}
			#endif
			#if NVIC_NUM_INTERRUPTS > 64 && defined(NVIC_ISER2)
			if (interruptMasksUsed & 0x04) {
				NVIC_ISER2 = interruptSave[2];
			}
			#endif
			#if NVIC_NUM_INTERRUPTS > 96 && defined(NVIC_ISER3)
			if (interruptMasksUsed & 0x08) {
				NVIC_ISER3 = interruptSave[3];
			}
			#endif
		}
	}

	// Disable the SPI bus
	static void end();

	// This function is deprecated.	 New applications should use
	// beginTransaction() to configure SPI settings.
	static void setBitOrder(uint8_t bitOrder);

	// This function is deprecated.	 New applications should use
	// beginTransaction() to configure SPI settings.
	static void setDataMode(uint8_t dataMode);

	// This function is deprecated.	 New applications should use
	// beginTransaction() to configure SPI settings.
	inline static void setClockDivider(uint8_t clockDiv) {
		if (clockDiv == SPI_CLOCK_DIV2) {
			setClockDivider_noInline(SPISettings(8000000, MSBFIRST, SPI_MODE0).ctar);
		} else if (clockDiv == SPI_CLOCK_DIV4) {
			setClockDivider_noInline(SPISettings(4000000, MSBFIRST, SPI_MODE0).ctar);
		} else if (clockDiv == SPI_CLOCK_DIV8) {
			setClockDivider_noInline(SPISettings(2000000, MSBFIRST, SPI_MODE0).ctar);
		} else if (clockDiv == SPI_CLOCK_DIV16) {
			setClockDivider_noInline(SPISettings(1000000, MSBFIRST, SPI_MODE0).ctar);
		} else if (clockDiv == SPI_CLOCK_DIV32) {
			setClockDivider_noInline(SPISettings(500000, MSBFIRST, SPI_MODE0).ctar);
		} else if (clockDiv == SPI_CLOCK_DIV64) {
			setClockDivider_noInline(SPISettings(250000, MSBFIRST, SPI_MODE0).ctar);
		} else { /* clockDiv == SPI_CLOCK_DIV128 */
			setClockDivider_noInline(SPISettings(125000, MSBFIRST, SPI_MODE0).ctar);
		}
	}
	static void setClockDivider_noInline(uint32_t clk);

	// These undocumented functions should not be used.  SPI.transfer()
	// polls the hardware flag which is automatically cleared as the
	// AVR responds to SPI's interrupt
	inline static void attachInterrupt() { }
	inline static void detachInterrupt() { }

	// Teensy 3.x can use alternate pins for these 3 SPI signals.
	inline static void setMOSI(uint8_t pin) __attribute__((always_inline)) {
		SPCR.setMOSI(pin);
	}
	inline static void setMISO(uint8_t pin) __attribute__((always_inline)) {
		SPCR.setMISO(pin);
	}
	inline static void setSCK(uint8_t pin) __attribute__((always_inline)) {
		SPCR.setSCK(pin);
	}
	// return true if "pin" has special chip select capability
	static bool pinIsChipSelect(uint8_t pin);
	// return true if both pin1 and pin2 have independent chip select capability
	static bool pinIsChipSelect(uint8_t pin1, uint8_t pin2);
	// configure a pin for chip select and return its SPI_MCR_PCSIS bitmask
	static uint8_t setCS(uint8_t pin);

private:
	static uint8_t interruptMasksUsed;
	static uint32_t interruptMask[(NVIC_NUM_INTERRUPTS+31)/32];
	static uint32_t interruptSave[(NVIC_NUM_INTERRUPTS+31)/32];
	#ifdef SPI_TRANSACTION_MISMATCH_LED
	static uint8_t inTransactionFlag;
	#endif
};


extern SPIClass SPI;

#endif
