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


#endif // __cplusplus

#endif
