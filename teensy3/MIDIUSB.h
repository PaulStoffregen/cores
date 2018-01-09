#ifndef MIDIUSB_h
#define MIDIUSB_h

// For compatibility with Arduino's MIDIUSB library

#include "usb_midi.h"

#ifdef __cplusplus
#if !defined(USB_MIDI) && !defined(USB_MIDI4) && !defined(USB_MIDI16) && !defined(USB_MIDI_SERIAL) && !defined(USB_MIDI4_SERIAL) && !defined(USB_MIDI16_SERIAL) && !defined(USB_MIDI_AUDIO_SERIAL) && !defined(USB_MIDI16_AUDIO_SERIAL) && !defined(USB_EVERYTHING)
#error "Please select MIDI in Tools > USB Type to use MIDIUSB.h"
#endif

typedef struct {
 union {
  struct {
	uint8_t header;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
  };
	uint32_t word;
 };
} midiEventPacket_t;


class MIDI_
{
public:
	constexpr MIDI_(void) { }
	uint32_t available(void) {
		return usb_midi_available();
	}
	midiEventPacket_t read(void) {
		midiEventPacket_t event;
		event.word = usb_midi_read_message();
		return event;
	}
	void flush(void) {
		usb_midi_flush_output();
	}
	void sendMIDI(midiEventPacket_t event) {
		usb_midi_write_packed(event.word);
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
