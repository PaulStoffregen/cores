
#include "core_pins.h"

/*
struct digital_pin_bitband_and_config_table_struct {
        volatile uint32_t *reg;
        volatile uint32_t *mux;
        volatile uint32_t *pad;
        uint32_t mask;
};
extern const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[];
#define digitalPinToPort(pin)    (pin)
#define digitalPinToBitMask(pin) (digital_pin_to_info_PGM[(pin)].mask)
#define portOutputRegister(pin)  ((digital_pin_to_info_PGM[(pin)].reg))
#define portSetRegister(pin)     ((digital_pin_to_info_PGM[(pin)].reg + 0x21))
#define portClearRegister(pin)   ((digital_pin_to_info_PGM[(pin)].reg + 0x22))
#define portToggleRegister(pin)  ((digital_pin_to_info_PGM[(pin)].reg + 0x23))
#define portInputRegister(pin)   ((digital_pin_to_info_PGM[(pin)].reg + 2))
#define portModeRegister(pin)    ((digital_pin_to_info_PGM[(pin)].reg + 1))
#define portConfigRegister(pin)  ((digital_pin_to_info_PGM[(pin)].max))
#define digitalPinToPortReg(pin) (portOutputRegister(pin))
*/

const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[] = PINS_TO_DIGITAL_INFO;

void digitalWrite(uint8_t pin, uint8_t val)
{
	const struct digital_pin_bitband_and_config_table_struct *p;
	uint32_t pinmode, mask;

	if (pin >= CORE_NUM_DIGITAL) return;
	p = digital_pin_to_info_PGM + pin;
	pinmode = *(p->reg + 1);
	mask = p->mask;
	if (pinmode & mask) {
		// pin is configured for output mode
		if (val) {
			*(p->reg + 0x21) = mask; // set register
		} else {
			*(p->reg + 0x22) = mask; // clear register
		}
	} else {
		// pin is configured for input mode
		// value controls PULLUP/PULLDOWN resistors
		if (val) {
			*(p->pad) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;
		} else {
			*(p->pad) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(0) | IOMUXC_PAD_HYS;
		}
	}
}

void digitalToggle(uint8_t pin)
{
	const struct digital_pin_bitband_and_config_table_struct *p;
	uint32_t mask;

	if (pin >= CORE_NUM_DIGITAL) return;
	p = digital_pin_to_info_PGM + pin;
	mask = p->mask;
	*(p->reg + 0x23) = mask; // toggle register
}

uint8_t digitalRead(uint8_t pin)
{
	const struct digital_pin_bitband_and_config_table_struct *p;

	if (pin >= CORE_NUM_DIGITAL) return 0;
	p = digital_pin_to_info_PGM + pin;
	return (*(p->reg + 2) & p->mask) ? 1 : 0;
}

void pinMode(uint8_t pin, uint8_t mode)
{
	const struct digital_pin_bitband_and_config_table_struct *p;

	if (pin >= CORE_NUM_DIGITAL) return;
	p = digital_pin_to_info_PGM + pin;
	if (mode == OUTPUT || mode == OUTPUT_OPENDRAIN) {
		*(p->reg + 1) |= p->mask; // TODO: atomic
		if (mode == OUTPUT) {
			*(p->pad) = IOMUXC_PAD_DSE(7);
		} else { // OUTPUT_OPENDRAIN
			*(p->pad) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_ODE;
		}
	} else {
		*(p->reg + 1) &= ~(p->mask); // TODO: atomic
		if (mode == INPUT) {
			*(p->pad) = IOMUXC_PAD_DSE(7);
		} else if (mode == INPUT_PULLUP) {
			*(p->pad) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;
		} else if (mode == INPUT_PULLDOWN) {
			*(p->pad) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(0) | IOMUXC_PAD_HYS;
		} else { // INPUT_DISABLE
			*(p->pad) = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_HYS;
		}
	}
	*(p->mux) = 5 | 0x10;
}

void _shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
        if (bitOrder == LSBFIRST) {
                shiftOut_lsbFirst(dataPin, clockPin, value);
        } else {
                shiftOut_msbFirst(dataPin, clockPin, value);
        }
}

static const unsigned maxSpeed = 10000000ULL; //10 MHz
static const unsigned maxSpeedBeforeDelay = 392000000ULL; //max F_CPU_ACTUAL before doing delays (measured for 10MHz, -O2)

void shiftOut_lsbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value)
{
	uint8_t mask;
	if (F_CPU_ACTUAL > maxSpeedBeforeDelay) {
		uint32_t cycles = (F_CPU_ACTUAL / 2 / maxSpeed);
		uint32_t t = ARM_DWT_CYCCNT;
		for (mask = 0x01; mask; mask <<= 1) {
		    digitalWrite(dataPin, value & mask);
		    do {;} while(ARM_DWT_CYCCNT - t < cycles);
		    t += cycles / 2;

		    digitalWrite(clockPin, HIGH);
		    do {;} while(ARM_DWT_CYCCNT - t < cycles);
		    t += cycles;

		    digitalWrite(clockPin, LOW);
		    do {;} while(ARM_DWT_CYCCNT - t < cycles);
		    t += cycles / 2;
		}
	}
	else
	for (mask=0x01; mask; mask <<= 1) {
		digitalWrite(dataPin, value & mask);
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
}

void shiftOut_msbFirst(uint8_t dataPin, uint8_t clockPin, uint8_t value)
{
	uint32_t v;
	asm volatile ("rbit %0, %1" : "=r" (v) : "r" (value) );
	shiftOut_lsbFirst(dataPin, clockPin, v >> 24);
}

uint8_t _shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
        if (bitOrder == LSBFIRST) {
                return shiftIn_lsbFirst(dataPin, clockPin);
        } else {
                return shiftIn_msbFirst(dataPin, clockPin);
        }
}

uint8_t shiftIn_lsbFirst(uint8_t dataPin, uint8_t clockPin)
{
        uint8_t mask, value=0;
        for (mask=0x01; mask; mask <<= 1) {
                digitalWrite(clockPin, HIGH);
                if (digitalRead(dataPin)) value |= mask;
                digitalWrite(clockPin, LOW);
        }
        return value;
}

uint8_t shiftIn_msbFirst(uint8_t dataPin, uint8_t clockPin)
{
        uint8_t mask, value=0;
        for (mask=0x80; mask; mask >>= 1) {
                digitalWrite(clockPin, HIGH);
                if (digitalRead(dataPin)) value |= mask;
                digitalWrite(clockPin, LOW);
        }
        return value;
}

//(*portInputRegister(pin) & digitalPinToBitMask(pin))
uint32_t pulseIn_high(uint8_t pin, uint32_t timeout)
{
	const struct digital_pin_bitband_and_config_table_struct *p;
	p = digital_pin_to_info_PGM + pin;

	uint32_t usec_start, usec_stop;

	// wait for any previous pulse to end
	usec_start = micros();
	while ((*(p->reg + 2) & p->mask)) {
		if (micros()-usec_start > timeout) return 0;
	}
	// wait for the pulse to start
	usec_start = micros();
	while (!(*(p->reg + 2) & p->mask)) {
		if (micros()-usec_start > timeout) return 0;
	}
	usec_start = micros();
	// wait for the pulse to stop
	while ((*(p->reg + 2) & p->mask)) {
		if (micros()-usec_start > timeout) return 0;
	}
	usec_stop = micros();
	return usec_stop - usec_start;
}

uint32_t pulseIn_low(uint8_t pin, uint32_t timeout)
{
	const struct digital_pin_bitband_and_config_table_struct *p;
	p = digital_pin_to_info_PGM + pin;

	uint32_t usec_start, usec_stop;

	// wait for any previous pulse to end
	usec_start = micros();
	while (!(*(p->reg + 2) & p->mask)) {
		if (micros() - usec_start > timeout) return 0;
	}
	// wait for the pulse to start
	usec_start = micros();
	while ((*(p->reg + 2) & p->mask)) {
		if (micros() - usec_start > timeout) return 0;
	}
	usec_start = micros();
	// wait for the pulse to stop
	while (!(*(p->reg + 2) & p->mask)) {
		if (micros() - usec_start > timeout) return 0;
	}
	usec_stop = micros();
	return usec_stop - usec_start;
}

// TODO: an inline version should handle the common case where state is const
uint32_t pulseIn(uint8_t pin, uint8_t state, uint32_t timeout)
{
	if (pin >= CORE_NUM_DIGITAL) return 0;
	if (state) return pulseIn_high(pin, timeout);
	return pulseIn_low(pin, timeout);
}
