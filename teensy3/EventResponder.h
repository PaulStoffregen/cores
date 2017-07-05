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

#if !defined(EventResponder_h) && defined(__cplusplus)
#define EventResponder_h

#include <Arduino.h>

class EventResponder;
typedef EventResponder& EventResponderRef;
typedef void (*EventResponderFunction)(EventResponderRef);
class EventResponder
{
public:
	constexpr EventResponder() {
	}
	~EventResponder() {
		detach();
	}
	enum EventType {
		EventTypeDetached = 0, // no function is called
		EventTypeYield,        // function is called from yield()
		EventTypeImmediate,    // function is called immediately
		EventTypeInterrupt,    // function is called from interrupt
		EventTypeThread        // function is run as a new thread
	};
	void attach(EventResponderFunction function) {
		detach();
		_function = function;
		_type = EventTypeYield;
	}
	void attachImmediate(EventResponderFunction function) {
		detach();
		_function = function;
		_type = EventTypeImmediate;
	}
	void attachInterrupt(EventResponderFunction function) {
		detach();
		_function = function;
		_type = EventTypeInterrupt;
		// TODO: configure PendSV
	}
	void attachThread(EventResponderFunction function, void *param=nullptr) {
		attach(function); // for non-RTOS usage, compile as default attach
	}
	void detach();
	virtual void triggerEvent(int status=0, void *data=nullptr) {
		_status = status;
		_data = data;
		if (_type == EventTypeImmediate) {
			(*_function)(*this);
		} else {
			triggerEventNotImmediate();
		}
	}
	bool clearEvent();
	int getStatus() { return _status; }
	void setContext(void *context) { _context = context; }
	void * getContext() { return _context; }
	void * getData() { return _data; }
	bool waitForEvent(EventResponderRef event, int timeout);
	EventResponder * waitForEvent(EventResponder *list, int listsize, int timeout);
	static void runFromYield() {
		EventResponder *first = firstYield;
		if (first && !runningFromYield) {
			runningFromYield = true;
			firstYield = first->_next;
			if (firstYield) firstYield->_prev = nullptr;
			first->_pending = false;
			(*(first->_function))(*first);
			runningFromYield = false;
		}
	}
	static void runFromInterrupt();
	operator bool() { return _pending; }
protected:
	void triggerEventNotImmediate();
	int _status = 0;
	EventResponderFunction _function = nullptr;
	void *_data = nullptr;
	void *_context = nullptr;
	EventResponder *_next = nullptr;
	EventResponder *_prev = nullptr;
	EventType _type = EventTypeDetached;
	bool _pending = false;
	static EventResponder *firstYield;
	static EventResponder *lastYield;
	static EventResponder *firstInterrupt;
	static EventResponder *lastInterrupt;
	static bool runningFromYield;
};


#endif
