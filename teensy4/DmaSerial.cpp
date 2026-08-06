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

#include "DmaSerial.h"
#include "Arduino.h"
#include <cstring>
#include <cmath>
#include <algorithm>

#ifdef __IMXRT1062__  // teensy 4.0, 4.1

#define UART_CLOCK 24000000

#define CTRL_ENABLE 		(LPUART_CTRL_TE | LPUART_CTRL_RE)

// *********************************************************************************************************
// ** There is a fatal bug in imxrt.h that DMAMUX_SOURCE_LPUARTx_RX and DMAMUX_SOURCE_LPUARTx_TX values
// ** are incorrect. They should swap their values in imxrt.h file. This bug took me 6 hours to find!
// ** This is probably because this library was originally written for imxrt1052 micro and they forgot
// ** to add the necessary changes to support imxrt1062 which is the micro on teensy 4.0.
// *********************************************************************************************************

// teensy 4.0 specific board information:
const DmaSerial::Base_t DmaSerial::serial1Base = {
        &IMXRT_LPUART6,
        DMAMUX_SOURCE_LPUART6_RX,
        DMAMUX_SOURCE_LPUART6_TX,
        CCM_CCGR3,
        CCM_CCGR3_LPUART6(CCM_CCGR_ON),
        {{0,2, &IOMUXC_LPUART6_RX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
        {{1,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
};

const DmaSerial::Base_t DmaSerial::serial2Base = {
        &IMXRT_LPUART4,
        DMAMUX_SOURCE_LPUART4_RX,
        DMAMUX_SOURCE_LPUART4_TX,
        CCM_CCGR1,
        CCM_CCGR1_LPUART4(CCM_CCGR_ON),
        #if defined(__IMXRT1052__)
        {{6,2, &IOMUXC_LPUART4_RX_SELECT_INPUT, 2}, {0xff, 0xff, nullptr, 0}},
	    {{7,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
        #elif defined(__IMXRT1062__)
        {{7,2, &IOMUXC_LPUART4_RX_SELECT_INPUT, 2}, {0xff, 0xff, nullptr, 0}},
        {{8,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
        #endif
};

const DmaSerial::Base_t DmaSerial::serial3Base = {
        &IMXRT_LPUART2,
        DMAMUX_SOURCE_LPUART2_RX,
        DMAMUX_SOURCE_LPUART2_TX,
        CCM_CCGR0,
        CCM_CCGR0_LPUART2(CCM_CCGR_ON),
        {{15,2, &IOMUXC_LPUART2_RX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
        {{14,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
};

const DmaSerial::Base_t DmaSerial::serial4Base = {
        &IMXRT_LPUART3,
        DMAMUX_SOURCE_LPUART3_RX,
        DMAMUX_SOURCE_LPUART3_TX,
        CCM_CCGR0,
        CCM_CCGR0_LPUART3(CCM_CCGR_ON),
        {{16,2, &IOMUXC_LPUART3_RX_SELECT_INPUT, 0}, {0xff, 0xff, nullptr, 0}},
        {{17,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
};

const DmaSerial::Base_t DmaSerial::serial5Base = {
        &IMXRT_LPUART8,
        DMAMUX_SOURCE_LPUART8_RX,
        DMAMUX_SOURCE_LPUART8_TX,
        CCM_CCGR6,
        CCM_CCGR6_LPUART8(CCM_CCGR_ON),
        {{21,2, &IOMUXC_LPUART8_RX_SELECT_INPUT, 1}, {38, 2, &IOMUXC_LPUART8_RX_SELECT_INPUT, 0}},
        {{20,2, &IOMUXC_LPUART8_TX_SELECT_INPUT, 1}, {39, 2, &IOMUXC_LPUART8_TX_SELECT_INPUT, 0}},
};

const DmaSerial::Base_t DmaSerial::serial6Base = {
        &IMXRT_LPUART1,
        DMAMUX_SOURCE_LPUART1_RX,
        DMAMUX_SOURCE_LPUART1_TX,
        CCM_CCGR5,
        CCM_CCGR5_LPUART1(CCM_CCGR_ON),
        {{25,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
        {{24,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
};

const DmaSerial::Base_t DmaSerial::serial7Base = {
        &IMXRT_LPUART7,
        DMAMUX_SOURCE_LPUART7_TX,
        DMAMUX_SOURCE_LPUART7_RX,
        CCM_CCGR5,
        CCM_CCGR5_LPUART7(CCM_CCGR_ON),
        {{28,2, &IOMUXC_LPUART7_RX_SELECT_INPUT, 1}, {0xff, 0xff, nullptr, 0}},
        {{29,2, nullptr, 0}, {0xff, 0xff, nullptr, 0}},
};

const DmaSerial::Base_t* DmaSerial::allSerialBases[7] = {
        &serial1Base,
        &serial2Base,
        &serial3Base,
        &serial4Base,
        &serial5Base,
        &serial6Base,
        &serial7Base,
};

DmaSerial dmaSerial1(1);
DmaSerial dmaSerial2(2);
DmaSerial dmaSerial3(3);
DmaSerial dmaSerial4(4);
DmaSerial dmaSerial5(5);
DmaSerial dmaSerial6(6);
DmaSerial dmaSerial7(7);
const DmaSerial* DmaSerial::dmaSerials[7] = {
        &dmaSerial1,
        &dmaSerial2,
        &dmaSerial3,
        &dmaSerial4,
        &dmaSerial5,
        &dmaSerial6,
        &dmaSerial7,
};
#else
#error "no supported board"
#endif

void DmaSerial::txCompleteCallback1() {dmaSerial1.txIsr();}
void DmaSerial::txCompleteCallback2() {dmaSerial2.txIsr();}
void DmaSerial::txCompleteCallback3() {dmaSerial3.txIsr();}
void DmaSerial::txCompleteCallback4() {dmaSerial4.txIsr();}
void DmaSerial::txCompleteCallback5() {dmaSerial5.txIsr();}
void DmaSerial::txCompleteCallback6() {dmaSerial6.txIsr();}
void DmaSerial::txCompleteCallback7() {dmaSerial7.txIsr();}
void (* const DmaSerial::allTxIsr[7])() = {
        txCompleteCallback1,
        txCompleteCallback2,
        txCompleteCallback3,
        txCompleteCallback4,
        txCompleteCallback5,
        txCompleteCallback6,
        txCompleteCallback7,
};

DmaSerial::DmaSerial(int serialNo)
    : serialNo(serialNo)
{
    serialBase = allSerialBases[serialNo - 1];
    rxPinIndex = 0; // default pin = first pin
    txPinIndex = 0; // default pin = first pin

    txBufferTail = 0;
    txBufferHead = 0;
    txBufferCount = 0;
    rxBufferTail = 0;
    // rxBufferHead = 0; // no need for this
}


void DmaSerial::begin(uint32_t baud, uint16_t format) {

    if (!txBuffer) {
        txBuffer = new uint8_t[DMA_TX_BUFFER_SIZE];
    }
    if (!rxBuffer) {
        rxBuffer = new uint8_t[DMA_RX_BUFFER_SIZE];
    }

    // configure DMA channels:
    if (!dmaChannelSend) {
        dmaChannelSend = new DMAChannel();
        dmaChannelSend->destination(*(uint8_t*)&serialBase->port->DATA);
        // source is not configured here
        dmaChannelSend->triggerAtHardwareEvent(serialBase->dmaMuxSourceTx);
        dmaChannelSend->attachInterrupt(allTxIsr[serialNo - 1]);
        dmaChannelSend->interruptAtCompletion();
        dmaChannelSend->disableOnCompletion();
        // not enabled here
    }
    if (!dmaChannelReceive) {
        dmaChannelReceive = new DMAChannel();
        dmaChannelReceive->source(*(uint8_t*)&serialBase->port->DATA);
        dmaChannelReceive->destinationBuffer(rxBuffer, DMA_RX_BUFFER_SIZE);
        dmaChannelReceive->triggerAtHardwareEvent(serialBase->dmaMuxSourceRx);
        dmaChannelReceive->enable();
    }

    txBufferTail = 0;
    txBufferHead = 0;
    txBufferCount = 0;
    rxBufferTail = 0;
    // rxBufferHead = 0; // no need for this

    // calculate baudrate:
    float base = (float)UART_CLOCK / (float)baud;
    float besterr = 1e20;
    int bestdiv = 1;
    int bestosr = 4;
    for (int osr=4; osr <= 32; osr++) {
        float div = base / (float)osr;
        int divint = lroundf(div);
        if (divint < 1) divint = 1;
        else if (divint > 8191) divint = 8191;
        float err = ((float)divint - div) / div;
        if (err < 0.0f) err = -err;
        if (err <= besterr) {
            besterr = err;
            bestdiv = divint;
            bestosr = osr;
        }
    }

    // turn on clock for UART:
    serialBase->ccm_register |= serialBase->ccm_value;

    // disable UART:
    serialBase->port->CTRL = 0;

    // config Rx Pin:
    *(portControlRegister(serialBase->rx_pins[rxPinIndex].pin)) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;
    *(portConfigRegister(serialBase->rx_pins[rxPinIndex].pin)) = serialBase->rx_pins[rxPinIndex].mux_val;
    if (serialBase->rx_pins[rxPinIndex].select_input_register) {
        *(serialBase->rx_pins[rxPinIndex].select_input_register) =  serialBase->rx_pins[rxPinIndex].select_val;
    }

    // config Tx Pin:
    *(portControlRegister(serialBase->tx_pins[txPinIndex].pin)) =  IOMUXC_PAD_SRE | IOMUXC_PAD_DSE(3) | IOMUXC_PAD_SPEED(3);
    *(portConfigRegister(serialBase->tx_pins[txPinIndex].pin)) = serialBase->tx_pins[txPinIndex].mux_val;

    serialBase->port->BAUD = LPUART_BAUD_OSR(bestosr - 1) | LPUART_BAUD_SBR(bestdiv);
    serialBase->port->PINCFG = 0;

    // enabling DMA instead:
    serialBase->port->BAUD |= (LPUART_BAUD_TDMAE | LPUART_BAUD_RDMAE);

    // disabling FIFO:
    serialBase->port->FIFO &= ~(LPUART_FIFO_TXFE | LPUART_FIFO_RXFE);

    // lets configure up our CTRL register value
    uint32_t ctrl = CTRL_ENABLE | LPUART_CTRL_RIE | LPUART_CTRL_TIE | LPUART_CTRL_ILIE;

    // Now process the bits in the Format value passed in
    // Bits 0-2 - Parity plus 9  bit.
    ctrl |= (format & (LPUART_CTRL_PT | LPUART_CTRL_PE) );	// configure parity - turn off PT, PE, M and configure PT, PE
    if (format & 0x04) ctrl |= LPUART_CTRL_M;		// 9 bits (might include parity)
    if ((format & 0x0F) == 0x04) ctrl |=  LPUART_CTRL_R9T8; // 8N2 is 9 bit with 9th bit always 1

    // Bit 5 TXINVERT
    if (format & 0x20) ctrl |= LPUART_CTRL_TXINV;		// tx invert

    // Bit 3 10 bit - Will assume that begin already cleared it.
    // process some other bits which change other registers.
    if (format & 0x08) 	serialBase->port->BAUD |= LPUART_BAUD_M10;

    // Bit 4 RXINVERT
    uint32_t c = serialBase->port->STAT & ~LPUART_STAT_RXINV;
    if (format & 0x10) c |= LPUART_STAT_RXINV;		// rx invert
    serialBase->port->STAT = c;

    // bit 8 can turn on 2 stop bit mote
    if ( format & 0x100) serialBase->port->BAUD |= LPUART_BAUD_SBNS;

    // write out computed CTRL and turn on UART transmit and receive
    serialBase->port->CTRL = ctrl;

}

/**
 * Number of bytes in the buffer
 * @return 0 to 2047
 */
int DmaSerial::available() {
    auto biter = dmaChannelReceive->TCD->BITER;
    auto citer = dmaChannelReceive->TCD->CITER;
    auto csr = dmaChannelReceive->TCD->CSR;
    if (csr & 0x80) { // done so Rx buffer is full
        if (rxBufferTail == 0) return 0;
        else return DMA_RX_BUFFER_SIZE - rxBufferTail;
    }
    else {
        // our version of buffer indexes are not update
        size_t head = biter - citer;
        if (head >= rxBufferTail) return head - rxBufferTail;
        else return head - rxBufferTail + DMA_RX_BUFFER_SIZE;
    }
}

int DmaSerial::read() {
    uint8_t c = rxBuffer[rxBufferTail++];
    if (rxBufferTail >= DMA_RX_BUFFER_SIZE)
        rxBufferTail -= DMA_RX_BUFFER_SIZE;
    return c;
}

int DmaSerial::peek() {
    return rxBuffer[rxBufferTail];
}

size_t DmaSerial::write(uint8_t c) {
    write(&c, 1);
    return 1;
}

size_t DmaSerial::write(char c) {
    return write((uint8_t *)&c, 1);
}

size_t DmaSerial::write(const uint8_t *p, size_t len) {

    size_t index = 0;
    while (index < len) {

        // wait until there is free space in the buffer:
        while (DMA_TX_BUFFER_SIZE - txBufferCount == 0); //

        // get a chunk of data to add to the buffer
        size_t chunkSize = std::min(len - index, DMA_TX_BUFFER_SIZE - txBufferCount);

        // copy the data to the buffer:
        size_t s1 = std::min(chunkSize, DMA_TX_BUFFER_SIZE - txBufferHead);
        size_t s2 = chunkSize - s1;
        memcpy(&txBuffer[txBufferHead], &p[index], s1);
        if (s2 > 0)
            memcpy(&txBuffer[0], &p[index + s1], s2);
        index += chunkSize;

        // move the head:
        txBufferCount += chunkSize;
        txBufferHead += chunkSize;
        if (txBufferHead >= DMA_TX_BUFFER_SIZE)
            txBufferHead -= DMA_TX_BUFFER_SIZE;

        // start transmitting from the tail:
        if (!transmitting) {
            transmitting = true;
            __disable_irq()
            size_t count = std::min(DMA_TX_BUFFER_SIZE - txBufferTail, chunkSize);
            count = std::min(count, size_t(DMA_MAX_BURST_DATA_TRANSFER)); // min(remaining in the buffer, len_truncate, max_burst)
            dmaChannelSend->sourceBuffer(&txBuffer[txBufferTail], count);
            dmaChannelSend->enable();
            __enable_irq();
        }
    }
    return len;

}

void DmaSerial::txIsr() {
    dmaChannelSend->clearInterrupt();

    // move the tail:
    {
        int count = dmaChannelSend->TCD->BITER;

        txBufferTail += count;
        if (txBufferTail >= DMA_TX_BUFFER_SIZE)
            txBufferTail -= DMA_TX_BUFFER_SIZE;
        txBufferCount -= count;
    }

    if (txBufferCount > 0) {
        transmitting = true;
        __disable_irq()
        size_t count = std::min(size_t(DMA_TX_BUFFER_SIZE) - txBufferTail, size_t(txBufferCount));
        count = std::min(count, size_t(DMA_MAX_BURST_DATA_TRANSFER)); // MIN(remaining in the buffer, txBufferCount, max_burst)
        dmaChannelSend->sourceBuffer(&txBuffer[txBufferTail], count);
        dmaChannelSend->enable();
        __enable_irq();
    }
    else {
        transmitting = false;
    }
}


