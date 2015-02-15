/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "SPI.h"
#include "pins_arduino.h"


/**********************************************************/
/*     32 bit Teensy 3.0 and 3.1			  */
/**********************************************************/

SPIClass SPI;

uint8_t SPIClass::interruptMasksUsed = 0;
uint32_t SPIClass::interruptMask[(NVIC_NUM_INTERRUPTS+31)/32];
uint32_t SPIClass::interruptSave[(NVIC_NUM_INTERRUPTS+31)/32];
#ifdef SPI_TRANSACTION_MISMATCH_LED
uint8_t SPIClass::inTransactionFlag = 0;
#endif

void SPIClass::begin()
{
	SIM_SCGC6 |= SIM_SCGC6_SPI0;
	SPI0_MCR = SPI_MCR_MDIS | SPI_MCR_HALT | SPI_MCR_PCSIS(0x1F);
	SPI0_CTAR0 = SPI_CTAR_FMSZ(7) | SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
	SPI0_CTAR1 = SPI_CTAR_FMSZ(15) | SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1);
	SPI0_MCR = SPI_MCR_MSTR | SPI_MCR_PCSIS(0x1F);
	SPCR.enable_pins(); // pins managed by SPCRemulation in avr_emulation.h
}

void SPIClass::end() {
	SPCR.disable_pins();
	SPI0_MCR = SPI_MCR_MDIS | SPI_MCR_HALT | SPI_MCR_PCSIS(0x1F);
}

void SPIClass::usingInterrupt(IRQ_NUMBER_t interruptName)
{
	uint32_t n = (uint32_t)interruptName;

	if (n >= NVIC_NUM_INTERRUPTS) return;

	//Serial.print("usingInterrupt ");
	//Serial.println(n);
	interruptMasksUsed |= (1 << (n >> 5));
	interruptMask[n >> 5] |= (1 << (n & 0x1F));
	//Serial.printf("interruptMasksUsed = %d\n", interruptMasksUsed);
	//Serial.printf("interruptMask[0] = %08X\n", interruptMask[0]);
	//Serial.printf("interruptMask[1] = %08X\n", interruptMask[1]);
	//Serial.printf("interruptMask[2] = %08X\n", interruptMask[2]);
}

void SPIClass::notUsingInterrupt(IRQ_NUMBER_t interruptName)
{
	uint32_t n = (uint32_t)interruptName;
	if (n >= NVIC_NUM_INTERRUPTS) return;
	interruptMask[n >> 5] &= ~(1 << (n & 0x1F));
	if (interruptMask[n >> 5] == 0) {
		interruptMasksUsed &= ~(1 << (n >> 5));
	}
}

const uint16_t SPISettings::ctar_div_table[23] = {
	2, 3, 4, 5, 6, 8, 10, 12, 16, 20, 24, 32, 40,
	56, 64, 96, 128, 192, 256, 384, 512, 640, 768
};
const uint32_t SPISettings::ctar_clock_table[23] = {
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_DBR | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1),
	SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(1),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2),
	SPI_CTAR_PBR(2) | SPI_CTAR_BR(1) | SPI_CTAR_CSSCK(0),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(4) | SPI_CTAR_CSSCK(3),
	SPI_CTAR_PBR(2) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2),
	SPI_CTAR_PBR(3) | SPI_CTAR_BR(3) | SPI_CTAR_CSSCK(2),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(5) | SPI_CTAR_CSSCK(4),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(5) | SPI_CTAR_CSSCK(4),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(6) | SPI_CTAR_CSSCK(5),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(6) | SPI_CTAR_CSSCK(5),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(6),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(6),
	SPI_CTAR_PBR(0) | SPI_CTAR_BR(8) | SPI_CTAR_CSSCK(7),
	SPI_CTAR_PBR(2) | SPI_CTAR_BR(7) | SPI_CTAR_CSSCK(6),
	SPI_CTAR_PBR(1) | SPI_CTAR_BR(8) | SPI_CTAR_CSSCK(7)
};

static void updateCTAR(uint32_t ctar)
{
	if (SPI0_CTAR0 != ctar) {
		uint32_t mcr = SPI0_MCR;
		if (mcr & SPI_MCR_MDIS) {
			SPI0_CTAR0 = ctar;
			SPI0_CTAR1 = ctar | SPI_CTAR_FMSZ(8);
		} else {
			SPI0_MCR = SPI_MCR_MDIS | SPI_MCR_HALT | SPI_MCR_PCSIS(0x1F);
			SPI0_CTAR0 = ctar;
			SPI0_CTAR1 = ctar | SPI_CTAR_FMSZ(8);
			SPI0_MCR = mcr;
		}
	}
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
	SIM_SCGC6 |= SIM_SCGC6_SPI0;
	uint32_t ctar = SPI0_CTAR0;
	if (bitOrder == LSBFIRST) {
		ctar |= SPI_CTAR_LSBFE;
	} else {
		ctar &= ~SPI_CTAR_LSBFE;
	}
	updateCTAR(ctar);
}

void SPIClass::setDataMode(uint8_t dataMode)
{
	SIM_SCGC6 |= SIM_SCGC6_SPI0;

	// TODO: implement with native code

	SPCR = (SPCR & ~SPI_MODE_MASK) | dataMode;
}

void SPIClass::setClockDivider_noInline(uint32_t clk)
{
	SIM_SCGC6 |= SIM_SCGC6_SPI0;
	uint32_t ctar = SPI0_CTAR0;
	ctar &= (SPI_CTAR_CPOL | SPI_CTAR_CPHA | SPI_CTAR_LSBFE);
	if (ctar & SPI_CTAR_CPHA) {
		clk = (clk & 0xFFFF0FFF) | ((clk & 0xF000) >> 4);
	}
	ctar |= clk;
	updateCTAR(ctar);
}

bool SPIClass::pinIsChipSelect(uint8_t pin)
{
	if (pin == 10 || pin == 9 || pin == 6 || pin == 2 || pin == 15) return true;
	if (pin >= 20 && pin <= 23) return true;
	return false;
}

bool SPIClass::pinIsChipSelect(uint8_t pin1, uint8_t pin2)
{
	if (!pinIsChipSelect(pin1) || !pinIsChipSelect(pin2)) return false;
	if ((pin1 ==  2 && pin2 == 10) || (pin1 == 10 && pin2 ==  2)) return false;
	if ((pin1 ==  6 && pin2 ==  9) || (pin1 ==  9 && pin2 ==  6)) return false;
	if ((pin1 == 20 && pin2 == 23) || (pin1 == 23 && pin2 == 20)) return false;
	if ((pin1 == 21 && pin2 == 22) || (pin1 == 22 && pin2 == 21)) return false;
	return true;
}

uint8_t SPIClass::setCS(uint8_t pin)
{
	switch (pin) {
	  case 10: CORE_PIN10_CONFIG = PORT_PCR_MUX(2); return 0x01; // PTC4
	  case 2:  CORE_PIN2_CONFIG  = PORT_PCR_MUX(2); return 0x01; // PTD0
	  case 9:  CORE_PIN9_CONFIG  = PORT_PCR_MUX(2); return 0x02; // PTC3
	  case 6:  CORE_PIN6_CONFIG  = PORT_PCR_MUX(2); return 0x02; // PTD4
	  case 20: CORE_PIN20_CONFIG = PORT_PCR_MUX(2); return 0x04; // PTD5
	  case 23: CORE_PIN23_CONFIG = PORT_PCR_MUX(2); return 0x04; // PTC2
	  case 21: CORE_PIN21_CONFIG = PORT_PCR_MUX(2); return 0x08; // PTD6
	  case 22: CORE_PIN22_CONFIG = PORT_PCR_MUX(2); return 0x08; // PTC1
	  case 15: CORE_PIN15_CONFIG = PORT_PCR_MUX(2); return 0x10; // PTC0
	}
	return 0;
}


#endif
