
#include "HardwareSerial.h"

#include "debug/printf.h"

/*typedef struct {
        const uint32_t VERID;
        const uint32_t PARAM;
        volatile uint32_t GLOBAL;
        volatile uint32_t PINCFG;
        volatile uint32_t BAUD;
        volatile uint32_t STAT;
        volatile uint32_t CTRL;
        volatile uint32_t DATA;
        volatile uint32_t MATCH;
        volatile uint32_t MODIR;
        volatile uint32_t FIFO;
        volatile uint32_t WATER;
} IMXRT_LPUART_t; */

#define UART_CLOCK 24000000

void HardwareSerial::begin(uint32_t baud, uint8_t format)
{
	//printf("HardwareSerial begin\n");
	float base = (float)UART_CLOCK / (float)baud;
	float besterr = 1e20;
	int bestdiv = 1;
	int bestosr = 4;
	for (int osr=4; osr <= 32; osr++) {
		float div = base / (float)osr;
		int divint = (int)(div + 0.5f);
		if (divint < 1) divint = 1;
		else if (divint > 8191) divint = 8191;
		float err = ((float)divint - div) / div;
		if (err < 0.0f) err = -err;
		if (err <= besterr) {
			besterr = err;
			bestdiv = divint;
			bestosr = osr;
		}
	}
	//printf(" baud %d: osr=%d, div=%d\n", baud, bestosr, bestdiv);
	hardware->ccm_register |= hardware->ccm_value;
	hardware->rx_mux_register = hardware->rx_mux_val;
	hardware->tx_mux_register = hardware->tx_mux_val;
	port->BAUD = LPUART_BAUD_OSR(bestosr - 1) | LPUART_BAUD_SBR(bestdiv);
	port->CTRL = LPUART_CTRL_TE | LPUART_CTRL_RE;
};

int HardwareSerial::available(void)
{
	return -1;
}

int HardwareSerial::peek(void)
{
	return -1;
}

int HardwareSerial::read(void)
{
	return -1;
}
void HardwareSerial::flush(void)
{
}

size_t HardwareSerial::write(uint8_t c)
{
	while (!(port->STAT & LPUART_STAT_TDRE)) ; // wait
	port->DATA = c;
	return 1;
}

__attribute__((section(".progmem")))
const HardwareSerial::hardware_t UART6_Hardware = {
	IRQ_LPUART6,
	CCM_CCGR3, CCM_CCGR3_LPUART6(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03, // pin 0
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02, // pin 1
	2, // page 473
	2, // page 472
};
HardwareSerial Serial1(&IMXRT_LPUART6, &UART6_Hardware);

static HardwareSerial::hardware_t UART4_Hardware = {
	IRQ_LPUART4,
	CCM_CCGR1, CCM_CCGR1_LPUART4(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01, // pin 6
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00, // pin 7
	2, // page 521
	2, // page 520
};
HardwareSerial Serial2(&IMXRT_LPUART4, &UART4_Hardware);

static HardwareSerial::hardware_t UART2_Hardware = {
	IRQ_LPUART2,
	CCM_CCGR0, CCM_CCGR0_LPUART2(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03, // pin 15
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02, // pin 14
	2, // page 491
	2, // page 490
};
HardwareSerial Serial3(&IMXRT_LPUART2, &UART2_Hardware);

static HardwareSerial::hardware_t UART3_Hardware = {
	IRQ_LPUART3,
	CCM_CCGR0, CCM_CCGR0_LPUART3(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07, // pin 16
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06, // pin 17
	2, // page 495
	2, // page 494
};
HardwareSerial Serial4(&IMXRT_LPUART3, &UART3_Hardware);

static HardwareSerial::hardware_t UART8_Hardware = {
	IRQ_LPUART8,
	CCM_CCGR6, CCM_CCGR6_LPUART8(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11, // pin 21
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10, // pin 20
	2, // page 499
	2, // page 498
};
HardwareSerial Serial5(&IMXRT_LPUART8, &UART8_Hardware);

static HardwareSerial::hardware_t UART1_Hardware = {
	IRQ_LPUART1,
	CCM_CCGR5, CCM_CCGR5_LPUART1(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13, // pin 25
	IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12, // pin 24
	2, // page 486
	2, // page 485
};
HardwareSerial Serial6(&IMXRT_LPUART1, &UART1_Hardware);

static HardwareSerial::hardware_t UART7_Hardware = {
	IRQ_LPUART7,
	CCM_CCGR5, CCM_CCGR5_LPUART7(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32, // pin 28
	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31, // pin 29
	2, // page 458
	2, // page 457
};
HardwareSerial Serial7(&IMXRT_LPUART7, &UART7_Hardware);

static HardwareSerial::hardware_t UART5_Hardware = {
	IRQ_LPUART5,
	CCM_CCGR3, CCM_CCGR3_LPUART5(CCM_CCGR_ON),
	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_24, // pin 30
	IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_23, // pin 31
	2, // page 450
	2, // page 449
};
HardwareSerial Serial8(&IMXRT_LPUART5, &UART5_Hardware);




