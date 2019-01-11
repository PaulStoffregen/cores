#include "Arduino.h"
#include "pins_arduino.h"
#include "debug/printf.h"

static void dummy_isr() {};
typedef void (*voidFuncPtr)(void);

// TODO: define these properly in core_pins.h - don't waste memory
#define CORE_MAX_PIN_PORT1 31
#define CORE_MAX_PIN_PORT2 31
#define CORE_MAX_PIN_PORT3 31
#define CORE_MAX_PIN_PORT4 31

voidFuncPtr isr_table_gpio1[CORE_MAX_PIN_PORT1+1] = { [0 ... CORE_MAX_PIN_PORT1] = dummy_isr };
voidFuncPtr isr_table_gpio2[CORE_MAX_PIN_PORT2+1] = { [0 ... CORE_MAX_PIN_PORT2] = dummy_isr };
voidFuncPtr isr_table_gpio3[CORE_MAX_PIN_PORT3+1] = { [0 ... CORE_MAX_PIN_PORT3] = dummy_isr };
voidFuncPtr isr_table_gpio4[CORE_MAX_PIN_PORT4+1] = { [0 ... CORE_MAX_PIN_PORT4] = dummy_isr };

#define DR    0
#define GDIR  1
#define PSR   2
#define ICR1  3
#define ICR2  4
#define IMR   5
#define ISR   6
#define EDGE  7

FASTRUN
void irq_anyport(volatile uint32_t *gpio, voidFuncPtr *table)
{
	uint32_t status = gpio[ISR] & gpio[IMR];
	gpio[ISR] = status;
	while (status) {
		uint32_t index = __builtin_ctz(status);
		table[index]();
		status = status & ~(1 << index);
		//status = status & (status - 1);
	}
}

FASTRUN
void irq_gpio1(void)
{
	irq_anyport(&GPIO1_DR, isr_table_gpio1);
}

FASTRUN
void irq_gpio2(void)
{
	irq_anyport(&GPIO2_DR, isr_table_gpio2);
}

FASTRUN
void irq_gpio3(void)
{
	irq_anyport(&GPIO3_DR, isr_table_gpio3);
}

FASTRUN
void irq_gpio4(void)
{
	irq_anyport(&GPIO4_DR, isr_table_gpio4);
}



void attachInterrupt(uint8_t pin, void (*function)(void), int mode)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	//printf("attachInterrupt, pin=%u\n", pin);
	volatile uint32_t *gpio = portOutputRegister(pin);
	volatile uint32_t *mux = portConfigRegister(pin);
	//volatile uint32_t *pad = portControlRegister(pin);
	uint32_t mask = digitalPinToBitMask(pin);

	voidFuncPtr *table;
	switch((uint32_t)gpio) {
		case (uint32_t)&GPIO1_DR:
			table = isr_table_gpio1;
			attachInterruptVector(IRQ_GPIO1_0_15, &irq_gpio1);
			attachInterruptVector(IRQ_GPIO1_16_31, &irq_gpio1);
			NVIC_ENABLE_IRQ(IRQ_GPIO1_0_15);
			NVIC_ENABLE_IRQ(IRQ_GPIO1_16_31);
			break;
		case (uint32_t)&GPIO2_DR:
			table = isr_table_gpio2;
			attachInterruptVector(IRQ_GPIO2_0_15, &irq_gpio2);
			attachInterruptVector(IRQ_GPIO2_16_31, &irq_gpio2);
			NVIC_ENABLE_IRQ(IRQ_GPIO2_0_15);
			NVIC_ENABLE_IRQ(IRQ_GPIO2_16_31);
			break;
		case (uint32_t)&GPIO3_DR:
			table = isr_table_gpio3;
			attachInterruptVector(IRQ_GPIO3_0_15, &irq_gpio3);
			attachInterruptVector(IRQ_GPIO3_16_31, &irq_gpio3);
			NVIC_ENABLE_IRQ(IRQ_GPIO3_0_15);
			NVIC_ENABLE_IRQ(IRQ_GPIO3_16_31);
			break;
		case (uint32_t)&GPIO4_DR:
			table = isr_table_gpio4;
			attachInterruptVector(IRQ_GPIO4_0_15, &irq_gpio4);
			attachInterruptVector(IRQ_GPIO4_16_31, &irq_gpio4);
			NVIC_ENABLE_IRQ(IRQ_GPIO4_0_15);
			NVIC_ENABLE_IRQ(IRQ_GPIO4_16_31);
			break;
		default:
			return;
	}

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
	gpio[IMR] &= ~mask;	// disable interrupt
	*mux = 5;		// pin is GPIO
	gpio[GDIR] &= ~mask;	// pin to input mode
	uint32_t index = __builtin_ctz(mask);
	table[index] = function;
	if (mode == CHANGE) {
		gpio[EDGE] |= mask;
	} else {
		gpio[EDGE] &= ~mask;
		if (index < 15) {
			uint32_t shift = index * 2;
			gpio[ICR1] = (gpio[ICR1] & ~(3 << shift)) | (icr << shift);
		} else {
			uint32_t shift = (index - 16) * 2;
			gpio[ICR2] = (gpio[ICR2] & ~(3 << shift)) | (icr << shift);
		}
	}
	gpio[ISR] = mask;  // clear any prior pending interrupt
	gpio[IMR] |= mask; // enable interrupt
}

void detachInterrupt(uint8_t pin)
{
	if (pin >= CORE_NUM_DIGITAL) return;
	volatile uint32_t *gpio = portOutputRegister(pin);
	uint32_t mask = digitalPinToBitMask(pin);
	gpio[IMR] &= ~mask;
}

