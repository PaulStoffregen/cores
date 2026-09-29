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



#include <Arduino.h>
#include "usbHostRequestBuffer.h"

#ifdef ACTIVATE_BUFFER
namespace {

	typedef union {
 struct {
  union {
    struct {
        uint8_t bmRequestType;
        uint8_t bRequest;
    };
        uint16_t wRequestAndType;
	};
			uint16_t wValue;
			uint16_t wIndex;
			uint16_t wLength;
	};
	struct {
			uint32_t word1;
			uint32_t word2;
	};
		uint64_t bothwords;
	} setup_t;
}

volatile int32_t rBufferWIndex = -1;
uint64_t rBuffer[USB_REQUEST_BUFFER_LENGTH];
volatile uint32_t stalledWIndex = 0;
uint8_t stalled[USB_REQUEST_BUFFER_LENGTH];

void addToRequestBuffer(uint64_t r){
	if (rBufferWIndex==-1){
		rBufferWIndex=0;
	}
	rBuffer[rBufferWIndex] = r;
	rBufferWIndex =(rBufferWIndex+1)%USB_REQUEST_BUFFER_LENGTH;	
}
void setStalled(uint8_t b, uint8_t predecessor){
	uint32_t idx = (predecessor && stalledWIndex>0) ? stalledWIndex-1 : stalledWIndex;
	if(idx < USB_REQUEST_BUFFER_LENGTH){
		stalled[idx] = b;
		if(!predecessor){			
			stalledWIndex =(stalledWIndex+1)%USB_REQUEST_BUFFER_LENGTH;	
		}
	}
}
void print(uint32_t index){
	Serial.print(index);
	Serial.print(": ");
	setup_t s;
	s.bothwords = rBuffer[index];
	Serial.print("request and type: ");
	Serial.print(s.wRequestAndType, HEX);
	Serial.print(", bmRequestType: ");
	Serial.print(s.bmRequestType, BIN);
	Serial.print(", bRequest: ");
	Serial.print(s.bRequest, HEX);
	Serial.print(", wValue: ");
	Serial.print(s.wValue, HEX);
	Serial.print(", wIndex: ");
	Serial.print(s.wIndex, HEX);

	Serial.print(", was stalled: ");
	Serial.println(stalled[index]);
}
void printRequestBuffer(){
	uint32_t l = rBufferWIndex;
	for (uint32_t i =0; i< l; i++){
		print(i);
	}
}

int32_t printLastRequest(int32_t lastPrinted){
	if (rBufferWIndex==-1){
		return lastPrinted;
	}
	int32_t lastWriteIndex = (rBufferWIndex +USB_REQUEST_BUFFER_LENGTH-1)%USB_REQUEST_BUFFER_LENGTH;
	if(lastPrinted != lastWriteIndex){
		lastPrinted = lastWriteIndex;
		if(Serial){
			print(lastWriteIndex);
		}
	}
	return lastPrinted;
}

#else
void printRequestBuffer(){}
void setStalled(uint8_t b, uint8_t predecessor){}
void addToRequestBuffer(uint64_t r){}
int32_t printLastRequest(int32_t lastPrinted){return lastPrinted;}
#endif
