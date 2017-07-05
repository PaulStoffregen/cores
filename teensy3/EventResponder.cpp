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
	if (_pending) {
		// already triggered
		return;
	}
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
			lastInterrupt = this;
		}
		// TODO set interrupt pending
	} else {
		// detached, easy :-)
	}
	_pending = true;
}

void pendablesrvreq_isr(void)
{
	EventResponder::runFromInterrupt();
}

void EventResponder::runFromInterrupt()
{
	for (EventResponder *first=firstInterrupt; first; first = first->_next) {
		first->_pending = false;
		(*(first->_function))(*first);
	}
	firstInterrupt = nullptr;
	lastInterrupt = nullptr;
}

bool EventResponder::clearEvent()
{
	if (_pending) {
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
		_pending = false;
		return true;
	}
	return false;
}

void EventResponder::detach()
{
	if (_type == EventTypeYield) {
		if (_pending) {
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
		if (_pending) {
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


