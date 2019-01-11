/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
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

#ifndef _SPIFIFO_h_
#define _SPIFIFO_h_

#include "avr_emulation.h"

#ifdef KINETISK

// The preferred way to set SPI speed is with SPI.beginTransaction()

#if F_BUS == 128000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0))		    //(128 / 3) * ((1+0)/2) = 21.3MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2))                //(128 / 2) * ((1+0)/4)
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(2))                //(128 / 3) * ((1+0)/4) = 10.6 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(6)) 		    //(128 / 2) * ((1+0)/8) 
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(6))                //(128 / 3) * ((1+0)/8) = 5.3 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(6))                //(128 / 5) * ((1+0)/8) = 3.2MHz

#elif F_BUS == 120000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(120 / 5) * ((1+1)/2)
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2))                //(120 / 2) * ((1+0)/4) = 15 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0))                //(120 / 5) * ((1+0)/2)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(120 / 5) * ((1+1)/6)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(2))                //(120 / 5) * ((1+0)/4)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(4)) 		    //(120 / 5) * ((1+0)/6)

#elif F_BUS == 108000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(108 / 5) * ((1+1)/2) = 21.6 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2))                //(108 / 2) * ((1+0)/4) = 13.5 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(108 / 3) * ((1+1)/6)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(108 / 5) * ((1+1)/6) = 7.2 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(4))                //(108 / 3) * ((1+0)/6) 
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(5) | SPI_CTAR_BR(2)) 		    //(108 / 7) * ((1+0)/4) = 3.86 MHz

#elif F_BUS == 96000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(96 / 2) * ((1+0)/2)
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(96 / 2) * ((1+1)/6)
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(6) | SPI_CTAR_DBR) //(96 / 2) * ((1+1)/8)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(2))                //(96 / 3) * ((1+0)/4)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(6))                //(96 / 2) * ((1+0)/8)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(6)) 		    //(96 / 3) * ((1+0)/8)

#elif F_BUS == 90000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(90 / 2) * ((1+0)/2) = 22.5 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(90 / 2) * ((1+1)/6) = 15 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(6) | SPI_CTAR_DBR) //(90 / 2) * ((1+1)/8) = 11.25 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4))                //(90 / 2) * ((1+0)/6) = 7.5 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(90 / 5) * ((1+1)/6)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(6)) 		    //(90 / 3) * ((1+0)/8) = 3.75 MHz

#elif F_BUS == 80000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(80 / 2) * ((1+0)/2) = 20 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(80 / 5) * ((1+1)/2)
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(5) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(80 / 7) * ((1+1)/2) = 11.42 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0))                //(80 / 5) * ((1+0)/2)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(5) | SPI_CTAR_BR(0))                //(80 / 7) * ((1+0)/2) = 5.7 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(2)) 		    //(80 / 5) * ((1+0)/4)

#elif F_BUS == 72000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(72 / 3) * ((1+1)/2)
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(72 / 2) * ((1+1)/6) = 12 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(72 / 2) * ((1+1)/6)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(4) | SPI_CTAR_DBR) //(72 / 3) * ((1+1)/6)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4))                //(72 / 2) * ((1+0)/6)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(4)) 		    //(72 / 3) * ((1+0)/6)

#elif F_BUS == 64000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(64 / 3) * ((1+1)/2) = 21.3 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(64 / 2) * ((1+0)/2)
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0)) 		    //(64 / 3) * ((1+0)/2) = 10.67 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2))                //(64 / 2) * ((1+0)/4)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(4))                //(64 / 2) * ((1+0)/6) = 5.3 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(6)) 		    //(64 / 2) * ((1+0)/8)

#elif F_BUS == 60000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(60 / 3) * ((1+1)/2) = 20 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(60 / 2) * ((1+0)/2) = 15 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(60 / 5) * ((1+1)/2)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1))                //(60 / 2) * ((1+0)/4) = 7.5 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(2) | SPI_CTAR_BR(0))                //(60 / 5) * ((1+0)/2)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(2) | SPI_CTAR_BR(2) | SPI_CTAR_DBR) //(60 / 5) * ((1+1)/6)

#elif F_BUS == 56000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(56 / 3) * ((1+1)/2) = 18.67
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(56 / 2) * ((1+0)/2) = 14
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(56 / 5) * ((1+1)/2) = 11.2
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(56 / 7) * ((1+1)/2)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(2) | SPI_CTAR_BR(0))                //(56 / 5) * ((1+0)/2)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(0))                //(56 / 7) * ((1+0)/2)

#elif F_BUS == 48000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(48 / 2) * ((1+1)/2)
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(48 / 3) * ((1+1)/2)
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(48 / 2) * ((1+0)/2)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2) | SPI_CTAR_DBR) //(48 / 2) * ((1+1)/6)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1))                //(48 / 2) * ((1+0)/4)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2))                //(48 / 2) * ((1+0)/6)

#elif F_BUS == 40000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(40 / 2) * ((1+1)/2) = 20
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(40 / 3) * ((1+1)/2) = 13.33
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(40 / 2) * ((1+0)/2) = 10
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(40 / 5) * ((1+1)/2)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(3) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(40 / 7) * ((1+1)/2) = 5.71
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(2) | SPI_CTAR_BR(1))                //(40 / 5) * ((1+0)/2)

#elif F_BUS == 36000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(36 / 2) * ((1+1)/2) = 18
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(36 / 3) * ((1+1)/2) = 12
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(36 / 3) * ((1+1)/2) = 12
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(2) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(36 / 5) * ((1+1)/2) = 7.2
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2) | SPI_CTAR_DBR) //(36 / 2) * ((1+1)/6)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(2) | SPI_CTAR_DBR) //(36 / 3) * ((1+1)/6)

#elif F_BUS == 24000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(24 / 2) * ((1+1)/2)  12 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(24 / 2) * ((1+1)/2)  12 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(24 / 2) * ((1+1)/2)
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(1) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(24 / 3) * ((1+1)/2)
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0))                //(24 / 2) * ((1+0)/2)
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(2) | SPI_CTAR_DBR) //(24 / 2) * ((1+1)/6)

#elif F_BUS == 16000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_DBR) //(16 / 2) * ((1+1)/8) = 2 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_DBR) //(16 / 2) * ((1+1)/8) = 2 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_DBR) //(16 / 2) * ((1+1)/8) = 2 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_DBR) //(16 / 2) * ((1+1)/8) = 2 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_DBR) //(16 / 2) * ((1+1)/8) = 2 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(3) | SPI_CTAR_DBR) //(16 / 2) * ((1+1)/8) = 2 MHz

#elif F_BUS == 8000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(8 / 2) * ((1+1)/4) = 2 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(8 / 2) * ((1+1)/4) = 2 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(8 / 2) * ((1+1)/4) = 2 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(8 / 2) * ((1+1)/4) = 2 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(8 / 2) * ((1+1)/4) = 2 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(1) | SPI_CTAR_DBR) //(8 / 2) * ((1+1)/4) = 2 MHz

#elif F_BUS == 4000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 2 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 2 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 2 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 2 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 2 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 2 MHz

#elif F_BUS == 2000000
#define HAS_SPIFIFO
#define SPI_CLOCK_24MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 1 MHz
#define SPI_CLOCK_16MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 1 MHz
#define SPI_CLOCK_12MHz   (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 1 MHz
#define SPI_CLOCK_8MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 1 MHz
#define SPI_CLOCK_6MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 1 MHz
#define SPI_CLOCK_4MHz    (SPI_CTAR_PBR(0) | SPI_CTAR_BR(0) | SPI_CTAR_DBR) //(4 / 2) * ((1+1)/2) = 1 MHz

#endif // F_BUS

#endif // KINETISK

/*
#! /usr/bin/perl
$clock = 60;
for $i (2, 3, 5, 7) {
        for $j (0, 1) {
                for $k (2, 4, 6, 8, 16, 32) {
                        $out = $clock / $i * (1 + $j) / $k;
                        printf "%0.2f :  ", $out;
                        print "$clock / $i * (1 + $j) / $k = $out\n";
                }
        }
}
*/

// sck = F_BUS / PBR * ((1+DBR)/BR)
//  PBR = 2, 3, 5, 7
//  DBR = 0, 1         -- zero preferred
//  BR = 2, 4, 6, 8, 16, 32, 64, 128, 256, 512


#ifdef HAS_SPIFIFO

#ifndef SPI_MODE0
#define SPI_MODE0 0x00  // CPOL = 0, CPHA = 0
#define SPI_MODE1 0x04  // CPOL = 0, CPHA = 1
#define SPI_MODE2 0x08  // CPOL = 1, CPHA = 0
#define SPI_MODE3 0x0C  // CPOL = 1, CPHA = 1
#endif

#define SPI_CONTINUE 1

class SPIFIFOclass
{
public:
	inline void begin(uint8_t pin, uint32_t speed, uint32_t mode=SPI_MODE0) __attribute__((always_inline, deprecated)) {
		uint32_t p, ctar = speed;
		SIM_SCGC6 |= SIM_SCGC6_SPI0;

		KINETISK_SPI0.MCR = SPI_MCR_MSTR | SPI_MCR_MDIS | SPI_MCR_HALT | SPI_MCR_PCSIS(0x1F);
		if (mode & 0x08) ctar |= SPI_CTAR_CPOL;
		if (mode & 0x04) {
			ctar |= SPI_CTAR_CPHA;
			ctar |= (ctar & 0x0F) << 8;
		} else {
			ctar |= (ctar & 0x0F) << 12;
		}
		KINETISK_SPI0.CTAR0 = ctar | SPI_CTAR_FMSZ(7);
		KINETISK_SPI0.CTAR1 = ctar | SPI_CTAR_FMSZ(15);
		if (pin == 10) {         // PTC4
			CORE_PIN10_CONFIG = PORT_PCR_MUX(2);
			p = 0x01;
		} else if (pin == 2) {   // PTD0
			CORE_PIN2_CONFIG = PORT_PCR_MUX(2);
			p = 0x01;
		} else if (pin == 9) {   // PTC3
			CORE_PIN9_CONFIG = PORT_PCR_MUX(2);
			p = 0x02;
		} else if (pin == 6) {   // PTD4
			CORE_PIN6_CONFIG = PORT_PCR_MUX(2);
			p = 0x02;
		} else if (pin == 20) {  // PTD5
			CORE_PIN20_CONFIG = PORT_PCR_MUX(2);
			p = 0x04;
		} else if (pin == 23) {  // PTC2
			CORE_PIN23_CONFIG = PORT_PCR_MUX(2);
			p = 0x04;
		} else if (pin == 21) {  // PTD6
			CORE_PIN21_CONFIG = PORT_PCR_MUX(2);
			p = 0x08;
		} else if (pin == 22) {  // PTC1
			CORE_PIN22_CONFIG = PORT_PCR_MUX(2);
			p = 0x08;
		} else if (pin == 15) {  // PTC0
			CORE_PIN15_CONFIG = PORT_PCR_MUX(2);
			p = 0x10;
#if defined(__MK64FX512__) || defined(__MK66FX1M0__)
		} else if (pin == 26) {  
			CORE_PIN26_CONFIG = PORT_PCR_MUX(2);
			p = 0x01;
#endif
		} else {
			reg = portOutputRegister(pin);
			pinMode(pin, OUTPUT);
			*reg = 1;
			p = 0;
		}
		pcs = p;
		clear();
		SPCR.enable_pins();
	}
	inline void write(uint32_t b, uint32_t cont=0) __attribute__((always_inline)) {
		uint32_t pcsbits = pcs << 16;
		if (pcsbits) {
			KINETISK_SPI0.PUSHR = (b & 0xFF) | pcsbits | (cont ? SPI_PUSHR_CONT : 0);
			while (((KINETISK_SPI0.SR) & (15 << 12)) > (3 << 12)) ; // wait if FIFO full
		} else {
			*reg = 0;
			KINETISK_SPI0.SR = SPI_SR_EOQF;
			KINETISK_SPI0.PUSHR = (b & 0xFF) | (cont ? 0 : SPI_PUSHR_EOQ);
			if (cont) {
				while (((KINETISK_SPI0.SR) & (15 << 12)) > (3 << 12)) ;
			} else {
				while (!(KINETISK_SPI0.SR & SPI_SR_EOQF)) ;
				*reg = 1;
			}
		}
	}
	inline void write16(uint32_t b, uint32_t cont=0) __attribute__((always_inline)) {
		uint32_t pcsbits = pcs << 16;
		if (pcsbits) {
			KINETISK_SPI0.PUSHR = (b & 0xFFFF) | (pcs << 16) |
				(cont ? SPI_PUSHR_CONT : 0) | SPI_PUSHR_CTAS(1);
			while (((KINETISK_SPI0.SR) & (15 << 12)) > (3 << 12)) ;
		} else {
			*reg = 0;
			KINETISK_SPI0.SR = SPI_SR_EOQF;
			KINETISK_SPI0.PUSHR = (b & 0xFFFF) | (cont ? 0 : SPI_PUSHR_EOQ) | SPI_PUSHR_CTAS(1);
			if (cont) {
				while (((KINETISK_SPI0.SR) & (15 << 12)) > (3 << 12)) ;
			} else {
				while (!(KINETISK_SPI0.SR & SPI_SR_EOQF)) ;
				*reg = 1;
			}
		}
	}
	inline uint32_t read(void) __attribute__((always_inline)) {
		while ((KINETISK_SPI0.SR & (15 << 4)) == 0) ;  // TODO, could wait forever
		return KINETISK_SPI0.POPR;
	}
	inline void clear(void) __attribute__((always_inline)) {
		KINETISK_SPI0.MCR = SPI_MCR_MSTR | SPI_MCR_PCSIS(0x1F) | SPI_MCR_CLR_TXF | SPI_MCR_CLR_RXF;
	}
private:
	static uint8_t pcs;
	static volatile uint8_t *reg;
};
extern SPIFIFOclass SPIFIFO;

#endif // HAS_SPIFIFO

#endif
