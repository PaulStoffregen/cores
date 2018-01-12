#ifndef USBserial_h_
#define USBserial_h_

#include <inttypes.h>

#include "Stream.h"

#define USB_MIDI_SYSEX_MAX 60  // maximum sysex length we can receive

class usb_midi_class
{
public:
        // Message type names for compatibility with Arduino MIDI library 4.3.1
        enum MidiType {
                InvalidType           = 0x00, // For notifying errors
                NoteOff               = 0x80, // Note Off
                NoteOn                = 0x90, // Note On
                AfterTouchPoly        = 0xA0, // Polyphonic AfterTouch
                ControlChange         = 0xB0, // Control Change / Channel Mode
                ProgramChange         = 0xC0, // Program Change
                AfterTouchChannel     = 0xD0, // Channel (monophonic) AfterTouch
                PitchBend             = 0xE0, // Pitch Bend
                SystemExclusive       = 0xF0, // System Exclusive
                TimeCodeQuarterFrame  = 0xF1, // System Common - MIDI Time Code Quarter Frame
                SongPosition          = 0xF2, // System Common - Song Position Pointer
                SongSelect            = 0xF3, // System Common - Song Select
                TuneRequest           = 0xF6, // System Common - Tune Request
                Clock                 = 0xF8, // System Real Time - Timing Clock
                Start                 = 0xFA, // System Real Time - Start
                Continue              = 0xFB, // System Real Time - Continue
                Stop                  = 0xFC, // System Real Time - Stop
                ActiveSensing         = 0xFE, // System Real Time - Active Sensing
                SystemReset           = 0xFF, // System Real Time - System Reset
        };
        void begin(void) { }
        void end(void) { }
	void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable=0) {
		send(0x80, note, velocity, channel, cable);
	}
	void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable=0) {
		send(0x90, note, velocity, channel, cable);
	}
	void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable=0) {
		send(0xA0, note, pressure, channel, cable);
	}
	void sendAfterTouchPoly(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable=0) {
		send(0xA0, note, pressure, channel, cable);
	}
	void sendControlChange(uint8_t control, uint8_t value, uint8_t channel, uint8_t cable=0) {
		send(0xB0, control, value, channel, cable);
	}
	void sendProgramChange(uint8_t program, uint8_t channel, uint8_t cable=0) {
		send(0xC0, program, 0, channel, cable);
	}
	void sendAfterTouch(uint8_t pressure, uint8_t channel, uint8_t cable=0) {
		send(0xD0, pressure, 0, channel, cable);
	}
	void sendPitchBend(int value, uint8_t channel, uint8_t cable=0) {
		if (value < -8192) {
			value = -8192;
		} else if (value > 8191) {
			value = 8191;
		}
		value += 8192;
		send(0xE0, value, value >> 7, channel, cable);
	}
	void sendSysEx(uint16_t length, const uint8_t *data, bool hasTerm=false, uint8_t cable=0) {
		if (cable > 0) return;
		if (hasTerm) {
			sendSysEx_BufferHasTerm(length, data);
		} else {
			sendSysEx_AddTermBytes(length, data);
		}
	}
	void sendRealTime(uint8_t type, uint8_t cable=0) __attribute__((always_inline)) __attribute__((always_inline)) {
                switch (type) {
                        case 0xF8: // Clock
                        case 0xFA: // Start
                        case 0xFB: // Continue
                        case 0xFC: // Stop
                        case 0xFE: // ActiveSensing
                        case 0xFF: // SystemReset
                                send(type, 0, 0, 0, cable);
                                break;
                        default: // Invalid Real Time marker
                                break;
                }
        }
        void sendTimeCodeQuarterFrame(uint8_t type, uint8_t value, uint8_t cable=0) __attribute__((always_inline)) __attribute__((always_inline)) {
                send(0xF1, ((type & 0x07) << 4) | (value & 0x0F), 0, 0, cable);
        }
        void sendSongPosition(uint16_t beats, uint8_t cable=0) __attribute__((always_inline)) {
                send(0xF2, beats, beats >> 7, 0, cable);
        }
        void sendSongSelect(uint8_t song, uint8_t cable=0) __attribute__((always_inline)) {
                send(0xF3, song, 0, 0, cable);
        }
        void sendTuneRequest(uint8_t cable=0) __attribute__((always_inline)) {
                send(0xF6, 0, 0, 0, cable);
        }
        void beginRpn(uint16_t number, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(101, number >> 7, channel, cable);
                sendControlChange(100, number, channel, cable);
        }
        void sendRpnValue(uint16_t value, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(6, value >> 7, channel, cable);
                sendControlChange(38, value, channel, cable);
        }
        void sendRpnIncrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(96, amount, channel, cable);
        }
        void sendRpnDecrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(97, amount, channel, cable);
        }
        void endRpn(uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(101, 0x7F, channel, cable);
                sendControlChange(100, 0x7F, channel, cable);
        }
        void beginNrpn(uint16_t number, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(99, number >> 7, channel, cable);
                sendControlChange(98, number, channel, cable);
        }
        void sendNrpnValue(uint16_t value, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(6, value >> 7, channel, cable);
                sendControlChange(38, value, channel, cable);
        }
        void sendNrpnIncrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(96, amount, channel, cable);
        }
        void sendNrpnDecrement(uint8_t amount, uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(97, amount, channel, cable);
        }
        void endNrpn(uint8_t channel, uint8_t cable=0) __attribute__((always_inline)) {
                sendControlChange(99, 0x7F, channel, cable);
                sendControlChange(98, 0x7F, channel, cable);
        }
        void send(uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel, uint8_t cable) __attribute__((always_inline)) {
		if (cable > 0) return;
		if (type < 0xF0) {
			if (type < 0x80) return;
			send_raw(type >> 4, (type & 0xF0) | ((channel - 1) & 0x0F),
				data1 & 0x7F, data2 & 0x7F);
		} else if (type >= 0xF8 || type == 0xF6) {
			send_raw(0x0F, type, 0, 0);
		} else if (type == 0xF1 || type == 0xF3) {
			send_raw(0x02, type, data1 & 0x7F, 0);
		} else if (type == 0xF2) {
			send_raw(0x03, type, data1 & 0x7F, data2 & 0x7F);
		}
	}
	void send_now(void);
	uint8_t analog2velocity(uint16_t val, uint8_t range);
	bool read(uint8_t channel=0);
	inline uint8_t getType(void) {
		return msg_type;
	}
	uint8_t getCable(void) {
		return 0;
	}
	uint8_t getChannel(void) {
		return msg_channel;
	}
	uint8_t getData1(void) {
		return msg_data1;
	}
	uint8_t getData2(void) {
		return msg_data2;
	}
	uint8_t * getSysExArray(void) {
		return msg_sysex;
	}
	void setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
		// type: 0x80  NoteOff
		handleNoteOff = fptr;
	}
	void setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
		// type: 0x90  NoteOn
		handleNoteOn = fptr;
	}
	void setHandleVelocityChange(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
		// type: 0xA0  AfterTouchPoly
		handleVelocityChange = fptr;
	}
	void setHandleAfterTouchPoly(void (*fptr)(uint8_t channel, uint8_t note, uint8_t pressure)) {
		// type: 0xA0  AfterTouchPoly
		handleVelocityChange = fptr;
	}
	void setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t control, uint8_t value)) {
		// type: 0xB0  ControlChange
		handleControlChange = fptr;
	}
	void setHandleProgramChange(void (*fptr)(uint8_t channel, uint8_t program)) {
		// type: 0xC0  ProgramChange
		handleProgramChange = fptr;
	}
	void setHandleAfterTouch(void (*fptr)(uint8_t channel, uint8_t pressure)) {
		// type: 0xD0  AfterTouchChannel
		handleAfterTouch = fptr;
	}
	void setHandleAfterTouchChannel(void (*fptr)(uint8_t channel, uint8_t pressure)) {
		// type: 0xD0  AfterTouchChannel
		handleAfterTouch = fptr;
	}
	void setHandlePitchChange(void (*fptr)(uint8_t channel, int pitch)) {
		// type: 0xE0  PitchBend
		handlePitchChange = fptr;
	}
	void setHandleSysEx(void (*fptr)(const uint8_t *data, uint16_t length, bool complete)) {
		// type: 0xF0  SystemExclusive - multiple calls for message bigger than buffer
		handleSysExPartial = (void (*)(const uint8_t *, uint16_t, uint8_t))fptr;
	}
	void setHandleSystemExclusive(void (*fptr)(const uint8_t *data, uint16_t length, bool complete)) {
		// type: 0xF0  SystemExclusive - multiple calls for message bigger than buffer
		handleSysExPartial = (void (*)(const uint8_t *, uint16_t, uint8_t))fptr;
	}
	void setHandleSystemExclusive(void (*fptr)(uint8_t *data, unsigned int size)) {
		// type: 0xF0  SystemExclusive - single call, message larger than buffer is truncated
		handleSysExComplete = fptr;
	}
	void setHandleTimeCodeQuarterFrame(void (*fptr)(uint8_t data)) {
		// type: 0xF1  TimeCodeQuarterFrame
		handleTimeCodeQuarterFrame = fptr;
	}
	void setHandleSongPosition(void (*fptr)(uint16_t beats)) {
		// type: 0xF2  SongPosition
		handleSongPosition = fptr;
	}
	void setHandleSongSelect(void (*fptr)(uint8_t songnumber)) {
		// type: 0xF3  SongSelect
		handleSongSelect = fptr;
	}
	void setHandleTuneRequest(void (*fptr)(void)) {
		// type: 0xF6  TuneRequest
		handleTuneRequest = fptr;
	}
	void setHandleClock(void (*fptr)(void)) {
		// type: 0xF8  Clock
		handleClock = fptr;
	}
	void setHandleStart(void (*fptr)(void)) {
		// type: 0xFA  Start
		handleStart = fptr;
	}
	void setHandleContinue(void (*fptr)(void)) {
		// type: 0xFB  Continue
		handleContinue = fptr;
	}
	void setHandleStop(void (*fptr)(void)) {
		// type: 0xFC  Stop
		handleStop = fptr;
	}
	void setHandleActiveSensing(void (*fptr)(void)) {
		// type: 0xFE  ActiveSensing
		handleActiveSensing = fptr;
	}
	void setHandleSystemReset(void (*fptr)(void)) {
		// type: 0xFF  SystemReset
		handleSystemReset = fptr;
	}
	void setHandleRealTimeSystem(void (*fptr)(uint8_t realtimebyte)) {
		// type: 0xF8-0xFF - if more specific handler not configured
		handleRealTimeSystem = fptr;
	}
private:
	void send_raw(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);
	uint32_t midiusb_available();
	void midiusb_read(uint8_t *buf);
	void sendSysEx_BufferHasTerm(uint16_t length, const uint8_t *data);
	void sendSysEx_AddTermBytes(uint16_t length, const uint8_t *data);
	void read_sysex_byte(uint8_t b);
	uint8_t msg_channel;
	uint8_t msg_type;
	uint8_t msg_data1;
	uint8_t msg_data2;
	uint8_t msg_sysex[USB_MIDI_SYSEX_MAX];
	uint16_t msg_sysex_len;
	void (*handleNoteOff)(uint8_t ch, uint8_t note, uint8_t vel);
	void (*handleNoteOn)(uint8_t ch, uint8_t note, uint8_t vel);
	void (*handleVelocityChange)(uint8_t ch, uint8_t note, uint8_t vel);
	void (*handleControlChange)(uint8_t ch, uint8_t, uint8_t);
	void (*handleProgramChange)(uint8_t ch, uint8_t);
	void (*handleAfterTouch)(uint8_t ch, uint8_t);
	void (*handlePitchChange)(uint8_t ch, int pitch);
	void (*handleSysExPartial)(const uint8_t *data, uint16_t length, uint8_t complete);
	void (*handleSysExComplete)(uint8_t *data, unsigned int size);
	void (*handleTimeCodeQuarterFrame)(uint8_t data);
	void (*handleSongPosition)(uint16_t beats);
	void (*handleSongSelect)(uint8_t songnumber);
	void (*handleTuneRequest)(void);
	void (*handleClock)(void);
	void (*handleStart)(void);
	void (*handleContinue)(void);
	void (*handleStop)(void);
	void (*handleActiveSensing)(void);
	void (*handleSystemReset)(void);
	void (*handleRealTimeSystem)(uint8_t rtb);
	friend class MIDI_;
};

extern usb_midi_class usbMIDI;


class usb_serial_class : public Stream
{
public:
	// standard Arduino functions
	void begin(long);
	void end();
	virtual int available();
	virtual int read();
	virtual int peek();
	virtual void flush();
#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void write(uint8_t);
#endif
	using Print::write;
	operator bool();
	// Teensy extensions
	void send_now(void);
	uint32_t baud(void);
	uint8_t stopbits(void);
	uint8_t paritytype(void);
	uint8_t numbits(void);
	uint8_t dtr(void);
	uint8_t rts(void);
private:
	uint8_t readnext(void);
};

extern usb_serial_class Serial;


#endif
