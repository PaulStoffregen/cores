#include "Arduino.h"
#include "pins_arduino.h"
#include "debug/printf.h"

#define DR_INDEX    0
#define GDIR_INDEX  1
#define PSR_INDEX   2
#define ICR1_INDEX  3
#define ICR2_INDEX  4
#define IMR_INDEX   5
#define ISR_INDEX   6
#define EDGE_INDEX  7

static void dummy_isr() {};
typedef void (*voidFuncPtr)(void);

// TODO: Use of Fast GPIO6 - GPIO9 probably breaks everything about attachInterrupt()

// TODO: define these properly in core_pins.h - don't waste memory
#define CORE_MAX_PIN_PORT1 31
#define CORE_MAX_PIN_PORT2 31
#define CORE_MAX_PIN_PORT3 31
#define CORE_MAX_PIN_PORT4 31

voidFuncPtr isr_table_gpio1[CORE_MAX_PIN_PORT1+1] = { [0 ... CORE_MAX_PIN_PORT1] = dummy_isr };
voidFuncPtr isr_table_gpio2[CORE_MAX_PIN_PORT2+1] = { [0 ... CORE_MAX_PIN_PORT2] = dummy_isr };
voidFuncPtr isr_table_gpio3[CORE_MAX_PIN_PORT3+1] = { [0 ... CORE_MAX_PIN_PORT3] = dummy_isr };
voidFuncPtr isr_table_gpio4[CORE_MAX_PIN_PORT4+1] = { [0 ... CORE_MAX_PIN_PORT4] = dummy_isr };

#if defined(__IMXRT1062__)
FASTRUN static inline __attribute__((always_inline))
inline void irq_anyport(volatile uint32_t *gpio, voidFuncPtr *table)
{
	uint32_t status = gpio[ISR_INDEX] & gpio[IMR_INDEX];
	if (status) {
		gpio[ISR_INDEX] = status;
		while (status) {
			uint32_t index = __builtin_ctz(status);
			table[index]();
			status = status & ~(1 << index);
			//status = status & (status - 1);
		}
	}
}

FASTRUN
void irq_gpio6789(void)
{
	irq_anyport(&GPIO6_DR, isr_table_gpio1);
	irq_anyport(&GPIO7_DR, isr_table_gpio2);
	irq_anyport(&GPIO8_DR, isr_table_gpio3);
	irq_anyport(&GPIO9_DR, isr_table_gpio4);
}

#endif

void attachInterrupt(uint8_t pin, void (*function)(void), int mode)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	//printf("attachInterrupt, pin=%u\n", pin);
	volatile uint32_t *gpio = portOutputRegister(pin);
	volatile uint32_t *mux = portConfigRegister(pin);
	//volatile uint32_t *pad = portControlRegister(pin);
	uint32_t mask = digitalPinToBitMask(pin);

	voidFuncPtr *table;

#if defined(__IMXRT1062__)

	switch((uint32_t)gpio) {
		case (uint32_t)&GPIO6_DR:
			table = isr_table_gpio1;
			break;
		case (uint32_t)&GPIO7_DR:
			table = isr_table_gpio2;
			break;
		case (uint32_t)&GPIO8_DR:
			table = isr_table_gpio3;
			break;
		case (uint32_t)&GPIO9_DR:
			table = isr_table_gpio4;
			break;
		default:
			return;
	}

	attachInterruptVector(IRQ_GPIO6789, &irq_gpio6789);
	NVIC_ENABLE_IRQ(IRQ_GPIO6789);

#endif

	uint32_t icr;
	switch (mode) {
		case CHANGE:  icr = 0; break;
		case RISING:  icr = 2; break;
		case FALLING: icr = 3; break;
		case LOW:     icr = 0; break;
		case HIGH:    icr = 1; break;
		default: return;
	}

	// TODO: global interrupt disable to protect these read-modify-write accesses?
	gpio[IMR_INDEX] &= ~mask;	// disable interrupt
	*mux = 5;		// pin is GPIO
	gpio[GDIR_INDEX] &= ~mask;	// pin to input mode
	uint32_t index = __builtin_ctz(mask);
	table[index] = function;
	if (mode == CHANGE) {
		gpio[EDGE_INDEX] |= mask;
	} else {
		gpio[EDGE_INDEX] &= ~mask;
		if (index < 16) {
			uint32_t shift = index * 2;
			gpio[ICR1_INDEX] = (gpio[ICR1_INDEX] & ~(3 << shift)) | (icr << shift);
		} else {
			uint32_t shift = (index - 16) * 2;
			gpio[ICR2_INDEX] = (gpio[ICR2_INDEX] & ~(3 << shift)) | (icr << shift);
		}
	}
	gpio[ISR_INDEX] = mask;  // clear any prior pending interrupt
	gpio[IMR_INDEX] |= mask; // enable interrupt
}

void detachInterrupt(uint8_t pin)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	volatile uint32_t *gpio = portOutputRegister(pin);
	uint32_t mask = digitalPinToBitMask(pin);
	gpio[IMR_INDEX] &= ~mask;
}
