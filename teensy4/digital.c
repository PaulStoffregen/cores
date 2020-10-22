
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

const struct digital_pin_bitband_and_config_table_struct digital_pin_to_info_PGM[] = {
	{&CORE_PIN0_PORTREG, &CORE_PIN0_CONFIG, &CORE_PIN0_PADCONFIG, CORE_PIN0_BITMASK},
	{&CORE_PIN1_PORTREG, &CORE_PIN1_CONFIG, &CORE_PIN1_PADCONFIG, CORE_PIN1_BITMASK},
	{&CORE_PIN2_PORTREG, &CORE_PIN2_CONFIG, &CORE_PIN2_PADCONFIG, CORE_PIN2_BITMASK},
	{&CORE_PIN3_PORTREG, &CORE_PIN3_CONFIG, &CORE_PIN3_PADCONFIG, CORE_PIN3_BITMASK},
	{&CORE_PIN4_PORTREG, &CORE_PIN4_CONFIG, &CORE_PIN4_PADCONFIG, CORE_PIN4_BITMASK},
	{&CORE_PIN5_PORTREG, &CORE_PIN5_CONFIG, &CORE_PIN5_PADCONFIG, CORE_PIN5_BITMASK},
	{&CORE_PIN6_PORTREG, &CORE_PIN6_CONFIG, &CORE_PIN6_PADCONFIG, CORE_PIN6_BITMASK},
	{&CORE_PIN7_PORTREG, &CORE_PIN7_CONFIG, &CORE_PIN7_PADCONFIG, CORE_PIN7_BITMASK},
	{&CORE_PIN8_PORTREG, &CORE_PIN8_CONFIG, &CORE_PIN8_PADCONFIG, CORE_PIN8_BITMASK},
	{&CORE_PIN9_PORTREG, &CORE_PIN9_CONFIG, &CORE_PIN9_PADCONFIG, CORE_PIN9_BITMASK},
	{&CORE_PIN10_PORTREG, &CORE_PIN10_CONFIG, &CORE_PIN10_PADCONFIG, CORE_PIN10_BITMASK},
	{&CORE_PIN11_PORTREG, &CORE_PIN11_CONFIG, &CORE_PIN11_PADCONFIG, CORE_PIN11_BITMASK},
	{&CORE_PIN12_PORTREG, &CORE_PIN12_CONFIG, &CORE_PIN12_PADCONFIG, CORE_PIN12_BITMASK},
	{&CORE_PIN13_PORTREG, &CORE_PIN13_CONFIG, &CORE_PIN13_PADCONFIG, CORE_PIN13_BITMASK},
	{&CORE_PIN14_PORTREG, &CORE_PIN14_CONFIG, &CORE_PIN14_PADCONFIG, CORE_PIN14_BITMASK},
	{&CORE_PIN15_PORTREG, &CORE_PIN15_CONFIG, &CORE_PIN15_PADCONFIG, CORE_PIN15_BITMASK},
	{&CORE_PIN16_PORTREG, &CORE_PIN16_CONFIG, &CORE_PIN16_PADCONFIG, CORE_PIN16_BITMASK},
	{&CORE_PIN17_PORTREG, &CORE_PIN17_CONFIG, &CORE_PIN17_PADCONFIG, CORE_PIN17_BITMASK},
	{&CORE_PIN18_PORTREG, &CORE_PIN18_CONFIG, &CORE_PIN18_PADCONFIG, CORE_PIN18_BITMASK},
	{&CORE_PIN19_PORTREG, &CORE_PIN19_CONFIG, &CORE_PIN19_PADCONFIG, CORE_PIN19_BITMASK},
	{&CORE_PIN20_PORTREG, &CORE_PIN20_CONFIG, &CORE_PIN20_PADCONFIG, CORE_PIN20_BITMASK},
	{&CORE_PIN21_PORTREG, &CORE_PIN21_CONFIG, &CORE_PIN21_PADCONFIG, CORE_PIN21_BITMASK},
	{&CORE_PIN22_PORTREG, &CORE_PIN22_CONFIG, &CORE_PIN22_PADCONFIG, CORE_PIN22_BITMASK},
	{&CORE_PIN23_PORTREG, &CORE_PIN23_CONFIG, &CORE_PIN23_PADCONFIG, CORE_PIN23_BITMASK},
	{&CORE_PIN24_PORTREG, &CORE_PIN24_CONFIG, &CORE_PIN24_PADCONFIG, CORE_PIN24_BITMASK},
	{&CORE_PIN25_PORTREG, &CORE_PIN25_CONFIG, &CORE_PIN25_PADCONFIG, CORE_PIN25_BITMASK},
	{&CORE_PIN26_PORTREG, &CORE_PIN26_CONFIG, &CORE_PIN26_PADCONFIG, CORE_PIN26_BITMASK},
	{&CORE_PIN27_PORTREG, &CORE_PIN27_CONFIG, &CORE_PIN27_PADCONFIG, CORE_PIN27_BITMASK},
	{&CORE_PIN28_PORTREG, &CORE_PIN28_CONFIG, &CORE_PIN28_PADCONFIG, CORE_PIN28_BITMASK},
	{&CORE_PIN29_PORTREG, &CORE_PIN29_CONFIG, &CORE_PIN29_PADCONFIG, CORE_PIN29_BITMASK},
	{&CORE_PIN30_PORTREG, &CORE_PIN30_CONFIG, &CORE_PIN30_PADCONFIG, CORE_PIN30_BITMASK},
	{&CORE_PIN31_PORTREG, &CORE_PIN31_CONFIG, &CORE_PIN31_PADCONFIG, CORE_PIN31_BITMASK},
	{&CORE_PIN32_PORTREG, &CORE_PIN32_CONFIG, &CORE_PIN32_PADCONFIG, CORE_PIN32_BITMASK},
	{&CORE_PIN33_PORTREG, &CORE_PIN33_CONFIG, &CORE_PIN33_PADCONFIG, CORE_PIN33_BITMASK},
	{&CORE_PIN34_PORTREG, &CORE_PIN34_CONFIG, &CORE_PIN34_PADCONFIG, CORE_PIN34_BITMASK},
	{&CORE_PIN35_PORTREG, &CORE_PIN35_CONFIG, &CORE_PIN35_PADCONFIG, CORE_PIN35_BITMASK},
	{&CORE_PIN36_PORTREG, &CORE_PIN36_CONFIG, &CORE_PIN36_PADCONFIG, CORE_PIN36_BITMASK},
	{&CORE_PIN37_PORTREG, &CORE_PIN37_CONFIG, &CORE_PIN37_PADCONFIG, CORE_PIN37_BITMASK},
	{&CORE_PIN38_PORTREG, &CORE_PIN38_CONFIG, &CORE_PIN38_PADCONFIG, CORE_PIN38_BITMASK},
	{&CORE_PIN39_PORTREG, &CORE_PIN39_CONFIG, &CORE_PIN39_PADCONFIG, CORE_PIN39_BITMASK},
#if CORE_NUM_DIGITAL > 40
	{&CORE_PIN40_PORTREG, &CORE_PIN40_CONFIG, &CORE_PIN40_PADCONFIG, CORE_PIN40_BITMASK},
	{&CORE_PIN41_PORTREG, &CORE_PIN41_CONFIG, &CORE_PIN41_PADCONFIG, CORE_PIN41_BITMASK},
	{&CORE_PIN42_PORTREG, &CORE_PIN42_CONFIG, &CORE_PIN42_PADCONFIG, CORE_PIN42_BITMASK},
	{&CORE_PIN43_PORTREG, &CORE_PIN43_CONFIG, &CORE_PIN43_PADCONFIG, CORE_PIN43_BITMASK},
	{&CORE_PIN44_PORTREG, &CORE_PIN44_CONFIG, &CORE_PIN44_PADCONFIG, CORE_PIN44_BITMASK},
	{&CORE_PIN45_PORTREG, &CORE_PIN45_CONFIG, &CORE_PIN45_PADCONFIG, CORE_PIN45_BITMASK},
#endif
#if CORE_NUM_DIGITAL > 46
	{&CORE_PIN46_PORTREG, &CORE_PIN46_CONFIG, &CORE_PIN46_PADCONFIG, CORE_PIN46_BITMASK},
	{&CORE_PIN47_PORTREG, &CORE_PIN47_CONFIG, &CORE_PIN47_PADCONFIG, CORE_PIN47_BITMASK},
	{&CORE_PIN48_PORTREG, &CORE_PIN48_CONFIG, &CORE_PIN48_PADCONFIG, CORE_PIN48_BITMASK},
	{&CORE_PIN49_PORTREG, &CORE_PIN49_CONFIG, &CORE_PIN49_PADCONFIG, CORE_PIN49_BITMASK},
	{&CORE_PIN50_PORTREG, &CORE_PIN50_CONFIG, &CORE_PIN50_PADCONFIG, CORE_PIN50_BITMASK},
	{&CORE_PIN51_PORTREG, &CORE_PIN51_CONFIG, &CORE_PIN51_PADCONFIG, CORE_PIN51_BITMASK},
	{&CORE_PIN52_PORTREG, &CORE_PIN52_CONFIG, &CORE_PIN52_PADCONFIG, CORE_PIN52_BITMASK},
	{&CORE_PIN53_PORTREG, &CORE_PIN53_CONFIG, &CORE_PIN53_PADCONFIG, CORE_PIN53_BITMASK},
	{&CORE_PIN54_PORTREG, &CORE_PIN54_CONFIG, &CORE_PIN54_PADCONFIG, CORE_PIN54_BITMASK},
#endif
};

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
