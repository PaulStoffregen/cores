/* EventResponder - Simple event-based programming for Arduino
 * Copyright 2017 Paul Stoffregen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
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

/* EventResponder is an experimental API, almost certain to
 * incompatibly change as it develops.  Please understand any
 * programs you write now using EventResponder may need to be
 * updated as EventResponder develops.
 *
 * Please post EventResponder post your feedback here:
 *     https://forum.pjrc.com/threads/44723-Arduino-Events
 */

#include <Arduino.h>
#include "EventResponder.h"

EventResponder * EventResponder::firstYield = nullptr;
EventResponder * EventResponder::lastYield = nullptr;
EventResponder * EventResponder::firstInterrupt = nullptr;
EventResponder * EventResponder::lastInterrupt = nullptr;
bool EventResponder::runningFromYield = false;

// TODO: interrupt disable/enable needed in many places!!!

void EventResponder::triggerEventNotImmediate()
{
	bool irq = disableInterrupts();
	if (_triggered == false) {
		// not already triggered
		if (_type == EventTypeYield) {
			// normal type, called from yield()
			if (firstYield == nullptr) {
				_next = nullptr;
				_prev = nullptr;
				firstYield = this;
				lastYield = this;
			} else {
				_next = nullptr;
				_prev = lastYield;
				_prev->_next = this;
				lastYield = this;
			}
		} else if (_type == EventTypeInterrupt) {
			// interrupt, called from software interrupt
			if (firstInterrupt == nullptr) {
				_next = nullptr;
				_prev = nullptr;
				firstInterrupt = this;
				lastInterrupt = this;
			} else {
				_next = nullptr;
				_prev = lastInterrupt;
				_prev->_next = this;
				lastInterrupt = this;
			}
			SCB_ICSR = SCB_ICSR_PENDSVSET; // set PendSV interrupt
		} else {
			// detached, easy :-)
		}
		_triggered = true;
	}
	enableInterrupts(irq);
}

extern "C" void pendablesrvreq_isr(void)
{
	EventResponder::runFromInterrupt();
}

void EventResponder::runFromInterrupt()
{
	while (1) {
		bool irq = disableInterrupts();
		EventResponder *first = firstInterrupt;
		if (first) {
			firstInterrupt = first->_next;
			if (firstInterrupt) {
				firstInterrupt->_prev = nullptr;
			} else {
				lastInterrupt = nullptr;
			}
			enableInterrupts(irq);
			first->_triggered = false;
			(*(first->_function))(*first);
		} else {
			enableInterrupts(irq);
			break;
		}
	}
}

bool EventResponder::clearEvent()
{
	bool ret = false;
	bool irq = disableInterrupts();
	if (_triggered) {
		if (_type == EventTypeYield) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstYield = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastYield = _prev;
			}
		} else if (_type == EventTypeInterrupt) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstInterrupt = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastInterrupt = _prev;
			}
		}
		_triggered = false;
		ret = true;
	}
	enableInterrupts(irq);
	return ret;
}

// this detach must be called with interrupts disabled
void EventResponder::detachNoInterrupts()
{
	if (_type == EventTypeYield) {
		if (_triggered) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstYield = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastYield = _prev;
			}
		}
		_type = EventTypeDetached;
	} else if (_type == EventTypeInterrupt) {
		if (_triggered) {
			if (_prev) {
				_prev->_next = _next;
			} else {
				firstInterrupt = _next;
			}
			if (_next) {
				_next->_prev = _prev;
			} else {
				lastInterrupt = _prev;
			}
		}
		_type = EventTypeDetached;
	}
}


//-------------------------------------------------------------


MillisTimer * MillisTimer::listWaiting = nullptr;
MillisTimer * MillisTimer::listActive = nullptr;

void MillisTimer::begin(unsigned long milliseconds, EventResponderRef event)
{
	if (_state != TimerOff) end();
	if (!milliseconds) return;
	_event = &event;
	_ms = (milliseconds > 2)? milliseconds-2 : 0;
	_reload = 0;
	addToWaitingList();
}

void MillisTimer::beginRepeating(unsigned long milliseconds, EventResponderRef event)
{
	if (_state != TimerOff) end();
	if (!milliseconds) return;
	_event = &event;
	_ms = (milliseconds > 2)? milliseconds-2 : 0;
	_reload = milliseconds;
	addToWaitingList();
}

void MillisTimer::addToWaitingList()
{
	_prev = nullptr;
	bool irq = disableTimerInterrupt();
	_next = listWaiting;
	listWaiting = this; // TODO: use STREX to avoid interrupt disable
	_state = TimerWaiting;
	enableTimerInterrupt(irq);
}

void MillisTimer::addToActiveList() // only called by runFromTimer()
{
	if (listActive == nullptr) {
		// list is empty, easy case
		_next = nullptr;
		_prev = nullptr;
		listActive = this;
	} else if (_ms < listActive->_ms) {
		// this timer triggers before any on the list
		_next = listActive;
		_prev = nullptr;
		listActive->_prev = this;
		// Decrement the next items wait time be our wait time as to properly handle waits for all other items...
		listActive->_ms -= _ms;	
		listActive = this;
	} else {
		// add this timer somewhere after the first already on the list
		MillisTimer *timer = listActive;
		while (timer->_next) {
			_ms -= timer->_ms;
			timer = timer->_next;
			if (_ms < timer->_ms) {
				// found the right place in the middle of list
				_next = timer;
				_prev = timer->_prev;
				timer->_prev = this;
				_prev->_next = this;
				timer->_ms -= _ms;
				_state = TimerActive;
				return;
			}
		}
		// add this time at the end of the list
		_ms -= timer->_ms;
		_next = nullptr;
		_prev = timer;
		timer->_next = this;
	}
	_state = TimerActive;
}

void MillisTimer::end()
{
	bool irq = disableTimerInterrupt();
	TimerStateType s = _state;
	if (s == TimerActive) {
		if (_next) {
			_next->_prev = _prev;
			_next->_ms += _ms;   // add in the rest of our timing to next entry...
		}
		if (_prev) {
			_prev->_next = _next;
		} else {
			listActive = _next;
		}
		_state = TimerOff;
	} else if (s == TimerWaiting) {
		if (listWaiting == this) {
			listWaiting = _next;
		} else {
			MillisTimer *timer = listWaiting;
			while (timer) {
				if (timer->_next == this) {
					timer->_next = _next;
					break;
				}
				timer = timer->_next;
			}
		}
		_state = TimerOff;
	}
	enableTimerInterrupt(irq);
}

void MillisTimer::runFromTimer()
{
	MillisTimer *timer = listActive;
	while (timer) {
		if (timer->_ms > 0) {
			timer->_ms--;
			break;
		} else {
			MillisTimer *next = timer->_next;
			if (next) next->_prev = nullptr;
			listActive = next;
			timer->_state = TimerOff;
			EventResponderRef event = *(timer->_event);
			event.triggerEvent(0, timer);
			if (timer->_reload) {
				timer->_ms = timer->_reload;
				timer->addToActiveList();
			}
			timer = listActive;
		}
	}
	bool irq = disableTimerInterrupt();
	MillisTimer *waiting = listWaiting;
	listWaiting = nullptr; // TODO: use STREX to avoid interrupt disable
	enableTimerInterrupt(irq);
	while (waiting) {
		MillisTimer *next = waiting->_next;
		waiting->addToActiveList();
		waiting = next;
	}
}

// Long ago you could install your own systick interrupt handler by just
// creating your own systick_isr() function.  No longer.  But if you
// *really* want to commandeer systick, you can still do so by writing
// your function into the RAM-based vector table.
//
//   _VectorsRam[15] = my_systick_function;
//
// However, for long-term portability, use a MillisTimer object to
// generate an event every millisecond, and attach your function to
// its EventResponder.  You can attach as a software interrupt, so your
// code will run at lower interrupt priority for better compatibility
// with libraries using mid-to-high priority interrupts.

// TODO: this doesn't work for IMXRT - no longer using predefined names
extern "C" volatile uint32_t systick_millis_count;
extern "C" volatile uint32_t systick_cycle_count;
extern "C" uint32_t systick_safe_read; // micros() synchronization
extern "C" void systick_isr(void)
{
	systick_cycle_count = ARM_DWT_CYCCNT;
	systick_millis_count++;
	MillisTimer::runFromTimer();
}


