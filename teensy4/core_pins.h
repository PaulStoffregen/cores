/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2018 PJRC.COM, LLC.
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

#pragma once
#include "imxrt.h"
#include "pins_arduino.h"

#define HIGH			1
#define LOW			0
#define INPUT			0
#define OUTPUT			1
#define INPUT_PULLUP		2
#define INPUT_PULLDOWN		3
#define OUTPUT_OPENDRAIN	4
#define INPUT_DISABLE		5
#define LSBFIRST		0
#define MSBFIRST		1
#define _BV(n)			(1<<(n))
#define CHANGE			4
#define FALLING			2
#define RISING			3


#if defined(__IMXRT1062__)

#define CORE_NUM_TOTAL_PINS	40
#define CORE_NUM_DIGITAL	40
#define CORE_NUM_INTERRUPT	40
#define CORE_NUM_ANALOG		14
#define CORE_NUM_PWM		27

#define CORE_PIN0_BIT		3
#define CORE_PIN1_BIT		2
#define CORE_PIN2_BIT		4
#define CORE_PIN3_BIT		5
#define CORE_PIN4_BIT		6
#define CORE_PIN5_BIT		8
#define CORE_PIN6_BIT		10
#define CORE_PIN7_BIT		17
#define CORE_PIN8_BIT		16
#define CORE_PIN9_BIT		11
#define CORE_PIN10_BIT		0
#define CORE_PIN11_BIT		2
#define CORE_PIN12_BIT		1
#define CORE_PIN13_BIT		3
#define CORE_PIN14_BIT		18
#define CORE_PIN15_BIT		19
#define CORE_PIN16_BIT		23
#define CORE_PIN17_BIT		22
#define CORE_PIN18_BIT		17
#define CORE_PIN19_BIT		16
#define CORE_PIN20_BIT		26
#define CORE_PIN21_BIT		27
#define CORE_PIN22_BIT		24
#define CORE_PIN23_BIT		25
#define CORE_PIN24_BIT		12
#define CORE_PIN25_BIT		13
#define CORE_PIN26_BIT		30
#define CORE_PIN27_BIT		31
#define CORE_PIN28_BIT		18
#define CORE_PIN29_BIT		31
#define CORE_PIN30_BIT		23
#define CORE_PIN31_BIT		22
#define CORE_PIN32_BIT		12
#define CORE_PIN33_BIT		7
#define CORE_PIN34_BIT		15
#define CORE_PIN35_BIT		14
#define CORE_PIN36_BIT		13
#define CORE_PIN37_BIT		12
#define CORE_PIN38_BIT		17
#define CORE_PIN39_BIT		16

#define CORE_PIN0_BITMASK	(1<<(CORE_PIN0_BIT))
#define CORE_PIN1_BITMASK	(1<<(CORE_PIN1_BIT))
#define CORE_PIN2_BITMASK	(1<<(CORE_PIN2_BIT))
#define CORE_PIN3_BITMASK	(1<<(CORE_PIN3_BIT))
#define CORE_PIN4_BITMASK	(1<<(CORE_PIN4_BIT))
#define CORE_PIN5_BITMASK	(1<<(CORE_PIN5_BIT))
#define CORE_PIN6_BITMASK	(1<<(CORE_PIN6_BIT))
#define CORE_PIN7_BITMASK	(1<<(CORE_PIN7_BIT))
#define CORE_PIN8_BITMASK	(1<<(CORE_PIN8_BIT))
#define CORE_PIN9_BITMASK	(1<<(CORE_PIN9_BIT))
#define CORE_PIN10_BITMASK	(1<<(CORE_PIN10_BIT))
#define CORE_PIN11_BITMASK	(1<<(CORE_PIN11_BIT))
#define CORE_PIN12_BITMASK	(1<<(CORE_PIN12_BIT))
#define CORE_PIN13_BITMASK	(1<<(CORE_PIN13_BIT))
#define CORE_PIN14_BITMASK	(1<<(CORE_PIN14_BIT))
#define CORE_PIN15_BITMASK	(1<<(CORE_PIN15_BIT))
#define CORE_PIN16_BITMASK	(1<<(CORE_PIN16_BIT))
#define CORE_PIN17_BITMASK	(1<<(CORE_PIN17_BIT))
#define CORE_PIN18_BITMASK	(1<<(CORE_PIN18_BIT))
#define CORE_PIN19_BITMASK	(1<<(CORE_PIN19_BIT))
#define CORE_PIN20_BITMASK	(1<<(CORE_PIN20_BIT))
#define CORE_PIN21_BITMASK	(1<<(CORE_PIN21_BIT))
#define CORE_PIN22_BITMASK	(1<<(CORE_PIN22_BIT))
#define CORE_PIN23_BITMASK	(1<<(CORE_PIN23_BIT))
#define CORE_PIN24_BITMASK	(1<<(CORE_PIN24_BIT))
#define CORE_PIN25_BITMASK	(1<<(CORE_PIN25_BIT))
#define CORE_PIN26_BITMASK	(1<<(CORE_PIN26_BIT))
#define CORE_PIN27_BITMASK	(1<<(CORE_PIN27_BIT))
#define CORE_PIN28_BITMASK	(1<<(CORE_PIN28_BIT))
#define CORE_PIN29_BITMASK	(1<<(CORE_PIN29_BIT))
#define CORE_PIN30_BITMASK	(1<<(CORE_PIN30_BIT))
#define CORE_PIN31_BITMASK	(1<<(CORE_PIN31_BIT))
#define CORE_PIN32_BITMASK	(1<<(CORE_PIN32_BIT))
#define CORE_PIN33_BITMASK	(1<<(CORE_PIN33_BIT))
#define CORE_PIN34_BITMASK	(1<<(CORE_PIN34_BIT))
#define CORE_PIN35_BITMASK	(1<<(CORE_PIN35_BIT))
#define CORE_PIN36_BITMASK	(1<<(CORE_PIN36_BIT))
#define CORE_PIN37_BITMASK	(1<<(CORE_PIN37_BIT))
#define CORE_PIN38_BITMASK	(1<<(CORE_PIN38_BIT))
#define CORE_PIN39_BITMASK	(1<<(CORE_PIN39_BIT))


// Fast GPIO
#define CORE_PIN0_PORTREG	GPIO6_DR
#define CORE_PIN1_PORTREG	GPIO6_DR
#define CORE_PIN2_PORTREG	GPIO9_DR
#define CORE_PIN3_PORTREG	GPIO9_DR
#define CORE_PIN4_PORTREG	GPIO9_DR
#define CORE_PIN5_PORTREG	GPIO9_DR
#define CORE_PIN6_PORTREG	GPIO7_DR
#define CORE_PIN7_PORTREG	GPIO7_DR
#define CORE_PIN8_PORTREG	GPIO7_DR
#define CORE_PIN9_PORTREG	GPIO7_DR
#define CORE_PIN10_PORTREG	GPIO7_DR
#define CORE_PIN11_PORTREG	GPIO7_DR
#define CORE_PIN12_PORTREG	GPIO7_DR
#define CORE_PIN13_PORTREG	GPIO7_DR
#define CORE_PIN14_PORTREG	GPIO6_DR
#define CORE_PIN15_PORTREG	GPIO6_DR
#define CORE_PIN16_PORTREG	GPIO6_DR
#define CORE_PIN17_PORTREG	GPIO6_DR
#define CORE_PIN18_PORTREG	GPIO6_DR
#define CORE_PIN19_PORTREG	GPIO6_DR
#define CORE_PIN20_PORTREG	GPIO6_DR
#define CORE_PIN21_PORTREG	GPIO6_DR
#define CORE_PIN22_PORTREG	GPIO6_DR
#define CORE_PIN23_PORTREG	GPIO6_DR
#define CORE_PIN24_PORTREG	GPIO6_DR
#define CORE_PIN25_PORTREG	GPIO6_DR
#define CORE_PIN26_PORTREG	GPIO6_DR
#define CORE_PIN27_PORTREG	GPIO6_DR
#define CORE_PIN28_PORTREG	GPIO8_DR
#define CORE_PIN29_PORTREG	GPIO9_DR
#define CORE_PIN30_PORTREG	GPIO8_DR
#define CORE_PIN31_PORTREG	GPIO8_DR
#define CORE_PIN32_PORTREG	GPIO7_DR
#define CORE_PIN33_PORTREG	GPIO9_DR
#define CORE_PIN34_PORTREG	GPIO8_DR
#define CORE_PIN35_PORTREG	GPIO8_DR
#define CORE_PIN36_PORTREG	GPIO8_DR
#define CORE_PIN37_PORTREG	GPIO8_DR
#define CORE_PIN38_PORTREG	GPIO8_DR
#define CORE_PIN39_PORTREG	GPIO8_DR

#define CORE_PIN0_PORTSET	GPIO6_DR_SET
#define CORE_PIN1_PORTSET	GPIO6_DR_SET
#define CORE_PIN2_PORTSET	GPIO9_DR_SET
#define CORE_PIN3_PORTSET	GPIO9_DR_SET
#define CORE_PIN4_PORTSET	GPIO9_DR_SET
#define CORE_PIN5_PORTSET	GPIO9_DR_SET
#define CORE_PIN6_PORTSET	GPIO7_DR_SET
#define CORE_PIN7_PORTSET	GPIO7_DR_SET
#define CORE_PIN8_PORTSET	GPIO7_DR_SET
#define CORE_PIN9_PORTSET	GPIO7_DR_SET
#define CORE_PIN10_PORTSET	GPIO7_DR_SET
#define CORE_PIN11_PORTSET	GPIO7_DR_SET
#define CORE_PIN12_PORTSET	GPIO7_DR_SET
#define CORE_PIN13_PORTSET	GPIO7_DR_SET
#define CORE_PIN14_PORTSET	GPIO6_DR_SET
#define CORE_PIN15_PORTSET	GPIO6_DR_SET
#define CORE_PIN16_PORTSET	GPIO6_DR_SET
#define CORE_PIN17_PORTSET	GPIO6_DR_SET
#define CORE_PIN18_PORTSET	GPIO6_DR_SET
#define CORE_PIN19_PORTSET	GPIO6_DR_SET
#define CORE_PIN20_PORTSET	GPIO6_DR_SET
#define CORE_PIN21_PORTSET	GPIO6_DR_SET
#define CORE_PIN22_PORTSET	GPIO6_DR_SET
#define CORE_PIN23_PORTSET	GPIO6_DR_SET
#define CORE_PIN24_PORTSET	GPIO6_DR_SET
#define CORE_PIN25_PORTSET	GPIO6_DR_SET
#define CORE_PIN26_PORTSET	GPIO6_DR_SET
#define CORE_PIN27_PORTSET	GPIO6_DR_SET
#define CORE_PIN28_PORTSET	GPIO8_DR_SET
#define CORE_PIN29_PORTSET	GPIO9_DR_SET
#define CORE_PIN30_PORTSET	GPIO8_DR_SET
#define CORE_PIN31_PORTSET	GPIO8_DR_SET
#define CORE_PIN32_PORTSET	GPIO7_DR_SET
#define CORE_PIN33_PORTSET	GPIO9_DR_SET
#define CORE_PIN34_PORTSET	GPIO8_DR_SET
#define CORE_PIN35_PORTSET	GPIO8_DR_SET
#define CORE_PIN36_PORTSET	GPIO8_DR_SET
#define CORE_PIN37_PORTSET	GPIO8_DR_SET
#define CORE_PIN38_PORTSET	GPIO8_DR_SET
#define CORE_PIN39_PORTSET	GPIO8_DR_SET

#define CORE_PIN0_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN1_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN2_PORTCLEAR	GPIO9_DR_CLEAR
#define CORE_PIN3_PORTCLEAR	GPIO9_DR_CLEAR
#define CORE_PIN4_PORTCLEAR	GPIO9_DR_CLEAR
#define CORE_PIN5_PORTCLEAR	GPIO9_DR_CLEAR
#define CORE_PIN6_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN7_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN8_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN9_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN10_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN11_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN12_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN13_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN14_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN15_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN16_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN17_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN18_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN19_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN20_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN21_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN22_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN23_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN24_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN25_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN26_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN27_PORTCLEAR	GPIO6_DR_CLEAR
#define CORE_PIN28_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN29_PORTCLEAR	GPIO9_DR_CLEAR
#define CORE_PIN30_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN31_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN32_PORTCLEAR	GPIO7_DR_CLEAR
#define CORE_PIN33_PORTCLEAR	GPIO9_DR_CLEAR
#define CORE_PIN34_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN35_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN36_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN37_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN38_PORTCLEAR	GPIO8_DR_CLEAR
#define CORE_PIN39_PORTCLEAR	GPIO8_DR_CLEAR

#define CORE_PIN0_DDRREG	GPIO6_GDIR
#define CORE_PIN1_DDRREG	GPIO6_GDIR
#define CORE_PIN2_DDRREG	GPIO9_GDIR
#define CORE_PIN3_DDRREG	GPIO9_GDIR
#define CORE_PIN4_DDRREG	GPIO9_GDIR
#define CORE_PIN5_DDRREG	GPIO9_GDIR
#define CORE_PIN6_DDRREG	GPIO7_GDIR
#define CORE_PIN7_DDRREG	GPIO7_GDIR
#define CORE_PIN8_DDRREG	GPIO7_GDIR
#define CORE_PIN9_DDRREG	GPIO7_GDIR
#define CORE_PIN10_DDRREG	GPIO7_GDIR
#define CORE_PIN11_DDRREG	GPIO7_GDIR
#define CORE_PIN12_DDRREG	GPIO7_GDIR
#define CORE_PIN13_DDRREG	GPIO7_GDIR
#define CORE_PIN14_DDRREG	GPIO6_GDIR
#define CORE_PIN15_DDRREG	GPIO6_GDIR
#define CORE_PIN16_DDRREG	GPIO6_GDIR
#define CORE_PIN17_DDRREG	GPIO6_GDIR
#define CORE_PIN18_DDRREG	GPIO6_GDIR
#define CORE_PIN19_DDRREG	GPIO6_GDIR
#define CORE_PIN20_DDRREG	GPIO6_GDIR
#define CORE_PIN21_DDRREG	GPIO6_GDIR
#define CORE_PIN22_DDRREG	GPIO6_GDIR
#define CORE_PIN23_DDRREG	GPIO6_GDIR
#define CORE_PIN24_DDRREG	GPIO6_GDIR
#define CORE_PIN25_DDRREG	GPIO6_GDIR
#define CORE_PIN26_DDRREG	GPIO6_GDIR
#define CORE_PIN27_DDRREG	GPIO6_GDIR
#define CORE_PIN28_DDRREG	GPIO8_GDIR
#define CORE_PIN29_DDRREG	GPIO9_GDIR
#define CORE_PIN30_DDRREG	GPIO8_GDIR
#define CORE_PIN31_DDRREG	GPIO8_GDIR
#define CORE_PIN32_DDRREG	GPIO7_GDIR
#define CORE_PIN33_DDRREG	GPIO9_GDIR
#define CORE_PIN34_DDRREG	GPIO8_GDIR
#define CORE_PIN35_DDRREG	GPIO8_GDIR
#define CORE_PIN36_DDRREG	GPIO8_GDIR
#define CORE_PIN37_DDRREG	GPIO8_GDIR
#define CORE_PIN38_DDRREG	GPIO8_GDIR
#define CORE_PIN39_DDRREG	GPIO8_GDIR

#define CORE_PIN0_PINREG	GPIO6_PSR
#define CORE_PIN1_PINREG	GPIO6_PSR
#define CORE_PIN2_PINREG	GPIO9_PSR
#define CORE_PIN3_PINREG	GPIO9_PSR
#define CORE_PIN4_PINREG	GPIO9_PSR
#define CORE_PIN5_PINREG	GPIO9_PSR
#define CORE_PIN6_PINREG	GPIO7_PSR
#define CORE_PIN7_PINREG	GPIO7_PSR
#define CORE_PIN8_PINREG	GPIO7_PSR
#define CORE_PIN9_PINREG	GPIO7_PSR
#define CORE_PIN10_PINREG	GPIO7_PSR
#define CORE_PIN11_PINREG	GPIO7_PSR
#define CORE_PIN12_PINREG	GPIO7_PSR
#define CORE_PIN13_PINREG	GPIO7_PSR
#define CORE_PIN14_PINREG	GPIO6_PSR
#define CORE_PIN15_PINREG	GPIO6_PSR
#define CORE_PIN16_PINREG	GPIO6_PSR
#define CORE_PIN17_PINREG	GPIO6_PSR
#define CORE_PIN18_PINREG	GPIO6_PSR
#define CORE_PIN19_PINREG	GPIO6_PSR
#define CORE_PIN20_PINREG	GPIO6_PSR
#define CORE_PIN21_PINREG	GPIO6_PSR
#define CORE_PIN22_PINREG	GPIO6_PSR
#define CORE_PIN23_PINREG	GPIO6_PSR
#define CORE_PIN24_PINREG	GPIO6_PSR
#define CORE_PIN25_PINREG	GPIO6_PSR
#define CORE_PIN26_PINREG	GPIO6_PSR
#define CORE_PIN27_PINREG	GPIO6_PSR
#define CORE_PIN28_PINREG	GPIO8_PSR
#define CORE_PIN29_PINREG	GPIO9_PSR
#define CORE_PIN30_PINREG	GPIO8_PSR
#define CORE_PIN31_PINREG	GPIO8_PSR
#define CORE_PIN32_PINREG	GPIO7_PSR
#define CORE_PIN33_PINREG	GPIO9_PSR
#define CORE_PIN34_PINREG	GPIO8_PSR
#define CORE_PIN35_PINREG	GPIO8_PSR
#define CORE_PIN36_PINREG	GPIO8_PSR
#define CORE_PIN37_PINREG	GPIO8_PSR
#define CORE_PIN38_PINREG	GPIO8_PSR
#define CORE_PIN39_PINREG	GPIO8_PSR



// mux config registers control which peripheral uses the pin
#define CORE_PIN0_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03
#define CORE_PIN1_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02
#define CORE_PIN2_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04
#define CORE_PIN3_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05
#define CORE_PIN4_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06
#define CORE_PIN5_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08
#define CORE_PIN6_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10
#define CORE_PIN7_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01
#define CORE_PIN8_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00
#define CORE_PIN9_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11
#define CORE_PIN10_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00
#define CORE_PIN11_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02
#define CORE_PIN12_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01
#define CORE_PIN13_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03
#define CORE_PIN14_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02
#define CORE_PIN15_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03
#define CORE_PIN16_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07
#define CORE_PIN17_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06
#define CORE_PIN18_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01
#define CORE_PIN19_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00
#define CORE_PIN20_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10
#define CORE_PIN21_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11
#define CORE_PIN22_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08
#define CORE_PIN23_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09
#define CORE_PIN24_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12
#define CORE_PIN25_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13
#define CORE_PIN26_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14
#define CORE_PIN27_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15
#define CORE_PIN28_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32
#define CORE_PIN29_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31
#define CORE_PIN30_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37
#define CORE_PIN31_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36
#define CORE_PIN32_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12
#define CORE_PIN33_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07
#define CORE_PIN34_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_03
#define CORE_PIN35_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_02
#define CORE_PIN36_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01
#define CORE_PIN37_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_00
#define CORE_PIN38_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05
#define CORE_PIN39_CONFIG	IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04

// pad config registers control pullup/pulldown/keeper, drive strength, etc
#define CORE_PIN0_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03
#define CORE_PIN1_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02
#define CORE_PIN2_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04
#define CORE_PIN3_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05
#define CORE_PIN4_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06
#define CORE_PIN5_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08
#define CORE_PIN6_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10
#define CORE_PIN7_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01
#define CORE_PIN8_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00
#define CORE_PIN9_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11
#define CORE_PIN10_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00
#define CORE_PIN11_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02
#define CORE_PIN12_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01
#define CORE_PIN13_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03
#define CORE_PIN14_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02
#define CORE_PIN15_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03
#define CORE_PIN16_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07
#define CORE_PIN17_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06
#define CORE_PIN18_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01
#define CORE_PIN19_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00
#define CORE_PIN20_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10
#define CORE_PIN21_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11
#define CORE_PIN22_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08
#define CORE_PIN23_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09
#define CORE_PIN24_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12
#define CORE_PIN25_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13
#define CORE_PIN26_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14
#define CORE_PIN27_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15
#define CORE_PIN28_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32
#define CORE_PIN29_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31
#define CORE_PIN30_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37
#define CORE_PIN31_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36
#define CORE_PIN32_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12
#define CORE_PIN33_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07
#define CORE_PIN34_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_03
#define CORE_PIN35_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_02
#define CORE_PIN36_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_01
#define CORE_PIN37_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00
#define CORE_PIN38_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_05
#define CORE_PIN39_PADCONFIG	IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_04

#define CORE_LED0_PIN		13

#define CORE_ADC0_PIN		14
#define CORE_ADC1_PIN		15
#define CORE_ADC2_PIN		16
#define CORE_ADC3_PIN		17
#define CORE_ADC4_PIN		18
#define CORE_ADC5_PIN		19
#define CORE_ADC6_PIN		20
#define CORE_ADC7_PIN		21
#define CORE_ADC8_PIN		22
#define CORE_ADC9_PIN		23

#define CORE_RXD0_PIN		0
#define CORE_TXD0_PIN		1
#define CORE_RXD1_PIN		7
#define CORE_TXD1_PIN		8
#define CORE_RXD2_PIN		15
#define CORE_TXD2_PIN		14
#define CORE_RXD3_PIN		16
#define CORE_TXD3_PIN		17
#define CORE_RXD4_PIN		21
#define CORE_TXD4_PIN		20
#define CORE_RXD5_PIN		25
#define CORE_TXD5_PIN		24
#define CORE_RXD6_PIN		28
#define CORE_TXD6_PIN		29

#define CORE_INT0_PIN		0
#define CORE_INT1_PIN		1
#define CORE_INT2_PIN		2
#define CORE_INT3_PIN		3
#define CORE_INT4_PIN		4
#define CORE_INT5_PIN		5
#define CORE_INT6_PIN		6
#define CORE_INT7_PIN		7
#define CORE_INT8_PIN		8
#define CORE_INT9_PIN		9
#define CORE_INT10_PIN		10
#define CORE_INT11_PIN		11
#define CORE_INT12_PIN		12
#define CORE_INT13_PIN		13
#define CORE_INT14_PIN		14
#define CORE_INT15_PIN		15
#define CORE_INT16_PIN		16
#define CORE_INT17_PIN		17
#define CORE_INT18_PIN		18
#define CORE_INT19_PIN		19
#define CORE_INT20_PIN		20
#define CORE_INT21_PIN		21
#define CORE_INT22_PIN		22
#define CORE_INT23_PIN		23
#define CORE_INT24_PIN		24
#define CORE_INT25_PIN		25
#define CORE_INT26_PIN		26
#define CORE_INT27_PIN		27
#define CORE_INT28_PIN		28
#define CORE_INT29_PIN		29
#define CORE_INT30_PIN		30
#define CORE_INT31_PIN		31
#define CORE_INT32_PIN		32
#define CORE_INT33_PIN		33
#define CORE_INT34_PIN		34
#define CORE_INT35_PIN		35
#define CORE_INT36_PIN		36
#define CORE_INT37_PIN		37
#define CORE_INT38_PIN		38
#define CORE_INT39_PIN		39
#define CORE_INT_EVERY_PIN	1

#endif // __IMXRT1062__

#ifdef __cplusplus
extern "C" {
#endif

//TODO:
//#define analogInputToDigitalPin(p)
//#define digitalPinHasPWM(p)
#define digitalPinToInterrupt(p)  ((p) < NUM_DIGITAL_PINS ? (p) : -1)

void digitalWrite(uint8_t pin, uint8_t val);
static inline void digitalWriteFast(uint8_t pin, uint8_t val) __attribute__((always_inline, unused));
static inline void digitalWriteFast(uint8_t pin, uint8_t val)
{
	if (__builtin_constant_p(pin)) {
		if (val) {
			if (pin == 0) {
				CORE_PIN0_PORTSET = CORE_PIN0_BITMASK;
			} else if (pin == 1) {
				CORE_PIN1_PORTSET = CORE_PIN1_BITMASK;
			} else if (pin == 2) {
				CORE_PIN2_PORTSET = CORE_PIN2_BITMASK;
			} else if (pin == 3) {
				CORE_PIN3_PORTSET = CORE_PIN3_BITMASK;
			} else if (pin == 4) {
				CORE_PIN4_PORTSET = CORE_PIN4_BITMASK;
			} else if (pin == 5) {
				CORE_PIN5_PORTSET = CORE_PIN5_BITMASK;
			} else if (pin == 6) {
				CORE_PIN6_PORTSET = CORE_PIN6_BITMASK;
			} else if (pin == 7) {
				CORE_PIN7_PORTSET = CORE_PIN7_BITMASK;
			} else if (pin == 8) {
				CORE_PIN8_PORTSET = CORE_PIN8_BITMASK;
			} else if (pin == 9) {
				CORE_PIN9_PORTSET = CORE_PIN9_BITMASK;
			} else if (pin == 10) {
				CORE_PIN10_PORTSET = CORE_PIN10_BITMASK;
			} else if (pin == 11) {
				CORE_PIN11_PORTSET = CORE_PIN11_BITMASK;
			} else if (pin == 12) {
				CORE_PIN12_PORTSET = CORE_PIN12_BITMASK;
			} else if (pin == 13) {
				CORE_PIN13_PORTSET = CORE_PIN13_BITMASK;
			} else if (pin == 14) {
				CORE_PIN14_PORTSET = CORE_PIN14_BITMASK;
			} else if (pin == 15) {
				CORE_PIN15_PORTSET = CORE_PIN15_BITMASK;
			} else if (pin == 16) {
				CORE_PIN16_PORTSET = CORE_PIN16_BITMASK;
			} else if (pin == 17) {
				CORE_PIN17_PORTSET = CORE_PIN17_BITMASK;
			} else if (pin == 18) {
				CORE_PIN18_PORTSET = CORE_PIN18_BITMASK;
			} else if (pin == 19) {
				CORE_PIN19_PORTSET = CORE_PIN19_BITMASK;
			} else if (pin == 20) {
				CORE_PIN20_PORTSET = CORE_PIN20_BITMASK;
			} else if (pin == 21) {
				CORE_PIN21_PORTSET = CORE_PIN21_BITMASK;
			} else if (pin == 22) {
				CORE_PIN22_PORTSET = CORE_PIN22_BITMASK;
			} else if (pin == 23) {
				CORE_PIN23_PORTSET = CORE_PIN23_BITMASK;
			} else if (pin == 24) {
				CORE_PIN24_PORTSET = CORE_PIN24_BITMASK;
			} else if (pin == 25) {
				CORE_PIN25_PORTSET = CORE_PIN25_BITMASK;
			} else if (pin == 26) {
				CORE_PIN26_PORTSET = CORE_PIN26_BITMASK;
			} else if (pin == 27) {
				CORE_PIN27_PORTSET = CORE_PIN27_BITMASK;
			} else if (pin == 28) {
				CORE_PIN28_PORTSET = CORE_PIN28_BITMASK;
			} else if (pin == 29) {
				CORE_PIN29_PORTSET = CORE_PIN29_BITMASK;
			} else if (pin == 30) {
				CORE_PIN30_PORTSET = CORE_PIN30_BITMASK;
			} else if (pin == 31) {
				CORE_PIN31_PORTSET = CORE_PIN31_BITMASK;
			} else if (pin == 32) {
				CORE_PIN32_PORTSET = CORE_PIN32_BITMASK;
			} else if (pin == 33) {
				CORE_PIN33_PORTSET = CORE_PIN33_BITMASK;
#if defined(__IMXRT1062__)
			} else if (pin == 34) {
				CORE_PIN34_PORTSET = CORE_PIN34_BITMASK;
			} else if (pin == 35) {
				CORE_PIN35_PORTSET = CORE_PIN35_BITMASK;
			} else if (pin == 36) {
				CORE_PIN36_PORTSET = CORE_PIN36_BITMASK;
			} else if (pin == 37) {
				CORE_PIN37_PORTSET = CORE_PIN37_BITMASK;
			} else if (pin == 38) {
				CORE_PIN38_PORTSET = CORE_PIN38_BITMASK;
			} else if (pin == 39) {
				CORE_PIN39_PORTSET = CORE_PIN39_BITMASK;
#endif
			}
		} else {
			if (pin == 0) {
				CORE_PIN0_PORTCLEAR = CORE_PIN0_BITMASK;
			} else if (pin == 1) {
				CORE_PIN1_PORTCLEAR = CORE_PIN1_BITMASK;
			} else if (pin == 2) {
				CORE_PIN2_PORTCLEAR = CORE_PIN2_BITMASK;
			} else if (pin == 3) {
				CORE_PIN3_PORTCLEAR = CORE_PIN3_BITMASK;
			} else if (pin == 4) {
				CORE_PIN4_PORTCLEAR = CORE_PIN4_BITMASK;
			} else if (pin == 5) {
				CORE_PIN5_PORTCLEAR = CORE_PIN5_BITMASK;
			} else if (pin == 6) {
				CORE_PIN6_PORTCLEAR = CORE_PIN6_BITMASK;
			} else if (pin == 7) {
				CORE_PIN7_PORTCLEAR = CORE_PIN7_BITMASK;
			} else if (pin == 8) {
				CORE_PIN8_PORTCLEAR = CORE_PIN8_BITMASK;
			} else if (pin == 9) {
				CORE_PIN9_PORTCLEAR = CORE_PIN9_BITMASK;
			} else if (pin == 10) {
				CORE_PIN10_PORTCLEAR = CORE_PIN10_BITMASK;
			} else if (pin == 11) {
				CORE_PIN11_PORTCLEAR = CORE_PIN11_BITMASK;
			} else if (pin == 12) {
				CORE_PIN12_PORTCLEAR = CORE_PIN12_BITMASK;
			} else if (pin == 13) {
				CORE_PIN13_PORTCLEAR = CORE_PIN13_BITMASK;
			} else if (pin == 14) {
				CORE_PIN14_PORTCLEAR = CORE_PIN14_BITMASK;
			} else if (pin == 15) {
				CORE_PIN15_PORTCLEAR = CORE_PIN15_BITMASK;
			} else if (pin == 16) {
				CORE_PIN16_PORTCLEAR = CORE_PIN16_BITMASK;
			} else if (pin == 17) {
				CORE_PIN17_PORTCLEAR = CORE_PIN17_BITMASK;
			} else if (pin == 18) {
				CORE_PIN18_PORTCLEAR = CORE_PIN18_BITMASK;
			} else if (pin == 19) {
				CORE_PIN19_PORTCLEAR = CORE_PIN19_BITMASK;
			} else if (pin == 20) {
				CORE_PIN20_PORTCLEAR = CORE_PIN20_BITMASK;
			} else if (pin == 21) {
				CORE_PIN21_PORTCLEAR = CORE_PIN21_BITMASK;
			} else if (pin == 22) {
				CORE_PIN22_PORTCLEAR = CORE_PIN22_BITMASK;
			} else if (pin == 23) {
				CORE_PIN23_PORTCLEAR = CORE_PIN23_BITMASK;
			} else if (pin == 24) {
				CORE_PIN24_PORTCLEAR = CORE_PIN24_BITMASK;
			} else if (pin == 25) {
				CORE_PIN25_PORTCLEAR = CORE_PIN25_BITMASK;
			} else if (pin == 26) {
				CORE_PIN26_PORTCLEAR = CORE_PIN26_BITMASK;
			} else if (pin == 27) {
				CORE_PIN27_PORTCLEAR = CORE_PIN27_BITMASK;
			} else if (pin == 28) {
				CORE_PIN28_PORTCLEAR = CORE_PIN28_BITMASK;
			} else if (pin == 29) {
				CORE_PIN29_PORTCLEAR = CORE_PIN29_BITMASK;
			} else if (pin == 30) {
				CORE_PIN30_PORTCLEAR = CORE_PIN30_BITMASK;
			} else if (pin == 31) {
				CORE_PIN31_PORTCLEAR = CORE_PIN31_BITMASK;
			} else if (pin == 32) {
				CORE_PIN32_PORTCLEAR = CORE_PIN32_BITMASK;
			} else if (pin == 33) {
				CORE_PIN33_PORTCLEAR = CORE_PIN33_BITMASK;
#if defined(__IMXRT1062__)
			} else if (pin == 34) {
				CORE_PIN34_PORTCLEAR = CORE_PIN34_BITMASK;
			} else if (pin == 35) {
				CORE_PIN35_PORTCLEAR = CORE_PIN35_BITMASK;
			} else if (pin == 36) {
				CORE_PIN36_PORTCLEAR = CORE_PIN36_BITMASK;
			} else if (pin == 37) {
				CORE_PIN37_PORTCLEAR = CORE_PIN37_BITMASK;
			} else if (pin == 38) {
				CORE_PIN38_PORTCLEAR = CORE_PIN38_BITMASK;
			} else if (pin == 39) {
				CORE_PIN39_PORTCLEAR = CORE_PIN39_BITMASK;
#endif
			}
		}
	} else {
		if(val) *portSetRegister(pin) = digitalPinToBitMask(pin);
		else *portClearRegister(pin) = digitalPinToBitMask(pin);
	}
}

uint8_t digitalRead(uint8_t pin);
static inline uint8_t digitalReadFast(uint8_t pin) __attribute__((always_inline, unused));
static inline uint8_t digitalReadFast(uint8_t pin)
{
	if (__builtin_constant_p(pin)) {
		if (pin == 0) {
			return (CORE_PIN0_PINREG & CORE_PIN0_BITMASK) ? 1 : 0;
		} else if (pin == 1) {
			return (CORE_PIN1_PINREG & CORE_PIN1_BITMASK) ? 1 : 0;
		} else if (pin == 2) {
			return (CORE_PIN2_PINREG & CORE_PIN2_BITMASK) ? 1 : 0;
		} else if (pin == 3) {
			return (CORE_PIN3_PINREG & CORE_PIN3_BITMASK) ? 1 : 0;
		} else if (pin == 4) {
			return (CORE_PIN4_PINREG & CORE_PIN4_BITMASK) ? 1 : 0;
		} else if (pin == 5) {
			return (CORE_PIN5_PINREG & CORE_PIN5_BITMASK) ? 1 : 0;
		} else if (pin == 6) {
			return (CORE_PIN6_PINREG & CORE_PIN6_BITMASK) ? 1 : 0;
		} else if (pin == 7) {
			return (CORE_PIN7_PINREG & CORE_PIN7_BITMASK) ? 1 : 0;
		} else if (pin == 8) {
			return (CORE_PIN8_PINREG & CORE_PIN8_BITMASK) ? 1 : 0;
		} else if (pin == 9) {
			return (CORE_PIN9_PINREG & CORE_PIN9_BITMASK) ? 1 : 0;
		} else if (pin == 10) {
			return (CORE_PIN10_PINREG & CORE_PIN10_BITMASK) ? 1 : 0;
		} else if (pin == 11) {
			return (CORE_PIN11_PINREG & CORE_PIN11_BITMASK) ? 1 : 0;
		} else if (pin == 12) {
			return (CORE_PIN12_PINREG & CORE_PIN12_BITMASK) ? 1 : 0;
		} else if (pin == 13) {
			return (CORE_PIN13_PINREG & CORE_PIN13_BITMASK) ? 1 : 0;
		} else if (pin == 14) {
			return (CORE_PIN14_PINREG & CORE_PIN14_BITMASK) ? 1 : 0;
		} else if (pin == 15) {
			return (CORE_PIN15_PINREG & CORE_PIN15_BITMASK) ? 1 : 0;
		} else if (pin == 16) {
			return (CORE_PIN16_PINREG & CORE_PIN16_BITMASK) ? 1 : 0;
		} else if (pin == 17) {
			return (CORE_PIN17_PINREG & CORE_PIN17_BITMASK) ? 1 : 0;
		} else if (pin == 18) {
			return (CORE_PIN18_PINREG & CORE_PIN18_BITMASK) ? 1 : 0;
		} else if (pin == 19) {
			return (CORE_PIN19_PINREG & CORE_PIN19_BITMASK) ? 1 : 0;
		} else if (pin == 20) {
			return (CORE_PIN20_PINREG & CORE_PIN20_BITMASK) ? 1 : 0;
		} else if (pin == 21) {
			return (CORE_PIN21_PINREG & CORE_PIN21_BITMASK) ? 1 : 0;
		} else if (pin == 22) {
			return (CORE_PIN22_PINREG & CORE_PIN22_BITMASK) ? 1 : 0;
		} else if (pin == 23) {
			return (CORE_PIN23_PINREG & CORE_PIN23_BITMASK) ? 1 : 0;
		} else if (pin == 24) {
			return (CORE_PIN24_PINREG & CORE_PIN24_BITMASK) ? 1 : 0;
		} else if (pin == 25) {
			return (CORE_PIN25_PINREG & CORE_PIN25_BITMASK) ? 1 : 0;
		} else if (pin == 26) {
			return (CORE_PIN26_PINREG & CORE_PIN26_BITMASK) ? 1 : 0;
		} else if (pin == 27) {
			return (CORE_PIN27_PINREG & CORE_PIN27_BITMASK) ? 1 : 0;
		} else if (pin == 28) {
			return (CORE_PIN28_PINREG & CORE_PIN28_BITMASK) ? 1 : 0;
		} else if (pin == 29) {
			return (CORE_PIN29_PINREG & CORE_PIN29_BITMASK) ? 1 : 0;
		} else if (pin == 30) {
			return (CORE_PIN30_PINREG & CORE_PIN30_BITMASK) ? 1 : 0;
		} else if (pin == 31) {
			return (CORE_PIN31_PINREG & CORE_PIN31_BITMASK) ? 1 : 0;
		} else if (pin == 32) {
			return (CORE_PIN32_PINREG & CORE_PIN32_BITMASK) ? 1 : 0;
		} else if (pin == 33) {
			return (CORE_PIN33_PINREG & CORE_PIN33_BITMASK) ? 1 : 0;
		} else {
			return 0;
		}
	} else {
		return (*portInputRegister(pin) & digitalPinToBitMask(pin)) ? 1 : 0;
	}
}


void pinMode(uint8_t pin, uint8_t mode);
void init_pins(void);
void analogWrite(uint8_t pin, int val);
uint32_t analogWriteRes(uint32_t bits);
static inline uint32_t analogWriteResolution(uint32_t bits) { return analogWriteRes(bits); }
void analogWriteFrequency(uint8_t pin, float frequency);
void attachInterrupt(uint8_t pin, void (*function)(void), int mode);
void detachInterrupt(uint8_t pin);
void _init_Teensyduino_internal_(void);
int analogRead(uint8_t pin);
void analogReference(uint8_t type);
void analogReadRes(unsigned int bits);
static inline void analogReadResolution(unsigned int bits) { analogReadRes(bits); }
void analogReadAveraging(unsigned int num);
void analog_init(void);
int touchRead(uint8_t pin);

static inline void shiftOut(uint8_t, uint8_t, uint8_t, uint8_t) __attribute__((always_inline, unused));
extern void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value) __attribute__((noinline));
extern void shiftOut_lsbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value) __attribute__((noinline));
extern void shiftOut_msbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value) __attribute__((noinline));

static inline void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
        if (__builtin_constant_p(bitOrder)) {
                if (bitOrder == LSBFIRST) {
                        shiftOut_lsbFirst(dataPin, clockPin, value);
                } else {
                        shiftOut_msbFirst(dataPin, clockPin, value);
                }
        } else {
                _shiftOut(dataPin, clockPin, bitOrder, value);
        }
}

static inline uint8_t shiftIn(uint8_t, uint8_t, uint8_t) __attribute__((always_inline, unused));
extern uint8_t _shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) __attribute__((noinline));
extern uint8_t shiftIn_lsbFirst(uint8_t dataPin, uint8_t clockPin) __attribute__((noinline));
extern uint8_t shiftIn_msbFirst(uint8_t dataPin, uint8_t clockPin) __attribute__((noinline));

static inline uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
        if (__builtin_constant_p(bitOrder)) {
                if (bitOrder == LSBFIRST) {
                        return shiftIn_lsbFirst(dataPin, clockPin);
                } else {
                        return shiftIn_msbFirst(dataPin, clockPin);
                }
        } else {
                return _shiftIn(dataPin, clockPin, bitOrder);
        }
}

void _reboot_Teensyduino_(void) __attribute__((noreturn));
void _restart_Teensyduino_(void) __attribute__((noreturn));

void yield(void);

void delay(uint32_t msec);

extern volatile uint32_t F_CPU_ACTUAL;
extern volatile uint32_t F_BUS_ACTUAL;
extern volatile uint32_t systick_millis_count;

static inline uint32_t millis(void) __attribute__((always_inline, unused));
static inline uint32_t millis(void)
{
	return systick_millis_count;
}

uint32_t micros(void);

static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayMicroseconds(uint32_t usec)
{
	uint32_t begin = ARM_DWT_CYCCNT;
	uint32_t cycles = F_CPU_ACTUAL / 1000000 * usec;
	// TODO: check if cycles is large, do a wait with yield calls until it's smaller
	while (ARM_DWT_CYCCNT - begin < cycles) ; // wait
}

static inline void delayNanoseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayNanoseconds(uint32_t nsec)
{
	uint32_t begin = ARM_DWT_CYCCNT;
	uint32_t cycles =   ((F_CPU_ACTUAL>>16) * nsec) / (1000000000UL>>16);
	while (ARM_DWT_CYCCNT - begin < cycles) ; // wait
}


unsigned long rtc_get(void);
void rtc_set(unsigned long t);
void rtc_compensate(int adjust);

void tempmon_init(void);
float tempmonGetTemp(void);
void tempmon_Start();
void tempmon_Stop();
void tempmon_PwrDwn();

#ifdef __cplusplus
}

class teensy3_clock_class
{
public:
        static unsigned long get(void) __attribute__((always_inline)) { return rtc_get(); }
        static void set(unsigned long t) __attribute__((always_inline)) { rtc_set(t); }
        static void compensate(int adj) __attribute__((always_inline)) { rtc_compensate(adj); }
};
extern teensy3_clock_class Teensy3Clock;

#endif // __cplusplus




