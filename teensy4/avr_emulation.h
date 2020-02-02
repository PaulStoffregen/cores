/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2019 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _avr_emulation_h_
#define _avr_emulation_h_

#include "imxrt.h"
#include "core_pins.h"
#include "pins_arduino.h"

#ifdef __cplusplus


// bitband addressing for atomic access to data direction register
static inline void GPIO_SETBIT_ATOMIC(volatile uint32_t *reg, uint32_t mask) {
	__disable_irq();
	*reg |= mask;
	__enable_irq();
}

static inline void GPIO_CLRBIT_ATOMIC(volatile uint32_t *reg, uint32_t mask) {
	__disable_irq();
	*reg &= ~mask;
	__enable_irq();
}

#define CONFIG_PULLUP ( IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS )
#define CONFIG_NOPULLUP ( IOMUXC_PAD_DSE(7))


// SPI Control Register ­ SPCR
#define SPIE	7	// SPI Interrupt Enable - not supported
#define SPE	6	// SPI Enable
#define DORD	5	// DORD: Data Order
#define MSTR	4	// MSTR: Master/Slave Select
#define CPOL	3	// CPOL: Clock Polarity
#define CPHA	2	// CPHA: Clock Phase
#define SPR1	1	// Clock: 3 = 125 kHz, 2 = 250 kHz, 1 = 1 MHz, 0->4 MHz
#define SPR0	0
// SPI Status Register ­ SPSR
#define SPIF	7	// SPIF: SPI Interrupt Flag
#define WCOL	6	// WCOL: Write COLlision Flag - not implemented
#define SPI2X	0	// SPI2X: Double SPI Speed Bit
// SPI Data Register ­ SPDR


class SPCRemulation;
class SPSRemulation;
class SPDRemulation;

class SPCRemulation
{
public:
	inline SPCRemulation & operator = (int val) __attribute__((always_inline)) {
/*
		uint32_t ctar, mcr, sim6;
		//serial_print("SPCR=");
		//serial_phex(val);
		//serial_print("\n");
		sim6 = SIM_SCGC6;
		if (!(sim6 & SIM_SCGC6_SPI0)) {
			//serial_print("init1\n");
			SIM_SCGC6 = sim6 | SIM_SCGC6_SPI0;
			SPI0_CTAR0 = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(1) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
		}
		if (!(val & (1<<SPE))) {
			SPI0_MCR |= SPI_MCR_MDIS; // TODO: use bitband for atomic access
		}
		ctar = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(1);
		if (val & (1<<DORD))  ctar |= SPI_CTAR_LSBFE;
		if (val & (1<<CPOL))  ctar |= SPI_CTAR_CPOL;
		if (val & (1<<CPHA)) {
			ctar |= SPI_CTAR_CPHA;
			if ((val & 3) == 0) {
				ctar |= SPI_CTAR_BR(1) | SPI_CTAR_ASC(1);
			} else if ((val & 3) == 1) {
				ctar |= SPI_CTAR_BR(4) | SPI_CTAR_ASC(4);
			} else if ((val & 3) == 2) {
				ctar |= SPI_CTAR_BR(6) | SPI_CTAR_ASC(6);
			} else {
				ctar |= SPI_CTAR_BR(7) | SPI_CTAR_ASC(7);
			}
		} else {
			if ((val & 3) == 0) {
				ctar |= SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
			} else if ((val & 3) == 1) {
				ctar |= SPI_CTAR_BR(4) | SPI_CTAR_CSSCK(4);
			} else if ((val & 3) == 2) {
				ctar |= SPI_CTAR_BR(6) | SPI_CTAR_CSSCK(6);
			} else {
				ctar |= SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(7);
			}
		}
		ctar |= (SPI0_CTAR0 & SPI_CTAR_DBR);
		update_ctar(ctar);
		mcr = SPI_MCR_DCONF(0) | SPI_MCR_PCSIS(0x1F);
		if (val & (1<<MSTR)) mcr |= SPI_MCR_MSTR;
		if (val & (1<<SPE)) {
			mcr &= ~(SPI_MCR_MDIS | SPI_MCR_HALT);
			SPI0_MCR = mcr;
			enable_pins();
		} else {
			mcr |= (SPI_MCR_MDIS | SPI_MCR_HALT);
			SPI0_MCR = mcr;
			disable_pins();
		}
		//serial_print("MCR:");
		//serial_phex32(SPI0_MCR);
		//serial_print(", CTAR0:");
		//serial_phex32(SPI0_CTAR0);
		//serial_print("\n");
*/
		return *this;
	}
	inline SPCRemulation & operator |= (int val) __attribute__((always_inline)) {
/*
		uint32_t sim6;
		//serial_print("SPCR |= ");
		//serial_phex(val);
		//serial_print("\n");
		sim6 = SIM_SCGC6;
		if (!(sim6 & SIM_SCGC6_SPI0)) {
			//serial_print("init2\n");
			SIM_SCGC6 = sim6 | SIM_SCGC6_SPI0;
			SPI0_CTAR0 = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(1) | SPI_CTAR_BR(1);
		}
		if (val & ((1<<DORD)|(1<<CPOL)|(1<<CPHA)|3)) {
			uint32_t ctar = SPI0_CTAR0;
			if (val & (1<<DORD)) ctar |= SPI_CTAR_LSBFE; // TODO: use bitband
			if (val & (1<<CPOL)) ctar |= SPI_CTAR_CPOL;
			if (val & (1<<CPHA) && !(ctar & SPI_CTAR_CPHA)) {
				ctar |= SPI_CTAR_CPHA;
				ctar &= 0xFFFF00FF;
				ctar |= SPI_CTAR_ASC(ctar & 15);
			}
			if ((val & 3) != 0) {
				uint32_t br = ctar & 15;
				uint32_t priorval;
				if (br <= 1) priorval = 0;
				else if (br <= 4) priorval = 1;
				else if (br <= 6) priorval = 2;
				else priorval = 3;
				uint32_t newval = priorval | (val & 3);
				if (newval != priorval) {
					if (newval == 0) br = 1;
					else if (newval == 0) br = 4;
					else if (newval == 0) br = 6;
					else br = 7;
					ctar &= 0xFFFF00F0; // clear BR, ASC, CSSCK
					if ((ctar & SPI_CTAR_CPHA)) {
						ctar |= SPI_CTAR_BR(br) | SPI_CTAR_ASC(br);
					} else {
						ctar |= SPI_CTAR_BR(br) | SPI_CTAR_CSSCK(br);
					}
				}
			}
			update_ctar(ctar);
		}
		if (val & (1<<MSTR)) SPI0_MCR |= SPI_MCR_MSTR;
		if (val & (1<<SPE)) {
			SPI0_MCR &= ~(SPI_MCR_MDIS | SPI_MCR_HALT);
			enable_pins();
		}
		//serial_print("MCR:");
		//serial_phex32(SPI0_MCR);
		//serial_print(", CTAR0:");
		//serial_phex32(SPI0_CTAR0);
		//serial_print("\n");
*/
		return *this;
	}
	inline SPCRemulation & operator &= (int val) __attribute__((always_inline)) {
/*
		//serial_print("SPCR &= ");
		//serial_phex(val);
		//serial_print("\n");
		SIM_SCGC6 |= SIM_SCGC6_SPI0;
		if (!(val & (1<<SPE))) {
			SPI0_MCR |= (SPI_MCR_MDIS | SPI_MCR_HALT);
			disable_pins();
		}
		if ((val & ((1<<DORD)|(1<<CPOL)|(1<<CPHA)|3)) != ((1<<DORD)|(1<<CPOL)|(1<<CPHA)|3)) {
			uint32_t ctar = SPI0_CTAR0;
			if (!(val & (1<<DORD))) ctar &= ~SPI_CTAR_LSBFE; // TODO: use bitband
			if (!(val & (1<<CPOL))) ctar &= ~SPI_CTAR_CPOL;
			if (!(val & (1<<CPHA)) && (ctar & SPI_CTAR_CPHA)) {
				ctar &= ~SPI_CTAR_CPHA;
				ctar &= 0xFFFF00FF;
				ctar |= SPI_CTAR_CSSCK(ctar & 15);
			}
			if ((val & 3) != 3) {
				uint32_t br = ctar & 15;
				uint32_t priorval;
				if (br <= 1) priorval = 0;
				else if (br <= 4) priorval = 1;
				else if (br <= 6) priorval = 2;
				else priorval = 3;
				uint32_t newval = priorval & (val & 3);
				if (newval != priorval) {
					if (newval == 0) br = 1;
					else if (newval == 0) br = 4;
					else if (newval == 0) br = 6;
					else br = 7;
					ctar &= 0xFFFF00F0; // clear BR, ASC, CSSCK
					if ((ctar & SPI_CTAR_CPHA)) {
						ctar |= SPI_CTAR_BR(br) | SPI_CTAR_ASC(br);
					} else {
						ctar |= SPI_CTAR_BR(br) | SPI_CTAR_CSSCK(br);
					}
				}
			}
			update_ctar(ctar);
		}
		if (!(val & (1<<MSTR))) SPI0_MCR &= ~SPI_MCR_MSTR;
*/
		return *this;
	}
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
/*		
		//serial_print("SPCR & ");
		//serial_phex(val);
		//serial_print("\n");
		SIM_SCGC6 |= SIM_SCGC6_SPI0;
		if ((val & (1<<DORD)) && (SPI0_CTAR0 & SPI_CTAR_LSBFE)) ret |= (1<<DORD);
		if ((val & (1<<CPOL)) && (SPI0_CTAR0 & SPI_CTAR_CPOL)) ret |= (1<<CPOL);
		if ((val & (1<<CPHA)) && (SPI0_CTAR0 & SPI_CTAR_CPHA)) ret |= (1<<CPHA);
		if ((val & 3) != 0) {
			uint32_t dbr = SPI0_CTAR0 & 15;
			uint32_t spr10;
			if (dbr <= 1) {
				spr10 = 0;
			} else if (dbr <= 4) {
				spr10 |= (1<<SPR0);
			} else if (dbr <= 6) {
				spr10 |= (1<<SPR1);
			} else {
				spr10 |= (1<<SPR1)|(1<<SPR0);
			}
			ret |= spr10 & (val & 3);
		}
		if (val & (1<<SPE) && (!(SPI0_MCR & SPI_MCR_MDIS))) ret |= (1<<SPE);
		if (val & (1<<MSTR) && (SPI0_MCR & SPI_MCR_MSTR)) ret |= (1<<MSTR);
		//serial_print("ret = ");
		//serial_phex(ret);
		//serial_print("\n");
*/
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
/*		
		if ((SIM_SCGC6 & SIM_SCGC6_SPI0)) {
			int ctar = SPI0_CTAR0;
			if (ctar & SPI_CTAR_LSBFE) ret |= (1<<DORD);
			if (ctar & SPI_CTAR_CPOL) ret |= (1<<CPOL);
			if (ctar & SPI_CTAR_CPHA) ret |= (1<<CPHA);
			ctar &= 15;
			if (ctar <= 1) {
			} else if (ctar <= 4) {
				ret |= (1<<SPR0);
			} else if (ctar <= 6) {
				ret |= (1<<SPR1);
			} else {
				ret |= (1<<SPR1)|(1<<SPR0);
			}
			int mcr = SPI0_MCR;
			if (!(mcr & SPI_MCR_MDIS)) ret |= (1<<SPE);
			if (mcr & SPI_MCR_MSTR) ret |= (1<<MSTR);
		}
*/
		return ret;
	}
	inline void setMOSI(uint8_t pin) __attribute__((always_inline)) {
	}
	inline void setMOSI_soft(uint8_t pin) __attribute__((always_inline)) {
	}
	inline void setMISO(uint8_t pin) __attribute__((always_inline)) {
	}
	inline void setSCK(uint8_t pin) __attribute__((always_inline)) {
	}
	friend class SPSRemulation;
	friend class SPIFIFOclass;
private:
	static uint8_t pinout;
public:
	inline void enable_pins(void) __attribute__((always_inline)) {
		//serial_print("enable_pins\n");
	}
	inline void disable_pins(void) __attribute__((always_inline)) {
	}
};
extern SPCRemulation SPCR;


class SPSRemulation
{
public:
	inline SPSRemulation & operator = (int val) __attribute__((always_inline)) {
		//serial_print("SPSR=");
		//serial_phex(val);
		//serial_print("\n");
/*
		uint32_t ctar = SPI0_CTAR0;
		if (val & (1<<SPI2X)) {
			ctar |= SPI_CTAR_DBR;
		} else {
			ctar &= ~SPI_CTAR_DBR;
		}
		SPCRemulation::update_ctar(ctar);
		//serial_print("MCR:");
		//serial_phex32(SPI0_MCR);
		//serial_print(", CTAR0:");
		//serial_phex32(SPI0_CTAR0);
		//serial_print("\n");
*/		
		return *this;
	}
	inline SPSRemulation & operator |= (int val) __attribute__((always_inline)) {
/*
		//serial_print("SPSR |= ");
		//serial_phex(val);
		//serial_print("\n");
		if (val & (1<<SPI2X)) SPCRemulation::update_ctar(SPI0_CTAR0 |= SPI_CTAR_DBR);
*/
		return *this;
	}
	inline SPSRemulation & operator &= (int val) __attribute__((always_inline)) {
/*
		//serial_print("SPSR &= ");
		//serial_phex(val);
		//serial_print("\n");
		if (!(val & (1<<SPI2X))) SPCRemulation::update_ctar(SPI0_CTAR0 &= ~SPI_CTAR_DBR);
*/
		return *this;
	}
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		//serial_print("SPSR & ");
		//serial_phex(val);
		//serial_print("\n");
		// TODO: using SPI_SR_TCF isn't quite right.  Control returns to the
		// caller after the final edge that captures data, which is 1/2 cycle
		// sooner than AVR returns.  At 500 kHz and slower SPI, this can make
		// a difference when digitalWrite is used to manually control the CS
		// pin, and perhaps it could matter at high clocks if faster register
		// access is used?  But does it really matter?  Do any SPI chips in
		// practice really perform differently if CS negates early, after the
		// final bit is clocked, but before the end of the whole clock cycle?
		if ((val & (1<<SPIF)) && ((LPSPI4_RSR & LPSPI_RSR_RXEMPTY) == 0)) ret = (1<<SPIF);
		//if ((val & (1<<SPI2X)) && (SPI0_CTAR0 & SPI_CTAR_DBR)) ret |= (1<<SPI2X);
		//delayMicroseconds(50000);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		//serial_print("SPSR (int)\n");
		if ((LPSPI4_RSR & LPSPI_RSR_RXEMPTY) == 0) ret = (1<<SPIF);
		//if (SPI0_CTAR0 & SPI_CTAR_DBR) ret |= (1<<SPI2X);
		return ret;
	}
};
extern SPSRemulation SPSR;

class SPDRemulation
{
public:
	inline SPDRemulation & operator = (int val) __attribute__((always_inline)) {
		//serial_print("SPDR = ");
		//serial_phex(val);
		//serial_print("\n");
		LPSPI4_CR = LPSPI_CR_RRF | LPSPI_CR_MEN;	// Module enabled anc clear the receive. 
		LPSPI4_TDR = (val & 255);
		return *this;
	}
	operator int () const __attribute__((always_inline)) {
		uint32_t val;
		val = LPSPI4_RDR & 255;
		return val;
	}
};
extern SPDRemulation SPDR;

class PORTDemulation
{
public:
	inline PORTDemulation & operator = (int val) __attribute__((always_inline)) {
		digitalWriteFast(0, (val & (1<<0)));
		if (!(CORE_PIN0_DDRREG & CORE_PIN0_BITMASK))
			CORE_PIN0_PADCONFIG = ((val & (1<<0)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(1, (val & (1<<1)));
		if (!(CORE_PIN1_DDRREG & CORE_PIN1_BITMASK))
			CORE_PIN1_PADCONFIG = ((val & (1<<1)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(2, (val & (1<<2)));
		if (!(CORE_PIN2_DDRREG & CORE_PIN2_BITMASK))
			CORE_PIN2_PADCONFIG = ((val & (1<<2)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(3, (val & (1<<3)));
		if (!(CORE_PIN3_DDRREG & CORE_PIN3_BITMASK))
			CORE_PIN3_PADCONFIG = ((val & (1<<3)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(4, (val & (1<<4)));
		if (!(CORE_PIN4_DDRREG & CORE_PIN4_BITMASK))
			CORE_PIN4_PADCONFIG = ((val & (1<<4)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(5, (val & (1<<5)));
		if (!(CORE_PIN5_DDRREG & CORE_PIN5_BITMASK))
			CORE_PIN5_PADCONFIG = ((val & (1<<5)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(6, (val & (1<<6)));
		if (!(CORE_PIN6_DDRREG & CORE_PIN6_BITMASK))
			CORE_PIN6_PADCONFIG = ((val & (1<<6)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(7, (val & (1<<7)));
		if (!(CORE_PIN7_DDRREG & CORE_PIN7_BITMASK))
			CORE_PIN7_PADCONFIG = ((val & (1<<7)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		return *this;
	}
	inline PORTDemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) {
			digitalWriteFast(0, HIGH);
			if (!(CORE_PIN0_DDRREG & CORE_PIN0_BITMASK)) CORE_PIN0_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<1)) {
			digitalWriteFast(1, HIGH);
			if (!(CORE_PIN1_DDRREG & CORE_PIN1_BITMASK)) CORE_PIN1_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<2)) {
			digitalWriteFast(2, HIGH);
			if (!(CORE_PIN2_DDRREG & CORE_PIN2_BITMASK)) CORE_PIN2_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<3)) {
			digitalWriteFast(3, HIGH);
			if (!(CORE_PIN3_DDRREG & CORE_PIN3_BITMASK)) CORE_PIN3_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<4)) {
			digitalWriteFast(4, HIGH);
			if (!(CORE_PIN4_DDRREG & CORE_PIN4_BITMASK)) CORE_PIN4_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<5)) {
			digitalWriteFast(5, HIGH);
			if (!(CORE_PIN5_DDRREG & CORE_PIN5_BITMASK)) CORE_PIN5_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<6)) {
			digitalWriteFast(6, HIGH);
			if (!(CORE_PIN6_DDRREG & CORE_PIN6_BITMASK)) CORE_PIN6_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<7)) {
			digitalWriteFast(7, HIGH);
			if (!(CORE_PIN7_DDRREG & CORE_PIN7_BITMASK)) CORE_PIN7_CONFIG = CONFIG_PULLUP;
		}
		return *this;
	}
	inline PORTDemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) {
			digitalWriteFast(0, LOW);
			if (!(CORE_PIN0_DDRREG & CORE_PIN0_BITMASK)) CORE_PIN0_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<1))) {
			digitalWriteFast(1, LOW);
			if (!(CORE_PIN1_DDRREG & CORE_PIN1_BITMASK)) CORE_PIN1_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<2))) {
			digitalWriteFast(2, LOW);
			if (!(CORE_PIN2_DDRREG & CORE_PIN2_BITMASK)) CORE_PIN2_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<3))) {
			digitalWriteFast(3, LOW);
			if (!(CORE_PIN3_DDRREG & CORE_PIN3_BITMASK)) CORE_PIN3_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<4))) {
			digitalWriteFast(4, LOW);
			if (!(CORE_PIN4_DDRREG & CORE_PIN4_BITMASK)) CORE_PIN4_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<5))) {
			digitalWriteFast(5, LOW);
			if (!(CORE_PIN5_DDRREG & CORE_PIN5_BITMASK)) CORE_PIN5_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<6))) {
			digitalWriteFast(6, LOW);
			if (!(CORE_PIN6_DDRREG & CORE_PIN6_BITMASK)) CORE_PIN6_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<7))) {
			digitalWriteFast(7, LOW);
			if (!(CORE_PIN7_DDRREG & CORE_PIN7_BITMASK)) CORE_PIN7_CONFIG = CONFIG_NOPULLUP;
		}
		return *this;
	}
};
extern PORTDemulation PORTD;

class PINDemulation
{
public:
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		if ((val & (1<<0)) && digitalReadFast(0)) ret |= (1<<0);
		if ((val & (1<<1)) && digitalReadFast(1)) ret |= (1<<1);
		if ((val & (1<<2)) && digitalReadFast(2)) ret |= (1<<2);
		if ((val & (1<<3)) && digitalReadFast(3)) ret |= (1<<3);
		if ((val & (1<<4)) && digitalReadFast(4)) ret |= (1<<4);
		if ((val & (1<<5)) && digitalReadFast(5)) ret |= (1<<5);
		if ((val & (1<<6)) && digitalReadFast(6)) ret |= (1<<6);
		if ((val & (1<<7)) && digitalReadFast(7)) ret |= (1<<7);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if (digitalReadFast(0)) ret |= (1<<0);
		if (digitalReadFast(1)) ret |= (1<<1);
		if (digitalReadFast(2)) ret |= (1<<2);
		if (digitalReadFast(3)) ret |= (1<<3);
		if (digitalReadFast(4)) ret |= (1<<4);
		if (digitalReadFast(5)) ret |= (1<<5);
		if (digitalReadFast(6)) ret |= (1<<6);
		if (digitalReadFast(7)) ret |= (1<<7);
		return ret;
	}
};
extern PINDemulation PIND;

class DDRDemulation
{
public:
	inline DDRDemulation & operator = (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) set0(); else clr0();
		if (val & (1<<1)) set1(); else clr1();
		if (val & (1<<2)) set2(); else clr2();
		if (val & (1<<3)) set3(); else clr3();
		if (val & (1<<4)) set4(); else clr4();
		if (val & (1<<5)) set5(); else clr5();
		if (val & (1<<6)) set6(); else clr6();
		if (val & (1<<7)) set7(); else clr7();
		return *this;
	}
	inline DDRDemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) set0();
		if (val & (1<<1)) set1();
		if (val & (1<<2)) set2();
		if (val & (1<<3)) set3();
		if (val & (1<<4)) set4();
		if (val & (1<<5)) set5();
		if (val & (1<<6)) set6();
		if (val & (1<<7)) set7();
		return *this;
	}
	inline DDRDemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) clr0();
		if (!(val & (1<<1))) clr1();
		if (!(val & (1<<2))) clr2();
		if (!(val & (1<<3))) clr3();
		if (!(val & (1<<4))) clr4();
		if (!(val & (1<<5))) clr5();
		if (!(val & (1<<6))) clr6();
		if (!(val & (1<<7))) clr7();
		return *this;
	}
private:
	inline void set0() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN0_DDRREG, CORE_PIN0_BITMASK);
		CORE_PIN0_CONFIG = 5 | 0x10;
		CORE_PIN0_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set1() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN1_DDRREG, CORE_PIN1_BITMASK);
		CORE_PIN1_CONFIG = 5 | 0x10;
		CORE_PIN1_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set2() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN2_DDRREG, CORE_PIN2_BITMASK);
		CORE_PIN2_CONFIG = 5 | 0x10;
		CORE_PIN2_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set3() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN3_DDRREG, CORE_PIN3_BITMASK);
		CORE_PIN3_CONFIG = 5 | 0x10;
		CORE_PIN3_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set4() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN4_DDRREG, CORE_PIN4_BITMASK);
		CORE_PIN4_CONFIG = 5 | 0x10;
		CORE_PIN4_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set5() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN5_DDRREG, CORE_PIN5_BITMASK);
		CORE_PIN5_CONFIG = 5 | 0x10;
		CORE_PIN5_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set6() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN6_DDRREG, CORE_PIN6_BITMASK);
		CORE_PIN6_CONFIG = 5 | 0x10;
		CORE_PIN6_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set7() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN7_DDRREG, CORE_PIN7_BITMASK);
		CORE_PIN7_CONFIG = 5 | 0x10;
		CORE_PIN7_PADCONFIG = CONFIG_PULLUP;
	}
	inline void clr0() __attribute__((always_inline)) {
		CORE_PIN0_CONFIG = 5 | 0x10;
		CORE_PIN0_PADCONFIG = ((CORE_PIN0_PORTREG & CORE_PIN0_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN0_DDRREG, CORE_PIN0_BITMASK);
	}
	inline void clr1() __attribute__((always_inline)) {
		CORE_PIN1_CONFIG = 5 | 0x10;
		CORE_PIN1_PADCONFIG = ((CORE_PIN1_PORTREG & CORE_PIN1_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN1_DDRREG, CORE_PIN1_BITMASK);
	}
	inline void clr2() __attribute__((always_inline)) {
		CORE_PIN2_CONFIG = 5 | 0x10;
		CORE_PIN2_PADCONFIG = ((CORE_PIN2_PORTREG & CORE_PIN2_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN2_DDRREG, CORE_PIN2_BITMASK);
	}
	inline void clr3() __attribute__((always_inline)) {
		CORE_PIN3_CONFIG = 5 | 0x10;
		CORE_PIN3_PADCONFIG = ((CORE_PIN3_PORTREG & CORE_PIN3_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN3_DDRREG, CORE_PIN3_BITMASK);
	}
	inline void clr4() __attribute__((always_inline)) {
		CORE_PIN4_CONFIG = 5 | 0x10;
		CORE_PIN4_PADCONFIG = ((CORE_PIN4_PORTREG & CORE_PIN4_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN4_DDRREG, CORE_PIN4_BITMASK);
	}
	inline void clr5() __attribute__((always_inline)) {
		CORE_PIN5_CONFIG = 5 | 0x10;
		CORE_PIN5_PADCONFIG = ((CORE_PIN5_PORTREG & CORE_PIN5_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN5_DDRREG, CORE_PIN5_BITMASK);
	}
	inline void clr6() __attribute__((always_inline)) {
		CORE_PIN6_CONFIG = 5 | 0x10;
		CORE_PIN6_PADCONFIG = ((CORE_PIN6_PORTREG & CORE_PIN6_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN6_DDRREG, CORE_PIN6_BITMASK);
	}
	inline void clr7() __attribute__((always_inline)) {
		CORE_PIN7_CONFIG = 5 | 0x10;
		CORE_PIN7_PADCONFIG = ((CORE_PIN7_PORTREG & CORE_PIN7_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN7_DDRREG, CORE_PIN7_BITMASK);
	}
};

extern DDRDemulation DDRD;






class PORTBemulation
{
public:
	inline PORTBemulation & operator = (int val) __attribute__((always_inline)) {
		digitalWriteFast(8, (val & (1<<0)));
		if (!(CORE_PIN8_DDRREG & CORE_PIN8_BITMASK))
			CORE_PIN8_PADCONFIG = ((val & (1<<0)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(9, (val & (1<<1)));
		if (!(CORE_PIN9_DDRREG & CORE_PIN9_BITMASK))
			CORE_PIN9_PADCONFIG = ((val & (1<<1)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(10, (val & (1<<2)));
		if (!(CORE_PIN10_DDRREG & CORE_PIN10_BITMASK))
			CORE_PIN10_PADCONFIG = ((val & (1<<2)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(11, (val & (1<<3)));
		if (!(CORE_PIN11_DDRREG & CORE_PIN11_BITMASK))
			CORE_PIN11_PADCONFIG = ((val & (1<<3)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(12, (val & (1<<4)));
		if (!(CORE_PIN12_DDRREG & CORE_PIN12_BITMASK))
			CORE_PIN12_PADCONFIG = ((val & (1<<4)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(13, (val & (1<<5)));
		if (!(CORE_PIN13_DDRREG & CORE_PIN13_BITMASK))
			CORE_PIN13_PADCONFIG = ((val & (1<<5)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		return *this;
	}
	inline PORTBemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) {
			digitalWriteFast(8, HIGH);
			if (!(CORE_PIN7_DDRREG & CORE_PIN7_BITMASK)) CORE_PIN8_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<1)) {
			digitalWriteFast(9, HIGH);
			if (!(CORE_PIN7_DDRREG & CORE_PIN7_BITMASK)) CORE_PIN9_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<2)) {
			digitalWriteFast(10, HIGH);
			if (!(CORE_PIN10_DDRREG & CORE_PIN10_BITMASK)) CORE_PIN10_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<3)) {
			digitalWriteFast(11, HIGH);
			if (!(CORE_PIN11_DDRREG & CORE_PIN11_BITMASK)) CORE_PIN11_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<4)) {
			digitalWriteFast(12, HIGH);
			if (!(CORE_PIN12_DDRREG & CORE_PIN12_BITMASK)) CORE_PIN12_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<5)) {
			digitalWriteFast(13, HIGH);
			if (!(CORE_PIN13_DDRREG & CORE_PIN13_BITMASK)) CORE_PIN13_CONFIG = CONFIG_PULLUP;
		}
		return *this;
	}
	inline PORTBemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) {
			digitalWriteFast(8, LOW);
			if (!(CORE_PIN8_DDRREG & CORE_PIN8_BITMASK)) CORE_PIN8_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<1))) {
			digitalWriteFast(9, LOW);
			if (!(CORE_PIN9_DDRREG & CORE_PIN9_BITMASK)) CORE_PIN9_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<2))) {
			digitalWriteFast(10, LOW);
			if (!(CORE_PIN10_DDRREG & CORE_PIN10_BITMASK)) CORE_PIN10_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<3))) {
			digitalWriteFast(11, LOW);
			if (!(CORE_PIN11_DDRREG & CORE_PIN11_BITMASK)) CORE_PIN11_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<4))) {
			digitalWriteFast(12, LOW);
			if (!(CORE_PIN12_DDRREG & CORE_PIN12_BITMASK)) CORE_PIN12_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<5))) {
			digitalWriteFast(13, LOW);
			if (!(CORE_PIN13_DDRREG & CORE_PIN13_BITMASK)) CORE_PIN13_CONFIG = CONFIG_NOPULLUP;
		}
		return *this;
	}
};
extern PORTBemulation PORTB;

class PINBemulation
{
public:
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		if ((val & (1<<0)) && digitalReadFast(8)) ret |= (1<<0);
		if ((val & (1<<1)) && digitalReadFast(9)) ret |= (1<<1);
		if ((val & (1<<2)) && digitalReadFast(10)) ret |= (1<<2);
		if ((val & (1<<3)) && digitalReadFast(11)) ret |= (1<<3);
		if ((val & (1<<4)) && digitalReadFast(12)) ret |= (1<<4);
		if ((val & (1<<5)) && digitalReadFast(13)) ret |= (1<<5);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if (digitalReadFast(8)) ret |= (1<<0);
		if (digitalReadFast(9)) ret |= (1<<1);
		if (digitalReadFast(10)) ret |= (1<<2);
		if (digitalReadFast(11)) ret |= (1<<3);
		if (digitalReadFast(12)) ret |= (1<<4);
		if (digitalReadFast(13)) ret |= (1<<5);
		return ret;
	}
};
extern PINBemulation PINB;

class DDRBemulation
{
public:
	inline DDRBemulation & operator = (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) set0(); else clr0();
		if (val & (1<<1)) set1(); else clr1();
		if (val & (1<<2)) set2(); else clr2();
		if (val & (1<<3)) set3(); else clr3();
		if (val & (1<<4)) set4(); else clr4();
		if (val & (1<<5)) set5(); else clr5();
		return *this;
	}
	inline DDRBemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) set0();
		if (val & (1<<1)) set1();
		if (val & (1<<2)) set2();
		if (val & (1<<3)) set3();
		if (val & (1<<4)) set4();
		if (val & (1<<5)) set5();
		return *this;
	}
	inline DDRBemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) clr0();
		if (!(val & (1<<1))) clr1();
		if (!(val & (1<<2))) clr2();
		if (!(val & (1<<3))) clr3();
		if (!(val & (1<<4))) clr4();
		if (!(val & (1<<5))) clr5();
		return *this;
	}
private:
	inline void set0() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN8_DDRREG, CORE_PIN8_BITMASK);
		CORE_PIN8_CONFIG = 5 | 0x10;
		CORE_PIN8_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set1() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN9_DDRREG, CORE_PIN9_BITMASK);
		CORE_PIN9_CONFIG = 5 | 0x10;
		CORE_PIN9_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set2() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN10_DDRREG, CORE_PIN10_BITMASK);
		CORE_PIN10_CONFIG = 5 | 0x10;
		CORE_PIN10_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set3() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN11_DDRREG, CORE_PIN11_BITMASK);
		CORE_PIN11_CONFIG = 5 | 0x10;
		CORE_PIN11_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set4() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN12_DDRREG, CORE_PIN12_BITMASK);
		CORE_PIN12_CONFIG = 5 | 0x10;
		CORE_PIN12_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set5() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN13_DDRREG, CORE_PIN13_BITMASK);
		CORE_PIN13_CONFIG = 5 | 0x10;
		CORE_PIN13_PADCONFIG = CONFIG_PULLUP;
	}
	inline void clr0() __attribute__((always_inline)) {
		CORE_PIN8_CONFIG = 5 | 0x10;
		CORE_PIN8_PADCONFIG = ((CORE_PIN8_PORTREG & CORE_PIN8_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN8_DDRREG, CORE_PIN8_BITMASK);
	}
	inline void clr1() __attribute__((always_inline)) {
		CORE_PIN9_CONFIG = 5 | 0x10;
		CORE_PIN9_PADCONFIG = ((CORE_PIN9_PORTREG & CORE_PIN9_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN9_DDRREG, CORE_PIN9_BITMASK);
	}
	inline void clr2() __attribute__((always_inline)) {
		CORE_PIN10_CONFIG = 5 | 0x10;
		CORE_PIN10_PADCONFIG = ((CORE_PIN10_PORTREG & CORE_PIN10_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN10_DDRREG, CORE_PIN10_BITMASK);
	}
	inline void clr3() __attribute__((always_inline)) {
		CORE_PIN11_CONFIG = 5 | 0x10;
		CORE_PIN11_PADCONFIG = ((CORE_PIN11_PORTREG & CORE_PIN11_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN11_DDRREG, CORE_PIN11_BITMASK);
	}
	inline void clr4() __attribute__((always_inline)) {
		CORE_PIN12_CONFIG = 5 | 0x10;
		CORE_PIN12_PADCONFIG = ((CORE_PIN12_PORTREG & CORE_PIN12_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN12_DDRREG, CORE_PIN12_BITMASK);
	}
	inline void clr5() __attribute__((always_inline)) {
		CORE_PIN13_CONFIG = 5 | 0x10;
		CORE_PIN13_PADCONFIG = ((CORE_PIN13_PORTREG & CORE_PIN13_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN13_DDRREG, CORE_PIN13_BITMASK);
	}
};

extern DDRBemulation DDRB;






class PORTCemulation
{
public:
	inline PORTCemulation & operator = (int val) __attribute__((always_inline)) {
		digitalWriteFast(14, (val & (1<<0)));
		if (!(CORE_PIN14_DDRREG & CORE_PIN14_BITMASK))
			CORE_PIN14_PADCONFIG = ((val & (1<<0)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(15, (val & (1<<1)));
		if (!(CORE_PIN15_DDRREG & CORE_PIN15_BITMASK))
			CORE_PIN15_PADCONFIG = ((val & (1<<1)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(16, (val & (1<<2)));
		if (!(CORE_PIN16_DDRREG & CORE_PIN16_BITMASK))
			CORE_PIN16_PADCONFIG = ((val & (1<<2)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(17, (val & (1<<3)));
		if (!(CORE_PIN17_DDRREG & CORE_PIN17_BITMASK))
			CORE_PIN17_PADCONFIG = ((val & (1<<3)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(18, (val & (1<<4)));
		if (!(CORE_PIN18_DDRREG & CORE_PIN18_BITMASK))
			CORE_PIN18_PADCONFIG = ((val & (1<<4)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		digitalWriteFast(19, (val & (1<<5)));
		if (!(CORE_PIN19_DDRREG & CORE_PIN19_BITMASK))
			CORE_PIN19_PADCONFIG = ((val & (1<<5)) ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		return *this;
	}
	inline PORTCemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) {
			digitalWriteFast(14, HIGH);
			if (!(CORE_PIN14_DDRREG & CORE_PIN14_BITMASK)) CORE_PIN14_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<1)) {
			digitalWriteFast(15, HIGH);
			if (!(CORE_PIN15_DDRREG & CORE_PIN15_BITMASK)) CORE_PIN15_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<2)) {
			digitalWriteFast(16, HIGH);
			if (!(CORE_PIN16_DDRREG & CORE_PIN16_BITMASK)) CORE_PIN16_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<3)) {
			digitalWriteFast(17, HIGH);
			if (!(CORE_PIN17_DDRREG & CORE_PIN17_BITMASK)) CORE_PIN17_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<4)) {
			digitalWriteFast(18, HIGH);
			if (!(CORE_PIN18_DDRREG & CORE_PIN18_BITMASK)) CORE_PIN18_CONFIG = CONFIG_PULLUP;
		}
		if (val & (1<<5)) {
			digitalWriteFast(19, HIGH);
			if (!(CORE_PIN19_DDRREG & CORE_PIN19_BITMASK)) CORE_PIN19_CONFIG = CONFIG_PULLUP;
		}
		return *this;
	}
	inline PORTCemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) {
			digitalWriteFast(14, LOW);
			if (!(CORE_PIN14_DDRREG & CORE_PIN14_BITMASK)) CORE_PIN14_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<1))) {
			digitalWriteFast(15, LOW);
			if (!(CORE_PIN15_DDRREG & CORE_PIN15_BITMASK)) CORE_PIN15_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<2))) {
			digitalWriteFast(16, LOW);
			if (!(CORE_PIN16_DDRREG & CORE_PIN16_BITMASK)) CORE_PIN16_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<3))) {
			digitalWriteFast(17, LOW);
			if (!(CORE_PIN17_DDRREG & CORE_PIN17_BITMASK)) CORE_PIN17_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<4))) {
			digitalWriteFast(18, LOW);
			if (!(CORE_PIN18_DDRREG & CORE_PIN18_BITMASK)) CORE_PIN18_CONFIG = CONFIG_NOPULLUP;
		}
		if (!(val & (1<<5))) {
			digitalWriteFast(19, LOW);
			if (!(CORE_PIN19_DDRREG & CORE_PIN19_BITMASK)) CORE_PIN19_CONFIG = CONFIG_NOPULLUP;
		}
		return *this;
	}
};
extern PORTCemulation PORTC;

class PINCemulation
{
public:
	inline int operator & (int val) const __attribute__((always_inline)) {
		int ret = 0;
		if ((val & (1<<0)) && digitalReadFast(14)) ret |= (1<<0);
		if ((val & (1<<1)) && digitalReadFast(15)) ret |= (1<<1);
		if ((val & (1<<2)) && digitalReadFast(16)) ret |= (1<<2);
		if ((val & (1<<3)) && digitalReadFast(17)) ret |= (1<<3);
		if ((val & (1<<4)) && digitalReadFast(18)) ret |= (1<<4);
		if ((val & (1<<5)) && digitalReadFast(19)) ret |= (1<<5);
		return ret;
	}
	operator int () const __attribute__((always_inline)) {
		int ret = 0;
		if (digitalReadFast(14)) ret |= (1<<0);
		if (digitalReadFast(15)) ret |= (1<<1);
		if (digitalReadFast(16)) ret |= (1<<2);
		if (digitalReadFast(17)) ret |= (1<<3);
		if (digitalReadFast(18)) ret |= (1<<4);
		if (digitalReadFast(19)) ret |= (1<<5);
		return ret;
	}
};
extern PINCemulation PINC;

class DDRCemulation
{
public:
	inline DDRCemulation & operator = (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) set0(); else clr0();
		if (val & (1<<1)) set1(); else clr1();
		if (val & (1<<2)) set2(); else clr2();
		if (val & (1<<3)) set3(); else clr3();
		if (val & (1<<4)) set4(); else clr4();
		if (val & (1<<5)) set5(); else clr5();
		return *this;
	}
	inline DDRCemulation & operator |= (int val) __attribute__((always_inline)) {
		if (val & (1<<0)) set0();
		if (val & (1<<1)) set1();
		if (val & (1<<2)) set2();
		if (val & (1<<3)) set3();
		if (val & (1<<4)) set4();
		if (val & (1<<5)) set5();
		return *this;
	}
	inline DDRCemulation & operator &= (int val) __attribute__((always_inline)) {
		if (!(val & (1<<0))) clr0();
		if (!(val & (1<<1))) clr1();
		if (!(val & (1<<2))) clr2();
		if (!(val & (1<<3))) clr3();
		if (!(val & (1<<4))) clr4();
		if (!(val & (1<<5))) clr5();
		return *this;
	}
private:
	inline void set0() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN14_DDRREG, CORE_PIN14_BITMASK);
		CORE_PIN14_CONFIG = 5 | 0x10;
		CORE_PIN14_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set1() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN15_DDRREG, CORE_PIN15_BITMASK);
		CORE_PIN15_CONFIG = 5 | 0x10;
		CORE_PIN15_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set2() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN16_DDRREG, CORE_PIN16_BITMASK);
		CORE_PIN16_CONFIG = 5 | 0x10;
		CORE_PIN16_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set3() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN17_DDRREG, CORE_PIN17_BITMASK);
		CORE_PIN17_CONFIG = 5 | 0x10;
		CORE_PIN17_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set4() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN18_DDRREG, CORE_PIN18_BITMASK);
		CORE_PIN18_CONFIG = 5 | 0x10;
		CORE_PIN18_PADCONFIG = CONFIG_PULLUP;
	}
	inline void set5() __attribute__((always_inline)) {
		GPIO_SETBIT_ATOMIC(&CORE_PIN19_DDRREG, CORE_PIN19_BITMASK);
		CORE_PIN19_CONFIG = 5 | 0x10;
		CORE_PIN19_PADCONFIG = CONFIG_PULLUP;
	}
	inline void clr0() __attribute__((always_inline)) {
		CORE_PIN14_CONFIG = 5 | 0x10;
		CORE_PIN14_PADCONFIG = ((CORE_PIN14_PORTREG & CORE_PIN14_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN14_DDRREG, CORE_PIN14_BITMASK);
	}
	inline void clr1() __attribute__((always_inline)) {
		CORE_PIN15_CONFIG = 5 | 0x10;
		CORE_PIN15_PADCONFIG = ((CORE_PIN15_PORTREG & CORE_PIN15_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN15_DDRREG, CORE_PIN15_BITMASK);
	}
	inline void clr2() __attribute__((always_inline)) {
		CORE_PIN16_CONFIG = 5 | 0x10;
		CORE_PIN16_PADCONFIG = ((CORE_PIN16_PORTREG & CORE_PIN16_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN16_DDRREG, CORE_PIN16_BITMASK);
	}
	inline void clr3() __attribute__((always_inline)) {
		CORE_PIN17_CONFIG = 5 | 0x10;
		CORE_PIN17_PADCONFIG = ((CORE_PIN17_PORTREG & CORE_PIN17_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN17_DDRREG, CORE_PIN17_BITMASK);
	}
	inline void clr4() __attribute__((always_inline)) {
		CORE_PIN18_CONFIG = 5 | 0x10;
		CORE_PIN18_PADCONFIG = ((CORE_PIN18_PORTREG & CORE_PIN18_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN18_DDRREG, CORE_PIN18_BITMASK);
	}
	inline void clr5() __attribute__((always_inline)) {
		CORE_PIN19_CONFIG = 5 | 0x10;
		CORE_PIN19_PADCONFIG = ((CORE_PIN19_PORTREG & CORE_PIN19_BITMASK)
		  ? CONFIG_PULLUP : CONFIG_NOPULLUP);
		GPIO_CLRBIT_ATOMIC(&CORE_PIN19_DDRREG, CORE_PIN19_BITMASK);
	}
};

extern DDRCemulation DDRC;


#define PINB0 0
#define PINB1 1
#define PINB2 2
#define PINB3 3
#define PINB4 4
#define PINB5 5
#define PINB6 6
#define PINB7 7
#define DDB0 0
#define DDB1 1
#define DDB2 2
#define DDB3 3
#define DDB4 4
#define DDB5 5
#define DDB6 6
#define DDB7 7
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2
#define PORTB3 3
#define PORTB4 4
#define PORTB5 5
#define PORTB6 6
#define PORTB7 7
#define PINC0 0
#define PINC1 1
#define PINC2 2
#define PINC3 3
#define PINC4 4
#define PINC5 5
#define PINC6 6
#define DDC0 0
#define DDC1 1
#define DDC2 2
#define DDC3 3
#define DDC4 4
#define DDC5 5
#define DDC6 6
#define PORTC0 0
#define PORTC1 1
#define PORTC2 2
#define PORTC3 3
#define PORTC4 4
#define PORTC5 5
#define PORTC6 6
#define PIND0 0
#define PIND1 1
#define PIND2 2
#define PIND3 3
#define PIND4 4
#define PIND5 5
#define PIND6 6
#define PIND7 7
#define DDD0 0
#define DDD1 1
#define DDD2 2
#define DDD3 3
#define DDD4 4
#define DDD5 5
#define DDD6 6
#define DDD7 7
#define PORTD0 0
#define PORTD1 1
#define PORTD2 2
#define PORTD3 3
#define PORTD4 4
#define PORTD5 5
#define PORTD6 6
#define PORTD7 7



#endif // __cplusplus

#endif
