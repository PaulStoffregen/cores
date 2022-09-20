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
#include "Arduino.h"
// as usual, Arduino macros clash with the standard library
#pragma push_macro("abs")
#undef abs

#include "imxrt.h"
#include <chrono>
#include <cstdlib>

#define FUNCTION_TYPE 1 // 0: std::function, 1: stdex::inplace_function, 2: staticFunctional

#if FUNCTION_TYPE == 0
    #include <functional>
    using callback_t = std::function<void(void)>;

#elif FUNCTION_TYPE == 1
    #include "inplace_function.h" // c++21 proposal from https://github.com/WG21-SG14/SG14
    using callback_t = stdext::inplace_function<void(void)>;

#elif FUNCTION_TYPE == 2
    #include "staticFunctional.h"
    using callback_t = staticFunctional::function<void(void)>;
#endif

/**
 * IntervalTimer provides access to hardware timers which can run an
 * interrupt function a precise timing intervals.  Up to 4 IntervalTimers
 * may be in use simultaneously.  Many libraries use IntervalTimer, so
 * some of these 4 possible instances may be in use by libraries.
 */
class IntervalTimer
{
 public:
    template <typename period_t>
    bool begin(callback_t callback, period_t period);

    template <typename period_t>
    void update(period_t period);

    void end();
    void priority(uint8_t n);
    operator IRQ_NUMBER_t();

    IntervalTimer()                                = default;
    IntervalTimer(const IntervalTimer&)            = delete; // we do not want to handle copies of IntervalTimers
    IntervalTimer& operator=(IntervalTimer const&) = delete; // ditto

    ~IntervalTimer() { end(); }

 protected:
    template <typename period_t>
    uint32_t constexpr period2cycles(period_t period);
    bool beginCycles(callback_t callback, uint32_t cycles);
    inline static void pit_isr();

    IMXRT_PIT_CHANNEL_t* channel = nullptr;
    uint8_t nvic_priority        = 128;

    static constexpr unsigned numChannels          = 4;
    static constexpr uint32_t cyclesPerMicrosecond = 24;
    static constexpr uint32_t maxPeriod            = UINT32_MAX / cyclesPerMicrosecond;
    static constexpr uint32_t minCycles            = 17;

    static uint8_t nvic_priorites[numChannels];
    static callback_t funct_table[numChannels] __attribute((aligned(32)));
};

//==============================================================================================================
// INLINE IMPLEMENTATION of templated member functions

/***************************************************************************************************************
 * Start the hardware timer and begin invoking the callback.
 * @param callback the function to be invoked periodically (free function pointers, lambda expressions, functors etc)
 * @param period the time between successive calls in microseconds. begin also accepts time literals e.g. 1.2us, 13.9ms, 800ns etc
 */
template <typename period_t>
bool IntervalTimer::begin(callback_t callback, period_t period)
{
    uint32_t cycles = period2cycles(period);
    if (cycles == 0) return false;
    return beginCycles(callback, cycles);
}

/****************************************************************************************************************
 * Changes the timer's interval. The current interval is completed as previously configured,
 * and then the next interval begins with this new setting.
 * @param period the new period between successive calls in microseconds. update also accepts time literals e.g. 1.2us, 13.9ms, 800ns etc.
 */
template <typename period_t>
void IntervalTimer::update(period_t period)
{
    uint32_t cycles = period2cycles(period);
    if (cycles == 0) return;
    if (channel) channel->LDVAL = cycles;
}

/****************************************************************************************************************
 * PIT ISR, handles flags and relays the ISR to the actual callbacks stored in func_table
 */
void IntervalTimer::pit_isr() // have that in the header to give the compiler more chances for optimization.
{                             // needs to be declared inline to avoid linker errors!
    IMXRT_PIT_CHANNEL_t* channel = IMXRT_PIT_CHANNELS;
    if (funct_table[0] != nullptr && channel->TFLG)
    {
        channel->TFLG = 1;
        funct_table[0]();
    }
    channel++;
    if (funct_table[1] != nullptr && channel->TFLG)
    {
        channel->TFLG = 1;
        funct_table[1]();
    }
    channel++;
    if (funct_table[2] != nullptr && channel->TFLG)
    {
        channel->TFLG = 1;
        funct_table[2]();
    }
    channel++;
    if (funct_table[3] != nullptr && channel->TFLG)
    {
        channel->TFLG = 1;
        funct_table[3]();
    }
    // asm volatile("dsb"); // prevent double entry for very fast callbacks
}

#pragma GCC system_header // only chance to get rid of a warning a "constexpr if" is c++17, despite it works perfectly on GCC11.3, c++14
                          // could of course work around if really necessary...

/***************************************************************************************************************
 * Converts a period-type to counter cycles. Conversion is done at compiletime if period is known at compiletime!
 * @param period the period to be converted (accepts integers, floats or numbers with std::chrono units (12ms, 0.89s, 123ns...))
 */
template <typename period_t>
uint32_t constexpr IntervalTimer::period2cycles(period_t period)
{
    using namespace std::chrono;

    uint32_t cycles = 0;
    if constexpr (std::is_arithmetic<period_t>::value) // arithmetic types (ints, floats etc)
    {
        if ((period < 0) || ((uint32_t)std::abs(period) > maxPeriod))
            return 0;

        if constexpr (std::is_integral<period_t>::value)          // integer values
            cycles = cyclesPerMicrosecond * (uint32_t)period - 1; // support switching clock frequency might be a good idea

        else // floating point values
            cycles = cyclesPerMicrosecond * period - 0.5f;
    }
    else if constexpr (__is_duration<period_t>::value) // chrono durations
    {
        float microseconds = duration_cast<duration<float, std::micro>>(period).count();
        cycles             = microseconds * cyclesPerMicrosecond - 0.5;
    }
    return cycles > minCycles ? cycles : 0;
}

#pragma pop_macro("abs")
