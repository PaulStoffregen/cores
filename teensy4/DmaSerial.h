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

#include "core_pins.h"
#include "HardwareSerial.h"
#include "DMAChannel.h"

// ------------------- change the following if you want ---------------------- //
#define DMA_TX_BUFFER_SIZE          128
#define DMA_RX_BUFFER_SIZE          4096

// ------------------- do not change the rest ------------------------//

#define DMA_MAX_BURST_DATA_TRANSFER 511         // This is the maximum data we are putting into DMA at once

class DmaSerial : public Stream {

private:

    static const uint8_t cnt_tx_pins = 2;
    static const uint8_t cnt_rx_pins = 2;
    typedef struct {
        const uint8_t 		pin;		// The pin number
        const uint32_t 		mux_val;	// Value to set for mux;
        volatile uint32_t	*select_input_register; // Which register controls the selection
        const uint32_t		select_val;	// Value for that selection
    } pin_info_t;

    typedef struct {
        IMXRT_LPUART_t* port;
        uint8_t dmaMuxSourceRx;
        uint8_t dmaMuxSourceTx;
        volatile uint32_t &ccm_register;
        const uint32_t ccm_value;
        pin_info_t rx_pins[cnt_rx_pins];
        pin_info_t tx_pins[cnt_tx_pins];
    } Base_t;

    const static Base_t serial1Base;
    const static Base_t serial2Base;
    const static Base_t serial3Base;
    const static Base_t serial4Base;
    const static Base_t serial5Base;
    const static Base_t serial6Base;
    const static Base_t serial7Base;
    const static Base_t* allSerialBases[7];
    const static DmaSerial* dmaSerials[7];

    static void txCompleteCallback1();
    static void txCompleteCallback2();
    static void txCompleteCallback3();
    static void txCompleteCallback4();
    static void txCompleteCallback5();
    static void txCompleteCallback6();
    static void txCompleteCallback7();
    static void (* const allTxIsr[7])();

    int serialNo;
    int rxPinIndex;
    int txPinIndex;

    uint8_t* txBuffer = nullptr;
    uint8_t* rxBuffer = nullptr;
    volatile size_t txBufferTail;
    volatile size_t txBufferHead;
    volatile size_t txBufferCount;
    volatile size_t rxBufferTail;
    // volatile uint32_t rxBufferHead; // no need for this

    volatile bool transmitting = false;

    const Base_t* serialBase = nullptr;
    DMAChannel* dmaChannelSend = nullptr;
    DMAChannel* dmaChannelReceive = nullptr;

    void txIsr();

public:

    explicit DmaSerial(int serialNo);
    int peek() override;
    void begin(uint32_t baud, uint16_t format = 0);
    int available() override;
    int read() override;
    using Print::write;
    size_t write(uint8_t c) override;
    size_t write(const uint8_t *buffer, size_t size) override;
    size_t write(char c);
    size_t write(unsigned long n)   { return write((uint8_t)n); }
    size_t write(long n)            { return write((uint8_t)n); }
    size_t write(unsigned int n)    { return write((uint8_t)n); }
    size_t write(int n)             { return write((uint8_t)n); }
};

#if defined(__IMXRT1062__)

extern DmaSerial dmaSerial1;
extern DmaSerial dmaSerial2;
extern DmaSerial dmaSerial3;
extern DmaSerial dmaSerial4;
extern DmaSerial dmaSerial5;
extern DmaSerial dmaSerial6;
extern DmaSerial dmaSerial7;

#endif
