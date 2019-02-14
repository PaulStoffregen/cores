#include "imxrt.h"
#include "core_pins.h"
#include "debug/printf.h"

static uint8_t calibrating;
static uint8_t analog_config_bits = 10;
static uint8_t analog_num_average = 4;


const uint8_t pin_to_channel[] = { // pg 482
	7,	// 0/A0  AD_B1_02
	8,	// 1/A1  AD_B1_03
	12,	// 2/A2  AD_B1_07
	11,	// 3/A3  AD_B1_06
	6,	// 4/A4  AD_B1_01
	5,	// 5/A5  AD_B1_00
	15,	// 6/A6  AD_B1_10
	0,	// 7/A7  AD_B1_11
	13,	// 8/A8  AD_B1_08
	14,	// 9/A9  AD_B1_09
	128,	// 10
	128,	// 11
	128,	// 12
	128,	// 13
	7,	// 14/A0  AD_B1_02
	8,	// 15/A1  AD_B1_03
	12,	// 16/A2  AD_B1_07
	11,	// 17/A3  AD_B1_06
	6,	// 18/A4  AD_B1_01
	5,	// 19/A5  AD_B1_00
	15,	// 20/A6  AD_B1_10
	0,	// 21/A7  AD_B1_11
	13,	// 22/A8  AD_B1_08
	14,	// 23/A9  AD_B1_09
	1,	// 24/A10 AD_B0_12
	2	// 25/A11 AD_B0_13
		// 26/A12 AD_B1_14 - only on ADC2
		// 27/A13 AD_B1_15 - only on ADC2
};


static void wait_for_cal(void)
{
	printf("wait_for_cal\n");
	while (ADC1_GC & ADC_GC_CAL) ;
	// TODO: check CALF, but what do to about CAL failure?
	calibrating = 0;
	printf("cal complete\n");
}


int analogRead(uint8_t pin)
{
	if (pin > sizeof(pin_to_channel)) return 0;
	if (calibrating) wait_for_cal();
	uint8_t ch = pin_to_channel[pin];
	if (ch > 15) return 0;
	ADC1_HC0 = ch;
	while (!(ADC1_HS & ADC_HS_COCO0)) ; // wait
	return ADC1_R0;
}

void analogReference(uint8_t type)
{
}

void analogReadRes(unsigned int bits)
{
  uint32_t tmp32, mode;

   if (bits == 8) {
    // 8 bit conversion (17 clocks) plus 8 clocks for input settling
    mode = ADC_CFG_MODE(0) | ADC_CFG_ADSTS(3);
  } else if (bits == 10) {
    // 10 bit conversion (17 clocks) plus 20 clocks for input settling
    mode = ADC_CFG_MODE(1) | ADC_CFG_ADSTS(2) | ADC_CFG_ADLSMP;
  } else {
    // 12 bit conversion (25 clocks) plus 24 clocks for input settling
    mode = ADC_CFG_MODE(2) | ADC_CFG_ADSTS(3) | ADC_CFG_ADLSMP;
  }

  tmp32  = (ADC1_CFG & (0xFFFFFC00));
  tmp32 |= (ADC1_CFG & (0x03));  // ADICLK
  tmp32 |= (ADC1_CFG & (0xE0));  // ADIV & ADLPC

  tmp32 |= mode; 
  ADC1_CFG = tmp32;
}

void analogReadAveraging(unsigned int num)
{
  uint32_t mode;
  
  //disable averaging
  ADC1_GC &= ~0x20;
  mode = ADC1_CFG & ~0xC000;

    if (num >= 32) {
      mode |= ADC_CFG_AVGS(3);
    } else if (num >= 16) {
      mode |= ADC_CFG_AVGS(2);
    } else if (num >= 8) {
      mode |= ADC_CFG_AVGS(1);
    } else if (num >= 4) {
      mode |= ADC_CFG_AVGS(0);
    } else {
      mode |= 0;
    }

  ADC1_CFG |= mode;

  if(num >= 4)
      ADC1_GC |= ADC_GC_AVGE;// turns on averaging
}

#define MAX_ADC_CLOCK 20000000

__attribute__((section(".progmem")))
void analog_init(void)
{
	uint32_t mode, avg=0;

	printf("analogInit\n");

	CCM_CCGR1 |= CCM_CCGR1_ADC1(CCM_CCGR_ON);

	if (analog_config_bits == 8) {
		// 8 bit conversion (17 clocks) plus 8 clocks for input settling
		mode = ADC_CFG_MODE(0) | ADC_CFG_ADSTS(3);
	} else if (analog_config_bits == 10) {
		// 10 bit conversion (17 clocks) plus 20 clocks for input settling
		mode = ADC_CFG_MODE(1) | ADC_CFG_ADSTS(2) | ADC_CFG_ADLSMP;
	} else {
		// 12 bit conversion (25 clocks) plus 24 clocks for input settling
		mode = ADC_CFG_MODE(2) | ADC_CFG_ADSTS(3) | ADC_CFG_ADLSMP;
	}
	if (analog_num_average >= 4) {
		if (analog_num_average >= 32) {
			mode |= ADC_CFG_AVGS(3);
		} else if (analog_num_average >= 16) {
			mode |= ADC_CFG_AVGS(2);
		} else if (analog_num_average >= 8) {
			mode |= ADC_CFG_AVGS(1);
		}
		avg = ADC_GC_AVGE;
	}
#if 1
	mode |= ADC_CFG_ADIV(1) | ADC_CFG_ADICLK(3); // async clock
#else
	uint32_t clock = F_BUS;
	if (clock > MAX_ADC_CLOCK*8) {
		mode |= ADC_CFG_ADIV(3) | ADC_CFG_ADICLK(1); // use IPG/16
	} else if (clock > MAX_ADC_CLOCK*4) {
		mode |= ADC_CFG_ADIV(2) | ADC_CFG_ADICLK(1); // use IPG/8
	} else if (clock > MAX_ADC_CLOCK*2) {
		mode |= ADC_CFG_ADIV(1) | ADC_CFG_ADICLK(1); // use IPG/4
	} else if (clock > MAX_ADC_CLOCK) {
		mode |= ADC_CFG_ADIV(0) | ADC_CFG_ADICLK(1); // use IPG/2
	} else {
		mode |= ADC_CFG_ADIV(0) | ADC_CFG_ADICLK(0); // use IPG
	}
#endif

	ADC1_CFG = mode | ADC_HC_AIEN | ADC_CFG_ADHSC;
	ADC1_GC = avg | ADC_GC_CAL;		// begin cal
	calibrating = 1;
}


