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

void pendablesrvreq_isr(void)
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

void EventResponder::detach()
{
	bool irq = disableInterrupts();
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
	enableInterrupts(irq);
}


//-------------------------------------------------------------


MillisTimer * MillisTimer::list = nullptr;

void MillisTimer::begin(unsigned long milliseconds, EventResponderRef event)
{
	end();
	if (!milliseconds) return;
	_event = &event;
	_ms = milliseconds;
	_reload = 0;
	addToList();
}

void MillisTimer::beginRepeating(unsigned long milliseconds, EventResponderRef event)
{
	end();
	if (!milliseconds) return;
	_event = &event;
	_ms = milliseconds;
	_reload = milliseconds;
	addToList();
}

void MillisTimer::addToList()
{
	bool irq = disableTimerInterrupt();
	if (list == nullptr) {
		// list is empty, easy case
		_next = nullptr;
		_prev = nullptr;
		list = this;
	} else if (_ms < list->_ms) {
		// this timer triggers before any on the list
		_next = list;
		_prev = nullptr;
		list->_prev = this;
		list = this;
	} else {
		// add this timer somewhere after the first already on the list
		MillisTimer *timer = list;
		while (timer->_next) {
			_ms -= timer->_ms;
			timer = timer->_next;
			if (_ms < timer->_ms) {
				// found the right place in the middle of list
				_next = timer;
				_prev = timer->_prev;
				timer->_prev = this;
				_prev->_next = this;
				isQueued = true;
				enableTimerInterrupt(irq);
				return;
			}
		}
		// add this time at the end of the list
		_ms -= timer->_ms;
		_next = nullptr;
		_prev = timer;
		timer->_next = this;
	}
	isQueued = true;
	enableTimerInterrupt(irq);
}

void MillisTimer::end()
{
	bool irq = disableTimerInterrupt();
	if (isQueued) {
		if (_next) {
			_next->_prev = _prev;
		}
		if (_prev) {
			_prev->_next = _next;
		} else {
			list = _next;
		}
		isQueued = false;
	}
	enableTimerInterrupt(irq);
}

void MillisTimer::runFromTimer()
{
	bool irq = disableTimerInterrupt();
	MillisTimer *timer = list;
	while (timer) {
		if (timer->_ms > 0) {
			timer->_ms--;
			break;
		} else {
			MillisTimer *next = timer->_next;
			if (next) next->_prev = nullptr;
			list = next;
			enableTimerInterrupt(irq);
			timer->isQueued = false;
			EventResponderRef event = *(timer->_event);
			event.triggerEvent(0, timer);
			if (timer->_reload) {
				timer->_ms = timer->_reload;
				timer->addToList();
			}
			irq = disableTimerInterrupt();
			timer = list;
		}
	}
	enableTimerInterrupt(irq);
}

extern "C" volatile uint32_t systick_millis_count;
void systick_isr(void)
{
	systick_millis_count++;
	MillisTimer::runFromTimer();
}


