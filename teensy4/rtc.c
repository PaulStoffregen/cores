#include "imxrt.h"
#include "core_pins.h"

extern void *__rtc_localtime; // Arduino build process sets this

__attribute__((section(".progmem")))
void rtc_init()
{
	CCM_CCGR2 |= CCM_CCGR2_IOMUXC_SNVS(CCM_CCGR_ON);
	SNVS_LPGPR = SNVS_DEFAULT_PGD_VALUE;
	SNVS_LPSR = SNVS_LPSR_PGD_MASK;
	if((uint32_t)&__rtc_localtime> (rtc_get() + 15))
		rtc_set((uint32_t)&__rtc_localtime);
}

unsigned long rtc_get(void)
{
	unsigned long seconds = 0;
	unsigned long tmp = 0;

	do {
		seconds = tmp;
		tmp = (SNVS_LPSRTCMR << 17U) | (SNVS_LPSRTCLR >> 15U);
	} while (tmp != seconds);

	return seconds;
}

void rtc_set(unsigned long t)
{
	SNVS_LPSRTCMR = (uint32_t)(t >> 17);
	SNVS_LPSRTCLR = (uint32_t)(t << 15);
}

#if 0 //TODO
void rtc_compensate(int adjust)
{
}
#endif
