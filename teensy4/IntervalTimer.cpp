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

#include "IntervalTimer.h"
#include "debug/printf.h"

bool IntervalTimer::beginCycles(callback_t callback, uint32_t cycles)
{
    printf("beginCycles %u\n", cycles);
    if (channel)
    {
        channel->TCTRL = 0;
        channel->TFLG  = 1;
    }
    else
    {
        CCM_CCGR1 |= CCM_CCGR1_PIT(CCM_CCGR_ON);
        PIT_MCR = 1;
        channel = IMXRT_PIT_CHANNELS;
        while (1)
        {
            if (channel->TCTRL == 0) break;
            if (++channel >= IMXRT_PIT_CHANNELS + numChannels)
            {
                channel = nullptr;
                return false;
            }
        }
    }
    int index             = channel - IMXRT_PIT_CHANNELS;
    funct_table[index]    = callback;
    channel->LDVAL        = cycles;
    channel->TCTRL        = 3;
    nvic_priorites[index] = nvic_priority;
    uint8_t top_priority  = 255;
    for (unsigned i = 0; i < numChannels; i++)
    {
        if (top_priority > nvic_priorites[i]) top_priority = nvic_priorites[i];
    }
    attachInterruptVector(IRQ_PIT, &pit_isr);
    NVIC_SET_PRIORITY(IRQ_PIT, top_priority);
    NVIC_ENABLE_IRQ(IRQ_PIT);
    return true;
}
/**
 * Stop the timer
 */
void IntervalTimer::end()
{
    if (channel)
    {
        int index = channel - IMXRT_PIT_CHANNELS;
        // TODO: disable IRQ_PIT, but only if all instances ended
        funct_table[index]    = nullptr;
        channel->TCTRL        = 0;
        nvic_priorites[index] = 255;
        uint8_t top_priority  = 255;
        for (unsigned i = 0; i < numChannels; i++)
        {
            if (top_priority > nvic_priorites[i]) top_priority = nvic_priorites[i];
        }
        NVIC_SET_PRIORITY(IRQ_PIT, top_priority);
        channel = 0;
    }
}

/**
 * Sets the interrupt priority. All intervalTimers run on the same timer module, -->
 * the timer with the highest priority determines the total priority
 * @param n: 0..255. smaller values set higher priority
 */
void IntervalTimer::priority(uint8_t n)
{
    nvic_priority = n;
    if (channel)
    {
        int index             = channel - IMXRT_PIT_CHANNELS;
        nvic_priorites[index] = nvic_priority;
        uint8_t top_priority  = nvic_priorites[0];
        for (uint8_t i = 1; i < (sizeof(nvic_priorites) / sizeof(nvic_priorites[0])); i++)
        {
            if (top_priority > nvic_priorites[i]) top_priority = nvic_priorites[i];
        }
        NVIC_SET_PRIORITY(IRQ_PIT, top_priority);
    }
}

IntervalTimer::operator IRQ_NUMBER_t()
{
    if (channel)
    {
        return IRQ_PIT;
    }
    return (IRQ_NUMBER_t)NVIC_NUM_INTERRUPTS;
}

// define static class members
callback_t IntervalTimer::funct_table[4]{nullptr, nullptr, nullptr, nullptr};
uint8_t IntervalTimer::nvic_priorites[4]{255, 255, 255, 255};