#include "imxrt.h"
#include "core_pins.h"
#include "debug/printf.h"
#include "avr/pgmspace.h"

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
	1,	// 24/A10 AD_B0_12 
	2,	// 25/A11 AD_B0_13
	128+3,	// 26/A12 AD_B1_14 - only on ADC2, 3
	128+4,	// 27/A13 AD_B1_15 - only on ADC2, 4
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
	2,	// 25/A11 AD_B0_13
	128+3,	// 26/A12 AD_B1_14 - only on ADC2, 3
	128+4,	// 27/A13 AD_B1_15 - only on ADC2, 4
#ifdef ARDUINO_TEENSY41
	255,	// 28
	255,	// 29
	255,	// 30
	255,	// 31
	255,	// 32
	255,	// 33
	255,	// 34
	255,	// 35
	255,	// 36
	255,	// 37
	128+1,	// 38/A14 AD_B1_12 - only on ADC2, 1
	128+2,	// 39/A15 AD_B1_13 - only on ADC2, 2
	9,	// 40/A16 AD_B1_04
	10,	// 41/A17 AD_B1_05
#endif
};


static void wait_for_cal(void)
{
	//printf("wait_for_cal\n");
	while (ADC1_GC & ADC_GC_CAL) ;
	while (ADC2_GC & ADC_GC_CAL) ;
	// TODO: check CALF, but what do to about CAL failure?
	calibrating = 0;
	//printf("cal complete\n");
}


int analogRead(uint8_t pin)
{
	if (pin > sizeof(pin_to_channel)) return 0;
	if (calibrating) wait_for_cal();
	uint8_t ch = pin_to_channel[pin];
	if (ch == 255) return 0;
//	printf("%d\n", ch);
//	if (ch > 15) return 0;
	if(!(ch & 0x80)) {
		ADC1_HC0 = ch;
		while (!(ADC1_HS & ADC_HS_COCO0)) ; // wait
		return ADC1_R0;
	} else {
		ADC2_HC0 = ch & 0x7f;
		while (!(ADC2_HS & ADC_HS_COCO0)) ; // wait
		return ADC2_R0;
	}
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
  
  tmp32  = (ADC2_CFG & (0xFFFFFC00));
  tmp32 |= (ADC2_CFG & (0x03));  // ADICLK
  tmp32 |= (ADC2_CFG & (0xE0));  // ADIV & ADLPC

  tmp32 |= mode; 
  ADC2_CFG = tmp32;
}

void analogReadAveraging(unsigned int num)
{
  uint32_t mode, mode1;
  
  //disable averaging, ADC1 and ADC2
  ADC1_GC &= ~0x20;
  mode = ADC1_CFG & ~0xC000;
  ADC2_GC &= ~0x20;
  mode1 = ADC2_CFG & ~0xC000;
  
    if (num >= 32) {
      mode |= ADC_CFG_AVGS(3);
      mode1 |= ADC_CFG_AVGS(3);

    } else if (num >= 16) {
      mode |= ADC_CFG_AVGS(2);
      mode1 |= ADC_CFG_AVGS(2);

    } else if (num >= 8) {
      mode |= ADC_CFG_AVGS(1);
      mode1 |= ADC_CFG_AVGS(1);

    } else if (num >= 4) {
      mode |= ADC_CFG_AVGS(0);
      mode1 |= ADC_CFG_AVGS(0);

    } else {
      mode |= 0;
      mode1 |= 0;
    }

  ADC1_CFG = mode;
  ADC2_CFG = mode1;
  
  if(num >= 4){
      ADC1_GC |= ADC_GC_AVGE;// turns on averaging
      ADC2_GC |= ADC_GC_AVGE;// turns on averaging
  }
}

#define MAX_ADC_CLOCK 20000000

FLASHMEM void analog_init(void)
{
	uint32_t mode, avg=0;

	printf("analogInit\n");

	CCM_CCGR1 |= CCM_CCGR1_ADC1(CCM_CCGR_ON);
	CCM_CCGR1 |= CCM_CCGR1_ADC2(CCM_CCGR_ON);
	
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
	//ADC1
	ADC1_CFG = mode | ADC_CFG_ADHSC;
	ADC1_GC = avg | ADC_GC_CAL;		// begin cal
	calibrating = 1;
	while (ADC1_GC & ADC_GC_CAL) ;
	calibrating = 0;
	//ADC2
	ADC2_CFG = mode | ADC_CFG_ADHSC;
	ADC2_GC = avg | ADC_GC_CAL;		// begin cal
	calibrating = 1;
	while (ADC2_GC & ADC_GC_CAL) ;
	calibrating = 0;
}


