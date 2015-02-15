#ifndef _AVR_SLEEP_H_
#define _AVR_SLEEP_H_ 1

#define SLEEP_MODE_IDLE         0
#define SLEEP_MODE_ADC		0
#define SLEEP_MODE_PWR_DOWN	1
#define SLEEP_MODE_PWR_SAVE	1
#define SLEEP_MODE_STANDBY	1
#define SLEEP_MODE_EXT_STANDBY	1

#define set_sleep_mode(mode)	// TODO: actually set the mode...
#define sleep_enable()
#define sleep_disable()
#define sleep_cpu()		(asm("wfi"))
#define sleep_bod_disable()
#define sleep_mode()		sleep_cpu()

// workaround for early versions of Nordic's BLE library
// EIMSK moved to a dummy byte in avr_emulation...
//#if defined(HAL_ACI_TL_H__) && defined(PLATFORM_H__)
//#define EIMSK uint8_t EIMSKworkaround=0; EIMSKworkaround
//#endif

#endif
