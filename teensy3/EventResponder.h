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
 * Please post your EventResponder feedback here:
 *     https://forum.pjrc.com/threads/44723-Arduino-Events
 */

#if !defined(EventResponder_h) && defined(__cplusplus)
#define EventResponder_h

#include <Arduino.h>

/* EventResponder lets you control how your program responds to an event.
 * Imagine a basketball or football (American soccer) player who gets the
 * ball.  Usually they will pass to another player who has the best
 * opportunity to score.  Similarly in Arduino programming, events are
 * often triggered within interrupts or other timing sensitive code.
 * EventResponder can call your function a short time later, giving you
 * the ability to use Arduino functions and libraries which would not
 * be safe to use from an interrupt.  However, some situations do call
 * for the most immediate response, even if doing so is more difficult.
 * EventResponder lets you choose how your function will be called,
 * without editing the timers or libraries which trigger the events.
 *
 * Event handling functions called by EventResponder should complete
 * their work quickly.  Avoid delays or operations which may take
 * substantial time.  While your function runs, no other event functions
 * (attached the same way) are able to run.
 *
 * If your EventResponder is triggered more than once before your
 * function can run, only the last trigger is used.  Prior triggering,
 * including the status integer and data pointer, are overwritten and
 * your function is called only one time, based on the last trigger
 * event.
 */

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
	enum EventType { // these are not meant for public consumption...
		EventTypeDetached = 0, // no function is called
		EventTypeYield,        // function is called from yield()
		EventTypeImmediate,    // function is called immediately
		EventTypeInterrupt,    // function is called from interrupt
		EventTypeThread        // function is run as a new thread
	};

	// Attach a function to be called from yield().  This should be the
	// default way to use EventResponder.  Calls from yield() allow use
	// of Arduino libraries, String, Serial, etc.
	void attach(EventResponderFunction function, uint8_t priority=128) {
		bool irq = disableInterrupts();
		detachNoInterrupts();
		_function = function;
		_type = EventTypeYield;
		enableInterrupts(irq);
	}

	// Attach a function to be called immediately.  This provides the
	// fastest possible response, but your function must be carefully
	// designed.
	void attachImmediate(EventResponderFunction function) {
		bool irq = disableInterrupts();
		detachNoInterrupts();
		_function = function;
		_type = EventTypeImmediate;
		enableInterrupts(irq);
	}

	// Attach a function to be called from a low priority interrupt.
	// Boards not supporting software triggered interrupts will implement
	// this as attachImmediate.  On ARM and other platforms with software
	// interrupts, this allow fast interrupt-based response, but with less
	// disruption to other libraries requiring their own interrupts.
	void attachInterrupt(EventResponderFunction function, uint8_t priority=128) {
		bool irq = disableInterrupts();
		detachNoInterrupts();
		_function = function;
		_type = EventTypeInterrupt;
		SCB_SHPR3 |= 0x00FF0000; // configure PendSV, lowest priority
		enableInterrupts(irq);
	}

	// Attach a function to be called as its own thread.  Boards not running
	// a RTOS or pre-emptive scheduler shall implement this as attach().
	void attachThread(EventResponderFunction function, void *param=nullptr) {
		attach(function); // for non-RTOS usage, compile as default attach
	}

	// Do not call any function.  The user's program must occasionally check
	// whether the event has occurred, or use one of the wait functions.
	void detach() {
		bool irq = disableInterrupts();
		detachNoInterrupts();
		enableInterrupts(irq);
	}

	// Trigger the event.  An optional status code and data may be provided.
	// The code triggering the event does NOT control which of the above
	// response methods will be used.
	virtual void triggerEvent(int status=0, void *data=nullptr) {
		_status = status;
		_data = data;
		if (_type == EventTypeImmediate) {
			(*_function)(*this);
		} else {
			triggerEventNotImmediate();
		}
	}
	// Clear an event which has been triggered, but has not yet caused a
	// function to be called.
	bool clearEvent();

	// Get the event's status code.  Typically this will indicate if the event was
	// triggered due to successful completion, or how much data was successfully
	// processed (positive numbers) or an error (negative numbers).  The
	// exact meaning of this status code depends on the code or library which
	// triggers the event.
	int getStatus() { return _status; }

	// Get the optional data pointer associated with the event.  Often this
	// will be NULL, or will be the object instance which triggered the event.
	// Some libraries may use this to pass data associated with the event.
	void * getData() { return _data; }

	// An optional "context" may be associated with each EventResponder.
	// When more than one EventResponder has the same function attached, these
	// may be used to allow the function to obtain extra information needed
	// depending on which EventResponder called it.
	void setContext(void *context) { _context = context; }
	void * getContext() { return _context; }

	// Wait for event(s) to occur.  These are most likely to be useful when
	// used with a scheduler or RTOS.
	bool waitForEvent(EventResponderRef event, int timeout);
	EventResponder * waitForEvent(EventResponder *list, int listsize, int timeout);

	static void runFromYield() {
		// First, check if yield was called from an interrupt
		// never call normal handler functions from any interrupt context
		uint32_t ipsr;
		__asm__ volatile("mrs %0, ipsr\n" : "=r" (ipsr)::);
		if (ipsr != 0) return;
		// Next, check if any events have been triggered
		bool irq = disableInterrupts();
		EventResponder *first = firstYield;
		if (first == nullptr) {
			enableInterrupts(irq);
			return;
		}
		// Finally, make sure we're not being recursively called,
		// which can happen if the user's function does anything
		// that calls yield.
		if (runningFromYield) {
			enableInterrupts(irq);
			return;
		}
		// Ok, update the runningFromYield flag and process event
		runningFromYield = true;
		firstYield = first->_next;
		if (firstYield) {
			firstYield->_prev = nullptr;
		} else {
			lastYield = nullptr;
		}
		enableInterrupts(irq);
		first->_triggered = false;
		(*(first->_function))(*first);
		runningFromYield = false;
	}
	static void runFromInterrupt();
	operator bool() { return _triggered; }
protected:
	void triggerEventNotImmediate();
	void detachNoInterrupts();
	int _status = 0;
	EventResponderFunction _function = nullptr;
	void *_data = nullptr;
	void *_context = nullptr;
	EventResponder *_next = nullptr;
	EventResponder *_prev = nullptr;
	EventType _type = EventTypeDetached;
	bool _triggered = false;
	static EventResponder *firstYield;
	static EventResponder *lastYield;
	static EventResponder *firstInterrupt;
	static EventResponder *lastInterrupt;
	static bool runningFromYield;
private:
	static bool disableInterrupts() {
		uint32_t primask;
		__asm__ volatile("mrs %0, primask\n" : "=r" (primask)::);
		__disable_irq();
		return (primask == 0) ? true : false;
	}
	static void enableInterrupts(bool doit) {
		if (doit) __enable_irq();
	}
};

class MillisTimer
{
public:
	constexpr MillisTimer() {
	}
	~MillisTimer() {
		end();
	}
	void begin(unsigned long milliseconds, EventResponderRef event);
	void beginRepeating(unsigned long milliseconds, EventResponderRef event);
	void end();
	static void runFromTimer();
private:
	void addToWaitingList();
	void addToActiveList();
	unsigned long _ms = 0;
	unsigned long _reload = 0;
	MillisTimer *_next = nullptr;
	MillisTimer *_prev = nullptr;
	EventResponder *_event = nullptr;
	enum TimerStateType {
		TimerOff = 0,
		TimerWaiting,
		TimerActive
	};
	volatile TimerStateType _state = TimerOff;
	static MillisTimer *listWaiting; // single linked list of waiting to start timers
	static MillisTimer *listActive;  // double linked list of running timers
	static bool disableTimerInterrupt() {
		uint32_t primask;
		__asm__ volatile("mrs %0, primask\n" : "=r" (primask)::);
		__disable_irq();
		return (primask == 0) ? true : false;
	}
	static void enableTimerInterrupt(bool doit) {
		if (doit) __enable_irq();
	}
};

#endif
