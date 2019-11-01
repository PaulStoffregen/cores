#include "imxrt.h"
#include "core_pins.h"
#include "debug/printf.h"


struct pwm_pin_info_struct {
	uint8_t type;    // 0=no pwm, 1=flexpwm, 2=quad
	uint8_t module;  // 0-3, 0-3
	uint8_t channel; // 0=X, 1=A, 2=B
	uint8_t muxval;  //
};

uint8_t analog_write_res = 8;

#define M(a, b) ((((a) - 1) << 4) | (b))

#if defined(__IMXRT1062__)

const struct pwm_pin_info_struct pwm_pin_info[] = {
	{1, M(1, 1), 0, 4},  // FlexPWM1_1_X   0  // AD_B0_03
	{1, M(1, 0), 0, 4},  // FlexPWM1_0_X   1  // AD_B0_02
	{1, M(4, 2), 1, 1},  // FlexPWM4_2_A   2  // EMC_04
	{1, M(4, 2), 2, 1},  // FlexPWM4_2_B   3  // EMC_05
	{1, M(2, 0), 1, 1},  // FlexPWM2_0_A   4  // EMC_06
	{1, M(2, 1), 1, 1},  // FlexPWM2_1_A   5  // EMC_08
	{1, M(2, 2), 1, 2},  // FlexPWM2_2_A   6  // B0_10
	{1, M(1, 3), 2, 6},  // FlexPWM1_3_B   7  // B1_01
	{1, M(1, 3), 1, 6},  // FlexPWM1_3_A   8  // B1_00
	{1, M(2, 2), 2, 2},  // FlexPWM2_2_B   9  // B0_11
	{2, M(1, 0), 0, 1},  // QuadTimer1_0  10  // B0_00
	{2, M(1, 2), 0, 1},  // QuadTimer1_2  11  // B0_02
	{2, M(1, 1), 0, 1},  // QuadTimer1_1  12  // B0_01
	{2, M(2, 0), 0, 1},  // QuadTimer2_0  13  // B0_03
	{2, M(3, 2), 0, 1},  // QuadTimer3_2  14  // AD_B1_02
	{2, M(3, 3), 0, 1},  // QuadTimer3_3  15  // AD_B1_03
	{0, M(1, 0), 0, 0},
	{0, M(1, 0), 0, 0},
	{2, M(3, 1), 0, 1},  // QuadTimer3_1  18  // AD_B1_01
	{2, M(3, 0), 0, 1},  // QuadTimer3_0  19  // AD_B1_00
	{0, M(1, 0), 0, 0},
	{0, M(1, 0), 0, 0},
	{1, M(4, 0), 1, 1},  // FlexPWM4_0_A  22  // AD_B1_08
	{1, M(4, 1), 1, 1},  // FlexPWM4_1_A  23  // AD_B1_09
	{1, M(1, 2), 0, 4},  // FlexPWM1_2_X  24  // AD_B0_12
	{1, M(1, 3), 0, 4},  // FlexPWM1_3_X  25  // AD_B0_13
	{0, M(1, 0), 0, 0},
	{0, M(1, 0), 0, 0},
	{1, M(3, 1), 2, 1},  // FlexPWM3_1_B  28  // EMC_32
	{1, M(3, 1), 1, 1},  // FlexPWM3_1_A  29  // EMC_31
	{0, M(1, 0), 0, 0},
	{0, M(1, 0), 0, 0},
	{0, M(1, 0), 0, 0},
	{1, M(2, 0), 2, 1},  // FlexPWM2_0_B  33  // EMC_07
	{1, M(1, 1), 2, 1},	 // FlexPWM1_1_B  34  // SD_B0_03
	{1, M(1, 1), 1, 1},	 // FlexPWM1_1_A  35  // SD_B0_02
	{1, M(1, 0), 2, 1},	 // FlexPWM1_0_B  36  // SD_B0_01
	{1, M(1, 0), 1, 1},	 // FlexPWM1_0_A  37  // SD_B0_00
	{1, M(1, 2), 2, 1},	 // FlexPWM1_2_B  38  // SD_B0_05
	{1, M(1, 2), 1, 1},	 // FlexPWM1_2_A  39  // SD_B0_04
};

#endif // __IMXRT1062__

void flexpwmWrite(IMXRT_FLEXPWM_t *p, unsigned int submodule, uint8_t channel, uint16_t val)
{
	uint16_t mask = 1 << submodule;
	uint32_t modulo = p->SM[submodule].VAL1;
	uint32_t cval = ((uint32_t)val * (modulo + 1)) >> analog_write_res;
	if (cval > modulo) cval = modulo; // TODO: is this check correct?

	//printf("flexpwmWrite, p=%08lX, sm=%d, ch=%c, cval=%ld\n",
		//(uint32_t)p, submodule, channel == 0 ? 'X' : (channel == 1 ? 'A' : 'B'), cval);
	p->MCTRL |= FLEXPWM_MCTRL_CLDOK(mask);
	switch (channel) {
	  case 0: // X
		p->SM[submodule].VAL0 = modulo - cval;
		p->OUTEN |= FLEXPWM_OUTEN_PWMX_EN(mask);
		//printf(" write channel X\n");
		break;
	  case 1: // A
		p->SM[submodule].VAL3 = cval;
		p->OUTEN |= FLEXPWM_OUTEN_PWMA_EN(mask);
		//printf(" write channel A\n");
		break;
	  case 2: // B
		p->SM[submodule].VAL5 = cval;
		p->OUTEN |= FLEXPWM_OUTEN_PWMB_EN(mask);
		//printf(" write channel B\n");
	}
	p->MCTRL |= FLEXPWM_MCTRL_LDOK(mask);
}

void flexpwmFrequency(IMXRT_FLEXPWM_t *p, unsigned int submodule, uint8_t channel, float frequency)
{
	uint16_t mask = 1 << submodule;
	uint32_t olddiv = p->SM[submodule].VAL1;
	uint32_t newdiv = (uint32_t)((float)F_BUS_ACTUAL / frequency + 0.5);
	uint32_t prescale = 0;
	//printf(" div=%lu\n", newdiv);
	while (newdiv > 65535 && prescale < 7) {
		newdiv = newdiv >> 1;
		prescale = prescale + 1;
	}
	if (newdiv > 65535) {
		newdiv = 65535;
	} else if (newdiv < 2) {
		newdiv = 2;
	}
	//printf(" div=%lu, scale=%lu\n", newdiv, prescale);
	p->MCTRL |= FLEXPWM_MCTRL_CLDOK(mask);
	p->SM[submodule].CTRL = FLEXPWM_SMCTRL_FULL | FLEXPWM_SMCTRL_PRSC(prescale);
	p->SM[submodule].VAL1 = newdiv - 1;
	p->SM[submodule].VAL0 = (p->SM[submodule].VAL0 * newdiv) / olddiv;
	p->SM[submodule].VAL3 = (p->SM[submodule].VAL3 * newdiv) / olddiv;
	p->SM[submodule].VAL5 = (p->SM[submodule].VAL5 * newdiv) / olddiv;
	p->MCTRL |= FLEXPWM_MCTRL_LDOK(mask);
}

void quadtimerWrite(IMXRT_TMR_t *p, unsigned int submodule, uint16_t val)
{
	uint32_t modulo = 65537 - p->CH[submodule].LOAD + p->CH[submodule].CMPLD1;
	uint32_t high = ((uint32_t)val * (modulo - 1)) >> analog_write_res;
	if (high >= modulo) high = modulo - 1; // TODO: is this check correct?

	//printf(" modulo=%lu\n", modulo);
	//printf(" high=%lu\n", high);
	uint32_t low = modulo - high; // TODO: low must never be 0 or 1 - can it be??
	//printf(" low=%lu\n", low);

	p->CH[submodule].LOAD = 65537 - low;
	p->CH[submodule].CMPLD1 = high;
}

void quadtimerFrequency(IMXRT_TMR_t *p, unsigned int submodule, float frequency)
{
	uint32_t newdiv = (uint32_t)((float)F_BUS_ACTUAL / frequency + 0.5);
	uint32_t prescale = 0;
	//printf(" div=%lu\n", newdiv);
	while (newdiv > 65534 && prescale < 7) {
		newdiv = newdiv >> 1; 
		prescale = prescale + 1;
	}
	if (newdiv > 65534) {
		newdiv = 65534;
	} else if (newdiv < 2) {
		newdiv = 2;
	}
	//printf(" div=%lu, scale=%lu\n", newdiv, prescale);
	uint32_t oldhigh = p->CH[submodule].CMPLD1;
	uint32_t oldlow = 65537 - p->CH[submodule].LOAD;
	uint32_t high = (oldhigh * newdiv) / (oldhigh + oldlow);
	// TODO: low must never be less than 2 - can it happen with this?
	uint32_t low = newdiv - high;
	//printf(" high=%lu, low=%lu\n", high, low);
	p->CH[submodule].LOAD = 65537 - low;
	p->CH[submodule].CMPLD1 = high;
	p->CH[submodule].CTRL = TMR_CTRL_CM(1) | TMR_CTRL_PCS(8 + prescale) |
		TMR_CTRL_LENGTH | TMR_CTRL_OUTMODE(6);
}

void analogWrite(uint8_t pin, int val)
{
	const struct pwm_pin_info_struct *info;

	if (pin >= CORE_NUM_DIGITAL) return;
	//printf("analogWrite, pin %d, val %d\n", pin, val);
	info = pwm_pin_info + pin;
	if (info->type == 1) {
		// FlexPWM pin
		IMXRT_FLEXPWM_t *flexpwm;
		switch ((info->module >> 4) & 3) {
		  case 0: flexpwm = &IMXRT_FLEXPWM1; break;
		  case 1: flexpwm = &IMXRT_FLEXPWM2; break;
		  case 2: flexpwm = &IMXRT_FLEXPWM3; break;
		  default: flexpwm = &IMXRT_FLEXPWM4;
		}
		flexpwmWrite(flexpwm, info->module & 0x03, info->channel, val);
	} else if (info->type == 2) {
		// QuadTimer pin
		IMXRT_TMR_t *qtimer;
		switch ((info->module >> 4) & 3) {
		  case 0: qtimer = &IMXRT_TMR1; break;
		  case 1: qtimer = &IMXRT_TMR2; break;
		  case 2: qtimer = &IMXRT_TMR3; break;
		  default: qtimer = &IMXRT_TMR4;
		}
		quadtimerWrite(qtimer, info->module & 0x03, val);
	} else {
		return;
	}
	*(portConfigRegister(pin)) = info->muxval;
	// TODO: pad config register
}

void analogWriteFrequency(uint8_t pin, float frequency)
{
	const struct pwm_pin_info_struct *info;

	if (pin >= CORE_NUM_DIGITAL) return;
	//printf("analogWriteFrequency, pin %d, freq %d\n", pin, (int)frequency);
	info = pwm_pin_info + pin;
	if (info->type == 1) {
		// FlexPWM pin
		IMXRT_FLEXPWM_t *flexpwm;
		switch ((info->module >> 4) & 3) {
		  case 0: flexpwm = &IMXRT_FLEXPWM1; break;
		  case 1: flexpwm = &IMXRT_FLEXPWM2; break;
		  case 2: flexpwm = &IMXRT_FLEXPWM3; break;
		  default: flexpwm = &IMXRT_FLEXPWM4;
		}
		flexpwmFrequency(flexpwm, info->module & 0x03, info->channel, frequency);
	} else if (info->type == 2) {
		// QuadTimer pin
		IMXRT_TMR_t *qtimer;
		switch ((info->module >> 4) & 3) {
		  case 0: qtimer = &IMXRT_TMR1; break;
		  case 1: qtimer = &IMXRT_TMR2; break;
		  case 2: qtimer = &IMXRT_TMR3; break;
		  default: qtimer = &IMXRT_TMR4;
		}
		quadtimerFrequency(qtimer, info->module & 0x03, frequency);
	}
}

void flexpwm_init(IMXRT_FLEXPWM_t *p)
{
	int i;

	p->FCTRL0 = FLEXPWM_FCTRL0_FLVL(15); // logic high = fault
	p->FSTS0 = 0x000F; // clear fault status
	p->FFILT0 = 0;
	p->MCTRL |= FLEXPWM_MCTRL_CLDOK(15);
	for (i=0; i < 4; i++) {
		p->SM[i].CTRL2 = FLEXPWM_SMCTRL2_INDEP | FLEXPWM_SMCTRL2_WAITEN
			| FLEXPWM_SMCTRL2_DBGEN;
		p->SM[i].CTRL = FLEXPWM_SMCTRL_FULL;
		p->SM[i].OCTRL = 0;
		p->SM[i].DTCNT0 = 0;
		p->SM[i].INIT = 0;
		p->SM[i].VAL0 = 0;
		p->SM[i].VAL1 = 33464;
		p->SM[i].VAL2 = 0;
		p->SM[i].VAL3 = 0;
		p->SM[i].VAL4 = 0;
		p->SM[i].VAL5 = 0;
	}
	p->MCTRL |= FLEXPWM_MCTRL_LDOK(15);
	p->MCTRL |= FLEXPWM_MCTRL_RUN(15);
}

void quadtimer_init(IMXRT_TMR_t *p)
{
	int i;

	for (i=0; i < 4; i++) {
		p->CH[i].CTRL = 0; // stop timer
		p->CH[i].CNTR = 0;
		p->CH[i].SCTRL = TMR_SCTRL_OEN | TMR_SCTRL_OPS | TMR_SCTRL_VAL | TMR_SCTRL_FORCE;
		p->CH[i].CSCTRL = TMR_CSCTRL_CL1(1) | TMR_CSCTRL_ALT_LOAD;
		// COMP must be less than LOAD - otherwise output is always low
		p->CH[i].LOAD = 24000;   // low time  (65537 - x) - 
		p->CH[i].COMP1 = 0;  // high time (0 = always low, max = LOAD-1)
		p->CH[i].CMPLD1 = 0;
		p->CH[i].CTRL = TMR_CTRL_CM(1) | TMR_CTRL_PCS(8) |
			TMR_CTRL_LENGTH | TMR_CTRL_OUTMODE(6);
	}
}

void pwm_init(void)
{
	//printf("pwm init\n");
	CCM_CCGR4 |= CCM_CCGR4_PWM1(CCM_CCGR_ON) | CCM_CCGR4_PWM2(CCM_CCGR_ON) |
		CCM_CCGR4_PWM3(CCM_CCGR_ON) | CCM_CCGR4_PWM4(CCM_CCGR_ON);
	CCM_CCGR6 |= CCM_CCGR6_QTIMER1(CCM_CCGR_ON) | CCM_CCGR6_QTIMER2(CCM_CCGR_ON) |
		CCM_CCGR6_QTIMER3(CCM_CCGR_ON) | CCM_CCGR6_QTIMER4(CCM_CCGR_ON);
	flexpwm_init(&IMXRT_FLEXPWM1);
	flexpwm_init(&IMXRT_FLEXPWM2);
	flexpwm_init(&IMXRT_FLEXPWM3);
	flexpwm_init(&IMXRT_FLEXPWM4);
	quadtimer_init(&IMXRT_TMR1);
	quadtimer_init(&IMXRT_TMR2);
	quadtimer_init(&IMXRT_TMR3);
}



void xbar_connect(unsigned int input, unsigned int output)
{
	if (input >= 88) return;
	if (output >= 132) return;
#if 1
	volatile uint16_t *xbar = &XBARA1_SEL0 + (output / 2);
	uint16_t val = *xbar;
	if (!(output & 1)) {
		val = (val & 0xFF00) | input;
	} else {
		val = (val & 0x00FF) | (input << 8);
	}
	*xbar = val;
#else
	// does not work, seems 8 bit access is not allowed
	volatile uint8_t *xbar = (volatile uint8_t *)XBARA1_SEL0;
	xbar[output] = input;
#endif
}

uint32_t analogWriteRes(uint32_t bits)
{
	uint32_t prior;
	if (bits < 1) {
		bits = 1;
	} else if (bits > 16) {
		bits = 16;
	}
	prior = analog_write_res;
	analog_write_res = bits;
	return prior;
}


