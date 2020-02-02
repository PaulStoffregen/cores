#ifndef MIDIUSB_h
#define MIDIUSB_h

// For compatibility with Arduino's MIDIUSB library

#ifdef __cplusplus
#if !defined(USB_MIDI)
#error "Please select MIDI in Tools > USB Type to use MIDIUSB.h"
#endif

#include "usb_api.h"

typedef struct {
  struct {
	uint8_t header;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
  };
} midiEventPacket_t;


class MIDI_
{
public:
	constexpr MIDI_(void) { }
	uint32_t available(void) {
		return usbMIDI.midiusb_available();
	}
	midiEventPacket_t read(void) {
		midiEventPacket_t event;
		usbMIDI.midiusb_read((uint8_t *)&event);
		return event;
	}
	void flush(void) {
		usbMIDI.send_now();
	}
	void sendMIDI(midiEventPacket_t event) {
		usbMIDI.send_raw(event.header, event.byte1, event.byte2, event.byte3);
	}
	size_t write(const uint8_t *buffer, size_t size) {
		// TODO - is this really needed?
		return 0;
	}
	operator bool() {
		// TODO - is this really needed?
		return true;
	}
};
extern MIDI_ MidiUSB;

#endif // __cplusplus
#endif // MIDIUSB_h
