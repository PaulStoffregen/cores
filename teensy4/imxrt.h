#pragma once
#include <stdint.h>

// Definitions based these documents:
//   i.MX RT1060 Reference Manual, Rev. 2, 12/2019 - https://www.pjrc.com/teensy/datasheets.html
//   ARM v7-M Architecture Reference Manual (DDI 0403E.b)

enum IRQ_NUMBER_t {
        IRQ_DMA_CH0 =           0,
        IRQ_DMA_CH1 =           1,
        IRQ_DMA_CH2 =           2,
        IRQ_DMA_CH3 =           3,
        IRQ_DMA_CH4 =           4,
        IRQ_DMA_CH5 =           5,
        IRQ_DMA_CH6 =           6,
        IRQ_DMA_CH7 =           7,
        IRQ_DMA_CH8 =           8,
        IRQ_DMA_CH9 =           9,
        IRQ_DMA_CH10 =          10,
        IRQ_DMA_CH11 =          11,
        IRQ_DMA_CH12 =          12,
        IRQ_DMA_CH13 =          13,
        IRQ_DMA_CH14 =          14,
        IRQ_DMA_CH15 =          15,
        IRQ_DMA_ERROR =         16,
        IRQ_CTI0 =              17,
        IRQ_CTI1 =              18,
        IRQ_CORE_ERROR =        19, // TODO - name?
        IRQ_LPUART1 =           20,
        IRQ_LPUART2 =           21,
        IRQ_LPUART3 =           22,
        IRQ_LPUART4 =           23,
        IRQ_LPUART5 =           24,
        IRQ_LPUART6 =           25,
        IRQ_LPUART7 =           26,
        IRQ_LPUART8 =           27,
        IRQ_LPI2C1 =            28,
        IRQ_LPI2C2 =            29,
        IRQ_LPI2C3 =            30,
        IRQ_LPI2C4 =            31,
        IRQ_LPSPI1 =            32,
        IRQ_LPSPI2 =            33,
        IRQ_LPSPI3 =            34,
        IRQ_LPSPI4 =            35,
        IRQ_CAN1 =              36,
        IRQ_CAN2 =              37,
        IRQ_ADDR_ERR =          38, // TODO: name?
        IRQ_KPP =               39,
        IRQ_TSC_DIG =           40,
        IRQ_GPR_IRQ =           41,
        IRQ_LCDIF =             42,
        IRQ_CSI =               43,
        IRQ_PXP =               44,
        IRQ_WDOG2 =             45,
        IRQ_SNVS_IRQ =          46,
        IRQ_SNVS_SECURITY =     47,
        IRQ_SNVS_ONOFF =        48,
        IRQ_CSU =               49,
        IRQ_DCP0 =              50, // TODO: ???
        IRQ_DCP1 =              51, // TODO: ???
        IRQ_DCP2 =              52, // TODO: ???
        IRQ_TRNG =              53,
        IRQ_SJC_IRQ =           54,
        IRQ_BEE =               55,
        IRQ_SAI1 =              56,
        IRQ_SAI2 =              57,
        IRQ_SAI3_RX =           58,
        IRQ_SAI3_TX =           59,
        IRQ_SPDIF =             60,
        IRQ_BROWNOUT0 =         61,
        IRQ_Reserved1 =         62,
        IRQ_TEMPERATURE =       63,
        IRQ_TEMPERATURE_PANIC = 64,
        IRQ_USBPHY0 =           65,
        IRQ_USBPHY1 =           66,
        IRQ_ADC1 =              67,
        IRQ_ADC2 =              68,
        IRQ_DCDC =              69,
        IRQ_SOFTWARE =          70,
        IRQ_Reserved2 =         71,
        IRQ_GPIO1_INT0 =        72,
        IRQ_GPIO1_INT1 =        73,
        IRQ_GPIO1_INT2 =        74,
        IRQ_GPIO1_INT3 =        75,
        IRQ_GPIO1_INT4 =        76,
        IRQ_GPIO1_INT5 =        77,
        IRQ_GPIO1_INT6 =        78,
        IRQ_GPIO1_INT7 =        79,
        IRQ_GPIO1_0_15 =        80,
        IRQ_GPIO1_16_31 =       81,
        IRQ_GPIO2_0_15 =        82,
        IRQ_GPIO2_16_31 =       83,
        IRQ_GPIO3_0_15 =        84,
        IRQ_GPIO3_16_31 =       85,
        IRQ_GPIO4_0_15 =        86,
        IRQ_GPIO4_16_31 =       87,
        IRQ_GPIO5_0_15 =        88,
        IRQ_GPIO5_16_31 =       89,
        IRQ_FLEXIO1 =           90,
        IRQ_FLEXIO2 =           91,
        IRQ_WDOG1 =             92,
        IRQ_RTWDOG =            93,
        IRQ_EWM =               94,
        IRQ_CCM1 =              95,
        IRQ_CCM2 =              96,
        IRQ_GPC =               97,
        IRQ_SRC =               98,
        IRQ_Reserved3 =         99,
        IRQ_GPT1 =              100,
        IRQ_GPT2 =              101,
        IRQ_FLEXPWM1_0 =        102,
        IRQ_FLEXPWM1_1 =        103,
        IRQ_FLEXPWM1_2 =        104,
        IRQ_FLEXPWM1_3 =        105,
        IRQ_FLEXPWM1_FAULT =    106,
        IRQ_FLEXSPI2 =          107, // RT1060 only
        IRQ_FLEXSPI =           108,
        IRQ_SEMC =              109,
        IRQ_SDHC1 =             110,
        IRQ_SDHC2 =             111,
        IRQ_USB2 =              112,
        IRQ_USB1 =              113,
        IRQ_ENET =              114,
        IRQ_ENET_TIMER =        115,
        IRQ_XBAR1_01 =          116,
        IRQ_XBAR1_23 =          117,
        IRQ_ADC_ETC0 =          118,
        IRQ_ADC_ETC1 =          119,
        IRQ_ADC_ETC2 =          120,
        IRQ_ADC_ETC_ERR =       121,
        IRQ_PIT =               122,
        IRQ_ACMP1 =             123,
        IRQ_ACMP2 =             124,
        IRQ_ACMP3 =             125,
        IRQ_ACMP4 =             126,
        IRQ_Reserved4 =         127,
        IRQ_Reserved5 =         128,
        IRQ_ENC1 =              129,
        IRQ_ENC2 =              130,
        IRQ_ENC3 =              131,
        IRQ_ENC4 =              132,
        IRQ_QTIMER1 =           133,
        IRQ_QTIMER2 =           134,
        IRQ_QTIMER3 =           135,
        IRQ_QTIMER4 =           136,
        IRQ_FLEXPWM2_0 =        137,
        IRQ_FLEXPWM2_1 =        138,
        IRQ_FLEXPWM2_2 =        139,
        IRQ_FLEXPWM2_3 =        140,
        IRQ_FLEXPWM2_FAULT =    141,
        IRQ_FLEXPWM3_0 =        142,
        IRQ_FLEXPWM3_1 =        143,
        IRQ_FLEXPWM3_2 =        144,
        IRQ_FLEXPWM3_3 =        145,
        IRQ_FLEXPWM3_FAULT =    146,
        IRQ_FLEXPWM4_0 =        147,
        IRQ_FLEXPWM4_1 =        148,
        IRQ_FLEXPWM4_2 =        149,
        IRQ_FLEXPWM4_3 =        150,
        IRQ_FLEXPWM4_FAULT =    151,
        IRQ_ENET2 =             152, // RT1060 only
        IRQ_ENET2_TIMER =       153, // RT1060 only
        IRQ_CAN3 =              154, // RT1060 only
        IRQ_Reserved6 =         155,
        IRQ_FLEXIO3 =           156, // RT1060 only
        IRQ_GPIO6789 =          157, // RT1060 only
        IRQ_SJC_DEBUG =         158,
        IRQ_NMI_WAKEUP =        159
};
#define NVIC_NUM_INTERRUPTS     160
#define DMA_NUM_CHANNELS        32


#define DMAMUX_SOURCE_FLEXIO1_REQUEST0		0
#define DMAMUX_SOURCE_FLEXIO1_REQUEST1		0
#define DMAMUX_SOURCE_FLEXIO2_REQUEST0		1
#define DMAMUX_SOURCE_FLEXIO2_REQUEST1		1
#define DMAMUX_SOURCE_LPUART1_TX		2
#define DMAMUX_SOURCE_LPUART1_RX		3
#define DMAMUX_SOURCE_LPUART3_TX		4
#define DMAMUX_SOURCE_LPUART3_RX		5
#define DMAMUX_SOURCE_LPUART5_TX		6
#define DMAMUX_SOURCE_LPUART5_RX		7
#define DMAMUX_SOURCE_LPUART7_TX		8
#define DMAMUX_SOURCE_LPUART7_RX		9
#define DMAMUX_SOURCE_FLEXCAN3			11
#define DMAMUX_SOURCE_CSI			12
#define DMAMUX_SOURCE_LPSPI1_RX			13
#define DMAMUX_SOURCE_LPSPI1_TX			14
#define DMAMUX_SOURCE_LPSPI3_RX			15
#define DMAMUX_SOURCE_LPSPI3_TX			16
#define DMAMUX_SOURCE_LPI2C1			17
#define DMAMUX_SOURCE_LPI2C3			18
#define DMAMUX_SOURCE_SAI1_RX			19
#define DMAMUX_SOURCE_SAI1_TX			20
#define DMAMUX_SOURCE_SAI2_RX			21
#define DMAMUX_SOURCE_SAI2_TX			22
#define DMAMUX_SOURCE_ADC_ETC			23
#define DMAMUX_SOURCE_ADC1			24
#define DMAMUX_SOURCE_ACMP1			25
#define DMAMUX_SOURCE_ACMP3			26
#define DMAMUX_SOURCE_FLEXSPI_RX		28
#define DMAMUX_SOURCE_FLEXSPI_TX		29
#define DMAMUX_SOURCE_XBAR1_0			30
#define DMAMUX_SOURCE_XBAR1_1			31
#define DMAMUX_SOURCE_FLEXPWM1_READ0		32
#define DMAMUX_SOURCE_FLEXPWM1_READ1		33
#define DMAMUX_SOURCE_FLEXPWM1_READ2		34
#define DMAMUX_SOURCE_FLEXPWM1_READ3		35
#define DMAMUX_SOURCE_FLEXPWM1_WRITE0		36
#define DMAMUX_SOURCE_FLEXPWM1_WRITE1		37
#define DMAMUX_SOURCE_FLEXPWM1_WRITE2		38
#define DMAMUX_SOURCE_FLEXPWM1_WRITE3		39
#define DMAMUX_SOURCE_FLEXPWM3_READ0		40
#define DMAMUX_SOURCE_FLEXPWM3_READ1		41
#define DMAMUX_SOURCE_FLEXPWM3_READ2		42
#define DMAMUX_SOURCE_FLEXPWM3_READ3		43
#define DMAMUX_SOURCE_FLEXPWM3_WRITE0		44
#define DMAMUX_SOURCE_FLEXPWM3_WRITE1		45
#define DMAMUX_SOURCE_FLEXPWM3_WRITE2		46
#define DMAMUX_SOURCE_FLEXPWM3_WRITE3		47
#define DMAMUX_SOURCE_QTIMER1_READ0		48
#define DMAMUX_SOURCE_QTIMER1_READ1		49
#define DMAMUX_SOURCE_QTIMER1_READ2		50
#define DMAMUX_SOURCE_QTIMER1_READ3		51
#define DMAMUX_SOURCE_QTIMER1_WRITE0_CMPLD1	52
#define DMAMUX_SOURCE_QTIMER1_WRITE1_CMPLD1	53
#define DMAMUX_SOURCE_QTIMER1_WRITE2_CMPLD1	54
#define DMAMUX_SOURCE_QTIMER1_WRITE3_CMPLD1	55
#define DMAMUX_SOURCE_QTIMER1_WRITE1_CMPLD2	52
#define DMAMUX_SOURCE_QTIMER1_WRITE0_CMPLD2	53
#define DMAMUX_SOURCE_QTIMER1_WRITE3_CMPLD2	54
#define DMAMUX_SOURCE_QTIMER1_WRITE2_CMPLD2	55
#define DMAMUX_SOURCE_QTIMER3_READ0		56
#define DMAMUX_SOURCE_QTIMER3_READ1		57
#define DMAMUX_SOURCE_QTIMER3_READ2		58
#define DMAMUX_SOURCE_QTIMER3_READ3		59
#define DMAMUX_SOURCE_QTIMER3_WRITE0_CMPLD1	56
#define DMAMUX_SOURCE_QTIMER3_WRITE1_CMPLD1	57
#define DMAMUX_SOURCE_QTIMER3_WRITE2_CMPLD1	58
#define DMAMUX_SOURCE_QTIMER3_WRITE3_CMPLD1	59
#define DMAMUX_SOURCE_QTIMER3_WRITE1_CMPLD2	56
#define DMAMUX_SOURCE_QTIMER3_WRITE0_CMPLD2	57
#define DMAMUX_SOURCE_QTIMER3_WRITE3_CMPLD2	58
#define DMAMUX_SOURCE_QTIMER3_WRITE2_CMPLD2	59
#define DMAMUX_SOURCE_FLEXSPI2_RX		60
#define DMAMUX_SOURCE_FLEXSPI2_TX		61
#define DMAMUX_SOURCE_FLEXIO1_REQUEST2		64
#define DMAMUX_SOURCE_FLEXIO1_REQUEST3		64
#define DMAMUX_SOURCE_FLEXIO2_REQUEST2		65
#define DMAMUX_SOURCE_FLEXIO2_REQUEST3		65
#define DMAMUX_SOURCE_LPUART2_TX		66
#define DMAMUX_SOURCE_LPUART2_RX		67
#define DMAMUX_SOURCE_LPUART4_TX		68
#define DMAMUX_SOURCE_LPUART4_RX		69
#define DMAMUX_SOURCE_LPUART6_TX                70
#define DMAMUX_SOURCE_LPUART6_RX		71
#define DMAMUX_SOURCE_LPUART8_TX		72
#define DMAMUX_SOURCE_LPUART8_RX		73
#define DMAMUX_SOURCE_PXP			75
#define DMAMUX_SOURCE_LCDIF			76
#define DMAMUX_SOURCE_LPSPI2_RX			77
#define DMAMUX_SOURCE_LPSPI2_TX			78
#define DMAMUX_SOURCE_LPSPI4_RX			79
#define DMAMUX_SOURCE_LPSPI4_TX			80
#define DMAMUX_SOURCE_LPI2C2			81
#define DMAMUX_SOURCE_LPI2C4			82
#define DMAMUX_SOURCE_SAI3_RX			83
#define DMAMUX_SOURCE_SAI3_TX			84
#define DMAMUX_SOURCE_SPDIF_RX			85
#define DMAMUX_SOURCE_SPDIF_TX			86
#define DMAMUX_SOURCE_ADC2			88
#define DMAMUX_SOURCE_ACMP2			89
#define DMAMUX_SOURCE_ACMP4			90
#define DMAMUX_SOURCE_ENET1_TIMER0		92
#define DMAMUX_SOURCE_ENET1_TIMER1		93
#define DMAMUX_SOURCE_XBAR1_2			94
#define DMAMUX_SOURCE_XBAR1_3			95
#define DMAMUX_SOURCE_FLEXPWM2_READ0		96
#define DMAMUX_SOURCE_FLEXPWM2_READ1		97
#define DMAMUX_SOURCE_FLEXPWM2_READ2		98
#define DMAMUX_SOURCE_FLEXPWM2_READ3		99
#define DMAMUX_SOURCE_FLEXPWM2_WRITE0		100
#define DMAMUX_SOURCE_FLEXPWM2_WRITE1		101
#define DMAMUX_SOURCE_FLEXPWM2_WRITE2		102
#define DMAMUX_SOURCE_FLEXPWM2_WRITE3		103
#define DMAMUX_SOURCE_FLEXPWM4_READ0		104
#define DMAMUX_SOURCE_FLEXPWM4_READ1		105
#define DMAMUX_SOURCE_FLEXPWM4_READ2		106
#define DMAMUX_SOURCE_FLEXPWM4_READ3		107
#define DMAMUX_SOURCE_FLEXPWM4_WRITE0		108
#define DMAMUX_SOURCE_FLEXPWM4_WRITE1		109
#define DMAMUX_SOURCE_FLEXPWM4_WRITE2		110
#define DMAMUX_SOURCE_FLEXPWM4_WRITE3		111
#define DMAMUX_SOURCE_QTIMER2_READ0		112
#define DMAMUX_SOURCE_QTIMER2_READ1		113
#define DMAMUX_SOURCE_QTIMER2_READ2		114
#define DMAMUX_SOURCE_QTIMER2_READ3		115
#define DMAMUX_SOURCE_QTIMER2_WRITE0_CMPLD1	116
#define DMAMUX_SOURCE_QTIMER2_WRITE1_CMPLD1	117
#define DMAMUX_SOURCE_QTIMER2_WRITE2_CMPLD1	118
#define DMAMUX_SOURCE_QTIMER2_WRITE3_CMPLD1	119
#define DMAMUX_SOURCE_QTIMER2_WRITE1_CMPLD2	116
#define DMAMUX_SOURCE_QTIMER2_WRITE0_CMPLD2	117
#define DMAMUX_SOURCE_QTIMER2_WRITE3_CMPLD2	118
#define DMAMUX_SOURCE_QTIMER2_WRITE2_CMPLD2	119
#define DMAMUX_SOURCE_QTIMER4_READ0		120
#define DMAMUX_SOURCE_QTIMER4_READ1		121
#define DMAMUX_SOURCE_QTIMER4_READ2		122
#define DMAMUX_SOURCE_QTIMER4_READ3		123
#define DMAMUX_SOURCE_QTIMER4_WRITE0_CMPLD1	120
#define DMAMUX_SOURCE_QTIMER4_WRITE1_CMPLD1	121
#define DMAMUX_SOURCE_QTIMER4_WRITE2_CMPLD1	122
#define DMAMUX_SOURCE_QTIMER4_WRITE3_CMPLD1	123
#define DMAMUX_SOURCE_QTIMER4_WRITE1_CMPLD2	120
#define DMAMUX_SOURCE_QTIMER4_WRITE0_CMPLD2	121
#define DMAMUX_SOURCE_QTIMER4_WRITE3_CMPLD2	122
#define DMAMUX_SOURCE_QTIMER4_WRITE2_CMPLD2	123
#define DMAMUX_SOURCE_ENET2_TIMER0		124
#define DMAMUX_SOURCE_ENET2_TIMER1		125

#define IMXRT_CMP1_ADDRESS		0x40094000
#define IMXRT_CMP2_ADDRESS		0x40094008
#define IMXRT_CMP3_ADDRESS		0x40094010
#define IMXRT_CMP4_ADDRESS		0x40094018
#define IMXRT_ADC1_ADDRESS		0x400C4000
#define IMXRT_ADC2_ADDRESS		0x400C8000
#define IMXRT_ADC_ETC_ADDRESS		0x403B0000
#define IMXRT_AIPSTZ1_ADDRESS		0x4007C000
#define IMXRT_AIPSTZ2_ADDRESS		0x4017C000
#define IMXRT_AIPSTZ3_ADDRESS		0x4027C000
#define IMXRT_AIPSTZ4_ADDRESS		0x4037C000
#define IMXRT_AOI1_ADDRESS		0x403B4000
#define IMXRT_AOI2_ADDRESS		0x403B8000
#define IMXRT_BEE_ADDRESS		0x403EC000
#define IMXRT_CCM_ADDRESS		0x400FC000
#define IMXRT_CCM_ANALOG_ADDRESS	0x400D8000
#define IMXRT_CSI_ADDRESS		0x402BC000
#define IMXRT_DCDC_ADDRESS		0x40080000
#define IMXRT_DCP_ADDRESS		0x402FC000
#define IMXRT_DMAMUX_ADDRESS		0x400EC000
#define IMXRT_DMA_ADDRESS		0x400E8000
#define IMXRT_ENC1_ADDRESS		0x403C8000
#define IMXRT_ENC2_ADDRESS		0x403CC000
#define IMXRT_ENC3_ADDRESS		0x403D0000
#define IMXRT_ENC4_ADDRESS		0x403D4000
#define IMXRT_ENET_ADDRESS		0x402D8000
#define IMXRT_ENET2_ADDRESS		0x402D4000
#define IMXRT_EWM_ADDRESS		0x400B4000
#define IMXRT_FLEXCAN1_ADDRESS		0x401D0000
#define IMXRT_FLEXCAN2_ADDRESS		0x401D4000
#define IMXRT_FLEXCAN3_ADDRESS		0x401D8000
#define IMXRT_FLEXIO1_ADDRESS		0x401AC000
#define IMXRT_FLEXIO2_ADDRESS		0x401B0000
#define IMXRT_FLEXIO3_ADDRESS		0x42020000
#define IMXRT_FLEXPWM1_ADDRESS		0x403DC000
#define IMXRT_FLEXPWM2_ADDRESS		0x403E0000
#define IMXRT_FLEXPWM3_ADDRESS		0x403E4000
#define IMXRT_FLEXPWM4_ADDRESS		0x403E8000
#define IMXRT_FLEXRAM_ADDRESS		0x400B0000
#define IMXRT_FLEXSPI_ADDRESS		0x402A8000
#define IMXRT_FLEXSPI2_ADDRESS		0x402A4000
#define IMXRT_GPC_ADDRESS		0x400F4000
#define IMXRT_GPIO1_ADDRESS		0x401B8000
#define IMXRT_GPIO2_ADDRESS		0x401BC000
#define IMXRT_GPIO3_ADDRESS		0x401C0000
#define IMXRT_GPIO4_ADDRESS		0x401C4000
#define IMXRT_GPIO5_ADDRESS		0x400C0000
#define IMXRT_GPIO6_ADDRESS		0x42000000
#define IMXRT_GPIO7_ADDRESS		0x42004000
#define IMXRT_GPIO8_ADDRESS		0x42008000
#define IMXRT_GPIO9_ADDRESS		0x4200C000
#define IMXRT_GPT1_ADDRESS		0x401EC000
#define IMXRT_GPT2_ADDRESS		0x401F0000
#define IMXRT_IOMUXC_GPR_ADDRESS	0x400AC000
#define IMXRT_IOMUXC_SNVS_ADDRESS	0x400A8000
#define IMXRT_IOMUXC_SNVS_GPR_ADDRESS	0x400A4000
#define IMXRT_IOMUXC_ADDRESS		0x401F8000
#define IMXRT_KPP_ADDRESS		0x401FC000
#define IMXRT_LCDIF_ADDRESS		0x402B8000
#define IMXRT_LPI2C1_ADDRESS		0x403F0000
#define IMXRT_LPI2C2_ADDRESS		0x403F4000
#define IMXRT_LPI2C3_ADDRESS		0x403F8000
#define IMXRT_LPI2C4_ADDRESS		0x403FC000
#define IMXRT_LPSPI1_ADDRESS		0x40394000
#define IMXRT_LPSPI2_ADDRESS		0x40398000
#define IMXRT_LPSPI3_ADDRESS		0x4039C000
#define IMXRT_LPSPI4_ADDRESS		0x403A0000
#define IMXRT_LPUART1_ADDRESS		0x40184000
#define IMXRT_LPUART2_ADDRESS		0x40188000
#define IMXRT_LPUART3_ADDRESS		0x4018C000
#define IMXRT_LPUART4_ADDRESS		0x40190000
#define IMXRT_LPUART5_ADDRESS		0x40194000
#define IMXRT_LPUART6_ADDRESS		0x40198000
#define IMXRT_LPUART7_ADDRESS		0x4019C000
#define IMXRT_LPUART8_ADDRESS		0x401A0000
#define IMXRT_OCOTP_ADDRESS		0x401F4000
#define IMXRT_PIT_ADDRESS		0x40084000
#define IMXRT_PMU_ADDRESS		0x400D8000
#define IMXRT_PXP_ADDRESS		0x402B4000
#define IMXRT_TMR1_ADDRESS		0x401DC000
#define IMXRT_TMR2_ADDRESS		0x401E0000
#define IMXRT_TMR3_ADDRESS		0x401E4000
#define IMXRT_TMR4_ADDRESS		0x401E8000
#define IMXRT_I2S1_ADDRESS		0x40384000
#define IMXRT_I2S2_ADDRESS		0x40388000
#define IMXRT_I2S3_ADDRESS		0x4038C000
#define IMXRT_SEMC_ADDRESS		0x402F0000
#define IMXRT_SNVS_ADDRESS		0x400D4000
#define IMXRT_SPDIF_ADDRESS		0x40380000
#define IMXRT_SRC_ADDRESS		0x400F8000
#define IMXRT_TEMPMON_ADDRESS		0x400D8180
#define IMXRT_TRNG_ADDRESS		0x400CC000
#define IMXRT_TSC_ADDRESS		0x400E0000
#define IMXRT_USB1_ADDRESS		0x402E0000
#define IMXRT_USB2_ADDRESS		0x402E0200
#define IMXRT_USBPHY1_ADDRESS		0x400D9000
#define IMXRT_USBPHY2_ADDRESS		0x400DA000
#define IMXRT_USDHC1_ADDRESS		0x402C0000
#define IMXRT_USDHC2_ADDRESS		0x402C4000
#define IMXRT_WDOG1_ADDRESS		0x400B8000
#define IMXRT_WDOG2_ADDRESS		0x400D0000
#define IMXRT_WDOG3_ADDRESS		0x400BC000
#define IMXRT_XBARA1_ADDRESS		0x403BC000
#define IMXRT_XBARB2_ADDRESS		0x403C0000
#define IMXRT_XBARB3_ADDRESS		0x403C4000
#define IMXRT_XTALOSC24M_ADDRESS	0x400D8000





#ifdef __cplusplus
extern "C" void (* volatile _VectorsRam[NVIC_NUM_INTERRUPTS+16])(void);
static inline void attachInterruptVector(IRQ_NUMBER_t irq, void (*function)(void)) __attribute__((always_inline, unused));
static inline void attachInterruptVector(IRQ_NUMBER_t irq, void (*function)(void)) { _VectorsRam[irq + 16] = function; asm volatile("": : :"memory"); }
#else
extern void (* volatile _VectorsRam[NVIC_NUM_INTERRUPTS+16])(void);
static inline void attachInterruptVector(enum IRQ_NUMBER_t irq, void (*function)(void)) __attribute__((always_inline, unused));
static inline void attachInterruptVector(enum IRQ_NUMBER_t irq, void (*function)(void)) { _VectorsRam[irq + 16] = function; asm volatile("": : :"memory"); }
#endif

typedef struct {
	volatile uint32_t offset000;
	volatile uint32_t offset004;
	volatile uint32_t offset008;
	volatile uint32_t offset00C;
	volatile uint32_t offset010;
	volatile uint32_t offset014;
	volatile uint32_t offset018;
	volatile uint32_t offset01C;
	volatile uint32_t offset020;
	volatile uint32_t offset024;
	volatile uint32_t offset028;
	volatile uint32_t offset02C;
	volatile uint32_t offset030;
	volatile uint32_t offset034;
	volatile uint32_t offset038;
	volatile uint32_t offset03C;
	volatile uint32_t offset040;
	volatile uint32_t offset044;
	volatile uint32_t offset048;
	volatile uint32_t offset04C;
	volatile uint32_t offset050;
	volatile uint32_t offset054;
	volatile uint32_t offset058;
	volatile uint32_t offset05C;
	volatile uint32_t offset060;
	volatile uint32_t offset064;
	volatile uint32_t offset068;
	volatile uint32_t offset06C;
	volatile uint32_t offset070;
	volatile uint32_t offset074;
	volatile uint32_t offset078;
	volatile uint32_t offset07C;
	volatile uint32_t offset080;
	volatile uint32_t offset084;
	volatile uint32_t offset088;
	volatile uint32_t offset08C;
	volatile uint32_t offset090;
	volatile uint32_t offset094;
	volatile uint32_t offset098;
	volatile uint32_t offset09C;
	volatile uint32_t offset0A0;
	volatile uint32_t offset0A4;
	volatile uint32_t offset0A8;
	volatile uint32_t offset0AC;
	volatile uint32_t offset0B0;
	volatile uint32_t offset0B4;
	volatile uint32_t offset0B8;
	volatile uint32_t offset0BC;
	volatile uint32_t offset0C0;
	volatile uint32_t offset0C4;
	volatile uint32_t offset0C8;
	volatile uint32_t offset0CC;
	volatile uint32_t offset0D0;
	volatile uint32_t offset0D4;
	volatile uint32_t offset0D8;
	volatile uint32_t offset0DC;
	volatile uint32_t offset0E0;
	volatile uint32_t offset0E4;
	volatile uint32_t offset0E8;
	volatile uint32_t offset0EC;
	volatile uint32_t offset0F0;
	volatile uint32_t offset0F4;
	volatile uint32_t offset0F8;
	volatile uint32_t offset0FC;
	volatile uint32_t offset100;
	volatile uint32_t offset104;
	volatile uint32_t offset108;
	volatile uint32_t offset10C;
	volatile uint32_t offset110;
	volatile uint32_t offset114;
	volatile uint32_t offset118;
	volatile uint32_t offset11C;
	volatile uint32_t offset120;
	volatile uint32_t offset124;
	volatile uint32_t offset128;
	volatile uint32_t offset12C;
	volatile uint32_t offset130;
	volatile uint32_t offset134;
	volatile uint32_t offset138;
	volatile uint32_t offset13C;
	volatile uint32_t offset140;
	volatile uint32_t offset144;
	volatile uint32_t offset148;
	volatile uint32_t offset14C;
	volatile uint32_t offset150;
	volatile uint32_t offset154;
	volatile uint32_t offset158;
	volatile uint32_t offset15C;
	volatile uint32_t offset160;
	volatile uint32_t offset164;
	volatile uint32_t offset168;
	volatile uint32_t offset16C;
	volatile uint32_t offset170;
	volatile uint32_t offset174;
	volatile uint32_t offset178;
	volatile uint32_t offset17C;
	volatile uint32_t offset180;
	volatile uint32_t offset184;
	volatile uint32_t offset188;
	volatile uint32_t offset18C;
	volatile uint32_t offset190;
	volatile uint32_t offset194;
	volatile uint32_t offset198;
	volatile uint32_t offset19C;
	volatile uint32_t offset1A0;
	volatile uint32_t offset1A4;
	volatile uint32_t offset1A8;
	volatile uint32_t offset1AC;
	volatile uint32_t offset1B0;
	volatile uint32_t offset1B4;
	volatile uint32_t offset1B8;
	volatile uint32_t offset1BC;
	volatile uint32_t offset1C0;
	volatile uint32_t offset1C4;
	volatile uint32_t offset1C8;
	volatile uint32_t offset1CC;
	volatile uint32_t offset1D0;
	volatile uint32_t offset1D4;
	volatile uint32_t offset1D8;
	volatile uint32_t offset1DC;
	volatile uint32_t offset1E0;
	volatile uint32_t offset1E4;
	volatile uint32_t offset1E8;
	volatile uint32_t offset1EC;
	volatile uint32_t offset1F0;
	volatile uint32_t offset1F4;
	volatile uint32_t offset1F8;
	volatile uint32_t offset1FC;
	volatile uint32_t offset200;
	volatile uint32_t offset204;
	volatile uint32_t offset208;
	volatile uint32_t offset20C;
	volatile uint32_t offset210;
	volatile uint32_t offset214;
	volatile uint32_t offset218;
	volatile uint32_t offset21C;
	volatile uint32_t offset220;
	volatile uint32_t offset224;
	volatile uint32_t offset228;
	volatile uint32_t offset22C;
	volatile uint32_t offset230;
	volatile uint32_t offset234;
	volatile uint32_t offset238;
	volatile uint32_t offset23C;
	volatile uint32_t offset240;
	volatile uint32_t offset244;
	volatile uint32_t offset248;
	volatile uint32_t offset24C;
	volatile uint32_t offset250;
	volatile uint32_t offset254;
	volatile uint32_t offset258;
	volatile uint32_t offset25C;
	volatile uint32_t offset260;
	volatile uint32_t offset264;
	volatile uint32_t offset268;
	volatile uint32_t offset26C;
	volatile uint32_t offset270;
	volatile uint32_t offset274;
	volatile uint32_t offset278;
	volatile uint32_t offset27C;
	volatile uint32_t offset280;
	volatile uint32_t offset284;
	volatile uint32_t offset288;
	volatile uint32_t offset28C;
	volatile uint32_t offset290;
	volatile uint32_t offset294;
	volatile uint32_t offset298;
	volatile uint32_t offset29C;
	volatile uint32_t offset2A0;
	volatile uint32_t offset2A4;
	volatile uint32_t offset2A8;
	volatile uint32_t offset2AC;
	volatile uint32_t offset2B0;
	volatile uint32_t offset2B4;
	volatile uint32_t offset2B8;
	volatile uint32_t offset2BC;
	volatile uint32_t offset2C0;
	volatile uint32_t offset2C4;
	volatile uint32_t offset2C8;
	volatile uint32_t offset2CC;
	volatile uint32_t offset2D0;
	volatile uint32_t offset2D4;
	volatile uint32_t offset2D8;
	volatile uint32_t offset2DC;
	volatile uint32_t offset2E0;
	volatile uint32_t offset2E4;
	volatile uint32_t offset2E8;
	volatile uint32_t offset2EC;
	volatile uint32_t offset2F0;
	volatile uint32_t offset2F4;
	volatile uint32_t offset2F8;
	volatile uint32_t offset2FC;
	volatile uint32_t offset300;
	volatile uint32_t offset304;
	volatile uint32_t offset308;
	volatile uint32_t offset30C;
	volatile uint32_t offset310;
	volatile uint32_t offset314;
	volatile uint32_t offset318;
	volatile uint32_t offset31C;
	volatile uint32_t offset320;
	volatile uint32_t offset324;
	volatile uint32_t offset328;
	volatile uint32_t offset32C;
	volatile uint32_t offset330;
	volatile uint32_t offset334;
	volatile uint32_t offset338;
	volatile uint32_t offset33C;
	volatile uint32_t offset340;
	volatile uint32_t offset344;
	volatile uint32_t offset348;
	volatile uint32_t offset34C;
	volatile uint32_t offset350;
	volatile uint32_t offset354;
	volatile uint32_t offset358;
	volatile uint32_t offset35C;
	volatile uint32_t offset360;
	volatile uint32_t offset364;
	volatile uint32_t offset368;
	volatile uint32_t offset36C;
	volatile uint32_t offset370;
	volatile uint32_t offset374;
	volatile uint32_t offset378;
	volatile uint32_t offset37C;
	volatile uint32_t offset380;
	volatile uint32_t offset384;
	volatile uint32_t offset388;
	volatile uint32_t offset38C;
	volatile uint32_t offset390;
	volatile uint32_t offset394;
	volatile uint32_t offset398;
	volatile uint32_t offset39C;
	volatile uint32_t offset3A0;
	volatile uint32_t offset3A4;
	volatile uint32_t offset3A8;
	volatile uint32_t offset3AC;
	volatile uint32_t offset3B0;
	volatile uint32_t offset3B4;
	volatile uint32_t offset3B8;
	volatile uint32_t offset3BC;
	volatile uint32_t offset3C0;
	volatile uint32_t offset3C4;
	volatile uint32_t offset3C8;
	volatile uint32_t offset3CC;
	volatile uint32_t offset3D0;
	volatile uint32_t offset3D4;
	volatile uint32_t offset3D8;
	volatile uint32_t offset3DC;
	volatile uint32_t offset3E0;
	volatile uint32_t offset3E4;
	volatile uint32_t offset3E8;
	volatile uint32_t offset3EC;
	volatile uint32_t offset3F0;
	volatile uint32_t offset3F4;
	volatile uint32_t offset3F8;
	volatile uint32_t offset3FC;
} IMXRT_REGISTER32_t;

typedef struct {
	volatile uint16_t offset000;
	volatile uint16_t offset002;
	volatile uint16_t offset004;
	volatile uint16_t offset006;
	volatile uint16_t offset008;
	volatile uint16_t offset00A;
	volatile uint16_t offset00C;
	volatile uint16_t offset00E;
	volatile uint16_t offset010;
	volatile uint16_t offset012;
	volatile uint16_t offset014;
	volatile uint16_t offset016;
	volatile uint16_t offset018;
	volatile uint16_t offset01A;
	volatile uint16_t offset01C;
	volatile uint16_t offset01E;
	volatile uint16_t offset020;
	volatile uint16_t offset022;
	volatile uint16_t offset024;
	volatile uint16_t offset026;
	volatile uint16_t offset028;
	volatile uint16_t offset02A;
	volatile uint16_t offset02C;
	volatile uint16_t offset02E;
	volatile uint16_t offset030;
	volatile uint16_t offset032;
	volatile uint16_t offset034;
	volatile uint16_t offset036;
	volatile uint16_t offset038;
	volatile uint16_t offset03A;
	volatile uint16_t offset03C;
	volatile uint16_t offset03E;
	volatile uint16_t offset040;
	volatile uint16_t offset042;
	volatile uint16_t offset044;
	volatile uint16_t offset046;
	volatile uint16_t offset048;
	volatile uint16_t offset04A;
	volatile uint16_t offset04C;
	volatile uint16_t offset04E;
	volatile uint16_t offset050;
	volatile uint16_t offset052;
	volatile uint16_t offset054;
	volatile uint16_t offset056;
	volatile uint16_t offset058;
	volatile uint16_t offset05A;
	volatile uint16_t offset05C;
	volatile uint16_t offset05E;
	volatile uint16_t offset060;
	volatile uint16_t offset062;
	volatile uint16_t offset064;
	volatile uint16_t offset066;
	volatile uint16_t offset068;
	volatile uint16_t offset06A;
	volatile uint16_t offset06C;
	volatile uint16_t offset06E;
	volatile uint16_t offset070;
	volatile uint16_t offset072;
	volatile uint16_t offset074;
	volatile uint16_t offset076;
	volatile uint16_t offset078;
	volatile uint16_t offset07A;
	volatile uint16_t offset07C;
	volatile uint16_t offset07E;
	volatile uint16_t offset080;
	volatile uint16_t offset082;
	volatile uint16_t offset084;
	volatile uint16_t offset086;
	volatile uint16_t offset088;
	volatile uint16_t offset08A;
	volatile uint16_t offset08C;
	volatile uint16_t offset08E;
	volatile uint16_t offset090;
	volatile uint16_t offset092;
	volatile uint16_t offset094;
	volatile uint16_t offset096;
	volatile uint16_t offset098;
	volatile uint16_t offset09A;
	volatile uint16_t offset09C;
	volatile uint16_t offset09E;
	volatile uint16_t offset0A0;
	volatile uint16_t offset0A2;
	volatile uint16_t offset0A4;
	volatile uint16_t offset0A6;
	volatile uint16_t offset0A8;
	volatile uint16_t offset0AA;
	volatile uint16_t offset0AC;
	volatile uint16_t offset0AE;
	volatile uint16_t offset0B0;
	volatile uint16_t offset0B2;
	volatile uint16_t offset0B4;
	volatile uint16_t offset0B6;
	volatile uint16_t offset0B8;
	volatile uint16_t offset0BA;
	volatile uint16_t offset0BC;
	volatile uint16_t offset0BE;
	volatile uint16_t offset0C0;
	volatile uint16_t offset0C2;
	volatile uint16_t offset0C4;
	volatile uint16_t offset0C6;
	volatile uint16_t offset0C8;
	volatile uint16_t offset0CA;
	volatile uint16_t offset0CC;
	volatile uint16_t offset0CE;
	volatile uint16_t offset0D0;
	volatile uint16_t offset0D2;
	volatile uint16_t offset0D4;
	volatile uint16_t offset0D6;
	volatile uint16_t offset0D8;
	volatile uint16_t offset0DA;
	volatile uint16_t offset0DC;
	volatile uint16_t offset0DE;
	volatile uint16_t offset0E0;
	volatile uint16_t offset0E2;
	volatile uint16_t offset0E4;
	volatile uint16_t offset0E6;
	volatile uint16_t offset0E8;
	volatile uint16_t offset0EA;
	volatile uint16_t offset0EC;
	volatile uint16_t offset0EE;
	volatile uint16_t offset0F0;
	volatile uint16_t offset0F2;
	volatile uint16_t offset0F4;
	volatile uint16_t offset0F6;
	volatile uint16_t offset0F8;
	volatile uint16_t offset0FA;
	volatile uint16_t offset0FC;
	volatile uint16_t offset0FE;
	volatile uint16_t offset100;
	volatile uint16_t offset102;
	volatile uint16_t offset104;
	volatile uint16_t offset106;
	volatile uint16_t offset108;
	volatile uint16_t offset10A;
	volatile uint16_t offset10C;
	volatile uint16_t offset10E;
	volatile uint16_t offset110;
	volatile uint16_t offset112;
	volatile uint16_t offset114;
	volatile uint16_t offset116;
	volatile uint16_t offset118;
	volatile uint16_t offset11A;
	volatile uint16_t offset11C;
	volatile uint16_t offset11E;
	volatile uint16_t offset120;
	volatile uint16_t offset122;
	volatile uint16_t offset124;
	volatile uint16_t offset126;
	volatile uint16_t offset128;
	volatile uint16_t offset12A;
	volatile uint16_t offset12C;
	volatile uint16_t offset12E;
	volatile uint16_t offset130;
	volatile uint16_t offset132;
	volatile uint16_t offset134;
	volatile uint16_t offset136;
	volatile uint16_t offset138;
	volatile uint16_t offset13A;
	volatile uint16_t offset13C;
	volatile uint16_t offset13E;
	volatile uint16_t offset140;
	volatile uint16_t offset142;
	volatile uint16_t offset144;
	volatile uint16_t offset146;
	volatile uint16_t offset148;
	volatile uint16_t offset14A;
	volatile uint16_t offset14C;
	volatile uint16_t offset14E;
	volatile uint16_t offset150;
	volatile uint16_t offset152;
	volatile uint16_t offset154;
	volatile uint16_t offset156;
	volatile uint16_t offset158;
	volatile uint16_t offset15A;
	volatile uint16_t offset15C;
	volatile uint16_t offset15E;
	volatile uint16_t offset160;
	volatile uint16_t offset162;
	volatile uint16_t offset164;
	volatile uint16_t offset166;
	volatile uint16_t offset168;
	volatile uint16_t offset16A;
	volatile uint16_t offset16C;
	volatile uint16_t offset16E;
	volatile uint16_t offset170;
	volatile uint16_t offset172;
	volatile uint16_t offset174;
	volatile uint16_t offset176;
	volatile uint16_t offset178;
	volatile uint16_t offset17A;
	volatile uint16_t offset17C;
	volatile uint16_t offset17E;
	volatile uint16_t offset180;
	volatile uint16_t offset182;
	volatile uint16_t offset184;
	volatile uint16_t offset186;
	volatile uint16_t offset188;
	volatile uint16_t offset18A;
	volatile uint16_t offset18C;
	volatile uint16_t offset18E;
	volatile uint16_t offset190;
	volatile uint16_t offset192;
	volatile uint16_t offset194;
	volatile uint16_t offset196;
	volatile uint16_t offset198;
	volatile uint16_t offset19A;
	volatile uint16_t offset19C;
	volatile uint16_t offset19E;
	volatile uint16_t offset1A0;
	volatile uint16_t offset1A2;
	volatile uint16_t offset1A4;
	volatile uint16_t offset1A6;
	volatile uint16_t offset1A8;
	volatile uint16_t offset1AA;
	volatile uint16_t offset1AC;
	volatile uint16_t offset1AE;
	volatile uint16_t offset1B0;
	volatile uint16_t offset1B2;
	volatile uint16_t offset1B4;
	volatile uint16_t offset1B6;
	volatile uint16_t offset1B8;
	volatile uint16_t offset1BA;
	volatile uint16_t offset1BC;
	volatile uint16_t offset1BE;
	volatile uint16_t offset1C0;
	volatile uint16_t offset1C2;
	volatile uint16_t offset1C4;
	volatile uint16_t offset1C6;
	volatile uint16_t offset1C8;
	volatile uint16_t offset1CA;
	volatile uint16_t offset1CC;
	volatile uint16_t offset1CE;
	volatile uint16_t offset1D0;
	volatile uint16_t offset1D2;
	volatile uint16_t offset1D4;
	volatile uint16_t offset1D6;
	volatile uint16_t offset1D8;
	volatile uint16_t offset1DA;
	volatile uint16_t offset1DC;
	volatile uint16_t offset1DE;
	volatile uint16_t offset1E0;
	volatile uint16_t offset1E2;
	volatile uint16_t offset1E4;
	volatile uint16_t offset1E6;
	volatile uint16_t offset1E8;
	volatile uint16_t offset1EA;
	volatile uint16_t offset1EC;
	volatile uint16_t offset1EE;
	volatile uint16_t offset1F0;
	volatile uint16_t offset1F2;
	volatile uint16_t offset1F4;
	volatile uint16_t offset1F6;
	volatile uint16_t offset1F8;
	volatile uint16_t offset1FA;
	volatile uint16_t offset1FC;
	volatile uint16_t offset1FE;
} IMXRT_REGISTER16_t;

typedef struct {
	volatile uint8_t offset00;
	volatile uint8_t offset01;
	volatile uint8_t offset02;
	volatile uint8_t offset03;
	volatile uint8_t offset04;
	volatile uint8_t offset05;
	volatile uint8_t offset06;
	volatile uint8_t offset07;
	volatile uint8_t offset08;
	volatile uint8_t offset09;
	volatile uint8_t offset0A;
	volatile uint8_t offset0B;
	volatile uint8_t offset0C;
	volatile uint8_t offset0D;
	volatile uint8_t offset0E;
	volatile uint8_t offset0F;
} IMXRT_REGISTER8_t;

// 65.3: page 3302
#define IMXRT_CMP1		(*(IMXRT_REGISTER8_t *)IMXRT_CMP1_ADDRESS)
#define CMP1_CR0			(IMXRT_CMP1.offset00)
#define CMP1_CR1			(IMXRT_CMP1.offset01)
#define CMP1_FPR			(IMXRT_CMP1.offset02)
#define CMP1_SCR			(IMXRT_CMP1.offset03)
#define CMP1_DACCR			(IMXRT_CMP1.offset04)
#define CMP1_MUXCR			(IMXRT_CMP1.offset05)
#define IMXRT_CMP2		(*(IMXRT_REGISTER8_t *)IMXRT_CMP2_ADDRESS)
#define CMP2_CR0			(IMXRT_CMP2.offset00)
#define CMP2_CR1			(IMXRT_CMP2.offset01)
#define CMP2_FPR			(IMXRT_CMP2.offset02)
#define CMP2_SCR			(IMXRT_CMP2.offset03)
#define CMP2_DACCR			(IMXRT_CMP2.offset04)
#define CMP2_MUXCR			(IMXRT_CMP2.offset05)
#define IMXRT_CMP3		(*(IMXRT_REGISTER8_t *)IMXRT_CMP3_ADDRESS)
#define CMP3_CR0			(IMXRT_CMP3.offset00)
#define CMP3_CR1			(IMXRT_CMP3.offset01)
#define CMP3_FPR			(IMXRT_CMP3.offset02)
#define CMP3_SCR			(IMXRT_CMP3.offset03)
#define CMP3_DACCR			(IMXRT_CMP3.offset04)
#define CMP3_MUXCR			(IMXRT_CMP3.offset05)
#define IMXRT_CMP4		(*(IMXRT_REGISTER8_t *)IMXRT_CMP4_ADDRESS)
#define CMP4_CR0			(IMXRT_CMP4.offset00)
#define CMP4_CR1			(IMXRT_CMP4.offset01)
#define CMP4_FPR			(IMXRT_CMP4.offset02)
#define CMP4_SCR			(IMXRT_CMP4.offset03)
#define CMP4_DACCR			(IMXRT_CMP4.offset04)
#define CMP4_MUXCR			(IMXRT_CMP4.offset05)

// 65.3 page 3302
typedef struct {
        volatile uint32_t HC0;
        volatile uint32_t HC1;
        volatile uint32_t HC2;
        volatile uint32_t HC3;
        volatile uint32_t HC4;
        volatile uint32_t HC5;
        volatile uint32_t HC6;
        volatile uint32_t HC7;
        volatile uint32_t HS; 
        volatile uint32_t R0; 
        volatile uint32_t R1; 
        volatile uint32_t R2; 
        volatile uint32_t R3; 
        volatile uint32_t R4; 
        volatile uint32_t R5; 
        volatile uint32_t R6; 
        volatile uint32_t R7; 
        volatile uint32_t CFG;
        volatile uint32_t GC; 
        volatile uint32_t GS; 
        volatile uint32_t CV; 
        volatile uint32_t OFS;
        volatile uint32_t CAL;
} IMXRT_ADCS_t;


#define IMXRT_ADC1                  (*(IMXRT_ADCS_t *)IMXRT_ADC1_ADDRESS)
#define IMXRT_ADC1S                 (*(IMXRT_ADCS_t *)IMXRT_ADC1_ADDRESS)
#define ADC1_HC0			(IMXRT_ADC1.HC0)
#define ADC1_HC1			(IMXRT_ADC1.HC1)
#define ADC1_HC2			(IMXRT_ADC1.HC2)
#define ADC1_HC3			(IMXRT_ADC1.HC3)
#define ADC1_HC4			(IMXRT_ADC1.HC4)
#define ADC1_HC5			(IMXRT_ADC1.HC5)
#define ADC1_HC6			(IMXRT_ADC1.HC6)
#define ADC1_HC7			(IMXRT_ADC1.HC7)
#define ADC1_HS				(IMXRT_ADC1.HS)
#define ADC1_R0				(IMXRT_ADC1.R0)
#define ADC1_R1				(IMXRT_ADC1.R1)
#define ADC1_R2				(IMXRT_ADC1.R2)
#define ADC1_R3				(IMXRT_ADC1.R3)
#define ADC1_R4				(IMXRT_ADC1.R4)
#define ADC1_R5				(IMXRT_ADC1.R5)
#define ADC1_R6				(IMXRT_ADC1.R6)
#define ADC1_R7				(IMXRT_ADC1.R7)
#define ADC1_CFG			(IMXRT_ADC1.CFG)
#define ADC1_GC				(IMXRT_ADC1.GC)
#define ADC1_GS				(IMXRT_ADC1.GS)
#define ADC1_CV				(IMXRT_ADC1.CV)
#define ADC1_OFS			(IMXRT_ADC1.OFS)
#define ADC1_CAL			(IMXRT_ADC1.CAL)
#define IMXRT_ADC2                 (*(IMXRT_ADCS_t *)IMXRT_ADC2_ADDRESS)
#define IMXRT_ADC2S                (*(IMXRT_ADCS_t *)IMXRT_ADC2_ADDRESS)
#define ADC2_HC0			(IMXRT_ADC2.HC0)
#define ADC2_HC1			(IMXRT_ADC2.HC1)
#define ADC2_HC2			(IMXRT_ADC2.HC2)
#define ADC2_HC3			(IMXRT_ADC2.HC3)
#define ADC2_HC4			(IMXRT_ADC2.HC4)
#define ADC2_HC5			(IMXRT_ADC2.HC5)
#define ADC2_HC6			(IMXRT_ADC2.HC6)
#define ADC2_HC7			(IMXRT_ADC2.HC7)
#define ADC2_HS				(IMXRT_ADC2.HS)
#define ADC2_R0				(IMXRT_ADC2.R0)
#define ADC2_R1				(IMXRT_ADC2.R1)
#define ADC2_R2				(IMXRT_ADC2.R2)
#define ADC2_R3				(IMXRT_ADC2.R3)
#define ADC2_R4				(IMXRT_ADC2.R4)
#define ADC2_R5				(IMXRT_ADC2.R5)
#define ADC2_R6				(IMXRT_ADC2.R6)
#define ADC2_R7				(IMXRT_ADC2.R7)
#define ADC2_CFG			(IMXRT_ADC2.CFG)
#define ADC2_GC				(IMXRT_ADC2.GC)
#define ADC2_GS				(IMXRT_ADC2.GS)
#define ADC2_CV				(IMXRT_ADC2.CV)
#define ADC2_OFS			(IMXRT_ADC2.OFS)
#define ADC2_CAL			(IMXRT_ADC2.CAL)
#define ADC_HC_AIEN				((uint32_t)(1<<7))
#define ADC_HC_ADCH(n)				((uint32_t)(((n) & 0x1F) << 0))
#define ADC_HS_COCO0				((uint32_t)(1<<0))
#define ADC_CFG_OVWREN				((uint32_t)(1<<16))
#define ADC_CFG_AVGS(n)				((uint32_t)(((n) & 0x03) << 14))
#define ADC_CFG_ADTRG				((uint32_t)(1<<13))
#define ADC_CFG_REFSEL(n)			((uint32_t)(((n) & 0x03) << 11))
#define ADC_CFG_ADHSC				((uint32_t)(1<<10))
#define ADC_CFG_ADSTS(n)			((uint32_t)(((n) & 0x03) << 8))
#define ADC_CFG_ADLPC				((uint32_t)(1<<7))
#define ADC_CFG_ADIV(n)				((uint32_t)(((n) & 0x03) << 5))
#define ADC_CFG_ADLSMP				((uint32_t)(1<<4))
#define ADC_CFG_MODE(n)				((uint32_t)(((n) & 0x03) << 2))
#define ADC_CFG_ADICLK(n)			((uint32_t)(((n) & 0x03) << 0))
#define ADC_GC_CAL				((uint32_t)(1<<7))
#define ADC_GC_ADCO				((uint32_t)(1<<6))
#define ADC_GC_AVGE				((uint32_t)(1<<5))
#define ADC_GC_ACFE				((uint32_t)(1<<4))
#define ADC_GC_ACFGT				((uint32_t)(1<<3))
#define ADC_GC_ACREN				((uint32_t)(1<<2))
#define ADC_GC_DMAEN				((uint32_t)(1<<1))
#define ADC_GC_ADACKEN				((uint32_t)(1<<0))
#define ADC_GS_AWKST				((uint32_t)(1<<2))
#define ADC_GS_CALF				((uint32_t)(1<<1))
#define ADC_GS_ADACT				((uint32_t)(1<<0))
#define ADC_CV_CV2(n)				((uint32_t)(((n) & 0xFFF) << 16))
#define ADC_CV_CV1(n)				((uint32_t)(((n) & 0xFFF) << 0))
#define ADC_OFS_SIGN				((uint32_t)(1<<12))
#define ADC_OFS_OFS(n)				((uint32_t)(((n) & 0xFFF) << 0))
#define ADC_CAL_CAL_CODE(n)			((uint32_t)(((n) & 0x0F) << 0))

// 66.5.1 Page 3504
typedef struct {
  volatile uint32_t CTRL;              // offset 0
  volatile uint32_t DONE0_1_IRQ;       // offset004
  volatile uint32_t DONE2_ERR_IRQ;     // offset008
  volatile uint32_t DMA_CTRL;          // offset00C
  struct {
    volatile uint32_t CTRL;            //offset010
    volatile uint32_t COUNTER;         //offset014
    volatile uint32_t CHAIN_1_0;
    volatile uint32_t CHAIN_3_2;
    volatile uint32_t CHAIN_5_4;
    volatile uint32_t CHAIN_7_6;
    volatile uint32_t RESULT_1_0;
    volatile uint32_t RESULT_3_2;
    volatile uint32_t RESULT_5_4;
    volatile uint32_t RESULT_7_6;
  } TRIG[7];
} IMXRT_ADC_ETC_t;

#define IMXRT_ADC_ETC		(*(IMXRT_ADC_ETC_t *)IMXRT_ADC_ETC_ADDRESS)
#define ADC_ETC_CTRL			(IMXRT_ADC_ETC.CTRL)
#define ADC_ETC_DONE0_1_IRQ		(IMXRT_ADC_ETC.DONE0_1_IRQ)
#define ADC_ETC_DONE2_ERR_IRQ		(IMXRT_ADC_ETC.DONE2_ERR_IRQ)
#define ADC_ETC_DMA_CTRL		(IMXRT_ADC_ETC.DMA_CTRL)
#define ADC_ETC_TRIG0_CTRL		(IMXRT_ADC_ETC.TRIG[0].CTRL)
#define ADC_ETC_TRIG0_COUNTER		(IMXRT_ADC_ETC.TRIG[0].COUNTER)
#define ADC_ETC_TRIG0_CHAIN_1_0		(IMXRT_ADC_ETC.TRIG[0].CHAIN_1_0)
#define ADC_ETC_TRIG0_CHAIN_3_2		(IMXRT_ADC_ETC.TRIG[0].CHAIN_3_2)
#define ADC_ETC_TRIG0_CHAIN_5_4		(IMXRT_ADC_ETC.TRIG[0].CHAIN_5_4)
#define ADC_ETC_TRIG0_CHAIN_7_6		(IMXRT_ADC_ETC.TRIG[0].CHAIN_7_6)
#define ADC_ETC_TRIG0_RESULT_1_0	(IMXRT_ADC_ETC.TRIG[0].RESULT_1_0)
#define ADC_ETC_TRIG0_RESULT_3_2	(IMXRT_ADC_ETC.TRIG[0].RESULT_3_2)
#define ADC_ETC_TRIG0_RESULT_5_4	(IMXRT_ADC_ETC.TRIG[0].RESULT_5_4)
#define ADC_ETC_TRIG0_RESULT_7_6	(IMXRT_ADC_ETC.TRIG[0].RESULT_7_6)

#define ADC_ETC_TRIG1_CTRL              (IMXRT_ADC_ETC.TRIG[1].CTRL)
#define ADC_ETC_TRIG1_COUNTER           (IMXRT_ADC_ETC.TRIG[1].COUNTER)
#define ADC_ETC_TRIG1_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[1].CHAIN_1_0)
#define ADC_ETC_TRIG1_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[1].CHAIN_3_2)
#define ADC_ETC_TRIG1_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[1].CHAIN_5_4)
#define ADC_ETC_TRIG1_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[1].CHAIN_7_6)
#define ADC_ETC_TRIG1_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[1].RESULT_1_0)
#define ADC_ETC_TRIG1_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[1].RESULT_3_2)
#define ADC_ETC_TRIG1_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[1].RESULT_5_4)
#define ADC_ETC_TRIG1_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[1].RESULT_7_6)
#define ADC_ETC_TRIG2_CTRL              (IMXRT_ADC_ETC.TRIG[2].CTRL)
#define ADC_ETC_TRIG2_COUNTER           (IMXRT_ADC_ETC.TRIG[2].COUNTER)
#define ADC_ETC_TRIG2_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[2].CHAIN_1_0)
#define ADC_ETC_TRIG2_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[2].CHAIN_3_2)
#define ADC_ETC_TRIG2_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[2].CHAIN_5_4)
#define ADC_ETC_TRIG2_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[2].CHAIN_7_6)
#define ADC_ETC_TRIG2_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[2].RESULT_1_0)
#define ADC_ETC_TRIG2_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[2].RESULT_3_2)
#define ADC_ETC_TRIG2_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[2].RESULT_5_4)
#define ADC_ETC_TRIG2_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[2].RESULT_7_6)
#define ADC_ETC_TRIG3_CTRL              (IMXRT_ADC_ETC.TRIG[3].CTRL)
#define ADC_ETC_TRIG3_COUNTER           (IMXRT_ADC_ETC.TRIG[3].COUNTER)
#define ADC_ETC_TRIG3_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[3].CHAIN_1_0)
#define ADC_ETC_TRIG3_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[3].CHAIN_3_2)
#define ADC_ETC_TRIG3_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[3].CHAIN_5_4)
#define ADC_ETC_TRIG3_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[3].CHAIN_7_6)
#define ADC_ETC_TRIG3_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[3].RESULT_1_0)
#define ADC_ETC_TRIG3_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[3].RESULT_3_2)
#define ADC_ETC_TRIG3_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[3].RESULT_5_4)
#define ADC_ETC_TRIG3_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[3].RESULT_7_6)
#define ADC_ETC_TRIG4_CTRL              (IMXRT_ADC_ETC.TRIG[4].CTRL)
#define ADC_ETC_TRIG4_COUNTER           (IMXRT_ADC_ETC.TRIG[4].COUNTER)
#define ADC_ETC_TRIG4_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[4].CHAIN_1_0)
#define ADC_ETC_TRIG4_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[4].CHAIN_3_2)
#define ADC_ETC_TRIG4_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[4].CHAIN_5_4)
#define ADC_ETC_TRIG4_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[4].CHAIN_7_6)
#define ADC_ETC_TRIG4_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[4].RESULT_1_0)
#define ADC_ETC_TRIG4_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[4].RESULT_3_2)
#define ADC_ETC_TRIG4_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[4].RESULT_5_4)
#define ADC_ETC_TRIG4_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[4].RESULT_7_6)
#define ADC_ETC_TRIG5_CTRL              (IMXRT_ADC_ETC.TRIG[5].CTRL)
#define ADC_ETC_TRIG5_COUNTER           (IMXRT_ADC_ETC.TRIG[5].COUNTER)
#define ADC_ETC_TRIG5_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[5].CHAIN_1_0)
#define ADC_ETC_TRIG5_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[5].CHAIN_3_2)
#define ADC_ETC_TRIG5_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[5].CHAIN_5_4)
#define ADC_ETC_TRIG5_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[5].CHAIN_7_6)
#define ADC_ETC_TRIG5_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[5].RESULT_1_0)
#define ADC_ETC_TRIG5_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[5].RESULT_3_2)
#define ADC_ETC_TRIG5_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[5].RESULT_5_4)
#define ADC_ETC_TRIG5_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[5].RESULT_7_6)
#define ADC_ETC_TRIG6_CTRL              (IMXRT_ADC_ETC.TRIG[6].CTRL)
#define ADC_ETC_TRIG6_COUNTER           (IMXRT_ADC_ETC.TRIG[6].COUNTER)
#define ADC_ETC_TRIG6_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[6].CHAIN_1_0)
#define ADC_ETC_TRIG6_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[6].CHAIN_3_2)
#define ADC_ETC_TRIG6_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[6].CHAIN_5_4)
#define ADC_ETC_TRIG6_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[6].CHAIN_7_6)
#define ADC_ETC_TRIG6_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[6].RESULT_1_0)
#define ADC_ETC_TRIG6_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[6].RESULT_3_2)
#define ADC_ETC_TRIG6_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[6].RESULT_5_4)
#define ADC_ETC_TRIG6_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[6].RESULT_7_6)
#define ADC_ETC_TRIG7_CTRL              (IMXRT_ADC_ETC.TRIG[7].CTRL)
#define ADC_ETC_TRIG7_COUNTER           (IMXRT_ADC_ETC.TRIG[7].COUNTER)
#define ADC_ETC_TRIG7_CHAIN_1_0         (IMXRT_ADC_ETC.TRIG[7].CHAIN_1_0)
#define ADC_ETC_TRIG7_CHAIN_3_2         (IMXRT_ADC_ETC.TRIG[7].CHAIN_3_2)
#define ADC_ETC_TRIG7_CHAIN_5_4         (IMXRT_ADC_ETC.TRIG[7].CHAIN_5_4)
#define ADC_ETC_TRIG7_CHAIN_7_6         (IMXRT_ADC_ETC.TRIG[7].CHAIN_7_6)
#define ADC_ETC_TRIG7_RESULT_1_0        (IMXRT_ADC_ETC.TRIG[7].RESULT_1_0)
#define ADC_ETC_TRIG7_RESULT_3_2        (IMXRT_ADC_ETC.TRIG[7].RESULT_3_2)
#define ADC_ETC_TRIG7_RESULT_5_4        (IMXRT_ADC_ETC.TRIG[7].RESULT_5_4)
#define ADC_ETC_TRIG7_RESULT_7_6        (IMXRT_ADC_ETC.TRIG[7].RESULT_7_6)

#define ADC_ETC_CTRL_SOFTRST            ((uint32_t)(1<<31))
#define ADC_ETC_CTRL_TSC_BYPASS         ((uint32_t)(1<<30))
#define ADC_ETC_CTRL_DMA_MODE_SEL       ((uint32_t)(1<<29))
#define ADC_ETC_CTRL_PRE_DIVIDER(n)     ((uint32_t)(((n) & 0xff) << 16))
#define ADC_ETC_CTRL_EXT1_TRIG_PRIORITY(n)  ((uint32_t)(((n) & 0x07) << 13))
#define ADC_ETC_CTRL_EXT1_TRIG_ENABLE       ((uint32_t)(1<<12))
#define ADC_ETC_CTRL_EXT0_TRIG_PRIORITY(n)  ((uint32_t)(((n) & 0x07) << 9))
#define ADC_ETC_CTRL_EXT0_TRIG_ENABLE       ((uint32_t)(1<<8))
#define ADC_ETC_CTRL_TRIG_ENABLE(n)     ((uint32_t)(((n) & 0xff) << 0))

#define ADC_ETC_DONE0_1_IRQ_TRIG_DONE1(n)  ((uint32_t)(1<<(16 + ((n) &0x7))))
#define ADC_ETC_DONE0_1_IRQ_TRIG_DONE0(n)  ((uint32_t)(1<<((n) &0x7)))

#define ADC_ETC_DONE2_ERR_IRQ_TRIG_ERR(n)  ((uint32_t)(1<<(16 + ((n) &0x7))))
#define ADC_ETC_DONE2_ERR_IRQ_TRIG_DONE2(n)  ((uint32_t)(1<<((n) &0x7)))

#define ADC_ETC_DMA_CTRL_TRIQ_REQ(n)    ((uint32_t)(1<<(16 + ((n) &0x7))))
#define ADC_ETC_DMA_CTRL_TRIQ_ENABLE(n) ((uint32_t)(1<<((n) &0x7)))

// For each TRIG elements in array
#define ADC_ETC_TRIG_CTRL_SYNC_MODE     ((uint32_t)(1<<16))
#define ADC_ETC_TRIG_CTRL_TRIG_PRIORITY(n)  ((uint32_t)(((n) & 0x07) << 12))
#define ADC_ETC_TRIG_CTRL_TRIG_CHAIN(n) ((uint32_t)(((n) & 0x07) << 8))
#define ADC_ETC_TRIG_CTRL_TRIG_MODE     ((uint32_t)(1<<4))
#define ADC_ETC_TRIG_CTRL_SW_TRIG       ((uint32_t)(1<<0))

#define ADC_ETC_TRIG_COUNTER_SAMPLE_INTERVAL(n) ((uint32_t)(((n) & 0xff) << 16))
#define ADC_ETC_TRIG_COUNTER_INIT_DELAY(n)    ((uint32_t)(((n) & 0xff) << 0))

#define ADC_ETC_TRIG_CHAIN_IE1(n)       ((uint32_t)(((n) & 0x03) << 29))
#define ADC_ETC_TRIG_CHAIN_B2B1         ((uint32_t)(1<<28))
#define ADC_ETC_TRIG_CHAIN_HWTS1(n)     ((uint32_t)(((n) & 0xff) << 20))
#define ADC_ETC_TRIG_CHAIN_CSEL1(n)     ((uint32_t)(((n) & 0x0f) << 16))
#define ADC_ETC_TRIG_CHAIN_IE0(n)       ((uint32_t)(((n) & 0x03) << 13))
#define ADC_ETC_TRIG_CHAIN_B2B0         ((uint32_t)(1<<12))
#define ADC_ETC_TRIG_CHAIN_HWTS0(n)     ((uint32_t)(((n) & 0xff) << 4))
#define ADC_ETC_TRIG_CHAIN_CSEL0(n)     ((uint32_t)(((n) & 0x0f) << 0))

#define ADC_ETC_TRIG_RESULT_DATA1(n)    ((uint32_t)(((n) & 0xfff) << 16))
#define ADC_ETC_TRIG_RESULT_DATA0(n)    ((uint32_t)(((n) & 0xfff) << 0))

// 32.8: page 1778
#define IMXRT_AIPSTZ1		(*(IMXRT_REGISTER32_t *)IMXRT_AIPSTZ1_ADDRESS)
#define AIPSTZ1_MPR			(IMXRT_AIPSTZ1.offset000)
#define AIPSTZ1_OPACR			(IMXRT_AIPSTZ1.offset040)
#define AIPSTZ1_OPACR1			(IMXRT_AIPSTZ1.offset044)
#define AIPSTZ1_OPACR2			(IMXRT_AIPSTZ1.offset048)
#define AIPSTZ1_OPACR3			(IMXRT_AIPSTZ1.offset04C)
#define AIPSTZ1_OPACR4			(IMXRT_AIPSTZ1.offset050)
#define IMXRT_AIPSTZ2		(*(IMXRT_REGISTER32_t *)IMXRT_AIPSTZ2_ADDRESS)
#define AIPSTZ2_MPR			(IMXRT_AIPSTZ2.offset000)
#define AIPSTZ2_OPACR			(IMXRT_AIPSTZ2.offset040)
#define AIPSTZ2_OPACR1			(IMXRT_AIPSTZ2.offset044)
#define AIPSTZ2_OPACR2			(IMXRT_AIPSTZ2.offset048)
#define AIPSTZ2_OPACR3			(IMXRT_AIPSTZ2.offset04C)
#define AIPSTZ2_OPACR4			(IMXRT_AIPSTZ2.offset050)
#define IMXRT_AIPSTZ3		(*(IMXRT_REGISTER32_t *)IMXRT_AIPSTZ3_ADDRESS)
#define AIPSTZ3_MPR			(IMXRT_AIPSTZ3.offset000)
#define AIPSTZ3_OPACR			(IMXRT_AIPSTZ3.offset040)
#define AIPSTZ3_OPACR1			(IMXRT_AIPSTZ3.offset044)
#define AIPSTZ3_OPACR2			(IMXRT_AIPSTZ3.offset048)
#define AIPSTZ3_OPACR3			(IMXRT_AIPSTZ3.offset04C)
#define AIPSTZ3_OPACR4			(IMXRT_AIPSTZ3.offset050)
#define IMXRT_AIPSTZ4		(*(IMXRT_REGISTER32_t *)IMXRT_AIPSTZ4_ADDRESS)
#define AIPSTZ4_MPR			(IMXRT_AIPSTZ4.offset000)
#define AIPSTZ4_OPACR			(IMXRT_AIPSTZ4.offset040)
#define AIPSTZ4_OPACR1			(IMXRT_AIPSTZ4.offset044)
#define AIPSTZ4_OPACR2			(IMXRT_AIPSTZ4.offset048)
#define AIPSTZ4_OPACR3			(IMXRT_AIPSTZ4.offset04C)
#define AIPSTZ4_OPACR4			(IMXRT_AIPSTZ4.offset050)

// 63.4: page 3287
#define IMXRT_AOI1		(*(IMXRT_REGISTER16_t *)IMXRT_AOI1_ADDRESS)
#define AOI1_BFCRT010			(IMXRT_AOI1.offset000)
#define AOI1_BFCRT230			(IMXRT_AOI1.offset002)
#define AOI1_BFCRT011			(IMXRT_AOI1.offset004)
#define AOI1_BFCRT231			(IMXRT_AOI1.offset006)
#define AOI1_BFCRT012			(IMXRT_AOI1.offset008)
#define AOI1_BFCRT232			(IMXRT_AOI1.offset00A)
#define AOI1_BFCRT013			(IMXRT_AOI1.offset00C)
#define AOI1_BFCRT233			(IMXRT_AOI1.offset00E)
#define IMXRT_AOI2		(*(IMXRT_REGISTER16_t *)IMXRT_AOI2_ADDRESS)
#define AOI2_BFCRT010			(IMXRT_AOI2.offset000)
#define AOI2_BFCRT230			(IMXRT_AOI2.offset002)
#define AOI2_BFCRT011			(IMXRT_AOI2.offset004)
#define AOI2_BFCRT231			(IMXRT_AOI2.offset006)
#define AOI2_BFCRT012			(IMXRT_AOI2.offset008)
#define AOI2_BFCRT232			(IMXRT_AOI2.offset00A)
#define AOI2_BFCRT013			(IMXRT_AOI2.offset00C)
#define AOI2_BFCRT233			(IMXRT_AOI2.offset00E)

// 14.7: page 1045
#define IMXRT_CCM		(*(IMXRT_REGISTER32_t *)IMXRT_CCM_ADDRESS)
#define CCM_CCR				(IMXRT_CCM.offset000)
#define CCM_CSR				(IMXRT_CCM.offset008)
#define CCM_CCSR			(IMXRT_CCM.offset00C)
#define CCM_CACRR			(IMXRT_CCM.offset010)
#define CCM_CBCDR			(IMXRT_CCM.offset014)
#define CCM_CBCMR			(IMXRT_CCM.offset018)
#define CCM_CSCMR1			(IMXRT_CCM.offset01C)
#define CCM_CSCMR2			(IMXRT_CCM.offset020)
#define CCM_CSCDR1			(IMXRT_CCM.offset024)
#define CCM_CS1CDR			(IMXRT_CCM.offset028)
#define CCM_CS2CDR			(IMXRT_CCM.offset02C)
#define CCM_CDCDR			(IMXRT_CCM.offset030)
#define CCM_CSCDR2			(IMXRT_CCM.offset038)
#define CCM_CSCDR3			(IMXRT_CCM.offset03C)
#define CCM_CDHIPR			(IMXRT_CCM.offset048)
#define CCM_CLPCR			(IMXRT_CCM.offset054)
#define CCM_CISR			(IMXRT_CCM.offset058)
#define CCM_CIMR			(IMXRT_CCM.offset05C)
#define CCM_CCOSR			(IMXRT_CCM.offset060)
#define CCM_CGPR			(IMXRT_CCM.offset064)
#define CCM_CCGR0			(IMXRT_CCM.offset068)
#define CCM_CCGR1			(IMXRT_CCM.offset06C)
#define CCM_CCGR2			(IMXRT_CCM.offset070)
#define CCM_CCGR3			(IMXRT_CCM.offset074)
#define CCM_CCGR4			(IMXRT_CCM.offset078)
#define CCM_CCGR5			(IMXRT_CCM.offset07C)
#define CCM_CCGR6			(IMXRT_CCM.offset080)
#define CCM_CCGR7			(IMXRT_CCM.offset084)
#define CCM_CMEOR			(IMXRT_CCM.offset088)
#define CCM_CCR_RBC_EN				((uint32_t)(1<<27))
#define CCM_CCR_REG_BYPASS_COUNT(n)		((uint32_t)(((n) & 0x3F) << 21))
#define CCM_CCR_COSC_EN				((uint32_t)(1<<12))
#define CCM_CCR_OSCNT(n)			((uint32_t)(((n) & 0xFF) << 0))
#define CCM_CSR_COSC_READY			((uint32_t)(1<<5))
#define CCM_CSR_CAMP2_READY			((uint32_t)(1<<3))
#define CCM_CSR_REF_EN_B			((uint32_t)(1<<0))
#define CCM_CCSR_PLL3_SW_CLK_SEL		((uint32_t)(1<<0))
#define CCM_CACRR_ARM_PODF(n)			((uint32_t)(((n) & 0x07) << 0))
#define CCM_CACRR_ARM_PODF_MASK			((uint32_t)(0x07 << 0))
#define CCM_CBCDR_PERIPH_CLK2_PODF(n)		((uint32_t)(((n) & 0x07) << 27))
#define CCM_CBCDR_PERIPH_CLK2_PODF_MASK		((uint32_t)(0x07 << 27))
#define CCM_CBCDR_PERIPH_CLK_SEL		((uint32_t)(1<<25))
#define CCM_CBCDR_SEMC_PODF(n)			((uint32_t)(((n) & 0x07) << 16))
#define CCM_CBCDR_AHB_PODF(n)			((uint32_t)(((n) & 0x07) << 10))
#define CCM_CBCDR_AHB_PODF_MASK			((uint32_t)(0x07 << 10))
#define CCM_CBCDR_IPG_PODF(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CBCDR_IPG_PODF_MASK			((uint32_t)(0x03 << 8))
#define CCM_CBCDR_SEMC_ALT_CLK_SEL		((uint32_t)(1<<7))
#define CCM_CBCDR_SEMC_CLK_SEL			((uint32_t)(1<<6))
#define CCM_CBCMR_FLEXSPI2_PODF(n)		((uint32_t)(((n) & 0x07) << 29))
#define CCM_CBCMR_LPSPI_PODF(n)			((uint32_t)(((n) & 0x07) << 26))
#define CCM_CBCMR_LCDIF_PODF(n)			((uint32_t)(((n) & 0x07) << 23))
#define CCM_CBCMR_PRE_PERIPH_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 18))
#define CCM_CBCMR_TRACE_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 14))
#define CCM_CBCMR_PERIPH_CLK2_SEL(n)		((uint32_t)(((n) & 0x03) << 12))
#define CCM_CBCMR_FLEXSPI2_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 8))
#define CCM_CBCMR_LPSPI_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 4))
#define CCM_CBCMR_FLEXSPI2_PODF_MASK		((uint32_t)(0x07 << 29))
#define CCM_CBCMR_LPSPI_PODF_MASK		((uint32_t)(0x07 << 26))
#define CCM_CBCMR_LCDIF_PODF_MASK		((uint32_t)(0x07 << 23))
#define CCM_CBCMR_PRE_PERIPH_CLK_SEL_MASK	((uint32_t)(0x03 << 18))
#define CCM_CBCMR_TRACE_CLK_SEL_MASK		((uint32_t)(0x03 << 14))
#define CCM_CBCMR_PERIPH_CLK2_SEL_MASK		((uint32_t)(0x03 << 12))
#define CCM_CBCMR_FLEXSPI2_CLK_SEL_MASK		((uint32_t)(0x03 << 8))
#define CCM_CBCMR_LPSPI_CLK_SEL_MASK		((uint32_t)(0x03 << 4))
#define CCM_CSCMR1_FLEXSPI_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 29))
#define CCM_CSCMR1_FLEXSPI_PODF(n)		((uint32_t)(((n) & 0x07) << 23))
#define CCM_CSCMR1_USDHC2_CLK_SEL		((uint32_t)(1<<17))
#define CCM_CSCMR1_USDHC1_CLK_SEL		((uint32_t)(1<<16))
#define CCM_CSCMR1_SAI3_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 14))
#define CCM_CSCMR1_SAI2_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 12))
#define CCM_CSCMR1_SAI1_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 10))
#define CCM_CSCMR1_PERCLK_CLK_SEL		((uint32_t)(1<<6))
#define CCM_CSCMR1_PERCLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 0))
#define CCM_CSCMR2_FLEXIO2_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 19))
#define CCM_CSCMR2_CAN_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 8))
#define CCM_CSCMR2_CAN_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 2))
#define CCM_CSCDR1_TRACE_PODF(n)		((uint32_t)(((n) & 0x07) << 25))
#define CCM_CSCDR1_USDHC2_PODF(n)		((uint32_t)(((n) & 0x07) << 16))
#define CCM_CSCDR1_USDHC1_PODF(n)		((uint32_t)(((n) & 0x07) << 11))
#define CCM_CSCDR1_UART_CLK_SEL			((uint32_t)(1<<6))
#define CCM_CSCDR1_UART_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 0))
#define CCM_CS1CDR_FLEXIO2_CLK_PODF(n)		((uint32_t)(((n) & 0x07) << 25))
#define CCM_CS1CDR_SAI3_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 22))
#define CCM_CS1CDR_SAI3_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 16))
#define CCM_CS1CDR_FLEXIO2_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 9))
#define CCM_CS1CDR_SAI1_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 6))
#define CCM_CS1CDR_SAI1_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 0))
#define CCM_CS2CDR_SAI2_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 6))
#define CCM_CS2CDR_SAI2_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 0))
#define CCM_CDCDR_SPDIF0_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 25))
#define CCM_CDCDR_SPDIF0_CLK_PODF(n)		((uint32_t)(((n) & 0x07) << 22))
#define CCM_CDCDR_SPDIF0_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 20))
#define CCM_CDCDR_FLEXIO1_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 12))
#define CCM_CDCDR_FLEXIO1_CLK_PODF(n)		((uint32_t)(((n) & 0x07) << 9))
#define CCM_CDCDR_FLEXIO1_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 7))
#define CCM_CSCDR2_LPI2C_CLK_PODF(n)		((uint32_t)(((n) & 0x1F) << 19))
#define CCM_CSCDR2_LPI2C_CLK_SEL		((uint32_t)(1<<18))
#define CCM_CSCDR2_LCDIF_PRE_CLK_SEL(n)		((uint32_t)(((n) & 0x07) << 15))
#define CCM_CSCDR2_LCDIF_PRED(n)		((uint32_t)(((n) & 0x07) << 12))
#define CCM_CSCDR2_LCDIF_CLK_SEL(n)		((uint32_t)(((n) & 0x07) << 9))
#define CCM_CSCDR3_CSI_PODF(n)			((uint32_t)(((n) & 0x07) << 11))
#define CCM_CSCDR3_CSI_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 9))
#define CCM_CDHIPR_ARM_PODF_BUSY		((uint32_t)(1<<16))
#define CCM_CDHIPR_PERIPH_CLK_SEL_BUSY		((uint32_t)(1<<5))
#define CCM_CDHIPR_PERIPH2_CLK_SEL_BUSY		((uint32_t)(1<<3))
#define CCM_CDHIPR_AHB_PODF_BUSY		((uint32_t)(1<<1))
#define CCM_CDHIPR_SEMC_PODF_BUSY		((uint32_t)(1<<0))
#define CCM_CLPCR_MASK_L2CC_IDLE		((uint32_t)(1<<27))
#define CCM_CLPCR_MASK_SCU_IDLE			((uint32_t)(1<<26))
#define CCM_CLPCR_MASK_CORE0_WFI		((uint32_t)(1<<22))
#define CCM_CLPCR_BYPASS_LPM_HS0		((uint32_t)(1<<21))
#define CCM_CLPCR_BYPASS_LPM_HS1		((uint32_t)(1<<19))
#define CCM_CLPCR_COSC_PWRDOWN			((uint32_t)(1<<11))
#define CCM_CLPCR_STBY_COUNT(n)			((uint32_t)(((n) & 0x03) << 9))
#define CCM_CLPCR_VSTBY				((uint32_t)(1<<8))
#define CCM_CLPCR_DIS_REF_OSC			((uint32_t)(1<<7))
#define CCM_CLPCR_SBYOS				((uint32_t)(1<<6))
#define CCM_CLPCR_ARM_CLK_DIS_ON_LPM		((uint32_t)(1<<5))
#define CCM_CLPCR_LPM(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CISR_ARM_PODF_LOADED		((uint32_t)(1<<26))
#define CCM_CISR_PERIPH_CLK_SEL_LOADED		((uint32_t)(1<<22))
#define CCM_CISR_AHB_PODF_LOADED		((uint32_t)(1<<20))
#define CCM_CISR_PERIPH2_CLK_SEL_LOADED		((uint32_t)(1<<19))
#define CCM_CISR_SEMC_PODF_LOADED		((uint32_t)(1<<17))
#define CCM_CISR_COSC_READY			((uint32_t)(1<<6))
#define CCM_CISR_LRF_PLL			((uint32_t)(1<<0))
#define CCM_CIMR_ARM_PODF_LOADED		((uint32_t)(1<<26))
#define CCM_CIMR_MASK_PERIPH_CLK_SEL_LOADED	((uint32_t)(1<<22))
#define CCM_CIMR_MASK_AHB_PODF_LOADED		((uint32_t)(1<<20))
#define CCM_CIMR_MASK_PERIPH2_CLK_SEL_LOADED	((uint32_t)(1<<19))
#define CCM_CIMR_MASK_SEMC_PODF_LOADED		((uint32_t)(1<<17))
#define CCM_CIMR_MASK_COSC_READY		((uint32_t)(1<<6))
#define CCM_CIMR_MASK_LRF_PLL			((uint32_t)(1<<0))
#define CCM_CCOSR_CLKO2_EN			((uint32_t)(1<<24))
#define CCM_CCOSR_CLKO2_DIV(n)			((uint32_t)(((n) & 0x07) << 21))
#define CCM_CCOSR_CLKO2_SEL(n)			((uint32_t)(((n) & 0x1F) << 16))
#define CCM_CCOSR_CLK_OUT_SEL			((uint32_t)(1<<8))
#define CCM_CCOSR_CLKO1_EN			((uint32_t)(1<<7))
#define CCM_CCOSR_CLKO1_DIV(n)			((uint32_t)(((n) & 0x07) << 4))
#define CCM_CCOSR_CLKO1_SEL(n)			((uint32_t)(((n) & 0x0F) << 0))
#define CCM_CGPR_INT_MEM_CLK_LPM		((uint32_t)(1<<17))
#define CCM_CGPR_FPL				((uint32_t)(1<<16))
#define CCM_CGPR_SYS_MEM_DS_CTRL(n)		((uint32_t)(((n) & 0x03) << 14))
#define CCM_CGPR_EFUSE_PROG_SUPPLY_GATE		((uint32_t)(1<<4))
#define CCM_CGPR_PMIC_DELAY_SCALER		((uint32_t)(1<<0))
#define CCM_CCGR_OFF				0
#define CCM_CCGR_ON_RUNONLY			1
#define CCM_CCGR_ON				3
#define CCM_CCGR0_GPIO2(n)			((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR0_LPUART2(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR0_GPT2_SERIAL(n)		((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR0_GPT2_BUS(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR0_TRACE(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR0_CAN2_SERIAL(n)		((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR0_CAN2(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR0_CAN1_SERIAL(n)		((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR0_CAN1(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR0_LPUART3(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR0_DCP(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR0_MQS_HMCLK(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR0_AIPS_TZ2(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR0_AIPS_TZ1(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CCGR1_CSU(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR1_GPIO1(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR1_LPUART4(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR1_GPT1_SERIAL(n)		((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR1_GPT1_BUS(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR1_GPT(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR1_ADC1(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR1_AOI2(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR1_PIT(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR1_ENET(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR1_ADC2(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR1_LPSPI4(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR1_LPSPI3(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR1_LPSPI2(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR1_LPSPI1(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CCGR2_PXP(n)			((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR2_LCD(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR2_GPIO3(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR2_XBAR2(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR2_XBAR1(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR2_IPMUX3(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR2_IPMUX2(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR2_IPMUX1(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR2_XBAR3(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR2_IIM(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR2_LPI2C3(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR2_LPI2C2(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR2_LPI2C1(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR2_IOMUXC_SNVS(n)		((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR2_CSI(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR3_IOMUXC_SNVS_GPR(n)		((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR3_OCRAM(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR3_ACMP4(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR3_ACMP3(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR3_ACMP2(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR3_ACMP1(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR3_FLEXRAM(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR3_WDOG1(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR3_EWM(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR3_GPIO4(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR3_LCDIF_PIX(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR3_AOI1(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR3_LPUART6(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR3_SEMC(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR3_LPUART5(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR3_FLEXIO2(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CCGR4_ENC4(n)			((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR4_ENC3(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR4_ENC2(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR4_ENC1(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR4_PWM4(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR4_PWM3(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR4_PWM2(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR4_PWM1(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR4_SIM_EMS(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR4_SIM_M(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR4_TSC(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR4_SIM_M7(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR4_BEE(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR4_IOMUXC_GPR(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR4_IOMUXC(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR5_SNVS_LP(n)			((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR5_SNVS_HP(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR5_LPUART7(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR5_LPUART1(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR5_SAI3(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR5_SAI2(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR5_SAI1(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR5_SIM_MAIN(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR5_SPDIF(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR5_AIPS_TZ4(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR5_WDOG2(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR5_KPP(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR5_DMA(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR5_WDOG3(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR5_FLEXIO1(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR5_ROM(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CCGR6_QTIMER3(n)			((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR6_QTIMER2(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR6_QTIMER1(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR6_LPI2C4_SERIAL(n)		((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR6_ANADIG(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR6_SIM_PER(n)			((uint32_t)(((n) & 0x03) << 20)) /* IMXRT1052 */
#define CCM_CCGR6_AXBS_P(n)			((uint32_t)(((n) & 0x03) << 20)) /* IMXRT1062 */
#define CCM_CCGR6_AIPS_TZ3(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR6_QTIMER4(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR6_LPUART8(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR6_TRNG(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR6_FLEXSPI(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR6_IPMUX4(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR6_DCDC(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR6_USDHC2(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR6_USDHC1(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR6_USBOH3(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CCGR7_FLEXIO3(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR7_APIS_LITE(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR7_CAN3_SERIAL(n)		((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR7_CAN3(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR7_AXBS_L(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR7_FLEXSPI2(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR7_ENET2(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CMEOR_MOD_EN_OV_CAN1_CPI		((uint32_t)(1<<30))
#define CCM_CMEOR_MOD_EN_OV_CAN2_CPI		((uint32_t)(1<<28))
#define CCM_CMEOR_MOD_EN_OV_TRNG		((uint32_t)(1<<9))
#define CCM_CMEOR_MOD_EN_USDHC			((uint32_t)(1<<7))
#define CCM_CMEOR_MOD_EN_OV_PIT			((uint32_t)(1<<6))
#define CCM_CMEOR_MOD_EN_OV_GPT			((uint32_t)(1<<5))

#define CCM_CSCMR1_SAI1_CLK_SEL_MASK		(CCM_CSCMR1_SAI1_CLK_SEL(0x03))
#define CCM_CS1CDR_SAI1_CLK_PRED_MASK		(CCM_CS1CDR_SAI1_CLK_PRED(0x07))
#define CCM_CS1CDR_SAI1_CLK_PODF_MASK		(CCM_CS1CDR_SAI1_CLK_PODF(0x3f))
#define CCM_CSCMR1_SAI2_CLK_SEL_MASK		(CCM_CSCMR1_SAI2_CLK_SEL(0x03))
#define CCM_CS2CDR_SAI2_CLK_PRED_MASK		(CCM_CS2CDR_SAI2_CLK_PRED(0x07))
#define CCM_CS2CDR_SAI2_CLK_PODF_MASK		(CCM_CS2CDR_SAI2_CLK_PODF(0x3f))
#define CCM_CSCMR1_SAI3_CLK_SEL_MASK		(CCM_CSCMR1_SAI3_CLK_SEL(0x03))
#define CCM_CS1CDR_SAI3_CLK_PRED_MASK		(CCM_CS1CDR_SAI3_CLK_PRED(0x07))
#define CCM_CS1CDR_SAI3_CLK_PODF_MASK		(CCM_CS1CDR_SAI3_CLK_PODF(0x3f))
#define CCM_CDCDR_SPDIF0_CLK_SEL_MASK		(CCM_CDCDR_SPDIF0_CLK_SEL(0x03))
#define CCM_CDCDR_SPDIF0_CLK_PRED_MASK		(CCM_CDCDR_SPDIF0_CLK_PRED(0x07))
#define CCM_CDCDR_SPDIF0_CLK_PODF_MASK		(CCM_CDCDR_SPDIF0_CLK_PODF(0x07))

// 14.8: page 1096
#define IMXRT_CCM_ANALOG	(*(IMXRT_REGISTER32_t *)IMXRT_CCM_ANALOG_ADDRESS)
#define CCM_ANALOG_PLL_ARM		(IMXRT_CCM_ANALOG.offset000)
#define CCM_ANALOG_PLL_ARM_SET		(IMXRT_CCM_ANALOG.offset004)
#define CCM_ANALOG_PLL_ARM_CLR		(IMXRT_CCM_ANALOG.offset008)
#define CCM_ANALOG_PLL_ARM_TOG		(IMXRT_CCM_ANALOG.offset00C)
#define CCM_ANALOG_PLL_USB1		(IMXRT_CCM_ANALOG.offset010)
#define CCM_ANALOG_PLL_USB1_SET		(IMXRT_CCM_ANALOG.offset014)
#define CCM_ANALOG_PLL_USB1_CLR		(IMXRT_CCM_ANALOG.offset018)
#define CCM_ANALOG_PLL_USB1_TOG		(IMXRT_CCM_ANALOG.offset01C)
#define CCM_ANALOG_PLL_USB2		(IMXRT_CCM_ANALOG.offset020)
#define CCM_ANALOG_PLL_USB2_SET		(IMXRT_CCM_ANALOG.offset024)
#define CCM_ANALOG_PLL_USB2_CLR		(IMXRT_CCM_ANALOG.offset028)
#define CCM_ANALOG_PLL_USB2_TOG		(IMXRT_CCM_ANALOG.offset02C)
#define CCM_ANALOG_PLL_SYS		(IMXRT_CCM_ANALOG.offset030)
#define CCM_ANALOG_PLL_SYS_SET		(IMXRT_CCM_ANALOG.offset034)
#define CCM_ANALOG_PLL_SYS_CLR		(IMXRT_CCM_ANALOG.offset038)
#define CCM_ANALOG_PLL_SYS_TOG		(IMXRT_CCM_ANALOG.offset03C)
#define CCM_ANALOG_PLL_SYS_SS		(IMXRT_CCM_ANALOG.offset040)
#define CCM_ANALOG_PLL_SYS_NUM		(IMXRT_CCM_ANALOG.offset050)
#define CCM_ANALOG_PLL_SYS_DENOM	(IMXRT_CCM_ANALOG.offset060)
#define CCM_ANALOG_PLL_AUDIO		(IMXRT_CCM_ANALOG.offset070)
#define CCM_ANALOG_PLL_AUDIO_SET	(IMXRT_CCM_ANALOG.offset074)
#define CCM_ANALOG_PLL_AUDIO_CLR	(IMXRT_CCM_ANALOG.offset078)
#define CCM_ANALOG_PLL_AUDIO_TOG	(IMXRT_CCM_ANALOG.offset07C)
#define CCM_ANALOG_PLL_AUDIO_NUM	(IMXRT_CCM_ANALOG.offset080)
#define CCM_ANALOG_PLL_AUDIO_DENOM	(IMXRT_CCM_ANALOG.offset090)
#define CCM_ANALOG_PLL_VIDEO		(IMXRT_CCM_ANALOG.offset0A0)
#define CCM_ANALOG_PLL_VIDEO_SET	(IMXRT_CCM_ANALOG.offset0A4)
#define CCM_ANALOG_PLL_VIDEO_CLR	(IMXRT_CCM_ANALOG.offset0A8)
#define CCM_ANALOG_PLL_VIDEO_TOG	(IMXRT_CCM_ANALOG.offset0AC)
#define CCM_ANALOG_PLL_VIDEO_NUM	(IMXRT_CCM_ANALOG.offset0B0)
#define CCM_ANALOG_PLL_VIDEO_DENOM	(IMXRT_CCM_ANALOG.offset0C0)
#define CCM_ANALOG_PLL_ENET		(IMXRT_CCM_ANALOG.offset0E0)
#define CCM_ANALOG_PLL_ENET_SET		(IMXRT_CCM_ANALOG.offset0E4)
#define CCM_ANALOG_PLL_ENET_CLR		(IMXRT_CCM_ANALOG.offset0E8)
#define CCM_ANALOG_PLL_ENET_TOG		(IMXRT_CCM_ANALOG.offset0EC)
#define CCM_ANALOG_PFD_480		(IMXRT_CCM_ANALOG.offset0F0)
#define CCM_ANALOG_PFD_480_SET		(IMXRT_CCM_ANALOG.offset0F4)
#define CCM_ANALOG_PFD_480_CLR		(IMXRT_CCM_ANALOG.offset0F8)
#define CCM_ANALOG_PFD_480_TOG		(IMXRT_CCM_ANALOG.offset0FC)
#define CCM_ANALOG_PFD_528		(IMXRT_CCM_ANALOG.offset100)
#define CCM_ANALOG_PFD_528_SET		(IMXRT_CCM_ANALOG.offset104)
#define CCM_ANALOG_PFD_528_CLR		(IMXRT_CCM_ANALOG.offset108)
#define CCM_ANALOG_PFD_528_TOG		(IMXRT_CCM_ANALOG.offset10C)
#define CCM_ANALOG_MISC0		(IMXRT_CCM_ANALOG.offset150)
#define CCM_ANALOG_MISC0_SET		(IMXRT_CCM_ANALOG.offset154)
#define CCM_ANALOG_MISC0_CLR		(IMXRT_CCM_ANALOG.offset158)
#define CCM_ANALOG_MISC0_TOG		(IMXRT_CCM_ANALOG.offset15C)
#define CCM_ANALOG_MISC1		(IMXRT_CCM_ANALOG.offset160)
#define CCM_ANALOG_MISC1_SET		(IMXRT_CCM_ANALOG.offset164)
#define CCM_ANALOG_MISC1_CLR		(IMXRT_CCM_ANALOG.offset168)
#define CCM_ANALOG_MISC1_TOG		(IMXRT_CCM_ANALOG.offset16C)
#define CCM_ANALOG_MISC2		(IMXRT_CCM_ANALOG.offset170)
#define CCM_ANALOG_MISC2_SET		(IMXRT_CCM_ANALOG.offset174)
#define CCM_ANALOG_MISC2_CLR		(IMXRT_CCM_ANALOG.offset178)
#define CCM_ANALOG_MISC2_TOG		(IMXRT_CCM_ANALOG.offset17C)
#define CCM_ANALOG_PLL_ARM_LOCK			((uint32_t)(1<<31))
#define CCM_ANALOG_PLL_ARM_BYPASS		((uint32_t)(1<<16))
#define CCM_ANALOG_PLL_ARM_ENABLE		((uint32_t)(1<<13))
#define CCM_ANALOG_PLL_ARM_POWERDOWN		((uint32_t)(1<<12))
#define CCM_ANALOG_PLL_ARM_DIV_SELECT(n)	((uint32_t)(((n) & 0x7F) << 0))
#define CCM_ANALOG_PLL_ARM_DIV_SELECT_MASK	((uint32_t)(0x7F << 0))
#define CCM_ANALOG_PLL_USB1_LOCK		((uint32_t)(1<<31))
#define CCM_ANALOG_PLL_USB1_BYPASS		((uint32_t)(1<<16))
#define CCM_ANALOG_PLL_USB1_ENABLE		((uint32_t)(1<<13))
#define CCM_ANALOG_PLL_USB1_POWER		((uint32_t)(1<<12))
#define CCM_ANALOG_PLL_USB1_EN_USB_CLKS		((uint32_t)(1<<6))
#define CCM_ANALOG_PLL_USB1_DIV_SELECT		((uint32_t)(1<<1))
#define CCM_ANALOG_PLL_USB2_LOCK		((uint32_t)(1<<31))
#define CCM_ANALOG_PLL_USB2_BYPASS		((uint32_t)(1<<16))
#define CCM_ANALOG_PLL_USB2_ENABLE		((uint32_t)(1<<13))
#define CCM_ANALOG_PLL_USB2_POWER		((uint32_t)(1<<12))
#define CCM_ANALOG_PLL_USB2_EN_USB_CLKS		((uint32_t)(1<<6))
#define CCM_ANALOG_PLL_USB2_DIV_SELECT		((uint32_t)(1<<1))
#define CCM_ANALOG_PLL_SYS_LOCK			((uint32_t)(1<<31))
#define CCM_ANALOG_PLL_SYS_BYPASS		((uint32_t)(1<<16))
#define CCM_ANALOG_PLL_SYS_ENABLE		((uint32_t)(1<<13))
#define CCM_ANALOG_PLL_SYS_POWERDOWN		((uint32_t)(1<<12))
#define CCM_ANALOG_PLL_SYS_DIV_SELECT		((uint32_t)(1<<1))
#define CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT(n)	((uint32_t)(((n) & 0x03) <<19)) 
#define CCM_ANALOG_PLL_AUDIO_BYPASS		((uint32_t)(1<<16)) 
#define CCM_ANALOG_PLL_AUDIO_BYPASS_CLK_SRC(n)	((uint32_t)(((n) & 0x03) <<14)) 
#define CCM_ANALOG_PLL_AUDIO_ENABLE		((uint32_t)(1<<13)) 
#define CCM_ANALOG_PLL_AUDIO_POWERDOWN		((uint32_t)(1<<12)) 
#define CCM_ANALOG_PLL_AUDIO_DIV_SELECT(n)	((uint32_t)((n) & ((1<<6)-1)))
#define CCM_ANALOG_PLL_VIDEO_LOCK		((uint32_t)(1<<31))
#define CCM_ANALOG_PLL_VIDEO_POST_DIV_SELECT(n)	((uint32_t)(((n) & 0x03) << 19))
#define CCM_ANALOG_PLL_VIDEO_BYPASS		((uint32_t)(1<<16))
#define CCM_ANALOG_PLL_VIDEO_BYPASS_CLK_SRC(n)	((uint32_t)(((n) & 0x03) << 14))
#define CCM_ANALOG_PLL_VIDEO_ENABLE		((uint32_t)(1<<13))
#define CCM_ANALOG_PLL_VIDEO_POWERDOWN		((uint32_t)(1<<12))
#define CCM_ANALOG_PLL_VIDEO_DIV_SELECT(n)	((uint32_t)(((n) & 0x7F) << 0))
#define CCM_ANALOG_PLL_ENET_LOCK		((uint32_t)(1<<31))
#define CCM_ANALOG_PLL_ENET_ENET_25M_REF_EN	((uint32_t)(1<<21))
#define CCM_ANALOG_PLL_ENET_ENET2_REF_EN	((uint32_t)(1<<20))
#define CCM_ANALOG_PLL_ENET_BYPASS		((uint32_t)(1<<16))
#define CCM_ANALOG_PLL_ENET_BYPASS_CLK_SRC(n)	((uint32_t)(((n) & 0x03) << 14))
#define CCM_ANALOG_PLL_ENET_ENABLE		((uint32_t)(1<<13))
#define CCM_ANALOG_PLL_ENET_POWERDOWN		((uint32_t)(1<<12))
#define CCM_ANALOG_PLL_ENET_ENET2_DIV_SELECT(n)	((uint32_t)(((n) & 0x03) << 2))
#define CCM_ANALOG_PLL_ENET_DIV_SELECT(n)	((uint32_t)(((n) & 0x03) << 0))
#define CCM_ANALOG_MISC0_XTAL_24M_PWD		((uint32_t)(1<<30))
#define CCM_ANALOG_MISC0_RTC_XTAL_SOURCE	((uint32_t)(1<<29))
#define CCM_ANALOG_MISC0_CLKGATE_DELAY(n)	((uint32_t)(((n) & 0x07) << 26))
#define CCM_ANALOG_MISC0_CLKGATE_CTRL		((uint32_t)(1<<25))
#define CCM_ANALOG_MISC0_OSC_XTALOK_EN		((uint32_t)(1<<16))
#define CCM_ANALOG_MISC0_OSC_XTALOK		((uint32_t)(1<<15))
#define CCM_ANALOG_MISC0_OSC_I(n)		((uint32_t)(((n) & 0x03) << 13))
#define CCM_ANALOG_MISC0_DISCON_HIGH_SNVS	((uint32_t)(1<<12))
#define CCM_ANALOG_MISC0_STOP_MODE_CONFIG(n)	((uint32_t)(((n) & 0x03) << 10))
#define CCM_ANALOG_MISC0_REFTOP_VBGUP		((uint32_t)(1<<7))
#define CCM_ANALOG_MISC0_REFTOP_VBGADJ(n)	((uint32_t)(((n) & 0x07) << 4))
#define CCM_ANALOG_MISC0_REFTOP_SELFBIASOFF	((uint32_t)(1<<3))
#define CCM_ANALOG_MISC0_REFTOP_PWD		((uint32_t)(1<<0))
#define CCM_ANALOG_MISC1_IRQ_DIG_BO		((uint32_t)(1<<31))
#define CCM_ANALOG_MISC1_IRQ_ANA_BO		((uint32_t)(1<<30))
#define CCM_ANALOG_MISC1_IRQ_TEMPHIGH		((uint32_t)(1<<29))
#define CCM_ANALOG_MISC1_IRQ_TEMPLOW		((uint32_t)(1<<28))
#define CCM_ANALOG_MISC1_IRQ_TEMPPANIC		((uint32_t)(1<<27))
#define CCM_ANALOG_MISC1_PFD_528_AUTOGATE_EN	((uint32_t)(1<<17))
#define CCM_ANALOG_MISC1_PFD_480_AUTOGATE_EN	((uint32_t)(1<<16))
#define CCM_ANALOG_MISC1_LVDSCLK1_IBEN		((uint32_t)(1<<12))
#define CCM_ANALOG_MISC1_LVDSCLK1_OBEN		((uint32_t)(1<<10))
#define CCM_ANALOG_MISC1_LVDS1_CLK_SEL(n)	((uint32_t)(((n) & 0x1F) << 0))
#define CCM_ANALOG_MISC2_VIDEO_DIV(n)		((uint32_t)(((n) & 0x03) << 30))
#define CCM_ANALOG_MISC2_REG2_STEP_TIME(n)	((uint32_t)(((n) & 0x03) << 28))
#define CCM_ANALOG_MISC2_REG1_STEP_TIME(n)	((uint32_t)(((n) & 0x03) << 26))
#define CCM_ANALOG_MISC2_REG0_STEP_TIME(n)	((uint32_t)(((n) & 0x03) << 24))
#define CCM_ANALOG_MISC2_DIV_MSB		((uint32_t)(1<<23))
#define CCM_ANALOG_MISC2_AUDIO_DIV_MSB		((uint32_t)(1<<23))
#define CCM_ANALOG_MISC2_REG2_OK		((uint32_t)(1<<22))
#define CCM_ANALOG_MISC2_REG2_ENABLE_BO		((uint32_t)(1<<21))
#define CCM_ANALOG_MISC2_REG2_BO_STATUS		((uint32_t)(1<<19))
#define CCM_ANALOG_MISC2_REG2_BO_OFFSET(n)	((uint32_t)(((n) & 0x07) << 16))
#define CCM_ANALOG_MISC2_DIV_LSB		((uint32_t)(1<<15))
#define CCM_ANALOG_MISC2_AUDIO_DIV_LSB		((uint32_t)(1<<15))
#define CCM_ANALOG_MISC2_REG1_OK		((uint32_t)(1<<14))
#define CCM_ANALOG_MISC2_REG1_ENABLE_BO		((uint32_t)(1<<13))
#define CCM_ANALOG_MISC2_REG1_BO_STATUS		((uint32_t)(1<<11))
#define CCM_ANALOG_MISC2_REG1_BO_OFFSET(n)	((uint32_t)(((n) & 0x07) << 8))
#define CCM_ANALOG_MISC2_PLL3_DISABLE		((uint32_t)(1<<7))
#define CCM_ANALOG_MISC2_REG0_OK		((uint32_t)(1<<6))
#define CCM_ANALOG_MISC2_REG0_ENABLE_BO		((uint32_t)(1<<5))
#define CCM_ANALOG_MISC2_REG0_BO_STATUS		((uint32_t)(1<<3))
#define CCM_ANALOG_MISC2_REG0_BO_OFFSET(n)	((uint32_t)(((n) & 0x07) << 0))
#define CCM_ANALOG_PLL_AUDIO_NUM_MASK		(((1<<29)-1))
#define CCM_ANALOG_PLL_AUDIO_DENOM_MASK		(((1<<29)-1))
#define CCM_ANALOG_PLL_AUDIO_LOCK		((uint32_t)(1<<31))


// 34.8: page 1818
#define IMXRT_CSI		(*(IMXRT_REGISTER32_t *)IMXRT_CSI_ADDRESS)
#define CSI_CSICR1			(IMXRT_CSI.offset000)
#define CSI_CSICR2			(IMXRT_CSI.offset004)
#define CSI_CSICR3			(IMXRT_CSI.offset008)
#define CSI_CSISTATFIFO			(IMXRT_CSI.offset00C)
#define CSI_CSIRFIFO			(IMXRT_CSI.offset010)
#define CSI_CSIRXCNT			(IMXRT_CSI.offset014)
#define CSI_CSISR			(IMXRT_CSI.offset018)
#define CSI_CSIDMASA_STATFIFO		(IMXRT_CSI.offset020)
#define CSI_CSIDMATS_STATFIFO		(IMXRT_CSI.offset024)
#define CSI_CSIDMASA_FB1		(IMXRT_CSI.offset028)
#define CSI_CSIDMASA_FB2		(IMXRT_CSI.offset02C)
#define CSI_CSIFBUF_PARA		(IMXRT_CSI.offset030)
#define CSI_CSIIMAG_PARA		(IMXRT_CSI.offset034)
#define CSI_CSICR18			(IMXRT_CSI.offset048)
#define CSI_CSICR19			(IMXRT_CSI.offset04C)

#define CSI_CSICR1_SWAP16_EN                    ((uint32_t)(1<<31))
#define CSI_CSICR1_EXT_VSYNC                    ((uint32_t)(1<<30))
#define CSI_CSICR1_EOF_INT_EN                   ((uint32_t)(1<<29))
#define CSI_CSICR1_PrP_IF_EN                    ((uint32_t)(1<<28))
#define CSI_CSICR1_CCIR_MODE                    ((uint32_t)(1<<27))
#define CSI_CSICR1_COF_INT_EN                   ((uint32_t)(1<<26))
#define CSI_CSICR1_SF_OR_INTEN                  ((uint32_t)(1<<25))
#define CSI_CSICR1_RF_OR_INTEN                  ((uint32_t)(1<<24))
#define CSI_CSICR1_SFF_DMA_DONE_INTEN           ((uint32_t)(1<<22))
#define CSI_CSICR1_STATFF_INTEN                 ((uint32_t)(1<<21))
#define CSI_CSICR1_FB2_DMA_DONE_INTEN           ((uint32_t)(1<<20))
#define CSI_CSICR1_FB1_DMA_DONE_INTEN           ((uint32_t)(1<<19))
#define CSI_CSICR1_RXFF_INTEN                   ((uint32_t)(1<<18))
#define CSI_CSICR1_SOF_POL                      ((uint32_t)(1<<17))
#define CSI_CSICR1_SOF_INTEN                    ((uint32_t)(1<<16))
#define CSI_CSICR1_HSYNC_POL                    ((uint32_t)(1<<11))
#define CSI_CSICR1_CCIR_EN                      ((uint32_t)(1<<10))
#define CSI_CSICR1_FCC                          ((uint32_t)(1<<8))
#define CSI_CSICR1_PACK_DIR                     ((uint32_t)(1<<7))
#define CSI_CSICR1_CLR_STATFIFO                 ((uint32_t)(1<<6))
#define CSI_CSICR1_CLR_RXFIFO                   ((uint32_t)(1<<5))
#define CSI_CSICR1_GCLK_MODE                    ((uint32_t)(1<<4))
#define CSI_CSICR1_INV_DATA                     ((uint32_t)(1<<3))
#define CSI_CSICR1_INV_PCLK                     ((uint32_t)(1<<2))
#define CSI_CSICR1_REDGE                        ((uint32_t)(1<<1))
#define CSI_CSICR1_PIXEL_BIT                    ((uint32_t)(1<<0))

#define CSI_CSICR2_DMA_BURST_TYPE_RFF(n)        ((uint32_t)(((n) & 0x3)<<30))
#define CSI_CSICR2_DMA_BURST_TYPE_SFF(n)        ((uint32_t)(((n) & 0x3)<<28))
#define CSI_CSICR2_DRM                          ((uint32_t)(1<<26))
#define CSI_CSICR2_AFS(n)                       ((uint32_t)(((n) & 0x3)<<24))
#define CSI_CSICR2_SCE                          ((uint32_t)(1<<23))
#define CSI_CSICR2_BTS(n)                       ((uint32_t)(((n) & 0x3)<<19))
#define CSI_CSICR2_LVRM(n)                      ((uint32_t)(((n) & 0x7)<<16))
#define CSI_CSICR2_VSC(n)                       ((uint32_t)(((n) & 0xff)<<8))
#define CSI_CSICR2_HSC(n)                       ((uint32_t)(((n) & 0xff)<<0))
    
#define CSI_CSICR3_FRMCNT(n)                    ((uint32_t)(((n) & 0xffff)<<16))
#define CSI_CSICR3_FRMCNT_RST                   ((uint32_t)(1<<15))
#define CSI_CSICR3_DMA_REFLASH_RFF              ((uint32_t)(1<<14))
#define CSI_CSICR3_DMA_REFLASH_SFF              ((uint32_t)(1<<13))
#define CSI_CSICR3_DMA_REQ_EN_RFF               ((uint32_t)(1<<12))
#define CSI_CSICR3_DMA_REQ_EN_SFF               ((uint32_t)(1<<11))
#define CSI_CSICR3_STATFF_LEVEL(n)              ((uint32_t)(((n) & 0x7)<<8))
#define CSI_CSICR3_HRESP_ERR_EN                 ((uint32_t)(1<<7))
#define CSI_CSICR3_RxFF_LEVEL(n)                ((uint32_t)(((n) & 0x7)<<4))
#define CSI_CSICR3_TWO_8BIT_SENSOR              ((uint32_t)(1<<3))
#define CSI_CSICR3_ZERO_PACK_EN                 ((uint32_t)(1<<2))
#define CSI_CSICR3_ECC_INT_EN                   ((uint32_t)(1<<1))
#define CSI_CSICR3_ECC_AUTO_EN                  ((uint32_t)(1<<0))

#define CSI_CSISR_BASEADDR_CHHANGE_ERROR        ((uint32_t)(1<<28))
#define CSI_CSISR_DMA_FIELD0_DONE               ((uint32_t)(1<<27))
#define CSI_CSISR_DMA_FIELD1_DONE               ((uint32_t)(1<<26))
#define CSI_CSISR_SF_OR_INT                     ((uint32_t)(1<<25))
#define CSI_CSISR_RF_OR_INT                     ((uint32_t)(1<<24))
#define CSI_CSISR_DMA_TSF_DONE_SFF              ((uint32_t)(1<<22))
#define CSI_CSISR_STATFF_INT                    ((uint32_t)(1<<21))
#define CSI_CSISR_DMA_TSF_DONE_FB2              ((uint32_t)(1<<20))
#define CSI_CSISR_DMA_TSF_DONE_FB1              ((uint32_t)(1<<19))
#define CSI_CSISR_RxFF_INT                      ((uint32_t)(1<<18))
#define CSI_CSISR_EOF_INT                       ((uint32_t)(1<<17))
#define CSI_CSISR_SOF_INT                       ((uint32_t)(1<<16))
#define CSI_CSISR_F2_INT                        ((uint32_t)(1<<15))
#define CSI_CSISR_F1_INT                        ((uint32_t)(1<<14))
#define CSI_CSISR_COF_INT                       ((uint32_t)(1<<13))
#define CSI_CSISR_HRESP_ERR_INT                 ((uint32_t)(1<<7))
#define CSI_CSISR_ECC_INT                       ((uint32_t)(1<<1))
#define CSI_CSISR_DRDY                          ((uint32_t)(1<<0))

#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE(n)  ((uint32_t)(((n) & 0xffff)<<16))
#define CSI_CSIFBUF_PARA_FBUF_STRIDE(n)         ((uint32_t)(((n) & 0xffff)<<0))

#define CSI_CSIIMAG_PARA_IMAGE_WIDTH(n)         ((uint32_t)(((n) & 0xffff)<<16))
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT(n)        ((uint32_t)(((n) & 0xffff)<<0))

#define CSI_CSICR18_CSI_ENABLE                  ((uint32_t)(1<<31))
#define CSI_CSICR18_MASK_OPTION(n)              ((uint32_t)(((n) & 0x3)<<18))
#define CSI_CSICR18_AHB_HPROT(n)                ((uint32_t)(((n) & 0xf)<<12))

#define CSI_CSICR18_RGB888A_FORMAT_SEL          ((uint32_t)(1<<10))
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE    ((uint32_t)(1<<9))
#define CSI_CSICR18_LAST_DMA_REQ_SEL            ((uint32_t)(1<<8))
#define CSI_CSICR18_DMA_FIELD1_DONE_IE          ((uint32_t)(1<<7))
#define CSI_CSICR18_FIELD0_DONE_IE              ((uint32_t)(1<<6))
#define CSI_CSICR18_BASEADDR_SWITCH_SEL         ((uint32_t)(1<<5))
#define CSI_CSICR18_BASEADDR_SWITCH_EN          ((uint32_t)(1<<4))
#define CSI_CSICR18_PARALLEL24_EN               ((uint32_t)(1<<3))
#define CSI_CSICR18_DEINTERLACE_EN              ((uint32_t)(1<<2))

#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL(n) ((uint32_t)(((n) & 0xf)<<12))


// 18.7.1.1: page 1209
#define IMXRT_DCDC		(*(IMXRT_REGISTER32_t *)IMXRT_DCDC_ADDRESS)
#define DCDC_REG0			(IMXRT_DCDC.offset000)
#define DCDC_REG1			(IMXRT_DCDC.offset004)
#define DCDC_REG2			(IMXRT_DCDC.offset008)
#define DCDC_REG3			(IMXRT_DCDC.offset00C)
#define DCDC_REG0_STS_DC_OK			((uint32_t)(1<<31))
#define DCDC_REG0_XTAL_24M_OK			((uint32_t)(1<<29))
#define DCDC_REG0_CURRENT_ALERT_RESET		((uint32_t)(1<<28))
#define DCDC_REG0_XTALOK_DISABLE		((uint32_t)(1<<27))
#define DCDC_REG0_PWD_CMP_OFFSET		((uint32_t)(1<<26))
#define DCDC_REG0_LP_HIGH_HYS			((uint32_t)(1<<21))
#define DCDC_REG0_LP_OVERLOAD_FREQ_SEL		((uint32_t)(1<<20))
#define DCDC_REG0_LP_OVERLOAD_THRSH(n)		((uint32_t)(((n) & 0x03) << 18))
#define DCDC_REG0_PWD_HIGH_VOLT_DET		((uint32_t)(1<<17))
#define DCDC_REG0_EN_LP_OVERLOAD_SNS		((uint32_t)(1<<16))
#define DCDC_REG0_ADJ_POSLIMIT_BUCK(n)		((uint32_t)(((n) & 0x0F) << 12))
#define DCDC_REG0_PWD_CMP_BATT_DET		((uint32_t)(1<<11))
#define DCDC_REG0_OVERCUR_TRIG_ADJ(n)		((uint32_t)(((n) & 0x03) << 9))
#define DCDC_REG0_PWD_OVERCUR_DET		((uint32_t)(1<<8))
#define DCDC_REG0_CUR_SNS_THRSH(n)		((uint32_t)(((n) & 0x07) << 5))
#define DCDC_REG0_PWD_CUR_SNS_CMP		((uint32_t)(1<<4))
#define DCDC_REG0_PWD_OSC_INT			((uint32_t)(1<<3))
#define DCDC_REG0_SEL_CLK			((uint32_t)(1<<2))
#define DCDC_REG0_DISABLE_AUTO_CLK_SWITCH	((uint32_t)(1<<1))
#define DCDC_REG0_PWD_ZCD			((uint32_t)(1<<0))
#define DCDC_REG1_VBG_TRIM(n)			((uint32_t)(((n) & 0x1F) << 24))
#define DCDC_REG1_LOOPCTRL_EN_HYST		((uint32_t)(1<<23))
#define DCDC_REG1_LOOPCTRL_HST_THRESH		((uint32_t)(1<<21))
#define DCDC_REG1_LP_CMP_ISRC_SEL(n)		((uint32_t)(((n) & 0x03) << 12))
#define DCDC_REG1_REG_RLOAD_SW			((uint32_t)(1<<9))
#define DCDC_REG1_REG_FBK_SEL(n)		((uint32_t)(((n) & 0x03) << 7))
#define DCDC_REG2_DCM_SET_CTRL			((uint32_t)(1<<28))
#define DCDC_REG2_DISABLE_PULSE_SKIP		((uint32_t)(1<<27))
#define DCDC_REG2_LOOPCTRL_HYST_SIGN		((uint32_t)(1<<13))
#define DCDC_REG2_LOOPCTRL_RCSCALE_THRSH	((uint32_t)(1<<12))
#define DCDC_REG2_LOOPCTRL_EN_RCSCALE		((uint32_t)(((n) & 0x07) << 9))
#define DCDC_REG2_LOOPCTRL_DC_FF		((uint32_t)(((n) & 0x07) << 6))
#define DCDC_REG2_LOOPCTRL_DC_R			((uint32_t)(((n) & 0x0F) << 2))
#define DCDC_REG2_LOOPCTRL_DC_C			((uint32_t)(((n) & 0x03) << 0))
#define DCDC_REG3_DISABLE_STEP			((uint32_t)(1<<30))
#define DCDC_REG3_MISC_DISABLEFET_LOGIC		((uint32_t)(1<<28))
#define DCDC_REG3_MISC_DELAY_TIMING		((uint32_t)(1<<27))
#define DCDC_REG3_MINPWR_DC_HALFCLK		((uint32_t)(1<<24))
#define DCDC_REG3_TARGET_LP(n)			((uint32_t)(((n) & 0x07) << 8))
#define DCDC_REG3_TRG(n)			((uint32_t)(((n) & 0x1F) << 0))
#define DCDC_REG3_TRG_MASK			((uint32_t)(0x1F << 0))

// 5.6.1.1: page 85
#define IMXRT_DMAMUX		(*(IMXRT_REGISTER32_t *)IMXRT_DMAMUX_ADDRESS)
#define DMAMUX_CHCFG0			(IMXRT_DMAMUX.offset000)
#define DMAMUX_CHCFG1			(IMXRT_DMAMUX.offset004)
#define DMAMUX_CHCFG2			(IMXRT_DMAMUX.offset008)
#define DMAMUX_CHCFG3			(IMXRT_DMAMUX.offset00C)
#define DMAMUX_CHCFG4			(IMXRT_DMAMUX.offset010)
#define DMAMUX_CHCFG5			(IMXRT_DMAMUX.offset014)
#define DMAMUX_CHCFG6			(IMXRT_DMAMUX.offset018)
#define DMAMUX_CHCFG7			(IMXRT_DMAMUX.offset01C)
#define DMAMUX_CHCFG8			(IMXRT_DMAMUX.offset020)
#define DMAMUX_CHCFG9			(IMXRT_DMAMUX.offset024)
#define DMAMUX_CHCFG10			(IMXRT_DMAMUX.offset028)
#define DMAMUX_CHCFG11			(IMXRT_DMAMUX.offset02C)
#define DMAMUX_CHCFG12			(IMXRT_DMAMUX.offset030)
#define DMAMUX_CHCFG13			(IMXRT_DMAMUX.offset034)
#define DMAMUX_CHCFG14			(IMXRT_DMAMUX.offset038)
#define DMAMUX_CHCFG15			(IMXRT_DMAMUX.offset03C)
#define DMAMUX_CHCFG16			(IMXRT_DMAMUX.offset040)
#define DMAMUX_CHCFG17			(IMXRT_DMAMUX.offset044)
#define DMAMUX_CHCFG18			(IMXRT_DMAMUX.offset048)
#define DMAMUX_CHCFG19			(IMXRT_DMAMUX.offset04C)
#define DMAMUX_CHCFG20			(IMXRT_DMAMUX.offset050)
#define DMAMUX_CHCFG21			(IMXRT_DMAMUX.offset054)
#define DMAMUX_CHCFG22			(IMXRT_DMAMUX.offset058)
#define DMAMUX_CHCFG23			(IMXRT_DMAMUX.offset05C)
#define DMAMUX_CHCFG24			(IMXRT_DMAMUX.offset060)
#define DMAMUX_CHCFG25			(IMXRT_DMAMUX.offset064)
#define DMAMUX_CHCFG26			(IMXRT_DMAMUX.offset068)
#define DMAMUX_CHCFG27			(IMXRT_DMAMUX.offset06C)
#define DMAMUX_CHCFG28			(IMXRT_DMAMUX.offset070)
#define DMAMUX_CHCFG29			(IMXRT_DMAMUX.offset074)
#define DMAMUX_CHCFG30			(IMXRT_DMAMUX.offset078)
#define DMAMUX_CHCFG31			(IMXRT_DMAMUX.offset07C)
#define DMAMUX_CHCFG_ENBL			((uint32_t)(1<<31))
#define DMAMUX_CHCFG_TRIG			((uint32_t)(1<<30))
#define DMAMUX_CHCFG_A_ON			((uint32_t)(1<<29))

// 6.6.5.1: page 116
typedef struct {
	volatile uint32_t CR;	// 0
	volatile uint32_t ES;	// 4
	uint32_t unused1;	// 8
	volatile uint32_t ERQ;	// C
	uint32_t unused2;	// 10
	volatile uint32_t EEI;	// 14
	volatile uint8_t CEEI;	// 18
	volatile uint8_t SEEI;	// 19
	volatile uint8_t CERQ;	// 1A
	volatile uint8_t SERQ;	// 1B
	volatile uint8_t CDNE;	// 1C
	volatile uint8_t SSRT;	// 1D
	volatile uint8_t CERR;	// 1E
	volatile uint8_t CINT;	// 1F
	uint32_t unused3;	// 20
	volatile uint32_t INT;	// 24
	uint32_t unused4;	// 28
	volatile uint32_t ERR;	// 2C
	uint32_t unused5;	// 30
	volatile uint32_t HRS;	// 34
	uint32_t unused6;	// 38
	uint32_t unused7;	// 3C
	uint32_t unused8;	// 40
	volatile uint32_t EARS;	// 44
	uint32_t unused[46];
	volatile uint8_t DCHPRI3;
	volatile uint8_t DCHPRI2;
	volatile uint8_t DCHPRI1;
	volatile uint8_t DCHPRI0;
	volatile uint8_t DCHPRI7;
	volatile uint8_t DCHPRI6;
	volatile uint8_t DCHPRI5;
	volatile uint8_t DCHPRI4;
	volatile uint8_t DCHPRI11;
	volatile uint8_t DCHPRI10;
	volatile uint8_t DCHPRI9;
	volatile uint8_t DCHPRI8;
	volatile uint8_t DCHPRI15;
	volatile uint8_t DCHPRI14;
	volatile uint8_t DCHPRI13;
	volatile uint8_t DCHPRI12;
	volatile uint8_t DCHPRI19;
	volatile uint8_t DCHPRI18;
	volatile uint8_t DCHPRI17;
	volatile uint8_t DCHPRI16;
	volatile uint8_t DCHPRI23;
	volatile uint8_t DCHPRI22;
	volatile uint8_t DCHPRI21;
	volatile uint8_t DCHPRI20;
	volatile uint8_t DCHPRI27;
	volatile uint8_t DCHPRI26;
	volatile uint8_t DCHPRI25;
	volatile uint8_t DCHPRI24;
	volatile uint8_t DCHPRI31;
	volatile uint8_t DCHPRI30;
	volatile uint8_t DCHPRI29;
	volatile uint8_t DCHPRI28;
} IMXRT_DMA_t;

typedef struct {
	volatile const void * volatile SADDR;
	int16_t SOFF;
	union {
		uint16_t ATTR;
		struct {
			uint8_t ATTR_DST;
			uint8_t ATTR_SRC;
		};
	};
	union {
		uint32_t NBYTES;
		uint32_t NBYTES_MLNO;
		uint32_t NBYTES_MLOFFNO;
		uint32_t NBYTES_MLOFFYES;
	};
	int32_t SLAST;
	volatile void * volatile DADDR;
	int16_t DOFF;
	union {
		volatile uint16_t CITER;
		volatile uint16_t CITER_ELINKYES;
		volatile uint16_t CITER_ELINKNO;
	};
	int32_t DLASTSGA;
	volatile uint16_t CSR;
	union {
		volatile uint16_t BITER;
		volatile uint16_t BITER_ELINKYES;
		volatile uint16_t BITER_ELINKNO;
	};
} IMXRT_DMA_TCD_t;
#define IMXRT_DMA		(*(IMXRT_DMA_t *)IMXRT_DMA_ADDRESS)
#define DMA_CR				(IMXRT_DMA.CR)
#define DMA_ES				(IMXRT_DMA.ES)
#define DMA_ERQ				(IMXRT_DMA.ERQ)
#define DMA_EEI				(IMXRT_DMA.EEI)
#define DMA_CEEI			(IMXRT_DMA.CEEI)
#define DMA_SEEI			(IMXRT_DMA.SEEI)
#define DMA_CERQ			(IMXRT_DMA.CERQ)
#define DMA_SERQ			(IMXRT_DMA.SERQ)
#define DMA_CDNE			(IMXRT_DMA.CDNE)
#define DMA_SSRT			(IMXRT_DMA.SSRT)
#define DMA_CERR			(IMXRT_DMA.CERR)
#define DMA_CINT			(IMXRT_DMA.CINT)
#define DMA_INT				(IMXRT_DMA.INT)
#define DMA_ERR				(IMXRT_DMA.ERR)
#define DMA_HRS				(IMXRT_DMA.HRS)
#define DMA_EARS			(IMXRT_DMA.EARS)
#define DMA_DCHPRI3			(IMXRT_DMA.DCHPRI3)
#define DMA_DCHPRI2			(IMXRT_DMA.DCHPRI2)
#define DMA_DCHPRI1			(IMXRT_DMA.DCHPRI1)
#define DMA_DCHPRI0			(IMXRT_DMA.DCHPRI0)
#define DMA_DCHPRI7			(IMXRT_DMA.DCHPRI7)
#define DMA_DCHPRI6			(IMXRT_DMA.DCHPRI6)
#define DMA_DCHPRI5			(IMXRT_DMA.DCHPRI5)
#define DMA_DCHPRI4			(IMXRT_DMA.DCHPRI4)
#define DMA_DCHPRI11			(IMXRT_DMA.DCHPRI11)
#define DMA_DCHPRI10			(IMXRT_DMA.DCHPRI10)
#define DMA_DCHPRI9			(IMXRT_DMA.DCHPRI9)
#define DMA_DCHPRI8			(IMXRT_DMA.DCHPRI8)
#define DMA_DCHPRI15			(IMXRT_DMA.DCHPRI15)
#define DMA_DCHPRI14			(IMXRT_DMA.DCHPRI14)
#define DMA_DCHPRI13			(IMXRT_DMA.DCHPRI13)
#define DMA_DCHPRI12			(IMXRT_DMA.DCHPRI12)
#define DMA_DCHPRI19			(IMXRT_DMA.DCHPRI19)
#define DMA_DCHPRI18			(IMXRT_DMA.DCHPRI18)
#define DMA_DCHPRI17			(IMXRT_DMA.DCHPRI17)
#define DMA_DCHPRI16			(IMXRT_DMA.DCHPRI16)
#define DMA_DCHPRI23			(IMXRT_DMA.DCHPRI23)
#define DMA_DCHPRI22			(IMXRT_DMA.DCHPRI22)
#define DMA_DCHPRI21			(IMXRT_DMA.DCHPRI21)
#define DMA_DCHPRI20			(IMXRT_DMA.DCHPRI20)
#define DMA_DCHPRI27			(IMXRT_DMA.DCHPRI27)
#define DMA_DCHPRI26			(IMXRT_DMA.DCHPRI26)
#define DMA_DCHPRI25			(IMXRT_DMA.DCHPRI25)
#define DMA_DCHPRI24			(IMXRT_DMA.DCHPRI24)
#define DMA_DCHPRI31			(IMXRT_DMA.DCHPRI31)
#define DMA_DCHPRI30			(IMXRT_DMA.DCHPRI30)
#define DMA_DCHPRI29			(IMXRT_DMA.DCHPRI29)
#define DMA_DCHPRI28			(IMXRT_DMA.DCHPRI28)

#define DMA_CR_ACTIVE                   ((uint32_t)(1<<31))     // 1=DMA is executing
#define DMA_CR_CX                       ((uint32_t)(1<<17))     // Cancel Transfer
#define DMA_CR_ECX                      ((uint32_t)(1<<16))     // Error Cancel Transfer
#define DMA_CR_GRP1PRI                  ((uint32_t)(1<<10))
#define DMA_CR_GRP0PRI                  ((uint32_t)(1<<8))
#define DMA_CR_EMLM                     ((uint32_t)(1<<7))      // Enable Minor Loop Mapping
#define DMA_CR_CLM                      ((uint32_t)(1<<6))      // Continuous Link Mode
#define DMA_CR_HALT                     ((uint32_t)(1<<5))      // Halt DMA Operations
#define DMA_CR_HOE                      ((uint32_t)(1<<4))      // Halt On Error
#define DMA_CR_ERGA                     ((uint32_t)(1<<3))      // Enable Round Robin Group Arb
#define DMA_CR_ERCA                     ((uint32_t)(1<<2))      // Enable Round Robin Channel Arb
#define DMA_CR_EDBG                     ((uint32_t)(1<<1))      // Enable Debug
#define DMA_CEEI_CEEI(n)                ((uint8_t)(n & 0x1F))   // Clear Enable Error Interrupt
#define DMA_CEEI_CAEE                   ((uint8_t)1<<6)         // Clear All Enable Error Interrupts
#define DMA_CEEI_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_SEEI_SEEI(n)                ((uint8_t)(n & 0x1F))   // Set Enable Error Interrupt
#define DMA_SEEI_SAEE                   ((uint8_t)1<<6)         // Set All Enable Error Interrupts
#define DMA_SEEI_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_CERQ_CERQ(n)                ((uint8_t)(n & 0x1F))   // Clear Enable Request
#define DMA_CERQ_CAER                   ((uint8_t)1<<6)         // Clear All Enable Requests
#define DMA_CERQ_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_SERQ_SERQ(n)                ((uint8_t)(n & 0x1F))   // Set Enable Request
#define DMA_SERQ_SAER                   ((uint8_t)1<<6)         // Set All Enable Requests
#define DMA_SERQ_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_CDNE_CDNE(n)                ((uint8_t)(n & 0x1F))   // Clear Done Bit
#define DMA_CDNE_CADN                   ((uint8_t)1<<6)         // Clear All Done Bits
#define DMA_CDNE_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_SSRT_SSRT(n)                ((uint8_t)(n & 0x1F))   // Set Start Bit
#define DMA_SSRT_SAST                   ((uint8_t)1<<6)         // Set All Start Bits
#define DMA_SSRT_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_CERR_CERR(n)                ((uint8_t)(n & 0x1F))   // Clear Error Indicator
#define DMA_CERR_CAEI                   ((uint8_t)1<<6)         // Clear All Error Indicators
#define DMA_CERR_NOP                    ((uint8_t)1<<7)         // NOP
#define DMA_CINT_CINT(n)                ((uint8_t)(n & 0x1F))   // Clear Interrupt Request
#define DMA_CINT_CAIR                   ((uint8_t)1<<6)         // Clear All Interrupt Requests
#define DMA_CINT_NOP                    ((uint8_t)1<<7)         // NOP

#define IMXRT_DMA_TCD		((IMXRT_DMA_TCD_t *)(IMXRT_DMA_ADDRESS+0x1000)
#define DMA_TCD0_SADDR			(IMXRT_DMA_TCD[0].SADDR)
#define DMA_TCD0_SOFF			(IMXRT_DMA_TCD[0].SOFF)
#define DMA_TCD0_ATTR			(IMXRT_DMA_TCD[0].ATTR)
#define DMA_TCD0_NBYTES			(IMXRT_DMA_TCD[0].NBYTES)
#define DMA_TCD0_NBYTES_MLNO		(IMXRT_DMA_TCD[0].NBYTES_MLNO)
#define DMA_TCD0_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[0].NBYTES_MLOFFNO)
#define DMA_TCD0_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[0].NBYTES_MLOFFYES)
#define DMA_TCD0_SLAST			(IMXRT_DMA_TCD[0].SLAST)
#define DMA_TCD0_DADDR			(IMXRT_DMA_TCD[0].DADDR)
#define DMA_TCD0_DOFF			(IMXRT_DMA_TCD[0].DOFF)
#define DMA_TCD0_CITER			(IMXRT_DMA_TCD[0].CITER)
#define DMA_TCD0_CITER_ELINKYES		(IMXRT_DMA_TCD[0].CITER_ELINKYES)
#define DMA_TCD0_CITER_ELINKNO		(IMXRT_DMA_TCD[0].CITER_ELINKNO)
#define DMA_TCD0_DLASTSGA		(IMXRT_DMA_TCD[0].DLASTSGA)
#define DMA_TCD0_CSR			(IMXRT_DMA_TCD[0].CSR)
#define DMA_TCD0_BITER			(IMXRT_DMA_TCD[0].BITER)
#define DMA_TCD0_BITER_ELINKYES		(IMXRT_DMA_TCD[0].BITER_ELINKYES)
#define DMA_TCD0_BITER_ELINKNO		(IMXRT_DMA_TCD[0].BITER_ELINKNO)

#define DMA_TCD1_SADDR			(IMXRT_DMA_TCD[1].SADDR)
#define DMA_TCD1_SOFF			(IMXRT_DMA_TCD[1].SOFF)
#define DMA_TCD1_ATTR			(IMXRT_DMA_TCD[1].ATTR)
#define DMA_TCD1_NBYTES			(IMXRT_DMA_TCD[1].NBYTES)
#define DMA_TCD1_NBYTES_MLNO		(IMXRT_DMA_TCD[1].NBYTES_MLNO)
#define DMA_TCD1_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[1].NBYTES_MLOFFNO)
#define DMA_TCD1_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[1].NBYTES_MLOFFYES)
#define DMA_TCD1_SLAST			(IMXRT_DMA_TCD[1].SLAST)
#define DMA_TCD1_DADDR			(IMXRT_DMA_TCD[1].DADDR)
#define DMA_TCD1_DOFF			(IMXRT_DMA_TCD[1].DOFF)
#define DMA_TCD1_CITER			(IMXRT_DMA_TCD[1].CITER)
#define DMA_TCD1_CITER_ELINKYES		(IMXRT_DMA_TCD[1].CITER_ELINKYES)
#define DMA_TCD1_CITER_ELINKNO		(IMXRT_DMA_TCD[1].CITER_ELINKNO)
#define DMA_TCD1_DLASTSGA		(IMXRT_DMA_TCD[1].DLASTSGA)
#define DMA_TCD1_CSR			(IMXRT_DMA_TCD[1].CSR)
#define DMA_TCD1_BITER			(IMXRT_DMA_TCD[1].BITER)
#define DMA_TCD1_BITER_ELINKYES		(IMXRT_DMA_TCD[1].BITER_ELINKYES)
#define DMA_TCD1_BITER_ELINKNO		(IMXRT_DMA_TCD[1].BITER_ELINKNO)

#define DMA_TCD2_SADDR			(IMXRT_DMA_TCD[2].SADDR)
#define DMA_TCD2_SOFF			(IMXRT_DMA_TCD[2].SOFF)
#define DMA_TCD2_ATTR			(IMXRT_DMA_TCD[2].ATTR)
#define DMA_TCD2_NBYTES			(IMXRT_DMA_TCD[2].NBYTES)
#define DMA_TCD2_NBYTES_MLNO		(IMXRT_DMA_TCD[2].NBYTES_MLNO)
#define DMA_TCD2_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[2].NBYTES_MLOFFNO)
#define DMA_TCD2_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[2].NBYTES_MLOFFYES)
#define DMA_TCD2_SLAST			(IMXRT_DMA_TCD[2].SLAST)
#define DMA_TCD2_DADDR			(IMXRT_DMA_TCD[2].DADDR)
#define DMA_TCD2_DOFF			(IMXRT_DMA_TCD[2].DOFF)
#define DMA_TCD2_CITER			(IMXRT_DMA_TCD[2].CITER)
#define DMA_TCD2_CITER_ELINKYES		(IMXRT_DMA_TCD[2].CITER_ELINKYES)
#define DMA_TCD2_CITER_ELINKNO		(IMXRT_DMA_TCD[2].CITER_ELINKNO)
#define DMA_TCD2_DLASTSGA		(IMXRT_DMA_TCD[2].DLASTSGA)
#define DMA_TCD2_CSR			(IMXRT_DMA_TCD[2].CSR)
#define DMA_TCD2_BITER			(IMXRT_DMA_TCD[2].BITER)
#define DMA_TCD2_BITER_ELINKYES		(IMXRT_DMA_TCD[2].BITER_ELINKYES)
#define DMA_TCD2_BITER_ELINKNO		(IMXRT_DMA_TCD[2].BITER_ELINKNO)

#define DMA_TCD3_SADDR			(IMXRT_DMA_TCD[3].SADDR)
#define DMA_TCD3_SOFF			(IMXRT_DMA_TCD[3].SOFF)
#define DMA_TCD3_ATTR			(IMXRT_DMA_TCD[3].ATTR)
#define DMA_TCD3_NBYTES			(IMXRT_DMA_TCD[3].NBYTES)
#define DMA_TCD3_NBYTES_MLNO		(IMXRT_DMA_TCD[3].NBYTES_MLNO)
#define DMA_TCD3_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[3].NBYTES_MLOFFNO)
#define DMA_TCD3_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[3].NBYTES_MLOFFYES)
#define DMA_TCD3_SLAST			(IMXRT_DMA_TCD[3].SLAST)
#define DMA_TCD3_DADDR			(IMXRT_DMA_TCD[3].DADDR)
#define DMA_TCD3_DOFF			(IMXRT_DMA_TCD[3].DOFF)
#define DMA_TCD3_CITER			(IMXRT_DMA_TCD[3].CITER)
#define DMA_TCD3_CITER_ELINKYES		(IMXRT_DMA_TCD[3].CITER_ELINKYES)
#define DMA_TCD3_CITER_ELINKNO		(IMXRT_DMA_TCD[3].CITER_ELINKNO)
#define DMA_TCD3_DLASTSGA		(IMXRT_DMA_TCD[3].DLASTSGA)
#define DMA_TCD3_CSR			(IMXRT_DMA_TCD[3].CSR)
#define DMA_TCD3_BITER			(IMXRT_DMA_TCD[3].BITER)
#define DMA_TCD3_BITER_ELINKYES		(IMXRT_DMA_TCD[3].BITER_ELINKYES)
#define DMA_TCD3_BITER_ELINKNO		(IMXRT_DMA_TCD[3].BITER_ELINKNO)

#define DMA_TCD4_SADDR			(IMXRT_DMA_TCD[4].SADDR)
#define DMA_TCD4_SOFF			(IMXRT_DMA_TCD[4].SOFF)
#define DMA_TCD4_ATTR			(IMXRT_DMA_TCD[4].ATTR)
#define DMA_TCD4_NBYTES			(IMXRT_DMA_TCD[4].NBYTES)
#define DMA_TCD4_NBYTES_MLNO		(IMXRT_DMA_TCD[4].NBYTES_MLNO)
#define DMA_TCD4_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[4].NBYTES_MLOFFNO)
#define DMA_TCD4_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[4].NBYTES_MLOFFYES)
#define DMA_TCD4_SLAST			(IMXRT_DMA_TCD[4].SLAST)
#define DMA_TCD4_DADDR			(IMXRT_DMA_TCD[4].DADDR)
#define DMA_TCD4_DOFF			(IMXRT_DMA_TCD[4].DOFF)
#define DMA_TCD4_CITER			(IMXRT_DMA_TCD[4].CITER)
#define DMA_TCD4_CITER_ELINKYES		(IMXRT_DMA_TCD[4].CITER_ELINKYES)
#define DMA_TCD4_CITER_ELINKNO		(IMXRT_DMA_TCD[4].CITER_ELINKNO)
#define DMA_TCD4_DLASTSGA		(IMXRT_DMA_TCD[4].DLASTSGA)
#define DMA_TCD4_CSR			(IMXRT_DMA_TCD[4].CSR)
#define DMA_TCD4_BITER			(IMXRT_DMA_TCD[4].BITER)
#define DMA_TCD4_BITER_ELINKYES		(IMXRT_DMA_TCD[4].BITER_ELINKYES)
#define DMA_TCD4_BITER_ELINKNO		(IMXRT_DMA_TCD[4].BITER_ELINKNO)

#define DMA_TCD5_SADDR			(IMXRT_DMA_TCD[5].SADDR)
#define DMA_TCD5_SOFF			(IMXRT_DMA_TCD[5].SOFF)
#define DMA_TCD5_ATTR			(IMXRT_DMA_TCD[5].ATTR)
#define DMA_TCD5_NBYTES			(IMXRT_DMA_TCD[5].NBYTES)
#define DMA_TCD5_NBYTES_MLNO		(IMXRT_DMA_TCD[5].NBYTES_MLNO)
#define DMA_TCD5_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[5].NBYTES_MLOFFNO)
#define DMA_TCD5_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[5].NBYTES_MLOFFYES)
#define DMA_TCD5_SLAST			(IMXRT_DMA_TCD[5].SLAST)
#define DMA_TCD5_DADDR			(IMXRT_DMA_TCD[5].DADDR)
#define DMA_TCD5_DOFF			(IMXRT_DMA_TCD[5].DOFF)
#define DMA_TCD5_CITER			(IMXRT_DMA_TCD[5].CITER)
#define DMA_TCD5_CITER_ELINKYES		(IMXRT_DMA_TCD[5].CITER_ELINKYES)
#define DMA_TCD5_CITER_ELINKNO		(IMXRT_DMA_TCD[5].CITER_ELINKNO)
#define DMA_TCD5_DLASTSGA		(IMXRT_DMA_TCD[5].DLASTSGA)
#define DMA_TCD5_CSR			(IMXRT_DMA_TCD[5].CSR)
#define DMA_TCD5_BITER			(IMXRT_DMA_TCD[5].BITER)
#define DMA_TCD5_BITER_ELINKYES		(IMXRT_DMA_TCD[5].BITER_ELINKYES)
#define DMA_TCD5_BITER_ELINKNO		(IMXRT_DMA_TCD[5].BITER_ELINKNO)

#define DMA_TCD6_SADDR			(IMXRT_DMA_TCD[6].SADDR)
#define DMA_TCD6_SOFF			(IMXRT_DMA_TCD[6].SOFF)
#define DMA_TCD6_ATTR			(IMXRT_DMA_TCD[6].ATTR)
#define DMA_TCD6_NBYTES			(IMXRT_DMA_TCD[6].NBYTES)
#define DMA_TCD6_NBYTES_MLNO		(IMXRT_DMA_TCD[6].NBYTES_MLNO)
#define DMA_TCD6_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[6].NBYTES_MLOFFNO)
#define DMA_TCD6_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[6].NBYTES_MLOFFYES)
#define DMA_TCD6_SLAST			(IMXRT_DMA_TCD[6].SLAST)
#define DMA_TCD6_DADDR			(IMXRT_DMA_TCD[6].DADDR)
#define DMA_TCD6_DOFF			(IMXRT_DMA_TCD[6].DOFF)
#define DMA_TCD6_CITER			(IMXRT_DMA_TCD[6].CITER)
#define DMA_TCD6_CITER_ELINKYES		(IMXRT_DMA_TCD[6].CITER_ELINKYES)
#define DMA_TCD6_CITER_ELINKNO		(IMXRT_DMA_TCD[6].CITER_ELINKNO)
#define DMA_TCD6_DLASTSGA		(IMXRT_DMA_TCD[6].DLASTSGA)
#define DMA_TCD6_CSR			(IMXRT_DMA_TCD[6].CSR)
#define DMA_TCD6_BITER			(IMXRT_DMA_TCD[6].BITER)
#define DMA_TCD6_BITER_ELINKYES		(IMXRT_DMA_TCD[6].BITER_ELINKYES)
#define DMA_TCD6_BITER_ELINKNO		(IMXRT_DMA_TCD[6].BITER_ELINKNO)

#define DMA_TCD7_SADDR			(IMXRT_DMA_TCD[7].SADDR)
#define DMA_TCD7_SOFF			(IMXRT_DMA_TCD[7].SOFF)
#define DMA_TCD7_ATTR			(IMXRT_DMA_TCD[7].ATTR)
#define DMA_TCD7_NBYTES			(IMXRT_DMA_TCD[7].NBYTES)
#define DMA_TCD7_NBYTES_MLNO		(IMXRT_DMA_TCD[7].NBYTES_MLNO)
#define DMA_TCD7_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[7].NBYTES_MLOFFNO)
#define DMA_TCD7_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[7].NBYTES_MLOFFYES)
#define DMA_TCD7_SLAST			(IMXRT_DMA_TCD[7].SLAST)
#define DMA_TCD7_DADDR			(IMXRT_DMA_TCD[7].DADDR)
#define DMA_TCD7_DOFF			(IMXRT_DMA_TCD[7].DOFF)
#define DMA_TCD7_CITER			(IMXRT_DMA_TCD[7].CITER)
#define DMA_TCD7_CITER_ELINKYES		(IMXRT_DMA_TCD[7].CITER_ELINKYES)
#define DMA_TCD7_CITER_ELINKNO		(IMXRT_DMA_TCD[7].CITER_ELINKNO)
#define DMA_TCD7_DLASTSGA		(IMXRT_DMA_TCD[7].DLASTSGA)
#define DMA_TCD7_CSR			(IMXRT_DMA_TCD[7].CSR)
#define DMA_TCD7_BITER			(IMXRT_DMA_TCD[7].BITER)
#define DMA_TCD7_BITER_ELINKYES		(IMXRT_DMA_TCD[7].BITER_ELINKYES)
#define DMA_TCD7_BITER_ELINKNO		(IMXRT_DMA_TCD[7].BITER_ELINKNO)

#define DMA_TCD8_SADDR			(IMXRT_DMA_TCD[8].SADDR)
#define DMA_TCD8_SOFF			(IMXRT_DMA_TCD[8].SOFF)
#define DMA_TCD8_ATTR			(IMXRT_DMA_TCD[8].ATTR)
#define DMA_TCD8_NBYTES			(IMXRT_DMA_TCD[8].NBYTES)
#define DMA_TCD8_NBYTES_MLNO		(IMXRT_DMA_TCD[8].NBYTES_MLNO)
#define DMA_TCD8_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[8].NBYTES_MLOFFNO)
#define DMA_TCD8_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[8].NBYTES_MLOFFYES)
#define DMA_TCD8_SLAST			(IMXRT_DMA_TCD[8].SLAST)
#define DMA_TCD8_DADDR			(IMXRT_DMA_TCD[8].DADDR)
#define DMA_TCD8_DOFF			(IMXRT_DMA_TCD[8].DOFF)
#define DMA_TCD8_CITER			(IMXRT_DMA_TCD[8].CITER)
#define DMA_TCD8_CITER_ELINKYES		(IMXRT_DMA_TCD[8].CITER_ELINKYES)
#define DMA_TCD8_CITER_ELINKNO		(IMXRT_DMA_TCD[8].CITER_ELINKNO)
#define DMA_TCD8_DLASTSGA		(IMXRT_DMA_TCD[8].DLASTSGA)
#define DMA_TCD8_CSR			(IMXRT_DMA_TCD[8].CSR)
#define DMA_TCD8_BITER			(IMXRT_DMA_TCD[8].BITER)
#define DMA_TCD8_BITER_ELINKYES		(IMXRT_DMA_TCD[8].BITER_ELINKYES)
#define DMA_TCD8_BITER_ELINKNO		(IMXRT_DMA_TCD[8].BITER_ELINKNO)

#define DMA_TCD9_SADDR			(IMXRT_DMA_TCD[9].SADDR)
#define DMA_TCD9_SOFF			(IMXRT_DMA_TCD[9].SOFF)
#define DMA_TCD9_ATTR			(IMXRT_DMA_TCD[9].ATTR)
#define DMA_TCD9_NBYTES			(IMXRT_DMA_TCD[9].NBYTES)
#define DMA_TCD9_NBYTES_MLNO		(IMXRT_DMA_TCD[9].NBYTES_MLNO)
#define DMA_TCD9_NBYTES_MLOFFNO		(IMXRT_DMA_TCD[9].NBYTES_MLOFFNO)
#define DMA_TCD9_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[9].NBYTES_MLOFFYES)
#define DMA_TCD9_SLAST			(IMXRT_DMA_TCD[9].SLAST)
#define DMA_TCD9_DADDR			(IMXRT_DMA_TCD[9].DADDR)
#define DMA_TCD9_DOFF			(IMXRT_DMA_TCD[9].DOFF)
#define DMA_TCD9_CITER			(IMXRT_DMA_TCD[9].CITER)
#define DMA_TCD9_CITER_ELINKYES		(IMXRT_DMA_TCD[9].CITER_ELINKYES)
#define DMA_TCD9_CITER_ELINKNO		(IMXRT_DMA_TCD[9].CITER_ELINKNO)
#define DMA_TCD9_DLASTSGA		(IMXRT_DMA_TCD[9].DLASTSGA)
#define DMA_TCD9_CSR			(IMXRT_DMA_TCD[9].CSR)
#define DMA_TCD9_BITER			(IMXRT_DMA_TCD[9].BITER)
#define DMA_TCD9_BITER_ELINKYES		(IMXRT_DMA_TCD[9].BITER_ELINKYES)
#define DMA_TCD9_BITER_ELINKNO		(IMXRT_DMA_TCD[9].BITER_ELINKNO)

#define DMA_TCD10_SADDR			(IMXRT_DMA_TCD[10].SADDR)
#define DMA_TCD10_SOFF			(IMXRT_DMA_TCD[10].SOFF)
#define DMA_TCD10_ATTR			(IMXRT_DMA_TCD[10].ATTR)
#define DMA_TCD10_NBYTES		(IMXRT_DMA_TCD[10].NBYTES)
#define DMA_TCD10_NBYTES_MLNO		(IMXRT_DMA_TCD[10].NBYTES_MLNO)
#define DMA_TCD10_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[10].NBYTES_MLOFFNO)
#define DMA_TCD10_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[10].NBYTES_MLOFFYES)
#define DMA_TCD10_SLAST			(IMXRT_DMA_TCD[10].SLAST)
#define DMA_TCD10_DADDR			(IMXRT_DMA_TCD[10].DADDR)
#define DMA_TCD10_DOFF			(IMXRT_DMA_TCD[10].DOFF)
#define DMA_TCD10_CITER			(IMXRT_DMA_TCD[10].CITER)
#define DMA_TCD10_CITER_ELINKYES	(IMXRT_DMA_TCD[10].CITER_ELINKYES)
#define DMA_TCD10_CITER_ELINKNO		(IMXRT_DMA_TCD[10].CITER_ELINKNO)
#define DMA_TCD10_DLASTSGA		(IMXRT_DMA_TCD[10].DLASTSGA)
#define DMA_TCD10_CSR			(IMXRT_DMA_TCD[10].CSR)
#define DMA_TCD10_BITER			(IMXRT_DMA_TCD[10].BITER)
#define DMA_TCD10_BITER_ELINKYES	(IMXRT_DMA_TCD[10].BITER_ELINKYES)
#define DMA_TCD10_BITER_ELINKNO		(IMXRT_DMA_TCD[10].BITER_ELINKNO)

#define DMA_TCD11_SADDR			(IMXRT_DMA_TCD[11].SADDR)
#define DMA_TCD11_SOFF			(IMXRT_DMA_TCD[11].SOFF)
#define DMA_TCD11_ATTR			(IMXRT_DMA_TCD[11].ATTR)
#define DMA_TCD11_NBYTES		(IMXRT_DMA_TCD[11].NBYTES)
#define DMA_TCD11_NBYTES_MLNO		(IMXRT_DMA_TCD[11].NBYTES_MLNO)
#define DMA_TCD11_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[11].NBYTES_MLOFFNO)
#define DMA_TCD11_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[11].NBYTES_MLOFFYES)
#define DMA_TCD11_SLAST			(IMXRT_DMA_TCD[11].SLAST)
#define DMA_TCD11_DADDR			(IMXRT_DMA_TCD[11].DADDR)
#define DMA_TCD11_DOFF			(IMXRT_DMA_TCD[11].DOFF)
#define DMA_TCD11_CITER			(IMXRT_DMA_TCD[11].CITER)
#define DMA_TCD11_CITER_ELINKYES	(IMXRT_DMA_TCD[11].CITER_ELINKYES)
#define DMA_TCD11_CITER_ELINKNO		(IMXRT_DMA_TCD[11].CITER_ELINKNO)
#define DMA_TCD11_DLASTSGA		(IMXRT_DMA_TCD[11].DLASTSGA)
#define DMA_TCD11_CSR			(IMXRT_DMA_TCD[11].CSR)
#define DMA_TCD11_BITER			(IMXRT_DMA_TCD[11].BITER)
#define DMA_TCD11_BITER_ELINKYES	(IMXRT_DMA_TCD[11].BITER_ELINKYES)
#define DMA_TCD11_BITER_ELINKNO		(IMXRT_DMA_TCD[11].BITER_ELINKNO)

#define DMA_TCD12_SADDR			(IMXRT_DMA_TCD[12].SADDR)
#define DMA_TCD12_SOFF			(IMXRT_DMA_TCD[12].SOFF)
#define DMA_TCD12_ATTR			(IMXRT_DMA_TCD[12].ATTR)
#define DMA_TCD12_NBYTES		(IMXRT_DMA_TCD[12].NBYTES)
#define DMA_TCD12_NBYTES_MLNO		(IMXRT_DMA_TCD[12].NBYTES_MLNO)
#define DMA_TCD12_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[12].NBYTES_MLOFFNO)
#define DMA_TCD12_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[12].NBYTES_MLOFFYES)
#define DMA_TCD12_SLAST			(IMXRT_DMA_TCD[12].SLAST)
#define DMA_TCD12_DADDR			(IMXRT_DMA_TCD[12].DADDR)
#define DMA_TCD12_DOFF			(IMXRT_DMA_TCD[12].DOFF)
#define DMA_TCD12_CITER			(IMXRT_DMA_TCD[12].CITER)
#define DMA_TCD12_CITER_ELINKYES	(IMXRT_DMA_TCD[12].CITER_ELINKYES)
#define DMA_TCD12_CITER_ELINKNO		(IMXRT_DMA_TCD[12].CITER_ELINKNO)
#define DMA_TCD12_DLASTSGA		(IMXRT_DMA_TCD[12].DLASTSGA)
#define DMA_TCD12_CSR			(IMXRT_DMA_TCD[12].CSR)
#define DMA_TCD12_BITER			(IMXRT_DMA_TCD[12].BITER)
#define DMA_TCD12_BITER_ELINKYES	(IMXRT_DMA_TCD[12].BITER_ELINKYES)
#define DMA_TCD12_BITER_ELINKNO		(IMXRT_DMA_TCD[12].BITER_ELINKNO)

#define DMA_TCD13_SADDR			(IMXRT_DMA_TCD[13].SADDR)
#define DMA_TCD13_SOFF			(IMXRT_DMA_TCD[13].SOFF)
#define DMA_TCD13_ATTR			(IMXRT_DMA_TCD[13].ATTR)
#define DMA_TCD13_NBYTES		(IMXRT_DMA_TCD[13].NBYTES)
#define DMA_TCD13_NBYTES_MLNO		(IMXRT_DMA_TCD[13].NBYTES_MLNO)
#define DMA_TCD13_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[13].NBYTES_MLOFFNO)
#define DMA_TCD13_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[13].NBYTES_MLOFFYES)
#define DMA_TCD13_SLAST			(IMXRT_DMA_TCD[13].SLAST)
#define DMA_TCD13_DADDR			(IMXRT_DMA_TCD[13].DADDR)
#define DMA_TCD13_DOFF			(IMXRT_DMA_TCD[13].DOFF)
#define DMA_TCD13_CITER			(IMXRT_DMA_TCD[13].CITER)
#define DMA_TCD13_CITER_ELINKYES	(IMXRT_DMA_TCD[13].CITER_ELINKYES)
#define DMA_TCD13_CITER_ELINKNO		(IMXRT_DMA_TCD[13].CITER_ELINKNO)
#define DMA_TCD13_DLASTSGA		(IMXRT_DMA_TCD[13].DLASTSGA)
#define DMA_TCD13_CSR			(IMXRT_DMA_TCD[13].CSR)
#define DMA_TCD13_BITER			(IMXRT_DMA_TCD[13].BITER)
#define DMA_TCD13_BITER_ELINKYES	(IMXRT_DMA_TCD[13].BITER_ELINKYES)
#define DMA_TCD13_BITER_ELINKNO		(IMXRT_DMA_TCD[13].BITER_ELINKNO)

#define DMA_TCD14_SADDR			(IMXRT_DMA_TCD[14].SADDR)
#define DMA_TCD14_SOFF			(IMXRT_DMA_TCD[14].SOFF)
#define DMA_TCD14_ATTR			(IMXRT_DMA_TCD[14].ATTR)
#define DMA_TCD14_NBYTES		(IMXRT_DMA_TCD[14].NBYTES)
#define DMA_TCD14_NBYTES_MLNO		(IMXRT_DMA_TCD[14].NBYTES_MLNO)
#define DMA_TCD14_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[14].NBYTES_MLOFFNO)
#define DMA_TCD14_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[14].NBYTES_MLOFFYES)
#define DMA_TCD14_SLAST			(IMXRT_DMA_TCD[14].SLAST)
#define DMA_TCD14_DADDR			(IMXRT_DMA_TCD[14].DADDR)
#define DMA_TCD14_DOFF			(IMXRT_DMA_TCD[14].DOFF)
#define DMA_TCD14_CITER			(IMXRT_DMA_TCD[14].CITER)
#define DMA_TCD14_CITER_ELINKYES	(IMXRT_DMA_TCD[14].CITER_ELINKYES)
#define DMA_TCD14_CITER_ELINKNO		(IMXRT_DMA_TCD[14].CITER_ELINKNO)
#define DMA_TCD14_DLASTSGA		(IMXRT_DMA_TCD[14].DLASTSGA)
#define DMA_TCD14_CSR			(IMXRT_DMA_TCD[14].CSR)
#define DMA_TCD14_BITER			(IMXRT_DMA_TCD[14].BITER)
#define DMA_TCD14_BITER_ELINKYES	(IMXRT_DMA_TCD[14].BITER_ELINKYES)
#define DMA_TCD14_BITER_ELINKNO		(IMXRT_DMA_TCD[14].BITER_ELINKNO)

#define DMA_TCD15_SADDR			(IMXRT_DMA_TCD[15].SADDR)
#define DMA_TCD15_SOFF			(IMXRT_DMA_TCD[15].SOFF)
#define DMA_TCD15_ATTR			(IMXRT_DMA_TCD[15].ATTR)
#define DMA_TCD15_NBYTES		(IMXRT_DMA_TCD[15].NBYTES)
#define DMA_TCD15_NBYTES_MLNO		(IMXRT_DMA_TCD[15].NBYTES_MLNO)
#define DMA_TCD15_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[15].NBYTES_MLOFFNO)
#define DMA_TCD15_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[15].NBYTES_MLOFFYES)
#define DMA_TCD15_SLAST			(IMXRT_DMA_TCD[15].SLAST)
#define DMA_TCD15_DADDR			(IMXRT_DMA_TCD[15].DADDR)
#define DMA_TCD15_DOFF			(IMXRT_DMA_TCD[15].DOFF)
#define DMA_TCD15_CITER			(IMXRT_DMA_TCD[15].CITER)
#define DMA_TCD15_CITER_ELINKYES	(IMXRT_DMA_TCD[15].CITER_ELINKYES)
#define DMA_TCD15_CITER_ELINKNO		(IMXRT_DMA_TCD[15].CITER_ELINKNO)
#define DMA_TCD15_DLASTSGA		(IMXRT_DMA_TCD[15].DLASTSGA)
#define DMA_TCD15_CSR			(IMXRT_DMA_TCD[15].CSR)
#define DMA_TCD15_BITER			(IMXRT_DMA_TCD[15].BITER)
#define DMA_TCD15_BITER_ELINKYES	(IMXRT_DMA_TCD[15].BITER_ELINKYES)
#define DMA_TCD15_BITER_ELINKNO		(IMXRT_DMA_TCD[15].BITER_ELINKNO)

#define DMA_TCD16_SADDR			(IMXRT_DMA_TCD[16].SADDR)
#define DMA_TCD16_SOFF			(IMXRT_DMA_TCD[16].SOFF)
#define DMA_TCD16_ATTR			(IMXRT_DMA_TCD[16].ATTR)
#define DMA_TCD16_NBYTES		(IMXRT_DMA_TCD[16].NBYTES)
#define DMA_TCD16_NBYTES_MLNO		(IMXRT_DMA_TCD[16].NBYTES_MLNO)
#define DMA_TCD16_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[16].NBYTES_MLOFFNO)
#define DMA_TCD16_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[16].NBYTES_MLOFFYES)
#define DMA_TCD16_SLAST			(IMXRT_DMA_TCD[16].SLAST)
#define DMA_TCD16_DADDR			(IMXRT_DMA_TCD[16].DADDR)
#define DMA_TCD16_DOFF			(IMXRT_DMA_TCD[16].DOFF)
#define DMA_TCD16_CITER			(IMXRT_DMA_TCD[16].CITER)
#define DMA_TCD16_CITER_ELINKYES	(IMXRT_DMA_TCD[16].CITER_ELINKYES)
#define DMA_TCD16_CITER_ELINKNO		(IMXRT_DMA_TCD[16].CITER_ELINKNO)
#define DMA_TCD16_DLASTSGA		(IMXRT_DMA_TCD[16].DLASTSGA)
#define DMA_TCD16_CSR			(IMXRT_DMA_TCD[16].CSR)
#define DMA_TCD16_BITER			(IMXRT_DMA_TCD[16].BITER)
#define DMA_TCD16_BITER_ELINKYES	(IMXRT_DMA_TCD[16].BITER_ELINKYES)
#define DMA_TCD16_BITER_ELINKNO		(IMXRT_DMA_TCD[16].BITER_ELINKNO)

#define DMA_TCD17_SADDR			(IMXRT_DMA_TCD[17].SADDR)
#define DMA_TCD17_SOFF			(IMXRT_DMA_TCD[17].SOFF)
#define DMA_TCD17_ATTR			(IMXRT_DMA_TCD[17].ATTR)
#define DMA_TCD17_NBYTES		(IMXRT_DMA_TCD[17].NBYTES)
#define DMA_TCD17_NBYTES_MLNO		(IMXRT_DMA_TCD[17].NBYTES_MLNO)
#define DMA_TCD17_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[17].NBYTES_MLOFFNO)
#define DMA_TCD17_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[17].NBYTES_MLOFFYES)
#define DMA_TCD17_SLAST			(IMXRT_DMA_TCD[17].SLAST)
#define DMA_TCD17_DADDR			(IMXRT_DMA_TCD[17].DADDR)
#define DMA_TCD17_DOFF			(IMXRT_DMA_TCD[17].DOFF)
#define DMA_TCD17_CITER			(IMXRT_DMA_TCD[17].CITER)
#define DMA_TCD17_CITER_ELINKYES	(IMXRT_DMA_TCD[17].CITER_ELINKYES)
#define DMA_TCD17_CITER_ELINKNO		(IMXRT_DMA_TCD[17].CITER_ELINKNO)
#define DMA_TCD17_DLASTSGA		(IMXRT_DMA_TCD[17].DLASTSGA)
#define DMA_TCD17_CSR			(IMXRT_DMA_TCD[17].CSR)
#define DMA_TCD17_BITER			(IMXRT_DMA_TCD[17].BITER)
#define DMA_TCD17_BITER_ELINKYES	(IMXRT_DMA_TCD[17].BITER_ELINKYES)
#define DMA_TCD17_BITER_ELINKNO		(IMXRT_DMA_TCD[17].BITER_ELINKNO)

#define DMA_TCD18_SADDR			(IMXRT_DMA_TCD[18].SADDR)
#define DMA_TCD18_SOFF			(IMXRT_DMA_TCD[18].SOFF)
#define DMA_TCD18_ATTR			(IMXRT_DMA_TCD[18].ATTR)
#define DMA_TCD18_NBYTES		(IMXRT_DMA_TCD[18].NBYTES)
#define DMA_TCD18_NBYTES_MLNO		(IMXRT_DMA_TCD[18].NBYTES_MLNO)
#define DMA_TCD18_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[18].NBYTES_MLOFFNO)
#define DMA_TCD18_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[18].NBYTES_MLOFFYES)
#define DMA_TCD18_SLAST			(IMXRT_DMA_TCD[18].SLAST)
#define DMA_TCD18_DADDR			(IMXRT_DMA_TCD[18].DADDR)
#define DMA_TCD18_DOFF			(IMXRT_DMA_TCD[18].DOFF)
#define DMA_TCD18_CITER			(IMXRT_DMA_TCD[18].CITER)
#define DMA_TCD18_CITER_ELINKYES	(IMXRT_DMA_TCD[18].CITER_ELINKYES)
#define DMA_TCD18_CITER_ELINKNO		(IMXRT_DMA_TCD[18].CITER_ELINKNO)
#define DMA_TCD18_DLASTSGA		(IMXRT_DMA_TCD[18].DLASTSGA)
#define DMA_TCD18_CSR			(IMXRT_DMA_TCD[18].CSR)
#define DMA_TCD18_BITER			(IMXRT_DMA_TCD[18].BITER)
#define DMA_TCD18_BITER_ELINKYES	(IMXRT_DMA_TCD[18].BITER_ELINKYES)
#define DMA_TCD18_BITER_ELINKNO		(IMXRT_DMA_TCD[18].BITER_ELINKNO)

#define DMA_TCD19_SADDR			(IMXRT_DMA_TCD[19].SADDR)
#define DMA_TCD19_SOFF			(IMXRT_DMA_TCD[19].SOFF)
#define DMA_TCD19_ATTR			(IMXRT_DMA_TCD[19].ATTR)
#define DMA_TCD19_NBYTES		(IMXRT_DMA_TCD[19].NBYTES)
#define DMA_TCD19_NBYTES_MLNO		(IMXRT_DMA_TCD[19].NBYTES_MLNO)
#define DMA_TCD19_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[19].NBYTES_MLOFFNO)
#define DMA_TCD19_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[19].NBYTES_MLOFFYES)
#define DMA_TCD19_SLAST			(IMXRT_DMA_TCD[19].SLAST)
#define DMA_TCD19_DADDR			(IMXRT_DMA_TCD[19].DADDR)
#define DMA_TCD19_DOFF			(IMXRT_DMA_TCD[19].DOFF)
#define DMA_TCD19_CITER			(IMXRT_DMA_TCD[19].CITER)
#define DMA_TCD19_CITER_ELINKYES	(IMXRT_DMA_TCD[19].CITER_ELINKYES)
#define DMA_TCD19_CITER_ELINKNO		(IMXRT_DMA_TCD[19].CITER_ELINKNO)
#define DMA_TCD19_DLASTSGA		(IMXRT_DMA_TCD[19].DLASTSGA)
#define DMA_TCD19_CSR			(IMXRT_DMA_TCD[19].CSR)
#define DMA_TCD19_BITER			(IMXRT_DMA_TCD[19].BITER)
#define DMA_TCD19_BITER_ELINKYES	(IMXRT_DMA_TCD[19].BITER_ELINKYES)
#define DMA_TCD19_BITER_ELINKNO		(IMXRT_DMA_TCD[19].BITER_ELINKNO)

#define DMA_TCD20_SADDR			(IMXRT_DMA_TCD[20].SADDR)
#define DMA_TCD20_SOFF			(IMXRT_DMA_TCD[20].SOFF)
#define DMA_TCD20_ATTR			(IMXRT_DMA_TCD[20].ATTR)
#define DMA_TCD20_NBYTES		(IMXRT_DMA_TCD[20].NBYTES)
#define DMA_TCD20_NBYTES_MLNO		(IMXRT_DMA_TCD[20].NBYTES_MLNO)
#define DMA_TCD20_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[20].NBYTES_MLOFFNO)
#define DMA_TCD20_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[20].NBYTES_MLOFFYES)
#define DMA_TCD20_SLAST			(IMXRT_DMA_TCD[20].SLAST)
#define DMA_TCD20_DADDR			(IMXRT_DMA_TCD[20].DADDR)
#define DMA_TCD20_DOFF			(IMXRT_DMA_TCD[20].DOFF)
#define DMA_TCD20_CITER			(IMXRT_DMA_TCD[20].CITER)
#define DMA_TCD20_CITER_ELINKYES	(IMXRT_DMA_TCD[20].CITER_ELINKYES)
#define DMA_TCD20_CITER_ELINKNO		(IMXRT_DMA_TCD[20].CITER_ELINKNO)
#define DMA_TCD20_DLASTSGA		(IMXRT_DMA_TCD[20].DLASTSGA)
#define DMA_TCD20_CSR			(IMXRT_DMA_TCD[20].CSR)
#define DMA_TCD20_BITER			(IMXRT_DMA_TCD[20].BITER)
#define DMA_TCD20_BITER_ELINKYES	(IMXRT_DMA_TCD[20].BITER_ELINKYES)
#define DMA_TCD20_BITER_ELINKNO		(IMXRT_DMA_TCD[20].BITER_ELINKNO)

#define DMA_TCD21_SADDR			(IMXRT_DMA_TCD[21].SADDR)
#define DMA_TCD21_SOFF			(IMXRT_DMA_TCD[21].SOFF)
#define DMA_TCD21_ATTR			(IMXRT_DMA_TCD[21].ATTR)
#define DMA_TCD21_NBYTES		(IMXRT_DMA_TCD[21].NBYTES)
#define DMA_TCD21_NBYTES_MLNO		(IMXRT_DMA_TCD[21].NBYTES_MLNO)
#define DMA_TCD21_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[21].NBYTES_MLOFFNO)
#define DMA_TCD21_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[21].NBYTES_MLOFFYES)
#define DMA_TCD21_SLAST			(IMXRT_DMA_TCD[21].SLAST)
#define DMA_TCD21_DADDR			(IMXRT_DMA_TCD[21].DADDR)
#define DMA_TCD21_DOFF			(IMXRT_DMA_TCD[21].DOFF)
#define DMA_TCD21_CITER			(IMXRT_DMA_TCD[21].CITER)
#define DMA_TCD21_CITER_ELINKYES	(IMXRT_DMA_TCD[21].CITER_ELINKYES)
#define DMA_TCD21_CITER_ELINKNO		(IMXRT_DMA_TCD[21].CITER_ELINKNO)
#define DMA_TCD21_DLASTSGA		(IMXRT_DMA_TCD[21].DLASTSGA)
#define DMA_TCD21_CSR			(IMXRT_DMA_TCD[21].CSR)
#define DMA_TCD21_BITER			(IMXRT_DMA_TCD[21].BITER)
#define DMA_TCD21_BITER_ELINKYES	(IMXRT_DMA_TCD[21].BITER_ELINKYES)
#define DMA_TCD21_BITER_ELINKNO		(IMXRT_DMA_TCD[21].BITER_ELINKNO)

#define DMA_TCD22_SADDR			(IMXRT_DMA_TCD[22].SADDR)
#define DMA_TCD22_SOFF			(IMXRT_DMA_TCD[22].SOFF)
#define DMA_TCD22_ATTR			(IMXRT_DMA_TCD[22].ATTR)
#define DMA_TCD22_NBYTES		(IMXRT_DMA_TCD[22].NBYTES)
#define DMA_TCD22_NBYTES_MLNO		(IMXRT_DMA_TCD[22].NBYTES_MLNO)
#define DMA_TCD22_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[22].NBYTES_MLOFFNO)
#define DMA_TCD22_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[22].NBYTES_MLOFFYES)
#define DMA_TCD22_SLAST			(IMXRT_DMA_TCD[22].SLAST)
#define DMA_TCD22_DADDR			(IMXRT_DMA_TCD[22].DADDR)
#define DMA_TCD22_DOFF			(IMXRT_DMA_TCD[22].DOFF)
#define DMA_TCD22_CITER			(IMXRT_DMA_TCD[22].CITER)
#define DMA_TCD22_CITER_ELINKYES	(IMXRT_DMA_TCD[22].CITER_ELINKYES)
#define DMA_TCD22_CITER_ELINKNO		(IMXRT_DMA_TCD[22].CITER_ELINKNO)
#define DMA_TCD22_DLASTSGA		(IMXRT_DMA_TCD[22].DLASTSGA)
#define DMA_TCD22_CSR			(IMXRT_DMA_TCD[22].CSR)
#define DMA_TCD22_BITER			(IMXRT_DMA_TCD[22].BITER)
#define DMA_TCD22_BITER_ELINKYES	(IMXRT_DMA_TCD[22].BITER_ELINKYES)
#define DMA_TCD22_BITER_ELINKNO		(IMXRT_DMA_TCD[22].BITER_ELINKNO)

#define DMA_TCD23_SADDR			(IMXRT_DMA_TCD[23].SADDR)
#define DMA_TCD23_SOFF			(IMXRT_DMA_TCD[23].SOFF)
#define DMA_TCD23_ATTR			(IMXRT_DMA_TCD[23].ATTR)
#define DMA_TCD23_NBYTES		(IMXRT_DMA_TCD[23].NBYTES)
#define DMA_TCD23_NBYTES_MLNO		(IMXRT_DMA_TCD[23].NBYTES_MLNO)
#define DMA_TCD23_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[23].NBYTES_MLOFFNO)
#define DMA_TCD23_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[23].NBYTES_MLOFFYES)
#define DMA_TCD23_SLAST			(IMXRT_DMA_TCD[23].SLAST)
#define DMA_TCD23_DADDR			(IMXRT_DMA_TCD[23].DADDR)
#define DMA_TCD23_DOFF			(IMXRT_DMA_TCD[23].DOFF)
#define DMA_TCD23_CITER			(IMXRT_DMA_TCD[23].CITER)
#define DMA_TCD23_CITER_ELINKYES	(IMXRT_DMA_TCD[23].CITER_ELINKYES)
#define DMA_TCD23_CITER_ELINKNO		(IMXRT_DMA_TCD[23].CITER_ELINKNO)
#define DMA_TCD23_DLASTSGA		(IMXRT_DMA_TCD[23].DLASTSGA)
#define DMA_TCD23_CSR			(IMXRT_DMA_TCD[23].CSR)
#define DMA_TCD23_BITER			(IMXRT_DMA_TCD[23].BITER)
#define DMA_TCD23_BITER_ELINKYES	(IMXRT_DMA_TCD[23].BITER_ELINKYES)
#define DMA_TCD23_BITER_ELINKNO		(IMXRT_DMA_TCD[23].BITER_ELINKNO)

#define DMA_TCD24_SADDR			(IMXRT_DMA_TCD[24].SADDR)
#define DMA_TCD24_SOFF			(IMXRT_DMA_TCD[24].SOFF)
#define DMA_TCD24_ATTR			(IMXRT_DMA_TCD[24].ATTR)
#define DMA_TCD24_NBYTES		(IMXRT_DMA_TCD[24].NBYTES)
#define DMA_TCD24_NBYTES_MLNO		(IMXRT_DMA_TCD[24].NBYTES_MLNO)
#define DMA_TCD24_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[24].NBYTES_MLOFFNO)
#define DMA_TCD24_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[24].NBYTES_MLOFFYES)
#define DMA_TCD24_SLAST			(IMXRT_DMA_TCD[24].SLAST)
#define DMA_TCD24_DADDR			(IMXRT_DMA_TCD[24].DADDR)
#define DMA_TCD24_DOFF			(IMXRT_DMA_TCD[24].DOFF)
#define DMA_TCD24_CITER			(IMXRT_DMA_TCD[24].CITER)
#define DMA_TCD24_CITER_ELINKYES	(IMXRT_DMA_TCD[24].CITER_ELINKYES)
#define DMA_TCD24_CITER_ELINKNO		(IMXRT_DMA_TCD[24].CITER_ELINKNO)
#define DMA_TCD24_DLASTSGA		(IMXRT_DMA_TCD[24].DLASTSGA)
#define DMA_TCD24_CSR			(IMXRT_DMA_TCD[24].CSR)
#define DMA_TCD24_BITER			(IMXRT_DMA_TCD[24].BITER)
#define DMA_TCD24_BITER_ELINKYES	(IMXRT_DMA_TCD[24].BITER_ELINKYES)
#define DMA_TCD24_BITER_ELINKNO		(IMXRT_DMA_TCD[24].BITER_ELINKNO)

#define DMA_TCD25_SADDR			(IMXRT_DMA_TCD[25].SADDR)
#define DMA_TCD25_SOFF			(IMXRT_DMA_TCD[25].SOFF)
#define DMA_TCD25_ATTR			(IMXRT_DMA_TCD[25].ATTR)
#define DMA_TCD25_NBYTES		(IMXRT_DMA_TCD[25].NBYTES)
#define DMA_TCD25_NBYTES_MLNO		(IMXRT_DMA_TCD[25].NBYTES_MLNO)
#define DMA_TCD25_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[25].NBYTES_MLOFFNO)
#define DMA_TCD25_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[25].NBYTES_MLOFFYES)
#define DMA_TCD25_SLAST			(IMXRT_DMA_TCD[25].SLAST)
#define DMA_TCD25_DADDR			(IMXRT_DMA_TCD[25].DADDR)
#define DMA_TCD25_DOFF			(IMXRT_DMA_TCD[25].DOFF)
#define DMA_TCD25_CITER			(IMXRT_DMA_TCD[25].CITER)
#define DMA_TCD25_CITER_ELINKYES	(IMXRT_DMA_TCD[25].CITER_ELINKYES)
#define DMA_TCD25_CITER_ELINKNO		(IMXRT_DMA_TCD[25].CITER_ELINKNO)
#define DMA_TCD25_DLASTSGA		(IMXRT_DMA_TCD[25].DLASTSGA)
#define DMA_TCD25_CSR			(IMXRT_DMA_TCD[25].CSR)
#define DMA_TCD25_BITER			(IMXRT_DMA_TCD[25].BITER)
#define DMA_TCD25_BITER_ELINKYES	(IMXRT_DMA_TCD[25].BITER_ELINKYES)
#define DMA_TCD25_BITER_ELINKNO		(IMXRT_DMA_TCD[25].BITER_ELINKNO)

#define DMA_TCD26_SADDR			(IMXRT_DMA_TCD[26].SADDR)
#define DMA_TCD26_SOFF			(IMXRT_DMA_TCD[26].SOFF)
#define DMA_TCD26_ATTR			(IMXRT_DMA_TCD[26].ATTR)
#define DMA_TCD26_NBYTES		(IMXRT_DMA_TCD[26].NBYTES)
#define DMA_TCD26_NBYTES_MLNO		(IMXRT_DMA_TCD[26].NBYTES_MLNO)
#define DMA_TCD26_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[26].NBYTES_MLOFFNO)
#define DMA_TCD26_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[26].NBYTES_MLOFFYES)
#define DMA_TCD26_SLAST			(IMXRT_DMA_TCD[26].SLAST)
#define DMA_TCD26_DADDR			(IMXRT_DMA_TCD[26].DADDR)
#define DMA_TCD26_DOFF			(IMXRT_DMA_TCD[26].DOFF)
#define DMA_TCD26_CITER			(IMXRT_DMA_TCD[26].CITER)
#define DMA_TCD26_CITER_ELINKYES	(IMXRT_DMA_TCD[26].CITER_ELINKYES)
#define DMA_TCD26_CITER_ELINKNO		(IMXRT_DMA_TCD[26].CITER_ELINKNO)
#define DMA_TCD26_DLASTSGA		(IMXRT_DMA_TCD[26].DLASTSGA)
#define DMA_TCD26_CSR			(IMXRT_DMA_TCD[26].CSR)
#define DMA_TCD26_BITER			(IMXRT_DMA_TCD[26].BITER)
#define DMA_TCD26_BITER_ELINKYES	(IMXRT_DMA_TCD[26].BITER_ELINKYES)
#define DMA_TCD26_BITER_ELINKNO		(IMXRT_DMA_TCD[26].BITER_ELINKNO)

#define DMA_TCD27_SADDR			(IMXRT_DMA_TCD[27].SADDR)
#define DMA_TCD27_SOFF			(IMXRT_DMA_TCD[27].SOFF)
#define DMA_TCD27_ATTR			(IMXRT_DMA_TCD[27].ATTR)
#define DMA_TCD27_NBYTES		(IMXRT_DMA_TCD[27].NBYTES)
#define DMA_TCD27_NBYTES_MLNO		(IMXRT_DMA_TCD[27].NBYTES_MLNO)
#define DMA_TCD27_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[27].NBYTES_MLOFFNO)
#define DMA_TCD27_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[27].NBYTES_MLOFFYES)
#define DMA_TCD27_SLAST			(IMXRT_DMA_TCD[27].SLAST)
#define DMA_TCD27_DADDR			(IMXRT_DMA_TCD[27].DADDR)
#define DMA_TCD27_DOFF			(IMXRT_DMA_TCD[27].DOFF)
#define DMA_TCD27_CITER			(IMXRT_DMA_TCD[27].CITER)
#define DMA_TCD27_CITER_ELINKYES	(IMXRT_DMA_TCD[27].CITER_ELINKYES)
#define DMA_TCD27_CITER_ELINKNO		(IMXRT_DMA_TCD[27].CITER_ELINKNO)
#define DMA_TCD27_DLASTSGA		(IMXRT_DMA_TCD[27].DLASTSGA)
#define DMA_TCD27_CSR			(IMXRT_DMA_TCD[27].CSR)
#define DMA_TCD27_BITER			(IMXRT_DMA_TCD[27].BITER)
#define DMA_TCD27_BITER_ELINKYES	(IMXRT_DMA_TCD[27].BITER_ELINKYES)
#define DMA_TCD27_BITER_ELINKNO		(IMXRT_DMA_TCD[27].BITER_ELINKNO)

#define DMA_TCD28_SADDR			(IMXRT_DMA_TCD[28].SADDR)
#define DMA_TCD28_SOFF			(IMXRT_DMA_TCD[28].SOFF)
#define DMA_TCD28_ATTR			(IMXRT_DMA_TCD[28].ATTR)
#define DMA_TCD28_NBYTES		(IMXRT_DMA_TCD[28].NBYTES)
#define DMA_TCD28_NBYTES_MLNO		(IMXRT_DMA_TCD[28].NBYTES_MLNO)
#define DMA_TCD28_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[28].NBYTES_MLOFFNO)
#define DMA_TCD28_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[28].NBYTES_MLOFFYES)
#define DMA_TCD28_SLAST			(IMXRT_DMA_TCD[28].SLAST)
#define DMA_TCD28_DADDR			(IMXRT_DMA_TCD[28].DADDR)
#define DMA_TCD28_DOFF			(IMXRT_DMA_TCD[28].DOFF)
#define DMA_TCD28_CITER			(IMXRT_DMA_TCD[28].CITER)
#define DMA_TCD28_CITER_ELINKYES	(IMXRT_DMA_TCD[28].CITER_ELINKYES)
#define DMA_TCD28_CITER_ELINKNO		(IMXRT_DMA_TCD[28].CITER_ELINKNO)
#define DMA_TCD28_DLASTSGA		(IMXRT_DMA_TCD[28].DLASTSGA)
#define DMA_TCD28_CSR			(IMXRT_DMA_TCD[28].CSR)
#define DMA_TCD28_BITER			(IMXRT_DMA_TCD[28].BITER)
#define DMA_TCD28_BITER_ELINKYES	(IMXRT_DMA_TCD[28].BITER_ELINKYES)
#define DMA_TCD28_BITER_ELINKNO		(IMXRT_DMA_TCD[28].BITER_ELINKNO)

#define DMA_TCD29_SADDR			(IMXRT_DMA_TCD[29].SADDR)
#define DMA_TCD29_SOFF			(IMXRT_DMA_TCD[29].SOFF)
#define DMA_TCD29_ATTR			(IMXRT_DMA_TCD[29].ATTR)
#define DMA_TCD29_NBYTES		(IMXRT_DMA_TCD[29].NBYTES)
#define DMA_TCD29_NBYTES_MLNO		(IMXRT_DMA_TCD[29].NBYTES_MLNO)
#define DMA_TCD29_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[29].NBYTES_MLOFFNO)
#define DMA_TCD29_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[29].NBYTES_MLOFFYES)
#define DMA_TCD29_SLAST			(IMXRT_DMA_TCD[29].SLAST)
#define DMA_TCD29_DADDR			(IMXRT_DMA_TCD[29].DADDR)
#define DMA_TCD29_DOFF			(IMXRT_DMA_TCD[29].DOFF)
#define DMA_TCD29_CITER			(IMXRT_DMA_TCD[29].CITER)
#define DMA_TCD29_CITER_ELINKYES	(IMXRT_DMA_TCD[29].CITER_ELINKYES)
#define DMA_TCD29_CITER_ELINKNO		(IMXRT_DMA_TCD[29].CITER_ELINKNO)
#define DMA_TCD29_DLASTSGA		(IMXRT_DMA_TCD[29].DLASTSGA)
#define DMA_TCD29_CSR			(IMXRT_DMA_TCD[29].CSR)
#define DMA_TCD29_BITER			(IMXRT_DMA_TCD[29].BITER)
#define DMA_TCD29_BITER_ELINKYES	(IMXRT_DMA_TCD[29].BITER_ELINKYES)
#define DMA_TCD29_BITER_ELINKNO		(IMXRT_DMA_TCD[29].BITER_ELINKNO)

#define DMA_TCD30_SADDR			(IMXRT_DMA_TCD[30].SADDR)
#define DMA_TCD30_SOFF			(IMXRT_DMA_TCD[30].SOFF)
#define DMA_TCD30_ATTR			(IMXRT_DMA_TCD[30].ATTR)
#define DMA_TCD30_NBYTES		(IMXRT_DMA_TCD[30].NBYTES)
#define DMA_TCD30_NBYTES_MLNO		(IMXRT_DMA_TCD[30].NBYTES_MLNO)
#define DMA_TCD30_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[30].NBYTES_MLOFFNO)
#define DMA_TCD30_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[30].NBYTES_MLOFFYES)
#define DMA_TCD30_SLAST			(IMXRT_DMA_TCD[30].SLAST)
#define DMA_TCD30_DADDR			(IMXRT_DMA_TCD[30].DADDR)
#define DMA_TCD30_DOFF			(IMXRT_DMA_TCD[30].DOFF)
#define DMA_TCD30_CITER			(IMXRT_DMA_TCD[30].CITER)
#define DMA_TCD30_CITER_ELINKYES	(IMXRT_DMA_TCD[30].CITER_ELINKYES)
#define DMA_TCD30_CITER_ELINKNO		(IMXRT_DMA_TCD[30].CITER_ELINKNO)
#define DMA_TCD30_DLASTSGA		(IMXRT_DMA_TCD[30].DLASTSGA)
#define DMA_TCD30_CSR			(IMXRT_DMA_TCD[30].CSR)
#define DMA_TCD30_BITER			(IMXRT_DMA_TCD[30].BITER)
#define DMA_TCD30_BITER_ELINKYES	(IMXRT_DMA_TCD[30].BITER_ELINKYES)
#define DMA_TCD30_BITER_ELINKNO		(IMXRT_DMA_TCD[30].BITER_ELINKNO)

#define DMA_TCD31_SADDR			(IMXRT_DMA_TCD[31].SADDR)
#define DMA_TCD31_SOFF			(IMXRT_DMA_TCD[31].SOFF)
#define DMA_TCD31_ATTR			(IMXRT_DMA_TCD[31].ATTR)
#define DMA_TCD31_NBYTES		(IMXRT_DMA_TCD[31].NBYTES)
#define DMA_TCD31_NBYTES_MLNO		(IMXRT_DMA_TCD[31].NBYTES_MLNO)
#define DMA_TCD31_NBYTES_MLOFFNO	(IMXRT_DMA_TCD[31].NBYTES_MLOFFNO)
#define DMA_TCD31_NBYTES_MLOFFYES	(IMXRT_DMA_TCD[31].NBYTES_MLOFFYES)
#define DMA_TCD31_SLAST			(IMXRT_DMA_TCD[31].SLAST)
#define DMA_TCD31_DADDR			(IMXRT_DMA_TCD[31].DADDR)
#define DMA_TCD31_DOFF			(IMXRT_DMA_TCD[31].DOFF)
#define DMA_TCD31_CITER			(IMXRT_DMA_TCD[31].CITER)
#define DMA_TCD31_CITER_ELINKYES	(IMXRT_DMA_TCD[31].CITER_ELINKYES)
#define DMA_TCD31_CITER_ELINKNO		(IMXRT_DMA_TCD[31].CITER_ELINKNO)
#define DMA_TCD31_DLASTSGA		(IMXRT_DMA_TCD[31].DLASTSGA)
#define DMA_TCD31_CSR			(IMXRT_DMA_TCD[31].CSR)
#define DMA_TCD31_BITER			(IMXRT_DMA_TCD[31].BITER)
#define DMA_TCD31_BITER_ELINKYES	(IMXRT_DMA_TCD[31].BITER_ELINKYES)
#define DMA_TCD31_BITER_ELINKNO		(IMXRT_DMA_TCD[31].BITER_ELINKNO)

// TODO: double check these defines from Teensy 3.x are still correct for IMXRT
#define DMA_TCD_ATTR_SMOD(n)            (((n) & 0x1F) << 11)
#define DMA_TCD_ATTR_SSIZE(n)           (((n) & 0x7) << 8)
#define DMA_TCD_ATTR_DMOD(n)            (((n) & 0x1F) << 3)
#define DMA_TCD_ATTR_DSIZE(n)           (((n) & 0x7) << 0)
#define DMA_TCD_ATTR_SIZE_8BIT          0
#define DMA_TCD_ATTR_SIZE_16BIT         1
#define DMA_TCD_ATTR_SIZE_32BIT         2
#define DMA_TCD_ATTR_SIZE_64BIT         3
#define DMA_TCD_ATTR_SIZE_32BYTE        5
#define DMA_TCD_CSR_BWC(n)              (((n) & 0x3) << 14)
#define DMA_TCD_CSR_BWC_MASK            0xC000
#define DMA_TCD_CSR_MAJORLINKCH(n)      (((n) & 0x1F) << 8)
#define DMA_TCD_CSR_MAJORLINKCH_MASK    0x1F00
#define DMA_TCD_CSR_DONE                0x0080
#define DMA_TCD_CSR_ACTIVE              0x0040
#define DMA_TCD_CSR_MAJORELINK          0x0020
#define DMA_TCD_CSR_ESG                 0x0010
#define DMA_TCD_CSR_DREQ                0x0008
#define DMA_TCD_CSR_INTHALF             0x0004
#define DMA_TCD_CSR_INTMAJOR            0x0002
#define DMA_TCD_CSR_START               0x0001
#define DMA_TCD_CITER_MASK              ((uint16_t)0x7FFF)         // Loop count mask
#define DMA_TCD_CITER_ELINK             ((uint16_t)1<<15)          // Enable channel linking on minor-loop complete
#define DMA_TCD_BITER_MASK              ((uint16_t)0x7FFF)         // Loop count mask
#define DMA_TCD_BITER_ELINK             ((uint16_t)1<<15)          // Enable channel linking on minor-loop complete
#define DMA_TCD_BITER_ELINKYES_ELINK            0x8000
#define DMA_TCD_BITER_ELINKYES_LINKCH(n)        (((n) & 0x1F) << 9)
#define DMA_TCD_BITER_ELINKYES_LINKCH_MASK      0x3E00
#define DMA_TCD_BITER_ELINKYES_BITER(n)         (((n) & 0x1FF) << 0)
#define DMA_TCD_BITER_ELINKYES_BITER_MASK       0x01FF
#define DMA_TCD_CITER_ELINKYES_ELINK            0x8000
#define DMA_TCD_CITER_ELINKYES_LINKCH(n)        (((n) & 0x1F) << 9)
#define DMA_TCD_CITER_ELINKYES_LINKCH_MASK      0x3E00
#define DMA_TCD_CITER_ELINKYES_CITER(n)         (((n) & 0x1FF) << 0)
#define DMA_TCD_CITER_ELINKYES_CITER_MASK       0x01FF
#define DMA_TCD_NBYTES_SMLOE                ((uint32_t)1<<31)               // Source Minor Loop Offset Enable
#define DMA_TCD_NBYTES_DMLOE                ((uint32_t)1<<30)               // Destination Minor Loop Offset Enable
#define DMA_TCD_NBYTES_MLOFFNO_NBYTES(n)    ((uint32_t)((n) & 0x3FFFFFFF))  // NBytes transfer count when minor loop disabled
#define DMA_TCD_NBYTES_MLOFFYES_NBYTES(n)   ((uint32_t)((n) & 0x3FF))       // NBytes transfer count when minor loop enabled
#define DMA_TCD_NBYTES_MLOFFYES_MLOFF(n)    ((uint32_t)((n) & 0xFFFFF)<<10) // Minor loop offset


// 56.8.1: page 3151
typedef struct {
  volatile uint16_t CTRL;		/**< Control Register, offset: 0x0 */
  volatile uint16_t FILT;		/**< Input Filter Register, offset: 0x2 */
  volatile uint16_t WTR;		/**< Watchdog Timeout Register, offset: 0x4 */
  volatile uint16_t POSD;		/**< Position Difference Counter Register, offset: 0x6 */
  volatile uint16_t POSDH;		/**< Position Difference Hold Register, offset: 0x8 */
  volatile uint16_t REV;		/**< Revolution Counter Register, offset: 0xA */
  volatile uint16_t REVH;		/**< Revolution Hold Register, offset: 0xC */
  volatile uint16_t UPOS;		/**< Upper Position Counter Register, offset: 0xE */
  volatile uint16_t LPOS;		/**< Lower Position Counter Register, offset: 0x10 */
  volatile uint16_t UPOSH;		/**< Upper Position Hold Register, offset: 0x12 */
  volatile uint16_t LPOSH;		/**< Lower Position Hold Register, offset: 0x14 */
  volatile uint16_t UINIT;		/**< Upper Initialization Register, offset: 0x16 */
  volatile uint16_t LINIT;		/**< Lower Initialization Register, offset: 0x18 */
  volatile uint16_t IMR;		/**< Input Monitor Register, offset: 0x1A */
  volatile uint16_t TST;		/**< Test Register, offset: 0x1C */
  volatile uint16_t CTRL2;		/**< Control 2 Register, offset: 0x1E */
  volatile uint16_t UMOD;		/**< Upper Modulus Register, offset: 0x20 */
  volatile uint16_t LMOD;		/**< Lower Modulus Register, offset: 0x22 */
  volatile uint16_t UCOMP;		/**< Upper Position Compare Register, offset: 0x24 */
  volatile uint16_t LCOMP;		/**< Lower Position Compare Register, offset: 0x26 */
} IMXRT_ENC_t;


#define IMXRT_ENC1		(*(IMXRT_ENC_t *)IMXRT_ENC1_ADDRESS)
#define ENC1_CTRL			(IMXRT_ENC1.CTRL)
#define ENC1_FILT			(IMXRT_ENC1.FILT)
#define ENC1_WTR			(IMXRT_ENC1.WTR)
#define ENC1_POSD			(IMXRT_ENC1.POSD)
#define ENC1_POSDH			(IMXRT_ENC1.POSDH)
#define ENC1_REV			(IMXRT_ENC1.REV)
#define ENC1_REVH			(IMXRT_ENC1.REVH)
#define ENC1_UPOS			(IMXRT_ENC1.UPOS)
#define ENC1_LPOS			(IMXRT_ENC1.LPOS)
#define ENC1_UPOSH			(IMXRT_ENC1.UPOSH)
#define ENC1_LPOSH			(IMXRT_ENC1.LPOSH)
#define ENC1_UINIT			(IMXRT_ENC1.UINIT)
#define ENC1_LINIT			(IMXRT_ENC1.LINIT)
#define ENC1_IMR			(IMXRT_ENC1.IMR)
#define ENC1_TST			(IMXRT_ENC1.TST)
#define ENC1_CTRL2			(IMXRT_ENC1.CTRL2)
#define ENC1_UMOD			(IMXRT_ENC1.UMOD)
#define ENC1_LMOD			(IMXRT_ENC1.LMOD)
#define ENC1_UCOMP			(IMXRT_ENC1.UCOMP)
#define ENC1_LCOMP			(IMXRT_ENC1.LCOMP)
#define IMXRT_ENC2		(*(IMXRT_ENC_t *)IMXRT_ENC2_ADDRESS)
#define ENC2_CTRL			(IMXRT_ENC2.CTRL)
#define ENC2_FILT			(IMXRT_ENC2.FILT)
#define ENC2_WTR			(IMXRT_ENC2.WTR)
#define ENC2_POSD			(IMXRT_ENC2.POSD)
#define ENC2_POSDH			(IMXRT_ENC2.POSDH)
#define ENC2_REV			(IMXRT_ENC2.REV)
#define ENC2_REVH			(IMXRT_ENC2.REVH)
#define ENC2_UPOS			(IMXRT_ENC2.UPOS)
#define ENC2_LPOS			(IMXRT_ENC2.LPOS)
#define ENC2_UPOSH			(IMXRT_ENC2.UPOSH)
#define ENC2_LPOSH			(IMXRT_ENC2.LPOSH)
#define ENC2_UINIT			(IMXRT_ENC2.UINIT)
#define ENC2_LINIT			(IMXRT_ENC2.LINIT)
#define ENC2_IMR			(IMXRT_ENC2.IMR)
#define ENC2_TST			(IMXRT_ENC2.TST)
#define ENC2_CTRL2			(IMXRT_ENC2.CTRL2)
#define ENC2_UMOD			(IMXRT_ENC2.UMOD)
#define ENC2_LMOD			(IMXRT_ENC2.LMOD)
#define ENC2_UCOMP			(IMXRT_ENC2.UCOMP)
#define ENC2_LCOMP			(IMXRT_ENC2.LCOMP)
#define IMXRT_ENC3		(*(IMXRT_ENC_t *)IMXRT_ENC3_ADDRESS)
#define ENC3_CTRL			(IMXRT_ENC3.CTRL)
#define ENC3_FILT			(IMXRT_ENC3.FILT)
#define ENC3_WTR			(IMXRT_ENC3.WTR)
#define ENC3_POSD			(IMXRT_ENC3.POSD)
#define ENC3_POSDH			(IMXRT_ENC3.POSDH)
#define ENC3_REV			(IMXRT_ENC3.REV)
#define ENC3_REVH			(IMXRT_ENC3.REVH)
#define ENC3_UPOS			(IMXRT_ENC3.UPOS)
#define ENC3_LPOS			(IMXRT_ENC3.LPOS)
#define ENC3_UPOSH			(IMXRT_ENC3.UPOSH)
#define ENC3_LPOSH			(IMXRT_ENC3.LPOSH)
#define ENC3_UINIT			(IMXRT_ENC3.UINIT)
#define ENC3_LINIT			(IMXRT_ENC3.LINIT)
#define ENC3_IMR			(IMXRT_ENC3.IMR)
#define ENC3_TST			(IMXRT_ENC3.TST)
#define ENC3_CTRL2			(IMXRT_ENC3.CTRL2)
#define ENC3_UMOD			(IMXRT_ENC3.UMOD)
#define ENC3_LMOD			(IMXRT_ENC3.LMOD)
#define ENC3_UCOMP			(IMXRT_ENC3.UCOMP)
#define ENC3_LCOMP			(IMXRT_ENC3.LCOMP)
#define IMXRT_ENC4		(*(IMXRT_ENC_t *)IMXRT_ENC4_ADDRESS)
#define ENC4_CTRL			(IMXRT_ENC4.CTRL)
#define ENC4_FILT			(IMXRT_ENC4.FILT)
#define ENC4_WTR			(IMXRT_ENC4.WTR)
#define ENC4_POSD			(IMXRT_ENC4.POSD)
#define ENC4_POSDH			(IMXRT_ENC4.POSDH)
#define ENC4_REV			(IMXRT_ENC4.REV)
#define ENC4_REVH			(IMXRT_ENC4.REVH)
#define ENC4_UPOS			(IMXRT_ENC4.UPOS)
#define ENC4_LPOS			(IMXRT_ENC4.LPOS)
#define ENC4_UPOSH			(IMXRT_ENC4.UPOSH)
#define ENC4_LPOSH			(IMXRT_ENC4.LPOSH)
#define ENC4_UINIT			(IMXRT_ENC4.UINIT)
#define ENC4_LINIT			(IMXRT_ENC4.LINIT)
#define ENC4_IMR			(IMXRT_ENC4.IMR)
#define ENC4_TST			(IMXRT_ENC4.TST)
#define ENC4_CTRL2			(IMXRT_ENC4.CTRL2)
#define ENC4_UMOD			(IMXRT_ENC4.UMOD)
#define ENC4_LMOD			(IMXRT_ENC4.LMOD)
#define ENC4_UCOMP			(IMXRT_ENC4.UCOMP)
#define ENC4_LCOMP			(IMXRT_ENC4.LCOMP)

// 41.6: page 2068
#define IMXRT_ENET		(*(IMXRT_REGISTER32_t *)IMXRT_ENET_ADDRESS)
#define IMXRT_ENET_TIMER	(*(IMXRT_REGISTER32_t *)(IMXRT_ENET_ADDRESS+0x400))
#define ENET_EIR			(IMXRT_ENET.offset004)
#define ENET_EIMR			(IMXRT_ENET.offset008)
#define ENET_RDAR			(IMXRT_ENET.offset010)
#define ENET_TDAR			(IMXRT_ENET.offset014)
#define ENET_ECR			(IMXRT_ENET.offset024)
#define ENET_MMFR			(IMXRT_ENET.offset040)
#define ENET_MSCR			(IMXRT_ENET.offset044)
#define ENET_MIBC			(IMXRT_ENET.offset064)
#define ENET_RCR			(IMXRT_ENET.offset084)
#define ENET_TCR			(IMXRT_ENET.offset0C4)
#define ENET_PALR			(IMXRT_ENET.offset0E4)
#define ENET_PAUR			(IMXRT_ENET.offset0E8)
#define ENET_OPD			(IMXRT_ENET.offset0EC)
#define ENET_TXIC			(IMXRT_ENET.offset0F0)
#define ENET_RXIC			(IMXRT_ENET.offset100)
#define ENET_IAUR			(IMXRT_ENET.offset118)
#define ENET_IALR			(IMXRT_ENET.offset11C)
#define ENET_GAUR			(IMXRT_ENET.offset120)
#define ENET_GALR			(IMXRT_ENET.offset124)
#define ENET_TFWR			(IMXRT_ENET.offset144)
#define ENET_RDSR			(IMXRT_ENET.offset180)
#define ENET_TDSR			(IMXRT_ENET.offset184)
#define ENET_MRBR			(IMXRT_ENET.offset188)
#define ENET_RSFL			(IMXRT_ENET.offset190)
#define ENET_RSEM			(IMXRT_ENET.offset194)
#define ENET_RAEM			(IMXRT_ENET.offset198)
#define ENET_RAFL			(IMXRT_ENET.offset19C)
#define ENET_TSEM			(IMXRT_ENET.offset1A0)
#define ENET_TAEM			(IMXRT_ENET.offset1A4)
#define ENET_TAFL			(IMXRT_ENET.offset1A8)
#define ENET_TIPG			(IMXRT_ENET.offset1AC)
#define ENET_FTRL			(IMXRT_ENET.offset1B0)
#define ENET_TACC			(IMXRT_ENET.offset1C0)
#define ENET_RACC			(IMXRT_ENET.offset1C4)
#define ENET_RMON_T_DROP		(IMXRT_ENET.offset200)
#define ENET_RMON_T_PACKETS		(IMXRT_ENET.offset204)
#define ENET_RMON_T_BC_PKT		(IMXRT_ENET.offset208)
#define ENET_RMON_T_MC_PKT		(IMXRT_ENET.offset20C)
#define ENET_RMON_T_CRC_ALIGN		(IMXRT_ENET.offset210)
#define ENET_RMON_T_UNDERSIZE		(IMXRT_ENET.offset214)
#define ENET_RMON_T_OVERSIZE		(IMXRT_ENET.offset218)
#define ENET_RMON_T_FRAG		(IMXRT_ENET.offset21C)
#define ENET_RMON_T_JAB			(IMXRT_ENET.offset220)
#define ENET_RMON_T_COL			(IMXRT_ENET.offset224)
#define ENET_RMON_T_P64			(IMXRT_ENET.offset228)
#define ENET_RMON_T_P65TO127		(IMXRT_ENET.offset22C)
#define ENET_RMON_T_P128TO255		(IMXRT_ENET.offset230)
#define ENET_RMON_T_P256TO511		(IMXRT_ENET.offset234)
#define ENET_RMON_T_P512TO1023		(IMXRT_ENET.offset238)
#define ENET_RMON_T_P1024TO2047		(IMXRT_ENET.offset23C)
#define ENET_RMON_T_P_GTE2048		(IMXRT_ENET.offset240)
#define ENET_RMON_T_OCTETS		(IMXRT_ENET.offset244)
#define ENET_IEEE_T_DROP		(IMXRT_ENET.offset248)
#define ENET_IEEE_T_FRAME_OK		(IMXRT_ENET.offset24C)
#define ENET_IEEE_T_1COL		(IMXRT_ENET.offset250)
#define ENET_IEEE_T_MCOL		(IMXRT_ENET.offset254)
#define ENET_IEEE_T_DEF			(IMXRT_ENET.offset258)
#define ENET_IEEE_T_LCOL		(IMXRT_ENET.offset25C)
#define ENET_IEEE_T_EXCOL		(IMXRT_ENET.offset260)
#define ENET_IEEE_T_MACERR		(IMXRT_ENET.offset264)
#define ENET_IEEE_T_CSERR		(IMXRT_ENET.offset268)
#define ENET_IEEE_T_SQE			(IMXRT_ENET.offset26C)
#define ENET_IEEE_T_FDXFC		(IMXRT_ENET.offset270)
#define ENET_IEEE_T_OCTETS_OK		(IMXRT_ENET.offset274)
#define ENET_RMON_R_PACKETS		(IMXRT_ENET.offset284)
#define ENET_RMON_R_BC_PKT		(IMXRT_ENET.offset288)
#define ENET_RMON_R_MC_PKT		(IMXRT_ENET.offset28C)
#define ENET_RMON_R_CRC_ALIGN		(IMXRT_ENET.offset290)
#define ENET_RMON_R_UNDERSIZE		(IMXRT_ENET.offset294)
#define ENET_RMON_R_OVERSIZE		(IMXRT_ENET.offset298)
#define ENET_RMON_R_FRAG		(IMXRT_ENET.offset29C)
#define ENET_RMON_R_JAB			(IMXRT_ENET.offset2A0)
#define ENET_RMON_R_RESVD_0		(IMXRT_ENET.offset2A4)
#define ENET_RMON_R_P64			(IMXRT_ENET.offset2A8)
#define ENET_RMON_R_P65TO127		(IMXRT_ENET.offset2AC)
#define ENET_RMON_R_P128TO255		(IMXRT_ENET.offset2B0)
#define ENET_RMON_R_P256TO511		(IMXRT_ENET.offset2B4)
#define ENET_RMON_R_P512TO1023		(IMXRT_ENET.offset2B8)
#define ENET_RMON_R_P1024TO2047		(IMXRT_ENET.offset2BC)
#define ENET_RMON_R_P_GTE2048		(IMXRT_ENET.offset2C0)
#define ENET_RMON_R_OCTETS		(IMXRT_ENET.offset2C4)
#define ENET_IEEE_R_DROP		(IMXRT_ENET.offset2C8)
#define ENET_IEEE_R_FRAME_OK		(IMXRT_ENET.offset2CC)
#define ENET_IEEE_R_CRC			(IMXRT_ENET.offset2D0)
#define ENET_IEEE_R_ALIGN		(IMXRT_ENET.offset2D4)
#define ENET_IEEE_R_MACERR		(IMXRT_ENET.offset2D8)
#define ENET_IEEE_R_FDXFC		(IMXRT_ENET.offset2DC)
#define ENET_IEEE_R_OCTETS_OK		(IMXRT_ENET.offset2E0)
#define ENET_ATCR			(IMXRT_ENET_TIMER.offset000)
#define ENET_ATVR			(IMXRT_ENET_TIMER.offset004)
#define ENET_ATOFF			(IMXRT_ENET_TIMER.offset008)
#define ENET_ATPER			(IMXRT_ENET_TIMER.offset00C)
#define ENET_ATCOR			(IMXRT_ENET_TIMER.offset010)
#define ENET_ATINC			(IMXRT_ENET_TIMER.offset014)
#define ENET_ATSTMP			(IMXRT_ENET_TIMER.offset018)
#define ENET_TGSR			(IMXRT_ENET_TIMER.offset204)
#define ENET_TCSR0			(IMXRT_ENET_TIMER.offset208)
#define ENET_TCCR0			(IMXRT_ENET_TIMER.offset20C)
#define ENET_TCSR1			(IMXRT_ENET_TIMER.offset210)
#define ENET_TCCR1			(IMXRT_ENET_TIMER.offset214)
#define ENET_TCSR2			(IMXRT_ENET_TIMER.offset218)
#define ENET_TCCR2			(IMXRT_ENET_TIMER.offset21C)
#define ENET_TCSR3			(IMXRT_ENET_TIMER.offset220)
#define ENET_TCCR3			(IMXRT_ENET_TIMER.offset224)
#define ENET_EIR_BABR				((uint32_t)(1<<30))
#define ENET_EIR_BABT				((uint32_t)(1<<29))
#define ENET_EIR_GRA				((uint32_t)(1<<28))
#define ENET_EIR_TXF				((uint32_t)(1<<27))
#define ENET_EIR_TXB				((uint32_t)(1<<26))
#define ENET_EIR_RXF				((uint32_t)(1<<25))
#define ENET_EIR_RXB				((uint32_t)(1<<24))
#define ENET_EIR_MII				((uint32_t)(1<<23))
#define ENET_EIR_EBERR				((uint32_t)(1<<22))
#define ENET_EIR_LC				((uint32_t)(1<<21))
#define ENET_EIR_RL				((uint32_t)(1<<20))
#define ENET_EIR_UN				((uint32_t)(1<<19))
#define ENET_EIR_PLR				((uint32_t)(1<<18))
#define ENET_EIR_WAKEUP				((uint32_t)(1<<17))
#define ENET_EIR_TS_AVAIL			((uint32_t)(1<<16))
#define ENET_EIR_TS_TIMER			((uint32_t)(1<<15))
#define ENET_EIMR_BABR				((uint32_t)(1<<30))
#define ENET_EIMR_BABT				((uint32_t)(1<<29))
#define ENET_EIMR_GRA				((uint32_t)(1<<28))
#define ENET_EIMR_TXF				((uint32_t)(1<<27))
#define ENET_EIMR_TXB				((uint32_t)(1<<26))
#define ENET_EIMR_RXF				((uint32_t)(1<<25))
#define ENET_EIMR_RXB				((uint32_t)(1<<24))
#define ENET_EIMR_MII				((uint32_t)(1<<23))
#define ENET_EIMR_EBERR				((uint32_t)(1<<22))
#define ENET_EIMR_LC				((uint32_t)(1<<21))
#define ENET_EIMR_RL				((uint32_t)(1<<20))
#define ENET_EIMR_UN				((uint32_t)(1<<19))
#define ENET_EIMR_PLR				((uint32_t)(1<<18))
#define ENET_EIMR_WAKEUP			((uint32_t)(1<<17))
#define ENET_EIMR_TS_AVAIL			((uint32_t)(1<<16))
#define ENET_EIMR_TS_TIMER			((uint32_t)(1<<15))
#define ENET_RDAR_RDAR				((uint32_t)(1<<24))
#define ENET_TDAR_TDAR				((uint32_t)(1<<24))
#define ENET_ECR_DBSWP				((uint32_t)(1<<8))
#define ENET_ECR_DBGEN				((uint32_t)(1<<6))
#define ENET_ECR_EN1588				((uint32_t)(1<<4))
#define ENET_ECR_SLEEP				((uint32_t)(1<<3))
#define ENET_ECR_MAGICEN			((uint32_t)(1<<2))
#define ENET_ECR_ETHEREN			((uint32_t)(1<<1))
#define ENET_ECR_RESET				((uint32_t)(1<<0))
#define ENET_MMFR_ST(n)				((uint32_t)(((n) & 0x03) << 30))
#define ENET_MMFR_OP(n)				((uint32_t)(((n) & 0x03) << 28))
#define ENET_MMFR_PA(n)				((uint32_t)(((n) & 0x1F) << 23))
#define ENET_MMFR_RA(n)				((uint32_t)(((n) & 0x1F) << 18))
#define ENET_MMFR_TA(n)				((uint32_t)(((n) & 0x03) << 16))
#define ENET_MMFR_DATA(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define ENET_MSCR_HOLDTIME(n)			((uint32_t)(((n) & 0x07) << 8))
#define ENET_MSCR_DIS_PRE			((uint32_t)(1<<7))
#define ENET_MSCR_MII_SPEED(n)			((uint32_t)(((n) & 0x3F) << 1))
#define ENET_MIBC_MIB_DIS			((uint32_t)(1<<31))
#define ENET_MIBC_MIB_IDLE			((uint32_t)(1<<30))
#define ENET_MIBC_MIB_CLEAR			((uint32_t)(1<<29))
#define ENET_RCR_GRS				((uint32_t)(1<<31))
#define ENET_RCR_NLC				((uint32_t)(1<<30))
#define ENET_RCR_MAX_FL(n)			((uint32_t)(((n) & 0x3FFF) << 16))
#define ENET_RCR_CFEN				((uint32_t)(1<<15))
#define ENET_RCR_CRCFWD				((uint32_t)(1<<14))
#define ENET_RCR_PAUFWD				((uint32_t)(1<<13))
#define ENET_RCR_PADEN				((uint32_t)(1<<12))
#define ENET_RCR_RMII_10T			((uint32_t)(1<<9))
#define ENET_RCR_RMII_MODE			((uint32_t)(1<<8))
#define ENET_RCR_FCE				((uint32_t)(1<<5))
#define ENET_RCR_BC_REJ				((uint32_t)(1<<4))
#define ENET_RCR_PROM				((uint32_t)(1<<3))
#define ENET_RCR_MII_MODE			((uint32_t)(1<<2))
#define ENET_RCR_DRT				((uint32_t)(1<<1))
#define ENET_RCR_LOOP				((uint32_t)(1<<0))
#define ENET_TCR_CRCFWD				((uint32_t)(1<<9))
#define ENET_TCR_ADDINS				((uint32_t)(1<<8))
#define ENET_TCR_ADDSEL(n)			((uint32_t)(((n) & 0x07) << 5))
#define ENET_TCR_RFC_PAUSE			((uint32_t)(1<<4))
#define ENET_TCR_TFC_PAUSE			((uint32_t)(1<<3))
#define ENET_TCR_FDEN				((uint32_t)(1<<2))
#define ENET_TCR_GTS				((uint32_t)(1<<0))
#define ENET_PAUR_PADDR2(n)			((uint32_t)(((n) & 0xFFFF) << 16))
#define ENET_PAUR_TYPE(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define ENET_OPD_OPCODE(n)			((uint32_t)(((n) & 0xFFFF) << 16))
#define ENET_OPD_PAUSE_DUR(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define ENET_TXIC_ICEN				((uint32_t)(1<<31))
#define ENET_TXIC_ICCS				((uint32_t)(1<<30))
#define ENET_TXIC_ICFT(n)			((uint32_t)(((n) & 0xFF) << 20))
#define ENET_TXIC_ICTT(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define ENET_RXIC_ICEN				((uint32_t)(1<<31))
#define ENET_RXIC_ICCS				((uint32_t)(1<<30))
#define ENET_RXIC_ICFT(n)			((uint32_t)(((n) & 0xFF) << 20))
#define ENET_RXIC_ICTT(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define ENET_TFWR_STRFWD			((uint32_t)(1<<8))
#define ENET_TFWR_TFWR(n)			((uint32_t)(((n) & 0x3F) << 0))
#define ENET_TACC_PROCHK			((uint32_t)(1<<4))
#define ENET_TACC_IPCHK				((uint32_t)(1<<3))
#define ENET_TACC_SHIFT16			((uint32_t)(1<<0))
#define ENET_RACC_SHIFT16			((uint32_t)(1<<7))
#define ENET_RACC_LINEDIS			((uint32_t)(1<<6))
#define ENET_RACC_PRODIS			((uint32_t)(1<<2))
#define ENET_RACC_IPDIS				((uint32_t)(1<<1))
#define ENET_RACC_PADREM			((uint32_t)(1<<0))

#define IMXRT_ENET2		(*(IMXRT_REGISTER32_t *)IMXRT_ENET2_ADDRESS)
#define IMXRT_ENET2_TIMER	(*(IMXRT_REGISTER32_t *)(IMXRT_ENET2_ADDRESS+0x400))
#define ENET2_EIR			(IMXRT_ENET2.offset004)
#define ENET2_EIMR			(IMXRT_ENET2.offset008)
#define ENET2_RDAR			(IMXRT_ENET2.offset010)
#define ENET2_TDAR			(IMXRT_ENET2.offset014)
#define ENET2_ECR			(IMXRT_ENET2.offset024)
#define ENET2_MMFR			(IMXRT_ENET2.offset040)
#define ENET2_MSCR			(IMXRT_ENET2.offset044)
#define ENET2_MIBC			(IMXRT_ENET2.offset064)
#define ENET2_RCR			(IMXRT_ENET2.offset084)
#define ENET2_TCR			(IMXRT_ENET2.offset0C4)
#define ENET2_PALR			(IMXRT_ENET2.offset0E4)
#define ENET2_PAUR			(IMXRT_ENET2.offset0E8)
#define ENET2_OPD			(IMXRT_ENET2.offset0EC)
#define ENET2_TXIC			(IMXRT_ENET2.offset0F0)
#define ENET2_RXIC			(IMXRT_ENET2.offset100)
#define ENET2_IAUR			(IMXRT_ENET2.offset118)
#define ENET2_IALR			(IMXRT_ENET2.offset11C)
#define ENET2_GAUR			(IMXRT_ENET2.offset120)
#define ENET2_GALR			(IMXRT_ENET2.offset124)
#define ENET2_TFWR			(IMXRT_ENET2.offset144)
#define ENET2_RDSR			(IMXRT_ENET2.offset180)
#define ENET2_TDSR			(IMXRT_ENET2.offset184)
#define ENET2_MRBR			(IMXRT_ENET2.offset188)
#define ENET2_RSFL			(IMXRT_ENET2.offset190)
#define ENET2_RSEM			(IMXRT_ENET2.offset194)
#define ENET2_RAEM			(IMXRT_ENET2.offset198)
#define ENET2_RAFL			(IMXRT_ENET2.offset19C)
#define ENET2_TSEM			(IMXRT_ENET2.offset1A0)
#define ENET2_TAEM			(IMXRT_ENET2.offset1A4)
#define ENET2_TAFL			(IMXRT_ENET2.offset1A8)
#define ENET2_TIPG			(IMXRT_ENET2.offset1AC)
#define ENET2_FTRL			(IMXRT_ENET2.offset1B0)
#define ENET2_TACC			(IMXRT_ENET2.offset1C0)
#define ENET2_RACC			(IMXRT_ENET2.offset1C4)
#define ENET2_RMON_T_DROP		(IMXRT_ENET2.offset200)
#define ENET2_RMON_T_PACKETS		(IMXRT_ENET2.offset204)
#define ENET2_RMON_T_BC_PKT		(IMXRT_ENET2.offset208)
#define ENET2_RMON_T_MC_PKT		(IMXRT_ENET2.offset20C)
#define ENET2_RMON_T_CRC_ALIGN		(IMXRT_ENET2.offset210)
#define ENET2_RMON_T_UNDERSIZE		(IMXRT_ENET2.offset214)
#define ENET2_RMON_T_OVERSIZE		(IMXRT_ENET2.offset218)
#define ENET2_RMON_T_FRAG		(IMXRT_ENET2.offset21C)
#define ENET2_RMON_T_JAB		(IMXRT_ENET2.offset220)
#define ENET2_RMON_T_COL		(IMXRT_ENET2.offset224)
#define ENET2_RMON_T_P64		(IMXRT_ENET2.offset228)
#define ENET2_RMON_T_P65TO127		(IMXRT_ENET2.offset22C)
#define ENET2_RMON_T_P128TO255		(IMXRT_ENET2.offset230)
#define ENET2_RMON_T_P256TO511		(IMXRT_ENET2.offset234)
#define ENET2_RMON_T_P512TO1023		(IMXRT_ENET2.offset238)
#define ENET2_RMON_T_P1024TO2047	(IMXRT_ENET2.offset23C)
#define ENET2_RMON_T_P_GTE2048		(IMXRT_ENET2.offset240)
#define ENET2_RMON_T_OCTETS		(IMXRT_ENET2.offset244)
#define ENET2_IEEE_T_DROP		(IMXRT_ENET2.offset248)
#define ENET2_IEEE_T_FRAME_OK		(IMXRT_ENET2.offset24C)
#define ENET2_IEEE_T_1COL		(IMXRT_ENET2.offset250)
#define ENET2_IEEE_T_MCOL		(IMXRT_ENET2.offset254)
#define ENET2_IEEE_T_DEF		(IMXRT_ENET2.offset258)
#define ENET2_IEEE_T_LCOL		(IMXRT_ENET2.offset25C)
#define ENET2_IEEE_T_EXCOL		(IMXRT_ENET2.offset260)
#define ENET2_IEEE_T_MACERR		(IMXRT_ENET2.offset264)
#define ENET2_IEEE_T_CSERR		(IMXRT_ENET2.offset268)
#define ENET2_IEEE_T_SQE		(IMXRT_ENET2.offset26C)
#define ENET2_IEEE_T_FDXFC		(IMXRT_ENET2.offset270)
#define ENET2_IEEE_T_OCTETS_OK		(IMXRT_ENET2.offset274)
#define ENET2_RMON_R_PACKETS		(IMXRT_ENET2.offset284)
#define ENET2_RMON_R_BC_PKT		(IMXRT_ENET2.offset288)
#define ENET2_RMON_R_MC_PKT		(IMXRT_ENET2.offset28C)
#define ENET2_RMON_R_CRC_ALIGN		(IMXRT_ENET2.offset290)
#define ENET2_RMON_R_UNDERSIZE		(IMXRT_ENET2.offset294)
#define ENET2_RMON_R_OVERSIZE		(IMXRT_ENET2.offset298)
#define ENET2_RMON_R_FRAG		(IMXRT_ENET2.offset29C)
#define ENET2_RMON_R_JAB		(IMXRT_ENET2.offset2A0)
#define ENET2_RMON_R_RESVD_0		(IMXRT_ENET2.offset2A4)
#define ENET2_RMON_R_P64		(IMXRT_ENET2.offset2A8)
#define ENET2_RMON_R_P65TO127		(IMXRT_ENET2.offset2AC)
#define ENET2_RMON_R_P128TO255		(IMXRT_ENET2.offset2B0)
#define ENET2_RMON_R_P256TO511		(IMXRT_ENET2.offset2B4)
#define ENET2_RMON_R_P512TO1023		(IMXRT_ENET2.offset2B8)
#define ENET2_RMON_R_P1024TO2047	(IMXRT_ENET2.offset2BC)
#define ENET2_RMON_R_P_GTE2048		(IMXRT_ENET2.offset2C0)
#define ENET2_RMON_R_OCTETS		(IMXRT_ENET2.offset2C4)
#define ENET2_IEEE_R_DROP		(IMXRT_ENET2.offset2C8)
#define ENET2_IEEE_R_FRAME_OK		(IMXRT_ENET2.offset2CC)
#define ENET2_IEEE_R_CRC		(IMXRT_ENET2.offset2D0)
#define ENET2_IEEE_R_ALIGN		(IMXRT_ENET2.offset2D4)
#define ENET2_IEEE_R_MACERR		(IMXRT_ENET2.offset2D8)
#define ENET2_IEEE_R_FDXFC		(IMXRT_ENET2.offset2DC)
#define ENET2_IEEE_R_OCTETS_OK		(IMXRT_ENET2.offset2E0)
#define ENET2_ATCR			(IMXRT_ENET2_TIMER.offset000)
#define ENET2_ATVR			(IMXRT_ENET2_TIMER.offset004)
#define ENET2_ATOFF			(IMXRT_ENET2_TIMER.offset008)
#define ENET2_ATPER			(IMXRT_ENET2_TIMER.offset00C)
#define ENET2_ATCOR			(IMXRT_ENET2_TIMER.offset010)
#define ENET2_ATINC			(IMXRT_ENET2_TIMER.offset014)
#define ENET2_ATSTMP			(IMXRT_ENET2_TIMER.offset018)
#define ENET2_TGSR			(IMXRT_ENET2_TIMER.offset204)
#define ENET2_TCSR0			(IMXRT_ENET2_TIMER.offset208)
#define ENET2_TCCR0			(IMXRT_ENET2_TIMER.offset20C)
#define ENET2_TCSR1			(IMXRT_ENET2_TIMER.offset210)
#define ENET2_TCCR1			(IMXRT_ENET2_TIMER.offset214)
#define ENET2_TCSR2			(IMXRT_ENET2_TIMER.offset218)
#define ENET2_TCCR2			(IMXRT_ENET2_TIMER.offset21C)
#define ENET2_TCSR3			(IMXRT_ENET2_TIMER.offset220)
#define ENET2_TCCR3			(IMXRT_ENET2_TIMER.offset224)

// 59.6.1.1: page 3221
#define IMXRT_EWM		(*(IMXRT_REGISTER8_t *)IMXRT_EWM_ADDRESS)
#define EWM_CTRL			(IMXRT_EWM.offset00)
#define EWM_SERV			(IMXRT_EWM.offset01)
#define EWM_CMPL			(IMXRT_EWM.offset02)
#define EWM_CMPH			(IMXRT_EWM.offset03)
#define EWM_CLKCTRL			(IMXRT_EWM.offset04)
#define EWM_CLKPRESCALER		(IMXRT_EWM.offset05)

// 44.9: page 2555
#define IMXRT_FLEXCAN1		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXCAN1_ADDRESS)
#define IMXRT_FLEXCAN1_MASK	(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXCAN1_ADDRESS+0x800))
#define FLEXCAN1_MCR			(IMXRT_FLEXCAN1.offset000)
#define FLEXCAN1_CTRL1			(IMXRT_FLEXCAN1.offset004)
#define FLEXCAN1_TIMER			(IMXRT_FLEXCAN1.offset008)
#define FLEXCAN1_RXMGMASK		(IMXRT_FLEXCAN1.offset010)
#define FLEXCAN1_RX14MASK		(IMXRT_FLEXCAN1.offset014)
#define FLEXCAN1_RX15MASK		(IMXRT_FLEXCAN1.offset018)
#define FLEXCAN1_ECR			(IMXRT_FLEXCAN1.offset01C)
#define FLEXCAN1_ESR1			(IMXRT_FLEXCAN1.offset020)
#define FLEXCAN1_IMASK2			(IMXRT_FLEXCAN1.offset024)
#define FLEXCAN1_IMASK1			(IMXRT_FLEXCAN1.offset028)
#define FLEXCAN1_IFLAG2			(IMXRT_FLEXCAN1.offset02C)
#define FLEXCAN1_IFLAG1			(IMXRT_FLEXCAN1.offset030)
#define FLEXCAN1_CTRL2			(IMXRT_FLEXCAN1.offset034)
#define FLEXCAN1_ESR2			(IMXRT_FLEXCAN1.offset038)
#define FLEXCAN1_CRCR			(IMXRT_FLEXCAN1.offset044)
#define FLEXCAN1_RXFGMASK		(IMXRT_FLEXCAN1.offset048)
#define FLEXCAN1_RXFIR			(IMXRT_FLEXCAN1.offset04C)
#define FLEXCAN1_RXIMR0			(IMXRT_FLEXCAN1_MASK.offset080)
#define FLEXCAN1_RXIMR1			(IMXRT_FLEXCAN1_MASK.offset084)
#define FLEXCAN1_RXIMR2			(IMXRT_FLEXCAN1_MASK.offset088)
#define FLEXCAN1_RXIMR3			(IMXRT_FLEXCAN1_MASK.offset08C)
#define FLEXCAN1_RXIMR4			(IMXRT_FLEXCAN1_MASK.offset090)
#define FLEXCAN1_RXIMR5			(IMXRT_FLEXCAN1_MASK.offset094)
#define FLEXCAN1_RXIMR6			(IMXRT_FLEXCAN1_MASK.offset098)
#define FLEXCAN1_RXIMR7			(IMXRT_FLEXCAN1_MASK.offset09C)
#define FLEXCAN1_RXIMR8			(IMXRT_FLEXCAN1_MASK.offset0A0)
#define FLEXCAN1_RXIMR9			(IMXRT_FLEXCAN1_MASK.offset0A4)
#define FLEXCAN1_RXIMR10		(IMXRT_FLEXCAN1_MASK.offset0A8)
#define FLEXCAN1_RXIMR11		(IMXRT_FLEXCAN1_MASK.offset0AC)
#define FLEXCAN1_RXIMR12		(IMXRT_FLEXCAN1_MASK.offset0B0)
#define FLEXCAN1_RXIMR13		(IMXRT_FLEXCAN1_MASK.offset0B4)
#define FLEXCAN1_RXIMR14		(IMXRT_FLEXCAN1_MASK.offset0B8)
#define FLEXCAN1_RXIMR15		(IMXRT_FLEXCAN1_MASK.offset0BC)
#define FLEXCAN1_RXIMR16		(IMXRT_FLEXCAN1_MASK.offset0C0)
#define FLEXCAN1_RXIMR17		(IMXRT_FLEXCAN1_MASK.offset0C4)
#define FLEXCAN1_RXIMR18		(IMXRT_FLEXCAN1_MASK.offset0C8)
#define FLEXCAN1_RXIMR19		(IMXRT_FLEXCAN1_MASK.offset0CC)
#define FLEXCAN1_RXIMR20		(IMXRT_FLEXCAN1_MASK.offset0D0)
#define FLEXCAN1_RXIMR21		(IMXRT_FLEXCAN1_MASK.offset0D4)
#define FLEXCAN1_RXIMR22		(IMXRT_FLEXCAN1_MASK.offset0D8)
#define FLEXCAN1_RXIMR23		(IMXRT_FLEXCAN1_MASK.offset0DC)
#define FLEXCAN1_RXIMR24		(IMXRT_FLEXCAN1_MASK.offset0E0)
#define FLEXCAN1_RXIMR25		(IMXRT_FLEXCAN1_MASK.offset0E4)
#define FLEXCAN1_RXIMR26		(IMXRT_FLEXCAN1_MASK.offset0E8)
#define FLEXCAN1_RXIMR27		(IMXRT_FLEXCAN1_MASK.offset0EC)
#define FLEXCAN1_RXIMR28		(IMXRT_FLEXCAN1_MASK.offset0F0)
#define FLEXCAN1_RXIMR29		(IMXRT_FLEXCAN1_MASK.offset0F4)
#define FLEXCAN1_RXIMR30		(IMXRT_FLEXCAN1_MASK.offset0F8)
#define FLEXCAN1_RXIMR31		(IMXRT_FLEXCAN1_MASK.offset0FC)
#define FLEXCAN1_RXIMR32		(IMXRT_FLEXCAN1_MASK.offset100)
#define FLEXCAN1_RXIMR33		(IMXRT_FLEXCAN1_MASK.offset104)
#define FLEXCAN1_RXIMR34		(IMXRT_FLEXCAN1_MASK.offset108)
#define FLEXCAN1_RXIMR35		(IMXRT_FLEXCAN1_MASK.offset10C)
#define FLEXCAN1_RXIMR36		(IMXRT_FLEXCAN1_MASK.offset110)
#define FLEXCAN1_RXIMR37		(IMXRT_FLEXCAN1_MASK.offset114)
#define FLEXCAN1_RXIMR38		(IMXRT_FLEXCAN1_MASK.offset118)
#define FLEXCAN1_RXIMR39		(IMXRT_FLEXCAN1_MASK.offset11C)
#define FLEXCAN1_RXIMR40		(IMXRT_FLEXCAN1_MASK.offset120)
#define FLEXCAN1_RXIMR41		(IMXRT_FLEXCAN1_MASK.offset124)
#define FLEXCAN1_RXIMR42		(IMXRT_FLEXCAN1_MASK.offset128)
#define FLEXCAN1_RXIMR43		(IMXRT_FLEXCAN1_MASK.offset12C)
#define FLEXCAN1_RXIMR44		(IMXRT_FLEXCAN1_MASK.offset130)
#define FLEXCAN1_RXIMR45		(IMXRT_FLEXCAN1_MASK.offset134)
#define FLEXCAN1_RXIMR46		(IMXRT_FLEXCAN1_MASK.offset138)
#define FLEXCAN1_RXIMR47		(IMXRT_FLEXCAN1_MASK.offset13C)
#define FLEXCAN1_RXIMR48		(IMXRT_FLEXCAN1_MASK.offset140)
#define FLEXCAN1_RXIMR49		(IMXRT_FLEXCAN1_MASK.offset144)
#define FLEXCAN1_RXIMR50		(IMXRT_FLEXCAN1_MASK.offset148)
#define FLEXCAN1_RXIMR51		(IMXRT_FLEXCAN1_MASK.offset14C)
#define FLEXCAN1_RXIMR52		(IMXRT_FLEXCAN1_MASK.offset150)
#define FLEXCAN1_RXIMR53		(IMXRT_FLEXCAN1_MASK.offset154)
#define FLEXCAN1_RXIMR54		(IMXRT_FLEXCAN1_MASK.offset158)
#define FLEXCAN1_RXIMR55		(IMXRT_FLEXCAN1_MASK.offset15C)
#define FLEXCAN1_RXIMR56		(IMXRT_FLEXCAN1_MASK.offset160)
#define FLEXCAN1_RXIMR57		(IMXRT_FLEXCAN1_MASK.offset164)
#define FLEXCAN1_RXIMR58		(IMXRT_FLEXCAN1_MASK.offset168)
#define FLEXCAN1_RXIMR59		(IMXRT_FLEXCAN1_MASK.offset16C)
#define FLEXCAN1_RXIMR60		(IMXRT_FLEXCAN1_MASK.offset170)
#define FLEXCAN1_RXIMR61		(IMXRT_FLEXCAN1_MASK.offset174)
#define FLEXCAN1_RXIMR62		(IMXRT_FLEXCAN1_MASK.offset178)
#define FLEXCAN1_RXIMR63		(IMXRT_FLEXCAN1_MASK.offset17C)
#define FLEXCAN1_GFWR			(IMXRT_FLEXCAN1_MASK.offset1E0)
#define IMXRT_FLEXCAN2		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXCAN2_ADDRESS)
#define IMXRT_FLEXCAN2_MASK	(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXCAN2_ADDRESS+0x800))
#define FLEXCAN2_MCR			(IMXRT_FLEXCAN2.offset000)
#define FLEXCAN2_CTRL1			(IMXRT_FLEXCAN2.offset004)
#define FLEXCAN2_TIMER			(IMXRT_FLEXCAN2.offset008)
#define FLEXCAN2_RXMGMASK		(IMXRT_FLEXCAN2.offset010)
#define FLEXCAN2_RX14MASK		(IMXRT_FLEXCAN2.offset014)
#define FLEXCAN2_RX15MASK		(IMXRT_FLEXCAN2.offset018)
#define FLEXCAN2_ECR			(IMXRT_FLEXCAN2.offset01C)
#define FLEXCAN2_ESR1			(IMXRT_FLEXCAN2.offset020)
#define FLEXCAN2_IMASK2			(IMXRT_FLEXCAN2.offset024)
#define FLEXCAN2_IMASK1			(IMXRT_FLEXCAN2.offset028)
#define FLEXCAN2_IFLAG2			(IMXRT_FLEXCAN2.offset02C)
#define FLEXCAN2_IFLAG1			(IMXRT_FLEXCAN2.offset030)
#define FLEXCAN2_CTRL2			(IMXRT_FLEXCAN2.offset034)
#define FLEXCAN2_ESR2			(IMXRT_FLEXCAN2.offset038)
#define FLEXCAN2_CRCR			(IMXRT_FLEXCAN2.offset044)
#define FLEXCAN2_RXFGMASK		(IMXRT_FLEXCAN2.offset048)
#define FLEXCAN2_RXFIR			(IMXRT_FLEXCAN2.offset04C)
#define FLEXCAN2_RXIMR0			(IMXRT_FLEXCAN2_MASK.offset080)
#define FLEXCAN2_RXIMR1			(IMXRT_FLEXCAN2_MASK.offset084)
#define FLEXCAN2_RXIMR2			(IMXRT_FLEXCAN2_MASK.offset088)
#define FLEXCAN2_RXIMR3			(IMXRT_FLEXCAN2_MASK.offset08C)
#define FLEXCAN2_RXIMR4			(IMXRT_FLEXCAN2_MASK.offset090)
#define FLEXCAN2_RXIMR5			(IMXRT_FLEXCAN2_MASK.offset094)
#define FLEXCAN2_RXIMR6			(IMXRT_FLEXCAN2_MASK.offset098)
#define FLEXCAN2_RXIMR7			(IMXRT_FLEXCAN2_MASK.offset09C)
#define FLEXCAN2_RXIMR8			(IMXRT_FLEXCAN2_MASK.offset0A0)
#define FLEXCAN2_RXIMR9			(IMXRT_FLEXCAN2_MASK.offset0A4)
#define FLEXCAN2_RXIMR10		(IMXRT_FLEXCAN2_MASK.offset0A8)
#define FLEXCAN2_RXIMR11		(IMXRT_FLEXCAN2_MASK.offset0AC)
#define FLEXCAN2_RXIMR12		(IMXRT_FLEXCAN2_MASK.offset0B0)
#define FLEXCAN2_RXIMR13		(IMXRT_FLEXCAN2_MASK.offset0B4)
#define FLEXCAN2_RXIMR14		(IMXRT_FLEXCAN2_MASK.offset0B8)
#define FLEXCAN2_RXIMR15		(IMXRT_FLEXCAN2_MASK.offset0BC)
#define FLEXCAN2_RXIMR16		(IMXRT_FLEXCAN2_MASK.offset0C0)
#define FLEXCAN2_RXIMR17		(IMXRT_FLEXCAN2_MASK.offset0C4)
#define FLEXCAN2_RXIMR18		(IMXRT_FLEXCAN2_MASK.offset0C8)
#define FLEXCAN2_RXIMR19		(IMXRT_FLEXCAN2_MASK.offset0CC)
#define FLEXCAN2_RXIMR20		(IMXRT_FLEXCAN2_MASK.offset0D0)
#define FLEXCAN2_RXIMR21		(IMXRT_FLEXCAN2_MASK.offset0D4)
#define FLEXCAN2_RXIMR22		(IMXRT_FLEXCAN2_MASK.offset0D8)
#define FLEXCAN2_RXIMR23		(IMXRT_FLEXCAN2_MASK.offset0DC)
#define FLEXCAN2_RXIMR24		(IMXRT_FLEXCAN2_MASK.offset0E0)
#define FLEXCAN2_RXIMR25		(IMXRT_FLEXCAN2_MASK.offset0E4)
#define FLEXCAN2_RXIMR26		(IMXRT_FLEXCAN2_MASK.offset0E8)
#define FLEXCAN2_RXIMR27		(IMXRT_FLEXCAN2_MASK.offset0EC)
#define FLEXCAN2_RXIMR28		(IMXRT_FLEXCAN2_MASK.offset0F0)
#define FLEXCAN2_RXIMR29		(IMXRT_FLEXCAN2_MASK.offset0F4)
#define FLEXCAN2_RXIMR30		(IMXRT_FLEXCAN2_MASK.offset0F8)
#define FLEXCAN2_RXIMR31		(IMXRT_FLEXCAN2_MASK.offset0FC)
#define FLEXCAN2_RXIMR32		(IMXRT_FLEXCAN2_MASK.offset100)
#define FLEXCAN2_RXIMR33		(IMXRT_FLEXCAN2_MASK.offset104)
#define FLEXCAN2_RXIMR34		(IMXRT_FLEXCAN2_MASK.offset108)
#define FLEXCAN2_RXIMR35		(IMXRT_FLEXCAN2_MASK.offset10C)
#define FLEXCAN2_RXIMR36		(IMXRT_FLEXCAN2_MASK.offset110)
#define FLEXCAN2_RXIMR37		(IMXRT_FLEXCAN2_MASK.offset114)
#define FLEXCAN2_RXIMR38		(IMXRT_FLEXCAN2_MASK.offset118)
#define FLEXCAN2_RXIMR39		(IMXRT_FLEXCAN2_MASK.offset11C)
#define FLEXCAN2_RXIMR40		(IMXRT_FLEXCAN2_MASK.offset120)
#define FLEXCAN2_RXIMR41		(IMXRT_FLEXCAN2_MASK.offset124)
#define FLEXCAN2_RXIMR42		(IMXRT_FLEXCAN2_MASK.offset128)
#define FLEXCAN2_RXIMR43		(IMXRT_FLEXCAN2_MASK.offset12C)
#define FLEXCAN2_RXIMR44		(IMXRT_FLEXCAN2_MASK.offset130)
#define FLEXCAN2_RXIMR45		(IMXRT_FLEXCAN2_MASK.offset134)
#define FLEXCAN2_RXIMR46		(IMXRT_FLEXCAN2_MASK.offset138)
#define FLEXCAN2_RXIMR47		(IMXRT_FLEXCAN2_MASK.offset13C)
#define FLEXCAN2_RXIMR48		(IMXRT_FLEXCAN2_MASK.offset140)
#define FLEXCAN2_RXIMR49		(IMXRT_FLEXCAN2_MASK.offset144)
#define FLEXCAN2_RXIMR50		(IMXRT_FLEXCAN2_MASK.offset148)
#define FLEXCAN2_RXIMR51		(IMXRT_FLEXCAN2_MASK.offset14C)
#define FLEXCAN2_RXIMR52		(IMXRT_FLEXCAN2_MASK.offset150)
#define FLEXCAN2_RXIMR53		(IMXRT_FLEXCAN2_MASK.offset154)
#define FLEXCAN2_RXIMR54		(IMXRT_FLEXCAN2_MASK.offset158)
#define FLEXCAN2_RXIMR55		(IMXRT_FLEXCAN2_MASK.offset15C)
#define FLEXCAN2_RXIMR56		(IMXRT_FLEXCAN2_MASK.offset160)
#define FLEXCAN2_RXIMR57		(IMXRT_FLEXCAN2_MASK.offset164)
#define FLEXCAN2_RXIMR58		(IMXRT_FLEXCAN2_MASK.offset168)
#define FLEXCAN2_RXIMR59		(IMXRT_FLEXCAN2_MASK.offset16C)
#define FLEXCAN2_RXIMR60		(IMXRT_FLEXCAN2_MASK.offset170)
#define FLEXCAN2_RXIMR61		(IMXRT_FLEXCAN2_MASK.offset174)
#define FLEXCAN2_RXIMR62		(IMXRT_FLEXCAN2_MASK.offset178)
#define FLEXCAN2_RXIMR63		(IMXRT_FLEXCAN2_MASK.offset17C)
#define FLEXCAN2_GFWR			(IMXRT_FLEXCAN2_MASK.offset1E0)

#define IMXRT_FLEXCAN3		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXCAN3_ADDRESS0)
#define IMXRT_FLEXCAN3_MASK	(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXCAN3_ADDRESS+0x800))
#define IMXRT_FLEXCAN3_EXT	(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXCAN3_ADDRESS+0xB00))
#define IMXRT_FLEXCAN3_ERXFIFO	(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXCAN3_ADDRESS+0x3000))
#define FLEXCAN3_MCR			(IMXRT_FLEXCAN3.offset000)
#define FLEXCAN3_CTRL1			(IMXRT_FLEXCAN3.offset004)
#define FLEXCAN3_TIMER			(IMXRT_FLEXCAN3.offset008)
#define FLEXCAN3_RXMGMASK		(IMXRT_FLEXCAN3.offset010)
#define FLEXCAN3_RX14MASK		(IMXRT_FLEXCAN3.offset014)
#define FLEXCAN3_RX15MASK		(IMXRT_FLEXCAN3.offset018)
#define FLEXCAN3_ECR			(IMXRT_FLEXCAN3.offset01C)
#define FLEXCAN3_ESR1			(IMXRT_FLEXCAN3.offset020)
#define FLEXCAN3_IMASK2			(IMXRT_FLEXCAN3.offset024)
#define FLEXCAN3_IMASK1			(IMXRT_FLEXCAN3.offset028)
#define FLEXCAN3_IFLAG2			(IMXRT_FLEXCAN3.offset02C)
#define FLEXCAN3_IFLAG1			(IMXRT_FLEXCAN3.offset030)
#define FLEXCAN3_CTRL2			(IMXRT_FLEXCAN3.offset034)
#define FLEXCAN3_ESR2			(IMXRT_FLEXCAN3.offset038)
#define FLEXCAN3_CRCR			(IMXRT_FLEXCAN3.offset044)
#define FLEXCAN3_RXFGMASK		(IMXRT_FLEXCAN3.offset048)
#define FLEXCAN3_RXFIR			(IMXRT_FLEXCAN3.offset04C)
#define FLEXCAN3_CBT			(IMXRT_FLEXCAN3.offset050)
#define FLEXCAN3_RXIMR0			(IMXRT_FLEXCAN3_MASK.offset080)
#define FLEXCAN3_RXIMR1			(IMXRT_FLEXCAN3_MASK.offset084)
#define FLEXCAN3_RXIMR2			(IMXRT_FLEXCAN3_MASK.offset088)
#define FLEXCAN3_RXIMR3			(IMXRT_FLEXCAN3_MASK.offset08C)
#define FLEXCAN3_RXIMR4			(IMXRT_FLEXCAN3_MASK.offset090)
#define FLEXCAN3_RXIMR5			(IMXRT_FLEXCAN3_MASK.offset094)
#define FLEXCAN3_RXIMR6			(IMXRT_FLEXCAN3_MASK.offset098)
#define FLEXCAN3_RXIMR7			(IMXRT_FLEXCAN3_MASK.offset09C)
#define FLEXCAN3_RXIMR8			(IMXRT_FLEXCAN3_MASK.offset0A0)
#define FLEXCAN3_RXIMR9			(IMXRT_FLEXCAN3_MASK.offset0A4)
#define FLEXCAN3_RXIMR10		(IMXRT_FLEXCAN3_MASK.offset0A8)
#define FLEXCAN3_RXIMR11		(IMXRT_FLEXCAN3_MASK.offset0AC)
#define FLEXCAN3_RXIMR12		(IMXRT_FLEXCAN3_MASK.offset0B0)
#define FLEXCAN3_RXIMR13		(IMXRT_FLEXCAN3_MASK.offset0B4)
#define FLEXCAN3_RXIMR14		(IMXRT_FLEXCAN3_MASK.offset0B8)
#define FLEXCAN3_RXIMR15		(IMXRT_FLEXCAN3_MASK.offset0BC)
#define FLEXCAN3_RXIMR16		(IMXRT_FLEXCAN3_MASK.offset0C0)
#define FLEXCAN3_RXIMR17		(IMXRT_FLEXCAN3_MASK.offset0C4)
#define FLEXCAN3_RXIMR18		(IMXRT_FLEXCAN3_MASK.offset0C8)
#define FLEXCAN3_RXIMR19		(IMXRT_FLEXCAN3_MASK.offset0CC)
#define FLEXCAN3_RXIMR20		(IMXRT_FLEXCAN3_MASK.offset0D0)
#define FLEXCAN3_RXIMR21		(IMXRT_FLEXCAN3_MASK.offset0D4)
#define FLEXCAN3_RXIMR22		(IMXRT_FLEXCAN3_MASK.offset0D8)
#define FLEXCAN3_RXIMR23		(IMXRT_FLEXCAN3_MASK.offset0DC)
#define FLEXCAN3_RXIMR24		(IMXRT_FLEXCAN3_MASK.offset0E0)
#define FLEXCAN3_RXIMR25		(IMXRT_FLEXCAN3_MASK.offset0E4)
#define FLEXCAN3_RXIMR26		(IMXRT_FLEXCAN3_MASK.offset0E8)
#define FLEXCAN3_RXIMR27		(IMXRT_FLEXCAN3_MASK.offset0EC)
#define FLEXCAN3_RXIMR28		(IMXRT_FLEXCAN3_MASK.offset0F0)
#define FLEXCAN3_RXIMR29		(IMXRT_FLEXCAN3_MASK.offset0F4)
#define FLEXCAN3_RXIMR30		(IMXRT_FLEXCAN3_MASK.offset0F8)
#define FLEXCAN3_RXIMR31		(IMXRT_FLEXCAN3_MASK.offset0FC)
#define FLEXCAN3_RXIMR32		(IMXRT_FLEXCAN3_MASK.offset100)
#define FLEXCAN3_RXIMR33		(IMXRT_FLEXCAN3_MASK.offset104)
#define FLEXCAN3_RXIMR34		(IMXRT_FLEXCAN3_MASK.offset108)
#define FLEXCAN3_RXIMR35		(IMXRT_FLEXCAN3_MASK.offset10C)
#define FLEXCAN3_RXIMR36		(IMXRT_FLEXCAN3_MASK.offset110)
#define FLEXCAN3_RXIMR37		(IMXRT_FLEXCAN3_MASK.offset114)
#define FLEXCAN3_RXIMR38		(IMXRT_FLEXCAN3_MASK.offset118)
#define FLEXCAN3_RXIMR39		(IMXRT_FLEXCAN3_MASK.offset11C)
#define FLEXCAN3_RXIMR40		(IMXRT_FLEXCAN3_MASK.offset120)
#define FLEXCAN3_RXIMR41		(IMXRT_FLEXCAN3_MASK.offset124)
#define FLEXCAN3_RXIMR42		(IMXRT_FLEXCAN3_MASK.offset128)
#define FLEXCAN3_RXIMR43		(IMXRT_FLEXCAN3_MASK.offset12C)
#define FLEXCAN3_RXIMR44		(IMXRT_FLEXCAN3_MASK.offset130)
#define FLEXCAN3_RXIMR45		(IMXRT_FLEXCAN3_MASK.offset134)
#define FLEXCAN3_RXIMR46		(IMXRT_FLEXCAN3_MASK.offset138)
#define FLEXCAN3_RXIMR47		(IMXRT_FLEXCAN3_MASK.offset13C)
#define FLEXCAN3_RXIMR48		(IMXRT_FLEXCAN3_MASK.offset140)
#define FLEXCAN3_RXIMR49		(IMXRT_FLEXCAN3_MASK.offset144)
#define FLEXCAN3_RXIMR50		(IMXRT_FLEXCAN3_MASK.offset148)
#define FLEXCAN3_RXIMR51		(IMXRT_FLEXCAN3_MASK.offset14C)
#define FLEXCAN3_RXIMR52		(IMXRT_FLEXCAN3_MASK.offset150)
#define FLEXCAN3_RXIMR53		(IMXRT_FLEXCAN3_MASK.offset154)
#define FLEXCAN3_RXIMR54		(IMXRT_FLEXCAN3_MASK.offset158)
#define FLEXCAN3_RXIMR55		(IMXRT_FLEXCAN3_MASK.offset15C)
#define FLEXCAN3_RXIMR56		(IMXRT_FLEXCAN3_MASK.offset160)
#define FLEXCAN3_RXIMR57		(IMXRT_FLEXCAN3_MASK.offset164)
#define FLEXCAN3_RXIMR58		(IMXRT_FLEXCAN3_MASK.offset168)
#define FLEXCAN3_RXIMR59		(IMXRT_FLEXCAN3_MASK.offset16C)
#define FLEXCAN3_RXIMR60		(IMXRT_FLEXCAN3_MASK.offset170)
#define FLEXCAN3_RXIMR61		(IMXRT_FLEXCAN3_MASK.offset174)
#define FLEXCAN3_RXIMR62		(IMXRT_FLEXCAN3_MASK.offset178)
#define FLEXCAN3_RXIMR63		(IMXRT_FLEXCAN3_MASK.offset17C)
#define FLEXCAN3_EPRS			(IMXRT_FLEXCAN3_EXT.offset0F0)
#define FLEXCAN3_ENCBT			(IMXRT_FLEXCAN3_EXT.offset0F4)
#define FLEXCAN3_EDCBT			(IMXRT_FLEXCAN3_EXT.offset0F8)
#define FLEXCAN3_ETDC			(IMXRT_FLEXCAN3_EXT.offset0FC)
#define FLEXCAN3_FDCTRL			(IMXRT_FLEXCAN3_EXT.offset100)
#define FLEXCAN3_FDCBT			(IMXRT_FLEXCAN3_EXT.offset104)
#define FLEXCAN3_FDCRC			(IMXRT_FLEXCAN3_EXT.offset108)
#define FLEXCAN3_ERFCR			(IMXRT_FLEXCAN3_EXT.offset10C)
#define FLEXCAN3_ERFIER			(IMXRT_FLEXCAN3_EXT.offset110)
#define FLEXCAN3_ERFSR			(IMXRT_FLEXCAN3_EXT.offset114)
#define FLEXCAN3_HR_TIME_STAMP0		(IMXRT_FLEXCAN3_EXT.offset130)
#define FLEXCAN3_HR_TIME_STAMP1		(IMXRT_FLEXCAN3_EXT.offset134)
#define FLEXCAN3_HR_TIME_STAMP2		(IMXRT_FLEXCAN3_EXT.offset138)
#define FLEXCAN3_HR_TIME_STAMP3		(IMXRT_FLEXCAN3_EXT.offset13C)
#define FLEXCAN3_HR_TIME_STAMP4		(IMXRT_FLEXCAN3_EXT.offset140)
#define FLEXCAN3_HR_TIME_STAMP5		(IMXRT_FLEXCAN3_EXT.offset144)
#define FLEXCAN3_HR_TIME_STAMP6		(IMXRT_FLEXCAN3_EXT.offset148)
#define FLEXCAN3_HR_TIME_STAMP7		(IMXRT_FLEXCAN3_EXT.offset14C)
#define FLEXCAN3_HR_TIME_STAMP8		(IMXRT_FLEXCAN3_EXT.offset150)
#define FLEXCAN3_HR_TIME_STAMP9		(IMXRT_FLEXCAN3_EXT.offset154)
#define FLEXCAN3_HR_TIME_STAMP10	(IMXRT_FLEXCAN3_EXT.offset158)
#define FLEXCAN3_HR_TIME_STAMP11	(IMXRT_FLEXCAN3_EXT.offset15C)
#define FLEXCAN3_HR_TIME_STAMP12	(IMXRT_FLEXCAN3_EXT.offset160)
#define FLEXCAN3_HR_TIME_STAMP13	(IMXRT_FLEXCAN3_EXT.offset164)
#define FLEXCAN3_HR_TIME_STAMP14	(IMXRT_FLEXCAN3_EXT.offset168)
#define FLEXCAN3_HR_TIME_STAMP15	(IMXRT_FLEXCAN3_EXT.offset16C)
#define FLEXCAN3_HR_TIME_STAMP16	(IMXRT_FLEXCAN3_EXT.offset170)
#define FLEXCAN3_HR_TIME_STAMP17	(IMXRT_FLEXCAN3_EXT.offset174)
#define FLEXCAN3_HR_TIME_STAMP18	(IMXRT_FLEXCAN3_EXT.offset178)
#define FLEXCAN3_HR_TIME_STAMP19	(IMXRT_FLEXCAN3_EXT.offset17C)
#define FLEXCAN3_HR_TIME_STAMP20	(IMXRT_FLEXCAN3_EXT.offset180)
#define FLEXCAN3_HR_TIME_STAMP21	(IMXRT_FLEXCAN3_EXT.offset184)
#define FLEXCAN3_HR_TIME_STAMP22	(IMXRT_FLEXCAN3_EXT.offset188)
#define FLEXCAN3_HR_TIME_STAMP23	(IMXRT_FLEXCAN3_EXT.offset18C)
#define FLEXCAN3_HR_TIME_STAMP24	(IMXRT_FLEXCAN3_EXT.offset190)
#define FLEXCAN3_HR_TIME_STAMP25	(IMXRT_FLEXCAN3_EXT.offset194)
#define FLEXCAN3_HR_TIME_STAMP26	(IMXRT_FLEXCAN3_EXT.offset198)
#define FLEXCAN3_HR_TIME_STAMP27	(IMXRT_FLEXCAN3_EXT.offset19C)
#define FLEXCAN3_HR_TIME_STAMP28	(IMXRT_FLEXCAN3_EXT.offset1A0)
#define FLEXCAN3_HR_TIME_STAMP29	(IMXRT_FLEXCAN3_EXT.offset1A4)
#define FLEXCAN3_HR_TIME_STAMP30	(IMXRT_FLEXCAN3_EXT.offset1A8)
#define FLEXCAN3_HR_TIME_STAMP31	(IMXRT_FLEXCAN3_EXT.offset1AC)
#define FLEXCAN3_HR_TIME_STAMP32	(IMXRT_FLEXCAN3_EXT.offset1B0)
#define FLEXCAN3_HR_TIME_STAMP33	(IMXRT_FLEXCAN3_EXT.offset1B4)
#define FLEXCAN3_HR_TIME_STAMP34	(IMXRT_FLEXCAN3_EXT.offset1B8)
#define FLEXCAN3_HR_TIME_STAMP35	(IMXRT_FLEXCAN3_EXT.offset1BC)
#define FLEXCAN3_HR_TIME_STAMP36	(IMXRT_FLEXCAN3_EXT.offset1C0)
#define FLEXCAN3_HR_TIME_STAMP37	(IMXRT_FLEXCAN3_EXT.offset1C4)
#define FLEXCAN3_HR_TIME_STAMP38	(IMXRT_FLEXCAN3_EXT.offset1C8)
#define FLEXCAN3_HR_TIME_STAMP39	(IMXRT_FLEXCAN3_EXT.offset1CC)
#define FLEXCAN3_HR_TIME_STAMP40	(IMXRT_FLEXCAN3_EXT.offset1D0)
#define FLEXCAN3_HR_TIME_STAMP41	(IMXRT_FLEXCAN3_EXT.offset1D4)
#define FLEXCAN3_HR_TIME_STAMP42	(IMXRT_FLEXCAN3_EXT.offset1D8)
#define FLEXCAN3_HR_TIME_STAMP43	(IMXRT_FLEXCAN3_EXT.offset1DC)
#define FLEXCAN3_HR_TIME_STAMP44	(IMXRT_FLEXCAN3_EXT.offset1E0)
#define FLEXCAN3_HR_TIME_STAMP45	(IMXRT_FLEXCAN3_EXT.offset1E4)
#define FLEXCAN3_HR_TIME_STAMP46	(IMXRT_FLEXCAN3_EXT.offset1E8)
#define FLEXCAN3_HR_TIME_STAMP47	(IMXRT_FLEXCAN3_EXT.offset1EC)
#define FLEXCAN3_HR_TIME_STAMP48	(IMXRT_FLEXCAN3_EXT.offset1F0)
#define FLEXCAN3_HR_TIME_STAMP49	(IMXRT_FLEXCAN3_EXT.offset1F4)
#define FLEXCAN3_HR_TIME_STAMP50	(IMXRT_FLEXCAN3_EXT.offset1F8)
#define FLEXCAN3_HR_TIME_STAMP51	(IMXRT_FLEXCAN3_EXT.offset1FC)
#define FLEXCAN3_HR_TIME_STAMP52	(IMXRT_FLEXCAN3_EXT.offset200)
#define FLEXCAN3_HR_TIME_STAMP53	(IMXRT_FLEXCAN3_EXT.offset204)
#define FLEXCAN3_HR_TIME_STAMP54	(IMXRT_FLEXCAN3_EXT.offset208)
#define FLEXCAN3_HR_TIME_STAMP55	(IMXRT_FLEXCAN3_EXT.offset20C)
#define FLEXCAN3_HR_TIME_STAMP56	(IMXRT_FLEXCAN3_EXT.offset210)
#define FLEXCAN3_HR_TIME_STAMP57	(IMXRT_FLEXCAN3_EXT.offset234)
#define FLEXCAN3_HR_TIME_STAMP58	(IMXRT_FLEXCAN3_EXT.offset218)
#define FLEXCAN3_HR_TIME_STAMP59	(IMXRT_FLEXCAN3_EXT.offset21C)
#define FLEXCAN3_HR_TIME_STAMP60	(IMXRT_FLEXCAN3_EXT.offset220)
#define FLEXCAN3_HR_TIME_STAMP61	(IMXRT_FLEXCAN3_EXT.offset224)
#define FLEXCAN3_HR_TIME_STAMP62	(IMXRT_FLEXCAN3_EXT.offset228)
#define FLEXCAN3_HR_TIME_STAMP63	(IMXRT_FLEXCAN3_EXT.offset22C)
#define FLEXCAN3_ERFFEL0		(IMXRT_FLEXCAN3_ERXFIFO.offset000)
#define FLEXCAN3_ERFFEL1		(IMXRT_FLEXCAN3_ERXFIFO.offset004)
#define FLEXCAN3_ERFFEL2		(IMXRT_FLEXCAN3_ERXFIFO.offset008)
#define FLEXCAN3_ERFFEL3		(IMXRT_FLEXCAN3_ERXFIFO.offset00C)
#define FLEXCAN3_ERFFEL4		(IMXRT_FLEXCAN3_ERXFIFO.offset010)
#define FLEXCAN3_ERFFEL5		(IMXRT_FLEXCAN3_ERXFIFO.offset014)
#define FLEXCAN3_ERFFEL6		(IMXRT_FLEXCAN3_ERXFIFO.offset018)
#define FLEXCAN3_ERFFEL7		(IMXRT_FLEXCAN3_ERXFIFO.offset01C)
#define FLEXCAN3_ERFFEL8		(IMXRT_FLEXCAN3_ERXFIFO.offset020)
#define FLEXCAN3_ERFFEL9		(IMXRT_FLEXCAN3_ERXFIFO.offset024)
#define FLEXCAN3_ERFFEL10		(IMXRT_FLEXCAN3_ERXFIFO.offset028)
#define FLEXCAN3_ERFFEL11		(IMXRT_FLEXCAN3_ERXFIFO.offset02C)
#define FLEXCAN3_ERFFEL12		(IMXRT_FLEXCAN3_ERXFIFO.offset030)
#define FLEXCAN3_ERFFEL13		(IMXRT_FLEXCAN3_ERXFIFO.offset034)
#define FLEXCAN3_ERFFEL14		(IMXRT_FLEXCAN3_ERXFIFO.offset038)
#define FLEXCAN3_ERFFEL15		(IMXRT_FLEXCAN3_ERXFIFO.offset03C)
#define FLEXCAN3_ERFFEL16		(IMXRT_FLEXCAN3_ERXFIFO.offset040)
#define FLEXCAN3_ERFFEL17		(IMXRT_FLEXCAN3_ERXFIFO.offset044)
#define FLEXCAN3_ERFFEL18		(IMXRT_FLEXCAN3_ERXFIFO.offset048)
#define FLEXCAN3_ERFFEL19		(IMXRT_FLEXCAN3_ERXFIFO.offset04C)
#define FLEXCAN3_ERFFEL20		(IMXRT_FLEXCAN3_ERXFIFO.offset050)
#define FLEXCAN3_ERFFEL21		(IMXRT_FLEXCAN3_ERXFIFO.offset054)
#define FLEXCAN3_ERFFEL22		(IMXRT_FLEXCAN3_ERXFIFO.offset058)
#define FLEXCAN3_ERFFEL23		(IMXRT_FLEXCAN3_ERXFIFO.offset05C)
#define FLEXCAN3_ERFFEL24		(IMXRT_FLEXCAN3_ERXFIFO.offset060)
#define FLEXCAN3_ERFFEL25		(IMXRT_FLEXCAN3_ERXFIFO.offset064)
#define FLEXCAN3_ERFFEL26		(IMXRT_FLEXCAN3_ERXFIFO.offset068)
#define FLEXCAN3_ERFFEL27		(IMXRT_FLEXCAN3_ERXFIFO.offset06C)
#define FLEXCAN3_ERFFEL28		(IMXRT_FLEXCAN3_ERXFIFO.offset070)
#define FLEXCAN3_ERFFEL29		(IMXRT_FLEXCAN3_ERXFIFO.offset074)
#define FLEXCAN3_ERFFEL30		(IMXRT_FLEXCAN3_ERXFIFO.offset078)
#define FLEXCAN3_ERFFEL31		(IMXRT_FLEXCAN3_ERXFIFO.offset07C)
#define FLEXCAN3_ERFFEL32		(IMXRT_FLEXCAN3_ERXFIFO.offset080)
#define FLEXCAN3_ERFFEL33		(IMXRT_FLEXCAN3_ERXFIFO.offset084)
#define FLEXCAN3_ERFFEL34		(IMXRT_FLEXCAN3_ERXFIFO.offset088)
#define FLEXCAN3_ERFFEL35		(IMXRT_FLEXCAN3_ERXFIFO.offset08C)
#define FLEXCAN3_ERFFEL36		(IMXRT_FLEXCAN3_ERXFIFO.offset090)
#define FLEXCAN3_ERFFEL37		(IMXRT_FLEXCAN3_ERXFIFO.offset094)
#define FLEXCAN3_ERFFEL38		(IMXRT_FLEXCAN3_ERXFIFO.offset098)
#define FLEXCAN3_ERFFEL39		(IMXRT_FLEXCAN3_ERXFIFO.offset09C)
#define FLEXCAN3_ERFFEL40		(IMXRT_FLEXCAN3_ERXFIFO.offset0A0)
#define FLEXCAN3_ERFFEL41		(IMXRT_FLEXCAN3_ERXFIFO.offset0A4)
#define FLEXCAN3_ERFFEL42		(IMXRT_FLEXCAN3_ERXFIFO.offset0A8)
#define FLEXCAN3_ERFFEL43		(IMXRT_FLEXCAN3_ERXFIFO.offset0AC)
#define FLEXCAN3_ERFFEL44		(IMXRT_FLEXCAN3_ERXFIFO.offset0B0)
#define FLEXCAN3_ERFFEL45		(IMXRT_FLEXCAN3_ERXFIFO.offset0B4)
#define FLEXCAN3_ERFFEL46		(IMXRT_FLEXCAN3_ERXFIFO.offset0B8)
#define FLEXCAN3_ERFFEL47		(IMXRT_FLEXCAN3_ERXFIFO.offset0BC)
#define FLEXCAN3_ERFFEL48		(IMXRT_FLEXCAN3_ERXFIFO.offset0C0)
#define FLEXCAN3_ERFFEL49		(IMXRT_FLEXCAN3_ERXFIFO.offset0C4)
#define FLEXCAN3_ERFFEL50		(IMXRT_FLEXCAN3_ERXFIFO.offset0C8)
#define FLEXCAN3_ERFFEL51		(IMXRT_FLEXCAN3_ERXFIFO.offset0CC)
#define FLEXCAN3_ERFFEL52		(IMXRT_FLEXCAN3_ERXFIFO.offset0D0)
#define FLEXCAN3_ERFFEL53		(IMXRT_FLEXCAN3_ERXFIFO.offset0D4)
#define FLEXCAN3_ERFFEL54		(IMXRT_FLEXCAN3_ERXFIFO.offset0D8)
#define FLEXCAN3_ERFFEL55		(IMXRT_FLEXCAN3_ERXFIFO.offset0DC)
#define FLEXCAN3_ERFFEL56		(IMXRT_FLEXCAN3_ERXFIFO.offset0E0)
#define FLEXCAN3_ERFFEL57		(IMXRT_FLEXCAN3_ERXFIFO.offset0E4)
#define FLEXCAN3_ERFFEL58		(IMXRT_FLEXCAN3_ERXFIFO.offset0E8)
#define FLEXCAN3_ERFFEL59		(IMXRT_FLEXCAN3_ERXFIFO.offset0EC)
#define FLEXCAN3_ERFFEL60		(IMXRT_FLEXCAN3_ERXFIFO.offset0F0)
#define FLEXCAN3_ERFFEL61		(IMXRT_FLEXCAN3_ERXFIFO.offset0F4)
#define FLEXCAN3_ERFFEL62		(IMXRT_FLEXCAN3_ERXFIFO.offset0F8)
#define FLEXCAN3_ERFFEL63		(IMXRT_FLEXCAN3_ERXFIFO.offset0FC)
#define FLEXCAN3_ERFFEL64		(IMXRT_FLEXCAN3_ERXFIFO.offset100)
#define FLEXCAN3_ERFFEL65		(IMXRT_FLEXCAN3_ERXFIFO.offset104)
#define FLEXCAN3_ERFFEL66		(IMXRT_FLEXCAN3_ERXFIFO.offset108)
#define FLEXCAN3_ERFFEL67		(IMXRT_FLEXCAN3_ERXFIFO.offset10C)
#define FLEXCAN3_ERFFEL68		(IMXRT_FLEXCAN3_ERXFIFO.offset110)
#define FLEXCAN3_ERFFEL69		(IMXRT_FLEXCAN3_ERXFIFO.offset114)
#define FLEXCAN3_ERFFEL70		(IMXRT_FLEXCAN3_ERXFIFO.offset118)
#define FLEXCAN3_ERFFEL71		(IMXRT_FLEXCAN3_ERXFIFO.offset11C)
#define FLEXCAN3_ERFFEL72		(IMXRT_FLEXCAN3_ERXFIFO.offset120)
#define FLEXCAN3_ERFFEL73		(IMXRT_FLEXCAN3_ERXFIFO.offset124)
#define FLEXCAN3_ERFFEL74		(IMXRT_FLEXCAN3_ERXFIFO.offset128)
#define FLEXCAN3_ERFFEL75		(IMXRT_FLEXCAN3_ERXFIFO.offset12C)
#define FLEXCAN3_ERFFEL76		(IMXRT_FLEXCAN3_ERXFIFO.offset130)
#define FLEXCAN3_ERFFEL77		(IMXRT_FLEXCAN3_ERXFIFO.offset134)
#define FLEXCAN3_ERFFEL78		(IMXRT_FLEXCAN3_ERXFIFO.offset138)
#define FLEXCAN3_ERFFEL79		(IMXRT_FLEXCAN3_ERXFIFO.offset13C)
#define FLEXCAN3_ERFFEL80		(IMXRT_FLEXCAN3_ERXFIFO.offset140)
#define FLEXCAN3_ERFFEL81		(IMXRT_FLEXCAN3_ERXFIFO.offset144)
#define FLEXCAN3_ERFFEL82		(IMXRT_FLEXCAN3_ERXFIFO.offset148)
#define FLEXCAN3_ERFFEL83		(IMXRT_FLEXCAN3_ERXFIFO.offset14C)
#define FLEXCAN3_ERFFEL84		(IMXRT_FLEXCAN3_ERXFIFO.offset150)
#define FLEXCAN3_ERFFEL85		(IMXRT_FLEXCAN3_ERXFIFO.offset154)
#define FLEXCAN3_ERFFEL86		(IMXRT_FLEXCAN3_ERXFIFO.offset158)
#define FLEXCAN3_ERFFEL87		(IMXRT_FLEXCAN3_ERXFIFO.offset15C)
#define FLEXCAN3_ERFFEL88		(IMXRT_FLEXCAN3_ERXFIFO.offset160)
#define FLEXCAN3_ERFFEL89		(IMXRT_FLEXCAN3_ERXFIFO.offset164)
#define FLEXCAN3_ERFFEL90		(IMXRT_FLEXCAN3_ERXFIFO.offset168)
#define FLEXCAN3_ERFFEL91		(IMXRT_FLEXCAN3_ERXFIFO.offset16C)
#define FLEXCAN3_ERFFEL92		(IMXRT_FLEXCAN3_ERXFIFO.offset170)
#define FLEXCAN3_ERFFEL93		(IMXRT_FLEXCAN3_ERXFIFO.offset174)
#define FLEXCAN3_ERFFEL94		(IMXRT_FLEXCAN3_ERXFIFO.offset178)
#define FLEXCAN3_ERFFEL95		(IMXRT_FLEXCAN3_ERXFIFO.offset17C)
#define FLEXCAN3_ERFFEL96		(IMXRT_FLEXCAN3_ERXFIFO.offset180)
#define FLEXCAN3_ERFFEL97		(IMXRT_FLEXCAN3_ERXFIFO.offset184)
#define FLEXCAN3_ERFFEL98		(IMXRT_FLEXCAN3_ERXFIFO.offset188)
#define FLEXCAN3_ERFFEL99		(IMXRT_FLEXCAN3_ERXFIFO.offset18C)
#define FLEXCAN3_ERFFEL100		(IMXRT_FLEXCAN3_ERXFIFO.offset190)
#define FLEXCAN3_ERFFEL101		(IMXRT_FLEXCAN3_ERXFIFO.offset194)
#define FLEXCAN3_ERFFEL102		(IMXRT_FLEXCAN3_ERXFIFO.offset198)
#define FLEXCAN3_ERFFEL103		(IMXRT_FLEXCAN3_ERXFIFO.offset19C)
#define FLEXCAN3_ERFFEL104		(IMXRT_FLEXCAN3_ERXFIFO.offset1A0)
#define FLEXCAN3_ERFFEL105		(IMXRT_FLEXCAN3_ERXFIFO.offset1A4)
#define FLEXCAN3_ERFFEL106		(IMXRT_FLEXCAN3_ERXFIFO.offset1A8)
#define FLEXCAN3_ERFFEL107		(IMXRT_FLEXCAN3_ERXFIFO.offset1AC)
#define FLEXCAN3_ERFFEL108		(IMXRT_FLEXCAN3_ERXFIFO.offset1B0)
#define FLEXCAN3_ERFFEL109		(IMXRT_FLEXCAN3_ERXFIFO.offset1B4)
#define FLEXCAN3_ERFFEL110		(IMXRT_FLEXCAN3_ERXFIFO.offset1B8)
#define FLEXCAN3_ERFFEL111		(IMXRT_FLEXCAN3_ERXFIFO.offset1BC)
#define FLEXCAN3_ERFFEL112		(IMXRT_FLEXCAN3_ERXFIFO.offset1C0)
#define FLEXCAN3_ERFFEL113		(IMXRT_FLEXCAN3_ERXFIFO.offset1C4)
#define FLEXCAN3_ERFFEL114		(IMXRT_FLEXCAN3_ERXFIFO.offset1C8)
#define FLEXCAN3_ERFFEL115		(IMXRT_FLEXCAN3_ERXFIFO.offset1CC)
#define FLEXCAN3_ERFFEL116		(IMXRT_FLEXCAN3_ERXFIFO.offset1D0)
#define FLEXCAN3_ERFFEL117		(IMXRT_FLEXCAN3_ERXFIFO.offset1D4)
#define FLEXCAN3_ERFFEL118		(IMXRT_FLEXCAN3_ERXFIFO.offset1D8)
#define FLEXCAN3_ERFFEL119		(IMXRT_FLEXCAN3_ERXFIFO.offset1DC)
#define FLEXCAN3_ERFFEL120		(IMXRT_FLEXCAN3_ERXFIFO.offset1E0)
#define FLEXCAN3_ERFFEL121		(IMXRT_FLEXCAN3_ERXFIFO.offset1E4)
#define FLEXCAN3_ERFFEL122		(IMXRT_FLEXCAN3_ERXFIFO.offset1E8)
#define FLEXCAN3_ERFFEL123		(IMXRT_FLEXCAN3_ERXFIFO.offset1EC)
#define FLEXCAN3_ERFFEL124		(IMXRT_FLEXCAN3_ERXFIFO.offset1F0)
#define FLEXCAN3_ERFFEL125		(IMXRT_FLEXCAN3_ERXFIFO.offset1F4)
#define FLEXCAN3_ERFFEL126		(IMXRT_FLEXCAN3_ERXFIFO.offset1F8)
#define FLEXCAN3_ERFFEL127		(IMXRT_FLEXCAN3_ERXFIFO.offset1FC)

// 50.5.1.1: page 2912
typedef struct {
        const   uint32_t VERID;                         // 0x00 (IMXRT_FLEXIO1.offset000)
        volatile uint32_t PARAM;                        // 0x04 // (IMXRT_FLEXIO1.offset004)
        volatile uint32_t CTRL;                         // 0x08(IMXRT_FLEXIO1.offset008)
        volatile uint32_t PIN;                          // 0x0c (IMXRT_FLEXIO1.offset00C)
        volatile uint32_t SHIFTSTAT;            // 0x10 (IMXRT_FLEXIO1.offset010)
        volatile uint32_t SHIFTERR;                     // 0x14(IMXRT_FLEXIO1.offset014)
        volatile uint32_t TIMSTAT;                      // 0x18 (IMXRT_FLEXIO1.offset018)
        const   uint32_t UNUSED0;                       // 0x1c
        volatile uint32_t SHIFTSIEN;            // 0x20 (IMXRT_FLEXIO1.offset020)
        volatile uint32_t SHIFTEIEN;            // 0x24 (IMXRT_FLEXIO1.offset024)
        volatile uint32_t TIMIEN;                       // 0x28 (IMXRT_FLEXIO1.offset028)
        const   uint32_t UNUSED1;                       // 0x2c
        volatile uint32_t SHIFTSDEN;            // 0x30 (IMXRT_FLEXIO1.offset030)
        const   uint32_t UNUSED2[3];            // 0x34 38 3C
        volatile uint32_t SHIFTSTATE;           // 0x40 (IMXRT_FLEXIO1.offset040)
        const   uint32_t UNUSED3[15];           // 0x44..  50... 60... 70...
        volatile uint32_t SHIFTCTL[8];          // 0x80 84 88 8C
        const   uint32_t UNUSED4[24];           // 0x90 - 0xfc
        volatile uint32_t SHIFTCFG[8];          // 0x100 104 108 10C (IMXRT_FLEXIO1.offset100)
        const   uint32_t UNUSED5[56];           // 0x110 - 0x1FC
        volatile uint32_t SHIFTBUF[8];          // 0x200 204 208 20c (IMXRT_FLEXIO1.offset200)
        const   uint32_t UNUSED6[24];           // 
        volatile uint32_t SHIFTBUFBIS[8];       // 0x280        // (IMXRT_FLEXIO1.offset280)
        const   uint32_t UNUSED7[24];           // 
        volatile uint32_t SHIFTBUFBYS[8];       // 0x300 (IMXRT_FLEXIO1.offset300)
        const   uint32_t UNUSED8[24];           // 
        volatile uint32_t SHIFTBUFBBS[8];       // 0x380 (IMXRT_FLEXIO1.offset380)
        const   uint32_t UNUSED9[24];           // 
        volatile uint32_t TIMCTL[8];            // 0x400 
        const   uint32_t UNUSED10[24];          // 
        volatile uint32_t TIMCFG[8];            // 0x480
        const   uint32_t UNUSED11[24];          // 
        volatile uint32_t TIMCMP[8];            // 0x500
        const   uint32_t UNUSED12[24+64];       // 
        volatile uint32_t SHIFTBUFNBS[8];       // 0x680
        const   uint32_t UNUSED13[24];          // 
        volatile uint32_t SHIFTBUFHWS[8];       // 0x700
        const   uint32_t UNUSED14[24];          // 
        volatile uint32_t SHIFTBUFNIS[8];       // 0x780
} IMXRT_FLEXIO_t;


#define IMXRT_FLEXIO1_S         (*(IMXRT_FLEXIO_t *)IMXRT_FLEXIO1_ADDRESS)
#define IMXRT_FLEXIO2_S         (*(IMXRT_FLEXIO_t *)IMXRT_FLEXIO2_ADDRESS)
#define IMXRT_FLEXIO3_S         (*(IMXRT_FLEXIO_t *)IMXRT_FLEXIO3_ADDRESS)

#define IMXRT_FLEXIO1		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXIO1_ADDRESS)
#define IMXRT_FLEXIO1_b		(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXIO1_ADDRESS+0x400))
#define FLEXIO1_VERID			(IMXRT_FLEXIO1.offset000)
#define FLEXIO1_PARAM			(IMXRT_FLEXIO1.offset004)
#define FLEXIO1_CTRL			(IMXRT_FLEXIO1.offset008)
#define FLEXIO1_PIN			(IMXRT_FLEXIO1.offset00C)
#define FLEXIO1_SHIFTSTAT		(IMXRT_FLEXIO1.offset010)
#define FLEXIO1_SHIFTERR		(IMXRT_FLEXIO1.offset014)
#define FLEXIO1_TIMSTAT			(IMXRT_FLEXIO1.offset018)
#define FLEXIO1_SHIFTSIEN		(IMXRT_FLEXIO1.offset020)
#define FLEXIO1_SHIFTEIEN		(IMXRT_FLEXIO1.offset024)
#define FLEXIO1_TIMIEN			(IMXRT_FLEXIO1.offset028)
#define FLEXIO1_SHIFTSDEN		(IMXRT_FLEXIO1.offset030)
#define FLEXIO1_SHIFTSTATE		(IMXRT_FLEXIO1.offset040)
#define FLEXIO1_SHIFTCTL0		(IMXRT_FLEXIO1.offset080)
#define FLEXIO1_SHIFTCTL1		(IMXRT_FLEXIO1.offset084)
#define FLEXIO1_SHIFTCTL2		(IMXRT_FLEXIO1.offset088)
#define FLEXIO1_SHIFTCTL3		(IMXRT_FLEXIO1.offset08C)
#define FLEXIO1_SHIFTCTL4		(IMXRT_FLEXIO1.offset090)
#define FLEXIO1_SHIFTCTL5		(IMXRT_FLEXIO1.offset094)
#define FLEXIO1_SHIFTCTL6		(IMXRT_FLEXIO1.offset098)
#define FLEXIO1_SHIFTCTL7		(IMXRT_FLEXIO1.offset09C)
#define FLEXIO1_SHIFTCFG0		(IMXRT_FLEXIO1.offset100)
#define FLEXIO1_SHIFTCFG1		(IMXRT_FLEXIO1.offset104)
#define FLEXIO1_SHIFTCFG2		(IMXRT_FLEXIO1.offset108)
#define FLEXIO1_SHIFTCFG3		(IMXRT_FLEXIO1.offset10C)
#define FLEXIO1_SHIFTCFG4		(IMXRT_FLEXIO1.offset110)
#define FLEXIO1_SHIFTCFG5		(IMXRT_FLEXIO1.offset114)
#define FLEXIO1_SHIFTCFG6		(IMXRT_FLEXIO1.offset118)
#define FLEXIO1_SHIFTCFG7		(IMXRT_FLEXIO1.offset11C)
#define FLEXIO1_SHIFTBUF0		(IMXRT_FLEXIO1.offset200)
#define FLEXIO1_SHIFTBUF1		(IMXRT_FLEXIO1.offset204)
#define FLEXIO1_SHIFTBUF2		(IMXRT_FLEXIO1.offset208)
#define FLEXIO1_SHIFTBUF3		(IMXRT_FLEXIO1.offset20C)
#define FLEXIO1_SHIFTBUF4		(IMXRT_FLEXIO1.offset210)
#define FLEXIO1_SHIFTBUF5		(IMXRT_FLEXIO1.offset214)
#define FLEXIO1_SHIFTBUF6		(IMXRT_FLEXIO1.offset218)
#define FLEXIO1_SHIFTBUF7		(IMXRT_FLEXIO1.offset21C)
#define FLEXIO1_SHIFTBUFBIS0		(IMXRT_FLEXIO1.offset280)
#define FLEXIO1_SHIFTBUFBIS1		(IMXRT_FLEXIO1.offset284)
#define FLEXIO1_SHIFTBUFBIS2		(IMXRT_FLEXIO1.offset288)
#define FLEXIO1_SHIFTBUFBIS3		(IMXRT_FLEXIO1.offset28C)
#define FLEXIO1_SHIFTBUFBIS4		(IMXRT_FLEXIO1.offset290)
#define FLEXIO1_SHIFTBUFBIS5		(IMXRT_FLEXIO1.offset294)
#define FLEXIO1_SHIFTBUFBIS6		(IMXRT_FLEXIO1.offset298)
#define FLEXIO1_SHIFTBUFBIS7		(IMXRT_FLEXIO1.offset29C)
#define FLEXIO1_SHIFTBUFBYS0		(IMXRT_FLEXIO1.offset300)
#define FLEXIO1_SHIFTBUFBYS1		(IMXRT_FLEXIO1.offset304)
#define FLEXIO1_SHIFTBUFBYS2		(IMXRT_FLEXIO1.offset308)
#define FLEXIO1_SHIFTBUFBYS3		(IMXRT_FLEXIO1.offset30C)
#define FLEXIO1_SHIFTBUFBYS4		(IMXRT_FLEXIO1.offset310)
#define FLEXIO1_SHIFTBUFBYS5		(IMXRT_FLEXIO1.offset314)
#define FLEXIO1_SHIFTBUFBYS6		(IMXRT_FLEXIO1.offset318)
#define FLEXIO1_SHIFTBUFBYS7		(IMXRT_FLEXIO1.offset31C)
#define FLEXIO1_SHIFTBUFBBS0		(IMXRT_FLEXIO1.offset380)
#define FLEXIO1_SHIFTBUFBBS1		(IMXRT_FLEXIO1.offset384)
#define FLEXIO1_SHIFTBUFBBS2		(IMXRT_FLEXIO1.offset388)
#define FLEXIO1_SHIFTBUFBBS3		(IMXRT_FLEXIO1.offset38C)
#define FLEXIO1_SHIFTBUFBBS4		(IMXRT_FLEXIO1.offset390)
#define FLEXIO1_SHIFTBUFBBS5		(IMXRT_FLEXIO1.offset394)
#define FLEXIO1_SHIFTBUFBBS6		(IMXRT_FLEXIO1.offset398)
#define FLEXIO1_SHIFTBUFBBS7		(IMXRT_FLEXIO1.offset39C)
#define FLEXIO1_TIMCTL0			(IMXRT_FLEXIO1_b.offset000)
#define FLEXIO1_TIMCTL1			(IMXRT_FLEXIO1_b.offset004)
#define FLEXIO1_TIMCTL2			(IMXRT_FLEXIO1_b.offset008)
#define FLEXIO1_TIMCTL3			(IMXRT_FLEXIO1_b.offset00C)
#define FLEXIO1_TIMCTL4			(IMXRT_FLEXIO1_b.offset010)
#define FLEXIO1_TIMCTL5			(IMXRT_FLEXIO1_b.offset014)
#define FLEXIO1_TIMCTL6			(IMXRT_FLEXIO1_b.offset018)
#define FLEXIO1_TIMCTL7			(IMXRT_FLEXIO1_b.offset01C)
#define FLEXIO1_TIMCFG0			(IMXRT_FLEXIO1_b.offset080)
#define FLEXIO1_TIMCFG1			(IMXRT_FLEXIO1_b.offset084)
#define FLEXIO1_TIMCFG2			(IMXRT_FLEXIO1_b.offset088)
#define FLEXIO1_TIMCFG3			(IMXRT_FLEXIO1_b.offset08C)
#define FLEXIO1_TIMCFG4			(IMXRT_FLEXIO1_b.offset090)
#define FLEXIO1_TIMCFG5			(IMXRT_FLEXIO1_b.offset094)
#define FLEXIO1_TIMCFG6			(IMXRT_FLEXIO1_b.offset098)
#define FLEXIO1_TIMCFG7			(IMXRT_FLEXIO1_b.offset09C)
#define FLEXIO1_TIMCMP0			(IMXRT_FLEXIO1_b.offset100)
#define FLEXIO1_TIMCMP1			(IMXRT_FLEXIO1_b.offset104)
#define FLEXIO1_TIMCMP2			(IMXRT_FLEXIO1_b.offset108)
#define FLEXIO1_TIMCMP3			(IMXRT_FLEXIO1_b.offset10C)
#define FLEXIO1_TIMCMP4			(IMXRT_FLEXIO1_b.offset110)
#define FLEXIO1_TIMCMP5			(IMXRT_FLEXIO1_b.offset114)
#define FLEXIO1_TIMCMP6			(IMXRT_FLEXIO1_b.offset118)
#define FLEXIO1_TIMCMP7			(IMXRT_FLEXIO1_b.offset11C)
#define FLEXIO1_SHIFTBUFNBS0		(IMXRT_FLEXIO1_b.offset280)
#define FLEXIO1_SHIFTBUFNBS1		(IMXRT_FLEXIO1_b.offset284)
#define FLEXIO1_SHIFTBUFNBS2		(IMXRT_FLEXIO1_b.offset288)
#define FLEXIO1_SHIFTBUFNBS3		(IMXRT_FLEXIO1_b.offset28C)
#define FLEXIO1_SHIFTBUFNBS4		(IMXRT_FLEXIO1_b.offset290)
#define FLEXIO1_SHIFTBUFNBS5		(IMXRT_FLEXIO1_b.offset294)
#define FLEXIO1_SHIFTBUFNBS6		(IMXRT_FLEXIO1_b.offset298)
#define FLEXIO1_SHIFTBUFNBS7		(IMXRT_FLEXIO1_b.offset29C)
#define FLEXIO1_SHIFTBUFHWS0		(IMXRT_FLEXIO1_b.offset300)
#define FLEXIO1_SHIFTBUFHWS1		(IMXRT_FLEXIO1_b.offset304)
#define FLEXIO1_SHIFTBUFHWS2		(IMXRT_FLEXIO1_b.offset308)
#define FLEXIO1_SHIFTBUFHWS3		(IMXRT_FLEXIO1_b.offset30C)
#define FLEXIO1_SHIFTBUFHWS4		(IMXRT_FLEXIO1_b.offset310)
#define FLEXIO1_SHIFTBUFHWS5		(IMXRT_FLEXIO1_b.offset314)
#define FLEXIO1_SHIFTBUFHWS6		(IMXRT_FLEXIO1_b.offset318)
#define FLEXIO1_SHIFTBUFHWS7		(IMXRT_FLEXIO1_b.offset31C)
#define FLEXIO1_SHIFTBUFNIS0		(IMXRT_FLEXIO1_b.offset380)
#define FLEXIO1_SHIFTBUFNIS1		(IMXRT_FLEXIO1_b.offset384)
#define FLEXIO1_SHIFTBUFNIS2		(IMXRT_FLEXIO1_b.offset388)
#define FLEXIO1_SHIFTBUFNIS3		(IMXRT_FLEXIO1_b.offset38C)
#define FLEXIO1_SHIFTBUFNIS4		(IMXRT_FLEXIO1_b.offset390)
#define FLEXIO1_SHIFTBUFNIS5		(IMXRT_FLEXIO1_b.offset394)
#define FLEXIO1_SHIFTBUFNIS6		(IMXRT_FLEXIO1_b.offset398)
#define FLEXIO1_SHIFTBUFNIS7		(IMXRT_FLEXIO1_b.offset39C)
#define IMXRT_FLEXIO2		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXIO2_ADDRESS)
#define IMXRT_FLEXIO2_b		(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXIO2_ADDRESS+0x400))
#define FLEXIO2_VERID			(IMXRT_FLEXIO2.offset000)
#define FLEXIO2_PARAM			(IMXRT_FLEXIO2.offset004)
#define FLEXIO2_CTRL			(IMXRT_FLEXIO2.offset008)
#define FLEXIO2_PIN			(IMXRT_FLEXIO2.offset00C)
#define FLEXIO2_SHIFTSTAT		(IMXRT_FLEXIO2.offset010)
#define FLEXIO2_SHIFTERR		(IMXRT_FLEXIO2.offset014)
#define FLEXIO2_TIMSTAT			(IMXRT_FLEXIO2.offset018)
#define FLEXIO2_SHIFTSIEN		(IMXRT_FLEXIO2.offset020)
#define FLEXIO2_SHIFTEIEN		(IMXRT_FLEXIO2.offset024)
#define FLEXIO2_TIMIEN			(IMXRT_FLEXIO2.offset028)
#define FLEXIO2_SHIFTSDEN		(IMXRT_FLEXIO2.offset030)
#define FLEXIO2_SHIFTSTATE		(IMXRT_FLEXIO2.offset040)
#define FLEXIO2_SHIFTCTL0		(IMXRT_FLEXIO2.offset080)
#define FLEXIO2_SHIFTCTL1		(IMXRT_FLEXIO2.offset084)
#define FLEXIO2_SHIFTCTL2		(IMXRT_FLEXIO2.offset088)
#define FLEXIO2_SHIFTCTL3		(IMXRT_FLEXIO2.offset08C)
#define FLEXIO2_SHIFTCTL4		(IMXRT_FLEXIO2.offset090)
#define FLEXIO2_SHIFTCTL5		(IMXRT_FLEXIO2.offset094)
#define FLEXIO2_SHIFTCTL6		(IMXRT_FLEXIO2.offset098)
#define FLEXIO2_SHIFTCTL7		(IMXRT_FLEXIO2.offset09C)
#define FLEXIO2_SHIFTCFG0		(IMXRT_FLEXIO2.offset100)
#define FLEXIO2_SHIFTCFG1		(IMXRT_FLEXIO2.offset104)
#define FLEXIO2_SHIFTCFG2		(IMXRT_FLEXIO2.offset108)
#define FLEXIO2_SHIFTCFG3		(IMXRT_FLEXIO2.offset10C)
#define FLEXIO2_SHIFTCFG4		(IMXRT_FLEXIO2.offset110)
#define FLEXIO2_SHIFTCFG5		(IMXRT_FLEXIO2.offset114)
#define FLEXIO2_SHIFTCFG6		(IMXRT_FLEXIO2.offset118)
#define FLEXIO2_SHIFTCFG7		(IMXRT_FLEXIO2.offset11C)
#define FLEXIO2_SHIFTBUF0		(IMXRT_FLEXIO2.offset200)
#define FLEXIO2_SHIFTBUF1		(IMXRT_FLEXIO2.offset204)
#define FLEXIO2_SHIFTBUF2		(IMXRT_FLEXIO2.offset208)
#define FLEXIO2_SHIFTBUF3		(IMXRT_FLEXIO2.offset20C)
#define FLEXIO2_SHIFTBUF4		(IMXRT_FLEXIO2.offset210)
#define FLEXIO2_SHIFTBUF5		(IMXRT_FLEXIO2.offset214)
#define FLEXIO2_SHIFTBUF6		(IMXRT_FLEXIO2.offset218)
#define FLEXIO2_SHIFTBUF7		(IMXRT_FLEXIO2.offset21C)
#define FLEXIO2_SHIFTBUFBIS0		(IMXRT_FLEXIO2.offset280)
#define FLEXIO2_SHIFTBUFBIS1		(IMXRT_FLEXIO2.offset284)
#define FLEXIO2_SHIFTBUFBIS2		(IMXRT_FLEXIO2.offset288)
#define FLEXIO2_SHIFTBUFBIS3		(IMXRT_FLEXIO2.offset28C)
#define FLEXIO2_SHIFTBUFBIS4		(IMXRT_FLEXIO2.offset290)
#define FLEXIO2_SHIFTBUFBIS5		(IMXRT_FLEXIO2.offset294)
#define FLEXIO2_SHIFTBUFBIS6		(IMXRT_FLEXIO2.offset298)
#define FLEXIO2_SHIFTBUFBIS7		(IMXRT_FLEXIO2.offset29C)
#define FLEXIO2_SHIFTBUFBYS0		(IMXRT_FLEXIO2.offset300)
#define FLEXIO2_SHIFTBUFBYS1		(IMXRT_FLEXIO2.offset304)
#define FLEXIO2_SHIFTBUFBYS2		(IMXRT_FLEXIO2.offset308)
#define FLEXIO2_SHIFTBUFBYS3		(IMXRT_FLEXIO2.offset30C)
#define FLEXIO2_SHIFTBUFBYS4		(IMXRT_FLEXIO2.offset310)
#define FLEXIO2_SHIFTBUFBYS5		(IMXRT_FLEXIO2.offset314)
#define FLEXIO2_SHIFTBUFBYS6		(IMXRT_FLEXIO2.offset318)
#define FLEXIO2_SHIFTBUFBYS7		(IMXRT_FLEXIO2.offset31C)
#define FLEXIO2_SHIFTBUFBBS0		(IMXRT_FLEXIO2.offset380)
#define FLEXIO2_SHIFTBUFBBS1		(IMXRT_FLEXIO2.offset384)
#define FLEXIO2_SHIFTBUFBBS2		(IMXRT_FLEXIO2.offset388)
#define FLEXIO2_SHIFTBUFBBS3		(IMXRT_FLEXIO2.offset38C)
#define FLEXIO2_SHIFTBUFBBS4		(IMXRT_FLEXIO2.offset390)
#define FLEXIO2_SHIFTBUFBBS5		(IMXRT_FLEXIO2.offset394)
#define FLEXIO2_SHIFTBUFBBS6		(IMXRT_FLEXIO2.offset398)
#define FLEXIO2_SHIFTBUFBBS7		(IMXRT_FLEXIO2.offset39C)
#define FLEXIO2_TIMCTL0			(IMXRT_FLEXIO2_b.offset000)
#define FLEXIO2_TIMCTL1			(IMXRT_FLEXIO2_b.offset004)
#define FLEXIO2_TIMCTL2			(IMXRT_FLEXIO2_b.offset008)
#define FLEXIO2_TIMCTL3			(IMXRT_FLEXIO2_b.offset00C)
#define FLEXIO2_TIMCTL4			(IMXRT_FLEXIO2_b.offset010)
#define FLEXIO2_TIMCTL5			(IMXRT_FLEXIO2_b.offset014)
#define FLEXIO2_TIMCTL6			(IMXRT_FLEXIO2_b.offset018)
#define FLEXIO2_TIMCTL7			(IMXRT_FLEXIO2_b.offset01C)
#define FLEXIO2_TIMCFG0			(IMXRT_FLEXIO2_b.offset080)
#define FLEXIO2_TIMCFG1			(IMXRT_FLEXIO2_b.offset084)
#define FLEXIO2_TIMCFG2			(IMXRT_FLEXIO2_b.offset088)
#define FLEXIO2_TIMCFG3			(IMXRT_FLEXIO2_b.offset08C)
#define FLEXIO2_TIMCFG4			(IMXRT_FLEXIO2_b.offset090)
#define FLEXIO2_TIMCFG5			(IMXRT_FLEXIO2_b.offset094)
#define FLEXIO2_TIMCFG6			(IMXRT_FLEXIO2_b.offset098)
#define FLEXIO2_TIMCFG7			(IMXRT_FLEXIO2_b.offset09C)
#define FLEXIO2_TIMCMP0			(IMXRT_FLEXIO2_b.offset100)
#define FLEXIO2_TIMCMP1			(IMXRT_FLEXIO2_b.offset104)
#define FLEXIO2_TIMCMP2			(IMXRT_FLEXIO2_b.offset108)
#define FLEXIO2_TIMCMP3			(IMXRT_FLEXIO2_b.offset10C)
#define FLEXIO2_TIMCMP4			(IMXRT_FLEXIO2_b.offset110)
#define FLEXIO2_TIMCMP5			(IMXRT_FLEXIO2_b.offset114)
#define FLEXIO2_TIMCMP6			(IMXRT_FLEXIO2_b.offset118)
#define FLEXIO2_TIMCMP7			(IMXRT_FLEXIO2_b.offset11C)
#define FLEXIO2_SHIFTBUFNBS0		(IMXRT_FLEXIO2_b.offset280)
#define FLEXIO2_SHIFTBUFNBS1		(IMXRT_FLEXIO2_b.offset284)
#define FLEXIO2_SHIFTBUFNBS2		(IMXRT_FLEXIO2_b.offset288)
#define FLEXIO2_SHIFTBUFNBS3		(IMXRT_FLEXIO2_b.offset28C)
#define FLEXIO2_SHIFTBUFNBS4		(IMXRT_FLEXIO2_b.offset290)
#define FLEXIO2_SHIFTBUFNBS5		(IMXRT_FLEXIO2_b.offset294)
#define FLEXIO2_SHIFTBUFNBS6		(IMXRT_FLEXIO2_b.offset298)
#define FLEXIO2_SHIFTBUFNBS7		(IMXRT_FLEXIO2_b.offset29C)
#define FLEXIO2_SHIFTBUFHWS0		(IMXRT_FLEXIO2_b.offset300)
#define FLEXIO2_SHIFTBUFHWS1		(IMXRT_FLEXIO2_b.offset304)
#define FLEXIO2_SHIFTBUFHWS2		(IMXRT_FLEXIO2_b.offset308)
#define FLEXIO2_SHIFTBUFHWS3		(IMXRT_FLEXIO2_b.offset30C)
#define FLEXIO2_SHIFTBUFHWS4		(IMXRT_FLEXIO2_b.offset310)
#define FLEXIO2_SHIFTBUFHWS5		(IMXRT_FLEXIO2_b.offset314)
#define FLEXIO2_SHIFTBUFHWS6		(IMXRT_FLEXIO2_b.offset318)
#define FLEXIO2_SHIFTBUFHWS7		(IMXRT_FLEXIO2_b.offset31C)
#define FLEXIO2_SHIFTBUFNIS0		(IMXRT_FLEXIO2_b.offset380)
#define FLEXIO2_SHIFTBUFNIS1		(IMXRT_FLEXIO2_b.offset384)
#define FLEXIO2_SHIFTBUFNIS2		(IMXRT_FLEXIO2_b.offset388)
#define FLEXIO2_SHIFTBUFNIS3		(IMXRT_FLEXIO2_b.offset38C)
#define FLEXIO2_SHIFTBUFNIS4		(IMXRT_FLEXIO2_b.offset390)
#define FLEXIO2_SHIFTBUFNIS5		(IMXRT_FLEXIO2_b.offset394)
#define FLEXIO2_SHIFTBUFNIS6		(IMXRT_FLEXIO2_b.offset398)
#define FLEXIO2_SHIFTBUFNIS7		(IMXRT_FLEXIO2_b.offset39C)
// FLEXIO3 only present in RT1062
#define IMXRT_FLEXIO3		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXIO3_ADDRESS)
#define IMXRT_FLEXIO3_b		(*(IMXRT_REGISTER32_t *)(IMXRT_FLEXIO3_ADDRESS+0x400))
#define FLEXIO3_VERID			(IMXRT_FLEXIO3.offset000)
#define FLEXIO3_PARAM			(IMXRT_FLEXIO3.offset004)
#define FLEXIO3_CTRL			(IMXRT_FLEXIO3.offset008)
#define FLEXIO3_PIN			(IMXRT_FLEXIO3.offset00C)
#define FLEXIO3_SHIFTSTAT		(IMXRT_FLEXIO3.offset010)
#define FLEXIO3_SHIFTERR		(IMXRT_FLEXIO3.offset014)
#define FLEXIO3_TIMSTAT			(IMXRT_FLEXIO3.offset018)
#define FLEXIO3_SHIFTSIEN		(IMXRT_FLEXIO3.offset020)
#define FLEXIO3_SHIFTEIEN		(IMXRT_FLEXIO3.offset024)
#define FLEXIO3_TIMIEN			(IMXRT_FLEXIO3.offset028)
#define FLEXIO3_SHIFTSDEN		(IMXRT_FLEXIO3.offset030)
#define FLEXIO3_SHIFTSTATE		(IMXRT_FLEXIO3.offset040)
#define FLEXIO3_SHIFTCTL0		(IMXRT_FLEXIO3.offset080)
#define FLEXIO3_SHIFTCTL1		(IMXRT_FLEXIO3.offset084)
#define FLEXIO3_SHIFTCTL2		(IMXRT_FLEXIO3.offset088)
#define FLEXIO3_SHIFTCTL3		(IMXRT_FLEXIO3.offset08C)
#define FLEXIO3_SHIFTCTL4		(IMXRT_FLEXIO3.offset090)
#define FLEXIO3_SHIFTCTL5		(IMXRT_FLEXIO3.offset094)
#define FLEXIO3_SHIFTCTL6		(IMXRT_FLEXIO3.offset098)
#define FLEXIO3_SHIFTCTL7		(IMXRT_FLEXIO3.offset09C)
#define FLEXIO3_SHIFTCFG0		(IMXRT_FLEXIO3.offset100)
#define FLEXIO3_SHIFTCFG1		(IMXRT_FLEXIO3.offset104)
#define FLEXIO3_SHIFTCFG2		(IMXRT_FLEXIO3.offset108)
#define FLEXIO3_SHIFTCFG3		(IMXRT_FLEXIO3.offset10C)
#define FLEXIO3_SHIFTCFG4		(IMXRT_FLEXIO3.offset110)
#define FLEXIO3_SHIFTCFG5		(IMXRT_FLEXIO3.offset114)
#define FLEXIO3_SHIFTCFG6		(IMXRT_FLEXIO3.offset118)
#define FLEXIO3_SHIFTCFG7		(IMXRT_FLEXIO3.offset11C)
#define FLEXIO3_SHIFTBUF0		(IMXRT_FLEXIO3.offset200)
#define FLEXIO3_SHIFTBUF1		(IMXRT_FLEXIO3.offset204)
#define FLEXIO3_SHIFTBUF2		(IMXRT_FLEXIO3.offset208)
#define FLEXIO3_SHIFTBUF3		(IMXRT_FLEXIO3.offset20C)
#define FLEXIO3_SHIFTBUF4		(IMXRT_FLEXIO3.offset210)
#define FLEXIO3_SHIFTBUF5		(IMXRT_FLEXIO3.offset214)
#define FLEXIO3_SHIFTBUF6		(IMXRT_FLEXIO3.offset218)
#define FLEXIO3_SHIFTBUF7		(IMXRT_FLEXIO3.offset21C)
#define FLEXIO3_SHIFTBUFBIS0		(IMXRT_FLEXIO3.offset280)
#define FLEXIO3_SHIFTBUFBIS1		(IMXRT_FLEXIO3.offset284)
#define FLEXIO3_SHIFTBUFBIS2		(IMXRT_FLEXIO3.offset288)
#define FLEXIO3_SHIFTBUFBIS3		(IMXRT_FLEXIO3.offset28C)
#define FLEXIO3_SHIFTBUFBIS4		(IMXRT_FLEXIO3.offset290)
#define FLEXIO3_SHIFTBUFBIS5		(IMXRT_FLEXIO3.offset294)
#define FLEXIO3_SHIFTBUFBIS6		(IMXRT_FLEXIO3.offset298)
#define FLEXIO3_SHIFTBUFBIS7		(IMXRT_FLEXIO3.offset29C)
#define FLEXIO3_SHIFTBUFBYS0		(IMXRT_FLEXIO3.offset300)
#define FLEXIO3_SHIFTBUFBYS1		(IMXRT_FLEXIO3.offset304)
#define FLEXIO3_SHIFTBUFBYS2		(IMXRT_FLEXIO3.offset308)
#define FLEXIO3_SHIFTBUFBYS3		(IMXRT_FLEXIO3.offset30C)
#define FLEXIO3_SHIFTBUFBYS4		(IMXRT_FLEXIO3.offset310)
#define FLEXIO3_SHIFTBUFBYS5		(IMXRT_FLEXIO3.offset314)
#define FLEXIO3_SHIFTBUFBYS6		(IMXRT_FLEXIO3.offset318)
#define FLEXIO3_SHIFTBUFBYS7		(IMXRT_FLEXIO3.offset31C)
#define FLEXIO3_SHIFTBUFBBS0		(IMXRT_FLEXIO3.offset380)
#define FLEXIO3_SHIFTBUFBBS1		(IMXRT_FLEXIO3.offset384)
#define FLEXIO3_SHIFTBUFBBS2		(IMXRT_FLEXIO3.offset388)
#define FLEXIO3_SHIFTBUFBBS3		(IMXRT_FLEXIO3.offset38C)
#define FLEXIO3_SHIFTBUFBBS4		(IMXRT_FLEXIO3.offset390)
#define FLEXIO3_SHIFTBUFBBS5		(IMXRT_FLEXIO3.offset394)
#define FLEXIO3_SHIFTBUFBBS6		(IMXRT_FLEXIO3.offset398)
#define FLEXIO3_SHIFTBUFBBS7		(IMXRT_FLEXIO3.offset39C)
#define FLEXIO3_TIMCTL0			(IMXRT_FLEXIO3_b.offset000)
#define FLEXIO3_TIMCTL1			(IMXRT_FLEXIO3_b.offset004)
#define FLEXIO3_TIMCTL2			(IMXRT_FLEXIO3_b.offset008)
#define FLEXIO3_TIMCTL3			(IMXRT_FLEXIO3_b.offset00C)
#define FLEXIO3_TIMCTL4			(IMXRT_FLEXIO3_b.offset010)
#define FLEXIO3_TIMCTL5			(IMXRT_FLEXIO3_b.offset014)
#define FLEXIO3_TIMCTL6			(IMXRT_FLEXIO3_b.offset018)
#define FLEXIO3_TIMCTL7			(IMXRT_FLEXIO3_b.offset01C)
#define FLEXIO3_TIMCFG0			(IMXRT_FLEXIO3_b.offset080)
#define FLEXIO3_TIMCFG1			(IMXRT_FLEXIO3_b.offset084)
#define FLEXIO3_TIMCFG2			(IMXRT_FLEXIO3_b.offset088)
#define FLEXIO3_TIMCFG3			(IMXRT_FLEXIO3_b.offset08C)
#define FLEXIO3_TIMCFG4			(IMXRT_FLEXIO3_b.offset090)
#define FLEXIO3_TIMCFG5			(IMXRT_FLEXIO3_b.offset094)
#define FLEXIO3_TIMCFG6			(IMXRT_FLEXIO3_b.offset098)
#define FLEXIO3_TIMCFG7			(IMXRT_FLEXIO3_b.offset09C)
#define FLEXIO3_TIMCMP0			(IMXRT_FLEXIO3_b.offset100)
#define FLEXIO3_TIMCMP1			(IMXRT_FLEXIO3_b.offset104)
#define FLEXIO3_TIMCMP2			(IMXRT_FLEXIO3_b.offset108)
#define FLEXIO3_TIMCMP3			(IMXRT_FLEXIO3_b.offset10C)
#define FLEXIO3_TIMCMP4			(IMXRT_FLEXIO3_b.offset110)
#define FLEXIO3_TIMCMP5			(IMXRT_FLEXIO3_b.offset114)
#define FLEXIO3_TIMCMP6			(IMXRT_FLEXIO3_b.offset118)
#define FLEXIO3_TIMCMP7			(IMXRT_FLEXIO3_b.offset11C)
#define FLEXIO3_SHIFTBUFNBS0		(IMXRT_FLEXIO3_b.offset280)
#define FLEXIO3_SHIFTBUFNBS1		(IMXRT_FLEXIO3_b.offset284)
#define FLEXIO3_SHIFTBUFNBS2		(IMXRT_FLEXIO3_b.offset288)
#define FLEXIO3_SHIFTBUFNBS3		(IMXRT_FLEXIO3_b.offset28C)
#define FLEXIO3_SHIFTBUFNBS4		(IMXRT_FLEXIO3_b.offset290)
#define FLEXIO3_SHIFTBUFNBS5		(IMXRT_FLEXIO3_b.offset294)
#define FLEXIO3_SHIFTBUFNBS6		(IMXRT_FLEXIO3_b.offset298)
#define FLEXIO3_SHIFTBUFNBS7		(IMXRT_FLEXIO3_b.offset29C)
#define FLEXIO3_SHIFTBUFHWS0		(IMXRT_FLEXIO3_b.offset300)
#define FLEXIO3_SHIFTBUFHWS1		(IMXRT_FLEXIO3_b.offset304)
#define FLEXIO3_SHIFTBUFHWS2		(IMXRT_FLEXIO3_b.offset308)
#define FLEXIO3_SHIFTBUFHWS3		(IMXRT_FLEXIO3_b.offset30C)
#define FLEXIO3_SHIFTBUFHWS4		(IMXRT_FLEXIO3_b.offset310)
#define FLEXIO3_SHIFTBUFHWS5		(IMXRT_FLEXIO3_b.offset314)
#define FLEXIO3_SHIFTBUFHWS6		(IMXRT_FLEXIO3_b.offset318)
#define FLEXIO3_SHIFTBUFHWS7		(IMXRT_FLEXIO3_b.offset31C)
#define FLEXIO3_SHIFTBUFNIS0		(IMXRT_FLEXIO3_b.offset380)
#define FLEXIO3_SHIFTBUFNIS1		(IMXRT_FLEXIO3_b.offset384)
#define FLEXIO3_SHIFTBUFNIS2		(IMXRT_FLEXIO3_b.offset388)
#define FLEXIO3_SHIFTBUFNIS3		(IMXRT_FLEXIO3_b.offset38C)
#define FLEXIO3_SHIFTBUFNIS4		(IMXRT_FLEXIO3_b.offset390)
#define FLEXIO3_SHIFTBUFNIS5		(IMXRT_FLEXIO3_b.offset394)
#define FLEXIO3_SHIFTBUFNIS6		(IMXRT_FLEXIO3_b.offset398)
#define FLEXIO3_SHIFTBUFNIS7		(IMXRT_FLEXIO3_b.offset39C)
#define FLEXIO_CTRL_DOZEN			((uint32_t)(1<<31))
#define FLEXIO_CTRL_DBGE			((uint32_t)(1<<30))
#define FLEXIO_CTRL_FASTACC			((uint32_t)(1<<2))
#define FLEXIO_CTRL_SWRST			((uint32_t)(1<<1))
#define FLEXIO_CTRL_FLEXEN			((uint32_t)(1<<0))
#define FLEXIO_SHIFTCTL_TIMSEL(n)		((uint32_t)(((n) & 0x03) << 24))
#define FLEXIO_SHIFTCTL_TIMPOL			((uint32_t)(1<<23))
#define FLEXIO_SHIFTCTL_PINCFG(n)		((uint32_t)(((n) & 0x03) << 16))
#define FLEXIO_SHIFTCTL_PINSEL(n)		((uint32_t)(((n) & 0x1F) << 8))
#define FLEXIO_SHIFTCTL_PINPOL			((uint32_t)(1<<7))
#define FLEXIO_SHIFTCTL_SMOD(n)			((uint32_t)(((n) & 0x07) << 0))
#define FLEXIO_SHIFTCFG_PWIDTH(n)		((uint32_t)(((n) & 0x1F) << 16))
#define FLEXIO_SHIFTCFG_INSRC			((uint32_t)(1<<8))
#define FLEXIO_SHIFTCFG_SSTOP(n)		((uint32_t)(((n) & 0x03) << 4))
#define FLEXIO_SHIFTCFG_SSTART(n)		((uint32_t)(((n) & 0x03) << 0))
#define FLEXIO_TIMCTL_TRGSEL(n)			((uint32_t)(((n) & 0x3F) << 24))
#define FLEXIO_TIMCTL_TRGPOL			((uint32_t)(1<<23))
#define FLEXIO_TIMCTL_TRGSRC			((uint32_t)(1<<22))
#define FLEXIO_TIMCTL_PINCFG(n)			((uint32_t)(((n) & 0x03) << 16))
#define FLEXIO_TIMCTL_PINSEL(n)			((uint32_t)(((n) & 0x1F) << 8))
#define FLEXIO_TIMCTL_PINPOL			((uint32_t)(1<<7))
#define FLEXIO_TIMCTL_TIMOD(n)			((uint32_t)(((n) & 0x03) << 0))
#define FLEXIO_TIMCFG_TIMOUT(n)			((uint32_t)(((n) & 0x03) << 24))
#define FLEXIO_TIMCFG_TIMDEC(n)			((uint32_t)(((n) & 0x03) << 20))
#define FLEXIO_TIMCFG_TIMRST(n)			((uint32_t)(((n) & 0x07) << 16))
#define FLEXIO_TIMCFG_TIMDIS(n)			((uint32_t)(((n) & 0x07) << 12))
#define FLEXIO_TIMCFG_TIMENA(n)			((uint32_t)(((n) & 0x07) << 8))
#define FLEXIO_TIMCFG_TSTOP(n)			((uint32_t)(((n) & 0x03) << 4))
#define FLEXIO_TIMCFG_TSTART			((uint32_t)(1<<1))

// 55.8.1: page 3074
typedef struct {
	struct {
		volatile uint16_t CNT;
		volatile uint16_t INIT;
		volatile uint16_t CTRL2;
		volatile uint16_t CTRL;
		volatile uint16_t unused1;
		volatile uint16_t VAL0;
		volatile uint16_t FRACVAL1;
		volatile uint16_t VAL1;
		volatile uint16_t FRACVAL2;
		volatile uint16_t VAL2;
		volatile uint16_t FRACVAL3;
		volatile uint16_t VAL3;
		volatile uint16_t FRACVAL4;
		volatile uint16_t VAL4;
		volatile uint16_t FRACVAL5;
		volatile uint16_t VAL5;
		volatile uint16_t FRCTRL;
		volatile uint16_t OCTRL;
		volatile uint16_t STS;
		volatile uint16_t INTEN;
		volatile uint16_t DMAEN;
		volatile uint16_t TCTRL;
		volatile uint16_t DISMAP0;
		volatile uint16_t DISMAP1;
		volatile uint16_t DTCNT0;
		volatile uint16_t DTCNT1;
		volatile uint16_t CAPTCTRLA;
		volatile uint16_t CAPTCOMPA;
		volatile uint16_t CAPTCTRLB;
		volatile uint16_t CAPTCOMPB;
		volatile uint16_t CAPTCTRLX;
		volatile uint16_t CAPTCOMPX;
		volatile uint16_t CVAL0;
		volatile uint16_t CVAL0CYC;
		volatile uint16_t CVAL1;
		volatile uint16_t CVAL1CYC;
		volatile uint16_t CVAL2;
		volatile uint16_t CVAL2CYC;
		volatile uint16_t CVAL3;
		volatile uint16_t CVAL3CYC;
		volatile uint16_t CVAL4;
		volatile uint16_t CVAL4CYC;
		volatile uint16_t CVAL5;
		volatile uint16_t CVAL5CYC;
		volatile uint16_t unused2;
		volatile uint16_t unused3;
		volatile uint16_t unused4;
		volatile uint16_t unused5;
	} SM[4];
	volatile uint16_t OUTEN;
	volatile uint16_t MASK;
	volatile uint16_t SWCOUT;
	volatile uint16_t DTSRCSEL;
	volatile uint16_t MCTRL;
	volatile uint16_t MCTRL2;
	volatile uint16_t FCTRL0;
	volatile uint16_t FSTS0;
	volatile uint16_t FFILT0;
	volatile uint16_t FTST0;
	volatile uint16_t FCTRL20;
} IMXRT_FLEXPWM_t;
#define IMXRT_FLEXPWM1		(*(IMXRT_FLEXPWM_t *)IMXRT_FLEXPWM1_ADDRESS)
#define IMXRT_FLEXPWM2		(*(IMXRT_FLEXPWM_t *)IMXRT_FLEXPWM2_ADDRESS)
#define IMXRT_FLEXPWM3		(*(IMXRT_FLEXPWM_t *)IMXRT_FLEXPWM3_ADDRESS)
#define IMXRT_FLEXPWM4		(*(IMXRT_FLEXPWM_t *)IMXRT_FLEXPWM4_ADDRESS)
#define FLEXPWM1_SM0CNT			(IMXRT_FLEXPWM1.SM[0].CNT)
#define FLEXPWM1_SM0INIT		(IMXRT_FLEXPWM1.SM[0].INIT)
#define FLEXPWM1_SM0CTRL2		(IMXRT_FLEXPWM1.SM[0].CTRL2)
#define FLEXPWM1_SM0CTRL		(IMXRT_FLEXPWM1.SM[0].CTRL)
#define FLEXPWM1_SM0VAL0		(IMXRT_FLEXPWM1.SM[0].VAL0)
#define FLEXPWM1_SM0FRACVAL1		(IMXRT_FLEXPWM1.SM[0].FRACVAL1)
#define FLEXPWM1_SM0VAL1		(IMXRT_FLEXPWM1.SM[0].VAL1)
#define FLEXPWM1_SM0FRACVAL2		(IMXRT_FLEXPWM1.SM[0].FRACVAL2)
#define FLEXPWM1_SM0VAL2		(IMXRT_FLEXPWM1.SM[0].VAL2)
#define FLEXPWM1_SM0FRACVAL3		(IMXRT_FLEXPWM1.SM[0].FRACVAL3)
#define FLEXPWM1_SM0VAL3		(IMXRT_FLEXPWM1.SM[0].VAL3)
#define FLEXPWM1_SM0FRACVAL4		(IMXRT_FLEXPWM1.SM[0].FRACVAL4)
#define FLEXPWM1_SM0VAL4		(IMXRT_FLEXPWM1.SM[0].VAL4)
#define FLEXPWM1_SM0FRACVAL5		(IMXRT_FLEXPWM1.SM[0].FRACVAL5)
#define FLEXPWM1_SM0VAL5		(IMXRT_FLEXPWM1.SM[0].VAL5)
#define FLEXPWM1_SM0FRCTRL		(IMXRT_FLEXPWM1.SM[0].FRCTRL)
#define FLEXPWM1_SM0OCTRL		(IMXRT_FLEXPWM1.SM[0].OCTRL)
#define FLEXPWM1_SM0STS			(IMXRT_FLEXPWM1.SM[0].STS)
#define FLEXPWM1_SM0INTEN		(IMXRT_FLEXPWM1.SM[0].INTEN)
#define FLEXPWM1_SM0DMAEN		(IMXRT_FLEXPWM1.SM[0].DMAEN)
#define FLEXPWM1_SM0TCTRL		(IMXRT_FLEXPWM1.SM[0].TCTRL)
#define FLEXPWM1_SM0DISMAP0		(IMXRT_FLEXPWM1.SM[0].DISMAP0)
#define FLEXPWM1_SM0DISMAP1		(IMXRT_FLEXPWM1.SM[0].DISMAP1)
#define FLEXPWM1_SM0DTCNT0		(IMXRT_FLEXPWM1.SM[0].DTCNT0)
#define FLEXPWM1_SM0DTCNT1		(IMXRT_FLEXPWM1.SM[0].DTCNT1)
#define FLEXPWM1_SM0CAPTCTRLA		(IMXRT_FLEXPWM1.SM[0].CAPTCTRLA)
#define FLEXPWM1_SM0CAPTCOMPA		(IMXRT_FLEXPWM1.SM[0].CAPTCOMPA)
#define FLEXPWM1_SM0CAPTCTRLB		(IMXRT_FLEXPWM1.SM[0].CAPTCTRLB)
#define FLEXPWM1_SM0CAPTCOMPB		(IMXRT_FLEXPWM1.SM[0].CAPTCOMPB)
#define FLEXPWM1_SM0CAPTCTRLX		(IMXRT_FLEXPWM1.SM[0].CAPTCTRLX)
#define FLEXPWM1_SM0CAPTCOMPX		(IMXRT_FLEXPWM1.SM[0].CAPTCOMPX)
#define FLEXPWM1_SM0CVAL0		(IMXRT_FLEXPWM1.SM[0].CVAL0)
#define FLEXPWM1_SM0CVAL0CYC		(IMXRT_FLEXPWM1.SM[0].CVAL0CYC)
#define FLEXPWM1_SM0CVAL1		(IMXRT_FLEXPWM1.SM[0].CVAL1)
#define FLEXPWM1_SM0CVAL1CYC		(IMXRT_FLEXPWM1.SM[0].CVAL1CYC)
#define FLEXPWM1_SM0CVAL2		(IMXRT_FLEXPWM1.SM[0].CVAL2)
#define FLEXPWM1_SM0CVAL2CYC		(IMXRT_FLEXPWM1.SM[0].CVAL2CYC)
#define FLEXPWM1_SM0CVAL3		(IMXRT_FLEXPWM1.SM[0].CVAL3)
#define FLEXPWM1_SM0CVAL3CYC		(IMXRT_FLEXPWM1.SM[0].CVAL3CYC)
#define FLEXPWM1_SM0CVAL4		(IMXRT_FLEXPWM1.SM[0].CVAL4)
#define FLEXPWM1_SM0CVAL4CYC		(IMXRT_FLEXPWM1.SM[0].CVAL4CYC)
#define FLEXPWM1_SM0CVAL5		(IMXRT_FLEXPWM1.SM[0].CVAL5)
#define FLEXPWM1_SM0CVAL5CYC		(IMXRT_FLEXPWM1.SM[0].CVAL5CYC)
#define FLEXPWM1_SM1CNT			(IMXRT_FLEXPWM1.SM[1].CNT)
#define FLEXPWM1_SM1INIT		(IMXRT_FLEXPWM1.SM[1].INIT)
#define FLEXPWM1_SM1CTRL2		(IMXRT_FLEXPWM1.SM[1].CTRL2)
#define FLEXPWM1_SM1CTRL		(IMXRT_FLEXPWM1.SM[1].CTRL)
#define FLEXPWM1_SM1VAL0		(IMXRT_FLEXPWM1.SM[1].VAL0)
#define FLEXPWM1_SM1FRACVAL1		(IMXRT_FLEXPWM1.SM[1].FRACVAL1)
#define FLEXPWM1_SM1VAL1		(IMXRT_FLEXPWM1.SM[1].VAL1)
#define FLEXPWM1_SM1FRACVAL2		(IMXRT_FLEXPWM1.SM[1].FRACVAL2)
#define FLEXPWM1_SM1VAL2		(IMXRT_FLEXPWM1.SM[1].VAL2)
#define FLEXPWM1_SM1FRACVAL3		(IMXRT_FLEXPWM1.SM[1].FRACVAL3)
#define FLEXPWM1_SM1VAL3		(IMXRT_FLEXPWM1.SM[1].VAL3)
#define FLEXPWM1_SM1FRACVAL4		(IMXRT_FLEXPWM1.SM[1].FRACVAL4)
#define FLEXPWM1_SM1VAL4		(IMXRT_FLEXPWM1.SM[1].VAL4)
#define FLEXPWM1_SM1FRACVAL5		(IMXRT_FLEXPWM1.SM[1].FRACVAL5)
#define FLEXPWM1_SM1VAL5		(IMXRT_FLEXPWM1.SM[1].VAL5)
#define FLEXPWM1_SM1FRCTRL		(IMXRT_FLEXPWM1.SM[1].FRCTRL)
#define FLEXPWM1_SM1OCTRL		(IMXRT_FLEXPWM1.SM[1].OCTRL)
#define FLEXPWM1_SM1STS			(IMXRT_FLEXPWM1.SM[1].STS)
#define FLEXPWM1_SM1INTEN		(IMXRT_FLEXPWM1.SM[1].INTEN)
#define FLEXPWM1_SM1DMAEN		(IMXRT_FLEXPWM1.SM[1].DMAEN)
#define FLEXPWM1_SM1TCTRL		(IMXRT_FLEXPWM1.SM[1].TCTRL)
#define FLEXPWM1_SM1DISMAP0		(IMXRT_FLEXPWM1.SM[1].DISMAP0)
#define FLEXPWM1_SM1DISMAP1		(IMXRT_FLEXPWM1.SM[1].DISMAP1)
#define FLEXPWM1_SM1DTCNT0		(IMXRT_FLEXPWM1.SM[1].DTCNT0)
#define FLEXPWM1_SM1DTCNT1		(IMXRT_FLEXPWM1.SM[1].DTCNT1)
#define FLEXPWM1_SM1CAPTCTRLA		(IMXRT_FLEXPWM1.SM[1].CAPTCTRLA)
#define FLEXPWM1_SM1CAPTCOMPA		(IMXRT_FLEXPWM1.SM[1].CAPTCOMPA)
#define FLEXPWM1_SM1CAPTCTRLB		(IMXRT_FLEXPWM1.SM[1].CAPTCTRLB)
#define FLEXPWM1_SM1CAPTCOMPB		(IMXRT_FLEXPWM1.SM[1].CAPTCOMPB)
#define FLEXPWM1_SM1CAPTCTRLX		(IMXRT_FLEXPWM1.SM[1].CAPTCTRLX)
#define FLEXPWM1_SM1CAPTCOMPX		(IMXRT_FLEXPWM1.SM[1].CAPTCOMPX)
#define FLEXPWM1_SM1CVAL0		(IMXRT_FLEXPWM1.SM[1].CVAL0)
#define FLEXPWM1_SM1CVAL0CYC		(IMXRT_FLEXPWM1.SM[1].CVAL0CYC)
#define FLEXPWM1_SM1CVAL1		(IMXRT_FLEXPWM1.SM[1].CVAL1)
#define FLEXPWM1_SM1CVAL1CYC		(IMXRT_FLEXPWM1.SM[1].CVAL1CYC)
#define FLEXPWM1_SM1CVAL2		(IMXRT_FLEXPWM1.SM[1].CVAL2)
#define FLEXPWM1_SM1CVAL2CYC		(IMXRT_FLEXPWM1.SM[1].CVAL2CYC)
#define FLEXPWM1_SM1CVAL3		(IMXRT_FLEXPWM1.SM[1].CVAL3)
#define FLEXPWM1_SM1CVAL3CYC		(IMXRT_FLEXPWM1.SM[1].CVAL3CYC)
#define FLEXPWM1_SM1CVAL4		(IMXRT_FLEXPWM1.SM[1].CVAL4)
#define FLEXPWM1_SM1CVAL4CYC		(IMXRT_FLEXPWM1.SM[1].CVAL4CYC)
#define FLEXPWM1_SM1CVAL5		(IMXRT_FLEXPWM1.SM[1].CVAL5)
#define FLEXPWM1_SM1CVAL5CYC		(IMXRT_FLEXPWM1.SM[1].CVAL5CYC)
#define FLEXPWM1_SM2CNT			(IMXRT_FLEXPWM1.SM[2].CNT)
#define FLEXPWM1_SM2INIT		(IMXRT_FLEXPWM1.SM[2].INIT)
#define FLEXPWM1_SM2CTRL2		(IMXRT_FLEXPWM1.SM[2].CTRL2)
#define FLEXPWM1_SM2CTRL		(IMXRT_FLEXPWM1.SM[2].CTRL)
#define FLEXPWM1_SM2VAL0		(IMXRT_FLEXPWM1.SM[2].VAL0)
#define FLEXPWM1_SM2FRACVAL1		(IMXRT_FLEXPWM1.SM[2].FRACVAL1)
#define FLEXPWM1_SM2VAL1		(IMXRT_FLEXPWM1.SM[2].VAL1)
#define FLEXPWM1_SM2FRACVAL2		(IMXRT_FLEXPWM1.SM[2].FRACVAL2)
#define FLEXPWM1_SM2VAL2		(IMXRT_FLEXPWM1.SM[2].VAL2)
#define FLEXPWM1_SM2FRACVAL3		(IMXRT_FLEXPWM1.SM[2].FRACVAL3)
#define FLEXPWM1_SM2VAL3		(IMXRT_FLEXPWM1.SM[2].VAL3)
#define FLEXPWM1_SM2FRACVAL4		(IMXRT_FLEXPWM1.SM[2].FRACVAL4)
#define FLEXPWM1_SM2VAL4		(IMXRT_FLEXPWM1.SM[2].VAL4)
#define FLEXPWM1_SM2FRACVAL5		(IMXRT_FLEXPWM1.SM[2].FRACVAL5)
#define FLEXPWM1_SM2VAL5		(IMXRT_FLEXPWM1.SM[2].VAL5)
#define FLEXPWM1_SM2FRCTRL		(IMXRT_FLEXPWM1.SM[2].FRCTRL)
#define FLEXPWM1_SM2OCTRL		(IMXRT_FLEXPWM1.SM[2].OCTRL)
#define FLEXPWM1_SM2STS			(IMXRT_FLEXPWM1.SM[2].STS)
#define FLEXPWM1_SM2INTEN		(IMXRT_FLEXPWM1.SM[2].INTEN)
#define FLEXPWM1_SM2DMAEN		(IMXRT_FLEXPWM1.SM[2].DMAEN)
#define FLEXPWM1_SM2TCTRL		(IMXRT_FLEXPWM1.SM[2].TCTRL)
#define FLEXPWM1_SM2DISMAP0		(IMXRT_FLEXPWM1.SM[2].DISMAP0)
#define FLEXPWM1_SM2DISMAP1		(IMXRT_FLEXPWM1.SM[2].DISMAP1)
#define FLEXPWM1_SM2DTCNT0		(IMXRT_FLEXPWM1.SM[2].DTCNT0)
#define FLEXPWM1_SM2DTCNT1		(IMXRT_FLEXPWM1.SM[2].DTCNT1)
#define FLEXPWM1_SM2CAPTCTRLA		(IMXRT_FLEXPWM1.SM[2].CAPTCTRLA)
#define FLEXPWM1_SM2CAPTCOMPA		(IMXRT_FLEXPWM1.SM[2].CAPTCOMPA)
#define FLEXPWM1_SM2CAPTCTRLB		(IMXRT_FLEXPWM1.SM[2].CAPTCTRLB)
#define FLEXPWM1_SM2CAPTCOMPB		(IMXRT_FLEXPWM1.SM[2].CAPTCOMPB)
#define FLEXPWM1_SM2CAPTCTRLX		(IMXRT_FLEXPWM1.SM[2].CAPTCTRLX)
#define FLEXPWM1_SM2CAPTCOMPX		(IMXRT_FLEXPWM1.SM[2].CAPTCOMPX)
#define FLEXPWM1_SM2CVAL0		(IMXRT_FLEXPWM1.SM[2].CVAL0)
#define FLEXPWM1_SM2CVAL0CYC		(IMXRT_FLEXPWM1.SM[2].CVAL0CYC)
#define FLEXPWM1_SM2CVAL1		(IMXRT_FLEXPWM1.SM[2].CVAL1)
#define FLEXPWM1_SM2CVAL1CYC		(IMXRT_FLEXPWM1.SM[2].CVAL1CYC)
#define FLEXPWM1_SM2CVAL2		(IMXRT_FLEXPWM1.SM[2].CVAL2)
#define FLEXPWM1_SM2CVAL2CYC		(IMXRT_FLEXPWM1.SM[2].CVAL2CYC)
#define FLEXPWM1_SM2CVAL3		(IMXRT_FLEXPWM1.SM[2].CVAL3)
#define FLEXPWM1_SM2CVAL3CYC		(IMXRT_FLEXPWM1.SM[2].CVAL3CYC)
#define FLEXPWM1_SM2CVAL4		(IMXRT_FLEXPWM1.SM[2].CVAL4)
#define FLEXPWM1_SM2CVAL4CYC		(IMXRT_FLEXPWM1.SM[2].CVAL4CYC)
#define FLEXPWM1_SM2CVAL5		(IMXRT_FLEXPWM1.SM[2].CVAL5)
#define FLEXPWM1_SM2CVAL5CYC		(IMXRT_FLEXPWM1.SM[2].CVAL5CYC)
#define FLEXPWM1_SM3CNT			(IMXRT_FLEXPWM1.SM[3].CNT)
#define FLEXPWM1_SM3INIT		(IMXRT_FLEXPWM1.SM[3].INIT)
#define FLEXPWM1_SM3CTRL2		(IMXRT_FLEXPWM1.SM[3].CTRL2)
#define FLEXPWM1_SM3CTRL		(IMXRT_FLEXPWM1.SM[3].CTRL)
#define FLEXPWM1_SM3VAL0		(IMXRT_FLEXPWM1.SM[3].VAL0)
#define FLEXPWM1_SM3FRACVAL1		(IMXRT_FLEXPWM1.SM[3].FRACVAL1)
#define FLEXPWM1_SM3VAL1		(IMXRT_FLEXPWM1.SM[3].VAL1)
#define FLEXPWM1_SM3FRACVAL2		(IMXRT_FLEXPWM1.SM[3].FRACVAL2)
#define FLEXPWM1_SM3VAL2		(IMXRT_FLEXPWM1.SM[3].VAL2)
#define FLEXPWM1_SM3FRACVAL3		(IMXRT_FLEXPWM1.SM[3].FRACVAL3)
#define FLEXPWM1_SM3VAL3		(IMXRT_FLEXPWM1.SM[3].VAL3)
#define FLEXPWM1_SM3FRACVAL4		(IMXRT_FLEXPWM1.SM[3].FRACVAL4)
#define FLEXPWM1_SM3VAL4		(IMXRT_FLEXPWM1.SM[3].VAL4)
#define FLEXPWM1_SM3FRACVAL5		(IMXRT_FLEXPWM1.SM[3].FRACVAL5)
#define FLEXPWM1_SM3VAL5		(IMXRT_FLEXPWM1.SM[3].VAL5)
#define FLEXPWM1_SM3FRCTRL		(IMXRT_FLEXPWM1.SM[3].FRCTRL)
#define FLEXPWM1_SM3OCTRL		(IMXRT_FLEXPWM1.SM[3].OCTRL)
#define FLEXPWM1_SM3STS			(IMXRT_FLEXPWM1.SM[3].STS)
#define FLEXPWM1_SM3INTEN		(IMXRT_FLEXPWM1.SM[3].INTEN)
#define FLEXPWM1_SM3DMAEN		(IMXRT_FLEXPWM1.SM[3].DMAEN)
#define FLEXPWM1_SM3TCTRL		(IMXRT_FLEXPWM1.SM[3].TCTRL)
#define FLEXPWM1_SM3DISMAP0		(IMXRT_FLEXPWM1.SM[3].DISMAP0)
#define FLEXPWM1_SM3DISMAP1		(IMXRT_FLEXPWM1.SM[3].DISMAP1)
#define FLEXPWM1_SM3DTCNT0		(IMXRT_FLEXPWM1.SM[3].DTCNT0)
#define FLEXPWM1_SM3DTCNT1		(IMXRT_FLEXPWM1.SM[3].DTCNT1)
#define FLEXPWM1_SM3CAPTCTRLA		(IMXRT_FLEXPWM1.SM[3].CAPTCTRLA)
#define FLEXPWM1_SM3CAPTCOMPA		(IMXRT_FLEXPWM1.SM[3].CAPTCOMPA)
#define FLEXPWM1_SM3CAPTCTRLB		(IMXRT_FLEXPWM1.SM[3].CAPTCTRLB)
#define FLEXPWM1_SM3CAPTCOMPB		(IMXRT_FLEXPWM1.SM[3].CAPTCOMPB)
#define FLEXPWM1_SM3CAPTCTRLX		(IMXRT_FLEXPWM1.SM[3].CAPTCTRLX)
#define FLEXPWM1_SM3CAPTCOMPX		(IMXRT_FLEXPWM1.SM[3].CAPTCOMPX)
#define FLEXPWM1_SM3CVAL0		(IMXRT_FLEXPWM1.SM[3].CVAL0)
#define FLEXPWM1_SM3CVAL0CYC		(IMXRT_FLEXPWM1.SM[3].CVAL0CYC)
#define FLEXPWM1_SM3CVAL1		(IMXRT_FLEXPWM1.SM[3].CVAL1)
#define FLEXPWM1_SM3CVAL1CYC		(IMXRT_FLEXPWM1.SM[3].CVAL1CYC)
#define FLEXPWM1_SM3CVAL2		(IMXRT_FLEXPWM1.SM[3].CVAL2)
#define FLEXPWM1_SM3CVAL2CYC		(IMXRT_FLEXPWM1.SM[3].CVAL2CYC)
#define FLEXPWM1_SM3CVAL3		(IMXRT_FLEXPWM1.SM[3].CVAL3)
#define FLEXPWM1_SM3CVAL3CYC		(IMXRT_FLEXPWM1.SM[3].CVAL3CYC)
#define FLEXPWM1_SM3CVAL4		(IMXRT_FLEXPWM1.SM[3].CVAL4)
#define FLEXPWM1_SM3CVAL4CYC		(IMXRT_FLEXPWM1.SM[3].CVAL4CYC)
#define FLEXPWM1_SM3CVAL5		(IMXRT_FLEXPWM1.SM[3].CVAL5)
#define FLEXPWM1_SM3CVAL5CYC		(IMXRT_FLEXPWM1.SM[3].CVAL5CYC)
#define FLEXPWM1_OUTEN			(IMXRT_FLEXPWM1.OUTEN)
#define FLEXPWM1_MASK			(IMXRT_FLEXPWM1.MASK)
#define FLEXPWM1_SWCOUT			(IMXRT_FLEXPWM1.SWCOUT)
#define FLEXPWM1_DTSRCSEL		(IMXRT_FLEXPWM1.DTSRCSEL)
#define FLEXPWM1_MCTRL			(IMXRT_FLEXPWM1.MCTRL)
#define FLEXPWM1_MCTRL2			(IMXRT_FLEXPWM1.MCTRL2)
#define FLEXPWM1_FCTRL0			(IMXRT_FLEXPWM1.FCTRL0)
#define FLEXPWM1_FSTS0			(IMXRT_FLEXPWM1.FSTS0)
#define FLEXPWM1_FFILT0			(IMXRT_FLEXPWM1.FFILT0)
#define FLEXPWM1_FTST0			(IMXRT_FLEXPWM1.FTST0)
#define FLEXPWM1_FCTRL20		(IMXRT_FLEXPWM1.FCTRL20)
#define FLEXPWM2_SM0CNT			(IMXRT_FLEXPWM2.SM[0].CNT)
#define FLEXPWM2_SM0INIT		(IMXRT_FLEXPWM2.SM[0].INIT)
#define FLEXPWM2_SM0CTRL2		(IMXRT_FLEXPWM2.SM[0].CTRL2)
#define FLEXPWM2_SM0CTRL		(IMXRT_FLEXPWM2.SM[0].CTRL)
#define FLEXPWM2_SM0VAL0		(IMXRT_FLEXPWM2.SM[0].VAL0)
#define FLEXPWM2_SM0FRACVAL1		(IMXRT_FLEXPWM2.SM[0].FRACVAL1)
#define FLEXPWM2_SM0VAL1		(IMXRT_FLEXPWM2.SM[0].VAL1)
#define FLEXPWM2_SM0FRACVAL2		(IMXRT_FLEXPWM2.SM[0].FRACVAL2)
#define FLEXPWM2_SM0VAL2		(IMXRT_FLEXPWM2.SM[0].VAL2)
#define FLEXPWM2_SM0FRACVAL3		(IMXRT_FLEXPWM2.SM[0].FRACVAL3)
#define FLEXPWM2_SM0VAL3		(IMXRT_FLEXPWM2.SM[0].VAL3)
#define FLEXPWM2_SM0FRACVAL4		(IMXRT_FLEXPWM2.SM[0].FRACVAL4)
#define FLEXPWM2_SM0VAL4		(IMXRT_FLEXPWM2.SM[0].VAL4)
#define FLEXPWM2_SM0FRACVAL5		(IMXRT_FLEXPWM2.SM[0].FRACVAL5)
#define FLEXPWM2_SM0VAL5		(IMXRT_FLEXPWM2.SM[0].VAL5)
#define FLEXPWM2_SM0FRCTRL		(IMXRT_FLEXPWM2.SM[0].FRCTRL)
#define FLEXPWM2_SM0OCTRL		(IMXRT_FLEXPWM2.SM[0].OCTRL)
#define FLEXPWM2_SM0STS			(IMXRT_FLEXPWM2.SM[0].STS)
#define FLEXPWM2_SM0INTEN		(IMXRT_FLEXPWM2.SM[0].INTEN)
#define FLEXPWM2_SM0DMAEN		(IMXRT_FLEXPWM2.SM[0].DMAEN)
#define FLEXPWM2_SM0TCTRL		(IMXRT_FLEXPWM2.SM[0].TCTRL)
#define FLEXPWM2_SM0DISMAP0		(IMXRT_FLEXPWM2.SM[0].DISMAP0)
#define FLEXPWM2_SM0DISMAP1		(IMXRT_FLEXPWM2.SM[0].DISMAP1)
#define FLEXPWM2_SM0DTCNT0		(IMXRT_FLEXPWM2.SM[0].DTCNT0)
#define FLEXPWM2_SM0DTCNT1		(IMXRT_FLEXPWM2.SM[0].DTCNT1)
#define FLEXPWM2_SM0CAPTCTRLA		(IMXRT_FLEXPWM2.SM[0].CAPTCTRLA)
#define FLEXPWM2_SM0CAPTCOMPA		(IMXRT_FLEXPWM2.SM[0].CAPTCOMPA)
#define FLEXPWM2_SM0CAPTCTRLB		(IMXRT_FLEXPWM2.SM[0].CAPTCTRLB)
#define FLEXPWM2_SM0CAPTCOMPB		(IMXRT_FLEXPWM2.SM[0].CAPTCOMPB)
#define FLEXPWM2_SM0CAPTCTRLX		(IMXRT_FLEXPWM2.SM[0].CAPTCTRLX)
#define FLEXPWM2_SM0CAPTCOMPX		(IMXRT_FLEXPWM2.SM[0].CAPTCOMPX)
#define FLEXPWM2_SM0CVAL0		(IMXRT_FLEXPWM2.SM[0].CVAL0)
#define FLEXPWM2_SM0CVAL0CYC		(IMXRT_FLEXPWM2.SM[0].CVAL0CYC)
#define FLEXPWM2_SM0CVAL1		(IMXRT_FLEXPWM2.SM[0].CVAL1)
#define FLEXPWM2_SM0CVAL1CYC		(IMXRT_FLEXPWM2.SM[0].CVAL1CYC)
#define FLEXPWM2_SM0CVAL2		(IMXRT_FLEXPWM2.SM[0].CVAL2)
#define FLEXPWM2_SM0CVAL2CYC		(IMXRT_FLEXPWM2.SM[0].CVAL2CYC)
#define FLEXPWM2_SM0CVAL3		(IMXRT_FLEXPWM2.SM[0].CVAL3)
#define FLEXPWM2_SM0CVAL3CYC		(IMXRT_FLEXPWM2.SM[0].CVAL3CYC)
#define FLEXPWM2_SM0CVAL4		(IMXRT_FLEXPWM2.SM[0].CVAL4)
#define FLEXPWM2_SM0CVAL4CYC		(IMXRT_FLEXPWM2.SM[0].CVAL4CYC)
#define FLEXPWM2_SM0CVAL5		(IMXRT_FLEXPWM2.SM[0].CVAL5)
#define FLEXPWM2_SM0CVAL5CYC		(IMXRT_FLEXPWM2.SM[0].CVAL5CYC)
#define FLEXPWM2_SM1CNT			(IMXRT_FLEXPWM2.SM[1].CNT)
#define FLEXPWM2_SM1INIT		(IMXRT_FLEXPWM2.SM[1].INIT)
#define FLEXPWM2_SM1CTRL2		(IMXRT_FLEXPWM2.SM[1].CTRL2)
#define FLEXPWM2_SM1CTRL		(IMXRT_FLEXPWM2.SM[1].CTRL)
#define FLEXPWM2_SM1VAL0		(IMXRT_FLEXPWM2.SM[1].VAL0)
#define FLEXPWM2_SM1FRACVAL1		(IMXRT_FLEXPWM2.SM[1].FRACVAL1)
#define FLEXPWM2_SM1VAL1		(IMXRT_FLEXPWM2.SM[1].VAL1)
#define FLEXPWM2_SM1FRACVAL2		(IMXRT_FLEXPWM2.SM[1].FRACVAL2)
#define FLEXPWM2_SM1VAL2		(IMXRT_FLEXPWM2.SM[1].VAL2)
#define FLEXPWM2_SM1FRACVAL3		(IMXRT_FLEXPWM2.SM[1].FRACVAL3)
#define FLEXPWM2_SM1VAL3		(IMXRT_FLEXPWM2.SM[1].VAL3)
#define FLEXPWM2_SM1FRACVAL4		(IMXRT_FLEXPWM2.SM[1].FRACVAL4)
#define FLEXPWM2_SM1VAL4		(IMXRT_FLEXPWM2.SM[1].VAL4)
#define FLEXPWM2_SM1FRACVAL5		(IMXRT_FLEXPWM2.SM[1].FRACVAL5)
#define FLEXPWM2_SM1VAL5		(IMXRT_FLEXPWM2.SM[1].VAL5)
#define FLEXPWM2_SM1FRCTRL		(IMXRT_FLEXPWM2.SM[1].FRCTRL)
#define FLEXPWM2_SM1OCTRL		(IMXRT_FLEXPWM2.SM[1].OCTRL)
#define FLEXPWM2_SM1STS			(IMXRT_FLEXPWM2.SM[1].STS)
#define FLEXPWM2_SM1INTEN		(IMXRT_FLEXPWM2.SM[1].INTEN)
#define FLEXPWM2_SM1DMAEN		(IMXRT_FLEXPWM2.SM[1].DMAEN)
#define FLEXPWM2_SM1TCTRL		(IMXRT_FLEXPWM2.SM[1].TCTRL)
#define FLEXPWM2_SM1DISMAP0		(IMXRT_FLEXPWM2.SM[1].DISMAP0)
#define FLEXPWM2_SM1DISMAP1		(IMXRT_FLEXPWM2.SM[1].DISMAP1)
#define FLEXPWM2_SM1DTCNT0		(IMXRT_FLEXPWM2.SM[1].DTCNT0)
#define FLEXPWM2_SM1DTCNT1		(IMXRT_FLEXPWM2.SM[1].DTCNT1)
#define FLEXPWM2_SM1CAPTCTRLA		(IMXRT_FLEXPWM2.SM[1].CAPTCTRLA)
#define FLEXPWM2_SM1CAPTCOMPA		(IMXRT_FLEXPWM2.SM[1].CAPTCOMPA)
#define FLEXPWM2_SM1CAPTCTRLB		(IMXRT_FLEXPWM2.SM[1].CAPTCTRLB)
#define FLEXPWM2_SM1CAPTCOMPB		(IMXRT_FLEXPWM2.SM[1].CAPTCOMPB)
#define FLEXPWM2_SM1CAPTCTRLX		(IMXRT_FLEXPWM2.SM[1].CAPTCTRLX)
#define FLEXPWM2_SM1CAPTCOMPX		(IMXRT_FLEXPWM2.SM[1].CAPTCOMPX)
#define FLEXPWM2_SM1CVAL0		(IMXRT_FLEXPWM2.SM[1].CVAL0)
#define FLEXPWM2_SM1CVAL0CYC		(IMXRT_FLEXPWM2.SM[1].CVAL0CYC)
#define FLEXPWM2_SM1CVAL1		(IMXRT_FLEXPWM2.SM[1].CVAL1)
#define FLEXPWM2_SM1CVAL1CYC		(IMXRT_FLEXPWM2.SM[1].CVAL1CYC)
#define FLEXPWM2_SM1CVAL2		(IMXRT_FLEXPWM2.SM[1].CVAL2)
#define FLEXPWM2_SM1CVAL2CYC		(IMXRT_FLEXPWM2.SM[1].CVAL2CYC)
#define FLEXPWM2_SM1CVAL3		(IMXRT_FLEXPWM2.SM[1].CVAL3)
#define FLEXPWM2_SM1CVAL3CYC		(IMXRT_FLEXPWM2.SM[1].CVAL3CYC)
#define FLEXPWM2_SM1CVAL4		(IMXRT_FLEXPWM2.SM[1].CVAL4)
#define FLEXPWM2_SM1CVAL4CYC		(IMXRT_FLEXPWM2.SM[1].CVAL4CYC)
#define FLEXPWM2_SM1CVAL5		(IMXRT_FLEXPWM2.SM[1].CVAL5)
#define FLEXPWM2_SM1CVAL5CYC		(IMXRT_FLEXPWM2.SM[1].CVAL5CYC)
#define FLEXPWM2_SM2CNT			(IMXRT_FLEXPWM2.SM[2].CNT)
#define FLEXPWM2_SM2INIT		(IMXRT_FLEXPWM2.SM[2].INIT)
#define FLEXPWM2_SM2CTRL2		(IMXRT_FLEXPWM2.SM[2].CTRL2)
#define FLEXPWM2_SM2CTRL		(IMXRT_FLEXPWM2.SM[2].CTRL)
#define FLEXPWM2_SM2VAL0		(IMXRT_FLEXPWM2.SM[2].VAL0)
#define FLEXPWM2_SM2FRACVAL1		(IMXRT_FLEXPWM2.SM[2].FRACVAL1)
#define FLEXPWM2_SM2VAL1		(IMXRT_FLEXPWM2.SM[2].VAL1)
#define FLEXPWM2_SM2FRACVAL2		(IMXRT_FLEXPWM2.SM[2].FRACVAL2)
#define FLEXPWM2_SM2VAL2		(IMXRT_FLEXPWM2.SM[2].VAL2)
#define FLEXPWM2_SM2FRACVAL3		(IMXRT_FLEXPWM2.SM[2].FRACVAL3)
#define FLEXPWM2_SM2VAL3		(IMXRT_FLEXPWM2.SM[2].VAL3)
#define FLEXPWM2_SM2FRACVAL4		(IMXRT_FLEXPWM2.SM[2].FRACVAL4)
#define FLEXPWM2_SM2VAL4		(IMXRT_FLEXPWM2.SM[2].VAL4)
#define FLEXPWM2_SM2FRACVAL5		(IMXRT_FLEXPWM2.SM[2].FRACVAL5)
#define FLEXPWM2_SM2VAL5		(IMXRT_FLEXPWM2.SM[2].VAL5)
#define FLEXPWM2_SM2FRCTRL		(IMXRT_FLEXPWM2.SM[2].FRCTRL)
#define FLEXPWM2_SM2OCTRL		(IMXRT_FLEXPWM2.SM[2].OCTRL)
#define FLEXPWM2_SM2STS			(IMXRT_FLEXPWM2.SM[2].STS)
#define FLEXPWM2_SM2INTEN		(IMXRT_FLEXPWM2.SM[2].INTEN)
#define FLEXPWM2_SM2DMAEN		(IMXRT_FLEXPWM2.SM[2].DMAEN)
#define FLEXPWM2_SM2TCTRL		(IMXRT_FLEXPWM2.SM[2].TCTRL)
#define FLEXPWM2_SM2DISMAP0		(IMXRT_FLEXPWM2.SM[2].DISMAP0)
#define FLEXPWM2_SM2DISMAP1		(IMXRT_FLEXPWM2.SM[2].DISMAP1)
#define FLEXPWM2_SM2DTCNT0		(IMXRT_FLEXPWM2.SM[2].DTCNT0)
#define FLEXPWM2_SM2DTCNT1		(IMXRT_FLEXPWM2.SM[2].DTCNT1)
#define FLEXPWM2_SM2CAPTCTRLA		(IMXRT_FLEXPWM2.SM[2].CAPTCTRLA)
#define FLEXPWM2_SM2CAPTCOMPA		(IMXRT_FLEXPWM2.SM[2].CAPTCOMPA)
#define FLEXPWM2_SM2CAPTCTRLB		(IMXRT_FLEXPWM2.SM[2].CAPTCTRLB)
#define FLEXPWM2_SM2CAPTCOMPB		(IMXRT_FLEXPWM2.SM[2].CAPTCOMPB)
#define FLEXPWM2_SM2CAPTCTRLX		(IMXRT_FLEXPWM2.SM[2].CAPTCTRLX)
#define FLEXPWM2_SM2CAPTCOMPX		(IMXRT_FLEXPWM2.SM[2].CAPTCOMPX)
#define FLEXPWM2_SM2CVAL0		(IMXRT_FLEXPWM2.SM[2].CVAL0)
#define FLEXPWM2_SM2CVAL0CYC		(IMXRT_FLEXPWM2.SM[2].CVAL0CYC)
#define FLEXPWM2_SM2CVAL1		(IMXRT_FLEXPWM2.SM[2].CVAL1)
#define FLEXPWM2_SM2CVAL1CYC		(IMXRT_FLEXPWM2.SM[2].CVAL1CYC)
#define FLEXPWM2_SM2CVAL2		(IMXRT_FLEXPWM2.SM[2].CVAL2)
#define FLEXPWM2_SM2CVAL2CYC		(IMXRT_FLEXPWM2.SM[2].CVAL2CYC)
#define FLEXPWM2_SM2CVAL3		(IMXRT_FLEXPWM2.SM[2].CVAL3)
#define FLEXPWM2_SM2CVAL3CYC		(IMXRT_FLEXPWM2.SM[2].CVAL3CYC)
#define FLEXPWM2_SM2CVAL4		(IMXRT_FLEXPWM2.SM[2].CVAL4)
#define FLEXPWM2_SM2CVAL4CYC		(IMXRT_FLEXPWM2.SM[2].CVAL4CYC)
#define FLEXPWM2_SM2CVAL5		(IMXRT_FLEXPWM2.SM[2].CVAL5)
#define FLEXPWM2_SM2CVAL5CYC		(IMXRT_FLEXPWM2.SM[2].CVAL5CYC)
#define FLEXPWM2_SM3CNT			(IMXRT_FLEXPWM2.SM[3].CNT)
#define FLEXPWM2_SM3INIT		(IMXRT_FLEXPWM2.SM[3].INIT)
#define FLEXPWM2_SM3CTRL2		(IMXRT_FLEXPWM2.SM[3].CTRL2)
#define FLEXPWM2_SM3CTRL		(IMXRT_FLEXPWM2.SM[3].CTRL)
#define FLEXPWM2_SM3VAL0		(IMXRT_FLEXPWM2.SM[3].VAL0)
#define FLEXPWM2_SM3FRACVAL1		(IMXRT_FLEXPWM2.SM[3].FRACVAL1)
#define FLEXPWM2_SM3VAL1		(IMXRT_FLEXPWM2.SM[3].VAL1)
#define FLEXPWM2_SM3FRACVAL2		(IMXRT_FLEXPWM2.SM[3].FRACVAL2)
#define FLEXPWM2_SM3VAL2		(IMXRT_FLEXPWM2.SM[3].VAL2)
#define FLEXPWM2_SM3FRACVAL3		(IMXRT_FLEXPWM2.SM[3].FRACVAL3)
#define FLEXPWM2_SM3VAL3		(IMXRT_FLEXPWM2.SM[3].VAL3)
#define FLEXPWM2_SM3FRACVAL4		(IMXRT_FLEXPWM2.SM[3].FRACVAL4)
#define FLEXPWM2_SM3VAL4		(IMXRT_FLEXPWM2.SM[3].VAL4)
#define FLEXPWM2_SM3FRACVAL5		(IMXRT_FLEXPWM2.SM[3].FRACVAL5)
#define FLEXPWM2_SM3VAL5		(IMXRT_FLEXPWM2.SM[3].VAL5)
#define FLEXPWM2_SM3FRCTRL		(IMXRT_FLEXPWM2.SM[3].FRCTRL)
#define FLEXPWM2_SM3OCTRL		(IMXRT_FLEXPWM2.SM[3].OCTRL)
#define FLEXPWM2_SM3STS			(IMXRT_FLEXPWM2.SM[3].STS)
#define FLEXPWM2_SM3INTEN		(IMXRT_FLEXPWM2.SM[3].INTEN)
#define FLEXPWM2_SM3DMAEN		(IMXRT_FLEXPWM2.SM[3].DMAEN)
#define FLEXPWM2_SM3TCTRL		(IMXRT_FLEXPWM2.SM[3].TCTRL)
#define FLEXPWM2_SM3DISMAP0		(IMXRT_FLEXPWM2.SM[3].DISMAP0)
#define FLEXPWM2_SM3DISMAP1		(IMXRT_FLEXPWM2.SM[3].DISMAP1)
#define FLEXPWM2_SM3DTCNT0		(IMXRT_FLEXPWM2.SM[3].DTCNT0)
#define FLEXPWM2_SM3DTCNT1		(IMXRT_FLEXPWM2.SM[3].DTCNT1)
#define FLEXPWM2_SM3CAPTCTRLA		(IMXRT_FLEXPWM2.SM[3].CAPTCTRLA)
#define FLEXPWM2_SM3CAPTCOMPA		(IMXRT_FLEXPWM2.SM[3].CAPTCOMPA)
#define FLEXPWM2_SM3CAPTCTRLB		(IMXRT_FLEXPWM2.SM[3].CAPTCTRLB)
#define FLEXPWM2_SM3CAPTCOMPB		(IMXRT_FLEXPWM2.SM[3].CAPTCOMPB)
#define FLEXPWM2_SM3CAPTCTRLX		(IMXRT_FLEXPWM2.SM[3].CAPTCTRLX)
#define FLEXPWM2_SM3CAPTCOMPX		(IMXRT_FLEXPWM2.SM[3].CAPTCOMPX)
#define FLEXPWM2_SM3CVAL0		(IMXRT_FLEXPWM2.SM[3].CVAL0)
#define FLEXPWM2_SM3CVAL0CYC		(IMXRT_FLEXPWM2.SM[3].CVAL0CYC)
#define FLEXPWM2_SM3CVAL1		(IMXRT_FLEXPWM2.SM[3].CVAL1)
#define FLEXPWM2_SM3CVAL1CYC		(IMXRT_FLEXPWM2.SM[3].CVAL1CYC)
#define FLEXPWM2_SM3CVAL2		(IMXRT_FLEXPWM2.SM[3].CVAL2)
#define FLEXPWM2_SM3CVAL2CYC		(IMXRT_FLEXPWM2.SM[3].CVAL2CYC)
#define FLEXPWM2_SM3CVAL3		(IMXRT_FLEXPWM2.SM[3].CVAL3)
#define FLEXPWM2_SM3CVAL3CYC		(IMXRT_FLEXPWM2.SM[3].CVAL3CYC)
#define FLEXPWM2_SM3CVAL4		(IMXRT_FLEXPWM2.SM[3].CVAL4)
#define FLEXPWM2_SM3CVAL4CYC		(IMXRT_FLEXPWM2.SM[3].CVAL4CYC)
#define FLEXPWM2_SM3CVAL5		(IMXRT_FLEXPWM2.SM[3].CVAL5)
#define FLEXPWM2_SM3CVAL5CYC		(IMXRT_FLEXPWM2.SM[3].CVAL5CYC)
#define FLEXPWM2_OUTEN			(IMXRT_FLEXPWM2.OUTEN)
#define FLEXPWM2_MASK			(IMXRT_FLEXPWM2.MASK)
#define FLEXPWM2_SWCOUT			(IMXRT_FLEXPWM2.SWCOUT)
#define FLEXPWM2_DTSRCSEL		(IMXRT_FLEXPWM2.DTSRCSEL)
#define FLEXPWM2_MCTRL			(IMXRT_FLEXPWM2.MCTRL)
#define FLEXPWM2_MCTRL2			(IMXRT_FLEXPWM2.MCTRL2)
#define FLEXPWM2_FCTRL0			(IMXRT_FLEXPWM2.FCTRL0)
#define FLEXPWM2_FSTS0			(IMXRT_FLEXPWM2.FSTS0)
#define FLEXPWM2_FFILT0			(IMXRT_FLEXPWM2.FFILT0)
#define FLEXPWM2_FTST0			(IMXRT_FLEXPWM2.FTST0)
#define FLEXPWM2_FCTRL20		(IMXRT_FLEXPWM2.FCTRL20)
#define FLEXPWM3_SM0CNT			(IMXRT_FLEXPWM3.SM[0].CNT)
#define FLEXPWM3_SM0INIT		(IMXRT_FLEXPWM3.SM[0].INIT)
#define FLEXPWM3_SM0CTRL2		(IMXRT_FLEXPWM3.SM[0].CTRL2)
#define FLEXPWM3_SM0CTRL		(IMXRT_FLEXPWM3.SM[0].CTRL)
#define FLEXPWM3_SM0VAL0		(IMXRT_FLEXPWM3.SM[0].VAL0)
#define FLEXPWM3_SM0FRACVAL1		(IMXRT_FLEXPWM3.SM[0].FRACVAL1)
#define FLEXPWM3_SM0VAL1		(IMXRT_FLEXPWM3.SM[0].VAL1)
#define FLEXPWM3_SM0FRACVAL2		(IMXRT_FLEXPWM3.SM[0].FRACVAL2)
#define FLEXPWM3_SM0VAL2		(IMXRT_FLEXPWM3.SM[0].VAL2)
#define FLEXPWM3_SM0FRACVAL3		(IMXRT_FLEXPWM3.SM[0].FRACVAL3)
#define FLEXPWM3_SM0VAL3		(IMXRT_FLEXPWM3.SM[0].VAL3)
#define FLEXPWM3_SM0FRACVAL4		(IMXRT_FLEXPWM3.SM[0].FRACVAL4)
#define FLEXPWM3_SM0VAL4		(IMXRT_FLEXPWM3.SM[0].VAL4)
#define FLEXPWM3_SM0FRACVAL5		(IMXRT_FLEXPWM3.SM[0].FRACVAL5)
#define FLEXPWM3_SM0VAL5		(IMXRT_FLEXPWM3.SM[0].VAL5)
#define FLEXPWM3_SM0FRCTRL		(IMXRT_FLEXPWM3.SM[0].FRCTRL)
#define FLEXPWM3_SM0OCTRL		(IMXRT_FLEXPWM3.SM[0].OCTRL)
#define FLEXPWM3_SM0STS			(IMXRT_FLEXPWM3.SM[0].STS)
#define FLEXPWM3_SM0INTEN		(IMXRT_FLEXPWM3.SM[0].INTEN)
#define FLEXPWM3_SM0DMAEN		(IMXRT_FLEXPWM3.SM[0].DMAEN)
#define FLEXPWM3_SM0TCTRL		(IMXRT_FLEXPWM3.SM[0].TCTRL)
#define FLEXPWM3_SM0DISMAP0		(IMXRT_FLEXPWM3.SM[0].DISMAP0)
#define FLEXPWM3_SM0DISMAP1		(IMXRT_FLEXPWM3.SM[0].DISMAP1)
#define FLEXPWM3_SM0DTCNT0		(IMXRT_FLEXPWM3.SM[0].DTCNT0)
#define FLEXPWM3_SM0DTCNT1		(IMXRT_FLEXPWM3.SM[0].DTCNT1)
#define FLEXPWM3_SM0CAPTCTRLA		(IMXRT_FLEXPWM3.SM[0].CAPTCTRLA)
#define FLEXPWM3_SM0CAPTCOMPA		(IMXRT_FLEXPWM3.SM[0].CAPTCOMPA)
#define FLEXPWM3_SM0CAPTCTRLB		(IMXRT_FLEXPWM3.SM[0].CAPTCTRLB)
#define FLEXPWM3_SM0CAPTCOMPB		(IMXRT_FLEXPWM3.SM[0].CAPTCOMPB)
#define FLEXPWM3_SM0CAPTCTRLX		(IMXRT_FLEXPWM3.SM[0].CAPTCTRLX)
#define FLEXPWM3_SM0CAPTCOMPX		(IMXRT_FLEXPWM3.SM[0].CAPTCOMPX)
#define FLEXPWM3_SM0CVAL0		(IMXRT_FLEXPWM3.SM[0].CVAL0)
#define FLEXPWM3_SM0CVAL0CYC		(IMXRT_FLEXPWM3.SM[0].CVAL0CYC)
#define FLEXPWM3_SM0CVAL1		(IMXRT_FLEXPWM3.SM[0].CVAL1)
#define FLEXPWM3_SM0CVAL1CYC		(IMXRT_FLEXPWM3.SM[0].CVAL1CYC)
#define FLEXPWM3_SM0CVAL2		(IMXRT_FLEXPWM3.SM[0].CVAL2)
#define FLEXPWM3_SM0CVAL2CYC		(IMXRT_FLEXPWM3.SM[0].CVAL2CYC)
#define FLEXPWM3_SM0CVAL3		(IMXRT_FLEXPWM3.SM[0].CVAL3)
#define FLEXPWM3_SM0CVAL3CYC		(IMXRT_FLEXPWM3.SM[0].CVAL3CYC)
#define FLEXPWM3_SM0CVAL4		(IMXRT_FLEXPWM3.SM[0].CVAL4)
#define FLEXPWM3_SM0CVAL4CYC		(IMXRT_FLEXPWM3.SM[0].CVAL4CYC)
#define FLEXPWM3_SM0CVAL5		(IMXRT_FLEXPWM3.SM[0].CVAL5)
#define FLEXPWM3_SM0CVAL5CYC		(IMXRT_FLEXPWM3.SM[0].CVAL5CYC)
#define FLEXPWM3_SM1CNT			(IMXRT_FLEXPWM3.SM[1].CNT)
#define FLEXPWM3_SM1INIT		(IMXRT_FLEXPWM3.SM[1].INIT)
#define FLEXPWM3_SM1CTRL2		(IMXRT_FLEXPWM3.SM[1].CTRL2)
#define FLEXPWM3_SM1CTRL		(IMXRT_FLEXPWM3.SM[1].CTRL)
#define FLEXPWM3_SM1VAL0		(IMXRT_FLEXPWM3.SM[1].VAL0)
#define FLEXPWM3_SM1FRACVAL1		(IMXRT_FLEXPWM3.SM[1].FRACVAL1)
#define FLEXPWM3_SM1VAL1		(IMXRT_FLEXPWM3.SM[1].VAL1)
#define FLEXPWM3_SM1FRACVAL2		(IMXRT_FLEXPWM3.SM[1].FRACVAL2)
#define FLEXPWM3_SM1VAL2		(IMXRT_FLEXPWM3.SM[1].VAL2)
#define FLEXPWM3_SM1FRACVAL3		(IMXRT_FLEXPWM3.SM[1].FRACVAL3)
#define FLEXPWM3_SM1VAL3		(IMXRT_FLEXPWM3.SM[1].VAL3)
#define FLEXPWM3_SM1FRACVAL4		(IMXRT_FLEXPWM3.SM[1].FRACVAL4)
#define FLEXPWM3_SM1VAL4		(IMXRT_FLEXPWM3.SM[1].VAL4)
#define FLEXPWM3_SM1FRACVAL5		(IMXRT_FLEXPWM3.SM[1].FRACVAL5)
#define FLEXPWM3_SM1VAL5		(IMXRT_FLEXPWM3.SM[1].VAL5)
#define FLEXPWM3_SM1FRCTRL		(IMXRT_FLEXPWM3.SM[1].FRCTRL)
#define FLEXPWM3_SM1OCTRL		(IMXRT_FLEXPWM3.SM[1].OCTRL)
#define FLEXPWM3_SM1STS			(IMXRT_FLEXPWM3.SM[1].STS)
#define FLEXPWM3_SM1INTEN		(IMXRT_FLEXPWM3.SM[1].INTEN)
#define FLEXPWM3_SM1DMAEN		(IMXRT_FLEXPWM3.SM[1].DMAEN)
#define FLEXPWM3_SM1TCTRL		(IMXRT_FLEXPWM3.SM[1].TCTRL)
#define FLEXPWM3_SM1DISMAP0		(IMXRT_FLEXPWM3.SM[1].DISMAP0)
#define FLEXPWM3_SM1DISMAP1		(IMXRT_FLEXPWM3.SM[1].DISMAP1)
#define FLEXPWM3_SM1DTCNT0		(IMXRT_FLEXPWM3.SM[1].DTCNT0)
#define FLEXPWM3_SM1DTCNT1		(IMXRT_FLEXPWM3.SM[1].DTCNT1)
#define FLEXPWM3_SM1CAPTCTRLA		(IMXRT_FLEXPWM3.SM[1].CAPTCTRLA)
#define FLEXPWM3_SM1CAPTCOMPA		(IMXRT_FLEXPWM3.SM[1].CAPTCOMPA)
#define FLEXPWM3_SM1CAPTCTRLB		(IMXRT_FLEXPWM3.SM[1].CAPTCTRLB)
#define FLEXPWM3_SM1CAPTCOMPB		(IMXRT_FLEXPWM3.SM[1].CAPTCOMPB)
#define FLEXPWM3_SM1CAPTCTRLX		(IMXRT_FLEXPWM3.SM[1].CAPTCTRLX)
#define FLEXPWM3_SM1CAPTCOMPX		(IMXRT_FLEXPWM3.SM[1].CAPTCOMPX)
#define FLEXPWM3_SM1CVAL0		(IMXRT_FLEXPWM3.SM[1].CVAL0)
#define FLEXPWM3_SM1CVAL0CYC		(IMXRT_FLEXPWM3.SM[1].CVAL0CYC)
#define FLEXPWM3_SM1CVAL1		(IMXRT_FLEXPWM3.SM[1].CVAL1)
#define FLEXPWM3_SM1CVAL1CYC		(IMXRT_FLEXPWM3.SM[1].CVAL1CYC)
#define FLEXPWM3_SM1CVAL2		(IMXRT_FLEXPWM3.SM[1].CVAL2)
#define FLEXPWM3_SM1CVAL2CYC		(IMXRT_FLEXPWM3.SM[1].CVAL2CYC)
#define FLEXPWM3_SM1CVAL3		(IMXRT_FLEXPWM3.SM[1].CVAL3)
#define FLEXPWM3_SM1CVAL3CYC		(IMXRT_FLEXPWM3.SM[1].CVAL3CYC)
#define FLEXPWM3_SM1CVAL4		(IMXRT_FLEXPWM3.SM[1].CVAL4)
#define FLEXPWM3_SM1CVAL4CYC		(IMXRT_FLEXPWM3.SM[1].CVAL4CYC)
#define FLEXPWM3_SM1CVAL5		(IMXRT_FLEXPWM3.SM[1].CVAL5)
#define FLEXPWM3_SM1CVAL5CYC		(IMXRT_FLEXPWM3.SM[1].CVAL5CYC)
#define FLEXPWM3_SM2CNT			(IMXRT_FLEXPWM3.SM[2].CNT)
#define FLEXPWM3_SM2INIT		(IMXRT_FLEXPWM3.SM[2].INIT)
#define FLEXPWM3_SM2CTRL2		(IMXRT_FLEXPWM3.SM[2].CTRL2)
#define FLEXPWM3_SM2CTRL		(IMXRT_FLEXPWM3.SM[2].CTRL)
#define FLEXPWM3_SM2VAL0		(IMXRT_FLEXPWM3.SM[2].VAL0)
#define FLEXPWM3_SM2FRACVAL1		(IMXRT_FLEXPWM3.SM[2].FRACVAL1)
#define FLEXPWM3_SM2VAL1		(IMXRT_FLEXPWM3.SM[2].VAL1)
#define FLEXPWM3_SM2FRACVAL2		(IMXRT_FLEXPWM3.SM[2].FRACVAL2)
#define FLEXPWM3_SM2VAL2		(IMXRT_FLEXPWM3.SM[2].VAL2)
#define FLEXPWM3_SM2FRACVAL3		(IMXRT_FLEXPWM3.SM[2].FRACVAL3)
#define FLEXPWM3_SM2VAL3		(IMXRT_FLEXPWM3.SM[2].VAL3)
#define FLEXPWM3_SM2FRACVAL4		(IMXRT_FLEXPWM3.SM[2].FRACVAL4)
#define FLEXPWM3_SM2VAL4		(IMXRT_FLEXPWM3.SM[2].VAL4)
#define FLEXPWM3_SM2FRACVAL5		(IMXRT_FLEXPWM3.SM[2].FRACVAL5)
#define FLEXPWM3_SM2VAL5		(IMXRT_FLEXPWM3.SM[2].VAL5)
#define FLEXPWM3_SM2FRCTRL		(IMXRT_FLEXPWM3.SM[2].FRCTRL)
#define FLEXPWM3_SM2OCTRL		(IMXRT_FLEXPWM3.SM[2].OCTRL)
#define FLEXPWM3_SM2STS			(IMXRT_FLEXPWM3.SM[2].STS)
#define FLEXPWM3_SM2INTEN		(IMXRT_FLEXPWM3.SM[2].INTEN)
#define FLEXPWM3_SM2DMAEN		(IMXRT_FLEXPWM3.SM[2].DMAEN)
#define FLEXPWM3_SM2TCTRL		(IMXRT_FLEXPWM3.SM[2].TCTRL)
#define FLEXPWM3_SM2DISMAP0		(IMXRT_FLEXPWM3.SM[2].DISMAP0)
#define FLEXPWM3_SM2DISMAP1		(IMXRT_FLEXPWM3.SM[2].DISMAP1)
#define FLEXPWM3_SM2DTCNT0		(IMXRT_FLEXPWM3.SM[2].DTCNT0)
#define FLEXPWM3_SM2DTCNT1		(IMXRT_FLEXPWM3.SM[2].DTCNT1)
#define FLEXPWM3_SM2CAPTCTRLA		(IMXRT_FLEXPWM3.SM[2].CAPTCTRLA)
#define FLEXPWM3_SM2CAPTCOMPA		(IMXRT_FLEXPWM3.SM[2].CAPTCOMPA)
#define FLEXPWM3_SM2CAPTCTRLB		(IMXRT_FLEXPWM3.SM[2].CAPTCTRLB)
#define FLEXPWM3_SM2CAPTCOMPB		(IMXRT_FLEXPWM3.SM[2].CAPTCOMPB)
#define FLEXPWM3_SM2CAPTCTRLX		(IMXRT_FLEXPWM3.SM[2].CAPTCTRLX)
#define FLEXPWM3_SM2CAPTCOMPX		(IMXRT_FLEXPWM3.SM[2].CAPTCOMPX)
#define FLEXPWM3_SM2CVAL0		(IMXRT_FLEXPWM3.SM[2].CVAL0)
#define FLEXPWM3_SM2CVAL0CYC		(IMXRT_FLEXPWM3.SM[2].CVAL0CYC)
#define FLEXPWM3_SM2CVAL1		(IMXRT_FLEXPWM3.SM[2].CVAL1)
#define FLEXPWM3_SM2CVAL1CYC		(IMXRT_FLEXPWM3.SM[2].CVAL1CYC)
#define FLEXPWM3_SM2CVAL2		(IMXRT_FLEXPWM3.SM[2].CVAL2)
#define FLEXPWM3_SM2CVAL2CYC		(IMXRT_FLEXPWM3.SM[2].CVAL2CYC)
#define FLEXPWM3_SM2CVAL3		(IMXRT_FLEXPWM3.SM[2].CVAL3)
#define FLEXPWM3_SM2CVAL3CYC		(IMXRT_FLEXPWM3.SM[2].CVAL3CYC)
#define FLEXPWM3_SM2CVAL4		(IMXRT_FLEXPWM3.SM[2].CVAL4)
#define FLEXPWM3_SM2CVAL4CYC		(IMXRT_FLEXPWM3.SM[2].CVAL4CYC)
#define FLEXPWM3_SM2CVAL5		(IMXRT_FLEXPWM3.SM[2].CVAL5)
#define FLEXPWM3_SM2CVAL5CYC		(IMXRT_FLEXPWM3.SM[2].CVAL5CYC)
#define FLEXPWM3_SM3CNT			(IMXRT_FLEXPWM3.SM[3].CNT)
#define FLEXPWM3_SM3INIT		(IMXRT_FLEXPWM3.SM[3].INIT)
#define FLEXPWM3_SM3CTRL2		(IMXRT_FLEXPWM3.SM[3].CTRL2)
#define FLEXPWM3_SM3CTRL		(IMXRT_FLEXPWM3.SM[3].CTRL)
#define FLEXPWM3_SM3VAL0		(IMXRT_FLEXPWM3.SM[3].VAL0)
#define FLEXPWM3_SM3FRACVAL1		(IMXRT_FLEXPWM3.SM[3].FRACVAL1)
#define FLEXPWM3_SM3VAL1		(IMXRT_FLEXPWM3.SM[3].VAL1)
#define FLEXPWM3_SM3FRACVAL2		(IMXRT_FLEXPWM3.SM[3].FRACVAL2)
#define FLEXPWM3_SM3VAL2		(IMXRT_FLEXPWM3.SM[3].VAL2)
#define FLEXPWM3_SM3FRACVAL3		(IMXRT_FLEXPWM3.SM[3].FRACVAL3)
#define FLEXPWM3_SM3VAL3		(IMXRT_FLEXPWM3.SM[3].VAL3)
#define FLEXPWM3_SM3FRACVAL4		(IMXRT_FLEXPWM3.SM[3].FRACVAL4)
#define FLEXPWM3_SM3VAL4		(IMXRT_FLEXPWM3.SM[3].VAL4)
#define FLEXPWM3_SM3FRACVAL5		(IMXRT_FLEXPWM3.SM[3].FRACVAL5)
#define FLEXPWM3_SM3VAL5		(IMXRT_FLEXPWM3.SM[3].VAL5)
#define FLEXPWM3_SM3FRCTRL		(IMXRT_FLEXPWM3.SM[3].FRCTRL)
#define FLEXPWM3_SM3OCTRL		(IMXRT_FLEXPWM3.SM[3].OCTRL)
#define FLEXPWM3_SM3STS			(IMXRT_FLEXPWM3.SM[3].STS)
#define FLEXPWM3_SM3INTEN		(IMXRT_FLEXPWM3.SM[3].INTEN)
#define FLEXPWM3_SM3DMAEN		(IMXRT_FLEXPWM3.SM[3].DMAEN)
#define FLEXPWM3_SM3TCTRL		(IMXRT_FLEXPWM3.SM[3].TCTRL)
#define FLEXPWM3_SM3DISMAP0		(IMXRT_FLEXPWM3.SM[3].DISMAP0)
#define FLEXPWM3_SM3DISMAP1		(IMXRT_FLEXPWM3.SM[3].DISMAP1)
#define FLEXPWM3_SM3DTCNT0		(IMXRT_FLEXPWM3.SM[3].DTCNT0)
#define FLEXPWM3_SM3DTCNT1		(IMXRT_FLEXPWM3.SM[3].DTCNT1)
#define FLEXPWM3_SM3CAPTCTRLA		(IMXRT_FLEXPWM3.SM[3].CAPTCTRLA)
#define FLEXPWM3_SM3CAPTCOMPA		(IMXRT_FLEXPWM3.SM[3].CAPTCOMPA)
#define FLEXPWM3_SM3CAPTCTRLB		(IMXRT_FLEXPWM3.SM[3].CAPTCTRLB)
#define FLEXPWM3_SM3CAPTCOMPB		(IMXRT_FLEXPWM3.SM[3].CAPTCOMPB)
#define FLEXPWM3_SM3CAPTCTRLX		(IMXRT_FLEXPWM3.SM[3].CAPTCTRLX)
#define FLEXPWM3_SM3CAPTCOMPX		(IMXRT_FLEXPWM3.SM[3].CAPTCOMPX)
#define FLEXPWM3_SM3CVAL0		(IMXRT_FLEXPWM3.SM[3].CVAL0)
#define FLEXPWM3_SM3CVAL0CYC		(IMXRT_FLEXPWM3.SM[3].CVAL0CYC)
#define FLEXPWM3_SM3CVAL1		(IMXRT_FLEXPWM3.SM[3].CVAL1)
#define FLEXPWM3_SM3CVAL1CYC		(IMXRT_FLEXPWM3.SM[3].CVAL1CYC)
#define FLEXPWM3_SM3CVAL2		(IMXRT_FLEXPWM3.SM[3].CVAL2)
#define FLEXPWM3_SM3CVAL2CYC		(IMXRT_FLEXPWM3.SM[3].CVAL2CYC)
#define FLEXPWM3_SM3CVAL3		(IMXRT_FLEXPWM3.SM[3].CVAL3)
#define FLEXPWM3_SM3CVAL3CYC		(IMXRT_FLEXPWM3.SM[3].CVAL3CYC)
#define FLEXPWM3_SM3CVAL4		(IMXRT_FLEXPWM3.SM[3].CVAL4)
#define FLEXPWM3_SM3CVAL4CYC		(IMXRT_FLEXPWM3.SM[3].CVAL4CYC)
#define FLEXPWM3_SM3CVAL5		(IMXRT_FLEXPWM3.SM[3].CVAL5)
#define FLEXPWM3_SM3CVAL5CYC		(IMXRT_FLEXPWM3.SM[3].CVAL5CYC)
#define FLEXPWM3_OUTEN			(IMXRT_FLEXPWM3.OUTEN)
#define FLEXPWM3_MASK			(IMXRT_FLEXPWM3.MASK)
#define FLEXPWM3_SWCOUT			(IMXRT_FLEXPWM3.SWCOUT)
#define FLEXPWM3_DTSRCSEL		(IMXRT_FLEXPWM3.DTSRCSEL)
#define FLEXPWM3_MCTRL			(IMXRT_FLEXPWM3.MCTRL)
#define FLEXPWM3_MCTRL2			(IMXRT_FLEXPWM3.MCTRL2)
#define FLEXPWM3_FCTRL0			(IMXRT_FLEXPWM3.FCTRL0)
#define FLEXPWM3_FSTS0			(IMXRT_FLEXPWM3.FSTS0)
#define FLEXPWM3_FFILT0			(IMXRT_FLEXPWM3.FFILT0)
#define FLEXPWM3_FTST0			(IMXRT_FLEXPWM3.FTST0)
#define FLEXPWM3_FCTRL20		(IMXRT_FLEXPWM3.FCTRL20)
#define FLEXPWM4_SM0CNT			(IMXRT_FLEXPWM4.SM[0].CNT)
#define FLEXPWM4_SM0INIT		(IMXRT_FLEXPWM4.SM[0].INIT)
#define FLEXPWM4_SM0CTRL2		(IMXRT_FLEXPWM4.SM[0].CTRL2)
#define FLEXPWM4_SM0CTRL		(IMXRT_FLEXPWM4.SM[0].CTRL)
#define FLEXPWM4_SM0VAL0		(IMXRT_FLEXPWM4.SM[0].VAL0)
#define FLEXPWM4_SM0FRACVAL1		(IMXRT_FLEXPWM4.SM[0].FRACVAL1)
#define FLEXPWM4_SM0VAL1		(IMXRT_FLEXPWM4.SM[0].VAL1)
#define FLEXPWM4_SM0FRACVAL2		(IMXRT_FLEXPWM4.SM[0].FRACVAL2)
#define FLEXPWM4_SM0VAL2		(IMXRT_FLEXPWM4.SM[0].VAL2)
#define FLEXPWM4_SM0FRACVAL3		(IMXRT_FLEXPWM4.SM[0].FRACVAL3)
#define FLEXPWM4_SM0VAL3		(IMXRT_FLEXPWM4.SM[0].VAL3)
#define FLEXPWM4_SM0FRACVAL4		(IMXRT_FLEXPWM4.SM[0].FRACVAL4)
#define FLEXPWM4_SM0VAL4		(IMXRT_FLEXPWM4.SM[0].VAL4)
#define FLEXPWM4_SM0FRACVAL5		(IMXRT_FLEXPWM4.SM[0].FRACVAL5)
#define FLEXPWM4_SM0VAL5		(IMXRT_FLEXPWM4.SM[0].VAL5)
#define FLEXPWM4_SM0FRCTRL		(IMXRT_FLEXPWM4.SM[0].FRCTRL)
#define FLEXPWM4_SM0OCTRL		(IMXRT_FLEXPWM4.SM[0].OCTRL)
#define FLEXPWM4_SM0STS			(IMXRT_FLEXPWM4.SM[0].STS)
#define FLEXPWM4_SM0INTEN		(IMXRT_FLEXPWM4.SM[0].INTEN)
#define FLEXPWM4_SM0DMAEN		(IMXRT_FLEXPWM4.SM[0].DMAEN)
#define FLEXPWM4_SM0TCTRL		(IMXRT_FLEXPWM4.SM[0].TCTRL)
#define FLEXPWM4_SM0DISMAP0		(IMXRT_FLEXPWM4.SM[0].DISMAP0)
#define FLEXPWM4_SM0DISMAP1		(IMXRT_FLEXPWM4.SM[0].DISMAP1)
#define FLEXPWM4_SM0DTCNT0		(IMXRT_FLEXPWM4.SM[0].DTCNT0)
#define FLEXPWM4_SM0DTCNT1		(IMXRT_FLEXPWM4.SM[0].DTCNT1)
#define FLEXPWM4_SM0CAPTCTRLA		(IMXRT_FLEXPWM4.SM[0].CAPTCTRLA)
#define FLEXPWM4_SM0CAPTCOMPA		(IMXRT_FLEXPWM4.SM[0].CAPTCOMPA)
#define FLEXPWM4_SM0CAPTCTRLB		(IMXRT_FLEXPWM4.SM[0].CAPTCTRLB)
#define FLEXPWM4_SM0CAPTCOMPB		(IMXRT_FLEXPWM4.SM[0].CAPTCOMPB)
#define FLEXPWM4_SM0CAPTCTRLX		(IMXRT_FLEXPWM4.SM[0].CAPTCTRLX)
#define FLEXPWM4_SM0CAPTCOMPX		(IMXRT_FLEXPWM4.SM[0].CAPTCOMPX)
#define FLEXPWM4_SM0CVAL0		(IMXRT_FLEXPWM4.SM[0].CVAL0)
#define FLEXPWM4_SM0CVAL0CYC		(IMXRT_FLEXPWM4.SM[0].CVAL0CYC)
#define FLEXPWM4_SM0CVAL1		(IMXRT_FLEXPWM4.SM[0].CVAL1)
#define FLEXPWM4_SM0CVAL1CYC		(IMXRT_FLEXPWM4.SM[0].CVAL1CYC)
#define FLEXPWM4_SM0CVAL2		(IMXRT_FLEXPWM4.SM[0].CVAL2)
#define FLEXPWM4_SM0CVAL2CYC		(IMXRT_FLEXPWM4.SM[0].CVAL2CYC)
#define FLEXPWM4_SM0CVAL3		(IMXRT_FLEXPWM4.SM[0].CVAL3)
#define FLEXPWM4_SM0CVAL3CYC		(IMXRT_FLEXPWM4.SM[0].CVAL3CYC)
#define FLEXPWM4_SM0CVAL4		(IMXRT_FLEXPWM4.SM[0].CVAL4)
#define FLEXPWM4_SM0CVAL4CYC		(IMXRT_FLEXPWM4.SM[0].CVAL4CYC)
#define FLEXPWM4_SM0CVAL5		(IMXRT_FLEXPWM4.SM[0].CVAL5)
#define FLEXPWM4_SM0CVAL5CYC		(IMXRT_FLEXPWM4.SM[0].CVAL5CYC)
#define FLEXPWM4_SM1CNT			(IMXRT_FLEXPWM4.SM[1].CNT)
#define FLEXPWM4_SM1INIT		(IMXRT_FLEXPWM4.SM[1].INIT)
#define FLEXPWM4_SM1CTRL2		(IMXRT_FLEXPWM4.SM[1].CTRL2)
#define FLEXPWM4_SM1CTRL		(IMXRT_FLEXPWM4.SM[1].CTRL)
#define FLEXPWM4_SM1VAL0		(IMXRT_FLEXPWM4.SM[1].VAL0)
#define FLEXPWM4_SM1FRACVAL1		(IMXRT_FLEXPWM4.SM[1].FRACVAL1)
#define FLEXPWM4_SM1VAL1		(IMXRT_FLEXPWM4.SM[1].VAL1)
#define FLEXPWM4_SM1FRACVAL2		(IMXRT_FLEXPWM4.SM[1].FRACVAL2)
#define FLEXPWM4_SM1VAL2		(IMXRT_FLEXPWM4.SM[1].VAL2)
#define FLEXPWM4_SM1FRACVAL3		(IMXRT_FLEXPWM4.SM[1].FRACVAL3)
#define FLEXPWM4_SM1VAL3		(IMXRT_FLEXPWM4.SM[1].VAL3)
#define FLEXPWM4_SM1FRACVAL4		(IMXRT_FLEXPWM4.SM[1].FRACVAL4)
#define FLEXPWM4_SM1VAL4		(IMXRT_FLEXPWM4.SM[1].VAL4)
#define FLEXPWM4_SM1FRACVAL5		(IMXRT_FLEXPWM4.SM[1].FRACVAL5)
#define FLEXPWM4_SM1VAL5		(IMXRT_FLEXPWM4.SM[1].VAL5)
#define FLEXPWM4_SM1FRCTRL		(IMXRT_FLEXPWM4.SM[1].FRCTRL)
#define FLEXPWM4_SM1OCTRL		(IMXRT_FLEXPWM4.SM[1].OCTRL)
#define FLEXPWM4_SM1STS			(IMXRT_FLEXPWM4.SM[1].STS)
#define FLEXPWM4_SM1INTEN		(IMXRT_FLEXPWM4.SM[1].INTEN)
#define FLEXPWM4_SM1DMAEN		(IMXRT_FLEXPWM4.SM[1].DMAEN)
#define FLEXPWM4_SM1TCTRL		(IMXRT_FLEXPWM4.SM[1].TCTRL)
#define FLEXPWM4_SM1DISMAP0		(IMXRT_FLEXPWM4.SM[1].DISMAP0)
#define FLEXPWM4_SM1DISMAP1		(IMXRT_FLEXPWM4.SM[1].DISMAP1)
#define FLEXPWM4_SM1DTCNT0		(IMXRT_FLEXPWM4.SM[1].DTCNT0)
#define FLEXPWM4_SM1DTCNT1		(IMXRT_FLEXPWM4.SM[1].DTCNT1)
#define FLEXPWM4_SM1CAPTCTRLA		(IMXRT_FLEXPWM4.SM[1].CAPTCTRLA)
#define FLEXPWM4_SM1CAPTCOMPA		(IMXRT_FLEXPWM4.SM[1].CAPTCOMPA)
#define FLEXPWM4_SM1CAPTCTRLB		(IMXRT_FLEXPWM4.SM[1].CAPTCTRLB)
#define FLEXPWM4_SM1CAPTCOMPB		(IMXRT_FLEXPWM4.SM[1].CAPTCOMPB)
#define FLEXPWM4_SM1CAPTCTRLX		(IMXRT_FLEXPWM4.SM[1].CAPTCTRLX)
#define FLEXPWM4_SM1CAPTCOMPX		(IMXRT_FLEXPWM4.SM[1].CAPTCOMPX)
#define FLEXPWM4_SM1CVAL0		(IMXRT_FLEXPWM4.SM[1].CVAL0)
#define FLEXPWM4_SM1CVAL0CYC		(IMXRT_FLEXPWM4.SM[1].CVAL0CYC)
#define FLEXPWM4_SM1CVAL1		(IMXRT_FLEXPWM4.SM[1].CVAL1)
#define FLEXPWM4_SM1CVAL1CYC		(IMXRT_FLEXPWM4.SM[1].CVAL1CYC)
#define FLEXPWM4_SM1CVAL2		(IMXRT_FLEXPWM4.SM[1].CVAL2)
#define FLEXPWM4_SM1CVAL2CYC		(IMXRT_FLEXPWM4.SM[1].CVAL2CYC)
#define FLEXPWM4_SM1CVAL3		(IMXRT_FLEXPWM4.SM[1].CVAL3)
#define FLEXPWM4_SM1CVAL3CYC		(IMXRT_FLEXPWM4.SM[1].CVAL3CYC)
#define FLEXPWM4_SM1CVAL4		(IMXRT_FLEXPWM4.SM[1].CVAL4)
#define FLEXPWM4_SM1CVAL4CYC		(IMXRT_FLEXPWM4.SM[1].CVAL4CYC)
#define FLEXPWM4_SM1CVAL5		(IMXRT_FLEXPWM4.SM[1].CVAL5)
#define FLEXPWM4_SM1CVAL5CYC		(IMXRT_FLEXPWM4.SM[1].CVAL5CYC)
#define FLEXPWM4_SM2CNT			(IMXRT_FLEXPWM4.SM[2].CNT)
#define FLEXPWM4_SM2INIT		(IMXRT_FLEXPWM4.SM[2].INIT)
#define FLEXPWM4_SM2CTRL2		(IMXRT_FLEXPWM4.SM[2].CTRL2)
#define FLEXPWM4_SM2CTRL		(IMXRT_FLEXPWM4.SM[2].CTRL)
#define FLEXPWM4_SM2VAL0		(IMXRT_FLEXPWM4.SM[2].VAL0)
#define FLEXPWM4_SM2FRACVAL1		(IMXRT_FLEXPWM4.SM[2].FRACVAL1)
#define FLEXPWM4_SM2VAL1		(IMXRT_FLEXPWM4.SM[2].VAL1)
#define FLEXPWM4_SM2FRACVAL2		(IMXRT_FLEXPWM4.SM[2].FRACVAL2)
#define FLEXPWM4_SM2VAL2		(IMXRT_FLEXPWM4.SM[2].VAL2)
#define FLEXPWM4_SM2FRACVAL3		(IMXRT_FLEXPWM4.SM[2].FRACVAL3)
#define FLEXPWM4_SM2VAL3		(IMXRT_FLEXPWM4.SM[2].VAL3)
#define FLEXPWM4_SM2FRACVAL4		(IMXRT_FLEXPWM4.SM[2].FRACVAL4)
#define FLEXPWM4_SM2VAL4		(IMXRT_FLEXPWM4.SM[2].VAL4)
#define FLEXPWM4_SM2FRACVAL5		(IMXRT_FLEXPWM4.SM[2].FRACVAL5)
#define FLEXPWM4_SM2VAL5		(IMXRT_FLEXPWM4.SM[2].VAL5)
#define FLEXPWM4_SM2FRCTRL		(IMXRT_FLEXPWM4.SM[2].FRCTRL)
#define FLEXPWM4_SM2OCTRL		(IMXRT_FLEXPWM4.SM[2].OCTRL)
#define FLEXPWM4_SM2STS			(IMXRT_FLEXPWM4.SM[2].STS)
#define FLEXPWM4_SM2INTEN		(IMXRT_FLEXPWM4.SM[2].INTEN)
#define FLEXPWM4_SM2DMAEN		(IMXRT_FLEXPWM4.SM[2].DMAEN)
#define FLEXPWM4_SM2TCTRL		(IMXRT_FLEXPWM4.SM[2].TCTRL)
#define FLEXPWM4_SM2DISMAP0		(IMXRT_FLEXPWM4.SM[2].DISMAP0)
#define FLEXPWM4_SM2DISMAP1		(IMXRT_FLEXPWM4.SM[2].DISMAP1)
#define FLEXPWM4_SM2DTCNT0		(IMXRT_FLEXPWM4.SM[2].DTCNT0)
#define FLEXPWM4_SM2DTCNT1		(IMXRT_FLEXPWM4.SM[2].DTCNT1)
#define FLEXPWM4_SM2CAPTCTRLA		(IMXRT_FLEXPWM4.SM[2].CAPTCTRLA)
#define FLEXPWM4_SM2CAPTCOMPA		(IMXRT_FLEXPWM4.SM[2].CAPTCOMPA)
#define FLEXPWM4_SM2CAPTCTRLB		(IMXRT_FLEXPWM4.SM[2].CAPTCTRLB)
#define FLEXPWM4_SM2CAPTCOMPB		(IMXRT_FLEXPWM4.SM[2].CAPTCOMPB)
#define FLEXPWM4_SM2CAPTCTRLX		(IMXRT_FLEXPWM4.SM[2].CAPTCTRLX)
#define FLEXPWM4_SM2CAPTCOMPX		(IMXRT_FLEXPWM4.SM[2].CAPTCOMPX)
#define FLEXPWM4_SM2CVAL0		(IMXRT_FLEXPWM4.SM[2].CVAL0)
#define FLEXPWM4_SM2CVAL0CYC		(IMXRT_FLEXPWM4.SM[2].CVAL0CYC)
#define FLEXPWM4_SM2CVAL1		(IMXRT_FLEXPWM4.SM[2].CVAL1)
#define FLEXPWM4_SM2CVAL1CYC		(IMXRT_FLEXPWM4.SM[2].CVAL1CYC)
#define FLEXPWM4_SM2CVAL2		(IMXRT_FLEXPWM4.SM[2].CVAL2)
#define FLEXPWM4_SM2CVAL2CYC		(IMXRT_FLEXPWM4.SM[2].CVAL2CYC)
#define FLEXPWM4_SM2CVAL3		(IMXRT_FLEXPWM4.SM[2].CVAL3)
#define FLEXPWM4_SM2CVAL3CYC		(IMXRT_FLEXPWM4.SM[2].CVAL3CYC)
#define FLEXPWM4_SM2CVAL4		(IMXRT_FLEXPWM4.SM[2].CVAL4)
#define FLEXPWM4_SM2CVAL4CYC		(IMXRT_FLEXPWM4.SM[2].CVAL4CYC)
#define FLEXPWM4_SM2CVAL5		(IMXRT_FLEXPWM4.SM[2].CVAL5)
#define FLEXPWM4_SM2CVAL5CYC		(IMXRT_FLEXPWM4.SM[2].CVAL5CYC)
#define FLEXPWM4_SM3CNT			(IMXRT_FLEXPWM4.SM[3].CNT)
#define FLEXPWM4_SM3INIT		(IMXRT_FLEXPWM4.SM[3].INIT)
#define FLEXPWM4_SM3CTRL2		(IMXRT_FLEXPWM4.SM[3].CTRL2)
#define FLEXPWM4_SM3CTRL		(IMXRT_FLEXPWM4.SM[3].CTRL)
#define FLEXPWM4_SM3VAL0		(IMXRT_FLEXPWM4.SM[3].VAL0)
#define FLEXPWM4_SM3FRACVAL1		(IMXRT_FLEXPWM4.SM[3].FRACVAL1)
#define FLEXPWM4_SM3VAL1		(IMXRT_FLEXPWM4.SM[3].VAL1)
#define FLEXPWM4_SM3FRACVAL2		(IMXRT_FLEXPWM4.SM[3].FRACVAL2)
#define FLEXPWM4_SM3VAL2		(IMXRT_FLEXPWM4.SM[3].VAL2)
#define FLEXPWM4_SM3FRACVAL3		(IMXRT_FLEXPWM4.SM[3].FRACVAL3)
#define FLEXPWM4_SM3VAL3		(IMXRT_FLEXPWM4.SM[3].VAL3)
#define FLEXPWM4_SM3FRACVAL4		(IMXRT_FLEXPWM4.SM[3].FRACVAL4)
#define FLEXPWM4_SM3VAL4		(IMXRT_FLEXPWM4.SM[3].VAL4)
#define FLEXPWM4_SM3FRACVAL5		(IMXRT_FLEXPWM4.SM[3].FRACVAL5)
#define FLEXPWM4_SM3VAL5		(IMXRT_FLEXPWM4.SM[3].VAL5)
#define FLEXPWM4_SM3FRCTRL		(IMXRT_FLEXPWM4.SM[3].FRCTRL)
#define FLEXPWM4_SM3OCTRL		(IMXRT_FLEXPWM4.SM[3].OCTRL)
#define FLEXPWM4_SM3STS			(IMXRT_FLEXPWM4.SM[3].STS)
#define FLEXPWM4_SM3INTEN		(IMXRT_FLEXPWM4.SM[3].INTEN)
#define FLEXPWM4_SM3DMAEN		(IMXRT_FLEXPWM4.SM[3].DMAEN)
#define FLEXPWM4_SM3TCTRL		(IMXRT_FLEXPWM4.SM[3].TCTRL)
#define FLEXPWM4_SM3DISMAP0		(IMXRT_FLEXPWM4.SM[3].DISMAP0)
#define FLEXPWM4_SM3DISMAP1		(IMXRT_FLEXPWM4.SM[3].DISMAP1)
#define FLEXPWM4_SM3DTCNT0		(IMXRT_FLEXPWM4.SM[3].DTCNT0)
#define FLEXPWM4_SM3DTCNT1		(IMXRT_FLEXPWM4.SM[3].DTCNT1)
#define FLEXPWM4_SM3CAPTCTRLA		(IMXRT_FLEXPWM4.SM[3].CAPTCTRLA)
#define FLEXPWM4_SM3CAPTCOMPA		(IMXRT_FLEXPWM4.SM[3].CAPTCOMPA)
#define FLEXPWM4_SM3CAPTCTRLB		(IMXRT_FLEXPWM4.SM[3].CAPTCTRLB)
#define FLEXPWM4_SM3CAPTCOMPB		(IMXRT_FLEXPWM4.SM[3].CAPTCOMPB)
#define FLEXPWM4_SM3CAPTCTRLX		(IMXRT_FLEXPWM4.SM[3].CAPTCTRLX)
#define FLEXPWM4_SM3CAPTCOMPX		(IMXRT_FLEXPWM4.SM[3].CAPTCOMPX)
#define FLEXPWM4_SM3CVAL0		(IMXRT_FLEXPWM4.SM[3].CVAL0)
#define FLEXPWM4_SM3CVAL0CYC		(IMXRT_FLEXPWM4.SM[3].CVAL0CYC)
#define FLEXPWM4_SM3CVAL1		(IMXRT_FLEXPWM4.SM[3].CVAL1)
#define FLEXPWM4_SM3CVAL1CYC		(IMXRT_FLEXPWM4.SM[3].CVAL1CYC)
#define FLEXPWM4_SM3CVAL2		(IMXRT_FLEXPWM4.SM[3].CVAL2)
#define FLEXPWM4_SM3CVAL2CYC		(IMXRT_FLEXPWM4.SM[3].CVAL2CYC)
#define FLEXPWM4_SM3CVAL3		(IMXRT_FLEXPWM4.SM[3].CVAL3)
#define FLEXPWM4_SM3CVAL3CYC		(IMXRT_FLEXPWM4.SM[3].CVAL3CYC)
#define FLEXPWM4_SM3CVAL4		(IMXRT_FLEXPWM4.SM[3].CVAL4)
#define FLEXPWM4_SM3CVAL4CYC		(IMXRT_FLEXPWM4.SM[3].CVAL4CYC)
#define FLEXPWM4_SM3CVAL5		(IMXRT_FLEXPWM4.SM[3].CVAL5)
#define FLEXPWM4_SM3CVAL5CYC		(IMXRT_FLEXPWM4.SM[3].CVAL5CYC)
#define FLEXPWM4_OUTEN			(IMXRT_FLEXPWM4.OUTEN)
#define FLEXPWM4_MASK			(IMXRT_FLEXPWM4.MASK)
#define FLEXPWM4_SWCOUT			(IMXRT_FLEXPWM4.SWCOUT)
#define FLEXPWM4_DTSRCSEL		(IMXRT_FLEXPWM4.DTSRCSEL)
#define FLEXPWM4_MCTRL			(IMXRT_FLEXPWM4.MCTRL)
#define FLEXPWM4_MCTRL2			(IMXRT_FLEXPWM4.MCTRL2)
#define FLEXPWM4_FCTRL0			(IMXRT_FLEXPWM4.FCTRL0)
#define FLEXPWM4_FSTS0			(IMXRT_FLEXPWM4.FSTS0)
#define FLEXPWM4_FFILT0			(IMXRT_FLEXPWM4.FFILT0)
#define FLEXPWM4_FTST0			(IMXRT_FLEXPWM4.FTST0)
#define FLEXPWM4_FCTRL20		(IMXRT_FLEXPWM4.FCTRL20)
// page 3081
#define FLEXPWM_SMCTRL2_DBGEN			((uint16_t)(1<<15))
#define FLEXPWM_SMCTRL2_WAITEN			((uint16_t)(1<<14))
#define FLEXPWM_SMCTRL2_INDEP			((uint16_t)(1<<13))
#define FLEXPWM_SMCTRL2_PWM23_INIT		((uint16_t)(1<<12))
#define FLEXPWM_SMCTRL2_PWM45_INIT		((uint16_t)(1<<11))
#define FLEXPWM_SMCTRL2_PWMX_INIT		((uint16_t)(1<<10))
#define FLEXPWM_SMCTRL2_INIT_SEL(n)		((uint16_t)(((n) & 0x03) << 8))
#define FLEXPWM_SMCTRL2_FRCEN			((uint16_t)(1<<7))
#define FLEXPWM_SMCTRL2_FORCE			((uint16_t)(1<<6))
#define FLEXPWM_SMCTRL2_FORCE_SEL(n)		((uint16_t)(((n) & 0x07) << 3))
#define FLEXPWM_SMCTRL2_RELOAD_SEL		((uint16_t)(1<<2))
#define FLEXPWM_SMCTRL2_CLK_SEL(n)		((uint16_t)(((n) & 0x03) << 0))
#define FLEXPWM_SMCTRL_LDFQ(n)			((uint16_t)(((n) & 0x0F) << 12))
#define FLEXPWM_SMCTRL_HALF			((uint16_t)(1<<11))
#define FLEXPWM_SMCTRL_FULL			((uint16_t)(1<<10))
#define FLEXPWM_SMCTRL_DT(n)			((uint16_t)(((n) & 0x03) << 8))
#define FLEXPWM_SMCTRL_COMPMODE			((uint16_t)(1<<7))
#define FLEXPWM_SMCTRL_PRSC(n)			((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_SMCTRL_SPLIT			((uint16_t)(1<<3))
#define FLEXPWM_SMCTRL_LDMOD			((uint16_t)(1<<2))
#define FLEXPWM_SMCTRL_DBLX			((uint16_t)(1<<1))
#define FLEXPWM_SMCTRL_DBLEN			((uint16_t)(1<<0))
#define FLEXPWM_SMFRCTRL_TEST			((uint16_t)(1<<15))
#define FLEXPWM_SMFRCTRL_FRAC_PU		((uint16_t)(1<<8))
#define FLEXPWM_SMFRCTRL_FRAC45_EN		((uint16_t)(1<<4))
#define FLEXPWM_SMFRCTRL_FRAC23_EN		((uint16_t)(1<<2))
#define FLEXPWM_SMFRCTRL_FRAC1_EN		((uint16_t)(1<<1))
#define FLEXPWM_SMOCTRL_PWMA_IN			((uint16_t)(1<<15))
#define FLEXPWM_SMOCTRL_PWMB_IN			((uint16_t)(1<<14))
#define FLEXPWM_SMOCTRL_PWMX_IN			((uint16_t)(1<<13))
#define FLEXPWM_SMOCTRL_POLA			((uint16_t)(1<<10))
#define FLEXPWM_SMOCTRL_POLB			((uint16_t)(1<<9))
#define FLEXPWM_SMOCTRL_POLX			((uint16_t)(1<<8))
#define FLEXPWM_SMOCTRL_PWMAFS(n)		((uint16_t)(((n) & 0x03) << 4))
#define FLEXPWM_SMOCTRL_PWMBFS(n)		((uint16_t)(((n) & 0x03) << 2))
#define FLEXPWM_SMOCTRL_PWMXFS(n)		((uint16_t)(((n) & 0x03) << 0))
#define FLEXPWM_SMSTS_RUF			((uint16_t)(1<<14))
#define FLEXPWM_SMSTS_REF			((uint16_t)(1<<13))
#define FLEXPWM_SMSTS_RF			((uint16_t)(1<<12))
#define FLEXPWM_SMSTS_CFA1			((uint16_t)(1<<11))
#define FLEXPWM_SMSTS_CFA0			((uint16_t)(1<<10))
#define FLEXPWM_SMSTS_CFB1			((uint16_t)(1<<9))
#define FLEXPWM_SMSTS_CFB0			((uint16_t)(1<<8))
#define FLEXPWM_SMSTS_CFX1			((uint16_t)(1<<7))
#define FLEXPWM_SMSTS_CFX0			((uint16_t)(1<<6))
#define FLEXPWM_SMSTS_CMPF(n)			((uint16_t)(((n) & 0x3F) << 0))
#define FLEXPWM_SMINTEN_REIE			((uint16_t)(1<<13))
#define FLEXPWM_SMINTEN_RIE			((uint16_t)(1<<12))
#define FLEXPWM_SMINTEN_CA1IE			((uint16_t)(1<<11))
#define FLEXPWM_SMINTEN_CA0IE			((uint16_t)(1<<10))
#define FLEXPWM_SMINTEN_CB1IE			((uint16_t)(1<<9))
#define FLEXPWM_SMINTEN_CB0IE			((uint16_t)(1<<8))
#define FLEXPWM_SMINTEN_CX1IE			((uint16_t)(1<<7))
#define FLEXPWM_SMINTEN_CX0IE			((uint16_t)(1<<6))
#define FLEXPWM_SMINTEN_CMPIE(n)		((uint16_t)(((n) & 0x3F) << 0))
#define FLEXPWM_SMDMAEN_VALDE			((uint16_t)(1<<9))
#define FLEXPWM_SMDMAEN_FAND			((uint16_t)(1<<8))
#define FLEXPWM_SMDMAEN_CAPTDE(n)		((uint16_t)(((n) & 0x03) << 6))
#define FLEXPWM_SMDMAEN_CA1DE			((uint16_t)(1<<5))
#define FLEXPWM_SMDMAEN_CA0DE			((uint16_t)(1<<4))
#define FLEXPWM_SMDMAEN_CB1DE			((uint16_t)(1<<3))
#define FLEXPWM_SMDMAEN_CB0DE			((uint16_t)(1<<2))
#define FLEXPWM_SMDMAEN_CX1DE			((uint16_t)(1<<1))
#define FLEXPWM_SMDMAEN_CX0DE			((uint16_t)(1<<0))
#define FLEXPWM_SMTCTRL_PWAOT0			((uint16_t)(1<<15))
#define FLEXPWM_SMTCTRL_PWBOT1			((uint16_t)(1<<14))
#define FLEXPWM_SMTCTRL_TRGFRQ			((uint16_t)(1<<12))
#define FLEXPWM_SMTCTRL_OUT_TRIG_EN(n)		((uint16_t)(((n) & 0x3F) << 0))
#define FLEXPWM_SMDISMAP0_DIS0X(n)		((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_SMDISMAP0_DIS0B(n)		((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_SMDISMAP0_DIS0A(n)		((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_SMDISMAP1_DIS1X(n)		((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_SMDISMAP1_DIS1B(n)		((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_SMDISMAP1_DIS1A(n)		((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_SMCAPTCTRLA_CA1CNT(n)		((uint16_t)(((n) & 0x07) << 13))
#define FLEXPWM_SMCAPTCTRLA_CA0CNT(n)		((uint16_t)(((n) & 0x07) << 10))
#define FLEXPWM_SMCAPTCTRLA_CFAWM(n)		((uint16_t)(((n) & 0x03) << 8))
#define FLEXPWM_SMCAPTCTRLA_EDGCNTA_EN		((uint16_t)(1<<7))
#define FLEXPWM_SMCAPTCTRLA_INP_SELA		((uint16_t)(1<<6))
#define FLEXPWM_SMCAPTCTRLA_EDGA1(n)		((uint16_t)(((n) & 0x03) << 4))
#define FLEXPWM_SMCAPTCTRLA_EDGA0(n)		((uint16_t)(((n) & 0x03) << 2))
#define FLEXPWM_SMCAPTCTRLA_ONESHOTA		((uint16_t)(1<<1))
#define FLEXPWM_SMCAPTCTRLA_ARMA		((uint16_t)(1<<0))
#define FLEXPWM_SMCAPTCOMPA_EDGCNTA(n)		((uint16_t)(((n) & 0xFF) << 8))
#define FLEXPWM_SMCAPTCOMPA_EDGCMPA(n)		((uint16_t)(((n) & 0xFF) << 0))
#define FLEXPWM_SMCAPTCTRLB_CB1CNT(n)		((uint16_t)(((n) & 0x07) << 13))
#define FLEXPWM_SMCAPTCTRLB_CB0CNT(n)		((uint16_t)(((n) & 0x07) << 10))
#define FLEXPWM_SMCAPTCTRLB_CFBWM(n)		((uint16_t)(((n) & 0x03) << 8))
#define FLEXPWM_SMCAPTCTRLB_EDGCNTB_EN		((uint16_t)(1<<7))
#define FLEXPWM_SMCAPTCTRLB_INP_SELB		((uint16_t)(1<<6))
#define FLEXPWM_SMCAPTCTRLB_EDGB1(n)		((uint16_t)(((n) & 0x03) << 4))
#define FLEXPWM_SMCAPTCTRLB_EDGB0(n)		((uint16_t)(((n) & 0x03) << 2))
#define FLEXPWM_SMCAPTCTRLB_ONESHOTB		((uint16_t)(1<<1))
#define FLEXPWM_SMCAPTCTRLB_ARMB		((uint16_t)(1<<0))
#define FLEXPWM_SMCAPTCOMPB_EDGCNTB(n)		((uint16_t)(((n) & 0xFF) << 8))
#define FLEXPWM_SMCAPTCOMPB_EDGCMPB(n)		((uint16_t)(((n) & 0xFF) << 0))
#define FLEXPWM_SMCAPTCTRLX_CX1CNT(n)		((uint16_t)(((n) & 0x07) << 13))
#define FLEXPWM_SMCAPTCTRLX_CX0CNT(n)		((uint16_t)(((n) & 0x07) << 10))
#define FLEXPWM_SMCAPTCTRLX_CFXWM(n)		((uint16_t)(((n) & 0x03) << 8))
#define FLEXPWM_SMCAPTCTRLX_EDGCNTX_EN 		((uint16_t)(1<<7))
#define FLEXPWM_SMCAPTCTRLX_INP_SELX		((uint16_t)(1<<6))
#define FLEXPWM_SMCAPTCTRLX_EDGX1(n)		((uint16_t)(((n) & 0x03) << 4))
#define FLEXPWM_SMCAPTCTRLX_EDGX0(n)		((uint16_t)(((n) & 0x03) << 2))
#define FLEXPWM_SMCAPTCTRLX_ONESHOTX		((uint16_t)(1<<1))
#define FLEXPWM_SMCAPTCTRLX_ARMX		((uint16_t)(1<<0))
#define FLEXPWM_SMCAPTCOMPX_EDGCNTX(n)		((uint16_t)(((n) & 0xFF) << 8))
#define FLEXPWM_SMCAPTCOMPX_EDGCMPX(n)		((uint16_t)(((n) & 0xFF) << 0))
#define FLEXPWM_OUTEN_PWMA_EN(n)		((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_OUTEN_PWMB_EN(n)		((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_OUTEN_PWMX_EN(n)		((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_MASK_UPDATE_MASK(n)		((uint16_t)(((n) & 0x0F) << 12))
#define FLEXPWM_MASK_MASKA(n)			((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_MASK_MASKB(n)			((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_MASK_MASKX(n)			((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_SWCOUT_SM3OUT23			((uint16_t)(1<<7))
#define FLEXPWM_SWCOUT_SM3OUT45			((uint16_t)(1<<6))
#define FLEXPWM_SWCOUT_SM2OUT23			((uint16_t)(1<<5))
#define FLEXPWM_SWCOUT_SM2OUT45			((uint16_t)(1<<4))
#define FLEXPWM_SWCOUT_SM1OUT23			((uint16_t)(1<<3))
#define FLEXPWM_SWCOUT_SM1OUT45			((uint16_t)(1<<2))
#define FLEXPWM_SWCOUT_SM0OUT23			((uint16_t)(1<<1))
#define FLEXPWM_SWCOUT_SM0OUT45			((uint16_t)(1<<0))
#define FLEXPWM_DTSRCSEL_SM3SEL23(n)		((uint16_t)(((n) & 0x03) << 14))
#define FLEXPWM_DTSRCSEL_SM3SEL45(n)		((uint16_t)(((n) & 0x03) << 12))
#define FLEXPWM_DTSRCSEL_SM2SEL23(n)		((uint16_t)(((n) & 0x03) << 10))
#define FLEXPWM_DTSRCSEL_SM2SEL45(n)		((uint16_t)(((n) & 0x03) << 8))
#define FLEXPWM_DTSRCSEL_SM1SEL23(n)		((uint16_t)(((n) & 0x03) << 6))
#define FLEXPWM_DTSRCSEL_SM1SEL45(n)		((uint16_t)(((n) & 0x03) << 4))
#define FLEXPWM_DTSRCSEL_SM0SEL23(n)		((uint16_t)(((n) & 0x03) << 2))
#define FLEXPWM_DTSRCSEL_SM0SEL45(n)		((uint16_t)(((n) & 0x03) << 0))
#define FLEXPWM_MCTRL_IPOL(n)			((uint16_t)(((n) & 0x0F) << 12))
#define FLEXPWM_MCTRL_RUN(n)			((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_MCTRL_CLDOK(n)			((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_MCTRL_LDOK(n)			((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_MCTRL2_MONPLL(n)		((uint16_t)(((n) & 0x03) << 0))
#define FLEXPWM_FCTRL0_FLVL(n)			((uint16_t)(((n) & 0x0F) << 12))
#define FLEXPWM_FCTRL0_FAUTO(n)			((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_FCTRL0_FSAFE(n)			((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_FCTRL0_FIE(n)			((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_FSTS0_FHALF(n)			((uint16_t)(((n) & 0x0F) << 12))
#define FLEXPWM_FSTS0_FFPIN(n)			((uint16_t)(((n) & 0x0F) << 8))
#define FLEXPWM_FSTS0_FFULL(n)			((uint16_t)(((n) & 0x0F) << 4))
#define FLEXPWM_FSTS0_FFLAG(n)			((uint16_t)(((n) & 0x0F) << 0))
#define FLEXPWM_FFILT0_GSTR			((uint16_t)(1<<15))
#define FLEXPWM_FFILT0_FILT_CNT(n)		((uint16_t)(((n) & 0x07) << 8))
#define FLEXPWM_FFILT0_FILT_PER(n)		((uint16_t)(((n) & 0xFF) << 0))
#define FLEXPWM_FTST0_FTEST			((uint16_t)(1<<0))
#define FLEXPWM_FCTRL20_NOCOMB(n)		((uint16_t)(((n) & 0x0F) << 0))

// 31.4.1.1: page 1766
#define IMXRT_FLEXRAM		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXRAM_ADDRESS)
#define FLEXRAM_TCM_CTRL		(IMXRT_FLEXRAM.offset000)
#define FLEXRAM_INT_STATUS		(IMXRT_FLEXRAM.offset010)
#define FLEXRAM_INT_STAT_EN		(IMXRT_FLEXRAM.offset014)
#define FLEXRAM_INT_SIG_EN		(IMXRT_FLEXRAM.offset018)
#define FLEXRAM_TCM_CTRL_FORCE_CLK_ON		((uint32_t)(1<<2))
#define FLEXRAM_TCM_CTRL_TCM_RWAIT_EN		((uint32_t)(1<<1))
#define FLEXRAM_TCM_CTRL_TCM_WWAIT_EN		((uint32_t)(1<<0))
#define FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS	((uint32_t)(1<<5))
#define FLEXRAM_INT_STATUS_DTCM_ERR_STATUS	((uint32_t)(1<<4))
#define FLEXRAM_INT_STATUS_ITCM_ERR_STATUS	((uint32_t)(1<<3))
#define FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN	((uint32_t)(1<<5))
#define FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN	((uint32_t)(1<<4))
#define FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN	((uint32_t)(1<<3))
#define FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN	((uint32_t)(1<<5))
#define FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN	((uint32_t)(1<<4))
#define FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN	((uint32_t)(1<<3))

// 27.7.2.1: page 1695
#define IMXRT_FLEXSPI		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXSPI_ADDRESS)
#define FLEXSPI_MCR0			(IMXRT_FLEXSPI.offset000)
#define FLEXSPI_MCR0_AHBGRANTWAIT(n)		((uint32_t)(((n) & 0xFF) << 24))
#define FLEXSPI_MCR0_AHBGRANTWAIT_MASK		((uint32_t)(0xFF << 24))
#define FLEXSPI_MCR0_IPGRANTWAIT(n)		((uint32_t)(((n) & 0xFF) << 16))
#define FLEXSPI_MCR0_IPGRANTWAIT_MASK		((uint32_t)(0xFF << 16))
#define FLEXSPI_MCR0_SCKFREERUNEN		((uint32_t)(1<<14))
#define FLEXSPI_MCR0_COMBINATIONEN		((uint32_t)(1<<13))
#define FLEXSPI_MCR0_DOZEEN			((uint32_t)(1<<12))
#define FLEXSPI_MCR0_HSEN			((uint32_t)(1<<11))
#define FLEXSPI_MCR0_ATDFEN			((uint32_t)(1<<7))
#define FLEXSPI_MCR0_ARDFEN			((uint32_t)(1<<6))
#define FLEXSPI_MCR0_RXCLKSRC(n)		((uint32_t)(((n) & 0x03) << 4))
#define FLEXSPI_MCR0_RXCLKSRC_MASK		((uint32_t)(0x03 << 4))
#define FLEXSPI_MCR0_MDIS			((uint32_t)(1<<1))
#define FLEXSPI_MCR0_SWRESET			((uint32_t)(1<<0))
#define FLEXSPI_MCR1			(IMXRT_FLEXSPI.offset004)
#define FLEXSPI_MCR1_SEQWAIT(n)			((uint32_t)(((n) & 0xFFFF) << 16))
#define FLEXSPI_MCR1_AHBBUSWAIT(n)		((uint32_t)(((n) & 0xFFFF) << 0))
#define FLEXSPI_MCR2			(IMXRT_FLEXSPI.offset008)
#define FLEXSPI_MCR2_RESUMEWAIT(n)		((uint32_t)(((n) & 0xFF) << 24))
#define FLEXSPI_MCR2_RESUMEWAIT_MASK		((uint32_t)(0xFF << 24))
#define FLEXSPI_MCR2_SCKBDIFFOPT		((uint32_t)(1<<19))
#define FLEXSPI_MCR2_SAMEDEVICEEN		((uint32_t)(1<<15))
#define FLEXSPI_MCR2_CLRLEARNPHASE		((uint32_t)(1<<14))
#define FLEXSPI_MCR2_CLRAHBBUFOPT		((uint32_t)(1<<11))
#define FLEXSPI_AHBCR			(IMXRT_FLEXSPI.offset00C)
#define FLEXSPI_AHBCR_READADDROPT		((uint32_t)(1<<6))
#define FLEXSPI_AHBCR_PREFETCHEN		((uint32_t)(1<<5))
#define FLEXSPI_AHBCR_BUFFERABLEEN		((uint32_t)(1<<4))
#define FLEXSPI_AHBCR_CACHABLEEN		((uint32_t)(1<<3))
#define FLEXSPI_AHBCR_APAREN			((uint32_t)(1<<0))
#define FLEXSPI_INTEN			(IMXRT_FLEXSPI.offset010)
#define FLEXSPI_INTEN_SEQTIMEOUTEN		((uint32_t)(1<<11))
#define FLEXSPI_INTEN_AHBBUSTIMEOUTEN		((uint32_t)(1<<10))
#define FLEXSPI_INTEN_SCKSTOPBYWREN		((uint32_t)(1<<9))
#define FLEXSPI_INTEN_SCKSTOPBYRDEN		((uint32_t)(1<<8))
#define FLEXSPI_INTEN_IPTXWEEN			((uint32_t)(1<<6))
#define FLEXSPI_INTEN_IPRXWAEN			((uint32_t)(1<<5))
#define FLEXSPI_INTEN_AHBCMDERREN		((uint32_t)(1<<4))
#define FLEXSPI_INTEN_IPCMDERREN		((uint32_t)(1<<3))
#define FLEXSPI_INTEN_AHBCMDGEEN		((uint32_t)(1<<2))
#define FLEXSPI_INTEN_IPCMDGEEN			((uint32_t)(1<<1))
#define FLEXSPI_INTEN_IPCMDDONEEN		((uint32_t)(1<<0))
#define FLEXSPI_INTR			(IMXRT_FLEXSPI.offset014)
#define FLEXSPI_INTR_SEQTIMEOUT			((uint32_t)(1<<11))
#define FLEXSPI_INTR_AHBBUSTIMEOUT		((uint32_t)(1<<10))
#define FLEXSPI_INTR_SCKSTOPBYWR		((uint32_t)(1<<9))
#define FLEXSPI_INTR_SCKSTOPBYRD		((uint32_t)(1<<8))
#define FLEXSPI_INTR_IPTXWE			((uint32_t)(1<<6))
#define FLEXSPI_INTR_IPRXWA			((uint32_t)(1<<5))
#define FLEXSPI_INTR_AHBCMDERR			((uint32_t)(1<<4))
#define FLEXSPI_INTR_IPCMDERR			((uint32_t)(1<<3))
#define FLEXSPI_INTR_AHBCMDGE			((uint32_t)(1<<2))
#define FLEXSPI_INTR_IPCMDGE			((uint32_t)(1<<1))
#define FLEXSPI_INTR_IPCMDDONE			((uint32_t)(1<<0))
#define FLEXSPI_LUTKEY			(IMXRT_FLEXSPI.offset018)
#define FLEXSPI_LUTKEY_VALUE			((uint32_t)0x5AF05AF0)
#define FLEXSPI_LUTCR			(IMXRT_FLEXSPI.offset01C)
#define FLEXSPI_LUTCR_UNLOCK			((uint32_t)(1<<1))
#define FLEXSPI_LUTCR_LOCK			((uint32_t)(1<<0))
#define FLEXSPI_AHBRXBUF0CR0		(IMXRT_FLEXSPI.offset020)
#define FLEXSPI_AHBRXBUF1CR0		(IMXRT_FLEXSPI.offset024)
#define FLEXSPI_AHBRXBUF2CR0		(IMXRT_FLEXSPI.offset028)
#define FLEXSPI_AHBRXBUF3CR0		(IMXRT_FLEXSPI.offset02C)
#define FLEXSPI_AHBRXBUFCR0_PREFETCHEN		((uint32_t)(1<<31))
#define FLEXSPI_AHBRXBUFCR0_PRIORITY(n)		((uint32_t)(((n) & 0x03) << 24))
#define FLEXSPI_AHBRXBUFCR0_PRIORITY_MASK	((uint32_t)((0x03) << 24))
#define FLEXSPI_AHBRXBUFCR0_MSTRID(n)		((uint32_t)(((n) & 0x0F) << 16))
#define FLEXSPI_AHBRXBUFCR0_MSTRID_MASK		((uint32_t)((0x0F) << 16))
#define FLEXSPI_AHBRXBUFCR0_BUFSZ(n)		((uint32_t)(((n) & 0xFF) << 0))
#define FLEXSPI_AHBRXBUFCR0_BUFSZ_MASK		((uint32_t)((0xFF) << 0))
#define FLEXSPI_FLSHA1CR0		(IMXRT_FLEXSPI.offset060)
#define FLEXSPI_FLSHA2CR0		(IMXRT_FLEXSPI.offset064)
#define FLEXSPI_FLSHB1CR0		(IMXRT_FLEXSPI.offset068)
#define FLEXSPI_FLSHB2CR0		(IMXRT_FLEXSPI.offset06C)
#define FLEXSPI_FLSHCR0_FLSHSZ(n)		((uint32_t)(((n) & 0x7FFFFF) << 0))
#define FLEXSPI_FLSHCR0_FLSHSZ_MASK		((uint32_t)((0x7FFFFF) << 0))
#define FLEXSPI_FLSHA1CR1		(IMXRT_FLEXSPI.offset070)
#define FLEXSPI_FLSHA2CR1		(IMXRT_FLEXSPI.offset074)
#define FLEXSPI_FLSHB1CR1		(IMXRT_FLEXSPI.offset078)
#define FLEXSPI_FLSHB2CR1		(IMXRT_FLEXSPI.offset07C)
#define FLEXSPI_FLSHCR1_CSINTERVAL(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define FLEXSPI_FLSHCR1_CSINTERVAL_MASK		((uint32_t)((0xFFFF) << 16))
#define FLEXSPI_FLSHCR1_CSINTERVALUNIT		((uint32_t)(1<<15))
#define FLEXSPI_FLSHCR1_CAS(n)			((uint32_t)(((n) & 0x0F) << 11))
#define FLEXSPI_FLSHCR1_WA			((uint32_t)(1<<10))
#define FLEXSPI_FLSHCR1_TCSH(n)			((uint32_t)(((n) & 0x1F) << 5))
#define FLEXSPI_FLSHCR1_TCSH_MASK		((uint32_t)((0x1F) << 5))
#define FLEXSPI_FLSHCR1_TCSS(n)			((uint32_t)(((n) & 0x1F) << 0))
#define FLEXSPI_FLSHCR1_TCSS_MASK		((uint32_t)((0x1F) << 0))
#define FLEXSPI_FLSHA1CR2		(IMXRT_FLEXSPI.offset080)
#define FLEXSPI_FLSHA2CR2		(IMXRT_FLEXSPI.offset084)
#define FLEXSPI_FLSHB1CR2		(IMXRT_FLEXSPI.offset088)
#define FLEXSPI_FLSHB2CR2		(IMXRT_FLEXSPI.offset08C)
#define FLEXSPI_FLSHCR2_CLRINSTRPTR		((uint32_t)(1<<31))
#define FLEXSPI_FLSHCR2_AWRWAITUNIT(n)		((uint32_t)(((n) & 0x07) << 28))
#define FLEXSPI_FLSHCR2_AWRWAIT(n)		((uint32_t)(((n) & 0xFFF) << 16))
#define FLEXSPI_FLSHCR2_AWRSEQNUM(n)		((uint32_t)(((n) & 0x07) << 13))
#define FLEXSPI_FLSHCR2_AWRSEQID(n)		((uint32_t)(((n) & 0x0F) << 8))
#define FLEXSPI_FLSHCR2_ARDSEQNUM(n)		((uint32_t)(((n) & 0x07) << 5))
#define FLEXSPI_FLSHCR2_ARDSEQID(n)		((uint32_t)(((n) & 0x0F) << 0))
#define FLEXSPI_FLSHCR4			(IMXRT_FLEXSPI.offset094)
#define FLEXSPI_FLSHCR4_WMENB			((uint32_t)(1<<3))
#define FLEXSPI_FLSHCR4_WMENA			((uint32_t)(1<<2))
#define FLEXSPI_FLSHCR4_WMOPT1			((uint32_t)(1<<0))
#define FLEXSPI_IPCR0			(IMXRT_FLEXSPI.offset0A0)
#define FLEXSPI_IPCR0_SFAR(n)			((uint32_t)(n))
#define FLEXSPI_IPCR1			(IMXRT_FLEXSPI.offset0A4)
#define FLEXSPI_IPCR1_IPAREN			((uint32_t)(1<<31))
#define FLEXSPI_IPCR1_ISEQNUM(n)		((uint32_t)(((n) & 0x07) << 24))
#define FLEXSPI_IPCR1_ISEQID(n)			((uint32_t)(((n) & 0x0F) << 16))
#define FLEXSPI_IPCR1_IDATSZ(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define FLEXSPI_IPCMD			(IMXRT_FLEXSPI.offset0B0)
#define FLEXSPI_IPCMD_TRG			((uint32_t)(1<<0))
#define FLEXSPI_IPRXFCR			(IMXRT_FLEXSPI.offset0B8)
#define FLEXSPI_IPRXFCR_RXWMRK(n)		((uint32_t)(((n) & 0x0F) << 2))
#define FLEXSPI_IPRXFCR_RXDMAEN			((uint32_t)(1<<1))
#define FLEXSPI_IPRXFCR_CLRIPRXF		((uint32_t)(1<<0))
#define FLEXSPI_IPTXFCR			(IMXRT_FLEXSPI.offset0BC)
#define FLEXSPI_IPTXFCR_TXWMRK(n)		((uint32_t)(((n) & 0x0F) << 2))
#define FLEXSPI_IPTXFCR_TXDMAEN			((uint32_t)(1<<1))
#define FLEXSPI_IPTXFCR_CLRIPTXF		((uint32_t)(1<<0))
#define FLEXSPI_DLLACR			(IMXRT_FLEXSPI.offset0C0)
#define FLEXSPI_DLLBCR			(IMXRT_FLEXSPI.offset0C4)
#define FLEXSPI_DLLCR_OVRDVAL(n)		((uint32_t)(((n) & 0x3F) << 9))
#define FLEXSPI_DLLCR_OVRDEN			((uint32_t)(1<<8))
#define FLEXSPI_DLLCR_SLVDLYTARGET(n)		((uint32_t)(((n) & 0x0F) << 3))
#define FLEXSPI_DLLCR_DLLRESET			((uint32_t)(1<<1))
#define FLEXSPI_DLLCR_DLLEN			((uint32_t)(1<<0))
#define FLEXSPI_STS0			(IMXRT_FLEXSPI.offset0E0)
#define FLEXSPI_STS0_ARBCMDSRC(n)		((uint32_t)(((n) & 0x03) << 2))
#define FLEXSPI_STS0_ARBIDLE			((uint32_t)(1<<1))
#define FLEXSPI_STS0_SEQIDLE			((uint32_t)(1<<0))
#define FLEXSPI_STS1			(IMXRT_FLEXSPI.offset0E4)
#define FLEXSPI_STS1_IPCMDERRCODE(n)		((uint32_t)(((n) & 0x0F) << 24))
#define FLEXSPI_STS1_IPCMDERRID(n)		((uint32_t)(((n) & 0x0F) << 16))
#define FLEXSPI_STS1_AHBCMDERRCODE(n)		((uint32_t)(((n) & 0x0F) << 8))
#define FLEXSPI_STS1_AHBCMDERRID(n)		((uint32_t)(((n) & 0x0F) << 0))
#define FLEXSPI_STS2			(IMXRT_FLEXSPI.offset0E8)
#define FLEXSPI_STS2_BREFSEL(n)			((uint32_t)(((n) & 0x3F) << 24))
#define FLEXSPI_STS2_BSLVSEL(n)			((uint32_t)(((n) & 0x3F) << 18))
#define FLEXSPI_STS2_BREFLOCK			((uint32_t)(1<<17))
#define FLEXSPI_STS2_BSLVLOCK			((uint32_t)(1<<16))
#define FLEXSPI_STS2_AREFSEL(n)			((uint32_t)(((n) & 0x3F) << 8))
#define FLEXSPI_STS2_ASLVSEL(n)			((uint32_t)(((n) & 0x3F) << 2))
#define FLEXSPI_STS2_AREFLOCK			((uint32_t)(1<<1))
#define FLEXSPI_STS2_ASLVLOCK			((uint32_t)(1<<0))
#define FLEXSPI_AHBSPNDSTS		(IMXRT_FLEXSPI.offset0EC)
#define FLEXSPI_AHBSPNDSTS_DATLFT(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define FLEXSPI_AHBSPNDSTS_BUFID(n)		((uint32_t)(((n) & 0x7) << 1))
#define FLEXSPI_AHBSPNDSTS_ACTIVE		((uint32_t)(1<<0))
#define FLEXSPI_IPRXFSTS		(IMXRT_FLEXSPI.offset0F0)
#define FLEXSPI_IPRXFSTS_RDCNTR(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define FLEXSPI_IPRXFSTS_FILL(n)		((uint32_t)(((n) & 0xFF) << 0))
#define FLEXSPI_IPTXFSTS		(IMXRT_FLEXSPI.offset0F4)
#define FLEXSPI_IPTXFSTS_WRCNTR(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define FLEXSPI_IPTXFSTS_FILL(n)		((uint32_t)(((n) & 0xFF) << 0))
#define FLEXSPI_RFDR0			(IMXRT_FLEXSPI.offset100)
#define FLEXSPI_RFDR1			(IMXRT_FLEXSPI.offset104)
#define FLEXSPI_RFDR2			(IMXRT_FLEXSPI.offset108)
#define FLEXSPI_RFDR3			(IMXRT_FLEXSPI.offset10C)
#define FLEXSPI_RFDR4			(IMXRT_FLEXSPI.offset110)
#define FLEXSPI_RFDR5			(IMXRT_FLEXSPI.offset114)
#define FLEXSPI_RFDR6			(IMXRT_FLEXSPI.offset118)
#define FLEXSPI_RFDR7			(IMXRT_FLEXSPI.offset11C)
#define FLEXSPI_RFDR8			(IMXRT_FLEXSPI.offset120)
#define FLEXSPI_RFDR9			(IMXRT_FLEXSPI.offset124)
#define FLEXSPI_RFDR10			(IMXRT_FLEXSPI.offset128)
#define FLEXSPI_RFDR11			(IMXRT_FLEXSPI.offset12C)
#define FLEXSPI_RFDR12			(IMXRT_FLEXSPI.offset130)
#define FLEXSPI_RFDR13			(IMXRT_FLEXSPI.offset134)
#define FLEXSPI_RFDR14			(IMXRT_FLEXSPI.offset138)
#define FLEXSPI_RFDR15			(IMXRT_FLEXSPI.offset13C)
#define FLEXSPI_RFDR16			(IMXRT_FLEXSPI.offset140)
#define FLEXSPI_RFDR17			(IMXRT_FLEXSPI.offset144)
#define FLEXSPI_RFDR18			(IMXRT_FLEXSPI.offset148)
#define FLEXSPI_RFDR19			(IMXRT_FLEXSPI.offset14C)
#define FLEXSPI_RFDR20			(IMXRT_FLEXSPI.offset150)
#define FLEXSPI_RFDR21			(IMXRT_FLEXSPI.offset154)
#define FLEXSPI_RFDR22			(IMXRT_FLEXSPI.offset158)
#define FLEXSPI_RFDR23			(IMXRT_FLEXSPI.offset15C)
#define FLEXSPI_RFDR24			(IMXRT_FLEXSPI.offset160)
#define FLEXSPI_RFDR25			(IMXRT_FLEXSPI.offset164)
#define FLEXSPI_RFDR26			(IMXRT_FLEXSPI.offset168)
#define FLEXSPI_RFDR27			(IMXRT_FLEXSPI.offset16C)
#define FLEXSPI_RFDR28			(IMXRT_FLEXSPI.offset170)
#define FLEXSPI_RFDR29			(IMXRT_FLEXSPI.offset174)
#define FLEXSPI_RFDR30			(IMXRT_FLEXSPI.offset178)
#define FLEXSPI_RFDR31			(IMXRT_FLEXSPI.offset17C)
#define FLEXSPI_TFDR0			(IMXRT_FLEXSPI.offset180)
#define FLEXSPI_TFDR1			(IMXRT_FLEXSPI.offset184)
#define FLEXSPI_TFDR2			(IMXRT_FLEXSPI.offset188)
#define FLEXSPI_TFDR3			(IMXRT_FLEXSPI.offset18C)
#define FLEXSPI_TFDR4			(IMXRT_FLEXSPI.offset190)
#define FLEXSPI_TFDR5			(IMXRT_FLEXSPI.offset194)
#define FLEXSPI_TFDR6			(IMXRT_FLEXSPI.offset198)
#define FLEXSPI_TFDR7			(IMXRT_FLEXSPI.offset19C)
#define FLEXSPI_TFDR8			(IMXRT_FLEXSPI.offset1A0)
#define FLEXSPI_TFDR9			(IMXRT_FLEXSPI.offset1A4)
#define FLEXSPI_TFDR10			(IMXRT_FLEXSPI.offset1A8)
#define FLEXSPI_TFDR11			(IMXRT_FLEXSPI.offset1AC)
#define FLEXSPI_TFDR12			(IMXRT_FLEXSPI.offset1B0)
#define FLEXSPI_TFDR13			(IMXRT_FLEXSPI.offset1B4)
#define FLEXSPI_TFDR14			(IMXRT_FLEXSPI.offset1B8)
#define FLEXSPI_TFDR15			(IMXRT_FLEXSPI.offset1BC)
#define FLEXSPI_TFDR16			(IMXRT_FLEXSPI.offset1C0)
#define FLEXSPI_TFDR17			(IMXRT_FLEXSPI.offset1C4)
#define FLEXSPI_TFDR18			(IMXRT_FLEXSPI.offset1C8)
#define FLEXSPI_TFDR19			(IMXRT_FLEXSPI.offset1CC)
#define FLEXSPI_TFDR20			(IMXRT_FLEXSPI.offset1D0)
#define FLEXSPI_TFDR21			(IMXRT_FLEXSPI.offset1D4)
#define FLEXSPI_TFDR22			(IMXRT_FLEXSPI.offset1D8)
#define FLEXSPI_TFDR23			(IMXRT_FLEXSPI.offset1DC)
#define FLEXSPI_TFDR24			(IMXRT_FLEXSPI.offset1E0)
#define FLEXSPI_TFDR25			(IMXRT_FLEXSPI.offset1E4)
#define FLEXSPI_TFDR26			(IMXRT_FLEXSPI.offset1E8)
#define FLEXSPI_TFDR27			(IMXRT_FLEXSPI.offset1EC)
#define FLEXSPI_TFDR28			(IMXRT_FLEXSPI.offset1F0)
#define FLEXSPI_TFDR29			(IMXRT_FLEXSPI.offset1F4)
#define FLEXSPI_TFDR30			(IMXRT_FLEXSPI.offset1F8)
#define FLEXSPI_TFDR31			(IMXRT_FLEXSPI.offset1FC)
#define FLEXSPI_LUT0			(IMXRT_FLEXSPI.offset200)
#define FLEXSPI_LUT1			(IMXRT_FLEXSPI.offset204)
#define FLEXSPI_LUT2			(IMXRT_FLEXSPI.offset208)
#define FLEXSPI_LUT3			(IMXRT_FLEXSPI.offset20C)
#define FLEXSPI_LUT4			(IMXRT_FLEXSPI.offset210)
#define FLEXSPI_LUT5			(IMXRT_FLEXSPI.offset214)
#define FLEXSPI_LUT6			(IMXRT_FLEXSPI.offset218)
#define FLEXSPI_LUT7			(IMXRT_FLEXSPI.offset21C)
#define FLEXSPI_LUT8			(IMXRT_FLEXSPI.offset220)
#define FLEXSPI_LUT9			(IMXRT_FLEXSPI.offset224)
#define FLEXSPI_LUT10			(IMXRT_FLEXSPI.offset228)
#define FLEXSPI_LUT11			(IMXRT_FLEXSPI.offset22C)
#define FLEXSPI_LUT12			(IMXRT_FLEXSPI.offset230)
#define FLEXSPI_LUT13			(IMXRT_FLEXSPI.offset234)
#define FLEXSPI_LUT14			(IMXRT_FLEXSPI.offset238)
#define FLEXSPI_LUT15			(IMXRT_FLEXSPI.offset23C)
#define FLEXSPI_LUT16			(IMXRT_FLEXSPI.offset240)
#define FLEXSPI_LUT17			(IMXRT_FLEXSPI.offset244)
#define FLEXSPI_LUT18			(IMXRT_FLEXSPI.offset248)
#define FLEXSPI_LUT19			(IMXRT_FLEXSPI.offset24C)
#define FLEXSPI_LUT20			(IMXRT_FLEXSPI.offset250)
#define FLEXSPI_LUT21			(IMXRT_FLEXSPI.offset254)
#define FLEXSPI_LUT22			(IMXRT_FLEXSPI.offset258)
#define FLEXSPI_LUT23			(IMXRT_FLEXSPI.offset25C)
#define FLEXSPI_LUT24			(IMXRT_FLEXSPI.offset260)
#define FLEXSPI_LUT25			(IMXRT_FLEXSPI.offset264)
#define FLEXSPI_LUT26			(IMXRT_FLEXSPI.offset268)
#define FLEXSPI_LUT27			(IMXRT_FLEXSPI.offset26C)
#define FLEXSPI_LUT28			(IMXRT_FLEXSPI.offset270)
#define FLEXSPI_LUT29			(IMXRT_FLEXSPI.offset274)
#define FLEXSPI_LUT30			(IMXRT_FLEXSPI.offset278)
#define FLEXSPI_LUT31			(IMXRT_FLEXSPI.offset27C)
#define FLEXSPI_LUT32			(IMXRT_FLEXSPI.offset280)
#define FLEXSPI_LUT33			(IMXRT_FLEXSPI.offset284)
#define FLEXSPI_LUT34			(IMXRT_FLEXSPI.offset288)
#define FLEXSPI_LUT35			(IMXRT_FLEXSPI.offset28C)
#define FLEXSPI_LUT36			(IMXRT_FLEXSPI.offset290)
#define FLEXSPI_LUT37			(IMXRT_FLEXSPI.offset294)
#define FLEXSPI_LUT38			(IMXRT_FLEXSPI.offset298)
#define FLEXSPI_LUT39			(IMXRT_FLEXSPI.offset29C)
#define FLEXSPI_LUT40			(IMXRT_FLEXSPI.offset2A0)
#define FLEXSPI_LUT41			(IMXRT_FLEXSPI.offset2A4)
#define FLEXSPI_LUT42			(IMXRT_FLEXSPI.offset2A8)
#define FLEXSPI_LUT43			(IMXRT_FLEXSPI.offset2AC)
#define FLEXSPI_LUT44			(IMXRT_FLEXSPI.offset2B0)
#define FLEXSPI_LUT45			(IMXRT_FLEXSPI.offset2B4)
#define FLEXSPI_LUT46			(IMXRT_FLEXSPI.offset2B8)
#define FLEXSPI_LUT47			(IMXRT_FLEXSPI.offset2BC)
#define FLEXSPI_LUT48			(IMXRT_FLEXSPI.offset2C0)
#define FLEXSPI_LUT49			(IMXRT_FLEXSPI.offset2C4)
#define FLEXSPI_LUT50			(IMXRT_FLEXSPI.offset2C8)
#define FLEXSPI_LUT51			(IMXRT_FLEXSPI.offset2CC)
#define FLEXSPI_LUT52			(IMXRT_FLEXSPI.offset2D0)
#define FLEXSPI_LUT53			(IMXRT_FLEXSPI.offset2D4)
#define FLEXSPI_LUT54			(IMXRT_FLEXSPI.offset2D8)
#define FLEXSPI_LUT55			(IMXRT_FLEXSPI.offset2DC)
#define FLEXSPI_LUT56			(IMXRT_FLEXSPI.offset2E0)
#define FLEXSPI_LUT57			(IMXRT_FLEXSPI.offset2E4)
#define FLEXSPI_LUT58			(IMXRT_FLEXSPI.offset2E8)
#define FLEXSPI_LUT59			(IMXRT_FLEXSPI.offset2EC)
#define FLEXSPI_LUT60			(IMXRT_FLEXSPI.offset2F0)
#define FLEXSPI_LUT61			(IMXRT_FLEXSPI.offset2F4)
#define FLEXSPI_LUT62			(IMXRT_FLEXSPI.offset2F8)
#define FLEXSPI_LUT63			(IMXRT_FLEXSPI.offset2FC)
#define FLEXSPI_LUT_OPCODE1(n)			((uint32_t)(((n) & 0x3F) << 26))
#define FLEXSPI_LUT_NUM_PADS1(n)		((uint32_t)(((n) & 0x03) << 24))
#define FLEXSPI_LUT_OPERAND1(n)			((uint32_t)(((n) & 0xFF) << 16))
#define FLEXSPI_LUT_OPCODE0(n)			((uint32_t)(((n) & 0x3F) << 10))
#define FLEXSPI_LUT_NUM_PADS0(n)		((uint32_t)(((n) & 0x03) << 8))
#define FLEXSPI_LUT_OPERAND0(n)			((uint32_t)(((n) & 0xFF) << 0))
#define FLEXSPI_LUT_INSTRUCTION(opcode, pads, operand) ((uint32_t)(\
	(((opcode) & 0x3F) << 10) | (((pads) & 0x03) << 8) | ((operand) & 0xFF)))
// 30.7.8: page 1637
#define FLEXSPI_LUT_OPCODE_CMD_SDR		0x01
#define FLEXSPI_LUT_OPCODE_CMD_DDR		0x21
#define FLEXSPI_LUT_OPCODE_RADDR_SDR		0x02
#define FLEXSPI_LUT_OPCODE_RADDR_DDR		0x22
#define FLEXSPI_LUT_OPCODE_CADDR_SDR		0x03
#define FLEXSPI_LUT_OPCODE_CADDR_DDR		0x23
#define FLEXSPI_LUT_OPCODE_MODE1_SDR		0x04
#define FLEXSPI_LUT_OPCODE_MODE1_DDR		0x24
#define FLEXSPI_LUT_OPCODE_MODE2_SDR		0x05
#define FLEXSPI_LUT_OPCODE_MODE2_DDR		0x25
#define FLEXSPI_LUT_OPCODE_MODE4_SDR		0x06
#define FLEXSPI_LUT_OPCODE_MODE4_DDR		0x26
#define FLEXSPI_LUT_OPCODE_MODE8_SDR		0x07
#define FLEXSPI_LUT_OPCODE_MODE8_DDR		0x27
#define FLEXSPI_LUT_OPCODE_WRITE_SDR		0x08
#define FLEXSPI_LUT_OPCODE_WRITE_DDR		0x28
#define FLEXSPI_LUT_OPCODE_READ_SDR		0x09
#define FLEXSPI_LUT_OPCODE_READ_DDR		0x29
#define FLEXSPI_LUT_OPCODE_LEARN_SDR		0x0A
#define FLEXSPI_LUT_OPCODE_LEARN_DDR		0x2A
#define FLEXSPI_LUT_OPCODE_DATSZ_SDR		0x0B
#define FLEXSPI_LUT_OPCODE_DATSZ_DDR		0x2B
#define FLEXSPI_LUT_OPCODE_DUMMY_SDR		0x0C
#define FLEXSPI_LUT_OPCODE_DUMMY_DDR		0x2C
#define FLEXSPI_LUT_OPCODE_DUMMY_RWDS_SDR	0x0D
#define FLEXSPI_LUT_OPCODE_DUMMY_RWDS_DDR	0x2D
#define FLEXSPI_LUT_OPCODE_JMP_ON_CS		0x1F
#define FLEXSPI_LUT_OPCODE_STOP			0x00
#define FLEXSPI_LUT_NUM_PADS_1			0x00
#define FLEXSPI_LUT_NUM_PADS_2			0x01
#define FLEXSPI_LUT_NUM_PADS_4			0x02
#define FLEXSPI_LUT_NUM_PADS_8			0x03

#define IMXRT_FLEXSPI2		(*(IMXRT_REGISTER32_t *)IMXRT_FLEXSPI2_ADDRESS)
#define FLEXSPI2_MCR0			(IMXRT_FLEXSPI2.offset000)
#define FLEXSPI2_MCR1			(IMXRT_FLEXSPI2.offset004)
#define FLEXSPI2_MCR2			(IMXRT_FLEXSPI2.offset008)
#define FLEXSPI2_AHBCR			(IMXRT_FLEXSPI2.offset00C)
#define FLEXSPI2_INTEN			(IMXRT_FLEXSPI2.offset010)
#define FLEXSPI2_INTR			(IMXRT_FLEXSPI2.offset014)
#define FLEXSPI2_LUTKEY			(IMXRT_FLEXSPI2.offset018)
#define FLEXSPI2_LUTCR			(IMXRT_FLEXSPI2.offset01C)
#define FLEXSPI2_AHBRXBUF0CR0		(IMXRT_FLEXSPI2.offset020)
#define FLEXSPI2_AHBRXBUF1CR0		(IMXRT_FLEXSPI2.offset024)
#define FLEXSPI2_AHBRXBUF2CR0		(IMXRT_FLEXSPI2.offset028)
#define FLEXSPI2_AHBRXBUF3CR0		(IMXRT_FLEXSPI2.offset02C)
#define FLEXSPI2_FLSHA1CR0		(IMXRT_FLEXSPI2.offset060)
#define FLEXSPI2_FLSHA2CR0		(IMXRT_FLEXSPI2.offset064)
#define FLEXSPI2_FLSHB1CR0		(IMXRT_FLEXSPI2.offset068)
#define FLEXSPI2_FLSHB2CR0		(IMXRT_FLEXSPI2.offset06C)
#define FLEXSPI2_FLSHA1CR1		(IMXRT_FLEXSPI2.offset070)
#define FLEXSPI2_FLSHA2CR1		(IMXRT_FLEXSPI2.offset074)
#define FLEXSPI2_FLSHB1CR1		(IMXRT_FLEXSPI2.offset078)
#define FLEXSPI2_FLSHB2CR1		(IMXRT_FLEXSPI2.offset07C)
#define FLEXSPI2_FLSHA1CR2		(IMXRT_FLEXSPI2.offset080)
#define FLEXSPI2_FLSHA2CR2		(IMXRT_FLEXSPI2.offset084)
#define FLEXSPI2_FLSHB1CR2		(IMXRT_FLEXSPI2.offset088)
#define FLEXSPI2_FLSHB2CR2		(IMXRT_FLEXSPI2.offset08C)
#define FLEXSPI2_FLSHCR4		(IMXRT_FLEXSPI2.offset094)
#define FLEXSPI2_IPCR0			(IMXRT_FLEXSPI2.offset0A0)
#define FLEXSPI2_IPCR1			(IMXRT_FLEXSPI2.offset0A4)
#define FLEXSPI2_IPCMD			(IMXRT_FLEXSPI2.offset0B0)
#define FLEXSPI2_IPRXFCR		(IMXRT_FLEXSPI2.offset0B8)
#define FLEXSPI2_IPTXFCR		(IMXRT_FLEXSPI2.offset0BC)
#define FLEXSPI2_DLLACR			(IMXRT_FLEXSPI2.offset0C0)
#define FLEXSPI2_DLLBCR			(IMXRT_FLEXSPI2.offset0C4)
#define FLEXSPI2_STS0			(IMXRT_FLEXSPI2.offset0E0)
#define FLEXSPI2_STS1			(IMXRT_FLEXSPI2.offset0E4)
#define FLEXSPI2_STS2			(IMXRT_FLEXSPI2.offset0E8)
#define FLEXSPI2_AHBSPNDSTS		(IMXRT_FLEXSPI2.offset0EC)
#define FLEXSPI2_IPRXFSTS		(IMXRT_FLEXSPI2.offset0F0)
#define FLEXSPI2_IPTXFSTS		(IMXRT_FLEXSPI2.offset0F4)
#define FLEXSPI2_RFDR0			(IMXRT_FLEXSPI2.offset100)
#define FLEXSPI2_RFDR1			(IMXRT_FLEXSPI2.offset104)
#define FLEXSPI2_RFDR2			(IMXRT_FLEXSPI2.offset108)
#define FLEXSPI2_RFDR3			(IMXRT_FLEXSPI2.offset10C)
#define FLEXSPI2_RFDR4			(IMXRT_FLEXSPI2.offset110)
#define FLEXSPI2_RFDR5			(IMXRT_FLEXSPI2.offset114)
#define FLEXSPI2_RFDR6			(IMXRT_FLEXSPI2.offset118)
#define FLEXSPI2_RFDR7			(IMXRT_FLEXSPI2.offset11C)
#define FLEXSPI2_RFDR8			(IMXRT_FLEXSPI2.offset120)
#define FLEXSPI2_RFDR9			(IMXRT_FLEXSPI2.offset124)
#define FLEXSPI2_RFDR10			(IMXRT_FLEXSPI2.offset128)
#define FLEXSPI2_RFDR11			(IMXRT_FLEXSPI2.offset12C)
#define FLEXSPI2_RFDR12			(IMXRT_FLEXSPI2.offset130)
#define FLEXSPI2_RFDR13			(IMXRT_FLEXSPI2.offset134)
#define FLEXSPI2_RFDR14			(IMXRT_FLEXSPI2.offset138)
#define FLEXSPI2_RFDR15			(IMXRT_FLEXSPI2.offset13C)
#define FLEXSPI2_RFDR16			(IMXRT_FLEXSPI2.offset140)
#define FLEXSPI2_RFDR17			(IMXRT_FLEXSPI2.offset144)
#define FLEXSPI2_RFDR18			(IMXRT_FLEXSPI2.offset148)
#define FLEXSPI2_RFDR19			(IMXRT_FLEXSPI2.offset14C)
#define FLEXSPI2_RFDR20			(IMXRT_FLEXSPI2.offset150)
#define FLEXSPI2_RFDR21			(IMXRT_FLEXSPI2.offset154)
#define FLEXSPI2_RFDR22			(IMXRT_FLEXSPI2.offset158)
#define FLEXSPI2_RFDR23			(IMXRT_FLEXSPI2.offset15C)
#define FLEXSPI2_RFDR24			(IMXRT_FLEXSPI2.offset160)
#define FLEXSPI2_RFDR25			(IMXRT_FLEXSPI2.offset164)
#define FLEXSPI2_RFDR26			(IMXRT_FLEXSPI2.offset168)
#define FLEXSPI2_RFDR27			(IMXRT_FLEXSPI2.offset16C)
#define FLEXSPI2_RFDR28			(IMXRT_FLEXSPI2.offset170)
#define FLEXSPI2_RFDR29			(IMXRT_FLEXSPI2.offset174)
#define FLEXSPI2_RFDR30			(IMXRT_FLEXSPI2.offset178)
#define FLEXSPI2_RFDR31			(IMXRT_FLEXSPI2.offset17C)
#define FLEXSPI2_TFDR0			(IMXRT_FLEXSPI2.offset180)
#define FLEXSPI2_TFDR1			(IMXRT_FLEXSPI2.offset184)
#define FLEXSPI2_TFDR2			(IMXRT_FLEXSPI2.offset188)
#define FLEXSPI2_TFDR3			(IMXRT_FLEXSPI2.offset18C)
#define FLEXSPI2_TFDR4			(IMXRT_FLEXSPI2.offset190)
#define FLEXSPI2_TFDR5			(IMXRT_FLEXSPI2.offset194)
#define FLEXSPI2_TFDR6			(IMXRT_FLEXSPI2.offset198)
#define FLEXSPI2_TFDR7			(IMXRT_FLEXSPI2.offset19C)
#define FLEXSPI2_TFDR8			(IMXRT_FLEXSPI2.offset1A0)
#define FLEXSPI2_TFDR9			(IMXRT_FLEXSPI2.offset1A4)
#define FLEXSPI2_TFDR10			(IMXRT_FLEXSPI2.offset1A8)
#define FLEXSPI2_TFDR11			(IMXRT_FLEXSPI2.offset1AC)
#define FLEXSPI2_TFDR12			(IMXRT_FLEXSPI2.offset1B0)
#define FLEXSPI2_TFDR13			(IMXRT_FLEXSPI2.offset1B4)
#define FLEXSPI2_TFDR14			(IMXRT_FLEXSPI2.offset1B8)
#define FLEXSPI2_TFDR15			(IMXRT_FLEXSPI2.offset1BC)
#define FLEXSPI2_TFDR16			(IMXRT_FLEXSPI2.offset1C0)
#define FLEXSPI2_TFDR17			(IMXRT_FLEXSPI2.offset1C4)
#define FLEXSPI2_TFDR18			(IMXRT_FLEXSPI2.offset1C8)
#define FLEXSPI2_TFDR19			(IMXRT_FLEXSPI2.offset1CC)
#define FLEXSPI2_TFDR20			(IMXRT_FLEXSPI2.offset1D0)
#define FLEXSPI2_TFDR21			(IMXRT_FLEXSPI2.offset1D4)
#define FLEXSPI2_TFDR22			(IMXRT_FLEXSPI2.offset1D8)
#define FLEXSPI2_TFDR23			(IMXRT_FLEXSPI2.offset1DC)
#define FLEXSPI2_TFDR24			(IMXRT_FLEXSPI2.offset1E0)
#define FLEXSPI2_TFDR25			(IMXRT_FLEXSPI2.offset1E4)
#define FLEXSPI2_TFDR26			(IMXRT_FLEXSPI2.offset1E8)
#define FLEXSPI2_TFDR27			(IMXRT_FLEXSPI2.offset1EC)
#define FLEXSPI2_TFDR28			(IMXRT_FLEXSPI2.offset1F0)
#define FLEXSPI2_TFDR29			(IMXRT_FLEXSPI2.offset1F4)
#define FLEXSPI2_TFDR30			(IMXRT_FLEXSPI2.offset1F8)
#define FLEXSPI2_TFDR31			(IMXRT_FLEXSPI2.offset1FC)
#define FLEXSPI2_LUT0			(IMXRT_FLEXSPI2.offset200)
#define FLEXSPI2_LUT1			(IMXRT_FLEXSPI2.offset204)
#define FLEXSPI2_LUT2			(IMXRT_FLEXSPI2.offset208)
#define FLEXSPI2_LUT3			(IMXRT_FLEXSPI2.offset20C)
#define FLEXSPI2_LUT4			(IMXRT_FLEXSPI2.offset210)
#define FLEXSPI2_LUT5			(IMXRT_FLEXSPI2.offset214)
#define FLEXSPI2_LUT6			(IMXRT_FLEXSPI2.offset218)
#define FLEXSPI2_LUT7			(IMXRT_FLEXSPI2.offset21C)
#define FLEXSPI2_LUT8			(IMXRT_FLEXSPI2.offset220)
#define FLEXSPI2_LUT9			(IMXRT_FLEXSPI2.offset224)
#define FLEXSPI2_LUT10			(IMXRT_FLEXSPI2.offset228)
#define FLEXSPI2_LUT11			(IMXRT_FLEXSPI2.offset22C)
#define FLEXSPI2_LUT12			(IMXRT_FLEXSPI2.offset230)
#define FLEXSPI2_LUT13			(IMXRT_FLEXSPI2.offset234)
#define FLEXSPI2_LUT14			(IMXRT_FLEXSPI2.offset238)
#define FLEXSPI2_LUT15			(IMXRT_FLEXSPI2.offset23C)
#define FLEXSPI2_LUT16			(IMXRT_FLEXSPI2.offset240)
#define FLEXSPI2_LUT17			(IMXRT_FLEXSPI2.offset244)
#define FLEXSPI2_LUT18			(IMXRT_FLEXSPI2.offset248)
#define FLEXSPI2_LUT19			(IMXRT_FLEXSPI2.offset24C)
#define FLEXSPI2_LUT20			(IMXRT_FLEXSPI2.offset250)
#define FLEXSPI2_LUT21			(IMXRT_FLEXSPI2.offset254)
#define FLEXSPI2_LUT22			(IMXRT_FLEXSPI2.offset258)
#define FLEXSPI2_LUT23			(IMXRT_FLEXSPI2.offset25C)
#define FLEXSPI2_LUT24			(IMXRT_FLEXSPI2.offset260)
#define FLEXSPI2_LUT25			(IMXRT_FLEXSPI2.offset264)
#define FLEXSPI2_LUT26			(IMXRT_FLEXSPI2.offset268)
#define FLEXSPI2_LUT27			(IMXRT_FLEXSPI2.offset26C)
#define FLEXSPI2_LUT28			(IMXRT_FLEXSPI2.offset270)
#define FLEXSPI2_LUT29			(IMXRT_FLEXSPI2.offset274)
#define FLEXSPI2_LUT30			(IMXRT_FLEXSPI2.offset278)
#define FLEXSPI2_LUT31			(IMXRT_FLEXSPI2.offset27C)
#define FLEXSPI2_LUT32			(IMXRT_FLEXSPI2.offset280)
#define FLEXSPI2_LUT33			(IMXRT_FLEXSPI2.offset284)
#define FLEXSPI2_LUT34			(IMXRT_FLEXSPI2.offset288)
#define FLEXSPI2_LUT35			(IMXRT_FLEXSPI2.offset28C)
#define FLEXSPI2_LUT36			(IMXRT_FLEXSPI2.offset290)
#define FLEXSPI2_LUT37			(IMXRT_FLEXSPI2.offset294)
#define FLEXSPI2_LUT38			(IMXRT_FLEXSPI2.offset298)
#define FLEXSPI2_LUT39			(IMXRT_FLEXSPI2.offset29C)
#define FLEXSPI2_LUT40			(IMXRT_FLEXSPI2.offset2A0)
#define FLEXSPI2_LUT41			(IMXRT_FLEXSPI2.offset2A4)
#define FLEXSPI2_LUT42			(IMXRT_FLEXSPI2.offset2A8)
#define FLEXSPI2_LUT43			(IMXRT_FLEXSPI2.offset2AC)
#define FLEXSPI2_LUT44			(IMXRT_FLEXSPI2.offset2B0)
#define FLEXSPI2_LUT45			(IMXRT_FLEXSPI2.offset2B4)
#define FLEXSPI2_LUT46			(IMXRT_FLEXSPI2.offset2B8)
#define FLEXSPI2_LUT47			(IMXRT_FLEXSPI2.offset2BC)
#define FLEXSPI2_LUT48			(IMXRT_FLEXSPI2.offset2C0)
#define FLEXSPI2_LUT49			(IMXRT_FLEXSPI2.offset2C4)
#define FLEXSPI2_LUT50			(IMXRT_FLEXSPI2.offset2C8)
#define FLEXSPI2_LUT51			(IMXRT_FLEXSPI2.offset2CC)
#define FLEXSPI2_LUT52			(IMXRT_FLEXSPI2.offset2D0)
#define FLEXSPI2_LUT53			(IMXRT_FLEXSPI2.offset2D4)
#define FLEXSPI2_LUT54			(IMXRT_FLEXSPI2.offset2D8)
#define FLEXSPI2_LUT55			(IMXRT_FLEXSPI2.offset2DC)
#define FLEXSPI2_LUT56			(IMXRT_FLEXSPI2.offset2E0)
#define FLEXSPI2_LUT57			(IMXRT_FLEXSPI2.offset2E4)
#define FLEXSPI2_LUT58			(IMXRT_FLEXSPI2.offset2E8)
#define FLEXSPI2_LUT59			(IMXRT_FLEXSPI2.offset2EC)
#define FLEXSPI2_LUT60			(IMXRT_FLEXSPI2.offset2F0)
#define FLEXSPI2_LUT61			(IMXRT_FLEXSPI2.offset2F4)
#define FLEXSPI2_LUT62			(IMXRT_FLEXSPI2.offset2F8)
#define FLEXSPI2_LUT63			(IMXRT_FLEXSPI2.offset2FC)

// 17.6: page 1190
#define IMXRT_GPC		(*(IMXRT_REGISTER32_t *)IMXRT_GPC_ADDRESS)
#define GPC_CNTR			(IMXRT_GPC.offset000)
#define GPC_IMR1			(IMXRT_GPC.offset008)
#define GPC_IMR2			(IMXRT_GPC.offset00C)
#define GPC_IMR3			(IMXRT_GPC.offset010)
#define GPC_IMR4			(IMXRT_GPC.offset014)
#define GPC_ISR1			(IMXRT_GPC.offset018)
#define GPC_ISR2			(IMXRT_GPC.offset01C)
#define GPC_ISR3			(IMXRT_GPC.offset020)
#define GPC_ISR4			(IMXRT_GPC.offset024)
#define GPC_IMR5			(IMXRT_GPC.offset034)
#define GPC_ISR5			(IMXRT_GPC.offset038)
#define GPC_CNTR_PDRAM0_PGE			((uint32_t)(1<<22))
#define GPC_CNTR_MEGA_PUP_REQ			((uint32_t)(1<<3))
#define GPC_CNTR_MEGA_PDN_REQ			((uint32_t)(1<<2))
// page 1602
#define PGC_MEGA_CTRL			(IMXRT_GPC.offset220)
#define PGC_MEGA_PUPSCR			(IMXRT_GPC.offset224)
#define PGC_MEGA_PDNSCR			(IMXRT_GPC.offset228)
#define PGC_MEGA_SR			(IMXRT_GPC.offset22C)
#define PGC_CPU_CTRL			(IMXRT_GPC.offset2A0)
#define PGC_CPU_PUPSCR			(IMXRT_GPC.offset2A4)
#define PGC_CPU_PDNSCR			(IMXRT_GPC.offset2A8)
#define PGC_CPU_SR			(IMXRT_GPC.offset2AC)
#define PGC_MEGA_CTRL_PCR			((uint32_t)(1<<0))
#define PGC_MEGA_PUPSCR_SW2ISO(n)		((uint32_t)(((n) & 0x3F) << 8))
#define PGC_MEGA_PUPSCR_SW(n)			((uint32_t)(((n) & 0x3F) << 0))
#define PGC_MEGA_PDNSCR_ISO2SW(n)		((uint32_t)(((n) & 0x3F) << 8))
#define PGC_MEGA_PDNSCR_ISO(n)			((uint32_t)(((n) & 0x3F) << 0))
#define PGC_MEGA_SR_PSR				((uint32_t)(1<<0))
#define PGC_CPU_CTRL_PCR			((uint32_t)(1<<0))
#define PGC_CPU_PUPSCR_SW2ISO(n)		((uint32_t)(((n) & 0x3F) << 8))
#define PGC_CPU_PUPSCR_SW(n)			((uint32_t)(((n) & 0x3F) << 0))
#define PGC_CPU_PDNSCR_ISO2SW(n)		((uint32_t)(((n) & 0x3F) << 8))
#define PGC_CPU_PDNSCR_ISO(n)			((uint32_t)(((n) & 0x3F) << 0))
#define PGC_CPU_SR_PSR				((uint32_t)(1<<0))

// 12.5.1: page 961
typedef struct {
        volatile uint32_t DR;                  // 00
        volatile uint32_t GDIR;                // 04
        volatile uint32_t PSR;                 // 08
        volatile uint32_t ICR1;                // 0C
        volatile uint32_t ICR2;                // 10
        volatile uint32_t IMR;                 // 14
        volatile uint32_t ISR;                 // 18
        volatile uint32_t EDGE_SEL;            // 1C
        uint32_t          UNUSED[25];          // 20 - 83
        volatile uint32_t DR_SET;              // 84
        volatile uint32_t DR_CLEAR;            // 88
        volatile uint32_t DR_TOGGLE;           // 8C

} IMXRT_GPIO_t;

#define IMXRT_GPIO1		(*(IMXRT_GPIO_t *)IMXRT_GPIO1_ADDRESS)
#define GPIO1_DR			(IMXRT_GPIO1.DR)
#define GPIO1_GDIR			(IMXRT_GPIO1.GDIR)
#define GPIO1_PSR			(IMXRT_GPIO1.PSR)
#define GPIO1_ICR1			(IMXRT_GPIO1.ICR1)
#define GPIO1_ICR2			(IMXRT_GPIO1.ICR2)
#define GPIO1_IMR			(IMXRT_GPIO1.IMR)
#define GPIO1_ISR			(IMXRT_GPIO1.ISR)
#define GPIO1_EDGE_SEL			(IMXRT_GPIO1.EDGE_SEL)
#define GPIO1_DR_SET			(IMXRT_GPIO1.DR_SET)
#define GPIO1_DR_CLEAR			(IMXRT_GPIO1.DR_CLEAR)
#define GPIO1_DR_TOGGLE			(IMXRT_GPIO1.DR_TOGGLE)
#define IMXRT_GPIO2		(*(IMXRT_GPIO_t *)IMXRT_GPIO2_ADDRESS)
#define GPIO2_DR			(IMXRT_GPIO2.DR)
#define GPIO2_GDIR			(IMXRT_GPIO2.GDIR)
#define GPIO2_PSR			(IMXRT_GPIO2.PSR)
#define GPIO2_ICR1			(IMXRT_GPIO2.ICR1)
#define GPIO2_ICR2			(IMXRT_GPIO2.ICR2)
#define GPIO2_IMR			(IMXRT_GPIO2.IMR)
#define GPIO2_ISR			(IMXRT_GPIO2.ISR)
#define GPIO2_EDGE_SEL			(IMXRT_GPIO2.EDGE_SEL)
#define GPIO2_DR_SET			(IMXRT_GPIO2.DR_SET)
#define GPIO2_DR_CLEAR			(IMXRT_GPIO2.DR_CLEAR)
#define GPIO2_DR_TOGGLE			(IMXRT_GPIO2.DR_TOGGLE)
#define IMXRT_GPIO3		(*(IMXRT_GPIO_t *)IMXRT_GPIO3_ADDRESS)
#define GPIO3_DR			(IMXRT_GPIO3.DR)
#define GPIO3_GDIR			(IMXRT_GPIO3.GDIR)
#define GPIO3_PSR			(IMXRT_GPIO3.PSR)
#define GPIO3_ICR1			(IMXRT_GPIO3.ICR1)
#define GPIO3_ICR2			(IMXRT_GPIO3.ICR2)
#define GPIO3_IMR			(IMXRT_GPIO3.IMR)
#define GPIO3_ISR			(IMXRT_GPIO3.ISR)
#define GPIO3_EDGE_SEL			(IMXRT_GPIO3.EDGE_SEL)
#define GPIO3_DR_SET			(IMXRT_GPIO3.DR_SET)
#define GPIO3_DR_CLEAR			(IMXRT_GPIO3.DR_CLEAR)
#define GPIO3_DR_TOGGLE			(IMXRT_GPIO3.DR_TOGGLE)
#define IMXRT_GPIO4		(*(IMXRT_GPIO_t *)IMXRT_GPIO4_ADDRESS)
#define GPIO4_DR			(IMXRT_GPIO4.DR)
#define GPIO4_GDIR			(IMXRT_GPIO4.GDIR)
#define GPIO4_PSR			(IMXRT_GPIO4.PSR)
#define GPIO4_ICR1			(IMXRT_GPIO4.ICR1)
#define GPIO4_ICR2			(IMXRT_GPIO4.ICR2)
#define GPIO4_IMR			(IMXRT_GPIO4.IMR)
#define GPIO4_ISR			(IMXRT_GPIO4.ISR)
#define GPIO4_EDGE_SEL			(IMXRT_GPIO4.EDGE_SEL)
#define GPIO4_DR_SET			(IMXRT_GPIO4.DR_SET)
#define GPIO4_DR_CLEAR			(IMXRT_GPIO4.DR_CLEAR)
#define GPIO4_DR_TOGGLE			(IMXRT_GPIO4.DR_TOGGLE)
#define IMXRT_GPIO5		(*(IMXRT_GPIO_t *)IMXRT_GPIO5_ADDRESS)
#define GPIO5_DR			(IMXRT_GPIO5.DR)
#define GPIO5_GDIR			(IMXRT_GPIO5.GDIR)
#define GPIO5_PSR			(IMXRT_GPIO5.PSR)
#define GPIO5_ICR1			(IMXRT_GPIO5.ICR1)
#define GPIO5_ICR2			(IMXRT_GPIO5.ICR2)
#define GPIO5_IMR			(IMXRT_GPIO5.IMR)
#define GPIO5_ISR			(IMXRT_GPIO5.ISR)
#define GPIO5_EDGE_SEL			(IMXRT_GPIO5.EDGE_SEL)
#define GPIO5_DR_SET			(IMXRT_GPIO5.DR_SET)
#define GPIO5_DR_CLEAR			(IMXRT_GPIO5.DR_CLEAR)
#define GPIO5_DR_TOGGLE			(IMXRT_GPIO5.DR_TOGGLE)
#define IMXRT_GPIO6		(*(IMXRT_GPIO_t *)IMXRT_GPIO6_ADDRESS)
#define GPIO6_DR			(IMXRT_GPIO6.DR)
#define GPIO6_GDIR			(IMXRT_GPIO6.GDIR)
#define GPIO6_PSR			(IMXRT_GPIO6.PSR)
#define GPIO6_ICR1			(IMXRT_GPIO6.ICR1)
#define GPIO6_ICR2			(IMXRT_GPIO6.ICR2)
#define GPIO6_IMR			(IMXRT_GPIO6.IMR)
#define GPIO6_ISR			(IMXRT_GPIO6.ISR)
#define GPIO6_EDGE_SEL			(IMXRT_GPIO6.EDGE_SEL)
#define GPIO6_DR_SET			(IMXRT_GPIO6.DR_SET)
#define GPIO6_DR_CLEAR			(IMXRT_GPIO6.DR_CLEAR)
#define GPIO6_DR_TOGGLE			(IMXRT_GPIO6.DR_TOGGLE)
#define IMXRT_GPIO7		(*(IMXRT_GPIO_t *)IMXRT_GPIO7_ADDRESS)
#define GPIO7_DR			(IMXRT_GPIO7.DR)
#define GPIO7_GDIR			(IMXRT_GPIO7.GDIR)
#define GPIO7_PSR			(IMXRT_GPIO7.PSR)
#define GPIO7_ICR1			(IMXRT_GPIO7.ICR1)
#define GPIO7_ICR2			(IMXRT_GPIO7.ICR2)
#define GPIO7_IMR			(IMXRT_GPIO7.IMR)
#define GPIO7_ISR			(IMXRT_GPIO7.ISR)
#define GPIO7_EDGE_SEL			(IMXRT_GPIO7.EDGE_SEL)
#define GPIO7_DR_SET			(IMXRT_GPIO7.DR_SET)
#define GPIO7_DR_CLEAR			(IMXRT_GPIO7.DR_CLEAR)
#define GPIO7_DR_TOGGLE			(IMXRT_GPIO7.DR_TOGGLE)
#define IMXRT_GPIO8		(*(IMXRT_GPIO_t *)IMXRT_GPIO8_ADDRESS)
#define GPIO8_DR			(IMXRT_GPIO8.DR)
#define GPIO8_GDIR			(IMXRT_GPIO8.GDIR)
#define GPIO8_PSR			(IMXRT_GPIO8.PSR)
#define GPIO8_ICR1			(IMXRT_GPIO8.ICR1)
#define GPIO8_ICR2			(IMXRT_GPIO8.ICR2)
#define GPIO8_IMR			(IMXRT_GPIO8.IMR)
#define GPIO8_ISR			(IMXRT_GPIO8.ISR)
#define GPIO8_EDGE_SEL			(IMXRT_GPIO8.EDGE_SEL)
#define GPIO8_DR_SET			(IMXRT_GPIO8.DR_SET)
#define GPIO8_DR_CLEAR			(IMXRT_GPIO8.DR_CLEAR)
#define GPIO8_DR_TOGGLE			(IMXRT_GPIO8.DR_TOGGLE)
#define IMXRT_GPIO9		(*(IMXRT_GPIO_t *)IMXRT_GPIO9_ADDRESS)
#define GPIO9_DR			(IMXRT_GPIO9.DR)
#define GPIO9_GDIR			(IMXRT_GPIO9.GDIR)
#define GPIO9_PSR			(IMXRT_GPIO9.PSR)
#define GPIO9_ICR1			(IMXRT_GPIO9.ICR1)
#define GPIO9_ICR2			(IMXRT_GPIO9.ICR2)
#define GPIO9_IMR			(IMXRT_GPIO9.IMR)
#define GPIO9_ISR			(IMXRT_GPIO9.ISR)
#define GPIO9_EDGE_SEL			(IMXRT_GPIO9.EDGE_SEL)
#define GPIO9_DR_SET			(IMXRT_GPIO9.DR_SET)
#define GPIO9_DR_CLEAR			(IMXRT_GPIO9.DR_CLEAR)
#define GPIO9_DR_TOGGLE			(IMXRT_GPIO9.DR_TOGGLE)

// 52.7: page 2957
#define IMXRT_GPT1		(*(IMXRT_REGISTER32_t *)IMXRT_GPT1_ADDRESS)
#define GPT1_CR				(IMXRT_GPT1.offset000)
#define GPT1_PR				(IMXRT_GPT1.offset004)
#define GPT1_SR				(IMXRT_GPT1.offset008)
#define GPT1_IR				(IMXRT_GPT1.offset00C)
#define GPT1_OCR1			(IMXRT_GPT1.offset010)
#define GPT1_OCR2			(IMXRT_GPT1.offset014)
#define GPT1_OCR3			(IMXRT_GPT1.offset018)
#define GPT1_ICR1			(IMXRT_GPT1.offset01C)
#define GPT1_ICR2			(IMXRT_GPT1.offset020)
#define GPT1_CNT			(IMXRT_GPT1.offset024)
#define IMXRT_GPT2		(*(IMXRT_REGISTER32_t *)IMXRT_GPT2_ADDRESS)
#define GPT2_CR				(IMXRT_GPT2.offset000)
#define GPT2_PR				(IMXRT_GPT2.offset004)
#define GPT2_SR				(IMXRT_GPT2.offset008)
#define GPT2_IR				(IMXRT_GPT2.offset00C)
#define GPT2_OCR1			(IMXRT_GPT2.offset010)
#define GPT2_OCR2			(IMXRT_GPT2.offset014)
#define GPT2_OCR3			(IMXRT_GPT2.offset018)
#define GPT2_ICR1			(IMXRT_GPT2.offset01C)
#define GPT2_ICR2			(IMXRT_GPT2.offset020)
#define GPT2_CNT			(IMXRT_GPT2.offset024)
#define GPT_CR_FO3				((uint32_t)(1<<31))
#define GPT_CR_FO2				((uint32_t)(1<<30))
#define GPT_CR_FO1				((uint32_t)(1<<29))
#define GPT_CR_OM3(n)				((uint32_t)(((n) & 0x07) << 26))
#define GPT_CR_OM2(n)				((uint32_t)(((n) & 0x07) << 23))
#define GPT_CR_OM1(n)				((uint32_t)(((n) & 0x07) << 20))
#define GPT_CR_IM2(n)				((uint32_t)(((n) & 0x03) << 18))
#define GPT_CR_IM1(n)				((uint32_t)(((n) & 0x03) << 16))
#define GPT_CR_SWR				((uint32_t)(1<<15))
#define GPT_CR_EN_24M				((uint32_t)(1<<10))
#define GPT_CR_FRR				((uint32_t)(1<<9))
#define GPT_CR_CLKSRC(n)			((uint32_t)(((n) & 0x07) << 6))
#define GPT_CR_STOPEN				((uint32_t)(1<<5))
#define GPT_CR_DOZEEN				((uint32_t)(1<<4))
#define GPT_CR_WAITEN				((uint32_t)(1<<3))
#define GPT_CR_DBGEN				((uint32_t)(1<<2))
#define GPT_CR_ENMOD				((uint32_t)(1<<1))
#define GPT_CR_EN				((uint32_t)(1<<0))
#define GPT_PR_PRESCALER24M(n)			((uint32_t)(((n) & 0x0F) << 12))
#define GPT_PR_PRESCALER(n)			((uint32_t)(((n) & 0xFFF) << 0))
#define GPT_SR_ROV				((uint32_t)(1<<5))
#define GPT_SR_IF2				((uint32_t)(1<<4))
#define GPT_SR_IF1				((uint32_t)(1<<3))
#define GPT_SR_OF3				((uint32_t)(1<<2))
#define GPT_SR_OF2				((uint32_t)(1<<1))
#define GPT_SR_OF1				((uint32_t)(1<<0))
#define GPT_IR_ROVIE				((uint32_t)(1<<5))
#define GPT_IR_IF2IE				((uint32_t)(1<<4))
#define GPT_IR_IF1IE				((uint32_t)(1<<3))
#define GPT_IR_OF3IE				((uint32_t)(1<<2))
#define GPT_IR_OF2IE				((uint32_t)(1<<1))
#define GPT_IR_OF1IE				((uint32_t)(1<<0))

// 11.4: page 327
#define IMXRT_IOMUXC_GPR	(*(IMXRT_REGISTER32_t *)IMXRT_IOMUXC_GPR_ADDRESS)
#define IOMUXC_GPR_GPR0			(IMXRT_IOMUXC_GPR.offset000)
#define IOMUXC_GPR_GPR1			(IMXRT_IOMUXC_GPR.offset004)
#define IOMUXC_GPR_GPR2			(IMXRT_IOMUXC_GPR.offset008)
#define IOMUXC_GPR_GPR3			(IMXRT_IOMUXC_GPR.offset00C)
#define IOMUXC_GPR_GPR4			(IMXRT_IOMUXC_GPR.offset010)
#define IOMUXC_GPR_GPR5			(IMXRT_IOMUXC_GPR.offset014)
#define IOMUXC_GPR_GPR6			(IMXRT_IOMUXC_GPR.offset018)
#define IOMUXC_GPR_GPR7			(IMXRT_IOMUXC_GPR.offset01C)
#define IOMUXC_GPR_GPR8			(IMXRT_IOMUXC_GPR.offset020)
#define IOMUXC_GPR_GPR9			(IMXRT_IOMUXC_GPR.offset024)
#define IOMUXC_GPR_GPR10		(IMXRT_IOMUXC_GPR.offset028)
#define IOMUXC_GPR_GPR11		(IMXRT_IOMUXC_GPR.offset02C)
#define IOMUXC_GPR_GPR12		(IMXRT_IOMUXC_GPR.offset030)
#define IOMUXC_GPR_GPR13		(IMXRT_IOMUXC_GPR.offset034)
#define IOMUXC_GPR_GPR14		(IMXRT_IOMUXC_GPR.offset038)
#define IOMUXC_GPR_GPR15		(IMXRT_IOMUXC_GPR.offset03C)
#define IOMUXC_GPR_GPR16		(IMXRT_IOMUXC_GPR.offset040)
#define IOMUXC_GPR_GPR17		(IMXRT_IOMUXC_GPR.offset044)
#define IOMUXC_GPR_GPR18		(IMXRT_IOMUXC_GPR.offset048)
#define IOMUXC_GPR_GPR19		(IMXRT_IOMUXC_GPR.offset04C)
#define IOMUXC_GPR_GPR20		(IMXRT_IOMUXC_GPR.offset050)
#define IOMUXC_GPR_GPR21		(IMXRT_IOMUXC_GPR.offset054)
#define IOMUXC_GPR_GPR22		(IMXRT_IOMUXC_GPR.offset058)
#define IOMUXC_GPR_GPR23		(IMXRT_IOMUXC_GPR.offset05C)
#define IOMUXC_GPR_GPR24		(IMXRT_IOMUXC_GPR.offset060)
#define IOMUXC_GPR_GPR25		(IMXRT_IOMUXC_GPR.offset064)
#define IOMUXC_GPR_GPR26		(IMXRT_IOMUXC_GPR.offset068)
#define IOMUXC_GPR_GPR27		(IMXRT_IOMUXC_GPR.offset06C)
#define IOMUXC_GPR_GPR28		(IMXRT_IOMUXC_GPR.offset070)
#define IOMUXC_GPR_GPR29		(IMXRT_IOMUXC_GPR.offset074)
#define IOMUXC_GPR_GPR30		(IMXRT_IOMUXC_GPR.offset078)
#define IOMUXC_GPR_GPR31		(IMXRT_IOMUXC_GPR.offset07C)
#define IOMUXC_GPR_GPR32		(IMXRT_IOMUXC_GPR.offset080)
#define IOMUXC_GPR_GPR33		(IMXRT_IOMUXC_GPR.offset084)
#define IOMUXC_GPR_GPR34		(IMXRT_IOMUXC_GPR.offset088)
#define IOMUXC_GPR_GPR1_CM7_FORCE_HCLK_EN	((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR1_ENET_IPG_CLK_S_EN	((uint32_t)(1<<23))
#define IOMUXC_GPR_GPR1_EXC_MON			((uint32_t)(1<<22))
#define IOMUXC_GPR_GPR1_SAI3_MCLK_DIR		((uint32_t)(1<<21))
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR		((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR1_SAI1_MCLK_DIR		((uint32_t)(1<<19))
#define IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR	((uint32_t)(1<<18))
#define IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR	((uint32_t)(1<<17))
#define IOMUXC_GPR_GPR1_USB_EXP_MODE		((uint32_t)(1<<15))
#define IOMUXC_GPR_GPR1_ENET2_CLK_SEL		((uint32_t)(1<<14))
#define IOMUXC_GPR_GPR1_ENET1_CLK_SEL		((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR1_GINT			((uint32_t)(1<<12))
#define IOMUXC_GPR_GPR1_SAI3_MCLK3_SEL(n)	((uint32_t)(((n) & 0x03) << 10))
#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL(n)	((uint32_t)(((n) & 0x03) << 8))
#define IOMUXC_GPR_GPR1_SAI1_MCLK3_SEL(n)	((uint32_t)(((n) & 0x03) << 6))
#define IOMUXC_GPR_GPR1_SAI1_MCLK2_SEL(n)	((uint32_t)(((n) & 0x07) << 3))
#define IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(n)	((uint32_t)(((n) & 0x07) << 0))
#define IOMUXC_GPR_GPR1_SAI3_MCLK3_SEL_MASK	IOMUXC_GPR_GPR1_SAI3_MCLK3_SEL(3)
#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL_MASK	IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL(3)
#define IOMUXC_GPR_GPR1_SAI1_MCLK3_SEL_MASK	IOMUXC_GPR_GPR1_SAI1_MCLK3_SEL(3)
#define IOMUXC_GPR_GPR1_SAI1_MCLK2_SEL_MASK	IOMUXC_GPR_GPR1_SAI1_MCLK2_SEL(7)
#define IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL_MASK	IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(7)
#define IOMUXC_GPR_GPR2_QTIMER4_TMR_CNTS_FREEZE	((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR2_QTIMER3_TMR_CNTS_FREEZE	((uint32_t)(1<<30))
#define IOMUXC_GPR_GPR2_QTIMER2_TMR_CNTS_FREEZE	((uint32_t)(1<<29))
#define IOMUXC_GPR_GPR2_QTIMER1_TMR_CNTS_FREEZE	((uint32_t)(1<<28))
#define IOMUXC_GPR_GPR2_MQS_OVERSAMPLE		((uint32_t)(1<<26))
#define IOMUXC_GPR_GPR2_MQS_EN			((uint32_t)(1<<25))
#define IOMUXC_GPR_GPR2_MQS_SW_RST		((uint32_t)(1<<24))
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV(n)		((uint32_t)(((n) & 0xFF) << 16))
#define IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP	((uint32_t)(1<<14))
#define IOMUXC_GPR_GPR2_RAM_AUTO_CLK_GATING_EN	((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING	((uint32_t)(1<<12))
#define IOMUXC_GPR_GPR2_CANFD_FILTER_BYPASS	((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR2_AXBS_P_FORCE_ROUND_ROBIN ((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR2_AXBS_P_M1_HIGH_PRIORITY	((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR2_AXBS_P_M0_HIGH_PRIORITY	((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR2_AXBS_L_FORCE_ROUND_ROBIN ((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR2_AXBS_L_DMA_HIGH_PRIORITY ((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR2_AXBS_L_AHBXL_HIGH_PRIORITY ((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV_MASK	IOMUXC_GPR_GPR2_MQS_CLK_DIV(255)
#define IOMUXC_GPR_GPR3_AXBS_L_HALTED		((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR3_OCRAM2_STATUS(n)	((uint32_t)(((n) & 0x0F) << 24))
#define IOMUXC_GPR_GPR3_OCRAM_STATUS(n)		((uint32_t)(((n) & 0x0F) << 16))
#define IOMUXC_GPR_GPR3_AXBS_L_HALT_REQ		((uint32_t)(1<<15))
#define IOMUXC_GPR_GPR3_OCRAM2_CTL(n)		((uint32_t)(((n) & 0x0F) << 8))
#define IOMUXC_GPR_GPR3_DCP_KEY_SEL		((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR3_OCRAM_CTL(n)		((uint32_t)(((n) & 0x0F) << 0))
#define IOMUXC_GPR_GPR4_FLEXSPI2_STOP_ACK	((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR4_FLEXIO3_STOP_ACK	((uint32_t)(1<<30))
#define IOMUXC_GPR_GPR4_FLEXIO2_STOP_ACK	((uint32_t)(1<<29))
#define IOMUXC_GPR_GPR4_FLEXIO1_STOP_ACK	((uint32_t)(1<<28))
#define IOMUXC_GPR_GPR4_FLEXSPI_STOP_ACK	((uint32_t)(1<<27))
#define IOMUXC_GPR_GPR4_PIT_STOP_ACK		((uint32_t)(1<<26))
#define IOMUXC_GPR_GPR4_SEMC_STOP_ACK		((uint32_t)(1<<25))
#define IOMUXC_GPR_GPR4_SAI3_STOP_ACK		((uint32_t)(1<<23))
#define IOMUXC_GPR_GPR4_SAI2_STOP_ACK		((uint32_t)(1<<22))
#define IOMUXC_GPR_GPR4_SAI1_STOP_ACK		((uint32_t)(1<<21))
#define IOMUXC_GPR_GPR4_ENET_STOP_ACK		((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR4_TRNG_STOP_ACK		((uint32_t)(1<<19))
#define IOMUXC_GPR_GPR4_CAN2_STOP_ACK		((uint32_t)(1<<18))
#define IOMUXC_GPR_GPR4_CAN1_STOP_ACK		((uint32_t)(1<<17))
#define IOMUXC_GPR_GPR4_EDMA_STOP_ACK		((uint32_t)(1<<16))
#define IOMUXC_GPR_GPR4_FLEXSPI2_STOP_REQ	((uint32_t)(1<<15))
#define IOMUXC_GPR_GPR4_FLEXIO3_STOP_REQ	((uint32_t)(1<<14))
#define IOMUXC_GPR_GPR4_FLEXIO2_STOP_REQ	((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR4_FLEXIO1_STOP_REQ	((uint32_t)(1<<12))
#define IOMUXC_GPR_GPR4_FLEXSPI_STOP_REQ	((uint32_t)(1<<11))
#define IOMUXC_GPR_GPR4_PIT_STOP_REQ		((uint32_t)(1<<10))
#define IOMUXC_GPR_GPR4_SEMC_STOP_REQ		((uint32_t)(1<<9))
#define IOMUXC_GPR_GPR4_SAI3_STOP_REQ		((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR4_SAI2_STOP_REQ		((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR4_SAI1_STOP_REQ		((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR4_ENET_STOP_REQ		((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR4_TRNG_STOP_REQ		((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR4_CAN2_STOP_REQ		((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR4_CAN1_STOP_REQ		((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR4_EDMA_STOP_REQ		((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2	((uint32_t)(1<<29))
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1	((uint32_t)(1<<28))
#define IOMUXC_GPR_GPR5_ENET2_EVENT3IN_SEL	((uint32_t)(1<<26))
#define IOMUXC_GPR_GPR5_ENET_EVENT3IN_SEL	((uint32_t)(1<<25))
#define IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL		((uint32_t)(1<<24))
#define IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL		((uint32_t)(1<<23))
#define IOMUXC_GPR_GPR5_WDOG2_MASK		((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR5_WDOG1_MASK		((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_19	((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_18	((uint32_t)(1<<30))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_17	((uint32_t)(1<<29))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_16	((uint32_t)(1<<28))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_15	((uint32_t)(1<<27))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_14	((uint32_t)(1<<26))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_13	((uint32_t)(1<<25))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_12	((uint32_t)(1<<24))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_11	((uint32_t)(1<<23))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_10	((uint32_t)(1<<22))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_9	((uint32_t)(1<<21))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_8	((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_7	((uint32_t)(1<<19))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_6	((uint32_t)(1<<18))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_5	((uint32_t)(1<<17))
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_4	((uint32_t)(1<<16))
#define IOMUXC_GPR_GPR6_QTIMER4_TRM3_INPUT_SEL	((uint32_t)(1<<15))
#define IOMUXC_GPR_GPR6_QTIMER4_TRM2_INPUT_SEL	((uint32_t)(1<<14))
#define IOMUXC_GPR_GPR6_QTIMER4_TRM1_INPUT_SEL	((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR6_QTIMER4_TRM0_INPUT_SEL	((uint32_t)(1<<12))
#define IOMUXC_GPR_GPR6_QTIMER3_TRM3_INPUT_SEL	((uint32_t)(1<<11))
#define IOMUXC_GPR_GPR6_QTIMER3_TRM2_INPUT_SEL	((uint32_t)(1<<10))
#define IOMUXC_GPR_GPR6_QTIMER3_TRM1_INPUT_SEL	((uint32_t)(1<<9))
#define IOMUXC_GPR_GPR6_QTIMER3_TRM0_INPUT_SEL	((uint32_t)(1<<8))
#define IOMUXC_GPR_GPR6_QTIMER2_TRM3_INPUT_SEL	((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR6_QTIMER2_TRM2_INPUT_SEL	((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR6_QTIMER2_TRM1_INPUT_SEL	((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR6_QTIMER2_TRM0_INPUT_SEL	((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR6_QTIMER1_TRM3_INPUT_SEL	((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR6_QTIMER1_TRM2_INPUT_SEL	((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR6_QTIMER1_TRM1_INPUT_SEL	((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR6_QTIMER1_TRM0_INPUT_SEL	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR7_LPUART8_STOP_ACK	((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR7_LPUART7_STOP_ACK	((uint32_t)(1<<30))
#define IOMUXC_GPR_GPR7_LPUART6_STOP_ACK	((uint32_t)(1<<29))
#define IOMUXC_GPR_GPR7_LPUART5_STOP_ACK	((uint32_t)(1<<28))
#define IOMUXC_GPR_GPR7_LPUART4_STOP_ACK	((uint32_t)(1<<27))
#define IOMUXC_GPR_GPR7_LPUART3_STOP_ACK	((uint32_t)(1<<26))
#define IOMUXC_GPR_GPR7_LPUART2_STOP_ACK	((uint32_t)(1<<25))
#define IOMUXC_GPR_GPR7_LPUART1_STOP_ACK	((uint32_t)(1<<24))
#define IOMUXC_GPR_GPR7_LPSPI4_STOP_ACK		((uint32_t)(1<<23))
#define IOMUXC_GPR_GPR7_LPSPI3_STOP_ACK		((uint32_t)(1<<22))
#define IOMUXC_GPR_GPR7_LPSPI2_STOP_ACK		((uint32_t)(1<<21))
#define IOMUXC_GPR_GPR7_LPSPI1_STOP_ACK		((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR7_LPI2C4_STOP_ACK		((uint32_t)(1<<19))
#define IOMUXC_GPR_GPR7_LPI2C3_STOP_ACK		((uint32_t)(1<<18))
#define IOMUXC_GPR_GPR7_LPI2C2_STOP_ACK		((uint32_t)(1<<17))
#define IOMUXC_GPR_GPR7_LPI2C1_STOP_ACK		((uint32_t)(1<<16))
#define IOMUXC_GPR_GPR7_LPUART8_STOP_REQ	((uint32_t)(1<<15))
#define IOMUXC_GPR_GPR7_LPUART7_STOP_REQ	((uint32_t)(1<<14))
#define IOMUXC_GPR_GPR7_LPUART6_STOP_REQ	((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR7_LPUART5_STOP_REQ	((uint32_t)(1<<12))
#define IOMUXC_GPR_GPR7_LPUART4_STOP_REQ	((uint32_t)(1<<11))
#define IOMUXC_GPR_GPR7_LPUART3_STOP_REQ	((uint32_t)(1<<10))
#define IOMUXC_GPR_GPR7_LPUART2_STOP_REQ	((uint32_t)(1<<9))
#define IOMUXC_GPR_GPR7_LPUART1_STOP_REQ	((uint32_t)(1<<8))
#define IOMUXC_GPR_GPR7_LPSPI4_STOP_REQ		((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR7_LPSPI3_STOP_REQ		((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR7_LPSPI2_STOP_REQ		((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR7_LPSPI1_STOP_REQ		((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR7_LPI2C4_STOP_REQ		((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR7_LPI2C3_STOP_REQ		((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR7_LPI2C2_STOP_REQ		((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR7_LPI2C1_STOP_REQ		((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR8_LPUART8_IPG_DOZE	((uint32_t)(1<<31))
#define IOMUXC_GPR_GPR8_LPUART8_IPG_STOP_MODE	((uint32_t)(1<<30))
#define IOMUXC_GPR_GPR8_LPUART7_IPG_DOZE	((uint32_t)(1<<29))
#define IOMUXC_GPR_GPR8_LPUART7_IPG_STOP_MODE	((uint32_t)(1<<28))
#define IOMUXC_GPR_GPR8_LPUART6_IPG_DOZE	((uint32_t)(1<<27))
#define IOMUXC_GPR_GPR8_LPUART6_IPG_STOP_MODE	((uint32_t)(1<<26))
#define IOMUXC_GPR_GPR8_LPUART5_IPG_DOZE	((uint32_t)(1<<25))
#define IOMUXC_GPR_GPR8_LPUART5_IPG_STOP_MODE	((uint32_t)(1<<24))
#define IOMUXC_GPR_GPR8_LPUART4_IPG_DOZE	((uint32_t)(1<<23))
#define IOMUXC_GPR_GPR8_LPUART4_IPG_STOP_MODE	((uint32_t)(1<<22))
#define IOMUXC_GPR_GPR8_LPUART3_IPG_DOZE	((uint32_t)(1<<21))
#define IOMUXC_GPR_GPR8_LPUART3_IPG_STOP_MODE	((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR8_LPUART2_IPG_DOZE	((uint32_t)(1<<19))
#define IOMUXC_GPR_GPR8_LPUART2_IPG_STOP_MODE	((uint32_t)(1<<18))
#define IOMUXC_GPR_GPR8_LPUART1_IPG_DOZE	((uint32_t)(1<<17))
#define IOMUXC_GPR_GPR8_LPUART1_IPG_STOP_MODE	((uint32_t)(1<<16))
#define IOMUXC_GPR_GPR8_LPSPI4_IPG_DOZE		((uint32_t)(1<<15))
#define IOMUXC_GPR_GPR8_LPSPI4_IPG_STOP_MODE	((uint32_t)(1<<14))
#define IOMUXC_GPR_GPR8_LPSPI3_IPG_DOZE		((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR8_LPSPI3_IPG_STOP_MODE	((uint32_t)(1<<12))
#define IOMUXC_GPR_GPR8_LPSPI2_IPG_DOZE		((uint32_t)(1<<11))
#define IOMUXC_GPR_GPR8_LPSPI2_IPG_STOP_MODE	((uint32_t)(1<<10))
#define IOMUXC_GPR_GPR8_LPSPI1_IPG_DOZE		((uint32_t)(1<<9))
#define IOMUXC_GPR_GPR8_LPSPI1_IPG_STOP_MODE	((uint32_t)(1<<8))
#define IOMUXC_GPR_GPR8_LPI2C4_IPG_DOZE		((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR8_LPI2C4_IPG_STOP_MODE	((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR8_LPI2C3_IPG_DOZE		((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR8_LPI2C3_IPG_STOP_MODE	((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR8_LPI2C2_IPG_DOZE		((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR8_LPI2C2_IPG_STOP_MODE	((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR8_LPI2C1_IPG_DOZE		((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR8_LPI2C1_IPG_STOP_MODE	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR10_LOCK_OCRAM_TZ_ADDR(n)	((uint32_t)(((n) & 0x7F) << 25))
#define IOMUXC_GPR_GPR10_LOCK_OCRAM_TZ_EN	((uint32_t)(1<<24))
#define IOMUXC_GPR_GPR10_LOCK_DCPKEY_OCOTP_OR_KEYMUX	((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR10_LOCK_SEC_ERR_RESP	((uint32_t)(1<<18))
#define IOMUXC_GPR_GPR10_LOCK_DBG_EN		((uint32_t)(1<<17))
#define IOMUXC_GPR_GPR10_LOCK_NIDEN		((uint32_t)(1<<16))
#define IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR(n)	((uint32_t)(((n) & 0x7F) << 9))
#define IOMUXC_GPR_GPR10_OCRAM_TZ_EN		((uint32_t)(1<<8))
#define IOMUXC_GPR_GPR10_DCPKEY_OCOTP_OR_KEYMUX	((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR10_SEC_ERR_RESP		((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR10_DBG_EN			((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR10_NIDEN			((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR11_LOCK_BEE_DE_RX_EN(n)	((uint32_t)(((n) & 0x0F) << 24))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R3_CTRL(n)	((uint32_t)(((n) & 0x03) << 22))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R2_CTRL(n)	((uint32_t)(((n) & 0x03) << 20))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R1_CTRL(n)	((uint32_t)(((n) & 0x03) << 18))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R0_CTRL(n)	((uint32_t)(((n) & 0x03) << 16))
#define IOMUXC_GPR_GPR11_BEE_DE_RX_EN(n)	((uint32_t)(((n) & 0x0F) << 8))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R3_CTRL(n)	((uint32_t)(((n) & 0x03) << 6))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R2_CTRL(n)	((uint32_t)(((n) & 0x03) << 4))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R1_CTRL(n)	((uint32_t)(((n) & 0x03) << 2))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R0_CTRL(n)	((uint32_t)(((n) & 0x03) << 0))
#define IOMUXC_GPR_GPR12_FLEXIO3_IPG_DOZE	((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR12_FLEXIO3_IPG_STOP_MODE	((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR12_ACMP_IPG_STOP_MODE	((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR12_FLEXIO2_IPG_DOZE	((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR12_FLEXIO2_IPG_STOP_MODE	((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR12_FLEXIO1_IPG_DOZE	((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR12_FLEXIO1_IPG_STOP_MODE	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR13_CANFD_STOP_ACK		((uint32_t)(1<<20))
#define IOMUXC_GPR_GPR13_CACHE_USB		((uint32_t)(1<<13))
#define IOMUXC_GPR_GPR13_CACHE_ENET		((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR13_CANFD_STOP_REQ		((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR13_AWCACHE_USDHC		((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR13_ARCACHE_USDHC		((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR14_CM7_MX6RT_CFGDTCMSZ(n)	((uint32_t)(((n) & 0x0F) << 20))
#define IOMUXC_GPR_GPR14_CM7_MX6RT_CFGITCMSZ(n)	((uint32_t)(((n) & 0x0F) << 16))
#define IOMUXC_GPR_GPR14_ACMP4_SAMPLE_SYNC_EN	((uint32_t)(1<<11))
#define IOMUXC_GPR_GPR14_ACMP3_SAMPLE_SYNC_EN	((uint32_t)(1<<10))
#define IOMUXC_GPR_GPR14_ACMP2_SAMPLE_SYNC_EN	((uint32_t)(1<<9))
#define IOMUXC_GPR_GPR14_ACMP1_SAMPLE_SYNC_EN	((uint32_t)(1<<8))
#define IOMUXC_GPR_GPR14_ACMP4_CMP_IGEN_TRIM_UP	((uint32_t)(1<<7))
#define IOMUXC_GPR_GPR14_ACMP3_CMP_IGEN_TRIM_UP	((uint32_t)(1<<6))
#define IOMUXC_GPR_GPR14_ACMP2_CMP_IGEN_TRIM_UP	((uint32_t)(1<<5))
#define IOMUXC_GPR_GPR14_ACMP1_CMP_IGEN_TRIM_UP	((uint32_t)(1<<4))
#define IOMUXC_GPR_GPR14_ACMP4_CMP_IGEN_TRIM_DN	((uint32_t)(1<<3))
#define IOMUXC_GPR_GPR14_ACMP3_CMP_IGEN_TRIM_DN	((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR14_ACMP2_CMP_IGEN_TRIM_DN	((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR14_ACMP1_CMP_IGEN_TRIM_DN	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR16_CM7_INIT_VTOR(n)	((uint32_t)(((n) & 0x1FFFFFF) << 7))
#define IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL	((uint32_t)(1<<2))
#define IOMUXC_GPR_GPR16_INIT_DTCM_EN		((uint32_t)(1<<1))
#define IOMUXC_GPR_GPR16_INIT_ITCM_EN		((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR18_M7_APC_AC_R0_BOT(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR18_LOCK_M7_APC_AC_R0_BOT	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR19_M7_APC_AC_R0_TOP(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR19_LOCK_M7_APC_AC_R0_TOP	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR20_M7_APC_AC_R1_BOT(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR20_LOCK_M7_APC_AC_R1_BOT	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR21_M7_APC_AC_R1_TOP(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR21_LOCK_M7_APC_AC_R1_TOP	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR22_M7_APC_AC_R2_BOT(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR22_LOCK_M7_APC_AC_R2_BOT	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR23_M7_APC_AC_R2_TOP(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR23_LOCK_M7_APC_AC_R2_TOP	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR24_M7_APC_AC_R3_BOT(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR24_LOCK_M7_APC_AC_R3_BOT	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR25_M7_APC_AC_R3_TOP(n)	((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR25_LOCK_M7_APC_AC_R3_TOP	((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR33_LOCK_OCRAM2_TZ_ADDR(n)	((uint32_t)(((n) & 0x7F) << 17))
#define IOMUXC_GPR_GPR33_LOCK_OCRAM2_TZ_EN	((uint32_t)(1<<16))
#define IOMUXC_GPR_GPR33_OCRAM2_TZ_ADDR(n)	((uint32_t)(((n) & 0x7F) << 1))
#define IOMUXC_GPR_GPR33_OCRAM2_TZ_EN		((uint32_t)(1<<0))
#define IOMUXC_GPR_GPR34_SIP_TEST_MUX_QSPI_SIP_EN ((uint32_t)(1<<8))
#define IOMUXC_GPR_GPR34_SIP_TEST_MUX_BOOT_PIN_SEL(n) ((uint32_t)(((n) & 0xFF) << 0))

// 11.5: page 380
#define IMXRT_IOMUXC_SNVS	(*(IMXRT_REGISTER32_t *)IMXRT_IOMUXC_SNVS_ADDRESS)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP		(IMXRT_IOMUXC_SNVS.offset000)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ		(IMXRT_IOMUXC_SNVS.offset004)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ	(IMXRT_IOMUXC_SNVS.offset008)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE		(IMXRT_IOMUXC_SNVS.offset00C)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B		(IMXRT_IOMUXC_SNVS.offset010)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF		(IMXRT_IOMUXC_SNVS.offset014)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP		(IMXRT_IOMUXC_SNVS.offset018)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ		(IMXRT_IOMUXC_SNVS.offset01C)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ	(IMXRT_IOMUXC_SNVS.offset020)

// 11.6: page 399
#define IMXRT_IOMUXC_SNVS_GPR	(*(IMXRT_REGISTER32_t *)IMXRT_IOMUXC_SNVS_GPR_ADDRESS)
#define IOMUXC_SNVS_GPR_GPR0		(IMXRT_IOMUXC_SNVS_GPR.offset000)
#define IOMUXC_SNVS_GPR_GPR1		(IMXRT_IOMUXC_SNVS_GPR.offset004)
#define IOMUXC_SNVS_GPR_GPR2		(IMXRT_IOMUXC_SNVS_GPR.offset008)
#define IOMUXC_SNVS_GPR_GPR3		(IMXRT_IOMUXC_SNVS_GPR.offset00C)

// 11.7: page 403
#define IMXRT_IOMUXC		(*(IMXRT_REGISTER32_t *)IMXRT_IOMUXC_ADDRESS)
#define IMXRT_IOMUXC_b		(*(IMXRT_REGISTER32_t *)(IMXRT_IOMUXC_ADDRESS+0x400))
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_00	(IMXRT_IOMUXC.offset014)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_01	(IMXRT_IOMUXC.offset018)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_02	(IMXRT_IOMUXC.offset01C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_03	(IMXRT_IOMUXC.offset020)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04	(IMXRT_IOMUXC.offset024)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05	(IMXRT_IOMUXC.offset028)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06	(IMXRT_IOMUXC.offset02C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07	(IMXRT_IOMUXC.offset030)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08	(IMXRT_IOMUXC.offset034)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_09	(IMXRT_IOMUXC.offset038)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_10	(IMXRT_IOMUXC.offset03C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_11	(IMXRT_IOMUXC.offset040)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_12	(IMXRT_IOMUXC.offset044)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_13	(IMXRT_IOMUXC.offset048)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_14	(IMXRT_IOMUXC.offset04C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_15	(IMXRT_IOMUXC.offset050)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_16	(IMXRT_IOMUXC.offset054)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_17	(IMXRT_IOMUXC.offset058)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_18	(IMXRT_IOMUXC.offset05C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_19	(IMXRT_IOMUXC.offset060)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_20	(IMXRT_IOMUXC.offset064)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_21	(IMXRT_IOMUXC.offset068)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_22	(IMXRT_IOMUXC.offset06C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_23	(IMXRT_IOMUXC.offset070)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_24	(IMXRT_IOMUXC.offset074)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_25	(IMXRT_IOMUXC.offset078)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_26	(IMXRT_IOMUXC.offset07C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_27	(IMXRT_IOMUXC.offset080)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_28	(IMXRT_IOMUXC.offset084)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_29	(IMXRT_IOMUXC.offset088)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_30	(IMXRT_IOMUXC.offset08C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31	(IMXRT_IOMUXC.offset090)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32	(IMXRT_IOMUXC.offset094)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_33	(IMXRT_IOMUXC.offset098)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_34	(IMXRT_IOMUXC.offset09C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_35	(IMXRT_IOMUXC.offset0A0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36	(IMXRT_IOMUXC.offset0A4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37	(IMXRT_IOMUXC.offset0A8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_38	(IMXRT_IOMUXC.offset0AC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_39	(IMXRT_IOMUXC.offset0B0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_40	(IMXRT_IOMUXC.offset0B4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_41	(IMXRT_IOMUXC.offset0B8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_00	(IMXRT_IOMUXC.offset0BC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_01	(IMXRT_IOMUXC.offset0C0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02	(IMXRT_IOMUXC.offset0C4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03	(IMXRT_IOMUXC.offset0C8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_04	(IMXRT_IOMUXC.offset0CC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_05	(IMXRT_IOMUXC.offset0D0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_06	(IMXRT_IOMUXC.offset0D4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_07	(IMXRT_IOMUXC.offset0D8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_08	(IMXRT_IOMUXC.offset0DC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_09	(IMXRT_IOMUXC.offset0E0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_10	(IMXRT_IOMUXC.offset0E4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_11	(IMXRT_IOMUXC.offset0E8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12	(IMXRT_IOMUXC.offset0EC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13	(IMXRT_IOMUXC.offset0F0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_14	(IMXRT_IOMUXC.offset0F4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_15	(IMXRT_IOMUXC.offset0F8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00	(IMXRT_IOMUXC.offset0FC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01	(IMXRT_IOMUXC.offset100)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02	(IMXRT_IOMUXC.offset104)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03	(IMXRT_IOMUXC.offset108)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_04	(IMXRT_IOMUXC.offset10C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_05	(IMXRT_IOMUXC.offset110)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06	(IMXRT_IOMUXC.offset114)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07	(IMXRT_IOMUXC.offset118)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08	(IMXRT_IOMUXC.offset11C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09	(IMXRT_IOMUXC.offset120)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10	(IMXRT_IOMUXC.offset124)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11	(IMXRT_IOMUXC.offset128)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_12	(IMXRT_IOMUXC.offset12C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_13	(IMXRT_IOMUXC.offset130)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14	(IMXRT_IOMUXC.offset134)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15	(IMXRT_IOMUXC.offset138)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00	(IMXRT_IOMUXC.offset13C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01	(IMXRT_IOMUXC.offset140)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02	(IMXRT_IOMUXC.offset144)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03	(IMXRT_IOMUXC.offset148)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_04	(IMXRT_IOMUXC.offset14C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_05	(IMXRT_IOMUXC.offset150)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_06	(IMXRT_IOMUXC.offset154)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_07	(IMXRT_IOMUXC.offset158)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_08	(IMXRT_IOMUXC.offset15C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_09	(IMXRT_IOMUXC.offset160)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10	(IMXRT_IOMUXC.offset164)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11	(IMXRT_IOMUXC.offset168)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12	(IMXRT_IOMUXC.offset16C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_13	(IMXRT_IOMUXC.offset170)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_14	(IMXRT_IOMUXC.offset174)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_15	(IMXRT_IOMUXC.offset178)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00	(IMXRT_IOMUXC.offset17C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01	(IMXRT_IOMUXC.offset180)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_02	(IMXRT_IOMUXC.offset184)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_03	(IMXRT_IOMUXC.offset188)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_04	(IMXRT_IOMUXC.offset18C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_05	(IMXRT_IOMUXC.offset190)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_06	(IMXRT_IOMUXC.offset194)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_07	(IMXRT_IOMUXC.offset198)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_08	(IMXRT_IOMUXC.offset19C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_09	(IMXRT_IOMUXC.offset1A0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_10	(IMXRT_IOMUXC.offset1A4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_11	(IMXRT_IOMUXC.offset1A8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_12	(IMXRT_IOMUXC.offset1AC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_13	(IMXRT_IOMUXC.offset1B0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_14	(IMXRT_IOMUXC.offset1B4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_15	(IMXRT_IOMUXC.offset1B8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_00	(IMXRT_IOMUXC.offset1BC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01	(IMXRT_IOMUXC.offset1C0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_02	(IMXRT_IOMUXC.offset1C4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_03	(IMXRT_IOMUXC.offset1C8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04	(IMXRT_IOMUXC.offset1CC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05	(IMXRT_IOMUXC.offset1D0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_00	(IMXRT_IOMUXC.offset1D4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_01	(IMXRT_IOMUXC.offset1D8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_02	(IMXRT_IOMUXC.offset1DC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_03	(IMXRT_IOMUXC.offset1E0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_04	(IMXRT_IOMUXC.offset1E4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_05	(IMXRT_IOMUXC.offset1E8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_06	(IMXRT_IOMUXC.offset1EC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_07	(IMXRT_IOMUXC.offset1F0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_08	(IMXRT_IOMUXC.offset1F4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_09	(IMXRT_IOMUXC.offset1F8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_10	(IMXRT_IOMUXC.offset1FC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_11	(IMXRT_IOMUXC.offset200)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_00	(IMXRT_IOMUXC.offset204)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_01	(IMXRT_IOMUXC.offset208)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_02	(IMXRT_IOMUXC.offset20C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_03	(IMXRT_IOMUXC.offset210)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04	(IMXRT_IOMUXC.offset214)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05	(IMXRT_IOMUXC.offset218)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06	(IMXRT_IOMUXC.offset21C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07	(IMXRT_IOMUXC.offset220)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08	(IMXRT_IOMUXC.offset224)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_09	(IMXRT_IOMUXC.offset228)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_10	(IMXRT_IOMUXC.offset22C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_11	(IMXRT_IOMUXC.offset230)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_12	(IMXRT_IOMUXC.offset234)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_13	(IMXRT_IOMUXC.offset238)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_14	(IMXRT_IOMUXC.offset23C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_15	(IMXRT_IOMUXC.offset240)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_16	(IMXRT_IOMUXC.offset244)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_17	(IMXRT_IOMUXC.offset248)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_18	(IMXRT_IOMUXC.offset24C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_19	(IMXRT_IOMUXC.offset250)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_20	(IMXRT_IOMUXC.offset254)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_21	(IMXRT_IOMUXC.offset258)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_22	(IMXRT_IOMUXC.offset25C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_23	(IMXRT_IOMUXC.offset260)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_24	(IMXRT_IOMUXC.offset264)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_25	(IMXRT_IOMUXC.offset268)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_26	(IMXRT_IOMUXC.offset26C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_27	(IMXRT_IOMUXC.offset270)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_28	(IMXRT_IOMUXC.offset274)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_29	(IMXRT_IOMUXC.offset278)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_30	(IMXRT_IOMUXC.offset27C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31	(IMXRT_IOMUXC.offset280)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32	(IMXRT_IOMUXC.offset284)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_33	(IMXRT_IOMUXC.offset288)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_34	(IMXRT_IOMUXC.offset28C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_35	(IMXRT_IOMUXC.offset290)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36	(IMXRT_IOMUXC.offset294)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37	(IMXRT_IOMUXC.offset298)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_38	(IMXRT_IOMUXC.offset29C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_39	(IMXRT_IOMUXC.offset2A0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_40	(IMXRT_IOMUXC.offset2A4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_41	(IMXRT_IOMUXC.offset2A8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_00	(IMXRT_IOMUXC.offset2AC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_01	(IMXRT_IOMUXC.offset2B0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02	(IMXRT_IOMUXC.offset2B4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03	(IMXRT_IOMUXC.offset2B8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_04	(IMXRT_IOMUXC.offset2BC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_05	(IMXRT_IOMUXC.offset2C0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_06	(IMXRT_IOMUXC.offset2C4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_07	(IMXRT_IOMUXC.offset2C8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_08	(IMXRT_IOMUXC.offset2CC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_09	(IMXRT_IOMUXC.offset2D0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_10	(IMXRT_IOMUXC.offset2D4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_11	(IMXRT_IOMUXC.offset2D8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12	(IMXRT_IOMUXC.offset2DC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13	(IMXRT_IOMUXC.offset2E0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_14	(IMXRT_IOMUXC.offset2E4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_15	(IMXRT_IOMUXC.offset2E8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00	(IMXRT_IOMUXC.offset2EC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01	(IMXRT_IOMUXC.offset2F0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02	(IMXRT_IOMUXC.offset2F4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03	(IMXRT_IOMUXC.offset2F8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_04	(IMXRT_IOMUXC.offset2FC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_05	(IMXRT_IOMUXC.offset300)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06	(IMXRT_IOMUXC.offset304)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07	(IMXRT_IOMUXC.offset308)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08	(IMXRT_IOMUXC.offset30C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09	(IMXRT_IOMUXC.offset310)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10	(IMXRT_IOMUXC.offset314)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11	(IMXRT_IOMUXC.offset318)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_12	(IMXRT_IOMUXC.offset31C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_13	(IMXRT_IOMUXC.offset320)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14	(IMXRT_IOMUXC.offset324)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15	(IMXRT_IOMUXC.offset328)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00	(IMXRT_IOMUXC.offset32C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01	(IMXRT_IOMUXC.offset330)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02	(IMXRT_IOMUXC.offset334)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03	(IMXRT_IOMUXC.offset338)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_04	(IMXRT_IOMUXC.offset33C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_05	(IMXRT_IOMUXC.offset340)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_06	(IMXRT_IOMUXC.offset344)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_07	(IMXRT_IOMUXC.offset348)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_08	(IMXRT_IOMUXC.offset34C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_09	(IMXRT_IOMUXC.offset350)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10	(IMXRT_IOMUXC.offset354)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11	(IMXRT_IOMUXC.offset358)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12	(IMXRT_IOMUXC.offset35C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_13	(IMXRT_IOMUXC.offset360)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_14	(IMXRT_IOMUXC.offset364)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_15	(IMXRT_IOMUXC.offset368)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00	(IMXRT_IOMUXC.offset36C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01	(IMXRT_IOMUXC.offset370)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_02	(IMXRT_IOMUXC.offset374)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_03	(IMXRT_IOMUXC.offset378)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_04	(IMXRT_IOMUXC.offset37C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_05	(IMXRT_IOMUXC.offset380)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_06	(IMXRT_IOMUXC.offset384)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_07	(IMXRT_IOMUXC.offset388)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_08	(IMXRT_IOMUXC.offset38C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_09	(IMXRT_IOMUXC.offset390)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_10	(IMXRT_IOMUXC.offset394)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_11	(IMXRT_IOMUXC.offset398)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_12	(IMXRT_IOMUXC.offset39C)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_13	(IMXRT_IOMUXC.offset3A0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_14	(IMXRT_IOMUXC.offset3A4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_15	(IMXRT_IOMUXC.offset3A8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00	(IMXRT_IOMUXC.offset3AC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_01	(IMXRT_IOMUXC.offset3B0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_02	(IMXRT_IOMUXC.offset3B4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_03	(IMXRT_IOMUXC.offset3B8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_04	(IMXRT_IOMUXC.offset3BC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_05	(IMXRT_IOMUXC.offset3C0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_00	(IMXRT_IOMUXC.offset3C4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_01	(IMXRT_IOMUXC.offset3C8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_02	(IMXRT_IOMUXC.offset3CC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_03	(IMXRT_IOMUXC.offset3D0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_04	(IMXRT_IOMUXC.offset3D4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_05	(IMXRT_IOMUXC.offset3D8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_06	(IMXRT_IOMUXC.offset3DC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_07	(IMXRT_IOMUXC.offset3E0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_08	(IMXRT_IOMUXC.offset3E4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_09	(IMXRT_IOMUXC.offset3E8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_10	(IMXRT_IOMUXC.offset3EC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_11	(IMXRT_IOMUXC.offset3F0)
#define IOMUXC_ANATOP_USB_OTG_ID_SELECT_INPUT	(IMXRT_IOMUXC.offset3F4)
#define IOMUXC_ANATOP_USB_UH1_ID_SELECT_INPUT	(IMXRT_IOMUXC.offset3F8)
#define IOMUXC_CCM_PMIC_READY_SELECT_INPUT	(IMXRT_IOMUXC.offset3FC)
#define IOMUXC_CSI_DATA02_SELECT_INPUT		(IMXRT_IOMUXC_b.offset000)
#define IOMUXC_CSI_DATA03_SELECT_INPUT		(IMXRT_IOMUXC_b.offset004)
#define IOMUXC_CSI_DATA04_SELECT_INPUT		(IMXRT_IOMUXC_b.offset008)
#define IOMUXC_CSI_DATA05_SELECT_INPUT		(IMXRT_IOMUXC_b.offset00C)
#define IOMUXC_CSI_DATA06_SELECT_INPUT		(IMXRT_IOMUXC_b.offset010)
#define IOMUXC_CSI_DATA07_SELECT_INPUT		(IMXRT_IOMUXC_b.offset014)
#define IOMUXC_CSI_DATA08_SELECT_INPUT		(IMXRT_IOMUXC_b.offset018)
#define IOMUXC_CSI_DATA09_SELECT_INPUT		(IMXRT_IOMUXC_b.offset01C)
#define IOMUXC_CSI_HSYNC_SELECT_INPUT		(IMXRT_IOMUXC_b.offset020)
#define IOMUXC_CSI_PIXCLK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset024)
#define IOMUXC_CSI_VSYNC_SELECT_INPUT		(IMXRT_IOMUXC_b.offset028)
#define IOMUXC_ENET_IPG_CLK_RMII_SELECT_INPUT	(IMXRT_IOMUXC_b.offset02C)
#define IOMUXC_ENET_MDIO_SELECT_INPUT		(IMXRT_IOMUXC_b.offset030)
#define IOMUXC_ENET0_RXDATA_SELECT_INPUT	(IMXRT_IOMUXC_b.offset034)
#define IOMUXC_ENET1_RXDATA_SELECT_INPUT	(IMXRT_IOMUXC_b.offset038)
#define IOMUXC_ENET_RXEN_SELECT_INPUT		(IMXRT_IOMUXC_b.offset03C)
#define IOMUXC_ENET_RXERR_SELECT_INPUT		(IMXRT_IOMUXC_b.offset040)
#define IOMUXC_ENET0_TIMER_SELECT_INPUT		(IMXRT_IOMUXC_b.offset044)
#define IOMUXC_ENET_TXCLK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset048)
#define IOMUXC_FLEXCAN1_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset04C)
#define IOMUXC_FLEXCAN2_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset050)
#define IOMUXC_FLEXPWM1_PWMA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset054)
#define IOMUXC_FLEXPWM1_PWMA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset058)
#define IOMUXC_FLEXPWM1_PWMA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset05C)
#define IOMUXC_FLEXPWM1_PWMA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset060)
#define IOMUXC_FLEXPWM1_PWMB3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset064)
#define IOMUXC_FLEXPWM1_PWMB0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset068)
#define IOMUXC_FLEXPWM1_PWMB1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset06C)
#define IOMUXC_FLEXPWM1_PWMB2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset070)
#define IOMUXC_FLEXPWM2_PWMA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset074)
#define IOMUXC_FLEXPWM2_PWMA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset078)
#define IOMUXC_FLEXPWM2_PWMA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset07C)
#define IOMUXC_FLEXPWM2_PWMA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset080)
#define IOMUXC_FLEXPWM2_PWMB3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset084)
#define IOMUXC_FLEXPWM2_PWMB0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset088)
#define IOMUXC_FLEXPWM2_PWMB1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset09C)
#define IOMUXC_FLEXPWM2_PWMB2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset090)
#define IOMUXC_FLEXPWM4_PWMA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset094)
#define IOMUXC_FLEXPWM4_PWMA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset098)
#define IOMUXC_FLEXPWM4_PWMA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset09C)
#define IOMUXC_FLEXPWM4_PWMA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0A0)
#define IOMUXC_FLEXSPIA_DQS_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0A4)
#define IOMUXC_FLEXSPIA_DATA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0A8)
#define IOMUXC_FLEXSPIA_DATA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0AC)
#define IOMUXC_FLEXSPIA_DATA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0B0)
#define IOMUXC_FLEXSPIA_DATA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0B4)
#define IOMUXC_FLEXSPIB_DATA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0B8)
#define IOMUXC_FLEXSPIB_DATA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0BC)
#define IOMUXC_FLEXSPIB_DATA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0C0)
#define IOMUXC_FLEXSPIB_DATA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0C4)
#define IOMUXC_FLEXSPIA_SCK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset0C8)
#define IOMUXC_LPI2C1_SCL_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0CC)
#define IOMUXC_LPI2C1_SDA_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0D0)
#define IOMUXC_LPI2C2_SCL_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0D4)
#define IOMUXC_LPI2C2_SDA_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0D8)
#define IOMUXC_LPI2C3_SCL_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0DC)
#define IOMUXC_LPI2C3_SDA_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0E0)
#define IOMUXC_LPI2C4_SCL_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0E4)
#define IOMUXC_LPI2C4_SDA_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0E8)
#define IOMUXC_LPSPI1_PCS0_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0EC)
#define IOMUXC_LPSPI1_SCK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0F0)
#define IOMUXC_LPSPI1_SDI_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0F4)
#define IOMUXC_LPSPI1_SDO_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0F8)
#define IOMUXC_LPSPI2_PCS0_SELECT_INPUT		(IMXRT_IOMUXC_b.offset0FC)
#define IOMUXC_LPSPI2_SCK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset100)
#define IOMUXC_LPSPI2_SDI_SELECT_INPUT		(IMXRT_IOMUXC_b.offset104)
#define IOMUXC_LPSPI2_SDO_SELECT_INPUT		(IMXRT_IOMUXC_b.offset108)
#define IOMUXC_LPSPI3_PCS0_SELECT_INPUT		(IMXRT_IOMUXC_b.offset10C)
#define IOMUXC_LPSPI3_SCK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset110)
#define IOMUXC_LPSPI3_SDI_SELECT_INPUT		(IMXRT_IOMUXC_b.offset114)
#define IOMUXC_LPSPI3_SDO_SELECT_INPUT		(IMXRT_IOMUXC_b.offset118)
#define IOMUXC_LPSPI4_PCS0_SELECT_INPUT		(IMXRT_IOMUXC_b.offset11C)
#define IOMUXC_LPSPI4_SCK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset120)
#define IOMUXC_LPSPI4_SDI_SELECT_INPUT		(IMXRT_IOMUXC_b.offset124)
#define IOMUXC_LPSPI4_SDO_SELECT_INPUT		(IMXRT_IOMUXC_b.offset128)
#define IOMUXC_LPUART2_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset12C)
#define IOMUXC_LPUART2_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset130)
#define IOMUXC_LPUART3_CTS_B_SELECT_INPUT	(IMXRT_IOMUXC_b.offset134)
#define IOMUXC_LPUART3_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset138)
#define IOMUXC_LPUART3_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset13C)
#define IOMUXC_LPUART4_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset140)
#define IOMUXC_LPUART4_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset144)
#define IOMUXC_LPUART5_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset148)
#define IOMUXC_LPUART5_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset14C)
#define IOMUXC_LPUART6_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset150)
#define IOMUXC_LPUART6_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset154)
#define IOMUXC_LPUART7_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset158)
#define IOMUXC_LPUART7_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset15C)
#define IOMUXC_LPUART8_RX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset160)
#define IOMUXC_LPUART8_TX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset164)
#define IOMUXC_NMI_GLUE_NMI_SELECT_INPUT	(IMXRT_IOMUXC_b.offset168)
#define IOMUXC_QTIMER2_TIMER0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset16C)
#define IOMUXC_QTIMER2_TIMER1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset170)
#define IOMUXC_QTIMER2_TIMER2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset174)
#define IOMUXC_QTIMER2_TIMER3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset178)
#define IOMUXC_QTIMER3_TIMER0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset17C)
#define IOMUXC_QTIMER3_TIMER1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset180)
#define IOMUXC_QTIMER3_TIMER2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset184)
#define IOMUXC_QTIMER3_TIMER3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset188)
#define IOMUXC_SAI1_MCLK2_SELECT_INPUT		(IMXRT_IOMUXC_b.offset18C)
#define IOMUXC_SAI1_RX_BCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset190)
#define IOMUXC_SAI1_RX_DATA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset194)
#define IOMUXC_SAI1_RX_DATA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset198)
#define IOMUXC_SAI1_RX_DATA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset19C)
#define IOMUXC_SAI1_RX_DATA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1A0)
#define IOMUXC_SAI1_RX_SYNC_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1A4)
#define IOMUXC_SAI1_TX_BCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1A8)
#define IOMUXC_SAI1_TX_SYNC_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1AC)
#define IOMUXC_SAI2_MCLK2_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1B0)
#define IOMUXC_SAI2_RX_BCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1B4)
#define IOMUXC_SAI2_RX_DATA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1B8)
#define IOMUXC_SAI2_RX_SYNC_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1BC)
#define IOMUXC_SAI2_TX_BCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1C0)
#define IOMUXC_SAI2_TX_SYNC_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1C4)
#define IOMUXC_SPDIF_IN_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1C8)
#define IOMUXC_USB_OTG2_OC_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1CC)
#define IOMUXC_USB_OTG1_OC_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1D0)
#define IOMUXC_USDHC1_CD_B_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1D4)
#define IOMUXC_USDHC1_WP_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1D8)
#define IOMUXC_USDHC2_CLK_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1DC)
#define IOMUXC_USDHC2_CD_B_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1E0)
#define IOMUXC_USDHC2_CMD_SELECT_INPUT		(IMXRT_IOMUXC_b.offset1E4)
#define IOMUXC_USDHC2_DATA0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1E8)
#define IOMUXC_USDHC2_DATA1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1EC)
#define IOMUXC_USDHC2_DATA2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1F0)
#define IOMUXC_USDHC2_DATA3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1F4)
#define IOMUXC_USDHC2_DATA4_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1F8)
#define IOMUXC_USDHC2_DATA5_SELECT_INPUT	(IMXRT_IOMUXC_b.offset1FC)
#define IOMUXC_USDHC2_DATA6_SELECT_INPUT	(IMXRT_IOMUXC_b.offset200)
#define IOMUXC_USDHC2_DATA7_SELECT_INPUT	(IMXRT_IOMUXC_b.offset204)
#define IOMUXC_USDHC2_WP_SELECT_INPUT		(IMXRT_IOMUXC_b.offset208)
#define IOMUXC_XBAR1_IN02_SELECT_INPUT		(IMXRT_IOMUXC_b.offset20C)
#define IOMUXC_XBAR1_IN03_SELECT_INPUT		(IMXRT_IOMUXC_b.offset210)
#define IOMUXC_XBAR1_IN04_SELECT_INPUT		(IMXRT_IOMUXC_b.offset214)
#define IOMUXC_XBAR1_IN05_SELECT_INPUT		(IMXRT_IOMUXC_b.offset218)
#define IOMUXC_XBAR1_IN06_SELECT_INPUT		(IMXRT_IOMUXC_b.offset21C)
#define IOMUXC_XBAR1_IN07_SELECT_INPUT		(IMXRT_IOMUXC_b.offset220)
#define IOMUXC_XBAR1_IN08_SELECT_INPUT		(IMXRT_IOMUXC_b.offset224)
#define IOMUXC_XBAR1_IN09_SELECT_INPUT		(IMXRT_IOMUXC_b.offset228)
#define IOMUXC_XBAR1_IN17_SELECT_INPUT		(IMXRT_IOMUXC_b.offset22C)
#define IOMUXC_XBAR1_IN18_SELECT_INPUT		(IMXRT_IOMUXC_b.offset230)
#define IOMUXC_XBAR1_IN20_SELECT_INPUT		(IMXRT_IOMUXC_b.offset234)
#define IOMUXC_XBAR1_IN22_SELECT_INPUT		(IMXRT_IOMUXC_b.offset238)
#define IOMUXC_XBAR1_IN23_SELECT_INPUT		(IMXRT_IOMUXC_b.offset23C)
#define IOMUXC_XBAR1_IN24_SELECT_INPUT		(IMXRT_IOMUXC_b.offset240)
#define IOMUXC_XBAR1_IN14_SELECT_INPUT		(IMXRT_IOMUXC_b.offset244)
#define IOMUXC_XBAR1_IN15_SELECT_INPUT		(IMXRT_IOMUXC_b.offset248)
#define IOMUXC_XBAR1_IN16_SELECT_INPUT		(IMXRT_IOMUXC_b.offset24C)
#define IOMUXC_XBAR1_IN25_SELECT_INPUT		(IMXRT_IOMUXC_b.offset250)
#define IOMUXC_XBAR1_IN19_SELECT_INPUT		(IMXRT_IOMUXC_b.offset254)
#define IOMUXC_XBAR1_IN21_SELECT_INPUT		(IMXRT_IOMUXC_b.offset258)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_00	(IMXRT_IOMUXC_b.offset25C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_01	(IMXRT_IOMUXC_b.offset260)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_02	(IMXRT_IOMUXC_b.offset264)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_03	(IMXRT_IOMUXC_b.offset268)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_04	(IMXRT_IOMUXC_b.offset26C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_05	(IMXRT_IOMUXC_b.offset270)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_06	(IMXRT_IOMUXC_b.offset274)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_07	(IMXRT_IOMUXC_b.offset278)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_08	(IMXRT_IOMUXC_b.offset27C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_09	(IMXRT_IOMUXC_b.offset280)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_10	(IMXRT_IOMUXC_b.offset284)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_11	(IMXRT_IOMUXC_b.offset288)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_12	(IMXRT_IOMUXC_b.offset28C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B0_13	(IMXRT_IOMUXC_b.offset290)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_00	(IMXRT_IOMUXC_b.offset294)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_01	(IMXRT_IOMUXC_b.offset298)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_02	(IMXRT_IOMUXC_b.offset29C)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_03	(IMXRT_IOMUXC_b.offset2A0)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_04	(IMXRT_IOMUXC_b.offset2A4)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_05	(IMXRT_IOMUXC_b.offset2A8)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_06	(IMXRT_IOMUXC_b.offset2AC)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SPI_B1_07	(IMXRT_IOMUXC_b.offset2B0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_00	(IMXRT_IOMUXC_b.offset2B4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_01	(IMXRT_IOMUXC_b.offset2B8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_02	(IMXRT_IOMUXC_b.offset2BC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_03	(IMXRT_IOMUXC_b.offset2C0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_04	(IMXRT_IOMUXC_b.offset2C4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_05	(IMXRT_IOMUXC_b.offset2C8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_06	(IMXRT_IOMUXC_b.offset2CC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_07	(IMXRT_IOMUXC_b.offset2D0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_08	(IMXRT_IOMUXC_b.offset2D4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_09	(IMXRT_IOMUXC_b.offset2D8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_10	(IMXRT_IOMUXC_b.offset2DC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_11	(IMXRT_IOMUXC_b.offset2E0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_12	(IMXRT_IOMUXC_b.offset2E4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B0_13	(IMXRT_IOMUXC_b.offset2E8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_00	(IMXRT_IOMUXC_b.offset2EC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_01	(IMXRT_IOMUXC_b.offset2F0)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_02	(IMXRT_IOMUXC_b.offset2F4)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_03	(IMXRT_IOMUXC_b.offset2F8)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_04	(IMXRT_IOMUXC_b.offset2FC)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_05	(IMXRT_IOMUXC_b.offset300)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_06	(IMXRT_IOMUXC_b.offset304)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SPI_B1_07	(IMXRT_IOMUXC_b.offset308)
#define IOMUXC_ENET2_IPG_CLK_RMII_SELECT_INPUT	(IMXRT_IOMUXC_b.offset30C)
#define IOMUXC_ENET2_IPP_IND_MAC0_MDIO_SELECT_INPUT	(IMXRT_IOMUXC_b.offset310)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_0	(IMXRT_IOMUXC_b.offset314)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_1	(IMXRT_IOMUXC_b.offset318)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXEN_SELECT_INPUT	(IMXRT_IOMUXC_b.offset31C)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXERR_SELECT_INPUT	(IMXRT_IOMUXC_b.offset320)
#define IOMUXC_ENET2_IPP_IND_MAC0_TIMER_SELECT_INPUT_0	(IMXRT_IOMUXC_b.offset324)
#define IOMUXC_ENET2_IPP_IND_MAC0_TXCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset328)
#define IOMUXC_FLEXSPI2_IPP_IND_DQS_FA_SELECT_INPUT	(IMXRT_IOMUXC_b.offset32C)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset330)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset334)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset338)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset33C)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT0_SELECT_INPUT	(IMXRT_IOMUXC_b.offset340)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT1_SELECT_INPUT	(IMXRT_IOMUXC_b.offset344)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT2_SELECT_INPUT	(IMXRT_IOMUXC_b.offset348)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT3_SELECT_INPUT	(IMXRT_IOMUXC_b.offset34C)
#define IOMUXC_FLEXSPI2_IPP_IND_SCK_FA_SELECT_INPUT	(IMXRT_IOMUXC_b.offset350)
#define IOMUXC_FLEXSPI2_IPP_IND_SCK_FB_SELECT_INPUT	(IMXRT_IOMUXC_b.offset354)
#define IOMUXC_GPT1_IPP_IND_CAPIN1_SELECT_INPUT		(IMXRT_IOMUXC_b.offset358)
#define IOMUXC_GPT1_IPP_IND_CAPIN2_SELECT_INPUT		(IMXRT_IOMUXC_b.offset35C)
#define IOMUXC_GPT1_IPP_IND_CLKIN_SELECT_INPUT		(IMXRT_IOMUXC_b.offset360)
#define IOMUXC_GPT2_IPP_IND_CAPIN1_SELECT_INPUT		(IMXRT_IOMUXC_b.offset364)
#define IOMUXC_GPT2_IPP_IND_CAPIN2_SELECT_INPUT		(IMXRT_IOMUXC_b.offset368)
#define IOMUXC_GPT2_IPP_IND_CLKIN_SELECT_INPUT		(IMXRT_IOMUXC_b.offset36C)
#define IOMUXC_SAI3_IPG_CLK_SAI_MCLK_SELECT_INPUT_2	(IMXRT_IOMUXC_b.offset370)
#define IOMUXC_SAI3_IPP_IND_SAI_RXBCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset374)
#define IOMUXC_SAI3_IPP_IND_SAI_RXDATA_SELECT_INPUT_0	(IMXRT_IOMUXC_b.offset378)
#define IOMUXC_SAI3_IPP_IND_SAI_RXSYNC_SELECT_INPUT	(IMXRT_IOMUXC_b.offset37C)
#define IOMUXC_SAI3_IPP_IND_SAI_TXBCLK_SELECT_INPUT	(IMXRT_IOMUXC_b.offset380)
#define IOMUXC_SAI3_IPP_IND_SAI_TXSYNC_SELECT_INPUT	(IMXRT_IOMUXC_b.offset384)
#define IOMUXC_SEMC_I_IPP_IND_DQS4_SELECT_INPUT		(IMXRT_IOMUXC_b.offset388)
#define IOMUXC_CANFD_IPP_IND_CANRX_SELECT_INPUT		(IMXRT_IOMUXC_b.offset38C)
#define IOMUXC_PAD_SRE					((uint32_t)(1<<0))
#define IOMUXC_PAD_DSE(n)				((uint32_t)(((n) & 0x07) << 3))
#define IOMUXC_PAD_SPEED(n)				((uint32_t)(((n) & 0x03) << 6))
#define IOMUXC_PAD_ODE					((uint32_t)(1<<11))
#define IOMUXC_PAD_PKE					((uint32_t)(1<<12))
#define IOMUXC_PAD_PUE					((uint32_t)(1<<13))
#define IOMUXC_PAD_PUS(n)				((uint32_t)(((n) & 0x03) << 14))
#define IOMUXC_PAD_HYS					((uint32_t)(1<<16))

// 46.7: page 2732
#define IMXRT_KPP		(*(IMXRT_REGISTER16_t *)IMXRT_KPP_ADDRESS)
#define KPP_KPCR			(IMXRT_KPP.offset000)
#define KPP_KPSR			(IMXRT_KPP.offset002)
#define KPP_KDDR			(IMXRT_KPP.offset004)
#define KPP_KPDR			(IMXRT_KPP.offset006)

// 35.7: page 1860
#define IMXRT_LCDIF		(*(IMXRT_REGISTER32_t *)IMXRT_LCDIF_ADDRESS)
#define LCDIF_CTRL			(IMXRT_LCDIF.offset000)
#define LCDIF_CTRL_SET			(IMXRT_LCDIF.offset004)
#define LCDIF_CTRL_CLR			(IMXRT_LCDIF.offset008)
#define LCDIF_CTRL_TOG			(IMXRT_LCDIF.offset00C)
#define LCDIF_CTRL1			(IMXRT_LCDIF.offset010)
#define LCDIF_CTRL1_SET			(IMXRT_LCDIF.offset014)
#define LCDIF_CTRL1_CLR			(IMXRT_LCDIF.offset018)
#define LCDIF_CTRL1_TOG			(IMXRT_LCDIF.offset01C)
#define LCDIF_CTRL2			(IMXRT_LCDIF.offset020)
#define LCDIF_CTRL2_SET			(IMXRT_LCDIF.offset024)
#define LCDIF_CTRL2_CLR			(IMXRT_LCDIF.offset028)
#define LCDIF_CTRL2_TOG			(IMXRT_LCDIF.offset02C)
#define LCDIF_TRANSFER_COUNT		(IMXRT_LCDIF.offset030)
#define LCDIF_CUR_BUF			(IMXRT_LCDIF.offset040)
#define LCDIF_NEXT_BUF			(IMXRT_LCDIF.offset050)
#define LCDIF_VDCTRL0			(IMXRT_LCDIF.offset070)
#define LCDIF_VDCTRL0_SET		(IMXRT_LCDIF.offset074)
#define LCDIF_VDCTRL0_CLR		(IMXRT_LCDIF.offset078)
#define LCDIF_VDCTRL0_TOG		(IMXRT_LCDIF.offset07C)
#define LCDIF_VDCTRL1			(IMXRT_LCDIF.offset080)
#define LCDIF_VDCTRL2			(IMXRT_LCDIF.offset090)
#define LCDIF_VDCTRL3			(IMXRT_LCDIF.offset0A0)
#define LCDIF_VDCTRL4			(IMXRT_LCDIF.offset0B0)
#define LCDIF_BM_ERROR_STAT		(IMXRT_LCDIF.offset190)
#define LCDIF_CRC_STAT			(IMXRT_LCDIF.offset1A0)
#define LCDIF_STAT			(IMXRT_LCDIF.offset1B0)
#define LCDIF_THRES			(IMXRT_LCDIF.offset200)
#define LCDIF_AS_CTRL			(IMXRT_LCDIF.offset210)
#define LCDIF_AS_BUF			(IMXRT_LCDIF.offset220)
#define LCDIF_AS_NEXT_BUF		(IMXRT_LCDIF.offset230)
#define LCDIF_AS_CLRKEYLOW		(IMXRT_LCDIF.offset240)
#define LCDIF_AS_CLRKEYHIGH		(IMXRT_LCDIF.offset250)
#define LCDIF_PIGEONCTRL0		(IMXRT_LCDIF.offset380)
#define LCDIF_PIGEONCTRL0_SET		(IMXRT_LCDIF.offset384)
#define LCDIF_PIGEONCTRL0_CLR		(IMXRT_LCDIF.offset388)
#define LCDIF_PIGEONCTRL0_TOG		(IMXRT_LCDIF.offset38C)
#define LCDIF_PIGEONCTRL1		(IMXRT_LCDIF.offset390)
#define LCDIF_PIGEONCTRL1_SET		(IMXRT_LCDIF.offset394)
#define LCDIF_PIGEONCTRL1_CLR		(IMXRT_LCDIF.offset398)
#define LCDIF_PIGEONCTRL1_TOG		(IMXRT_LCDIF.offset39C)
#define LCDIF_PIGEONCTRL2		(IMXRT_LCDIF.offset3A0)
#define LCDIF_PIGEONCTRL2_SET		(IMXRT_LCDIF.offset3A4)
#define LCDIF_PIGEONCTRL2_CLR		(IMXRT_LCDIF.offset3A8)
#define LCDIF_PIGEONCTRL2_TOG		(IMXRT_LCDIF.offset3AC)
#define IMXRT_LCDIF_b		(*(IMXRT_REGISTER32_t *)(IMXRT_LCDIF_ADDRESS+0x800))
#define LCDIF_PIGEON_0_0		(IMXRT_LCDIF_b.offset000)
#define LCDIF_PIGEON_0_1		(IMXRT_LCDIF_b.offset010)
#define LCDIF_PIGEON_0_2		(IMXRT_LCDIF_b.offset020)
#define LCDIF_PIGEON_1_0		(IMXRT_LCDIF_b.offset040)
#define LCDIF_PIGEON_1_1		(IMXRT_LCDIF_b.offset050)
#define LCDIF_PIGEON_1_2		(IMXRT_LCDIF_b.offset060)
#define LCDIF_PIGEON_2_0		(IMXRT_LCDIF_b.offset080)
#define LCDIF_PIGEON_2_1		(IMXRT_LCDIF_b.offset090)
#define LCDIF_PIGEON_2_2		(IMXRT_LCDIF_b.offset0A0)
#define LCDIF_PIGEON_3_0		(IMXRT_LCDIF_b.offset0C0)
#define LCDIF_PIGEON_3_1		(IMXRT_LCDIF_b.offset0D0)
#define LCDIF_PIGEON_3_2		(IMXRT_LCDIF_b.offset0E0)
#define LCDIF_PIGEON_4_0		(IMXRT_LCDIF_b.offset100)
#define LCDIF_PIGEON_4_1		(IMXRT_LCDIF_b.offset110)
#define LCDIF_PIGEON_4_2		(IMXRT_LCDIF_b.offset120)
#define LCDIF_PIGEON_5_0		(IMXRT_LCDIF_b.offset140)
#define LCDIF_PIGEON_5_1		(IMXRT_LCDIF_b.offset150)
#define LCDIF_PIGEON_5_2		(IMXRT_LCDIF_b.offset160)
#define LCDIF_PIGEON_6_0		(IMXRT_LCDIF_b.offset180)
#define LCDIF_PIGEON_6_1		(IMXRT_LCDIF_b.offset190)
#define LCDIF_PIGEON_6_2		(IMXRT_LCDIF_b.offset1A0)
#define LCDIF_PIGEON_7_0		(IMXRT_LCDIF_b.offset1C0)
#define LCDIF_PIGEON_7_1		(IMXRT_LCDIF_b.offset1D0)
#define LCDIF_PIGEON_7_2		(IMXRT_LCDIF_b.offset1E0)
#define LCDIF_PIGEON_8_0		(IMXRT_LCDIF_b.offset200)
#define LCDIF_PIGEON_8_1		(IMXRT_LCDIF_b.offset210)
#define LCDIF_PIGEON_8_2		(IMXRT_LCDIF_b.offset220)
#define LCDIF_PIGEON_9_0		(IMXRT_LCDIF_b.offset240)
#define LCDIF_PIGEON_9_1		(IMXRT_LCDIF_b.offset250)
#define LCDIF_PIGEON_9_2		(IMXRT_LCDIF_b.offset260)
#define LCDIF_PIGEON_10_0		(IMXRT_LCDIF_b.offset280)
#define LCDIF_PIGEON_10_1		(IMXRT_LCDIF_b.offset290)
#define LCDIF_PIGEON_10_2		(IMXRT_LCDIF_b.offset2A0)
#define LCDIF_PIGEON_11_0		(IMXRT_LCDIF_b.offset2C0)
#define LCDIF_PIGEON_11_1		(IMXRT_LCDIF_b.offset2D0)
#define LCDIF_PIGEON_11_2		(IMXRT_LCDIF_b.offset2E0)

// 47.4.1.1: page 2758
typedef struct {
	const uint32_t VERID;
	const uint32_t PARAM;
	const uint32_t unused1;
	const uint32_t unused2;
	volatile uint32_t MCR;			// 010
	volatile uint32_t MSR;			// 014
	volatile uint32_t MIER;			// 018
	volatile uint32_t MDER;			// 01C
	volatile uint32_t MCFGR0;		// 020
	volatile uint32_t MCFGR1;		// 024
	volatile uint32_t MCFGR2;		// 028
	volatile uint32_t MCFGR3;		// 02C
	volatile uint32_t unused3[4];
	volatile uint32_t MDMR;			// 040
	volatile uint32_t unused4;
	volatile uint32_t MCCR0;		// 048
	volatile uint32_t unused5;
	volatile uint32_t MCCR1;		// 050
	volatile uint32_t unused6;
	volatile uint32_t MFCR;			// 058
	volatile uint32_t MFSR;			// 05C
	volatile uint32_t MTDR;			// 060
	volatile uint32_t unused7[3];
	volatile uint32_t MRDR;			// 070
	volatile uint32_t unused8[39];
	volatile uint32_t SCR;			// 110
	volatile uint32_t SSR;			// 114
	volatile uint32_t SIER;			// 118
	volatile uint32_t SDER;			// 11C
	volatile uint32_t unused9;
	volatile uint32_t SCFGR1;		// 124
	volatile uint32_t SCFGR2;		// 128
	volatile uint32_t unused10[5];
	volatile uint32_t SAMR;			// 140
	volatile uint32_t unused11[3];
	volatile uint32_t SASR;			// 150
	volatile uint32_t unused12[3];
	volatile uint32_t STAR;			// 154
	volatile uint32_t unused13[3];
	volatile uint32_t STDR;			// 160
	volatile uint32_t unused14[3];
	volatile uint32_t SRDR;			// 170
} IMXRT_LPI2C_t;
#define IMXRT_LPI2C1		(*(IMXRT_LPI2C_t *)IMXRT_LPI2C1_ADDRESS)
#define LPI2C1_VERID			(IMXRT_LPI2C1.VERID)
#define LPI2C1_PARAM			(IMXRT_LPI2C1.PARAM)
#define LPI2C1_MCR			(IMXRT_LPI2C1.MCR)
#define LPI2C1_MSR			(IMXRT_LPI2C1.MSR)
#define LPI2C1_MIER			(IMXRT_LPI2C1.MIER)
#define LPI2C1_MDER			(IMXRT_LPI2C1.MDER)
#define LPI2C1_MCFGR0			(IMXRT_LPI2C1.MCFGR0)
#define LPI2C1_MCFGR1			(IMXRT_LPI2C1.MCFGR1)
#define LPI2C1_MCFGR2			(IMXRT_LPI2C1.MCFGR2)
#define LPI2C1_MCFGR3			(IMXRT_LPI2C1.MCFGR3)
#define LPI2C1_MDMR			(IMXRT_LPI2C1.MDMR)
#define LPI2C1_MCCR0			(IMXRT_LPI2C1.MCCR0)
#define LPI2C1_MCCR1			(IMXRT_LPI2C1.MCCR1)
#define LPI2C1_MFCR			(IMXRT_LPI2C1.MFCR)
#define LPI2C1_MFSR			(IMXRT_LPI2C1.MFSR)
#define LPI2C1_MTDR			(IMXRT_LPI2C1.MTDR)
#define LPI2C1_MRDR			(IMXRT_LPI2C1.MRDR)
#define LPI2C1_SCR			(IMXRT_LPI2C1.SCR)
#define LPI2C1_SSR			(IMXRT_LPI2C1.SSR)
#define LPI2C1_SIER			(IMXRT_LPI2C1.SIER)
#define LPI2C1_SDER			(IMXRT_LPI2C1.SDER)
#define LPI2C1_SCFGR1			(IMXRT_LPI2C1.SCFGR1)
#define LPI2C1_SCFGR2			(IMXRT_LPI2C1.SCFGR2)
#define LPI2C1_SAMR			(IMXRT_LPI2C1.SAMR)
#define LPI2C1_SASR			(IMXRT_LPI2C1.SASR)
#define LPI2C1_STAR			(IMXRT_LPI2C1.STAR)
#define LPI2C1_STDR			(IMXRT_LPI2C1.STDR)
#define LPI2C1_SRDR			(IMXRT_LPI2C1.SRDR)
#define IMXRT_LPI2C2		(*(IMXRT_LPI2C_t *)IMXRT_LPI2C2_ADDRESS)
#define LPI2C2_VERID			(IMXRT_LPI2C2.VERID)
#define LPI2C2_PARAM			(IMXRT_LPI2C2.PARAM)
#define LPI2C2_MCR			(IMXRT_LPI2C2.MCR)
#define LPI2C2_MSR			(IMXRT_LPI2C2.MSR)
#define LPI2C2_MIER			(IMXRT_LPI2C2.MIER)
#define LPI2C2_MDER			(IMXRT_LPI2C2.MDER)
#define LPI2C2_MCFGR0			(IMXRT_LPI2C2.MCFGR0)
#define LPI2C2_MCFGR1			(IMXRT_LPI2C2.MCFGR1)
#define LPI2C2_MCFGR2			(IMXRT_LPI2C2.MCFGR2)
#define LPI2C2_MCFGR3			(IMXRT_LPI2C2.MCFGR3)
#define LPI2C2_MDMR			(IMXRT_LPI2C2.MDMR)
#define LPI2C2_MCCR0			(IMXRT_LPI2C2.MCCR0)
#define LPI2C2_MCCR1			(IMXRT_LPI2C2.MCCR1)
#define LPI2C2_MFCR			(IMXRT_LPI2C2.MFCR)
#define LPI2C2_MFSR			(IMXRT_LPI2C2.MFSR)
#define LPI2C2_MTDR			(IMXRT_LPI2C2.MTDR)
#define LPI2C2_MRDR			(IMXRT_LPI2C2.MRDR)
#define LPI2C2_SCR			(IMXRT_LPI2C2.SCR)
#define LPI2C2_SSR			(IMXRT_LPI2C2.SSR)
#define LPI2C2_SIER			(IMXRT_LPI2C2.SIER)
#define LPI2C2_SDER			(IMXRT_LPI2C2.SDER)
#define LPI2C2_SCFGR1			(IMXRT_LPI2C2.SCFGR1)
#define LPI2C2_SCFGR2			(IMXRT_LPI2C2.SCFGR2)
#define LPI2C2_SAMR			(IMXRT_LPI2C2.SAMR)
#define LPI2C2_SASR			(IMXRT_LPI2C2.SASR)
#define LPI2C2_STAR			(IMXRT_LPI2C2.STAR)
#define LPI2C2_STDR			(IMXRT_LPI2C2.STDR)
#define LPI2C2_SRDR			(IMXRT_LPI2C2.SRDR)
#define IMXRT_LPI2C3		(*(IMXRT_LPI2C_t *)IMXRT_LPI2C3_ADDRESS)
#define LPI2C3_VERID			(IMXRT_LPI2C3.VERID)
#define LPI2C3_PARAM			(IMXRT_LPI2C3.PARAM)
#define LPI2C3_MCR			(IMXRT_LPI2C3.MCR)
#define LPI2C3_MSR			(IMXRT_LPI2C3.MSR)
#define LPI2C3_MIER			(IMXRT_LPI2C3.MIER)
#define LPI2C3_MDER			(IMXRT_LPI2C3.MDER)
#define LPI2C3_MCFGR0			(IMXRT_LPI2C3.MCFGR0)
#define LPI2C3_MCFGR1			(IMXRT_LPI2C3.MCFGR1)
#define LPI2C3_MCFGR2			(IMXRT_LPI2C3.MCFGR2)
#define LPI2C3_MCFGR3			(IMXRT_LPI2C3.MCFGR3)
#define LPI2C3_MDMR			(IMXRT_LPI2C3.MDMR)
#define LPI2C3_MCCR0			(IMXRT_LPI2C3.MCCR0)
#define LPI2C3_MCCR1			(IMXRT_LPI2C3.MCCR1)
#define LPI2C3_MFCR			(IMXRT_LPI2C3.MFCR)
#define LPI2C3_MFSR			(IMXRT_LPI2C3.MFSR)
#define LPI2C3_MTDR			(IMXRT_LPI2C3.MTDR)
#define LPI2C3_MRDR			(IMXRT_LPI2C3.MRDR)
#define LPI2C3_SCR			(IMXRT_LPI2C3.SCR)
#define LPI2C3_SSR			(IMXRT_LPI2C3.SSR)
#define LPI2C3_SIER			(IMXRT_LPI2C3.SIER)
#define LPI2C3_SDER			(IMXRT_LPI2C3.SDER)
#define LPI2C3_SCFGR1			(IMXRT_LPI2C3.SCFGR1)
#define LPI2C3_SCFGR2			(IMXRT_LPI2C3.SCFGR2)
#define LPI2C3_SAMR			(IMXRT_LPI2C3.SAMR)
#define LPI2C3_SASR			(IMXRT_LPI2C3.SASR)
#define LPI2C3_STAR			(IMXRT_LPI2C3.STAR)
#define LPI2C3_STDR			(IMXRT_LPI2C3.STDR)
#define LPI2C3_SRDR			(IMXRT_LPI2C3.SRDR)
#define IMXRT_LPI2C4		(*(IMXRT_LPI2C_t *)IMXRT_LPI2C4_ADDRESS)
#define LPI2C4_VERID			(IMXRT_LPI2C4.VERID)
#define LPI2C4_PARAM			(IMXRT_LPI2C4.PARAM)
#define LPI2C4_MCR			(IMXRT_LPI2C4.MCR)
#define LPI2C4_MSR			(IMXRT_LPI2C4.MSR)
#define LPI2C4_MIER			(IMXRT_LPI2C4.MIER)
#define LPI2C4_MDER			(IMXRT_LPI2C4.MDER)
#define LPI2C4_MCFGR0			(IMXRT_LPI2C4.MCFGR0)
#define LPI2C4_MCFGR1			(IMXRT_LPI2C4.MCFGR1)
#define LPI2C4_MCFGR2			(IMXRT_LPI2C4.MCFGR2)
#define LPI2C4_MCFGR3			(IMXRT_LPI2C4.MCFGR3)
#define LPI2C4_MDMR			(IMXRT_LPI2C4.MDMR)
#define LPI2C4_MCCR0			(IMXRT_LPI2C4.MCCR0)
#define LPI2C4_MCCR1			(IMXRT_LPI2C4.MCCR1)
#define LPI2C4_MFCR			(IMXRT_LPI2C4.MFCR)
#define LPI2C4_MFSR			(IMXRT_LPI2C4.MFSR)
#define LPI2C4_MTDR			(IMXRT_LPI2C4.MTDR)
#define LPI2C4_MRDR			(IMXRT_LPI2C4.MRDR)
#define LPI2C4_SCR			(IMXRT_LPI2C4.SCR)
#define LPI2C4_SSR			(IMXRT_LPI2C4.SSR)
#define LPI2C4_SIER			(IMXRT_LPI2C4.SIER)
#define LPI2C4_SDER			(IMXRT_LPI2C4.SDER)
#define LPI2C4_SCFGR1			(IMXRT_LPI2C4.SCFGR1)
#define LPI2C4_SCFGR2			(IMXRT_LPI2C4.SCFGR2)
#define LPI2C4_SAMR			(IMXRT_LPI2C4.SAMR)
#define LPI2C4_SASR			(IMXRT_LPI2C4.SASR)
#define LPI2C4_STAR			(IMXRT_LPI2C4.STAR)
#define LPI2C4_STDR			(IMXRT_LPI2C4.STDR)
#define LPI2C4_SRDR			(IMXRT_LPI2C4.SRDR)
#define LPI2C_MCR_RRF				((uint32_t)(1<<9))
#define LPI2C_MCR_RTF				((uint32_t)(1<<8))
#define LPI2C_MCR_DBGEN				((uint32_t)(1<<3))
#define LPI2C_MCR_DOZEN				((uint32_t)(1<<2))
#define LPI2C_MCR_RST				((uint32_t)(1<<1))
#define LPI2C_MCR_MEN				((uint32_t)(1<<0))
#define LPI2C_MSR_BBF				((uint32_t)(1<<25))
#define LPI2C_MSR_MBF				((uint32_t)(1<<24))
#define LPI2C_MSR_DMF				((uint32_t)(1<<14))
#define LPI2C_MSR_PLTF				((uint32_t)(1<<13))
#define LPI2C_MSR_FEF				((uint32_t)(1<<12))
#define LPI2C_MSR_ALF				((uint32_t)(1<<11))
#define LPI2C_MSR_NDF				((uint32_t)(1<<10))
#define LPI2C_MSR_SDF				((uint32_t)(1<<9))
#define LPI2C_MSR_EPF				((uint32_t)(1<<8))
#define LPI2C_MSR_RDF				((uint32_t)(1<<1))
#define LPI2C_MSR_TDF				((uint32_t)(1<<0))
#define LPI2C_MIER_DMIE				((uint32_t)(1<<14))
#define LPI2C_MIER_PLTIE			((uint32_t)(1<<13))
#define LPI2C_MIER_FEIE				((uint32_t)(1<<12))
#define LPI2C_MIER_ALIE				((uint32_t)(1<<11))
#define LPI2C_MIER_NDIE				((uint32_t)(1<<10))
#define LPI2C_MIER_SDIE				((uint32_t)(1<<9))
#define LPI2C_MIER_EPIE				((uint32_t)(1<<8))
#define LPI2C_MIER_RDIE				((uint32_t)(1<<1))
#define LPI2C_MIER_TDIE				((uint32_t)(1<<0))
#define LPI2C_MDER_RDDE				((uint32_t)(1<<1))
#define LPI2C_MDER_TDDE				((uint32_t)(1<<0))
#define LPI2C_MCFGR0_RDMO			((uint32_t)(1<<9))
#define LPI2C_MCFGR0_CIRFIFO			((uint32_t)(1<<8))
#define LPI2C_MCFGR0_HRSEL			((uint32_t)(1<<2))
#define LPI2C_MCFGR0_HRPOL			((uint32_t)(1<<1))
#define LPI2C_MCFGR0_HREN			((uint32_t)(1<<0))
#define LPI2C_MCFGR1_PINCFG(n)			((uint32_t)(((n) & 0x07) << 24))
#define LPI2C_MCFGR1_MATCFG(n)			((uint32_t)(((n) & 0x07) << 16))
#define LPI2C_MCFGR1_TIMECFG			((uint32_t)(1<<10))
#define LPI2C_MCFGR1_IGNACK			((uint32_t)(1<<9))
#define LPI2C_MCFGR1_AUTOSTOP			((uint32_t)(1<<8))
#define LPI2C_MCFGR1_PRESCALE(n)		((uint32_t)(((n) & 0x07) << 0))
#define LPI2C_MCFGR2_FILTSDA(n)			((uint32_t)(((n) & 0x0F) << 24))
#define LPI2C_MCFGR2_FILTSCL(n)			((uint32_t)(((n) & 0x0F) << 16))
#define LPI2C_MCFGR2_BUSIDLE(n)			((uint32_t)(((n) & 0xFFF) << 0))
#define LPI2C_MCFGR3_PINLOW(n)			((uint32_t)(((n) & 0xFFF) << 8))
#define LPI2C_MDMR_MATCH1(n)			((uint32_t)(((n) & 0xFF) << 16))
#define LPI2C_MDMR_MATCH0(n)			((uint32_t)(((n) & 0xFF) << 0))
#define LPI2C_MCCR0_DATAVD(n)			((uint32_t)(((n) & 0x3F) << 24))
#define LPI2C_MCCR0_SETHOLD(n)			((uint32_t)(((n) & 0x3F) << 16))
#define LPI2C_MCCR0_CLKHI(n)			((uint32_t)(((n) & 0x3F) << 8))
#define LPI2C_MCCR0_CLKLO(n)			((uint32_t)(((n) & 0x3F) << 0))
#define LPI2C_MCCR1_DATAVD(n)			((uint32_t)(((n) & 0x3F) << 24))
#define LPI2C_MCCR1_SETHOLD(n)			((uint32_t)(((n) & 0x3F) << 16))
#define LPI2C_MCCR1_CLKHI(n)			((uint32_t)(((n) & 0x3F) << 8))
#define LPI2C_MCCR1_CLKLO(n)			((uint32_t)(((n) & 0x3F) << 0))
#define LPI2C_MFCR_RXWATER(n)			((uint32_t)(((n) & 0x03) << 16))
#define LPI2C_MFCR_TXWATER(n)			((uint32_t)(((n) & 0x03) << 0))
#define LPI2C_MFSR_RXCOUNT(n)			((uint32_t)(((n) & 0x07) << 16))
#define LPI2C_MFSR_TXCOUNT(n)			((uint32_t)(((n) & 0x07) << 16))
#define LPI2C_MTDR_CMD(n)			((uint32_t)(((n) & 0x07) << 8))
#define LPI2C_MTDR_CMD_TRANSMIT			((uint32_t)(0 << 8))
#define LPI2C_MTDR_CMD_RECEIVE			((uint32_t)(1 << 8))
#define LPI2C_MTDR_CMD_STOP			((uint32_t)(2 << 8))
#define LPI2C_MTDR_CMD_DISCARD			((uint32_t)(3 << 8))
#define LPI2C_MTDR_CMD_START			((uint32_t)(4 << 8))
#define LPI2C_MTDR_CMD_START_NACK		((uint32_t)(5 << 8))
#define LPI2C_MTDR_CMD_HS_START			((uint32_t)(6 << 8))
#define LPI2C_MTDR_CMD_HS_START_NAcK		((uint32_t)(7 << 8))
#define LPI2C_MTDR_DATA(n)			((uint32_t)(((n) & 0xFF) << 0))
#define LPI2C_MRDR_RXEMPTY			((uint32_t)(1<<14))
#define LPI2C_MRDR_DATA(n)			((uint32_t)(((n) & 0xFF) << 0))
#define LPI2C_SCR_RRF				((uint32_t)(1<<9))
#define LPI2C_SCR_RTF				((uint32_t)(1<<8))
#define LPI2C_SCR_FILTDZ			((uint32_t)(1<<5))
#define LPI2C_SCR_FILTEN			((uint32_t)(1<<4))
#define LPI2C_SCR_RST				((uint32_t)(1<<1))
#define LPI2C_SCR_SEN				((uint32_t)(1<<0))
#define LPI2C_SSR_BBF				((uint32_t)(1<<25))
#define LPI2C_SSR_SBF				((uint32_t)(1<<24))
#define LPI2C_SSR_SARF				((uint32_t)(1<<15))
#define LPI2C_SSR_GCF				((uint32_t)(1<<14))
#define LPI2C_SSR_AM1F				((uint32_t)(1<<13))
#define LPI2C_SSR_AM0F				((uint32_t)(1<<12))
#define LPI2C_SSR_FEF				((uint32_t)(1<<11))
#define LPI2C_SSR_BEF				((uint32_t)(1<<10))
#define LPI2C_SSR_SDF				((uint32_t)(1<<9))
#define LPI2C_SSR_RSF				((uint32_t)(1<<8))
#define LPI2C_SSR_TAF				((uint32_t)(1<<3))
#define LPI2C_SSR_AVF				((uint32_t)(1<<2))
#define LPI2C_SSR_RDF				((uint32_t)(1<<1))
#define LPI2C_SSR_TDF				((uint32_t)(1<<0))
#define LPI2C_SIER_SARIE			((uint32_t)(1<<25))
#define LPI2C_SIER_GCIE				((uint32_t)(1<<24))
#define LPI2C_SIER_AM1F				((uint32_t)(1<<13))
#define LPI2C_SIER_AM0IE			((uint32_t)(1<<12))
#define LPI2C_SIER_FEIE				((uint32_t)(1<<11))
#define LPI2C_SIER_BEIE				((uint32_t)(1<<10))
#define LPI2C_SIER_SDIE				((uint32_t)(1<<9))
#define LPI2C_SIER_RSIE				((uint32_t)(1<<8))
#define LPI2C_SIER_TAIE				((uint32_t)(1<<3))
#define LPI2C_SIER_AVIE				((uint32_t)(1<<2))
#define LPI2C_SIER_RDIE				((uint32_t)(1<<1))
#define LPI2C_SIER_TDIE				((uint32_t)(1<<0))
#define LPI2C_SDER_AVDE				((uint32_t)(1<<2))
#define LPI2C_SDER_RDDE				((uint32_t)(1<<1))
#define LPI2C_SDER_TDDE				((uint32_t)(1<<0))
#define LPI2C_SCFGR1_ADDRCFG(n)			((uint32_t)(((n) & 0x07) << 16))
#define LPI2C_SCFGR1_HSMEN			((uint32_t)(1<<13))
#define LPI2C_SCFGR1_IGNACK			((uint32_t)(1<<12))
#define LPI2C_SCFGR1_RXCFG			((uint32_t)(1<<11))
#define LPI2C_SCFGR1_TXCFG			((uint32_t)(1<<10))
#define LPI2C_SCFGR1_SAEN			((uint32_t)(1<<9))
#define LPI2C_SCFGR1_GCEN			((uint32_t)(1<<8))
#define LPI2C_SCFGR1_ACKSTALL			((uint32_t)(1<<3))
#define LPI2C_SCFGR1_TXDSTALL			((uint32_t)(1<<2))
#define LPI2C_SCFGR1_RXSTALL			((uint32_t)(1<<1))
#define LPI2C_SCFGR1_ADRSTALL			((uint32_t)(1<<0))
#define LPI2C_SCFGR2_FILTSDA(n)			((uint32_t)(((n) & 0x0F) << 24))
#define LPI2C_SCFGR2_FILTSCL(n)			((uint32_t)(((n) & 0x0F) << 16))
#define LPI2C_SCFGR2_DATAVD(n)			((uint32_t)(((n) & 0x3F) << 8))
#define LPI2C_SCFGR2_CLKHOLD(n)			((uint32_t)(((n) & 0x0F) << 0))
#define LPI2C_SAMR_ADDR1(n)			((uint32_t)(((n) & 0x7F) << 17))
#define LPI2C_SAMR_ADDR0(n)			((uint32_t)(((n) & 0x7F) << 1))
#define LPI2C_SASR_ANV				((uint32_t)(1<<14))
#define LPI2C_SASR_RADDR(n)			((uint32_t)(((n) & 0x7FF) << 0))
#define LPI2C_STAR_TXNACK			((uint32_t)(1<<0))
#define LPI2C_STDR_DATA(n)			((uint32_t)(((n) & 0xFF) << 0))
#define LPI2C_SRDR_SOF				((uint32_t)(1<<15))
#define LPI2C_SRDR_RXEMPTY			((uint32_t)(1<<14))
#define LPI2C_SRDR_DATA(n)			((uint32_t)(((n) & 0xFF) << 0))

// 48.4.1.1: page 2810
typedef struct {
        const uint32_t VERID;           // 0
        const uint32_t PARAM;           // 0x04
        const uint32_t UNUSED0;         // 0x08
        const uint32_t UNUSED1;         // 0x0c
        volatile uint32_t CR;           // 0x10
        volatile uint32_t SR;           // 0x14
        volatile uint32_t IER;          // 0x18
        volatile uint32_t DER;          // 0x1c
        volatile uint32_t CFGR0;        // 0x20
        volatile uint32_t CFGR1;        // 0x24
        const uint32_t UNUSED3;         // 0x28
        const uint32_t UNUSED4;         // 0x2c
        volatile uint32_t DMR0;         // 0x30
        volatile uint32_t DMR1;         // 0x34
        const uint32_t UNUSED5;         // 0x38
        const uint32_t UNUSED6;         // 0x3c
        volatile uint32_t CCR;          // 0x40
        const uint32_t UNUSED7;         // 0x44
        const uint32_t UNUSED8;         // 0x48
        const uint32_t UNUSED9;         // 0x4c
        const uint32_t UNUSED10;        // 0x50
        const uint32_t UNUSED11;        // 0x54
        volatile uint32_t FCR;          // 0x58
        volatile uint32_t FSR;          // 0x5C
        volatile uint32_t TCR;          // 0x60
        volatile uint32_t TDR;          // 0x64
        const uint32_t UNUSED12;        // 0x68
        const uint32_t UNUSED13;        // 0x6c
        volatile uint32_t RSR;          // 0x70
        volatile uint32_t RDR;          // 0x74
} IMXRT_LPSPI_t;

#define IMXRT_LPSPI1		(*(IMXRT_REGISTER32_t *)IMXRT_LPSPI1_ADDRESS)
#define IMXRT_LPSPI1_S          (*(IMXRT_LPSPI_t *)IMXRT_LPSPI1_ADDRESS)
#define LPSPI1_VERID			(IMXRT_LPSPI1.offset000)
#define LPSPI1_PARAM			(IMXRT_LPSPI1.offset004)
#define LPSPI1_CR			(IMXRT_LPSPI1.offset010)
#define LPSPI1_SR			(IMXRT_LPSPI1.offset014)
#define LPSPI1_IER			(IMXRT_LPSPI1.offset018)
#define LPSPI1_DER			(IMXRT_LPSPI1.offset01C)
#define LPSPI1_CFGR0			(IMXRT_LPSPI1.offset020)
#define LPSPI1_CFGR1			(IMXRT_LPSPI1.offset024)
#define LPSPI1_DMR0			(IMXRT_LPSPI1.offset030)
#define LPSPI1_DMR1			(IMXRT_LPSPI1.offset034)
#define LPSPI1_CCR			(IMXRT_LPSPI1.offset040)
#define LPSPI1_FCR			(IMXRT_LPSPI1.offset058)
#define LPSPI1_FSR			(IMXRT_LPSPI1.offset05C)
#define LPSPI1_TCR			(IMXRT_LPSPI1.offset060)
#define LPSPI1_TDR			(IMXRT_LPSPI1.offset064)
#define LPSPI1_RSR			(IMXRT_LPSPI1.offset070)
#define LPSPI1_RDR			(IMXRT_LPSPI1.offset074)
#define IMXRT_LPSPI2		(*(IMXRT_REGISTER32_t *)IMXRT_LPSPI2_ADDRESS)
#define IMXRT_LPSPI2_S          (*(IMXRT_LPSPI_t *)IMXRT_LPSPI2_ADDRESS)
#define LPSPI2_VERID			(IMXRT_LPSPI2.offset000)
#define LPSPI2_PARAM			(IMXRT_LPSPI2.offset004)
#define LPSPI2_CR			(IMXRT_LPSPI2.offset010)
#define LPSPI2_SR			(IMXRT_LPSPI2.offset014)
#define LPSPI2_IER			(IMXRT_LPSPI2.offset018)
#define LPSPI2_DER			(IMXRT_LPSPI2.offset01C)
#define LPSPI2_CFGR0			(IMXRT_LPSPI2.offset020)
#define LPSPI2_CFGR1			(IMXRT_LPSPI2.offset024)
#define LPSPI2_DMR0			(IMXRT_LPSPI2.offset030)
#define LPSPI2_DMR1			(IMXRT_LPSPI2.offset034)
#define LPSPI2_CCR			(IMXRT_LPSPI2.offset040)
#define LPSPI2_FCR			(IMXRT_LPSPI2.offset058)
#define LPSPI2_FSR			(IMXRT_LPSPI2.offset05C)
#define LPSPI2_TCR			(IMXRT_LPSPI2.offset060)
#define LPSPI2_TDR			(IMXRT_LPSPI2.offset064)
#define LPSPI2_RSR			(IMXRT_LPSPI2.offset070)
#define LPSPI2_RDR			(IMXRT_LPSPI2.offset074)
#define IMXRT_LPSPI3		(*(IMXRT_REGISTER32_t *)IMXRT_LPSPI3_ADDRESS)
#define IMXRT_LPSPI3_S          (*(IMXRT_LPSPI_t *)IMXRT_LPSPI3_ADDRESS)
#define LPSPI3_VERID			(IMXRT_LPSPI3.offset000)
#define LPSPI3_PARAM			(IMXRT_LPSPI3.offset004)
#define LPSPI3_CR			(IMXRT_LPSPI3.offset010)
#define LPSPI3_SR			(IMXRT_LPSPI3.offset014)
#define LPSPI3_IER			(IMXRT_LPSPI3.offset018)
#define LPSPI3_DER			(IMXRT_LPSPI3.offset01C)
#define LPSPI3_CFGR0			(IMXRT_LPSPI3.offset020)
#define LPSPI3_CFGR1			(IMXRT_LPSPI3.offset024)
#define LPSPI3_DMR0			(IMXRT_LPSPI3.offset030)
#define LPSPI3_DMR1			(IMXRT_LPSPI3.offset034)
#define LPSPI3_CCR			(IMXRT_LPSPI3.offset040)
#define LPSPI3_FCR			(IMXRT_LPSPI3.offset058)
#define LPSPI3_FSR			(IMXRT_LPSPI3.offset05C)
#define LPSPI3_TCR			(IMXRT_LPSPI3.offset060)
#define LPSPI3_TDR			(IMXRT_LPSPI3.offset064)
#define LPSPI3_RSR			(IMXRT_LPSPI3.offset070)
#define LPSPI3_RDR			(IMXRT_LPSPI3.offset074)
#define IMXRT_LPSPI4		(*(IMXRT_REGISTER32_t *)IMXRT_LPSPI4_ADDRESS)
#define IMXRT_LPSPI4_S          (*(IMXRT_LPSPI_t *)IMXRT_LPSPI4_ADDRESS)
#define LPSPI4_VERID			(IMXRT_LPSPI4.offset000)
#define LPSPI4_PARAM			(IMXRT_LPSPI4.offset004)
#define LPSPI4_CR			(IMXRT_LPSPI4.offset010)
#define LPSPI4_SR			(IMXRT_LPSPI4.offset014)
#define LPSPI4_IER			(IMXRT_LPSPI4.offset018)
#define LPSPI4_DER			(IMXRT_LPSPI4.offset01C)
#define LPSPI4_CFGR0			(IMXRT_LPSPI4.offset020)
#define LPSPI4_CFGR1			(IMXRT_LPSPI4.offset024)
#define LPSPI4_DMR0			(IMXRT_LPSPI4.offset030)
#define LPSPI4_DMR1			(IMXRT_LPSPI4.offset034)
#define LPSPI4_CCR			(IMXRT_LPSPI4.offset040)
#define LPSPI4_FCR			(IMXRT_LPSPI4.offset058)
#define LPSPI4_FSR			(IMXRT_LPSPI4.offset05C)
#define LPSPI4_TCR			(IMXRT_LPSPI4.offset060)
#define LPSPI4_TDR			(IMXRT_LPSPI4.offset064)
#define LPSPI4_RSR			(IMXRT_LPSPI4.offset070)
#define LPSPI4_RDR			(IMXRT_LPSPI4.offset074)
#define LPSPI_CR_RRF				((uint32_t)(1<<9))
#define LPSPI_CR_RTF				((uint32_t)(1<<8))
#define LPSPI_CR_DBGEN				((uint32_t)(1<<3))
#define LPSPI_CR_DOZEN				((uint32_t)(1<<2))
#define LPSPI_CR_RST				((uint32_t)(1<<1))
#define LPSPI_CR_MEN				((uint32_t)(1<<0))
#define LPSPI_SR_MBF				((uint32_t)(1<<24))
#define LPSPI_SR_DMF				((uint32_t)(1<<13))
#define LPSPI_SR_REF				((uint32_t)(1<<12))
#define LPSPI_SR_TEF				((uint32_t)(1<<11))
#define LPSPI_SR_TCF				((uint32_t)(1<<10))
#define LPSPI_SR_FCF				((uint32_t)(1<<9))
#define LPSPI_SR_WCF				((uint32_t)(1<<8))
#define LPSPI_SR_RDF				((uint32_t)(1<<1))
#define LPSPI_SR_TDF				((uint32_t)(1<<0))
#define LPSPI_IER_DMIE				((uint32_t)(1<<13))
#define LPSPI_IER_REIE				((uint32_t)(1<<12))
#define LPSPI_IER_TEIE				((uint32_t)(1<<11))
#define LPSPI_IER_TCIE				((uint32_t)(1<<10))
#define LPSPI_IER_FCIE				((uint32_t)(1<<9))
#define LPSPI_IER_WCIE				((uint32_t)(1<<8))
#define LPSPI_IER_RDIE				((uint32_t)(1<<1))
#define LPSPI_IER_TDIE				((uint32_t)(1<<0))
#define LPSPI_DER_RDDE				((uint32_t)(1<<1))
#define LPSPI_DER_TDDE				((uint32_t)(1<<0))
#define LPSPI_CFGR0_RDMO			((uint32_t)(1<<9))
#define LPSPI_CFGR0_CIRFIFO			((uint32_t)(1<<8))
#define LPSPI_CFGR0_HRSEL			((uint32_t)(1<<2))
#define LPSPI_CFGR0_HRPOL			((uint32_t)(1<<1))
#define LPSPI_CFGR0_HREN			((uint32_t)(1<<0))
#define LPSPI_CFGR1_PCSCFG			((uint32_t)(1<<27))
#define LPSPI_CFGR1_OUTCFG			((uint32_t)(1<<26))
#define LPSPI_CFGR1_PINCFG(n)			((uint32_t)(((n) & 0x03) << 24))
#define LPSPI_CFGR1_MATCFG(n)			((uint32_t)(((n) & 0x07) << 16))
#define LPSPI_CFGR1_PCSPOL(n)			((uint32_t)(((n) & 0x0F) << 8))
#define LPSPI_CFGR1_NOSTALL			((uint32_t)(1<<3))
#define LPSPI_CFGR1_AUTOPCS			((uint32_t)(1<<2))
#define LPSPI_CFGR1_SAMPLE			((uint32_t)(1<<1))
#define LPSPI_CFGR1_MASTER			((uint32_t)(1<<0))
#define LPSPI_CCR_SCKPCS(n)			((uint32_t)(((n) & 0xFF) << 24))
#define LPSPI_CCR_PCSSCK(n)			((uint32_t)(((n) & 0xFF) << 16))
#define LPSPI_CCR_DBT(n)			((uint32_t)(((n) & 0xFF) << 8))
#define LPSPI_CCR_SCKDIV(n)			((uint32_t)(((n) & 0xFF) << 0))
#define LPSPI_FCR_RXWATER(n)			((uint32_t)(((n) & 0x0F) << 16))
#define LPSPI_FCR_TXWATER(n)			((uint32_t)(((n) & 0x0F) << 0))
#define LPSPI_FSR_RXCOUNT(n)			((uint32_t)(((n) & 0x1F) << 16))
#define LPSPI_FSR_TXCOUNT(n)			((uint32_t)(((n) & 0x1F) << 0))
#define LPSPI_TCR_CPOL				((uint32_t)(1<<31))
#define LPSPI_TCR_CPHA				((uint32_t)(1<<30))
#define LPSPI_TCR_PRESCALE(n)			((uint32_t)(((n) & 0x07) << 27))
#define LPSPI_TCR_PCS(n)			((uint32_t)(((n) & 0x03) << 24))
#define LPSPI_TCR_LSBF				((uint32_t)(1<<23))
#define LPSPI_TCR_BYSW				((uint32_t)(1<<22))
#define LPSPI_TCR_CONT				((uint32_t)(1<<21))
#define LPSPI_TCR_CONTC				((uint32_t)(1<<20))
#define LPSPI_TCR_RXMSK				((uint32_t)(1<<19))
#define LPSPI_TCR_TXMSK				((uint32_t)(1<<18))
#define LPSPI_TCR_WIDTH(n)			((uint32_t)(((n) & 0x03) << 16))
#define LPSPI_TCR_FRAMESZ(n)			((uint32_t)(((n) & 0xFFF) << 0))
#define LPSPI_RSR_RXEMPTY			((uint32_t)(1<<1))
#define LPSPI_RSR_SOF				((uint32_t)(1<<0))

// 49.4.1.1: page 2854
typedef struct {
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
} IMXRT_LPUART_t;
#define IMXRT_LPUART1		(*(IMXRT_LPUART_t *)IMXRT_LPUART1_ADDRESS)
#define LPUART1_VERID			(IMXRT_LPUART1.VERID)
#define LPUART1_PARAM			(IMXRT_LPUART1.PARAM)
#define LPUART1_GLOBAL			(IMXRT_LPUART1.GLOBAL)
#define LPUART1_PINCFG			(IMXRT_LPUART1.PINCFG)
#define LPUART1_BAUD			(IMXRT_LPUART1.BAUD)
#define LPUART1_STAT			(IMXRT_LPUART1.STAT)
#define LPUART1_CTRL			(IMXRT_LPUART1.CTRL)
#define LPUART1_DATA			(IMXRT_LPUART1.DATA)
#define LPUART1_MATCH			(IMXRT_LPUART1.MATCH)
#define LPUART1_MODIR			(IMXRT_LPUART1.MODIR)
#define LPUART1_FIFO			(IMXRT_LPUART1.FIFO)
#define LPUART1_WATER			(IMXRT_LPUART1.WATER)
#define IMXRT_LPUART2		(*(IMXRT_LPUART_t *)IMXRT_LPUART2_ADDRESS)
#define LPUART2_VERID			(IMXRT_LPUART2.VERID)
#define LPUART2_PARAM			(IMXRT_LPUART2.PARAM)
#define LPUART2_GLOBAL			(IMXRT_LPUART2.GLOBAL)
#define LPUART2_PINCFG			(IMXRT_LPUART2.PINCFG)
#define LPUART2_BAUD			(IMXRT_LPUART2.BAUD)
#define LPUART2_STAT			(IMXRT_LPUART2.STAT)
#define LPUART2_CTRL			(IMXRT_LPUART2.CTRL)
#define LPUART2_DATA			(IMXRT_LPUART2.DATA)
#define LPUART2_MATCH			(IMXRT_LPUART2.MATCH)
#define LPUART2_MODIR			(IMXRT_LPUART2.MODIR)
#define LPUART2_FIFO			(IMXRT_LPUART2.FIFO)
#define LPUART2_WATER			(IMXRT_LPUART2.WATER)
#define IMXRT_LPUART3		(*(IMXRT_LPUART_t *)IMXRT_LPUART3_ADDRESS)
#define LPUART3_VERID			(IMXRT_LPUART3.VERID)
#define LPUART3_PARAM			(IMXRT_LPUART3.PARAM)
#define LPUART3_GLOBAL			(IMXRT_LPUART3.GLOBAL)
#define LPUART3_PINCFG			(IMXRT_LPUART3.PINCFG)
#define LPUART3_BAUD			(IMXRT_LPUART3.BAUD)
#define LPUART3_STAT			(IMXRT_LPUART3.STAT)
#define LPUART3_CTRL			(IMXRT_LPUART3.CTRL)
#define LPUART3_DATA			(IMXRT_LPUART3.DATA)
#define LPUART3_MATCH			(IMXRT_LPUART3.MATCH)
#define LPUART3_MODIR			(IMXRT_LPUART3.MODIR)
#define LPUART3_FIFO			(IMXRT_LPUART3.FIFO)
#define LPUART3_WATER			(IMXRT_LPUART3.WATER)
#define IMXRT_LPUART4		(*(IMXRT_LPUART_t *)IMXRT_LPUART4_ADDRESS)
#define LPUART4_VERID			(IMXRT_LPUART4.VERID)
#define LPUART4_PARAM			(IMXRT_LPUART4.PARAM)
#define LPUART4_GLOBAL			(IMXRT_LPUART4.GLOBAL)
#define LPUART4_PINCFG			(IMXRT_LPUART4.PINCFG)
#define LPUART4_BAUD			(IMXRT_LPUART4.BAUD)
#define LPUART4_STAT			(IMXRT_LPUART4.STAT)
#define LPUART4_CTRL			(IMXRT_LPUART4.CTRL)
#define LPUART4_DATA			(IMXRT_LPUART4.DATA)
#define LPUART4_MATCH			(IMXRT_LPUART4.MATCH)
#define LPUART4_MODIR			(IMXRT_LPUART4.MODIR)
#define LPUART4_FIFO			(IMXRT_LPUART4.FIFO)
#define LPUART4_WATER			(IMXRT_LPUART4.WATER)
#define IMXRT_LPUART5		(*(IMXRT_LPUART_t *)IMXRT_LPUART5_ADDRESS)
#define LPUART5_VERID			(IMXRT_LPUART5.VERID)
#define LPUART5_PARAM			(IMXRT_LPUART5.PARAM)
#define LPUART5_GLOBAL			(IMXRT_LPUART5.GLOBAL)
#define LPUART5_PINCFG			(IMXRT_LPUART5.PINCFG)
#define LPUART5_BAUD			(IMXRT_LPUART5.BAUD)
#define LPUART5_STAT			(IMXRT_LPUART5.STAT)
#define LPUART5_CTRL			(IMXRT_LPUART5.CTRL)
#define LPUART5_DATA			(IMXRT_LPUART5.DATA)
#define LPUART5_MATCH			(IMXRT_LPUART5.MATCH)
#define LPUART5_MODIR			(IMXRT_LPUART5.MODIR)
#define LPUART5_FIFO			(IMXRT_LPUART5.FIFO)
#define LPUART5_WATER			(IMXRT_LPUART5.WATER)
#define IMXRT_LPUART6		(*(IMXRT_LPUART_t *)IMXRT_LPUART6_ADDRESS)
#define LPUART6_VERID			(IMXRT_LPUART6.VERID)
#define LPUART6_PARAM			(IMXRT_LPUART6.PARAM)
#define LPUART6_GLOBAL			(IMXRT_LPUART6.GLOBAL)
#define LPUART6_PINCFG			(IMXRT_LPUART6.PINCFG)
#define LPUART6_BAUD			(IMXRT_LPUART6.BAUD)
#define LPUART6_STAT			(IMXRT_LPUART6.STAT)
#define LPUART6_CTRL			(IMXRT_LPUART6.CTRL)
#define LPUART6_DATA			(IMXRT_LPUART6.DATA)
#define LPUART6_MATCH			(IMXRT_LPUART6.MATCH)
#define LPUART6_MODIR			(IMXRT_LPUART6.MODIR)
#define LPUART6_FIFO			(IMXRT_LPUART6.FIFO)
#define LPUART6_WATER			(IMXRT_LPUART6.WATER)
#define IMXRT_LPUART7		(*(IMXRT_LPUART_t *)IMXRT_LPUART7_ADDRESS)
#define LPUART7_VERID			(IMXRT_LPUART7.VERID)
#define LPUART7_PARAM			(IMXRT_LPUART7.PARAM)
#define LPUART7_GLOBAL			(IMXRT_LPUART7.GLOBAL)
#define LPUART7_PINCFG			(IMXRT_LPUART7.PINCFG)
#define LPUART7_BAUD			(IMXRT_LPUART7.BAUD)
#define LPUART7_STAT			(IMXRT_LPUART7.STAT)
#define LPUART7_CTRL			(IMXRT_LPUART7.CTRL)
#define LPUART7_DATA			(IMXRT_LPUART7.DATA)
#define LPUART7_MATCH			(IMXRT_LPUART7.MATCH)
#define LPUART7_MODIR			(IMXRT_LPUART7.MODIR)
#define LPUART7_FIFO			(IMXRT_LPUART7.FIFO)
#define LPUART7_WATER			(IMXRT_LPUART7.WATER)
#define IMXRT_LPUART8		(*(IMXRT_LPUART_t *)IMXRT_LPUART8_ADDRESS)
#define LPUART8_VERID			(IMXRT_LPUART8.VERID)
#define LPUART8_PARAM			(IMXRT_LPUART8.PARAM)
#define LPUART8_GLOBAL			(IMXRT_LPUART8.GLOBAL)
#define LPUART8_PINCFG			(IMXRT_LPUART8.PINCFG)
#define LPUART8_BAUD			(IMXRT_LPUART8.BAUD)
#define LPUART8_STAT			(IMXRT_LPUART8.STAT)
#define LPUART8_CTRL			(IMXRT_LPUART8.CTRL)
#define LPUART8_DATA			(IMXRT_LPUART8.DATA)
#define LPUART8_MATCH			(IMXRT_LPUART8.MATCH)
#define LPUART8_MODIR			(IMXRT_LPUART8.MODIR)
#define LPUART8_FIFO			(IMXRT_LPUART8.FIFO)
#define LPUART8_WATER			(IMXRT_LPUART8.WATER)
#define LPUART_VERID_MAJOR(n)			((uint32_t)(((n) & 0xFF) << 24))
#define LPUART_VERID_MINOR(n)			((uint32_t)(((n) & 0xFF) << 16))
#define LPUART_VERID_FEATURE(n)			((uint32_t)(((n) & 0xFFFF) << 0))
#define LPUART_PARAM_RXFIFO(n)			((uint32_t)(((n) & 0xFF) << 8))
#define LPUART_PARAM_TXFIFO(n)			((uint32_t)(((n) & 0xFF) << 0))
#define LPUART_GLOBAL_RST			((uint32_t)(1<<1))
#define LPUART_PINCFG_TRGSEL(n)			((uint32_t)(((n) & 0x03) << 0))
#define LPUART_BAUD_MAEN1			((uint32_t)(1<<31))
#define LPUART_BAUD_MAEN2			((uint32_t)(1<<30))
#define LPUART_BAUD_M10				((uint32_t)(1<<29))
#define LPUART_BAUD_OSR(n)			((uint32_t)(((n) & 0x1F) << 24))
#define LPUART_BAUD_TDMAE			((uint32_t)(1<<23))
#define LPUART_BAUD_RDMAE			((uint32_t)(1<<21))
#define LPUART_BAUD_MATCFG(n)			((uint32_t)(((n) & 0x03) << 18))
#define LPUART_BAUD_BOTHEDGE			((uint32_t)(1<<17))
#define LPUART_BAUD_RESYNCDIS			((uint32_t)(1<<16))
#define LPUART_BAUD_LBKDIE			((uint32_t)(1<<15))
#define LPUART_BAUD_RXEDGIE			((uint32_t)(1<<14))
#define LPUART_BAUD_SBNS			((uint32_t)(1<<13))
#define LPUART_BAUD_SBR(n)			((uint32_t)(((n) & 0x01FFF) << 0))
#define LPUART_STAT_LBKDIF			((uint32_t)(1<<31))
#define LPUART_STAT_RXEDGIF			((uint32_t)(1<<30))
#define LPUART_STAT_MSBF			((uint32_t)(1<<29))
#define LPUART_STAT_RXINV			((uint32_t)(1<<28))
#define LPUART_STAT_RWUID			((uint32_t)(1<<27))
#define LPUART_STAT_BRK13			((uint32_t)(1<<26))
#define LPUART_STAT_LBKDE			((uint32_t)(1<<25))
#define LPUART_STAT_RAF				((uint32_t)(1<<24))
#define LPUART_STAT_TDRE			((uint32_t)(1<<23))
#define LPUART_STAT_TC				((uint32_t)(1<<22))
#define LPUART_STAT_RDRF			((uint32_t)(1<<21))
#define LPUART_STAT_IDLE			((uint32_t)(1<<20))
#define LPUART_STAT_OR				((uint32_t)(1<<19))
#define LPUART_STAT_NF				((uint32_t)(1<<18))
#define LPUART_STAT_FE				((uint32_t)(1<<17))
#define LPUART_STAT_PF				((uint32_t)(1<<16))
#define LPUART_STAT_MA1F			((uint32_t)(1<<15))
#define LPUART_STAT_MA2F			((uint32_t)(1<<14))
#define LPUART_CTRL_R8T9			((uint32_t)(1<<31))
#define LPUART_CTRL_R9T8			((uint32_t)(1<<30))
#define LPUART_CTRL_TXDIR			((uint32_t)(1<<29))
#define LPUART_CTRL_TXINV			((uint32_t)(1<<28))
#define LPUART_CTRL_ORIE			((uint32_t)(1<<27))
#define LPUART_CTRL_NEIE			((uint32_t)(1<<26))
#define LPUART_CTRL_FEIE			((uint32_t)(1<<25))
#define LPUART_CTRL_PEIE			((uint32_t)(1<<24))
#define LPUART_CTRL_TIE				((uint32_t)(1<<23))
#define LPUART_CTRL_TCIE			((uint32_t)(1<<22))
#define LPUART_CTRL_RIE				((uint32_t)(1<<21))
#define LPUART_CTRL_ILIE			((uint32_t)(1<<20))
#define LPUART_CTRL_TE				((uint32_t)(1<<19))
#define LPUART_CTRL_RE				((uint32_t)(1<<18))
#define LPUART_CTRL_RWU				((uint32_t)(1<<17))
#define LPUART_CTRL_SBK				((uint32_t)(1<<16))
#define LPUART_CTRL_MA1IE			((uint32_t)(1<<15))
#define LPUART_CTRL_MA2IE			((uint32_t)(1<<14))
#define LPUART_CTRL_M7				((uint32_t)(1<<11))
#define LPUART_CTRL_IDLECFG(n)			((uint32_t)(((n) & 0x07) << 8))
#define LPUART_CTRL_LOOPS			((uint32_t)(1<<7))
#define LPUART_CTRL_DOZEEN			((uint32_t)(1<<6))
#define LPUART_CTRL_RSRC			((uint32_t)(1<<5))
#define LPUART_CTRL_M				((uint32_t)(1<<4))
#define LPUART_CTRL_WAKE			((uint32_t)(1<<3))
#define LPUART_CTRL_ILT				((uint32_t)(1<<2))
#define LPUART_CTRL_PE				((uint32_t)(1<<1))
#define LPUART_CTRL_PT				((uint32_t)(1<<0))
#define LPUART_DATA_NOISY			((uint32_t)(1<<15))
#define LPUART_DATA_PARITYE			((uint32_t)(1<<14))
#define LPUART_DATA_FRETSC			((uint32_t)(1<<13))
#define LPUART_DATA_RXEMPT			((uint32_t)(1<<12))
#define LPUART_DATA_IDLINE			((uint32_t)(1<<11))
#define LPUART_MATCH_MA2(n)			((uint32_t)(((n) & 0x3FF) << 16))
#define LPUART_MATCH_MA1(n)			((uint32_t)(((n) & 0x3FF) << 0))
#define LPUART_MODIR_IREN			((uint32_t)(1<<18))
#define LPUART_MODIR_TNP(n)			((uint32_t)(((n) & 0x03) << 16))
#define LPUART_MODIR_RTSWATER(n)		((uint32_t)(((n) & 0x03) << 8))
#define LPUART_MODIR_TXCTSSRC			((uint32_t)(1<<5))
#define LPUART_MODIR_TXCTSC			((uint32_t)(1<<4))
#define LPUART_MODIR_RXRTSE			((uint32_t)(1<<3))
#define LPUART_MODIR_TXRTSPOL			((uint32_t)(1<<2))
#define LPUART_MODIR_TXRTSE			((uint32_t)(1<<1))
#define LPUART_MODIR_TXCTSE			((uint32_t)(1<<0))
#define LPUART_FIFO_TXEMPT			((uint32_t)(1<<23))
#define LPUART_FIFO_RXEMPT			((uint32_t)(1<<22))
#define LPUART_FIFO_TXOF			((uint32_t)(1<<17))
#define LPUART_FIFO_RXUF			((uint32_t)(1<<16))
#define LPUART_FIFO_TXFLUSH			((uint32_t)(1<<15))
#define LPUART_FIFO_RXFLUSH			((uint32_t)(1<<14))
#define LPUART_FIFO_RXIDEN(n)			((uint32_t)(((n) & 0x07) << 10))
#define LPUART_FIFO_TXOFE			((uint32_t)(1<<9))
#define LPUART_FIFO_RXUFE			((uint32_t)(1<<8))
#define LPUART_FIFO_TXFE			((uint32_t)(1<<7))
#define LPUART_FIFO_TXFIFOSIZE(n)		((uint32_t)(((n) & 0x07) << 4))
#define LPUART_FIFO_RXFE			((uint32_t)(1<<3))
#define LPUART_FIFO_RXFIFOSIZE(n)		((uint32_t)(((n) & 0x07) << 0))
#define LPUART_WATER_RXCOUNT(n)			((uint32_t)(((n) & 0x07) << 24))
#define LPUART_WATER_RXWATER(n)			((uint32_t)(((n) & 0x03) << 16))
#define LPUART_WATER_TXCOUNT(n)			((uint32_t)(((n) & 0x07) << 8))
#define LPUART_WATER_TXWATER(n)			((uint32_t)(((n) & 0x03) << 0))


// 23.6.1.1: page 1331
#define IMXRT_OCOTP		(*(IMXRT_REGISTER32_t *)IMXRT_OCOTP_ADDRESS)
#define HW_OCOTP_CTRL			(IMXRT_OCOTP.offset000)
#define HW_OCOTP_CTRL_SET		(IMXRT_OCOTP.offset004)
#define HW_OCOTP_CTRL_CLR		(IMXRT_OCOTP.offset008)
#define HW_OCOTP_CTRL_TOG		(IMXRT_OCOTP.offset00C)
#define HW_OCOTP_TIMING			(IMXRT_OCOTP.offset010)
#define HW_OCOTP_DATA			(IMXRT_OCOTP.offset020)
#define HW_OCOTP_READ_CTRL		(IMXRT_OCOTP.offset030)
#define HW_OCOTP_READ_FUSE_DATA		(IMXRT_OCOTP.offset040)
#define HW_OCOTP_SW_STICKY		(IMXRT_OCOTP.offset050)
#define HW_OCOTP_SCS			(IMXRT_OCOTP.offset060)
#define HW_OCOTP_SCS_SET		(IMXRT_OCOTP.offset064)
#define HW_OCOTP_SCS_CLR		(IMXRT_OCOTP.offset068)
#define HW_OCOTP_SCS_TOG		(IMXRT_OCOTP.offset06C)
#define HW_OCOTP_VERSION		(IMXRT_OCOTP.offset090)
#define HW_OCOTP_TIMING2		(IMXRT_OCOTP.offset100)
#define HW_OCOTP_CTRL_WR_UNLOCK(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define HW_OCOTP_CTRL_RELOAD_SHADOWS		((uint32_t)(1<<10))
#define HW_OCOTP_CTRL_ERROR			((uint32_t)(1<<9))
#define HW_OCOTP_CTRL_BUSY			((uint32_t)(1<<8))
#define HW_OCOTP_CTRL_ADDR(n)			((uint32_t)(((n) & 0x3F) << 0))
#define HW_OCOTP_TIMING_WAIT(n)			((uint32_t)(((n) & 0x3F) << 22))
#define HW_OCOTP_TIMING_STROBE_READ(n)		((uint32_t)(((n) & 0x3F) << 16))
#define HW_OCOTP_TIMING_RELAX(n)		((uint32_t)(((n) & 0x0F) << 12))
#define HW_OCOTP_TIMING_STROBE_PROG(n)		((uint32_t)(((n) & 0xFFF) << 0))
#define HW_OCOTP_READ_CTRL_READ_FUSE		((uint32_t)(1<<0))
#define HW_OCOTP_SW_STICKY_JTAG_BLOCK_RELEASE	((uint32_t)(1<<4))
#define HW_OCOTP_SW_STICKY_BLOCK_ROM_PART	((uint32_t)(1<<3))
#define HW_OCOTP_SW_STICKY_FIELD_RETURN_LOCK	((uint32_t)(1<<2))
#define HW_OCOTP_SW_STICKY_SRK_REVOKE_LOCK	((uint32_t)(1<<1))
#define HW_OCOTP_SW_STICKY_BLOCK_DTCP_KEY	((uint32_t)(1<<0))
#define HW_OCOTP_SCS_LOCK			((uint32_t)(1<<31))
#define HW_OCOTP_SCS_HAB_JDE			((uint32_t)(1<<0))
#define HW_OCOTP_TIMING2_RELAX1(n)		((uint32_t)(((n) & 0x7F) << 24))
#define HW_OCOTP_TIMING2_RELAX_READ(n)		((uint32_t)(((n) & 0x3F) << 16))
#define HW_OCOTP_TIMING2_RELAX_PROG(n)		((uint32_t)(((n) & 0xFFF) << 0))
#define IMXRT_OCOTP_VALUE	(*(IMXRT_REGISTER32_t *)(IMXRT_OCOTP_ADDRESS+0x400))
#define HW_OCOTP_LOCK			(IMXRT_OCOTP_VALUE.offset000)
#define HW_OCOTP_CFG0			(IMXRT_OCOTP_VALUE.offset010)
#define HW_OCOTP_CFG1			(IMXRT_OCOTP_VALUE.offset020)
#define HW_OCOTP_CFG2			(IMXRT_OCOTP_VALUE.offset030)
#define HW_OCOTP_CFG3			(IMXRT_OCOTP_VALUE.offset040)
#define HW_OCOTP_CFG4			(IMXRT_OCOTP_VALUE.offset050)
#define HW_OCOTP_CFG5			(IMXRT_OCOTP_VALUE.offset060)
#define HW_OCOTP_CFG6			(IMXRT_OCOTP_VALUE.offset070)
#define HW_OCOTP_ANA1			(IMXRT_OCOTP_VALUE.offset0E0)
#define HW_OCOTP_ANA2			(IMXRT_OCOTP_VALUE.offset0F0)
#define HW_OCOTP_0x580			(IMXRT_OCOTP_VALUE.offset180)
#define HW_OCOTP_0x590			(IMXRT_OCOTP_VALUE.offset190)
#define HW_OCOTP_0x5A0			(IMXRT_OCOTP_VALUE.offset1A0)
#define HW_OCOTP_0x5B0			(IMXRT_OCOTP_VALUE.offset1B0)
#define HW_OCOTP_0x5C0			(IMXRT_OCOTP_VALUE.offset1C0)
#define HW_OCOTP_0x5D0			(IMXRT_OCOTP_VALUE.offset1D0)
#define HW_OCOTP_0x5E0			(IMXRT_OCOTP_VALUE.offset1E0)
#define HW_OCOTP_0x5F0			(IMXRT_OCOTP_VALUE.offset1F0)
#define HW_OCOTP_SJC_RESP0		(IMXRT_OCOTP_VALUE.offset200)
#define HW_OCOTP_SJC_RESP1		(IMXRT_OCOTP_VALUE.offset210)
#define HW_OCOTP_MAC0			(IMXRT_OCOTP_VALUE.offset220)
#define HW_OCOTP_MAC1			(IMXRT_OCOTP_VALUE.offset230)
#define HW_OCOTP_MAC2			(IMXRT_OCOTP_VALUE.offset240)
#define HW_OCOTP_GP1			(IMXRT_OCOTP_VALUE.offset260)
#define HW_OCOTP_GP2			(IMXRT_OCOTP_VALUE.offset270)
#define HW_OCOTP_SW_GP1			(IMXRT_OCOTP_VALUE.offset280)
#define HW_OCOTP_0x690			(IMXRT_OCOTP_VALUE.offset290)
#define HW_OCOTP_0x6A0			(IMXRT_OCOTP_VALUE.offset2A0)
#define HW_OCOTP_0x6B0			(IMXRT_OCOTP_VALUE.offset2B0)
#define HW_OCOTP_0x6C0			(IMXRT_OCOTP_VALUE.offset2C0)
#define HW_OCOTP_MISC_CONF0		(IMXRT_OCOTP_VALUE.offset2D0)
#define HW_OCOTP_MISC_CONF1		(IMXRT_OCOTP_VALUE.offset2E0)
#if defined(__IMXRT1062__)
#define IMXRT_OCOTP_VALUE2	(*(IMXRT_REGISTER32_t *)(IMXRT_OCOTP_ADDRESS+0x800))
#define HW_OCOTP_GP30			(IMXRT_OCOTP_VALUE2.offset080)
#define HW_OCOTP_GP31			(IMXRT_OCOTP_VALUE2.offset090)
#define HW_OCOTP_GP32			(IMXRT_OCOTP_VALUE2.offset0A0)
#define HW_OCOTP_GP33			(IMXRT_OCOTP_VALUE2.offset0B0)
#define HW_OCOTP_0x8C0			(IMXRT_OCOTP_VALUE2.offset0C0)
#define HW_OCOTP_0x8D0			(IMXRT_OCOTP_VALUE2.offset0D0)
#define HW_OCOTP_0x8E0			(IMXRT_OCOTP_VALUE2.offset0E0)
#define HW_OCOTP_0x8F0			(IMXRT_OCOTP_VALUE2.offset0F0)
#endif

// 53.9.1: page 2978
#define IMXRT_PIT		(*(IMXRT_REGISTER32_t *)IMXRT_PIT_ADDRESS)
#define PIT_MCR				(IMXRT_PIT.offset000)
#define PIT_LTMR64H			(IMXRT_PIT.offset0E0)
#define PIT_LTMR64L			(IMXRT_PIT.offset0E4)
typedef struct {
	volatile uint32_t LDVAL;
	volatile uint32_t CVAL;
	volatile uint32_t TCTRL;
	volatile uint32_t TFLG;
} IMXRT_PIT_CHANNEL_t;
#define IMXRT_PIT_CHANNELS		((IMXRT_PIT_CHANNEL_t *)(&(IMXRT_PIT.offset100)))
#define PIT_LDVAL0			(IMXRT_PIT.offset100)
#define PIT_CVAL0			(IMXRT_PIT.offset104)
#define PIT_TCTRL0			(IMXRT_PIT.offset108)
#define PIT_TFLG0			(IMXRT_PIT.offset10C)
#define PIT_LDVAL1			(IMXRT_PIT.offset110)
#define PIT_CVAL1			(IMXRT_PIT.offset114)
#define PIT_TCTRL1			(IMXRT_PIT.offset118)
#define PIT_TFLG1			(IMXRT_PIT.offset11C)
#define PIT_LDVAL2			(IMXRT_PIT.offset120)
#define PIT_CVAL2			(IMXRT_PIT.offset124)
#define PIT_TCTRL2			(IMXRT_PIT.offset128)
#define PIT_TFLG2			(IMXRT_PIT.offset12C)
#define PIT_LDVAL3			(IMXRT_PIT.offset130)
#define PIT_CVAL3			(IMXRT_PIT.offset134)
#define PIT_TCTRL3			(IMXRT_PIT.offset138)
#define PIT_TFLG3			(IMXRT_PIT.offset13C)
#define PIT_MCR_MDIS				((uint32_t)(1<<1))
#define PIT_MCR_FRZ				((uint32_t)(1<<0))
#define PIT_TCTRL_CHN				((uint32_t)(1<<2))
#define PIT_TCTRL_TIE				((uint32_t)(1<<1))
#define PIT_TCTRL_TEN				((uint32_t)(1<<0))
#define PIT_TFLG_TIF				((uint32_t)(1<<0))

// 16.6: page 1160
#define IMXRT_PMU		(*(IMXRT_REGISTER32_t *)IMXRT_PMU_ADDRESS)
#define PMU_REG_1P1			(IMXRT_PMU.offset110)
#define PMU_REG_1P1_SET			(IMXRT_PMU.offset114)
#define PMU_REG_1P1_CLR			(IMXRT_PMU.offset118)
#define PMU_REG_1P1_TOG			(IMXRT_PMU.offset11C)
#define PMU_REG_3P0			(IMXRT_PMU.offset120)
#define PMU_REG_3P0_SET			(IMXRT_PMU.offset124)
#define PMU_REG_3P0_CLR			(IMXRT_PMU.offset128)
#define PMU_REG_3P0_TOG			(IMXRT_PMU.offset12C)
#define PMU_REG_2P5			(IMXRT_PMU.offset130)
#define PMU_REG_2P5_SET			(IMXRT_PMU.offset134)
#define PMU_REG_2P5_CLR			(IMXRT_PMU.offset138)
#define PMU_REG_2P5_TOG			(IMXRT_PMU.offset13C)
#define PMU_REG_CORE			(IMXRT_PMU.offset140)
#define PMU_REG_CORE_SET		(IMXRT_PMU.offset144)
#define PMU_REG_CORE_CLR		(IMXRT_PMU.offset148)
#define PMU_REG_CORE_TOG		(IMXRT_PMU.offset14C)
#define PMU_MISC0			(IMXRT_PMU.offset150)
#define PMU_MISC0_SET			(IMXRT_PMU.offset154)
#define PMU_MISC0_CLR			(IMXRT_PMU.offset158)
#define PMU_MISC0_TOG			(IMXRT_PMU.offset15C)
#define PMU_MISC1			(IMXRT_PMU.offset160)
#define PMU_MISC1_SET			(IMXRT_PMU.offset164)
#define PMU_MISC1_CLR			(IMXRT_PMU.offset168)
#define PMU_MISC1_TOG			(IMXRT_PMU.offset16C)
#define PMU_MISC2			(IMXRT_PMU.offset170)
#define PMU_MISC2_SET			(IMXRT_PMU.offset174)
#define PMU_MISC2_CLR			(IMXRT_PMU.offset178)
#define PMU_MISC2_TOG			(IMXRT_PMU.offset17C)
#define PMU_REG_1P1_SELREF_WEAK_LINREG		((uint32_t)(1<<19))
#define PMU_REG_1P1_ENABLE_WEAK_LINREG		((uint32_t)(1<<18))
#define PMU_REG_1P1_OK_VDD1P1			((uint32_t)(1<<17))
#define PMU_REG_1P1_BO_VDD1P1			((uint32_t)(1<<16))
#define PMU_REG_1P1_OUTPUT_TRG(n)		((uint32_t)(((n) & 0x0F) << 8))
#define PMU_REG_1P1_BO_OFFSET(n)		((uint32_t)(((n) & 0x07) << 4))
#define PMU_REG_1P1_ENABLE_PULLDOWN		((uint32_t)(1<<3))
#define PMU_REG_1P1_ENABLE_ILIMIT		((uint32_t)(1<<2))
#define PMU_REG_1P1_ENABLE_BO			((uint32_t)(1<<1))
#define PMU_REG_1P1_ENABLE_LINREG		((uint32_t)(1<<0))
#define PMU_REG_3P0_OK_VDD3P0			((uint32_t)(1<<17))
#define PMU_REG_3P0_BO_VDD3P0			((uint32_t)(1<<16))
#define PMU_REG_3P0_OUTPUT_TRG(n)		((uint32_t)(((n) & 0x1F) << 8))
#define PMU_REG_3P0_VBUS_SEL			((uint32_t)(1<<7))
#define PMU_REG_3P0_BO_OFFSET(n)		((uint32_t)(((n) & 0x07) << 4))
#define PMU_REG_3P0_ENABLE_ILIMIT		((uint32_t)(1<<2))
#define PMU_REG_3P0_ENABLE_BO			((uint32_t)(1<<1))
#define PMU_REG_3P0_ENABLE_LINREG		((uint32_t)(1<<0))
#define PMU_REG_2P5_ENABLE_WEAK_LINREG		((uint32_t)(1<<18))
#define PMU_REG_2P5_OK_VDD2P5			((uint32_t)(1<<17))
#define PMU_REG_2P5_BO_VDD2P5			((uint32_t)(1<<16))
#define PMU_REG_2P5_OUTPUT_TRG(n)		((uint32_t)(((n) & 0x0F) << 8))
#define PMU_REG_2P5_BO_OFFSET(n)		((uint32_t)(((n) & 0x07) << 4))
#define PMU_REG_2P5_ENABLE_PULLDOWN		((uint32_t)(1<<3))
#define PMU_REG_2P5_ENABLE_ILIMIT		((uint32_t)(1<<2))
#define PMU_REG_2P5_ENABLE_BO			((uint32_t)(1<<1))
#define PMU_REG_2P5_ENABLE_LINREG		((uint32_t)(1<<0))
#define PMU_REG_CORE_FET_ODRIVE			((uint32_t)(1<<29))
#define PMU_REG_CORE_RAMP_RATE(n)		((uint32_t)(((n) & 0x03) << 27))
#define PMU_REG_CORE_REG2_ADJ(n)		((uint32_t)(((n) & 0x0F) << 23))
#define PMU_REG_CORE_REG2_TARG(n)		((uint32_t)(((n) & 0x1F) << 18))
#define PMU_REG_CORE_REG1_ADJ(n)		((uint32_t)(((n) & 0x0F) << 14))
#define PMU_REG_CORE_REG1_TARG(n)		((uint32_t)(((n) & 0x1F) << 9))
#define PMU_REG_CORE_REG0_ADJ(n)		((uint32_t)(((n) & 0x0F) << 5))
#define PMU_REG_CORE_REG0_TARG(n)		((uint32_t)(((n) & 0x1F) << 0))
#define PMU_MISC0_VID_PLL_PREDIV		((uint32_t)(1<<31))
#define PMU_MISC0_XTAL_24M_PWD			((uint32_t)(1<<30))
#define PMU_MISC0_RTC_XTAL_SOURCE		((uint32_t)(1<<29))
#define PMU_MISC0_CLKGATE_DELAY(n)		((uint32_t)(((n) & 0x07) << 26))
#define PMU_MISC0_CLKGATE_CTRL			((uint32_t)(1<<25))
#define PMU_MISC0_OSC_XTALOK_EN			((uint32_t)(1<<16))
#define PMU_MISC0_OSC_XTALOK			((uint32_t)(1<<15))
#define PMU_MISC0_OSC_I(n)			((uint32_t)(((n) & 0x03) << 13))
#define PMU_MISC0_DISCON_HIGH_SNVS		((uint32_t)(1<<12))
#define PMU_MISC0_STOP_MODE_CONFIG(n)		((uint32_t)(((n) & 0x03) << 10))
#define PMU_MISC0_REFTOP_VBGUP			((uint32_t)(1<<7))
#define PMU_MISC0_REFTOP_VBGADJ(n)		((uint32_t)(((n) & 0x07) << 4))
#define PMU_MISC0_REFTOP_SELFBIASOFF		((uint32_t)(1<<3))
#define PMU_MISC0_REFTOP_PWD			((uint32_t)(1<<0))
#define PMU_MISC1_IRQ_DIG_BO			((uint32_t)(1<<31))
#define PMU_MISC1_IRQ_ANA_BO			((uint32_t)(1<<30))
#define PMU_MISC1_IRQ_TEMPHIGH			((uint32_t)(1<<29))
#define PMU_MISC1_IRQ_TEMPLOW			((uint32_t)(1<<28))
#define PMU_MISC1_IRQ_TEMPPANIC			((uint32_t)(1<<27))
#define PMU_MISC1_PFD_528_AUTOGATE_EN		((uint32_t)(1<<17))
#define PMU_MISC1_PFD_480_AUTOGATE_EN		((uint32_t)(1<<16))
#define PMU_MISC1_LVDSCLK2_IBEN			((uint32_t)(1<<13))
#define PMU_MISC1_LVDSCLK1_IBEN			((uint32_t)(1<<12))
#define PMU_MISC1_LVDSCLK2_OBEN			((uint32_t)(1<<11))
#define PMU_MISC1_LVDSCLK1_OBEN			((uint32_t)(1<<10))
#define PMU_MISC1_LVDS2_CLK_SEL(n)		((uint32_t)(((n) & 0x1F) << 5))
#define PMU_MISC1_LVDS1_CLK_SEL(n)		((uint32_t)(((n) & 0x1F) << 0))
#define PMU_MISC2_VIDEO_DIV(n)			((uint32_t)(((n) & 0x03) << 30))
#define PMU_MISC2_REG2_STEP_TIME(n)		((uint32_t)(((n) & 0x03) << 28))
#define PMU_MISC2_REG1_STEP_TIME(n)		((uint32_t)(((n) & 0x03) << 26))
#define PMU_MISC2_REG0_STEP_TIME(n)		((uint32_t)(((n) & 0x03) << 24))
#define PMU_MISC2_AUDIO_DIV_MSB			((uint32_t)(1<<23))
#define PMU_MISC2_REG2_OK			((uint32_t)(1<<22))
#define PMU_MISC2_REG2_ENABLE_BO		((uint32_t)(1<<21))
#define PMU_MISC2_REG2_BO_STATUS		((uint32_t)(1<<19))
#define PMU_MISC2_REG2_BO_OFFSET(n)		((uint32_t)(((n) & 0x07) << 16))
#define PMU_MISC2_AUDIO_DIV_LSB			((uint32_t)(1<<15))
#define PMU_MISC2_REG1_ENABLE_BO		((uint32_t)(1<<13))
#define PMU_MISC2_REG1_BO_STATUS		((uint32_t)(1<<11))
#define PMU_MISC2_REG1_BO_OFFSET(n)		((uint32_t)(((n) & 0x07) << 8))
#define PMU_MISC2_PLL3_DISABLE			((uint32_t)(1<<7))
#define PMU_MISC2_REG0_ENABLE_BO		((uint32_t)(1<<5))
#define PMU_MISC2_REG0_BO_STATUS		((uint32_t)(1<<3))
#define PMU_MISC2_REG0_BO_OFFSET(n)		((uint32_t)(((n) & 0x07) << 0))

// 36.8: page 1923
typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t CTRL_SET;
    volatile uint32_t CTRL_CLR;
    volatile uint32_t CTLR_TOG;
    volatile uint32_t STAT;
    volatile uint32_t STAT_SET;
    volatile uint32_t STAT_CLR;
    volatile uint32_t STAT_TOG;
    volatile uint32_t OUT_CTRL;
    volatile uint32_t OUT_CTRL_SET;
    volatile uint32_t OUT_CTRL_CLR;
    volatile uint32_t OUT_CTRL_TOG;
    volatile void*    OUT_BUF;
    volatile uint32_t unused1[3];
    volatile void*    OUT_BUF2;
    volatile uint32_t unused2[3];
    volatile uint32_t OUT_PITCH;
    volatile uint32_t unused3[3];
    volatile uint32_t OUT_LRC;
    volatile uint32_t unused4[3];
    volatile uint32_t OUT_PS_ULC;
    volatile uint32_t unused5[3];
    volatile uint32_t OUT_PS_LRC;
    volatile uint32_t unused6[3];
    volatile uint32_t OUT_AS_ULC;
    volatile uint32_t unused7[3];
    volatile uint32_t OUT_AS_LRC;
    volatile uint32_t unused8[3];
    volatile uint32_t PS_CTRL;
    volatile uint32_t PS_CTRL_SET;
    volatile uint32_t PS_CTRL_CLR;
    volatile uint32_t PS_CTRL_TOG;
    volatile void*    PS_BUF;
    volatile uint32_t unused9[3];
    volatile void*    PS_UBUF;
    volatile uint32_t unused10[3];
    volatile void*    PS_VBUF;
    volatile uint32_t unused11[3];
    volatile uint32_t PS_PITCH;
    volatile uint32_t unused12[3];
    volatile uint32_t PS_BACKGROUND;
    volatile uint32_t unused13[3];
    volatile uint32_t PS_SCALE;
    volatile uint32_t unused14[3];
    volatile uint32_t PS_OFFSET;
    volatile uint32_t unused15[3];
    volatile uint32_t PS_CLRKEYLOW;
    volatile uint32_t unused16[3];
    volatile uint32_t PS_CLRKEYHIGH;
    volatile uint32_t unused17[3];
    volatile uint32_t AS_CTRL;
    volatile uint32_t unused18[3];
    volatile void*    AS_BUF;
    volatile uint32_t unused19[3];
    volatile uint32_t AS_PITCH;
    volatile uint32_t unused20[3];
    volatile uint32_t AS_CLRKEYLOW;
    volatile uint32_t unused21[3];
    volatile uint32_t AS_CLRKEYHIGH;
    volatile uint32_t unused22[3];
    volatile uint32_t CSC1_COEF0;
    volatile uint32_t unused23[3];
    volatile uint32_t CSC1_COEF1;
    volatile uint32_t unused24[3];
    volatile uint32_t CSC1_COEF2;
    volatile uint32_t unused25[87];
    volatile uint32_t POWER;
    volatile uint32_t unused26[55];
    volatile uint32_t NEXT;
    volatile uint32_t unused27[15];
    volatile uint32_t PORTER_DUFF_CTRL;
} IMXRT_PXP_t;
#define IMXRT_PXP        (*(IMXRT_PXP_t *)IMXRT_PXP_ADDRESS)
#define PXP_CTRL            (IMXRT_PXP.CTRL)
#define PXP_CTRL_SET            (IMXRT_PXP.CTRL_SET)
#define PXP_CTRL_CLR            (IMXRT_PXP.CTRL_CLR)
#define PXP_CTRL_TOG            (IMXRT_PXP.CTRL_TOG)
#define PXP_STAT            (IMXRT_PXP.STAT)
#define PXP_STAT_SET            (IMXRT_PXP.STAT_SET)
#define PXP_STAT_CLR            (IMXRT_PXP.STAT_CLR)
#define PXP_STAT_TOG            (IMXRT_PXP.STAT_TOG)
#define PXP_OUT_CTRL            (IMXRT_PXP.OUT_CTRL)
#define PXP_OUT_CTRL_SET        (IMXRT_PXP.OUT_CTRL_SET)
#define PXP_OUT_CTRL_CLR        (IMXRT_PXP.OUT_CTRL_CLR)
#define PXP_OUT_CTRL_TOG        (IMXRT_PXP.OUT_CTRL_TOG)
#define PXP_OUT_BUF            (IMXRT_PXP.OUT_BUF)
#define PXP_OUT_BUF2            (IMXRT_PXP.OUT_BUF2)
#define PXP_OUT_PITCH            (IMXRT_PXP.OUT_PITCH)
#define PXP_OUT_LRC            (IMXRT_PXP.OUT_LRC)
#define PXP_OUT_PS_ULC            (IMXRT_PXP.OUT_PS_ULC)
#define PXP_OUT_PS_LRC            (IMXRT_PXP.OUT_PS_LRC)
#define PXP_OUT_AS_ULC            (IMXRT_PXP.OUT_AS_ULC)
#define PXP_OUT_AS_LRC            (IMXRT_PXP.OUT_AS_LRC)
#define PXP_PS_CTRL            (IMXRT_PXP.PS_CTRL)
#define PXP_PS_CTRL_SET            (IMXRT_PXP.PS_CTRL_SET)
#define PXP_PS_CTRL_CLR            (IMXRT_PXP.PS_CTRL_CLR)
#define PXP_PS_CTRL_TOG            (IMXRT_PXP.PS_CTRL_TOG)
#define PXP_PS_BUF            (IMXRT_PXP.PS_BUF)
#define PXP_PS_UBUF            (IMXRT_PXP.PS_UBUF)
#define PXP_PS_VBUF            (IMXRT_PXP.PS_VBUF)
#define PXP_PS_PITCH            (IMXRT_PXP.PS_PITCH)
#define PXP_PS_BACKGROUND_0        (IMXRT_PXP.PS_BACKGROUND)
#define PXP_PS_SCALE            (IMXRT_PXP.PS_SCALE)
#define PXP_PS_OFFSET            (IMXRT_PXP.PS_OFFSET)
#define PXP_PS_CLRKEYLOW_0        (IMXRT_PXP.PS_CLRKEYLOW)
#define PXP_PS_CLRKEYHIGH_0        (IMXRT_PXP.PS_CLRKEYHIGH)
#define PXP_AS_CTRL            (IMXRT_PXP.AS_CTRL)
#define PXP_AS_BUF            (IMXRT_PXP.AS_BUF)
#define PXP_AS_PITCH            (IMXRT_PXP.AS_PITCH)
#define PXP_AS_CLRKEYLOW_0        (IMXRT_PXP.AS_CLRKEYLOW)
#define PXP_AS_CLRKEYHIGH_0        (IMXRT_PXP.AS_CLRKEYHIGH)
#define PXP_CSC1_COEF0            (IMXRT_PXP.CSC1_COEF0)
#define PXP_CSC1_COEF1            (IMXRT_PXP.CSC1_COEF1)
#define PXP_CSC1_COEF2            (IMXRT_PXP.CSC1_COEF2)
#define PXP_POWER            (IMXRT_PXP.POWER)
#define PXP_NEXT            (IMXRT_PXP.NEXT)
#define PXP_PORTER_DUFF_CTRL        (IMXRT_PXP.PORTER_DUFF_CTRL)


#define PXP_ARGB8888                        0x0 //32-bit pixels with alpha
#define PXP_RGBA888                         0x1 //32-bit pixel with alpha at low 8 bits
#define PXP_RGB888                          0x4 //32-bit pixels without alpha (unpacked 24-bit format)
#define PXP_RGB888P                         0x5 //24-bit pixels (packed 24-bit format)
#define PXP_ARGB1555                        0x8 //16-bit pixels with alpha at low 1 bit
#define PXP_ARGB4444                        0x9 //16-bit pixels with alpha at low 4 bits
#define PXP_RGB555                          0xC //16-bit pixels without alpha
#define PXP_RGB444                          0xD //16-bit pixels without alpha
#define PXP_RGB565                          0xE //16-bit pixels without alpha
#define PXP_YUV1P444                        0x10 //32-bit pixels (1-plane XYUV unpacked)
#define PXP_UYVY1P422                       0x12 //16-bit pixels (1-plane U0,Y0,V0,Y1 interleaved bytes)
#define PXP_VYUY1P422                       0x13 //16-bit pixels (1-plane V0,Y0,U0,Y1 interleaved bytes)
#define PXP_Y8                              0x14 //8-bit monochrome pixels (1-plane Y luma output)
#define PXP_Y4                              0x15 //4-bit monochrome pixels (1-plane Y luma, 4 bit truncation)
#define PXP_YUV2P422                        0x18 //16-bit pixels (2-plane UV interleaved bytes)
#define PXP_YUV2P420                        0x19 //16-bit pixels (2-plane UV)
#define PXP_YVU2P422                        0x1A //16-bit pixels (2-plane VU interleaved bytes)
#define PXP_YVU2P420                        0x1B //16-bit pixels (2-plane VU)
#define PXP_YUV422                          0x1E //16-bit pixels (3-plane format)
#define PXP_YUV420                          0x1F //16-bit pixels (3-plane format)

#define PXP_MASKAS                          0x0
#define PXP_MASKNOTAS                       0x1
#define PXP_MASKASNOT                       0x2
#define PXP_MERGEAS                         0x3
#define PXP_MERGENOTAS                      0x4
#define PXP_MERGEASNOT                      0x5
#define PXP_NOTCOPYAS                       0x6
#define PXP_NOT                             0x7
#define PXP_NOTMASKAS                       0x8
#define PXP_NOTMERGEAS                      0x9
#define PXP_XORAS                           0xA
#define PXP_NOTXORAS                        0xB

#define PXP_CTRL_ENABLE                     ((uint32_t)(1))
#define PXP_CTRL_IRQ_ENABLE                 ((uint32_t)(1<<1))
#define PXP_CTRL_NEXT_IRQ_ENABLE            ((uint32_t)(1<<2))
#define PXP_CTRL_ENABLE_LCD_HANDSHAKE       ((uint32_t)(1<<4))
#define PXP_CTRL_ROTATE(n)                  ((uint32_t)(((n) & 0x03) << 8))
#define PXP_CTRL_HFLIP                      ((uint32_t)(1<<10))
#define PXP_CTRL_VFLIP                      ((uint32_t)(1<<11))
#define PXP_CTRL_ROT_POS                    ((uint32_t)(1<<22))
#define PXP_CTRL_BLOCK_SIZE                 ((uint32_t)(1<<23))
#define PXP_CTRL_EN_REPEAT                  ((uint32_t)(1<<28))
#define PXP_CTRL_CLKGATE                    ((uint32_t)(1<<30))
#define PXP_CTRL_SFTRST                     ((uint32_t)(1<<31))

#define PXP_STAT_IRQ                        ((uint32_t)(1))
#define PXP_STAT_AXI_WRITE_ERROR            ((uint32_t)(1<<1))
#define PXP_STAT_AXI_READ_ERROR             ((uint32_t)(1<<2))
#define PXP_STAT_NEXT_IRQ                   ((uint32_t)(1<<3))
#define PXP_STAT_AXI_ERROR_ID               ((uint32_t)((PXP_STAT>>4) & 0xF))
#define PXP_STAT_LUT_DMA_LOAD_DONE_IRQ      ((uint32_t)(1<<8))
#define PXP_STAT_BLOCKY                     ((uint32_t)((PXP_STAT>>16) & 0xFF))
#define PXP_STAT_BLOCKX                     ((uint32_t)((PXP_STAT>>24) & 0xFF))

#define PXP_OUT_CTRL_FORMAT(n)              ((uint32_t)(((n) & 0x1F)))
#define PXP_OUT_CTRL_INTERLACED_OUTPUT(n)   ((uint32_t)(((n) & 0x3) << 8))
#define PXP_OUT_CTRL_ALPHA_OUTPUT           ((uint32_t)(1<<23))
#define PXP_OUT_CTRL_ALPHA(n)               ((uint32_t)(((n) & 0xFF) << 24))

#define PXP_PS_CTRL_FORMAT(n)               ((uint32_t)(((n) & 0x1F)))
#define PXP_PS_CTRL_WB_SWAP                 ((uint32_t)(1<<5))
#define PXP_PS_CTRL_DECY(n)                 ((uint32_t)(((n) & 0x3) << 8))
#define PXP_PS_CTRL_DECX(n)                 ((uint32_t)(((n) & 0x3) << 10))

#define PXP_AS_CTRL_ALPHA_CTRL(n)           ((uint32_t)(((n) & 0x3) << 1))
#define PXP_AS_CTRL_ENABLE_COLORKEY         ((uint32_t)(1<<3))
#define PXP_AS_CTRL_FORMAT(n)               ((uint32_t)(((n) & 0xF) << 4))
#define PXP_AS_CTRL_ALPHA(n)                ((uint32_t)(((n) & 0xFF) << 8))
#define PXP_AS_CTRL_ROP(n)                  ((uint32_t)(((n) & 0xF) << 16))
#define PXP_AS_CTRL_ALPHA_INVERT            ((uint32_t)(1<<20))

#define PXP_COEF0_Y_OFFSET(n)               ((uint32_t)(((n) & 0x1FF)))
#define PXP_COEF0_UV_OFFSET(n)              ((uint32_t)(((n) & 0x1FF) << 9))
#define PXP_COEF0_C0(n)                     ((uint32_t)(((n) & 0x7FF) << 18))
#define PXP_COEF0_BYPASS                    ((uint32_t)(1<<30))
#define PXP_COEF0_YCBCR_MODE                ((uint32_t)(1<<31))

#define PXP_COEF1_C4(n)                     ((uint32_t)(((n) & 0x7FF)))
#define PXP_COEF1_C1(n)                     ((uint32_t)(((n) & 0x7FF) << 16))

#define PXP_COEF2_C3(n)                     ((uint32_t)(((n) & 0x7FF)))
#define PXP_COEF2_C2(n)                     ((uint32_t)(((n) & 0x7FF) << 16))

#define PXP_POWER_ROT_MEM_LP_STATE(n)       ((uint32_t)(((n) & 0x7) << 9))
#define PXP_POWER_CTRL(n)                   ((uint32_t)(((n) & 0xFFFFF) << 12))

#define PXP_NEXT_ENABLED                    ((uint32_t)(1))
#define PXP_NEXT_POINTER(n)                 ((uint32_t)(((n) & 0xFFFFFFFC)))

#define PXP_PORTER_DUFF_CTRL_PORTER_DUFF_ENABLE        ((uint32_t)(1))
#define PXP_PORTER_DUFF_CTRL_S0_S1_FACTOR_MODE(n)      ((uint32_t)(((n) & 0x3) << 1))
#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA_MODE(n)   ((uint32_t)(((n) & 0x3) << 3))
#define PXP_PORTER_DUFF_CTRL_S0_ALPHA_MODE             ((uint32_t)(1<<5))
#define PXP_PORTER_DUFF_CTRL_S0_COLOR_MODE             ((uint32_t)(1<<6))
#define PXP_PORTER_DUFF_CTRL_S1_S0_FACTOR_MODE(n)      ((uint32_t)(((n) & 0x3) << 8))
#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA_MODE(n)   ((uint32_t)(((n) & 0x3) << 10))
#define PXP_PORTER_DUFF_CTRL_S1_ALPHA_MODE             ((uint32_t)(1<<12))
#define PXP_PORTER_DUFF_CTRL_S1_COLOR_MODE             ((uint32_t)(1<<13))
#define PXP_PORTER_DUFF_CTRL_S0_GLOBAL_ALPHA(n)        ((uint32_t)(((n) & 0xFF) << 16))
#define PXP_PORTER_DUFF_CTRL_S1_GLOBAL_ALPHA(n)        ((uint32_t)(((n) & 0xFF) << 24))

#define PXP_PITCH(n)                        ((uint32_t)(((n) & 0xFFFF)))

#define PXP_XCOORD(n)                       ((uint32_t)(((n) & 0x3FFFFFFF) << 16))
#define PXP_YCOORD(n)                       ((uint32_t)(((n) & 0x3FFFFFFF)))

#define PXP_XSCALE(n)                       ((uint32_t)(((n) & 0x7FFFFFFF)))
#define PXP_YSCALE(n)                       ((uint32_t)(((n) & 0x7FFFFFFF) << 16))

#define PXP_XOFFSET(n)                      ((uint32_t)(((n) & 0xFFFFFFF)))
#define PXP_YOFFSET(n)                      ((uint32_t)(((n) & 0xFFFFFFF) << 16))

#define PXP_COLOR(n)                        ((uint32_t)(((n) & 0xFFFFFF)))

// 54.6: page 2990
typedef struct
{
   volatile uint16_t COMP1;
   volatile uint16_t COMP2;
   volatile uint16_t CAPT;
   volatile uint16_t LOAD;
   volatile uint16_t HOLD;
   volatile uint16_t CNTR;
   volatile uint16_t CTRL;
   volatile uint16_t SCTRL;
   volatile uint16_t CMPLD1;
   volatile uint16_t CMPLD2;
   volatile uint16_t CSCTRL;
   volatile uint16_t FILT;
   volatile uint16_t DMA;
   volatile uint16_t unused1[3];
} IMXRT_TMR_CH_t;
typedef struct
{
   union {
      IMXRT_TMR_CH_t CH[4];
      struct
      {
         volatile uint16_t unused2[15];
         volatile uint16_t ENBL;
      };
   };
} IMXRT_TMR_t;
#define IMXRT_TMR1		(*(IMXRT_TMR_t *)IMXRT_TMR1_ADDRESS)
#define TMR1_COMP10			(IMXRT_TMR1.CH[0].COMP1)
#define TMR1_COMP20			(IMXRT_TMR1.CH[0].COMP2)
#define TMR1_CAPT0			(IMXRT_TMR1.CH[0].CAPT)
#define TMR1_LOAD0			(IMXRT_TMR1.CH[0].LOAD)
#define TMR1_HOLD0			(IMXRT_TMR1.CH[0].HOLD)
#define TMR1_CNTR0			(IMXRT_TMR1.CH[0].CNTR)
#define TMR1_CTRL0			(IMXRT_TMR1.CH[0].CTRL)
#define TMR1_SCTRL0			(IMXRT_TMR1.CH[0].SCTRL)
#define TMR1_CMPLD10			(IMXRT_TMR1.CH[0].CMPLD1)
#define TMR1_CMPLD20			(IMXRT_TMR1.CH[0].CMPLD2)
#define TMR1_CSCTRL0			(IMXRT_TMR1.CH[0].CSCTRL)
#define TMR1_FILT0			(IMXRT_TMR1.CH[0].FILT)
#define TMR1_DMA0			(IMXRT_TMR1.CH[0].DMA)
#define TMR1_ENBL			(IMXRT_TMR1.ENBL)
#define TMR1_COMP11			(IMXRT_TMR1.CH[1].COMP1)
#define TMR1_COMP21			(IMXRT_TMR1.CH[1].COMP2)
#define TMR1_CAPT1			(IMXRT_TMR1.CH[1].CAPT)
#define TMR1_LOAD1			(IMXRT_TMR1.CH[1].LOAD)
#define TMR1_HOLD1			(IMXRT_TMR1.CH[1].HOLD)
#define TMR1_CNTR1			(IMXRT_TMR1.CH[1].CNTR)
#define TMR1_CTRL1			(IMXRT_TMR1.CH[1].CTRL)
#define TMR1_SCTRL1			(IMXRT_TMR1.CH[1].SCTRL)
#define TMR1_CMPLD11			(IMXRT_TMR1.CH[1].CMPLD1)
#define TMR1_CMPLD21			(IMXRT_TMR1.CH[1].CMPLD2)
#define TMR1_CSCTRL1			(IMXRT_TMR1.CH[1].CSCTRL)
#define TMR1_FILT1			(IMXRT_TMR1.CH[1].FILT)
#define TMR1_DMA1			(IMXRT_TMR1.CH[1].DMA)
#define TMR1_COMP12			(IMXRT_TMR1.CH[2].COMP1)
#define TMR1_COMP22			(IMXRT_TMR1.CH[2].COMP2)
#define TMR1_CAPT2			(IMXRT_TMR1.CH[2].CAPT)
#define TMR1_LOAD2			(IMXRT_TMR1.CH[2].LOAD)
#define TMR1_HOLD2			(IMXRT_TMR1.CH[2].HOLD)
#define TMR1_CNTR2			(IMXRT_TMR1.CH[2].CNTR)
#define TMR1_CTRL2			(IMXRT_TMR1.CH[2].CTRL)
#define TMR1_SCTRL2			(IMXRT_TMR1.CH[2].SCTRL)
#define TMR1_CMPLD12			(IMXRT_TMR1.CH[2].CMPLD1)
#define TMR1_CMPLD22			(IMXRT_TMR1.CH[2].CMPLD2)
#define TMR1_CSCTRL2			(IMXRT_TMR1.CH[2].CSCTRL)
#define TMR1_FILT2			(IMXRT_TMR1.CH[2].FILT)
#define TMR1_DMA2			(IMXRT_TMR1.CH[2].DMA)
#define TMR1_COMP13			(IMXRT_TMR1.CH[3].COMP1)
#define TMR1_COMP23			(IMXRT_TMR1.CH[3].COMP2)
#define TMR1_CAPT3			(IMXRT_TMR1.CH[3].CAPT)
#define TMR1_LOAD3			(IMXRT_TMR1.CH[3].LOAD)
#define TMR1_HOLD3			(IMXRT_TMR1.CH[3].HOLD)
#define TMR1_CNTR3			(IMXRT_TMR1.CH[3].CNTR)
#define TMR1_CTRL3			(IMXRT_TMR1.CH[3].CTRL)
#define TMR1_SCTRL3			(IMXRT_TMR1.CH[3].SCTRL)
#define TMR1_CMPLD13			(IMXRT_TMR1.CH[3].CMPLD1)
#define TMR1_CMPLD23			(IMXRT_TMR1.CH[3].CMPLD2)
#define TMR1_CSCTRL3			(IMXRT_TMR1.CH[3].CSCTRL)
#define TMR1_FILT3			(IMXRT_TMR1.CH[3].FILT)
#define TMR1_DMA3			(IMXRT_TMR1.CH[3].DMA)
#define IMXRT_TMR2		(*(IMXRT_TMR_t *)IMXRT_TMR2_ADDRESS)
#define TMR2_COMP10			(IMXRT_TMR2.CH[0].COMP1)
#define TMR2_COMP20			(IMXRT_TMR2.CH[0].COMP2)
#define TMR2_CAPT0			(IMXRT_TMR2.CH[0].CAPT)
#define TMR2_LOAD0			(IMXRT_TMR2.CH[0].LOAD)
#define TMR2_HOLD0			(IMXRT_TMR2.CH[0].HOLD)
#define TMR2_CNTR0			(IMXRT_TMR2.CH[0].CNTR)
#define TMR2_CTRL0			(IMXRT_TMR2.CH[0].CTRL)
#define TMR2_SCTRL0			(IMXRT_TMR2.CH[0].SCTRL)
#define TMR2_CMPLD10			(IMXRT_TMR2.CH[0].CMPLD1)
#define TMR2_CMPLD20			(IMXRT_TMR2.CH[0].CMPLD2)
#define TMR2_CSCTRL0			(IMXRT_TMR2.CH[0].CSCTRL)
#define TMR2_FILT0			(IMXRT_TMR2.CH[0].FILT)
#define TMR2_DMA0			(IMXRT_TMR2.CH[0].DMA)
#define TMR2_ENBL			(IMXRT_TMR2.ENBL)
#define TMR2_COMP11			(IMXRT_TMR2.CH[1].COMP1)
#define TMR2_COMP21			(IMXRT_TMR2.CH[1].COMP2)
#define TMR2_CAPT1			(IMXRT_TMR2.CH[1].CAPT)
#define TMR2_LOAD1			(IMXRT_TMR2.CH[1].LOAD)
#define TMR2_HOLD1			(IMXRT_TMR2.CH[1].HOLD)
#define TMR2_CNTR1			(IMXRT_TMR2.CH[1].CNTR)
#define TMR2_CTRL1			(IMXRT_TMR2.CH[1].CTRL)
#define TMR2_SCTRL1			(IMXRT_TMR2.CH[1].SCTRL)
#define TMR2_CMPLD11			(IMXRT_TMR2.CH[1].CMPLD1)
#define TMR2_CMPLD21			(IMXRT_TMR2.CH[1].CMPLD2)
#define TMR2_CSCTRL1			(IMXRT_TMR2.CH[1].CSCTRL)
#define TMR2_FILT1			(IMXRT_TMR2.CH[1].FILT)
#define TMR2_DMA1			(IMXRT_TMR2.CH[1].DMA)
#define TMR2_COMP12			(IMXRT_TMR2.CH[2].COMP1)
#define TMR2_COMP22			(IMXRT_TMR2.CH[2].COMP2)
#define TMR2_CAPT2			(IMXRT_TMR2.CH[2].CAPT)
#define TMR2_LOAD2			(IMXRT_TMR2.CH[2].LOAD)
#define TMR2_HOLD2			(IMXRT_TMR2.CH[2].HOLD)
#define TMR2_CNTR2			(IMXRT_TMR2.CH[2].CNTR)
#define TMR2_CTRL2			(IMXRT_TMR2.CH[2].CTRL)
#define TMR2_SCTRL2			(IMXRT_TMR2.CH[2].SCTRL)
#define TMR2_CMPLD12			(IMXRT_TMR2.CH[2].CMPLD1)
#define TMR2_CMPLD22			(IMXRT_TMR2.CH[2].CMPLD2)
#define TMR2_CSCTRL2			(IMXRT_TMR2.CH[2].CSCTRL)
#define TMR2_FILT2			(IMXRT_TMR2.CH[2].FILT)
#define TMR2_DMA2			(IMXRT_TMR2.CH[2].DMA)
#define TMR2_COMP13			(IMXRT_TMR2.CH[3].COMP1)
#define TMR2_COMP23			(IMXRT_TMR2.CH[3].COMP2)
#define TMR2_CAPT3			(IMXRT_TMR2.CH[3].CAPT)
#define TMR2_LOAD3			(IMXRT_TMR2.CH[3].LOAD)
#define TMR2_HOLD3			(IMXRT_TMR2.CH[3].HOLD)
#define TMR2_CNTR3			(IMXRT_TMR2.CH[3].CNTR)
#define TMR2_CTRL3			(IMXRT_TMR2.CH[3].CTRL)
#define TMR2_SCTRL3			(IMXRT_TMR2.CH[3].SCTRL)
#define TMR2_CMPLD13			(IMXRT_TMR2.CH[3].CMPLD1)
#define TMR2_CMPLD23			(IMXRT_TMR2.CH[3].CMPLD2)
#define TMR2_CSCTRL3			(IMXRT_TMR2.CH[3].CSCTRL)
#define TMR2_FILT3			(IMXRT_TMR2.CH[3].FILT)
#define TMR2_DMA3			(IMXRT_TMR2.CH[3].DMA)
#define IMXRT_TMR3		(*(IMXRT_TMR_t *)IMXRT_TMR3_ADDRESS)
#define TMR3_COMP10			(IMXRT_TMR3.CH[0].COMP1)
#define TMR3_COMP20			(IMXRT_TMR3.CH[0].COMP2)
#define TMR3_CAPT0			(IMXRT_TMR3.CH[0].CAPT)
#define TMR3_LOAD0			(IMXRT_TMR3.CH[0].LOAD)
#define TMR3_HOLD0			(IMXRT_TMR3.CH[0].HOLD)
#define TMR3_CNTR0			(IMXRT_TMR3.CH[0].CNTR)
#define TMR3_CTRL0			(IMXRT_TMR3.CH[0].CTRL)
#define TMR3_SCTRL0			(IMXRT_TMR3.CH[0].SCTRL)
#define TMR3_CMPLD10			(IMXRT_TMR3.CH[0].CMPLD1)
#define TMR3_CMPLD20			(IMXRT_TMR3.CH[0].CMPLD2)
#define TMR3_CSCTRL0			(IMXRT_TMR3.CH[0].CSCTRL)
#define TMR3_FILT0			(IMXRT_TMR3.CH[0].FILT)
#define TMR3_DMA0			(IMXRT_TMR3.CH[0].DMA)
#define TMR3_ENBL			(IMXRT_TMR3.ENBL)
#define TMR3_COMP11			(IMXRT_TMR3.CH[1].COMP1)
#define TMR3_COMP21			(IMXRT_TMR3.CH[1].COMP2)
#define TMR3_CAPT1			(IMXRT_TMR3.CH[1].CAPT)
#define TMR3_LOAD1			(IMXRT_TMR3.CH[1].LOAD)
#define TMR3_HOLD1			(IMXRT_TMR3.CH[1].HOLD)
#define TMR3_CNTR1			(IMXRT_TMR3.CH[1].CNTR)
#define TMR3_CTRL1			(IMXRT_TMR3.CH[1].CTRL)
#define TMR3_SCTRL1			(IMXRT_TMR3.CH[1].SCTRL)
#define TMR3_CMPLD11			(IMXRT_TMR3.CH[1].CMPLD1)
#define TMR3_CMPLD21			(IMXRT_TMR3.CH[1].CMPLD2)
#define TMR3_CSCTRL1			(IMXRT_TMR3.CH[1].CSCTRL)
#define TMR3_FILT1			(IMXRT_TMR3.CH[1].FILT)
#define TMR3_DMA1			(IMXRT_TMR3.CH[1].DMA)
#define TMR3_COMP12			(IMXRT_TMR3.CH[2].COMP1)
#define TMR3_COMP22			(IMXRT_TMR3.CH[2].COMP2)
#define TMR3_CAPT2			(IMXRT_TMR3.CH[2].CAPT)
#define TMR3_LOAD2			(IMXRT_TMR3.CH[2].LOAD)
#define TMR3_HOLD2			(IMXRT_TMR3.CH[2].HOLD)
#define TMR3_CNTR2			(IMXRT_TMR3.CH[2].CNTR)
#define TMR3_CTRL2			(IMXRT_TMR3.CH[2].CTRL)
#define TMR3_SCTRL2			(IMXRT_TMR3.CH[2].SCTRL)
#define TMR3_CMPLD12			(IMXRT_TMR3.CH[2].CMPLD1)
#define TMR3_CMPLD22			(IMXRT_TMR3.CH[2].CMPLD2)
#define TMR3_CSCTRL2			(IMXRT_TMR3.CH[2].CSCTRL)
#define TMR3_FILT2			(IMXRT_TMR3.CH[2].FILT)
#define TMR3_DMA2			(IMXRT_TMR3.CH[2].DMA)
#define TMR3_COMP13			(IMXRT_TMR3.CH[3].COMP1)
#define TMR3_COMP23			(IMXRT_TMR3.CH[3].COMP2)
#define TMR3_CAPT3			(IMXRT_TMR3.CH[3].CAPT)
#define TMR3_LOAD3			(IMXRT_TMR3.CH[3].LOAD)
#define TMR3_HOLD3			(IMXRT_TMR3.CH[3].HOLD)
#define TMR3_CNTR3			(IMXRT_TMR3.CH[3].CNTR)
#define TMR3_CTRL3			(IMXRT_TMR3.CH[3].CTRL)
#define TMR3_SCTRL3			(IMXRT_TMR3.CH[3].SCTRL)
#define TMR3_CMPLD13			(IMXRT_TMR3.CH[3].CMPLD1)
#define TMR3_CMPLD23			(IMXRT_TMR3.CH[3].CMPLD2)
#define TMR3_CSCTRL3			(IMXRT_TMR3.CH[3].CSCTRL)
#define TMR3_FILT3			(IMXRT_TMR3.CH[3].FILT)
#define TMR3_DMA3			(IMXRT_TMR3.CH[3].DMA)
#define IMXRT_TMR4		(*(IMXRT_TMR_t *)IMXRT_TMR4_ADDRESS)
#define TMR4_COMP10			(IMXRT_TMR4.CH[0].COMP1)
#define TMR4_COMP20			(IMXRT_TMR4.CH[0].COMP2)
#define TMR4_CAPT0			(IMXRT_TMR4.CH[0].CAPT)
#define TMR4_LOAD0			(IMXRT_TMR4.CH[0].LOAD)
#define TMR4_HOLD0			(IMXRT_TMR4.CH[0].HOLD)
#define TMR4_CNTR0			(IMXRT_TMR4.CH[0].CNTR)
#define TMR4_CTRL0			(IMXRT_TMR4.CH[0].CTRL)
#define TMR4_SCTRL0			(IMXRT_TMR4.CH[0].SCTRL)
#define TMR4_CMPLD10			(IMXRT_TMR4.CH[0].CMPLD1)
#define TMR4_CMPLD20			(IMXRT_TMR4.CH[0].CMPLD2)
#define TMR4_CSCTRL0			(IMXRT_TMR4.CH[0].CSCTRL)
#define TMR4_FILT0			(IMXRT_TMR4.CH[0].FILT)
#define TMR4_DMA0			(IMXRT_TMR4.CH[0].DMA)
#define TMR4_ENBL			(IMXRT_TMR4.ENBL)
#define TMR4_COMP11			(IMXRT_TMR4.CH[1].COMP1)
#define TMR4_COMP21			(IMXRT_TMR4.CH[1].COMP2)
#define TMR4_CAPT1			(IMXRT_TMR4.CH[1].CAPT)
#define TMR4_LOAD1			(IMXRT_TMR4.CH[1].LOAD)
#define TMR4_HOLD1			(IMXRT_TMR4.CH[1].HOLD)
#define TMR4_CNTR1			(IMXRT_TMR4.CH[1].CNTR)
#define TMR4_CTRL1			(IMXRT_TMR4.CH[1].CTRL)
#define TMR4_SCTRL1			(IMXRT_TMR4.CH[1].SCTRL)
#define TMR4_CMPLD11			(IMXRT_TMR4.CH[1].CMPLD1)
#define TMR4_CMPLD21			(IMXRT_TMR4.CH[1].CMPLD2)
#define TMR4_CSCTRL1			(IMXRT_TMR4.CH[1].CSCTRL)
#define TMR4_FILT1			(IMXRT_TMR4.CH[1].FILT)
#define TMR4_DMA1			(IMXRT_TMR4.CH[1].DMA)
#define TMR4_COMP12			(IMXRT_TMR4.CH[2].COMP1)
#define TMR4_COMP22			(IMXRT_TMR4.CH[2].COMP2)
#define TMR4_CAPT2			(IMXRT_TMR4.CH[2].CAPT)
#define TMR4_LOAD2			(IMXRT_TMR4.CH[2].LOAD)
#define TMR4_HOLD2			(IMXRT_TMR4.CH[2].HOLD)
#define TMR4_CNTR2			(IMXRT_TMR4.CH[2].CNTR)
#define TMR4_CTRL2			(IMXRT_TMR4.CH[2].CTRL)
#define TMR4_SCTRL2			(IMXRT_TMR4.CH[2].SCTRL)
#define TMR4_CMPLD12			(IMXRT_TMR4.CH[2].CMPLD1)
#define TMR4_CMPLD22			(IMXRT_TMR4.CH[2].CMPLD2)
#define TMR4_CSCTRL2			(IMXRT_TMR4.CH[2].CSCTRL)
#define TMR4_FILT2			(IMXRT_TMR4.CH[2].FILT)
#define TMR4_DMA2			(IMXRT_TMR4.CH[2].DMA)
#define TMR4_COMP13			(IMXRT_TMR4.CH[3].COMP1)
#define TMR4_COMP23			(IMXRT_TMR4.CH[3].COMP2)
#define TMR4_CAPT3			(IMXRT_TMR4.CH[3].CAPT)
#define TMR4_LOAD3			(IMXRT_TMR4.CH[3].LOAD)
#define TMR4_HOLD3			(IMXRT_TMR4.CH[3].HOLD)
#define TMR4_CNTR3			(IMXRT_TMR4.CH[3].CNTR)
#define TMR4_CTRL3			(IMXRT_TMR4.CH[3].CTRL)
#define TMR4_SCTRL3			(IMXRT_TMR4.CH[3].SCTRL)
#define TMR4_CMPLD13			(IMXRT_TMR4.CH[3].CMPLD1)
#define TMR4_CMPLD23			(IMXRT_TMR4.CH[3].CMPLD2)
#define TMR4_CSCTRL3			(IMXRT_TMR4.CH[3].CSCTRL)
#define TMR4_FILT3			(IMXRT_TMR4.CH[3].FILT)
#define TMR4_DMA3			(IMXRT_TMR4.CH[3].DMA)
#define TMR_CTRL_CM(n)				((uint16_t)(((n) & 0x07) << 13))
#define TMR_CTRL_PCS(n)				((uint16_t)(((n) & 0x0F) << 9))
#define TMR_CTRL_SCS(n)				((uint16_t)(((n) & 0x03) << 7))
#define TMR_CTRL_ONCE				((uint16_t)(1<<6))
#define TMR_CTRL_LENGTH				((uint16_t)(1<<5))
#define TMR_CTRL_DIR				((uint16_t)(1<<4))
#define TMR_CTRL_COINIT				((uint16_t)(1<<3))
#define TMR_CTRL_OUTMODE(n)			((uint16_t)(((n) & 0x07) << 0))
#define TMR_SCTRL_TCF				((uint16_t)(1<<15))
#define TMR_SCTRL_TCFIE				((uint16_t)(1<<14))
#define TMR_SCTRL_TOF				((uint16_t)(1<<13))
#define TMR_SCTRL_TOFIE				((uint16_t)(1<<12))
#define TMR_SCTRL_IEF				((uint16_t)(1<<11))
#define TMR_SCTRL_IEFIE				((uint16_t)(1<<10))
#define TMR_SCTRL_IPS				((uint16_t)(1<<9))
#define TMR_SCTRL_INPUT				((uint16_t)(1<<8))
#define TMR_SCTRL_CAPTURE_MODE(n)		((uint16_t)(((n) & 0x03) << 6))
#define TMR_SCTRL_MSTR				((uint16_t)(1<<5))
#define TMR_SCTRL_EEOF				((uint16_t)(1<<4))
#define TMR_SCTRL_VAL				((uint16_t)(1<<3))
#define TMR_SCTRL_FORCE				((uint16_t)(1<<2))
#define TMR_SCTRL_OPS				((uint16_t)(1<<1))
#define TMR_SCTRL_OEN				((uint16_t)(1<<0))
#define TMR_CSCTRL_DBG_EN(n)			((uint16_t)(((n) & 0x03) << 14))
#define TMR_CSCTRL_FAULT			((uint16_t)(1<<13))
#define TMR_CSCTRL_ALT_LOAD			((uint16_t)(1<<12))
#define TMR_CSCTRL_ROC				((uint16_t)(1<<11))
#define TMR_CSCTRL_TCI				((uint16_t)(1<<10))
#define TMR_CSCTRL_UP				((uint16_t)(1<<9))
#define TMR_CSCTRL_TCF2EN			((uint16_t)(1<<7))
#define TMR_CSCTRL_TCF1EN			((uint16_t)(1<<6))
#define TMR_CSCTRL_TCF2				((uint16_t)(1<<5))
#define TMR_CSCTRL_TCF1				((uint16_t)(1<<4))
#define TMR_CSCTRL_CL2(n)			((uint16_t)(((n) & 0x03) << 2))
#define TMR_CSCTRL_CL1(n)			((uint16_t)(((n) & 0x03) << 0))
#define TMR_FILT_FILT_CNT(n)			((uint16_t)(((n) & 0x07) << 8))
#define TMR_FILT_FILT_PER(n)			((uint16_t)(((n) & 0xFF) << 0))
#define TMR_DMA_CMPLD2DE			((uint16_t)(1<<2))
#define TMR_DMA_CMPLD1DE			((uint16_t)(1<<1))
#define TMR_DMA_IEFDE				((uint16_t)(1<<0))

// 38.5.1.1: page 1981
#define IMXRT_I2S1		(*(IMXRT_REGISTER32_t *)IMXRT_I2S1_ADDRESS)
#define I2S1_VERID			(IMXRT_I2S1.offset000)
#define I2S1_PARAM			(IMXRT_I2S1.offset004)
#define I2S1_TCSR			(IMXRT_I2S1.offset008)
#define I2S1_TCR1			(IMXRT_I2S1.offset00C)
#define I2S1_TCR2			(IMXRT_I2S1.offset010)
#define I2S1_TCR3			(IMXRT_I2S1.offset014)
#define I2S1_TCR4			(IMXRT_I2S1.offset018)
#define I2S1_TCR5			(IMXRT_I2S1.offset01C)
#define I2S1_TDR0			(IMXRT_I2S1.offset020)
#define I2S1_TDR1			(IMXRT_I2S1.offset024)
#define I2S1_TDR2			(IMXRT_I2S1.offset028)
#define I2S1_TDR3			(IMXRT_I2S1.offset02C)
#define I2S1_TFR0			(IMXRT_I2S1.offset040)
#define I2S1_TFR1			(IMXRT_I2S1.offset044)
#define I2S1_TFR2			(IMXRT_I2S1.offset048)
#define I2S1_TFR3			(IMXRT_I2S1.offset04C)
#define I2S1_TMR			(IMXRT_I2S1.offset060)
#define I2S1_RCSR			(IMXRT_I2S1.offset088)
#define I2S1_RCR1			(IMXRT_I2S1.offset08C)
#define I2S1_RCR2			(IMXRT_I2S1.offset090)
#define I2S1_RCR3			(IMXRT_I2S1.offset094)
#define I2S1_RCR4			(IMXRT_I2S1.offset098)
#define I2S1_RCR5			(IMXRT_I2S1.offset09C)
#define I2S1_RDR0			(IMXRT_I2S1.offset0A0)
#define I2S1_RDR1			(IMXRT_I2S1.offset0A4)
#define I2S1_RDR2			(IMXRT_I2S1.offset0A8)
#define I2S1_RDR3			(IMXRT_I2S1.offset0AC)
#define I2S1_RFR0			(IMXRT_I2S1.offset0C0)
#define I2S1_RFR1			(IMXRT_I2S1.offset0C4)
#define I2S1_RFR2			(IMXRT_I2S1.offset0C8)
#define I2S1_RFR3			(IMXRT_I2S1.offset0CC)
#define I2S1_RMR			(IMXRT_I2S1.offset0E0)
#define IMXRT_I2S2		(*(IMXRT_REGISTER32_t *)IMXRT_I2S2_ADDRESS)
#define I2S2_VERID			(IMXRT_I2S2.offset000)
#define I2S2_PARAM			(IMXRT_I2S2.offset004)
#define I2S2_TCSR			(IMXRT_I2S2.offset008)
#define I2S2_TCR1			(IMXRT_I2S2.offset00C)
#define I2S2_TCR2			(IMXRT_I2S2.offset010)
#define I2S2_TCR3			(IMXRT_I2S2.offset014)
#define I2S2_TCR4			(IMXRT_I2S2.offset018)
#define I2S2_TCR5			(IMXRT_I2S2.offset01C)
#define I2S2_TDR0			(IMXRT_I2S2.offset020)
#define I2S2_TDR1			(IMXRT_I2S2.offset024)
#define I2S2_TDR2			(IMXRT_I2S2.offset028)
#define I2S2_TDR3			(IMXRT_I2S2.offset02C)
#define I2S2_TFR0			(IMXRT_I2S2.offset040)
#define I2S2_TFR1			(IMXRT_I2S2.offset044)
#define I2S2_TFR2			(IMXRT_I2S2.offset048)
#define I2S2_TFR3			(IMXRT_I2S2.offset04C)
#define I2S2_TMR			(IMXRT_I2S2.offset060)
#define I2S2_RCSR			(IMXRT_I2S2.offset088)
#define I2S2_RCR1			(IMXRT_I2S2.offset08C)
#define I2S2_RCR2			(IMXRT_I2S2.offset090)
#define I2S2_RCR3			(IMXRT_I2S2.offset094)
#define I2S2_RCR4			(IMXRT_I2S2.offset098)
#define I2S2_RCR5			(IMXRT_I2S2.offset09C)
#define I2S2_RDR0			(IMXRT_I2S2.offset0A0)
#define I2S2_RDR1			(IMXRT_I2S2.offset0A4)
#define I2S2_RDR2			(IMXRT_I2S2.offset0A8)
#define I2S2_RDR3			(IMXRT_I2S2.offset0AC)
#define I2S2_RFR0			(IMXRT_I2S2.offset0C0)
#define I2S2_RFR1			(IMXRT_I2S2.offset0C4)
#define I2S2_RFR2			(IMXRT_I2S2.offset0C8)
#define I2S2_RFR3			(IMXRT_I2S2.offset0CC)
#define I2S2_RMR			(IMXRT_I2S2.offset0E0)
#define IMXRT_I2S3		(*(IMXRT_REGISTER32_t *)IMXRT_I2S3_ADDRESS)
#define I2S3_VERID			(IMXRT_I2S3.offset000)
#define I2S3_PARAM			(IMXRT_I2S3.offset004)
#define I2S3_TCSR			(IMXRT_I2S3.offset008)
#define I2S3_TCR1			(IMXRT_I2S3.offset00C)
#define I2S3_TCR2			(IMXRT_I2S3.offset010)
#define I2S3_TCR3			(IMXRT_I2S3.offset014)
#define I2S3_TCR4			(IMXRT_I2S3.offset018)
#define I2S3_TCR5			(IMXRT_I2S3.offset01C)
#define I2S3_TDR0			(IMXRT_I2S3.offset020)
#define I2S3_TDR1			(IMXRT_I2S3.offset024)
#define I2S3_TDR2			(IMXRT_I2S3.offset028)
#define I2S3_TDR3			(IMXRT_I2S3.offset02C)
#define I2S3_TFR0			(IMXRT_I2S3.offset040)
#define I2S3_TFR1			(IMXRT_I2S3.offset044)
#define I2S3_TFR2			(IMXRT_I2S3.offset048)
#define I2S3_TFR3			(IMXRT_I2S3.offset04C)
#define I2S3_TMR			(IMXRT_I2S3.offset060)
#define I2S3_RCSR			(IMXRT_I2S3.offset088)
#define I2S3_RCR1			(IMXRT_I2S3.offset08C)
#define I2S3_RCR2			(IMXRT_I2S3.offset090)
#define I2S3_RCR3			(IMXRT_I2S3.offset094)
#define I2S3_RCR4			(IMXRT_I2S3.offset098)
#define I2S3_RCR5			(IMXRT_I2S3.offset09C)
#define I2S3_RDR0			(IMXRT_I2S3.offset0A0)
#define I2S3_RDR1			(IMXRT_I2S3.offset0A4)
#define I2S3_RDR2			(IMXRT_I2S3.offset0A8)
#define I2S3_RDR3			(IMXRT_I2S3.offset0AC)
#define I2S3_RFR0			(IMXRT_I2S3.offset0C0)
#define I2S3_RFR1			(IMXRT_I2S3.offset0C4)
#define I2S3_RFR2			(IMXRT_I2S3.offset0C8)
#define I2S3_RFR3			(IMXRT_I2S3.offset0CC)
#define I2S3_RMR			(IMXRT_I2S3.offset0E0)

#define I2S_RCR1_RFW(n)			((uint32_t)n & 0x1f)	// Receive FIFO watermark
#define I2S_RCR2_DIV(n)			((uint32_t)n & 0xff)	// Bit clock divide by (DIV+1)*2
#define I2S_RCR2_BCD			((uint32_t)1<<24)	// Bit clock direction
#define I2S_RCR2_MSEL(n)		((uint32_t)(n & 3)<<26)	// MCLK select, 0=bus clock, 1=I2S0_MCLK
#define I2S_RCR2_SYNC(n)		((uint32_t)(n & 3)<<30)	// 0=async 1=sync with trasmitter
#define I2S_RCR3_RCE			((uint32_t)0x10000)	// receive channel enable
#define I2S_RCR3_RCE_2CH		((uint32_t)0x30000)
#define I2S_RCR3_RCE_3CH		((uint32_t)0x70000)
#define I2S_RCR3_RCE_4CH		((uint32_t)0xF0000)
#define I2S_RCR4_FSD			((uint32_t)1)		// Frame Sync Direction
#define I2S_RCR4_FSP			((uint32_t)1<<1)
#define I2S_RCR4_FSE			((uint32_t)8)		// Frame Sync Early
#define I2S_RCR4_MF			((uint32_t)0x10)	// MSB First
#define I2S_RCR4_SYWD(n)		((uint32_t)(n & 0x1f)<<8)	// Sync Width
#define I2S_RCR4_FRSZ(n)		((uint32_t)(n & 0x0f)<<16)	// Frame Size
#define I2S_RCR4_FCONT			((uint32_t)1<<28)	// FIFO Continue on Error
#define I2S_RCR5_FBT(n)			((uint32_t)(n & 0x1f)<<8)	// First Bit Shifted
#define I2S_RCR5_W0W(n)			((uint32_t)(n & 0x1f)<<16)	// Word 0 Width
#define I2S_RCR5_WNW(n)			((uint32_t)(n & 0x1f)<<24)	// Word N Width
#define I2S_RCR2_BCP			((uint32_t)1<<25)
#define I2S_RCSR_RE			((uint32_t)0x80000000)	// Receiver Enable
#define I2S_RCSR_FR			((uint32_t)0x02000000)	// FIFO Reset
#define I2S_RCSR_FRDE			((uint32_t)0x00000001)	// FIFO Request DMA Enable
#define I2S_RCSR_BCE			((uint32_t)0x10000000)	// Bit Clock Enable
#define I2S_TCR1_RFW(n)			((uint32_t)n & 0x1f)	// Receive FIFO watermark
#define I2S_TCR2_DIV(n)			((uint32_t)n & 0xff)	// Bit clock divide by (DIV+1)*2
#define I2S_TCR2_BCD			((uint32_t)1<<24)	// Bit clock direction
#define I2S_TCR2_MSEL(n)		((uint32_t)(n & 3)<<26)	// MCLK select, 0=bus clock, 1=I2S0_MCLK
#define I2S_TCR2_SYNC(n)		((uint32_t)(n & 3)<<30)	// 0=async 1=sync with receiver
#define I2S_TCR3_TCE			((uint32_t)0x10000)	// receive channel enable
#define I2S_TCR3_TCE_2CH		((uint32_t)0x30000)
#define I2S_TCR3_TCE_3CH		((uint32_t)0x70000)
#define I2S_TCR3_TCE_4CH		((uint32_t)0xF0000)
#define I2S_TCR4_FSD			((uint32_t)1)		// Frame Sync Direction
#define I2S_TCR4_FSP			((uint32_t)1<<1)
#define I2S_TCR4_FSE			((uint32_t)8)		// Frame Sync Early
#define I2S_TCR4_MF			((uint32_t)0x10)	// MSB First
#define I2S_TCR4_SYWD(n)		((uint32_t)(n & 0x1f)<<8)	// Sync Width
#define I2S_TCR4_FRSZ(n)		((uint32_t)(n & 0x0f)<<16)	// Frame Size
#define I2S_TCR4_FCONT			((uint32_t)1<<28)	// FIFO Continue on Error
#define I2S_TCR5_FBT(n)			((uint32_t)(n & 0x1f)<<8) 	// First Bit Shifted
#define I2S_TCR5_W0W(n)			((uint32_t)(n & 0x1f)<<16)	// Word 0 Width
#define I2S_TCR5_WNW(n)			((uint32_t)(n & 0x1f)<<24)	// Word N Width
#define I2S_TCR2_BCP			((uint32_t)1<<25)
#define I2S_TCSR_TE			((uint32_t)0x80000000)		// Receiver Enable
#define I2S_TCSR_BCE			((uint32_t)0x10000000)	// Bit Clock Enable
#define I2S_TCSR_FR			((uint32_t)0x02000000)	// FIFO Reset
#define I2S_TCSR_FRDE			((uint32_t)0x00000001)	// FIFO Request DMA Enable





// 25.4.1.1: page 1385
#define IMXRT_SEMC		(*(IMXRT_REGISTER32_t *)IMXRT_SEMC_ADDRESS)
#define SEMC_MCR			(IMXRT_SEMC.offset000)
#define SEMC_IOCR			(IMXRT_SEMC.offset004)
#define SEMC_BMCR0			(IMXRT_SEMC.offset008)
#define SEMC_BMCR1			(IMXRT_SEMC.offset00C)
#define SEMC_BR0			(IMXRT_SEMC.offset010)
#define SEMC_BR1			(IMXRT_SEMC.offset014)
#define SEMC_BR2			(IMXRT_SEMC.offset018)
#define SEMC_BR3			(IMXRT_SEMC.offset01C)
#define SEMC_BR4			(IMXRT_SEMC.offset020)
#define SEMC_BR5			(IMXRT_SEMC.offset024)
#define SEMC_BR6			(IMXRT_SEMC.offset028)
#define SEMC_BR7			(IMXRT_SEMC.offset02C)
#define SEMC_BR8			(IMXRT_SEMC.offset030)
#define SEMC_INTEN			(IMXRT_SEMC.offset038)
#define SEMC_INTR			(IMXRT_SEMC.offset03C)
#define SEMC_SDRAMCR0			(IMXRT_SEMC.offset040)
#define SEMC_SDRAMCR1			(IMXRT_SEMC.offset044)
#define SEMC_SDRAMCR2			(IMXRT_SEMC.offset048)
#define SEMC_SDRAMCR3			(IMXRT_SEMC.offset04C)
#define SEMC_NANDCR0			(IMXRT_SEMC.offset050)
#define SEMC_NANDCR1			(IMXRT_SEMC.offset054)
#define SEMC_NANDCR2			(IMXRT_SEMC.offset058)
#define SEMC_NANDCR3			(IMXRT_SEMC.offset05C)
#define SEMC_ORCR0			(IMXRT_SEMC.offset060)
#define SEMC_ORCR1			(IMXRT_SEMC.offset064)
#define SEMC_ORCR2			(IMXRT_SEMC.offset068)
#define SEMC_ORCR3			(IMXRT_SEMC.offset06C)
#define SEMC_SRAMCR0			(IMXRT_SEMC.offset070)
#define SEMC_SRAMCR1			(IMXRT_SEMC.offset074)
#define SEMC_SRAMCR2			(IMXRT_SEMC.offset078)
#define SEMC_SRAMCR3			(IMXRT_SEMC.offset07C)
#define SEMC_DBICR0			(IMXRT_SEMC.offset080)
#define SEMC_DBICR1			(IMXRT_SEMC.offset084)
#define SEMC_IPCR0			(IMXRT_SEMC.offset090)
#define SEMC_IPCR1			(IMXRT_SEMC.offset094)
#define SEMC_IPCR2			(IMXRT_SEMC.offset098)
#define SEMC_IPCMD			(IMXRT_SEMC.offset09C)
#define SEMC_IPTXDAT			(IMXRT_SEMC.offset0A0)
#define SEMC_IPRXDAT			(IMXRT_SEMC.offset0B0)
#define SEMC_STS0			(IMXRT_SEMC.offset0C0)
#define SEMC_STS1			(IMXRT_SEMC.offset0C4)
#define SEMC_STS2			(IMXRT_SEMC.offset0C8)
#define SEMC_STS3			(IMXRT_SEMC.offset0CC)
#define SEMC_STS4			(IMXRT_SEMC.offset0D0)
#define SEMC_STS5			(IMXRT_SEMC.offset0D4)
#define SEMC_STS6			(IMXRT_SEMC.offset0D8)
#define SEMC_STS7			(IMXRT_SEMC.offset0DC)
#define SEMC_STS8			(IMXRT_SEMC.offset0E0)
#define SEMC_STS9			(IMXRT_SEMC.offset0E4)
#define SEMC_STS10			(IMXRT_SEMC.offset0E8)
#define SEMC_STS11			(IMXRT_SEMC.offset0EC)
#define SEMC_STS12			(IMXRT_SEMC.offset0F0)
#define SEMC_STS13			(IMXRT_SEMC.offset0F4)
#define SEMC_STS14			(IMXRT_SEMC.offset0F8)
#define SEMC_STS15			(IMXRT_SEMC.offset0FC)

// 20.6.1: page 1242
#define IMXRT_SNVS		(*(IMXRT_REGISTER32_t *)IMXRT_SNVS_ADDRESS)
#define SNVS_HPLR			(IMXRT_SNVS.offset000)
#define SNVS_HPCOMR			(IMXRT_SNVS.offset004)
#define SNVS_HPCR			(IMXRT_SNVS.offset008)
#define SNVS_HPSICR			(IMXRT_SNVS.offset00C)
#define SNVS_HPSVCR			(IMXRT_SNVS.offset010)
#define SNVS_HPSR			(IMXRT_SNVS.offset014)
#define SNVS_HPSVSR			(IMXRT_SNVS.offset018)
#define SNVS_HPHACIVR			(IMXRT_SNVS.offset01C)
#define SNVS_HPHACR			(IMXRT_SNVS.offset020)
#define SNVS_HPRTCMR			(IMXRT_SNVS.offset024)
#define SNVS_HPRTCLR			(IMXRT_SNVS.offset028)
#define SNVS_HPTAMR			(IMXRT_SNVS.offset02C)
#define SNVS_HPTALR			(IMXRT_SNVS.offset030)
#define SNVS_LPLR			(IMXRT_SNVS.offset034)
#define SNVS_LPCR			(IMXRT_SNVS.offset038)
#define SNVS_LPMKCR			(IMXRT_SNVS.offset03C)
#define SNVS_LPSVCR			(IMXRT_SNVS.offset040)
#define SNVS_LPTDCR			(IMXRT_SNVS.offset048)
#define SNVS_LPSR			(IMXRT_SNVS.offset04C)
#define SNVS_LPSRTCMR			(IMXRT_SNVS.offset050)
#define SNVS_LPSRTCLR			(IMXRT_SNVS.offset054)
#define SNVS_LPTAR			(IMXRT_SNVS.offset058)
#define SNVS_LPSMCMR			(IMXRT_SNVS.offset05C)
#define SNVS_LPSMCLR			(IMXRT_SNVS.offset060)
#define SNVS_LPPGDR			(IMXRT_SNVS.offset064)
#define SNVS_LPGPR			(IMXRT_SNVS.offset068)
#define SNVS_LPGPR0                     (IMXRT_SNVS.offset100)
#define SNVS_LPGPR1                     (IMXRT_SNVS.offset104)
#define SNVS_LPGPR2                     (IMXRT_SNVS.offset108)
#define SNVS_LPGPR3                     (IMXRT_SNVS.offset10C)
#define IMXRT_SNVS_b		(*(IMXRT_REGISTER32_t *)(IMXRT_SNVS_ADDRESS+0x800))
#define SNVS_HPVIDR1			(IMXRT_SNVS_b.offset3F8)
#define SNVS_HPVIDR2			(IMXRT_SNVS_b.offset3FC)
#define SNVS_HPCR_BTN_MASK		((uint32_t)(1 << 27))
#define SNVS_HPCR_BTN_CONFIG(n)		((uint32_t)(((n) & 0x07) << 24))
#define SNVS_HPCR_HP_TS			((uint32_t)(1 << 16))
#define SNVS_HPCR_HPCALB_VAL(n)		((uint32_t)(((n) & 0x1F) << 10))
#define SNVS_HPCR_HPCALB_EN		((uint32_t)(1 << 8))
#define SNVS_HPCR_PI_FREQ(n)		((uint32_t)(((n) & 0x0F) << 4))
#define SNVS_HPCR_PI_EN			((uint32_t)(1 << 3))
#define SNVS_HPCR_DIS_PI		((uint32_t)(1 << 2))
#define SNVS_HPCR_HPTA_EN		((uint32_t)(1 << 1))
#define SNVS_HPCR_RTC_EN		((uint32_t)(1 << 0))
#define SNVS_DEFAULT_PGD_VALUE		(0x41736166U)
#define SNVS_LPCR_SRTC_ENV		((uint32_t)(1 << 0))
#define SNVS_LPCR_MC_ENV		((uint32_t)(1 << 2))
#define SNVS_LPCR_LPWUI_EN		((uint32_t)(1 << 3))
#define SNVS_LPCR_DP_EN			((uint32_t)(1 << 5))
#define SNVS_LPCR_TOP			((uint32_t)(1 << 6))
#define SNVS_LPCR_PWR_GLITCH_EN		((uint32_t)(1 << 7))
#define SNVS_LPCR_BTN_PRESS_TIME(n)	((uint32_t)(((n) & 0x03) << 16))
#define SNVS_LPCR_DEBOUNCE(n)		((uint32_t)(((n) & 0x03) << 18))
#define SNVS_LPCR_ON_TIME(n)		((uint32_t)(((n) & 0x03) << 20))
#define SNVS_LPCR_PK_EN			((uint32_t)(1 << 22))
#define SNVS_LPCR_PK_OVERRIDE		((uint32_t)(1 << 23))
#define SNVS_LPCR_GPR_Z_DIS             ((uint32_t)(1 << 24))

// 40.6: page 2035
#define IMXRT_SPDIF		(*(IMXRT_REGISTER32_t *)IMXRT_SPDIF_ADDRESS)
#define SPDIF_SCR			(IMXRT_SPDIF.offset000)
#define SPDIF_SRCD			(IMXRT_SPDIF.offset004)
#define SPDIF_SRPC			(IMXRT_SPDIF.offset008)
#define SPDIF_SIE			(IMXRT_SPDIF.offset00C)
#define SPDIF_SIS			(IMXRT_SPDIF.offset010)
#define SPDIF_SIC			(IMXRT_SPDIF.offset010)
#define SPDIF_SRL			(IMXRT_SPDIF.offset014)
#define SPDIF_SRR			(IMXRT_SPDIF.offset018)
#define SPDIF_SRCSH			(IMXRT_SPDIF.offset01C)
#define SPDIF_SRCSL			(IMXRT_SPDIF.offset020)
#define SPDIF_SRU			(IMXRT_SPDIF.offset024)
#define SPDIF_SRQ			(IMXRT_SPDIF.offset028)
#define SPDIF_STL			(IMXRT_SPDIF.offset02C)
#define SPDIF_STR			(IMXRT_SPDIF.offset030)
#define SPDIF_STCSCH			(IMXRT_SPDIF.offset034)
#define SPDIF_STCSCL			(IMXRT_SPDIF.offset038)
#define SPDIF_SRFM			(IMXRT_SPDIF.offset044)
#define SPDIF_STC			(IMXRT_SPDIF.offset050)
#define SPDIF_SCR_RXFIFO_CTR		((uint32_t)(1 << 23))
#define SPDIF_SCR_RXFIFO_OFF_ON		((uint32_t)(1 << 22))
#define SPDIF_SCR_RXFIFO_RST		((uint32_t)(1 << 21))
#define SPDIF_SCR_RXFIFOFULL_SEL(n)	((uint32_t)(((n) & 0x03) << 19))
#define SPDIF_SCR_RXAUTOSYNC		((uint32_t)(1 << 18))
#define SPDIF_SCR_TXAUTOSYNC		((uint32_t)(1 << 17))
#define SPDIF_SCR_TXFIFOEMPTY_SEL(n)	((uint32_t)(((n) & 0x03) << 15))
#define SPDIF_SCR_LOW_POWER		((uint32_t)(1 << 13))
#define SPDIF_SCR_SOFT_RESET		((uint32_t)(1 << 12))
#define SPDIF_SCR_TXFIFO_CTRL(n)	((uint32_t)(((n) & 0x03) << 10))
#define SPDIF_SCR_DMA_RX_EN		((uint32_t)(1 << 9))
#define SPDIF_SCR_DMA_TX_EN		((uint32_t)(1 << 8))
#define SPDIF_SCR_VALCTRL		((uint32_t)(1 << 5))
#define SPDIF_SCR_TXSEL(n)		((uint32_t)(((n) & 0x07) << 2))
#define SPDIF_SCR_USRC_SEL(n)		((uint32_t)(((n) & 0x03) << 0))
#define SPDIF_SRCD_USYNCMODE		((uint32_t)(1 << 1))
#define SPDIF_SRPC_CLKSRC_SEL(n)	((uint32_t)(((n) & 0x0f) << 7))
#define SPDIF_SRPC_LOCK			((uint32_t)(1 << 6))
#define SPDIF_SRPC_GAINSEL(n)		((uint32_t)(((n) & 0x07) << 3))
#define SPDIF_SIE_LOCK			((uint32_t)(1 << 20))
#define SPDIF_SIE_TXUNOV		((uint32_t)(1 << 19))
#define SPDIF_SIE_TXRESYN		((uint32_t)(1 << 18))
#define SPDIF_SIE_CNEW			((uint32_t)(1 << 17))
#define SPDIF_SIE_VALNOGOOD		((uint32_t)(1 << 16))
#define SPDIF_SIE_SYMERR		((uint32_t)(1 << 15))
#define SPDIF_SIE_BITERR		((uint32_t)(1 << 14))
#define SPDIF_SIE_URXFUL		((uint32_t)(1 << 10))
#define SPDIF_SIE_URXOV			((uint32_t)(1 << 9))
#define SPDIF_SIE_QRXFUL		((uint32_t)(1 << 8))
#define SPDIF_SIE_QRXOV			((uint32_t)(1 << 7))
#define SPDIF_SIE_UQSYNC		((uint32_t)(1 << 6))
#define SPDIF_SIE_UQERR			((uint32_t)(1 << 5))
#define SPDIF_SIE_RXFIFOUNOV		((uint32_t)(1 << 4))
#define SPDIF_SIE_RXFIFORESYN		((uint32_t)(1 << 3))
#define SPDIF_SIE_LOCKLOSS		((uint32_t)(1 << 2))
#define SPDIF_SIE_TXEM			((uint32_t)(1 << 1))
#define SPDIF_SIE_RXFIFOFUL		((uint32_t)(1 << 0))
#define SPDIF_SIS_LOCK			((uint32_t)(1 << 20))
#define SPDIF_SIS_TXUNOV		((uint32_t)(1 << 19))
#define SPDIF_SIS_TXRESYN		((uint32_t)(1 << 18))
#define SPDIF_SIS_CNEW			((uint32_t)(1 << 17))
#define SPDIF_SIS_VALNOGOOD		((uint32_t)(1 << 16))
#define SPDIF_SIS_SYMERR		((uint32_t)(1 << 15))
#define SPDIF_SIS_BITERR		((uint32_t)(1 << 14))
#define SPDIF_SIS_URXFUL		((uint32_t)(1 << 10))
#define SPDIF_SIS_URXOV			((uint32_t)(1 << 9))
#define SPDIF_SIS_QRXFUL		((uint32_t)(1 << 8))
#define SPDIF_SIS_QRXOV			((uint32_t)(1 << 7))
#define SPDIF_SIS_UQSYNC		((uint32_t)(1 << 6))
#define SPDIF_SIS_UQERR			((uint32_t)(1 << 5))
#define SPDIF_SIS_RXFIFOUNOV		((uint32_t)(1 << 4))
#define SPDIF_SIS_RXFIFORESYN		((uint32_t)(1 << 3))
#define SPDIF_SIS_LOCKLOSS		((uint32_t)(1 << 2))
#define SPDIF_SIS_TXEM			((uint32_t)(1 << 1))
#define SPDIF_SIS_RXFIFOFUL		((uint32_t)(1 << 0))
#define SPDIF_SIC_LOCK			((uint32_t)(1 << 20))
#define SPDIF_SIC_TXUNOV		((uint32_t)(1 << 19))
#define SPDIF_SIC_TXRESYN		((uint32_t)(1 << 18))
#define SPDIF_SIC_CNEW			((uint32_t)(1 << 17))
#define SPDIF_SIC_VALNOGOOD		((uint32_t)(1 << 16))
#define SPDIF_SIC_SYMERR		((uint32_t)(1 << 15))
#define SPDIF_SIC_BITERR		((uint32_t)(1 << 14))
#define SPDIF_SIC_URXFUL		((uint32_t)(1 << 10))
#define SPDIF_SIC_URXOV			((uint32_t)(1 << 9))
#define SPDIF_SIC_QRXOV			((uint32_t)(1 << 7))
#define SPDIF_SIC_UQSYNC		((uint32_t)(1 << 6))
#define SPDIF_SIC_UQERR			((uint32_t)(1 << 5))
#define SPDIF_SIC_RXFIFOUNOV		((uint32_t)(1 << 4))
#define SPDIF_SIC_RXFIFORESYN		((uint32_t)(1 << 3))
#define SPDIF_SIC_LOCKLOSS		((uint32_t)(1 << 2))
#define SPDIF_STC_SYSCLK_DF(n)		((uint32_t)(((n) & 0x1ff) << 11))
#define SPDIF_STC_TXCLK_SOURCE(n)	((uint32_t)(((n) & 0x07) << 8))
#define SPDIF_STC_TX_ALL_CLK_EN		((uint32_t)(1 << 7))
#define SPDIF_STC_TXCLK_DF(n)		((uint32_t)(((n) & 0x7f) << 0))

// 21.8: page 1284
#define IMXRT_SRC		(*(IMXRT_REGISTER32_t *)IMXRT_SRC_ADDRESS)
#define SRC_SCR				(IMXRT_SRC.offset000)
#define SRC_SBMR1			(IMXRT_SRC.offset004)
#define SRC_SRSR			(IMXRT_SRC.offset008)
#define SRC_SBMR2			(IMXRT_SRC.offset01C)
#define SRC_GPR5			(IMXRT_SRC.offset030)
/* 
These register are used by the ROM code and should not be used by application software 
#define SRC_GPR1			(IMXRT_SRC.offset020) 
#define SRC_GPR2			(IMXRT_SRC.offset024)
#define SRC_GPR3			(IMXRT_SRC.offset028)
#define SRC_GPR4			(IMXRT_SRC.offset02C)
#define SRC_GPR5			(IMXRT_SRC.offset030)
#define SRC_GPR6			(IMXRT_SRC.offset034)
#define SRC_GPR7			(IMXRT_SRC.offset038)
#define SRC_GPR8			(IMXRT_SRC.offset03C)
#define SRC_GPR9			(IMXRT_SRC.offset040)
#define SRC_GPR10			(IMXRT_SRC.offset044)
*/
#define SRC_SCR_MASK_WDOG3_RST(n)	((uint32_t)(((n) & 0x0f) << 28))
#define SRC_SCR_DBG_RST_MSK_PG		((uint32_t)(1 << 25))
#define SRC_SCR_CORE0_DBG_RST		((uint32_t)(1 << 17))
#define SRC_SCR_CORE0_RST		((uint32_t)(1 << 13))
#define SRC_SCR_MASK_WDOG_RST(n)	((uint32_t)(((n) & 0x0f) << 7))
#define SRC_SBMR1_BOOT_CFG4(n)		((uint32_t)(((n) & 0xff) << 24))
#define SRC_SBMR1_BOOT_CFG3(n)		((uint32_t)(((n) & 0xff) << 16))
#define SRC_SBMR1_BOOT_CFG2(n)		((uint32_t)(((n) & 0xff) << 8))
#define SRC_SBMR1_BOOT_CFG1(n)		((uint32_t)(((n) & 0xff) << 0))
#define SRC_SRSR_TEMPSENSE_RST_B	((uint32_t)(1 << 8))
#define SRC_SRSR_WDOG3_RST_B		((uint32_t)(1 << 7))
#define SRC_SRSR_JTAG_SW_RST		((uint32_t)(1 << 6))
#define SRC_SRSR_JTAG_RST_B		((uint32_t)(1 << 5))
#define SRC_SRSR_WDOG_RST_B		((uint32_t)(1 << 4))
#define SRC_SRSR_IPP_USER_RESET_B	((uint32_t)(1 << 3))
#define SRC_SRSR_CSU_RESET_B		((uint32_t)(1 << 2))
#define SRC_SRSR_LOCKUP_SYSRESETREQ	((uint32_t)(1 << 1))
#define SRC_SRSR_IPP_RESET_B		((uint32_t)(1 << 0))
#define SRC_SBMR2_BMOD(n)		((uint32_t)(((n) & 0x03) << 24))
#define SRC_SBMR2_BT_FUSE_SEL		((uint32_t)(1 << 4))
#define SRC_SBMR2_DIR_BT_DIS		((uint32_t)(1 << 3))
#define SRC_SBMR2_SEC_CONFIG(n)		((uint32_t)(((n) & 0x03) << 0))

// 19.4: page 1224
#define IMXRT_TEMPMON		(*(IMXRT_REGISTER32_t *)IMXRT_TEMPMON_ADDRESS)
#define TEMPMON_TEMPSENSE0          (IMXRT_TEMPMON.offset000)
#define TEMPMON_TEMPSENSE0_SET		(IMXRT_TEMPMON.offset004)
#define TEMPMON_TEMPSENSE0_CLR		(IMXRT_TEMPMON.offset008)
#define TEMPMON_TEMPSENSE0_TOG		(IMXRT_TEMPMON.offset00C)
#define TEMPMON_TEMPSENSE1		    (IMXRT_TEMPMON.offset010)
#define TEMPMON_TEMPSENSE1_SET		(IMXRT_TEMPMON.offset014)
#define TEMPMON_TEMPSENSE1_CLR		(IMXRT_TEMPMON.offset018)
#define TEMPMON_TEMPSENSE1_TOG		(IMXRT_TEMPMON.offset01C)
#define TEMPMON_TEMPSENSE2		    (IMXRT_TEMPMON.offset110)
#define TEMPMON_TEMPSENSE2_SET		(IMXRT_TEMPMON.offset114)
#define TEMPMON_TEMPSENSE2_CLR		(IMXRT_TEMPMON.offset118)
#define TEMPMON_TEMPSENSE2_TOG		(IMXRT_TEMPMON.offset11C)
#define TEMPMON_CTRL0_ALARM_VALUE(n)	((uint32_t)(((n) & 0x0fff) << 20))
#define TEMPMON_CTRL0_TEMP_CNT(n)	((uint32_t)(((n) & 0x0fff) << 8))
#define TEMPMON_CTRL0_FINISHED		((uint32_t)(1 << 2))
#define TEMPMON_CTRL0_MEASURE_TEMP	((uint32_t)(1 << 1))
#define TEMPMON_CTRL0_POWER_DOWN	((uint32_t)(1 << 0))
#define TEMPMON_CTRL1_MEASURE_FREQ(n)	((uint32_t)(((n) & 0xffff) << 0))
#define TEMPMON_CTRL2_PANIC_ALARM_VALUE(n)	((uint32_t)(((n) & 0x0fff) << 16))
#define TEMPMON_CTRL2_LOW_ALARM_VALUE(n)	((uint32_t)(((n) & 0x0fff) << 0))

#define IMXRT_TRNG		(*(IMXRT_REGISTER32_t *)IMXRT_TRNG_ADDRESS)
#define TRNG_MCTL			(IMXRT_TRNG.offset000)
#define TRNG_SCMISC			(IMXRT_TRNG.offset004)
#define TRNG_PKRRNG			(IMXRT_TRNG.offset008)
#define TRNG_PKRMAX			(IMXRT_TRNG.offset00C)
#define TRNG_PKRSQ			(IMXRT_TRNG.offset00C)
#define TRNG_SDCTL			(IMXRT_TRNG.offset010)
#define TRNG_SBLIM			(IMXRT_TRNG.offset014)
#define TRNG_TOTSAM			(IMXRT_TRNG.offset014)
#define TRNG_FRQMIN			(IMXRT_TRNG.offset018)
#define TRNG_FRQCNT			(IMXRT_TRNG.offset01C)
#define TRNG_FRQMAX			(IMXRT_TRNG.offset01C)
#define TRNG_SCMC			(IMXRT_TRNG.offset020)
#define TRNG_SCML			(IMXRT_TRNG.offset020)
#define TRNG_SCR1C			(IMXRT_TRNG.offset024)
#define TRNG_SCR1L			(IMXRT_TRNG.offset024)
#define TRNG_SCR2C			(IMXRT_TRNG.offset028)
#define TRNG_SCR2L			(IMXRT_TRNG.offset028)
#define TRNG_SCR3C			(IMXRT_TRNG.offset02C)
#define TRNG_SCR3L			(IMXRT_TRNG.offset02C)
#define TRNG_SCR4C			(IMXRT_TRNG.offset030)
#define TRNG_SCR4L			(IMXRT_TRNG.offset030)
#define TRNG_SCR5C			(IMXRT_TRNG.offset034)
#define TRNG_SCR5L			(IMXRT_TRNG.offset034)
#define TRNG_SCR6PC			(IMXRT_TRNG.offset038)
#define TRNG_SCR6PL			(IMXRT_TRNG.offset038)
#define TRNG_STATUS			(IMXRT_TRNG.offset03C)
#define TRNG_ENT0			(IMXRT_TRNG.offset040)
#define TRNG_ENT1			(IMXRT_TRNG.offset044)
#define TRNG_ENT2			(IMXRT_TRNG.offset048)
#define TRNG_ENT3			(IMXRT_TRNG.offset04C)
#define TRNG_ENT4			(IMXRT_TRNG.offset050)
#define TRNG_ENT5			(IMXRT_TRNG.offset054)
#define TRNG_ENT6			(IMXRT_TRNG.offset058)
#define TRNG_ENT7			(IMXRT_TRNG.offset05C)
#define TRNG_ENT8			(IMXRT_TRNG.offset060)
#define TRNG_ENT9			(IMXRT_TRNG.offset064)
#define TRNG_ENT10			(IMXRT_TRNG.offset068)
#define TRNG_ENT11			(IMXRT_TRNG.offset06C)
#define TRNG_ENT12			(IMXRT_TRNG.offset070)
#define TRNG_ENT13			(IMXRT_TRNG.offset074)
#define TRNG_ENT14			(IMXRT_TRNG.offset078)
#define TRNG_ENT15			(IMXRT_TRNG.offset07C)
#define TRNG_PKRCNT10			(IMXRT_TRNG.offset080)
#define TRNG_PKRCNT32			(IMXRT_TRNG.offset084)
#define TRNG_PKRCNT54			(IMXRT_TRNG.offset088)
#define TRNG_PKRCNT76			(IMXRT_TRNG.offset08C)
#define TRNG_PKRCNT98			(IMXRT_TRNG.offset090)
#define TRNG_PKRCNTBA			(IMXRT_TRNG.offset094)
#define TRNG_PKRCNTDC			(IMXRT_TRNG.offset098)
#define TRNG_PKRCNTFE			(IMXRT_TRNG.offset09C)
#define TRNG_SEC_CFG			(IMXRT_TRNG.offset0A0)
#define TRNG_INT_CTRL			(IMXRT_TRNG.offset0A4)
#define TRNG_INT_MASK			(IMXRT_TRNG.offset0A8)
#define TRNG_INT_STATUS			(IMXRT_TRNG.offset0AC)
#define TRNG_VID1			(IMXRT_TRNG.offset0F0)
#define TRNG_MCTL_PRGM			((uint32_t)(1 << 16))
#define TRNG_MCTL_LRUN_CONT		((uint32_t)(1 << 14))
#define TRNG_MCTL_TSTOP_OK		((uint32_t)(1 << 13))
#define TRNG_MCTL_ERR			((uint32_t)(1 << 12))
#define TRNG_MCTL_TST_OUT		((uint32_t)(1 << 11))
#define TRNG_MCTL_ENT_VAL		((uint32_t)(1 << 10))
#define TRNG_MCTL_FCT_VAL		((uint32_t)(1 << 9))
#define TRNG_MCTL_FCT_FAIL		((uint32_t)(1 << 8))
#define TRNG_MCTL_FOR_SCLK		((uint32_t)(1 << 7))
#define TRNG_MCTL_RST_DEF		((uint32_t)(1 << 6))
#define TRNG_MCTL_TRNG_ACC		((uint32_t)(1 << 5))
#define TRNG_MCTL_OSC_DIV(n)		((uint32_t)(((n) & 0x03) << 2))
#define TRNG_MCTL_SAMP_MODE(n)		((uint32_t)(((n) & 0x03) << 0))
#define TRNG_SCMISC_RTY_CT(n)		((uint32_t)(((n) & 0x0F) << 16))
#define TRNG_SCMISC_LRUN_MAX(n)		((uint32_t)(((n) & 0xFF) << 0))
#define TRNG_SDCTL_ENT_DLY(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define TRNG_SDCTL_SAMP_SIZE(n)		((uint32_t)(((n) & 0xFFFF) << 0))
#define TRNG_SCML_MONO_RNG(n)		((uint32_t)(((n) & 0xFFFF) << 16))
#define TRNG_SCML_MONO_MAX(n)		((uint32_t)(((n) & 0xFFFF) << 0))
#define TRNG_SCR1L_RUN1_RNG(n)		((uint32_t)(((n) & 0x7FFF) << 16))
#define TRNG_SCR1L_RUN1_MAX(n)		((uint32_t)(((n) & 0x7FFF) << 0))
#define TRNG_SCR2L_RUN2_RNG(n)		((uint32_t)(((n) & 0x3FFF) << 16))
#define TRNG_SCR2L_RUN2_MAX(n)		((uint32_t)(((n) & 0x3FFF) << 0))
#define TRNG_SCR3L_RUN3_RNG(n)		((uint32_t)(((n) & 0x1FFF) << 16))
#define TRNG_SCR3L_RUN3_MAX(n)		((uint32_t)(((n) & 0x1FFF) << 0))
#define TRNG_SCR4L_RUN4_RNG(n)		((uint32_t)(((n) & 0x0FFF) << 16))
#define TRNG_SCR4L_RUN4_MAX(n)		((uint32_t)(((n) & 0x0FFF) << 0))
#define TRNG_SCR5L_RUN5_RNG(n)		((uint32_t)(((n) & 0x07FF) << 16))
#define TRNG_SCR5L_RUN5_MAX(n)		((uint32_t)(((n) & 0x07FF) << 0))
#define TRNG_SCR6PL_RUN6P_RNG(n)	((uint32_t)(((n) & 0x07FF) << 16))
#define TRNG_SCR6PL_RUN6P_MAX(n)	((uint32_t)(((n) & 0x07FF) << 0))
// defaults from NXP's SDK (fsl_trng.c)
#define TRNG_DEFAULT_ENTROPY_DELAY	3200
#define TRNG_DEFAULT_SAMPLE_SIZE	2500
#define TRNG_DEFAULT_SPARSE_BIT_LIMIT	63
#define TRNG_DEFAULT_RETRY_COUNT	1
#define TRNG_DEFAULT_RUN_MAX_LIMIT	34
#define TRNG_DEFAULT_MONOBIT_MAXIMUM	1384
#define TRNG_DEFAULT_MONOBIT_MINIMUM	(TRNG_DEFAULT_MONOBIT_MAXIMUM - 268)
#define TRNG_DEFAULT_RUNBIT1_MAXIMUM	405
#define TRNG_DEFAULT_RUNBIT1_MINIMUM	(TRNG_DEFAULT_RUNBIT1_MAXIMUM - 178)
#define TRNG_DEFAULT_RUNBIT2_MAXIMUM	220
#define TRNG_DEFAULT_RUNBIT2_MINIMUM	(TRNG_DEFAULT_RUNBIT2_MAXIMUM - 122)
#define TRNG_DEFAULT_RUNBIT3_MAXIMUM	125
#define TRNG_DEFAULT_RUNBIT3_MINIMUM	(TRNG_DEFAULT_RUNBIT3_MAXIMUM - 88)
#define TRNG_DEFAULT_RUNBIT4_MAXIMUM	75
#define TRNG_DEFAULT_RUNBIT4_MINIMUM	(TRNG_DEFAULT_RUNBIT4_MAXIMUM - 64)
#define TRNG_DEFAULT_RUNBIT5_MAXIMUM	47
#define TRNG_DEFAULT_RUNBIT5_MINIMUM	(TRNG_DEFAULT_RUNBIT5_MAXIMUM - 46)
#define TRNG_DEFAULT_RUNBIT6PLUS_MAXIMUM 47
#define TRNG_DEFAULT_RUNBIT6PLUS_MINIMUM (TRNG_DEFAULT_RUNBIT6PLUS_MAXIMUM - 46)
#define TRNG_DEFAULT_POKER_MAXIMUM	26912
#define TRNG_DEFAULT_POKER_MINIMUM	(TRNG_DEFAULT_POKER_MAXIMUM - 2467)
#define TRNG_DEFAULT_FREQUENCY_MAXIMUM	25600
#define TRNG_DEFAULT_FREQUENCY_MINIMUM	1600


// BEE definitions adapted from NXP SDK 2.8.0, MIMXRT1062.h, lines 3131-3430
//  For BEE documentation & example code, see NXP Application Note 12852.
//  To encrypt data for use with BEE, look for NXP's image_enc.exe program.
//  Partial source code for image_enc.exe can be found in this zip archive:
//   image_enc.zip  sha256sum 6856a757fb0a9e13e926e8d461e23863d78568acebb81b6f361650ea4e050a03
//   https://community.nxp.com/t5/i-MX-RT/image-enc2-zip-download/m-p/1174943#M10980
#define IMXRT_BEE		(*(IMXRT_REGISTER32_t *)IMXRT_BEE_ADDRESS)
#define BEE_CTRL			(IMXRT_BEE.offset000)
#define BEE_ADDR_OFFSET0		(IMXRT_BEE.offset004)
#define BEE_ADDR_OFFSET1		(IMXRT_BEE.offset008)
#define BEE_AES_KEY0_W0			(IMXRT_BEE.offset00C)
#define BEE_AES_KEY0_W1			(IMXRT_BEE.offset010)
#define BEE_AES_KEY0_W2			(IMXRT_BEE.offset014)
#define BEE_AES_KEY0_W3			(IMXRT_BEE.offset018)
#define BEE_STATUS			(IMXRT_BEE.offset01C)
#define BEE_CTR_NONCE0_W0		(IMXRT_BEE.offset020)
#define BEE_CTR_NONCE0_W1		(IMXRT_BEE.offset024)
#define BEE_CTR_NONCE0_W2		(IMXRT_BEE.offset028)
#define BEE_CTR_NONCE0_W3		(IMXRT_BEE.offset02C)
#define BEE_CTR_NONCE1_W0		(IMXRT_BEE.offset030)
#define BEE_CTR_NONCE1_W1		(IMXRT_BEE.offset034)
#define BEE_CTR_NONCE1_W2		(IMXRT_BEE.offset038)
#define BEE_CTR_NONCE1_W3		(IMXRT_BEE.offset03C)
#define BEE_REGION1_TOP			(IMXRT_BEE.offset040)
#define BEE_REGION1_BOT			(IMXRT_BEE.offset044)
#define BEE_CTRL_BEE_ENABLE			((uint32_t)(1 << 0))
#define BEE_CTRL_CTRL_CLK_EN			((uint32_t)(1 << 1))
#define BEE_CTRL_CTRL_SFTRST_N			((uint32_t)(1 << 2))
#define BEE_CTRL_KEY_VALID			((uint32_t)(1 << 4))
#define BEE_CTRL_KEY_REGION_SEL			((uint32_t)(1 << 5))
#define BEE_CTRL_AC_PROT_EN			((uint32_t)(1 << 6))
#define BEE_CTRL_LITTLE_ENDIAN			((uint32_t)(1 << 7))
#define BEE_CTRL_SECURITY_LEVEL_R0(n)		((uint32_t)(((n) & 0x03) << 8))
#define BEE_CTRL_CTRL_AES_MODE_R0(n)		((uint32_t)(((n) & 0x03) << 10))
#define BEE_CTRL_SECURITY_LEVEL_R1(n)		((uint32_t)(((n) & 0x03) << 12))
#define BEE_CTRL_CTRL_AES_MODE_R1(n)		((uint32_t)(((n) & 0x03) << 14))
#define BEE_CTRL_BEE_ENABLE_LOCK		((uint32_t)(1 << 16))
#define BEE_CTRL_CTRL_CLK_EN_LOCK		((uint32_t)(1 << 17))
#define BEE_CTRL_CTRL_SFTRST_N_LOCK		((uint32_t)(1 << 18))
#define BEE_CTRL_REGION1_ADDR_LOCK		((uint32_t)(1 << 19))
#define BEE_CTRL_KEY_VALID_LOCK			((uint32_t)(1 << 20))
#define BEE_CTRL_KEY_REGION_SEL_LOCK		((uint32_t)(1 << 21))
#define BEE_CTRL_AC_PROT_EN_LOCK		((uint32_t)(1 << 22))
#define BEE_CTRL_LITTLE_ENDIAN_LOCK		((uint32_t)(1 << 23))
#define BEE_CTRL_SECURITY_LEVEL_R0_LOCK(n)	((uint32_t)(((n) & 0x03) << 24))
#define BEE_CTRL_CTRL_AES_MODE_R0_LOCK		((uint32_t)(1 << 26))
#define BEE_CTRL_REGION0_KEY_LOCK		((uint32_t)(1 << 27))
#define BEE_CTRL_SECURITY_LEVEL_R1_LOCK(n)	((uint32_t)(((n) & 0x03) << 28))
#define BEE_CTRL_CTRL_AES_MODE_R1_LOCK		((uint32_t)(1 << 30))
#define BEE_CTRL_REGION1_KEY_LOCK		((uint32_t)(1 << 31))


// DCP definitions adapted from NXP SDK 2.8.0, MIMXRT1062.h, lines 11448-13123
#define IMXRT_DCP		(*(IMXRT_REGISTER32_t *)IMXRT_DCP_ADDRESS)
// TODO - help wanted here....


// 68.4: page 3406
#define IMXRT_TSC		(*(IMXRT_REGISTER32_t *)IMXRT_TSC_ADDRESS)
#define TSC_BASIC_SETTING		(IMXRT_TSC.offset000)
#define TSC_PS_INPUT_BUFFER_ADDR	(IMXRT_TSC.offset010)
#define TSC_FLOW_CONTROL		(IMXRT_TSC.offset020)
#define TSC_MEASEURE_VALUE		(IMXRT_TSC.offset030)
#define TSC_INT_EN			(IMXRT_TSC.offset040)
#define TSC_INT_SIG_EN			(IMXRT_TSC.offset050)
#define TSC_INT_STATUS			(IMXRT_TSC.offset060)
#define TSC_DEBUG_MODE			(IMXRT_TSC.offset070)
#define TSC_DEBUG_MODE2			(IMXRT_TSC.offset080)

// 42.5.1.1: page 2212
#define IMXRT_USB1		(*(IMXRT_REGISTER32_t *)IMXRT_USB1_ADDRESS)
#define USB1_ID				(IMXRT_USB1.offset000)
#define USB1_HWGENERAL			(IMXRT_USB1.offset004)
#define USB1_HWHOST			(IMXRT_USB1.offset008)
#define USB1_HWDEVICE			(IMXRT_USB1.offset00C)
#define USB1_HWTXBUF			(IMXRT_USB1.offset010)
#define USB1_HWRXBUF			(IMXRT_USB1.offset014)
#define USB1_GPTIMER0LD			(IMXRT_USB1.offset080)
#define USB1_GPTIMER0CTRL		(IMXRT_USB1.offset084)
#define USB1_GPTIMER1LD			(IMXRT_USB1.offset088)
#define USB1_GPTIMER1CTRL		(IMXRT_USB1.offset08C)
#define USB1_SBUSCFG			(IMXRT_USB1.offset090)
#define USB1_HCIVERSION			(IMXRT_USB1.offset100)
#define USB1_HCSPARAMS			(IMXRT_USB1.offset104)
#define USB1_HCCPARAMS			(IMXRT_USB1.offset108)
#define USB1_DCIVERSION			(IMXRT_USB1.offset120)
#define USB1_DCCPARAMS			(IMXRT_USB1.offset124)
#define USB1_USBCMD			(IMXRT_USB1.offset140)
#define USB1_USBSTS			(IMXRT_USB1.offset144)
#define USB1_USBINTR			(IMXRT_USB1.offset148)
#define USB1_FRINDEX			(IMXRT_USB1.offset14C)
#define USB1_PERIODICLISTBASE		(IMXRT_USB1.offset154)
#define USB1_DEVICEADDR			(IMXRT_USB1.offset154)
#define USB1_ASYNCLISTADDR		(IMXRT_USB1.offset158)
#define USB1_ENDPOINTLISTADDR		(IMXRT_USB1.offset158)
#define USB1_BURSTSIZE			(IMXRT_USB1.offset160)
#define USB1_TXFILLTUNING		(IMXRT_USB1.offset164)
#define USB1_ENDPTNAK			(IMXRT_USB1.offset178)
#define USB1_ENDPTNAKEN			(IMXRT_USB1.offset17C)
#define USB1_CONFIGFLAG			(IMXRT_USB1.offset180)
#define USB1_PORTSC1			(IMXRT_USB1.offset184)
#define USB1_OTGSC			(IMXRT_USB1.offset1A4)
#define USB1_USBMODE			(IMXRT_USB1.offset1A8)
#define USB1_ENDPTSETUPSTAT		(IMXRT_USB1.offset1AC)
#define USB1_ENDPTPRIME			(IMXRT_USB1.offset1B0)
#define USB1_ENDPTFLUSH			(IMXRT_USB1.offset1B4)
#define USB1_ENDPTSTATUS		(IMXRT_USB1.offset1B8)
#define USB1_ENDPTCOMPLETE		(IMXRT_USB1.offset1BC)
#define USB1_ENDPTCTRL0			(IMXRT_USB1.offset1C0)
#define USB1_ENDPTCTRL1			(IMXRT_USB1.offset1C4)
#define USB1_ENDPTCTRL2			(IMXRT_USB1.offset1C8)
#define USB1_ENDPTCTRL3			(IMXRT_USB1.offset1CC)
#define USB1_ENDPTCTRL4			(IMXRT_USB1.offset1D0)
#define USB1_ENDPTCTRL5			(IMXRT_USB1.offset1D4)
#define USB1_ENDPTCTRL6			(IMXRT_USB1.offset1D8)
#define USB1_ENDPTCTRL7			(IMXRT_USB1.offset1DC)
#define IMXRT_USB2		(*(IMXRT_REGISTER32_t *)IMXRT_USB2_ADDRESS)
#define USB2_ID				(IMXRT_USB2.offset000)
#define USB2_HWGENERAL			(IMXRT_USB2.offset004)
#define USB2_HWHOST			(IMXRT_USB2.offset008)
#define USB2_HWDEVICE			(IMXRT_USB2.offset00C)
#define USB2_HWTXBUF			(IMXRT_USB2.offset010)
#define USB2_HWRXBUF			(IMXRT_USB2.offset014)
#define USB2_GPTIMER0LD			(IMXRT_USB2.offset080)
#define USB2_GPTIMER0CTRL		(IMXRT_USB2.offset084)
#define USB2_GPTIMER1LD			(IMXRT_USB2.offset088)
#define USB2_GPTIMER1CTRL		(IMXRT_USB2.offset08C)
#define USB2_SBUSCFG			(IMXRT_USB2.offset090)
#define USB2_HCIVERSION			(IMXRT_USB2.offset100)
#define USB2_HCSPARAMS			(IMXRT_USB2.offset104)
#define USB2_HCCPARAMS			(IMXRT_USB2.offset108)
#define USB2_DCIVERSION			(IMXRT_USB2.offset120)
#define USB2_DCCPARAMS			(IMXRT_USB2.offset124)
#define USB2_USBCMD			(IMXRT_USB2.offset140)
#define USB2_USBSTS			(IMXRT_USB2.offset144)
#define USB2_USBINTR			(IMXRT_USB2.offset148)
#define USB2_FRINDEX			(IMXRT_USB2.offset14C)
#define USB2_PERIODICLISTBASE		(IMXRT_USB2.offset154)
#define USB2_DEVICEADDR			(IMXRT_USB2.offset154)
#define USB2_ASYNCLISTADDR		(IMXRT_USB2.offset158)
#define USB2_ENDPOINTLISTADDR		(IMXRT_USB2.offset158)
#define USB2_BURSTSIZE			(IMXRT_USB2.offset160)
#define USB2_TXFILLTUNING		(IMXRT_USB2.offset164)
#define USB2_ENDPTNAK			(IMXRT_USB2.offset178)
#define USB2_ENDPTNAKEN			(IMXRT_USB2.offset17C)
#define USB2_CONFIGFLAG			(IMXRT_USB2.offset180)
#define USB2_PORTSC1			(IMXRT_USB2.offset184)
#define USB2_OTGSC			(IMXRT_USB2.offset1A4)
#define USB2_USBMODE			(IMXRT_USB2.offset1A8)
#define USB2_ENDPTSETUPSTAT		(IMXRT_USB2.offset1AC)
#define USB2_ENDPTPRIME			(IMXRT_USB2.offset1B0)
#define USB2_ENDPTFLUSH			(IMXRT_USB2.offset1B4)
#define USB2_ENDPTSTATUS		(IMXRT_USB2.offset1B8)
#define USB2_ENDPTCOMPLETE		(IMXRT_USB2.offset1BC)
#define USB2_ENDPTCTRL0			(IMXRT_USB2.offset1C0)
#define USB2_ENDPTCTRL1			(IMXRT_USB2.offset1C4)
#define USB2_ENDPTCTRL2			(IMXRT_USB2.offset1C8)
#define USB2_ENDPTCTRL3			(IMXRT_USB2.offset1CC)
#define USB2_ENDPTCTRL4			(IMXRT_USB2.offset1D0)
#define USB2_ENDPTCTRL5			(IMXRT_USB2.offset1D4)
#define USB2_ENDPTCTRL6			(IMXRT_USB2.offset1D8)
#define USB2_ENDPTCTRL7			(IMXRT_USB2.offset1DC)
#define USB_USBCMD_ITC(n)			((uint32_t)(((n) & 0xFF) << 16))
#define USB_USBCMD_FS_2				((uint32_t)(1<<15))
#define USB_USBCMD_ATDTW			((uint32_t)(1<<14))
#define USB_USBCMD_SUTW				((uint32_t)(1<<13))
#define USB_USBCMD_ASPE				((uint32_t)(1<<11))
#define USB_USBCMD_ASP(n)			((uint32_t)(((n) & 0x03) << 8))
#define USB_USBCMD_IAA				((uint32_t)(1<<6))
#define USB_USBCMD_ASE				((uint32_t)(1<<5))
#define USB_USBCMD_PSE				((uint32_t)(1<<4))
#define USB_USBCMD_FS_1(n)			((uint32_t)(((n) & 0x03) << 2))
#define USB_USBCMD_RST				((uint32_t)(1<<1))
#define USB_USBCMD_RS				((uint32_t)(1<<0))
#define USB_USBSTS_TI1				((uint32_t)(1<<25))
#define USB_USBSTS_TI0				((uint32_t)(1<<24))
#define USB_USBSTS_NAKI				((uint32_t)(1<<16))
#define USB_USBSTS_AS				((uint32_t)(1<<15))
#define USB_USBSTS_PS				((uint32_t)(1<<14))
#define USB_USBSTS_RCL				((uint32_t)(1<<13))
#define USB_USBSTS_HCH				((uint32_t)(1<<12))
#define USB_USBSTS_ULPII			((uint32_t)(1<<10))
#define USB_USBSTS_SLI				((uint32_t)(1<<8))
#define USB_USBSTS_SRI				((uint32_t)(1<<7))
#define USB_USBSTS_URI				((uint32_t)(1<<6))
#define USB_USBSTS_AAI				((uint32_t)(1<<5))
#define USB_USBSTS_SEI				((uint32_t)(1<<4))
#define USB_USBSTS_FRI				((uint32_t)(1<<3))
#define USB_USBSTS_PCI				((uint32_t)(1<<2))
#define USB_USBSTS_UEI				((uint32_t)(1<<1))
#define USB_USBSTS_UI				((uint32_t)(1<<0))
#define USB_USBINTR_TIE1			((uint32_t)(1<<25))
#define USB_USBINTR_TIE0			((uint32_t)(1<<24))
#define USB_USBINTR_UPIE			((uint32_t)(1<<19))
#define USB_USBINTR_UAIE			((uint32_t)(1<<18))
#define USB_USBINTR_NAKE			((uint32_t)(1<<16))
#define USB_USBINTR_ULPIE			((uint32_t)(1<<10))
#define USB_USBINTR_SLE				((uint32_t)(1<<8))
#define USB_USBINTR_SRE				((uint32_t)(1<<7))
#define USB_USBINTR_URE				((uint32_t)(1<<6))
#define USB_USBINTR_AAE				((uint32_t)(1<<5))
#define USB_USBINTR_SEE				((uint32_t)(1<<4))
#define USB_USBINTR_FRE				((uint32_t)(1<<3))
#define USB_USBINTR_PCE				((uint32_t)(1<<2))
#define USB_USBINTR_UEE				((uint32_t)(1<<1))
#define USB_USBINTR_UE				((uint32_t)(1<<0))
#define USB_DEVICEADDR_USBADR(n)		((uint32_t)(((n) & 0x7F) << 25))
#define USB_DEVICEADDR_USBADRA			((uint32_t)(1<<24))
#define USB_PORTSC1_PTS_1(n)			((uint32_t)(((n) & 0x03) << 30))
#define USB_PORTSC1_STS				((uint32_t)(1<<29))
#define USB_PORTSC1_PTW				((uint32_t)(1<<28))
#define USB_PORTSC1_PSPD(n)			((uint32_t)(((n) & 0x03) << 26))
#define USB_PORTSC1_PTS_2			((uint32_t)(1<<25))
#define USB_PORTSC1_PFSC			((uint32_t)(1<<24))
#define USB_PORTSC1_PHCD			((uint32_t)(1<<23))
#define USB_PORTSC1_WKOC			((uint32_t)(1<<22))
#define USB_PORTSC1_WKDC			((uint32_t)(1<<21))
#define USB_PORTSC1_WKCN			((uint32_t)(1<<20))
#define USB_PORTSC1_PTC(n)			((uint32_t)(((n) & 0x0F) << 16))
#define USB_PORTSC1_PIC(n)			((uint32_t)(((n) & 0x03) << 14))
#define USB_PORTSC1_PO				((uint32_t)(1<<13))
#define USB_PORTSC1_PP				((uint32_t)(1<<12))
#define USB_PORTSC1_LS(n)			((uint32_t)(((n) & 0x03) << 10))
#define USB_PORTSC1_HSP				((uint32_t)(1<<9))
#define USB_PORTSC1_PR				((uint32_t)(1<<8))
#define USB_PORTSC1_SUSP			((uint32_t)(1<<7))
#define USB_PORTSC1_FPR				((uint32_t)(1<<6))
#define USB_PORTSC1_OCC				((uint32_t)(1<<5))
#define USB_PORTSC1_OCA				((uint32_t)(1<<4))
#define USB_PORTSC1_PEC				((uint32_t)(1<<3))
#define USB_PORTSC1_PE				((uint32_t)(1<<2))
#define USB_PORTSC1_CSC				((uint32_t)(1<<1))
#define USB_PORTSC1_CCS				((uint32_t)(1<<0))
#define USB_USBMODE_SDIS			((uint32_t)(1<<4))
#define USB_USBMODE_SLOM			((uint32_t)(1<<3))
#define USB_USBMODE_ES				((uint32_t)(1<<2))
#define USB_USBMODE_CM(n)			((uint32_t)(((n) & 0x03) << 0))
#define USB_USBMODE_CM_MASK			USB_USBMODE_CM(3)
#define USB_ENDPTCTRL_TXE			((uint32_t)(1<<23))
#define USB_ENDPTCTRL_TXR			((uint32_t)(1<<22))
#define USB_ENDPTCTRL_TXI			((uint32_t)(1<<21))
#define USB_ENDPTCTRL_TXT(n)			((uint32_t)(((n) & 0x03) << 18))
#define USB_ENDPTCTRL_TXD			((uint32_t)(1<<17))
#define USB_ENDPTCTRL_TXS			((uint32_t)(1<<16))
#define USB_ENDPTCTRL_RXE			((uint32_t)(1<<7))
#define USB_ENDPTCTRL_RXR			((uint32_t)(1<<6))
#define USB_ENDPTCTRL_RXI			((uint32_t)(1<<5))
#define USB_ENDPTCTRL_RXT(n)			((uint32_t)(((n) & 0x03) << 2))
#define USB_ENDPTCTRL_RXD			((uint32_t)(1<<1))
#define USB_ENDPTCTRL_RXS			((uint32_t)(1<<0))
#define USB_GPTIMERCTRL_GPTRUN			((uint32_t)(1<<31))
#define USB_GPTIMERCTRL_GPTRST			((uint32_t)(1<<30))
#define USB_GPTIMERCTRL_GPTMODE			((uint32_t)(1<<24))
#define USB_GPTIMERCTRL_GPTCNT(n)		((uint32_t)(((n) & 0xFFFFFF) << 0))

// 43.3: page 2474
#define IMXRT_USBPHY1		(*(IMXRT_REGISTER32_t *)IMXRT_USBPHY1_ADDRESS)
#define USBPHY1_PWD			(IMXRT_USBPHY1.offset000)
#define USBPHY1_PWD_SET			(IMXRT_USBPHY1.offset004)
#define USBPHY1_PWD_CLR			(IMXRT_USBPHY1.offset008)
#define USBPHY1_PWD_TOG			(IMXRT_USBPHY1.offset00C)
#define USBPHY1_TX			(IMXRT_USBPHY1.offset010)
#define USBPHY1_TX_SET			(IMXRT_USBPHY1.offset014)
#define USBPHY1_TX_CLR			(IMXRT_USBPHY1.offset018)
#define USBPHY1_TX_TOG			(IMXRT_USBPHY1.offset01C)
#define USBPHY1_RX			(IMXRT_USBPHY1.offset020)
#define USBPHY1_RX_SET			(IMXRT_USBPHY1.offset024)
#define USBPHY1_RX_CLR			(IMXRT_USBPHY1.offset028)
#define USBPHY1_RX_TOG			(IMXRT_USBPHY1.offset02C)
#define USBPHY1_CTRL			(IMXRT_USBPHY1.offset030)
#define USBPHY1_CTRL_SET		(IMXRT_USBPHY1.offset034)
#define USBPHY1_CTRL_CLR		(IMXRT_USBPHY1.offset038)
#define USBPHY1_CTRL_TOG		(IMXRT_USBPHY1.offset03C)
#define USBPHY1_STATUS			(IMXRT_USBPHY1.offset040)
#define USBPHY1_DEBUG			(IMXRT_USBPHY1.offset050)
#define USBPHY1_DEBUG_SET		(IMXRT_USBPHY1.offset054)
#define USBPHY1_DEBUG_CLR		(IMXRT_USBPHY1.offset058)
#define USBPHY1_DEBUG_TOG		(IMXRT_USBPHY1.offset05C)
#define USBPHY1_DEBUG0_STATUS		(IMXRT_USBPHY1.offset060)
#define USBPHY1_DEBUG1			(IMXRT_USBPHY1.offset070)
#define USBPHY1_DEBUG1_SET		(IMXRT_USBPHY1.offset074)
#define USBPHY1_DEBUG1_CLR		(IMXRT_USBPHY1.offset078)
#define USBPHY1_DEBUG1_TOG		(IMXRT_USBPHY1.offset07C)
#define USBPHY1_VERSION			(IMXRT_USBPHY1.offset080)
#define IMXRT_USBPHY2		(*(IMXRT_REGISTER32_t *)IMXRT_USBPHY2_ADDRESS)
#define USBPHY2_PWD			(IMXRT_USBPHY2.offset000)
#define USBPHY2_PWD_SET			(IMXRT_USBPHY2.offset004)
#define USBPHY2_PWD_CLR			(IMXRT_USBPHY2.offset008)
#define USBPHY2_PWD_TOG			(IMXRT_USBPHY2.offset00C)
#define USBPHY2_TX			(IMXRT_USBPHY2.offset010)
#define USBPHY2_TX_SET			(IMXRT_USBPHY2.offset014)
#define USBPHY2_TX_CLR			(IMXRT_USBPHY2.offset018)
#define USBPHY2_TX_TOG			(IMXRT_USBPHY2.offset01C)
#define USBPHY2_RX			(IMXRT_USBPHY2.offset020)
#define USBPHY2_RX_SET			(IMXRT_USBPHY2.offset024)
#define USBPHY2_RX_CLR			(IMXRT_USBPHY2.offset028)
#define USBPHY2_RX_TOG			(IMXRT_USBPHY2.offset02C)
#define USBPHY2_CTRL			(IMXRT_USBPHY2.offset030)
#define USBPHY2_CTRL_SET		(IMXRT_USBPHY2.offset034)
#define USBPHY2_CTRL_CLR		(IMXRT_USBPHY2.offset038)
#define USBPHY2_CTRL_TOG		(IMXRT_USBPHY2.offset03C)
#define USBPHY2_STATUS			(IMXRT_USBPHY2.offset040)
#define USBPHY2_DEBUG			(IMXRT_USBPHY2.offset050)
#define USBPHY2_DEBUG_SET		(IMXRT_USBPHY2.offset054)
#define USBPHY2_DEBUG_CLR		(IMXRT_USBPHY2.offset058)
#define USBPHY2_DEBUG_TOG		(IMXRT_USBPHY2.offset05C)
#define USBPHY2_DEBUG0_STATUS		(IMXRT_USBPHY2.offset060)
#define USBPHY2_DEBUG1			(IMXRT_USBPHY2.offset070)
#define USBPHY2_DEBUG1_SET		(IMXRT_USBPHY2.offset074)
#define USBPHY2_DEBUG1_CLR		(IMXRT_USBPHY2.offset078)
#define USBPHY2_DEBUG1_TOG		(IMXRT_USBPHY2.offset07C)
#define USBPHY2_VERSION			(IMXRT_USBPHY2.offset080)
#define USBPHY_PWD_RXPWDRX			((uint32_t)(1<<20))
#define USBPHY_PWD_RXPWDDIFF			((uint32_t)(1<<19))
#define USBPHY_PWD_RXPWD1PT1			((uint32_t)(1<<18))
#define USBPHY_PWD_RXPWDENV			((uint32_t)(1<<17))
#define USBPHY_PWD_TXPWDV2I			((uint32_t)(1<<12))
#define USBPHY_PWD_TXPWDIBIAS			((uint32_t)(1<<11))
#define USBPHY_PWD_TXPWDFS			((uint32_t)(1<<10))
#define USBPHY_TX_USBPHY_TX_EDGECTRL(n)		((uint32_t)(((n) & 0x07) << 26))
#define USBPHY_TX_TXCAL45DP(n)			((uint32_t)(((n) & 0x0F) << 16))
#define USBPHY_TX_TXCAL45DN(n)			((uint32_t)(((n) & 0x0F) << 8))
#define USBPHY_TX_D_CAL(n)			((uint32_t)(((n) & 0x0F) << 0))
#define USBPHY_RX_RXDBYPASS			((uint32_t)(1<<22))
#define USBPHY_RX_DISCONADJ(n)			((uint32_t)(((n) & 0x07) << 4))
#define USBPHY_RX_ENVADJ(n)			((uint32_t)(((n) & 0x07) << 0))
#define USBPHY_CTRL_SFTRST			((uint32_t)(1<<31))
#define USBPHY_CTRL_CLKGATE			((uint32_t)(1<<30))
#define USBPHY_CTRL_UTMI_SUSPENDM		((uint32_t)(1<<29))
#define USBPHY_CTRL_HOST_FORCE_LS_SE0		((uint32_t)(1<<28))
#define USBPHY_CTRL_OTG_ID_VALUE		((uint32_t)(1<<27))
#define USBPHY_CTRL_FSDLL_RST_EN		((uint32_t)(1<<24))
#define USBPHY_CTRL_ENVBUSCHG_WKUP		((uint32_t)(1<<23))
#define USBPHY_CTRL_ENIDCHG_WKUP		((uint32_t)(1<<22))
#define USBPHY_CTRL_ENDPDMCHG_WKUP		((uint32_t)(1<<21))
#define USBPHY_CTRL_ENAUTOCLR_PHY_PWD		((uint32_t)(1<<20))
#define USBPHY_CTRL_ENAUTOCLR_CLKGATE		((uint32_t)(1<<19))
#define USBPHY_CTRL_ENAUTO_PWRON_PLL		((uint32_t)(1<<18))
#define USBPHY_CTRL_WAKEUP_IRQ			((uint32_t)(1<<17))
#define USBPHY_CTRL_ENIRQWAKEUP			((uint32_t)(1<<16))
#define USBPHY_CTRL_ENUTMILEVEL3		((uint32_t)(1<<15))
#define USBPHY_CTRL_ENUTMILEVEL2		((uint32_t)(1<<14))
#define USBPHY_CTRL_DATA_ON_LRADC		((uint32_t)(1<<13))
#define USBPHY_CTRL_DEVPLUGIN_IRQ		((uint32_t)(1<<12))
#define USBPHY_CTRL_ENIRQDEVPLUGIN		((uint32_t)(1<<11))
#define USBPHY_CTRL_RESUME_IRQ			((uint32_t)(1<<10))
#define USBPHY_CTRL_ENIRQRESUMEDETECT		((uint32_t)(1<<9))
#define USBPHY_CTRL_RESUMEIRQSTICKY		((uint32_t)(1<<8))
#define USBPHY_CTRL_ENOTGIDDETECT		((uint32_t)(1<<7))
#define USBPHY_CTRL_OTG_ID_CHG_IRQ		((uint32_t)(1<<6))
#define USBPHY_CTRL_DEVPLUGIN_POLARITY		((uint32_t)(1<<5))
#define USBPHY_CTRL_ENDEVPLUGINDETECT		((uint32_t)(1<<4))
#define USBPHY_CTRL_HOSTDISCONDETECT_IRQ	((uint32_t)(1<<3))
#define USBPHY_CTRL_ENIRQHOSTDISCON		((uint32_t)(1<<2))
#define USBPHY_CTRL_ENHOSTDISCONDETECT		((uint32_t)(1<<1))
#define USBPHY_CTRL_ENOTG_ID_CHG_IRQ		((uint32_t)(1<<0))

// 26.9.1.1: page 1553
#define IMXRT_USDHC1		(*(IMXRT_REGISTER32_t *)IMXRT_USDHC1_ADDRESS)
#define USDHC1_DS_ADDR			(IMXRT_USDHC1.offset000)
#define USDHC1_BLK_ATT			(IMXRT_USDHC1.offset004)
#define USDHC1_CMD_ARG			(IMXRT_USDHC1.offset008)
#define USDHC1_CMD_XFR_TYP		(IMXRT_USDHC1.offset00C)
#define USDHC1_CMD_RSP0			(IMXRT_USDHC1.offset010)
#define USDHC1_CMD_RSP1			(IMXRT_USDHC1.offset014)
#define USDHC1_CMD_RSP2			(IMXRT_USDHC1.offset018)
#define USDHC1_CMD_RSP3			(IMXRT_USDHC1.offset01C)
#define USDHC1_DATA_BUFF_ACC_PORT	(IMXRT_USDHC1.offset020)
#define USDHC1_PRES_STATE		(IMXRT_USDHC1.offset024)
#define USDHC1_PROT_CTRL		(IMXRT_USDHC1.offset028)
#define USDHC1_SYS_CTRL			(IMXRT_USDHC1.offset02C)
#define USDHC1_INT_STATUS		(IMXRT_USDHC1.offset030)
#define USDHC1_INT_STATUS_EN		(IMXRT_USDHC1.offset034)
#define USDHC1_INT_SIGNAL_EN		(IMXRT_USDHC1.offset038)
#define USDHC1_AUTOCMD12_ERR_STATUS	(IMXRT_USDHC1.offset03C)
#define USDHC1_HOST_CTRL_CAP		(IMXRT_USDHC1.offset040)
#define USDHC1_WTMK_LVL			(IMXRT_USDHC1.offset044)
#define USDHC1_MIX_CTRL			(IMXRT_USDHC1.offset048)
#define USDHC1_FORCE_EVENT		(IMXRT_USDHC1.offset050)
#define USDHC1_ADMA_ERR_STATUS		(IMXRT_USDHC1.offset054)
#define USDHC1_ADMA_SYS_ADDR		(IMXRT_USDHC1.offset058)
#define USDHC1_DLL_CTRL			(IMXRT_USDHC1.offset060)
#define USDHC1_DLL_STATUS		(IMXRT_USDHC1.offset064)
#define USDHC1_CLK_TUNE_CTRL_STATUS	(IMXRT_USDHC1.offset068)
#define USDHC1_VEND_SPEC		(IMXRT_USDHC1.offset0C0)
#define USDHC1_MMC_BOOT			(IMXRT_USDHC1.offset0C4)
#define USDHC1_VEND_SPEC2		(IMXRT_USDHC1.offset0C8)
#define USDHC1_TUNING_CTRL		(IMXRT_USDHC1.offset0CC)
#define IMXRT_USDHC2		(*(IMXRT_REGISTER32_t *)IMXRT_USDHC2_ADDRESS)
#define USDHC2_DS_ADDR			(IMXRT_USDHC2.offset000)
#define USDHC2_BLK_ATT			(IMXRT_USDHC2.offset004)
#define USDHC2_CMD_ARG			(IMXRT_USDHC2.offset008)
#define USDHC2_CMD_XFR_TYP		(IMXRT_USDHC2.offset00C)
#define USDHC2_CMD_RSP0			(IMXRT_USDHC2.offset010)
#define USDHC2_CMD_RSP1			(IMXRT_USDHC2.offset014)
#define USDHC2_CMD_RSP2			(IMXRT_USDHC2.offset018)
#define USDHC2_CMD_RSP3			(IMXRT_USDHC2.offset01C)
#define USDHC2_DATA_BUFF_ACC_PORT	(IMXRT_USDHC2.offset020)
#define USDHC2_PRES_STATE		(IMXRT_USDHC2.offset024)
#define USDHC2_PROT_CTRL		(IMXRT_USDHC2.offset028)
#define USDHC2_SYS_CTRL			(IMXRT_USDHC2.offset02C)
#define USDHC2_INT_STATUS		(IMXRT_USDHC2.offset030)
#define USDHC2_INT_STATUS_EN		(IMXRT_USDHC2.offset034)
#define USDHC2_INT_SIGNAL_EN		(IMXRT_USDHC2.offset038)
#define USDHC2_AUTOCMD12_ERR_STATUS	(IMXRT_USDHC2.offset03C)
#define USDHC2_HOST_CTRL_CAP		(IMXRT_USDHC2.offset040)
#define USDHC2_WTMK_LVL			(IMXRT_USDHC2.offset044)
#define USDHC2_MIX_CTRL			(IMXRT_USDHC2.offset048)
#define USDHC2_FORCE_EVENT		(IMXRT_USDHC2.offset050)
#define USDHC2_ADMA_ERR_STATUS		(IMXRT_USDHC2.offset054)
#define USDHC2_ADMA_SYS_ADDR		(IMXRT_USDHC2.offset058)
#define USDHC2_DLL_CTRL			(IMXRT_USDHC2.offset060)
#define USDHC2_DLL_STATUS		(IMXRT_USDHC2.offset064)
#define USDHC2_CLK_TUNE_CTRL_STATUS	(IMXRT_USDHC2.offset068)
#define USDHC2_VEND_SPEC		(IMXRT_USDHC2.offset0C0)
#define USDHC2_MMC_BOOT			(IMXRT_USDHC2.offset0C4)
#define USDHC2_VEND_SPEC2		(IMXRT_USDHC2.offset0C8)
#define USDHC2_TUNING_CTRL		(IMXRT_USDHC2.offset0CC)

// 57.8.1.1: page 3187
#define IMXRT_WDOG1		(*(IMXRT_REGISTER16_t *)IMXRT_WDOG1_ADDRESS)
#define WDOG1_WCR			(IMXRT_WDOG1.offset000)
#define WDOG1_WSR			(IMXRT_WDOG1.offset002)
#define WDOG1_WRSR			(IMXRT_WDOG1.offset004)
#define WDOG1_WICR			(IMXRT_WDOG1.offset006)
#define WDOG1_WMCR			(IMXRT_WDOG1.offset008)
#define IMXRT_WDOG2		(*(IMXRT_REGISTER16_t *)IMXRT_WDOG2_ADDRESS)
#define WDOG2_WCR			(IMXRT_WDOG2.offset000)
#define WDOG2_WSR			(IMXRT_WDOG2.offset002)
#define WDOG2_WRSR			(IMXRT_WDOG2.offset004)
#define WDOG2_WICR			(IMXRT_WDOG2.offset006)
#define WDOG2_WMCR			(IMXRT_WDOG2.offset008)
#define WDOG_WCR_WDZST				((uint16_t)(1<<0))
#define WDOG_WCR_WDBG				((uint16_t)(1<<1))
#define WDOG_WCR_WDE				((uint16_t)(1<<2))
#define WDOG_WCR_WDT				((uint16_t)(1<<3))
#define WDOG_WCR_SRS				((uint16_t)(1<<4))
#define WDOG_WCR_WDA				((uint16_t)(1<<5))
#define WDOG_WCR_SRE				((uint16_t)(1<<6))
#define WDOG_WCR_WDW				((uint16_t)(1<<7))
#define WDOG_WCR_WT(n)				((uint16_t)(((n) & 0xFF) << 8))
#define WDOG_WRSR_SFTW				((uint16_t)(1<<0))
#define WDOG_WRSR_TOUT				((uint16_t)(1<<1))
#define WDOG_WRSR_POR				((uint16_t)(1<<4))

// 58.5.1.1: page 3205
#define IMXRT_WDOG3		(*(IMXRT_REGISTER32_t *)IMXRT_WDOG3_ADDRESS)
#define WDOG3_CS			(IMXRT_WDOG3.offset000)
#define WDOG3_CNT			(IMXRT_WDOG3.offset004)
#define WDOG3_TOVAL			(IMXRT_WDOG3.offset008)
#define WDOG3_WIN			(IMXRT_WDOG3.offset00C)
#define WDOG_CS_STOP				((uint16_t)(1<<0))
#define WDOG_CS_WAIT				((uint16_t)(1<<1))
#define WDOG_CS_DBG				((uint16_t)(1<<2))
#define WDOG_CS_TST(n)				((uint16_t)(((n) & 0x03) << 3))
#define WDOG_CS_UPDATE				((uint16_t)(1<<5))
#define WDOG_CS_INT				((uint16_t)(1<<6))
#define WDOG_CS_EN				((uint16_t)(1<<7))
#define WDOG_CS_CLK(n)				((uint16_t)(((n) & 0x03) << 8))
#define WDOG_CS_RCS				((uint16_t)(1<<10))
#define WDOG_CS_ULK				((uint16_t)(1<<11))
#define WDOG_CS_PRES				((uint16_t)(1<<12))
#define WDOG_CS_CMD32EN				((uint16_t)(1<<13))
#define WDOG_CS_FLG				((uint16_t)(1<<14))
#define WDOG_CS_WIN				((uint16_t)(1<<15))

// 61.4: page 3235
#define IMXRT_XBARA1		(*(IMXRT_REGISTER16_t *)IMXRT_XBARA1_ADDRESS)
#define XBARA1_SEL0			(IMXRT_XBARA1.offset000)
#define XBARA1_SEL1			(IMXRT_XBARA1.offset002)
#define XBARA1_SEL2			(IMXRT_XBARA1.offset004)
#define XBARA1_SEL3			(IMXRT_XBARA1.offset006)
#define XBARA1_SEL4			(IMXRT_XBARA1.offset008)
#define XBARA1_SEL5			(IMXRT_XBARA1.offset00A)
#define XBARA1_SEL6			(IMXRT_XBARA1.offset00C)
#define XBARA1_SEL7			(IMXRT_XBARA1.offset00E)
#define XBARA1_SEL8			(IMXRT_XBARA1.offset010)
#define XBARA1_SEL9			(IMXRT_XBARA1.offset012)
#define XBARA1_SEL10			(IMXRT_XBARA1.offset014)
#define XBARA1_SEL11			(IMXRT_XBARA1.offset016)
#define XBARA1_SEL12			(IMXRT_XBARA1.offset018)
#define XBARA1_SEL13			(IMXRT_XBARA1.offset01A)
#define XBARA1_SEL14			(IMXRT_XBARA1.offset01C)
#define XBARA1_SEL15			(IMXRT_XBARA1.offset01E)
#define XBARA1_SEL16			(IMXRT_XBARA1.offset020)
#define XBARA1_SEL17			(IMXRT_XBARA1.offset022)
#define XBARA1_SEL18			(IMXRT_XBARA1.offset024)
#define XBARA1_SEL19			(IMXRT_XBARA1.offset026)
#define XBARA1_SEL20			(IMXRT_XBARA1.offset028)
#define XBARA1_SEL21			(IMXRT_XBARA1.offset02A)
#define XBARA1_SEL22			(IMXRT_XBARA1.offset02C)
#define XBARA1_SEL23			(IMXRT_XBARA1.offset02E)
#define XBARA1_SEL24			(IMXRT_XBARA1.offset030)
#define XBARA1_SEL25			(IMXRT_XBARA1.offset032)
#define XBARA1_SEL26			(IMXRT_XBARA1.offset034)
#define XBARA1_SEL27			(IMXRT_XBARA1.offset036)
#define XBARA1_SEL28			(IMXRT_XBARA1.offset038)
#define XBARA1_SEL29			(IMXRT_XBARA1.offset03A)
#define XBARA1_SEL30			(IMXRT_XBARA1.offset03C)
#define XBARA1_SEL31			(IMXRT_XBARA1.offset03E)
#define XBARA1_SEL32			(IMXRT_XBARA1.offset040)
#define XBARA1_SEL33			(IMXRT_XBARA1.offset042)
#define XBARA1_SEL34			(IMXRT_XBARA1.offset044)
#define XBARA1_SEL35			(IMXRT_XBARA1.offset046)
#define XBARA1_SEL36			(IMXRT_XBARA1.offset048)
#define XBARA1_SEL37			(IMXRT_XBARA1.offset04A)
#define XBARA1_SEL38			(IMXRT_XBARA1.offset04C)
#define XBARA1_SEL39			(IMXRT_XBARA1.offset04E)
#define XBARA1_SEL40			(IMXRT_XBARA1.offset050)
#define XBARA1_SEL41			(IMXRT_XBARA1.offset052)
#define XBARA1_SEL42			(IMXRT_XBARA1.offset054)
#define XBARA1_SEL43			(IMXRT_XBARA1.offset056)
#define XBARA1_SEL44			(IMXRT_XBARA1.offset058)
#define XBARA1_SEL45			(IMXRT_XBARA1.offset05A)
#define XBARA1_SEL46			(IMXRT_XBARA1.offset05C)
#define XBARA1_SEL47			(IMXRT_XBARA1.offset05E)
#define XBARA1_SEL48			(IMXRT_XBARA1.offset060)
#define XBARA1_SEL49			(IMXRT_XBARA1.offset062)
#define XBARA1_SEL50			(IMXRT_XBARA1.offset064)
#define XBARA1_SEL51			(IMXRT_XBARA1.offset066)
#define XBARA1_SEL52			(IMXRT_XBARA1.offset068)
#define XBARA1_SEL53			(IMXRT_XBARA1.offset06A)
#define XBARA1_SEL54			(IMXRT_XBARA1.offset06C)
#define XBARA1_SEL55			(IMXRT_XBARA1.offset06E)
#define XBARA1_SEL56			(IMXRT_XBARA1.offset070)
#define XBARA1_SEL57			(IMXRT_XBARA1.offset072)
#define XBARA1_SEL58			(IMXRT_XBARA1.offset074)
#define XBARA1_SEL59			(IMXRT_XBARA1.offset076)
#define XBARA1_SEL60			(IMXRT_XBARA1.offset078)
#define XBARA1_SEL61			(IMXRT_XBARA1.offset07A)
#define XBARA1_SEL62			(IMXRT_XBARA1.offset07C)
#define XBARA1_SEL63			(IMXRT_XBARA1.offset07E)
#define XBARA1_SEL64			(IMXRT_XBARA1.offset080)
#define XBARA1_SEL65			(IMXRT_XBARA1.offset082)
#define XBARA1_CTRL0			(IMXRT_XBARA1.offset084)
#define XBARA1_CTRL1			(IMXRT_XBARA1.offset086)
#define XBARA_CTRL_STS1				((uint16_t)(1<<12))
#define XBARA_CTRL_EDGE1(n)			((uint16_t)(((n) & 0x03) << 10))
#define XBARA_CTRL_IEN1				((uint16_t)(1<<9))
#define XBARA_CTRL_DEN1				((uint16_t)(1<<8))
#define XBARA_CTRL_STS0				((uint16_t)(1<<4))
#define XBARA_CTRL_EDGE0(n)			((uint16_t)(((n) & 0x03) << 2))
#define XBARA_CTRL_IEN0				((uint16_t)(1<<1))
#define XBARA_CTRL_DEN0				((uint16_t)(1<<0))

// 62.3: page 3278
#define IMXRT_XBARB2		(*(IMXRT_REGISTER16_t *)IMXRT_XBARB2_ADDRESS)
#define XBARB2_SEL0			(IMXRT_XBARB2.offset000)
#define XBARB2_SEL1			(IMXRT_XBARB2.offset002)
#define XBARB2_SEL2			(IMXRT_XBARB2.offset004)
#define XBARB2_SEL3			(IMXRT_XBARB2.offset006)
#define XBARB2_SEL4			(IMXRT_XBARB2.offset008)
#define XBARB2_SEL5			(IMXRT_XBARB2.offset00A)
#define XBARB2_SEL6			(IMXRT_XBARB2.offset00C)
#define XBARB2_SEL7			(IMXRT_XBARB2.offset00E)
#define IMXRT_XBARB3		(*(IMXRT_REGISTER16_t *)IMXRT_XBARB3_ADDRESS)
#define XBARB3_SEL0			(IMXRT_XBARB3.offset000)
#define XBARB3_SEL1			(IMXRT_XBARB3.offset002)
#define XBARB3_SEL2			(IMXRT_XBARB3.offset004)
#define XBARB3_SEL3			(IMXRT_XBARB3.offset006)
#define XBARB3_SEL4			(IMXRT_XBARB3.offset008)
#define XBARB3_SEL5			(IMXRT_XBARB3.offset00A)
#define XBARB3_SEL6			(IMXRT_XBARB3.offset00C)
#define XBARB3_SEL7			(IMXRT_XBARB3.offset00E)

// XBAR1 Inputs and Outputs Table 3-4 Starting Page 62
#define XBARA1_IN_LOGIC_LOW 0
#define XBARA1_IN_LOGIC_HIGH 1
#define XBARA1_IN_IOMUX_XBAR_IN02 2
#define XBARA1_IN_IOMUX_XBAR_IN03 3
#define XBARA1_IN_IOMUX_XBAR_INOUT04 4
#define XBARA1_IN_IOMUX_XBAR_INOUT05 5
#define XBARA1_IN_IOMUX_XBAR_INOUT06 6
#define XBARA1_IN_IOMUX_XBAR_INOUT07 7
#define XBARA1_IN_IOMUX_XBAR_INOUT08 8
#define XBARA1_IN_IOMUX_XBAR_INOUT09 9
#define XBARA1_IN_IOMUX_XBAR_INOUT10 10
#define XBARA1_IN_IOMUX_XBAR_INOUT11 11
#define XBARA1_IN_IOMUX_XBAR_INOUT12 12
#define XBARA1_IN_IOMUX_XBAR_INOUT13 13
#define XBARA1_IN_IOMUX_XBAR_INOUT14 14
#define XBARA1_IN_IOMUX_XBAR_INOUT15 15
#define XBARA1_IN_IOMUX_XBAR_INOUT16 16
#define XBARA1_IN_IOMUX_XBAR_INOUT17 17
#define XBARA1_IN_IOMUX_XBAR_INOUT18 18
#define XBARA1_IN_IOMUX_XBAR_INOUT19 19
#define XBARA1_IN_IOMUX_XBAR_IN20 20
#define XBARA1_IN_IOMUX_XBAR_IN21 21
#define XBARA1_IN_IOMUX_XBAR_IN22 22
#define XBARA1_IN_IOMUX_XBAR_IN23 23
#define XBARA1_IN_IOMUX_XBAR_IN24 24
#define XBARA1_IN_IOMUX_XBAR_IN25 25
#define XBARA1_IN_ACMP1_OUT 26
#define XBARA1_IN_ACMP2_OUT 27
#define XBARA1_IN_ACMP3_OUT 28
#define XBARA1_IN_ACMP4_OUT 29
//#define XBARA1_IN_Reserved 30
//#define XBARA1_IN_Reserved 31
#define XBARA1_IN_QTIMER3_TIMER0 32
#define XBARA1_IN_QTIMER3_TIMER1 33
#define XBARA1_IN_QTIMER3_TIMER2 34
#define XBARA1_IN_QTIMER3_TIMER3 35
#define XBARA1_IN_QTIMER4_TIMER0 36
#define XBARA1_IN_QTIMER4_TIMER1 37
#define XBARA1_IN_QTIMER4_TIMER2 38
#define XBARA1_IN_QTIMER4_TIMER3 39
#define XBARA1_IN_FLEXPWM1_PWM1_OUT_TRIG0 40
#define XBARA1_IN_FLEXPWM1_PWM1_OUT_TRIG1 40
#define XBARA1_IN_FLEXPWM1_PWM2_OUT_TRIG0 41
#define XBARA1_IN_FLEXPWM1_PWM2_OUT_TRIG1 41
#define XBARA1_IN_FLEXPWM1_PWM3_OUT_TRIG0 42
#define XBARA1_IN_FLEXPWM1_PWM3_OUT_TRIG1 42
#define XBARA1_IN_FLEXPWM1_PWM4_OUT_TRIG0 43
#define XBARA1_IN_FLEXPWM1_PWM4_OUT_TRIG1 43
#define XBARA1_IN_FLEXPWM2_PWM1_OUT_TRIG0 44
#define XBARA1_IN_FLEXPWM2_PWM1_OUT_TRIG1 44
#define XBARA1_IN_FLEXPWM2_PWM2_OUT_TRIG0 45
#define XBARA1_IN_FLEXPWM2_PWM2_OUT_TRIG1 45
#define XBARA1_IN_FLEXPWM2_PWM3_OUT_TRIG0 46
#define XBARA1_IN_FLEXPWM2_PWM3_OUT_TRIG1 46
#define XBARA1_IN_FLEXPWM2_PWM4_OUT_TRIG0 47
#define XBARA1_IN_FLEXPWM2_PWM4_OUT_TRIG1 47
#define XBARA1_IN_FLEXPWM3_PWM1_OUT_TRIG0 48
#define XBARA1_IN_FLEXPWM3_PWM1_OUT_TRIG1 48
#define XBARA1_IN_FLEXPWM3_PWM2_OUT_TRIG0 49
#define XBARA1_IN_FLEXPWM3_PWM2_OUT_TRIG1 49
#define XBARA1_IN_FLEXPWM3_PWM3_OUT_TRIG0 50
#define XBARA1_IN_FLEXPWM3_PWM3_OUT_TRIG1 50
#define XBARA1_IN_FLEXPWM3_PWM4_OUT_TRIG0 51
#define XBARA1_IN_FLEXPWM3_PWM4_OUT_TRIG1 51
#define XBARA1_IN_FLEXPWM4_PWM1_OUT_TRIG0 52
#define XBARA1_IN_FLEXPWM4_PWM1_OUT_TRIG1 52
#define XBARA1_IN_FLEXPWM4_PWM2_OUT_TRIG0 53
#define XBARA1_IN_FLEXPWM4_PWM2_OUT_TRIG1 53
#define XBARA1_IN_FLEXPWM4_PWM3_OUT_TRIG0 54
#define XBARA1_IN_FLEXPWM4_PWM3_OUT_TRIG1 54
#define XBARA1_IN_FLEXPWM4_PWM4_OUT_TRIG0 55
#define XBARA1_IN_FLEXPWM4_PWM4_OUT_TRIG1 55
#define XBARA1_IN_PIT_TRIGGER0 56
#define XBARA1_IN_PIT_TRIGGER1 57
#define XBARA1_IN_PIT_TRIGGER2 58
#define XBARA1_IN_PIT_TRIGGER3 59
#define XBARA1_IN_ENC1_POS_MATCH 60
#define XBARA1_IN_ENC2_POS_MATCH 61
#define XBARA1_IN_ENC3_POS_MATCH 62
#define XBARA1_IN_ENC4_POS_MATCH 63
#define XBARA1_IN_DMA_DONE0 64
#define XBARA1_IN_DMA_DONE1 65
#define XBARA1_IN_DMA_DONE2 66
#define XBARA1_IN_DMA_DONE3 67
#define XBARA1_IN_DMA_DONE4 68
#define XBARA1_IN_DMA_DONE5 69
#define XBARA1_IN_DMA_DONE6 70
#define XBARA1_IN_DMA_DONE7 71
#define XBARA1_IN_AOI1_OUT0 72
#define XBARA1_IN_AOI1_OUT1 73
#define XBARA1_IN_AOI1_OUT2 74
#define XBARA1_IN_AOI1_OUT3 75
#define XBARA1_IN_AOI2_OUT0 76
#define XBARA1_IN_AOI2_OUT1 77
#define XBARA1_IN_AOI2_OUT2 78
#define XBARA1_IN_AOI2_OUT3 79
#define XBARA1_IN_ADC_ETC0_COCO0 80
#define XBARA1_IN_ADC_ETC0_COCO1 81
#define XBARA1_IN_ADC_ETC0_COCO2 82
#define XBARA1_IN_ADC_ETC0_COCO3 83
#define XBARA1_IN_ADC_ETC1_COCO0 84
#define XBARA1_IN_ADC_ETC1_COCO1 85
#define XBARA1_IN_ADC_ETC1_COCO2 86
#define XBARA1_IN_ADC_ETC1_COCO3 87

#define XBARA1_OUT_DMA_CH_MUX_REQ30 0
#define XBARA1_OUT_DMA_CH_MUX_REQ31 1
#define XBARA1_OUT_DMA_CH_MUX_REQ94 2
#define XBARA1_OUT_DMA_CH_MUX_REQ95 3
#define XBARA1_OUT_IOMUX_XBAR_INOUT04 4
#define XBARA1_OUT_IOMUX_XBAR_INOUT05 5
#define XBARA1_OUT_IOMUX_XBAR_INOUT06 6
#define XBARA1_OUT_IOMUX_XBAR_INOUT07 7
#define XBARA1_OUT_IOMUX_XBAR_INOUT08 8
#define XBARA1_OUT_IOMUX_XBAR_INOUT09 9
#define XBARA1_OUT_IOMUX_XBAR_INOUT10 10
#define XBARA1_OUT_IOMUX_XBAR_INOUT11 11
#define XBARA1_OUT_IOMUX_XBAR_INOUT12 12
#define XBARA1_OUT_IOMUX_XBAR_INOUT13 13
#define XBARA1_OUT_IOMUX_XBAR_INOUT14 14
#define XBARA1_OUT_IOMUX_XBAR_INOUT15 15
#define XBARA1_OUT_IOMUX_XBAR_INOUT16 16
#define XBARA1_OUT_IOMUX_XBAR_INOUT17 17
#define XBARA1_OUT_IOMUX_XBAR_INOUT18 18
#define XBARA1_OUT_IOMUX_XBAR_INOUT19 19
#define XBARA1_OUT_ACMP1_SAMPLE 20
#define XBARA1_OUT_ACMP2_SAMPLE 21
#define XBARA1_OUT_ACMP3_SAMPLE 22
#define XBARA1_OUT_ACMP4_SAMPLE 23
//#define XBARA1_OUT_Reserved 24
//#define XBARA1_OUT_Reserved 25
#define XBARA1_OUT_FLEXPWM1_PWM0_EXTA 26
#define XBARA1_OUT_FLEXPWM1_PWM1_EXTA 27
#define XBARA1_OUT_FLEXPWM1_PWM2_EXTA 28
#define XBARA1_OUT_FLEXPWM1_PWM3_EXTA 29
#define XBARA1_OUT_FLEXPWM1_PWM0_EXT_SYNC 30
#define XBARA1_OUT_FLEXPWM1_PWM1_EXT_SYNC 31
#define XBARA1_OUT_FLEXPWM1_PWM2_EXT_SYNC 32
#define XBARA1_OUT_FLEXPWM1_PWM3_EXT_SYNC 33
#define XBARA1_OUT_FLEXPWM1_EXT_CLK 34
#define XBARA1_OUT_FLEXPWM1_FAULT0 35
#define XBARA1_OUT_FLEXPWM1_FAULT1 36
#define XBARA1_OUT_FLEXPWM1_FAULT2 37
#define XBARA1_OUT_FLEXPWM2_FAULT2 37
#define XBARA1_OUT_FLEXPWM3_FAULT2 37
#define XBARA1_OUT_FLEXPWM4_FAULT2 37
#define XBARA1_OUT_FLEXPWM1_FAULT3 38
#define XBARA1_OUT_FLEXPWM2_FAULT3 38
#define XBARA1_OUT_FLEXPWM3_FAULT3 38
#define XBARA1_OUT_FLEXPWM4_FAULT3 38
#define XBARA1_OUT_FLEXPWM1_EXT_FORCE 39
#define XBARA1_OUT_FLEXPWM2_PWM0_EXTA 40
#define XBARA1_OUT_FLEXPWM3_PWM0_EXTA 40
#define XBARA1_OUT_FLEXPWM4_PWM0_EXTA 40
#define XBARA1_OUT_FLEXPWM2_PWM1_EXTA 41
#define XBARA1_OUT_FLEXPWM3_PWM1_EXTA 41
#define XBARA1_OUT_FLEXPWM4_PWM1_EXTA 41
#define XBARA1_OUT_FLEXPWM2_PWM2_EXTA 42
#define XBARA1_OUT_FLEXPWM3_PWM2_EXTA 42
#define XBARA1_OUT_FLEXPWM4_PWM2_EXTA 42
#define XBARA1_OUT_FLEXPWM2_PWM3_EXTA 43
#define XBARA1_OUT_FLEXPWM3_PWM3_EXTA 43
#define XBARA1_OUT_FLEXPWM4_PWM3_EXTA 43
#define XBARA1_OUT_FLEXPWM2_PWM0_EXT_SYNC 44
#define XBARA1_OUT_FLEXPWM2_PWM1_EXT_SYNC 45
#define XBARA1_OUT_FLEXPWM2_PWM2_EXT_SYNC 46
#define XBARA1_OUT_FLEXPWM2_PWM3_EXT_SYNC 47
#define XBARA1_OUT_FLEXPWM2_EXT_CLK 48
#define XBARA1_OUT_FLEXPWM3_EXT_CLK 48
#define XBARA1_OUT_FLEXPWM4_EXT_CLK 48
#define XBARA1_OUT_FLEXPWM2_FAULT0 49
#define XBARA1_OUT_FLEXPWM2_FAULT1 50
#define XBARA1_OUT_FLEXPWM2_EXT_FORCE 51
#define XBARA1_OUT_FLEXPWM3_EXT_SYNC0 52
#define XBARA1_OUT_FLEXPWM3_EXT_SYNC1 53
#define XBARA1_OUT_FLEXPWM3_EXT_SYNC2 54
#define XBARA1_OUT_FLEXPWM3_EXT_SYNC3 55
#define XBARA1_OUT_FLEXPWM3_FAULT0 56
#define XBARA1_OUT_FLEXPWM3_FAULT1 57
#define XBARA1_OUT_FLEXPWM3_EXT_FORCE 58
#define XBARA1_OUT_FLEXPWM4_EXT_SYNC0 59
#define XBARA1_OUT_FLEXPWM4_EXT_SYNC1 60
#define XBARA1_OUT_FLEXPWM4_EXT_SYNC2 61
#define XBARA1_OUT_FLEXPWM4_EXT_SYNC3 62
#define XBARA1_OUT_FLEXPWM4_FAULT0 63
#define XBARA1_OUT_FLEXPWM4_FAULT1 64
#define XBARA1_OUT_FLEXPWM4_EXT_FORCE 65
#define XBARA1_OUT_ENC1_PHASEA_INPUT 66
#define XBARA1_OUT_ENC1_PHASEB_INPUT 67
#define XBARA1_OUT_ENC1_INDEX 68
#define XBARA1_OUT_ENC1_HOME 69
#define XBARA1_OUT_ENC1_TRIGGER 70
#define XBARA1_OUT_ENC2_PHASEA_INPUT 71
#define XBARA1_OUT_ENC2_PHASEB_INPUT 72
#define XBARA1_OUT_ENC2_INDEX 73
#define XBARA1_OUT_ENC2_HOME 74
#define XBARA1_OUT_ENC2_TRIGGER 75
#define XBARA1_OUT_ENC3_PHASEA_INPUT 76
#define XBARA1_OUT_ENC3_PHASEB_INPUT 77
#define XBARA1_OUT_ENC3_INDEX 78
#define XBARA1_OUT_ENC3_HOME 79
#define XBARA1_OUT_ENC3_TRIGGER 80
#define XBARA1_OUT_ENC4_PHASEA_INPUT 81
#define XBARA1_OUT_ENC4_PHASEB_INPUT 82
#define XBARA1_OUT_ENC4_INDEX 83
#define XBARA1_OUT_ENC4_HOME 84
#define XBARA1_OUT_ENC4_TRIGGER 85
#define XBARA1_OUT_QTIMER1_TIMER0 86
#define XBARA1_OUT_QTIMER1_TIMER1 87
#define XBARA1_OUT_QTIMER1_TIMER2 88
#define XBARA1_OUT_QTIMER1_TIMER3 89
#define XBARA1_OUT_QTIMER2_TIMER0 90
#define XBARA1_OUT_QTIMER2_TIMER1 91
#define XBARA1_OUT_QTIMER2_TIMER2 92
#define XBARA1_OUT_QTIMER2_TIMER3 93
#define XBARA1_OUT_QTIMER3_TIMER0 94
#define XBARA1_OUT_QTIMER3_TIMER1 95
#define XBARA1_OUT_QTIMER3_TIMER2 96
#define XBARA1_OUT_QTIMER3_TIMER3 97
#define XBARA1_OUT_QTIMER4_TIMER0 98
#define XBARA1_OUT_QTIMER4_TIMER1 99
#define XBARA1_OUT_QTIMER4_TIMER2 100
#define XBARA1_OUT_QTIMER4_TIMER3 101
#define XBARA1_OUT_EWM_EWM_IN 102
#define XBARA1_OUT_ADC_ETC_TRIG00 103
#define XBARA1_OUT_ADC_ETC_TRIG01 104
#define XBARA1_OUT_ADC_ETC_TRIG02 105
#define XBARA1_OUT_ADC_ETC_TRIG03 106
#define XBARA1_OUT_ADC_ETC_TRIG10 107
#define XBARA1_OUT_ADC_ETC_TRIG11 108
#define XBARA1_OUT_ADC_ETC_TRIG12 109
#define XBARA1_OUT_ADC_ETC_TRIG13 110
#define XBARA1_OUT_LPI2C1_TRG_INPUT 111
#define XBARA1_OUT_LPI2C2_TRG_INPUT 112
#define XBARA1_OUT_LPI2C3_TRG_INPUT 113
#define XBARA1_OUT_LPI2C4_TRG_INPUT 114
#define XBARA1_OUT_LPSPI1_TRG_INPUT 115
#define XBARA1_OUT_LPSPI2_TRG_INPUT 116
#define XBARA1_OUT_LPSPI3_TRG_INPUT 117
#define XBARA1_OUT_LPSPI4_TRG_INPUT 118
#define XBARA1_OUT_LPUART1_TRG_INPUT 119
#define XBARA1_OUT_LPUART2_TRG_INPUT 120
#define XBARA1_OUT_LPUART3_TRG_INPUT 121
#define XBARA1_OUT_LPUART4_TRG_INPUT 122
#define XBARA1_OUT_LPUART5_TRG_INPUT 123
#define XBARA1_OUT_LPUART6_TRG_INPUT 124
#define XBARA1_OUT_LPUART7_TRG_INPUT 125
#define XBARA1_OUT_LPUART8_TRG_INPUT 126
#define XBARA1_OUT_FLEXIO1_TRIGGER_IN0 127
#define XBARA1_OUT_FLEXIO1_TRIGGER_IN1 128
#define XBARA1_OUT_FLEXIO2_TRIGGER_IN0 129
#define XBARA1_OUT_FLEXIO2_TRIGGER_IN1 130
//#define XBARA1_OUT_Reserved 131

// XBAR2 Inputs and Outputs Table 3-5 P63
#define XBARB2_IN_LOGIC_LOW 0
#define XBARB2_IN_LOGIC_HIGH 1
//#define XBARB2_IN_Reserved 2
//#define XBARB2_IN_Reserved 3
//#define XBARB2_IN_Reserved 4
//#define XBARB2_IN_Reserved 5
#define XBARB2_IN_ACMP1_OUT 6
#define XBARB2_IN_ACMP2_OUT 7
#define XBARB2_IN_ACMP3_OUT 8
#define XBARB2_IN_ACMP4_OUT 9
//#define XBARB2_IN_Reserved 10
//#define XBARB2_IN_Reserved 11
#define XBARB2_IN_QTIMER3_TIMER0 12
#define XBARB2_IN_QTIMER3_TIMER1 13
#define XBARB2_IN_QTIMER3_TIMER2 14
#define XBARB2_IN_QTIMER3_TIMER3 15
#define XBARB2_IN_QTIMER4_TIMER0 16
#define XBARB2_IN_QTIMER4_TIMER1 17
#define XBARB2_IN_QTIMER4_TIMER2 18
#define XBARB2_IN_QTIMER4_TIMER3 19
#define XBARB2_IN_FLEXPWM1_PWM1_OUT_TRIG0 20
#define XBARB2_IN_FLEXPWM1_PWM1_OUT_TRIG1 20
#define XBARB2_IN_FLEXPWM1_PWM2_OUT_TRIG0 21
#define XBARB2_IN_FLEXPWM1_PWM2_OUT_TRIG1 21
#define XBARB2_IN_FLEXPWM1_PWM3_OUT_TRIG0 22
#define XBARB2_IN_FLEXPWM1_PWM3_OUT_TRIG1 22
#define XBARB2_IN_FLEXPWM1_PWM4_OUT_TRIG0 23
#define XBARB2_IN_FLEXPWM1_PWM4_OUT_TRIG1 23
#define XBARB2_IN_FLEXPWM2_PWM1_OUT_TRIG0 24
#define XBARB2_IN_FLEXPWM2_PWM1_OUT_TRIG1 24
#define XBARB2_IN_FLEXPWM2_PWM2_OUT_TRIG0 25
#define XBARB2_IN_FLEXPWM2_PWM2_OUT_TRIG1 25
#define XBARB2_IN_FLEXPWM2_PWM3_OUT_TRIG0 26
#define XBARB2_IN_FLEXPWM2_PWM3_OUT_TRIG1 26
#define XBARB2_IN_FLEXPWM2_PWM4_OUT_TRIG0 27
#define XBARB2_IN_FLEXPWM2_PWM4_OUT_TRIG1 27
#define XBARB2_IN_FLEXPWM3_PWM1_OUT_TRIG0 28
#define XBARB2_IN_FLEXPWM3_PWM1_OUT_TRIG1 28
#define XBARB2_IN_FLEXPWM3_PWM2_OUT_TRIG0 29
#define XBARB2_IN_FLEXPWM3_PWM2_OUT_TRIG1 29
#define XBARB2_IN_FLEXPWM3_PWM3_OUT_TRIG0 30
#define XBARB2_IN_FLEXPWM3_PWM3_OUT_TRIG1 30
#define XBARB2_IN_FLEXPWM3_PWM4_OUT_TRIG0 31
#define XBARB2_IN_FLEXPWM3_PWM4_OUT_TRIG1 31
#define XBARB2_IN_FLEXPWM4_PWM1_OUT_TRIG0 32
#define XBARB2_IN_FLEXPWM4_PWM1_OUT_TRIG1 32
#define XBARB2_IN_FLEXPWM4_PWM2_OUT_TRIG0 33
#define XBARB2_IN_FLEXPWM4_PWM2_OUT_TRIG1 33
#define XBARB2_IN_FLEXPWM4_PWM3_OUT_TRIG0 34
#define XBARB2_IN_FLEXPWM4_PWM3_OUT_TRIG1 34
#define XBARB2_IN_FLEXPWM4_PWM4_OUT_TRIG0 35
#define XBARB2_IN_FLEXPWM4_PWM4_OUT_TRIG1 35
#define XBARB2_IN_PIT_TRIGGER0 36
#define XBARB2_IN_PIT_TRIGGER1 37
#define XBARB2_IN_ADC_ETC0_COCO0 38
#define XBARB2_IN_ADC_ETC0_COCO1 39
#define XBARB2_IN_ADC_ETC0_COCO2 40
#define XBARB2_IN_ADC_ETC0_COCO3 41
#define XBARB2_IN_ADC_ETC1_COCO0 42
#define XBARB2_IN_ADC_ETC1_COCO1 43
#define XBARB2_IN_ADC_ETC1_COCO2 44
#define XBARB2_IN_ADC_ETC1_COCO3 45
#define XBARB2_IN_ENC1_POS_MATCH 46
#define XBARB2_IN_ENC2_POS_MATCH 47
#define XBARB2_IN_ENC3_POS_MATCH 48
#define XBARB2_IN_ENC4_POS_MATCH 49
#define XBARB2_IN_DMA_DONE0 50
#define XBARB2_IN_DMA_DONE1 51
#define XBARB2_IN_DMA_DONE2 52
#define XBARB2_IN_DMA_DONE3 53
#define XBARB2_IN_DMA_DONE4 54
#define XBARB2_IN_DMA_DONE5 55
#define XBARB2_IN_DMA_DONE6 56
#define XBARB2_IN_DMA_DONE7 57

#define XBARB2_OUT_AOI1_IN00 0
#define XBARB2_OUT_AOI1_IN01 1
#define XBARB2_OUT_AOI1_IN02 2
#define XBARB2_OUT_AOI1_IN03 3
#define XBARB2_OUT_AOI1_IN04 4
#define XBARB2_OUT_AOI1_IN05 5
#define XBARB2_OUT_AOI1_IN06 6
#define XBARB2_OUT_AOI1_IN07 7
#define XBARB2_OUT_AOI1_IN08 8
#define XBARB2_OUT_AOI1_IN09 9
#define XBARB2_OUT_AOI1_IN10 10
#define XBARB2_OUT_AOI1_IN11 11
#define XBARB2_OUT_AOI1_IN12 12
#define XBARB2_OUT_AOI1_IN13 13
#define XBARB2_OUT_AOI1_IN14 14

// XBAR3 Inputs and Outputs Table 3-6 Page 63
#define XBARB3_IN_LOGIC_LOW 0
#define XBARB3_IN_LOGIC_HIGH 1
//#define XBARB3_IN_Reserved 2
//#define XBARB3_IN_Reserved 3
//#define XBARB3_IN_Reserved 4
//#define XBARB3_IN_Reserved 5
#define XBARB3_IN_ACMP1_OUT 6
#define XBARB3_IN_ACMP2_OUT 7
#define XBARB3_IN_ACMP3_OUT 8
#define XBARB3_IN_ACMP4_OUT 9
//#define XBARB3_IN_Reserved 10
//#define XBARB3_IN_Reserved 11
#define XBARB3_IN_QTIMER3_TIMER0 12
#define XBARB3_IN_QTIMER3_TIMER1 13
#define XBARB3_IN_QTIMER3_TIMER2 14
#define XBARB3_IN_QTIMER3_TIMER3 15
#define XBARB3_IN_QTIMER4_TIMER0 16
#define XBARB3_IN_QTIMER4_TIMER1 17
#define XBARB3_IN_QTIMER4_TIMER2 18
#define XBARB3_IN_QTIMER4_TIMER3 19
#define XBARB3_IN_FLEXPWM1_PWM1_OUT_TRIG0 20
#define XBARB3_IN_FLEXPWM1_PWM2_OUT_TRIG0 21
#define XBARB3_IN_FLEXPWM1_PWM3_OUT_TRIG0 22
#define XBARB3_IN_FLEXPWM1_PWM4_OUT_TRIG0 23
#define XBARB3_IN_FLEXPWM2_PWM1_OUT_TRIG0 24
#define XBARB3_IN_FLEXPWM2_PWM2_OUT_TRIG0 25
#define XBARB3_IN_FLEXPWM2_PWM3_OUT_TRIG0 26
#define XBARB3_IN_FLEXPWM2_PWM4_OUT_TRIG0 27
#define XBARB3_IN_FLEXPWM3_PWM1_OUT_TRIG0 28
#define XBARB3_IN_FLEXPWM3_PWM2_OUT_TRIG0 29
#define XBARB3_IN_FLEXPWM3_PWM3_OUT_TRIG0 30
#define XBARB3_IN_FLEXPWM3_PWM4_OUT_TRIG0 31
#define XBARB3_IN_FLEXPWM4_PWM1_OUT_TRIG0 32
#define XBARB3_IN_FLEXPWM4_PWM2_OUT_TRIG0 33
#define XBARB3_IN_FLEXPWM4_PWM3_OUT_TRIG0 34
#define XBARB3_IN_FLEXPWM4_PWM4_OUT_TRIG0 35
#define XBARB3_IN_PIT_TRIGGER0 36
#define XBARB3_IN_PIT_TRIGGER1 37
#define XBARB3_IN_ADC_ETC0_COCO0 38
#define XBARB3_IN_ADC_ETC0_COCO1 39
#define XBARB3_IN_ADC_ETC0_COCO2 40
#define XBARB3_IN_ADC_ETC0_COCO3 41
#define XBARB3_IN_ADC_ETC1_COCO0 42
#define XBARB3_IN_ADC_ETC1_COCO1 43
#define XBARB3_IN_ADC_ETC1_COCO2 44
#define XBARB3_IN_ADC_ETC1_COCO3 45
#define XBARB3_IN_ENC1_POS_MATCH 46
#define XBARB3_IN_ENC2_POS_MATCH 47
#define XBARB3_IN_ENC3_POS_MATCH 48
#define XBARB3_IN_ENC4_POS_MATCH 49
#define XBARB3_IN_DMA_DONE0 50
#define XBARB3_IN_DMA_DONE1 51
#define XBARB3_IN_DMA_DONE2 52
#define XBARB3_IN_DMA_DONE3 53
#define XBARB3_IN_DMA_DONE4 54
#define XBARB3_IN_DMA_DONE5 55
#define XBARB3_IN_DMA_DONE6 56
#define XBARB3_IN_DMA_DONE7 57

#define XBARB3_OUT_AOI2_IN00 0
#define XBARB3_OUT_AOI2_IN01 1
#define XBARB3_OUT_AOI2_IN02 2
#define XBARB3_OUT_AOI2_IN03 3
#define XBARB3_OUT_AOI2_IN04 4
#define XBARB3_OUT_AOI2_IN05 5
#define XBARB3_OUT_AOI2_IN06 6
#define XBARB3_OUT_AOI2_IN07 7
#define XBARB3_OUT_AOI2_IN08 8
#define XBARB3_OUT_AOI2_IN09 9
#define XBARB3_OUT_AOI2_IN10 10
#define XBARB3_OUT_AOI2_IN11 11
#define XBARB3_OUT_AOI2_IN12 12
#define XBARB3_OUT_AOI2_IN13 13
#define XBARB3_OUT_AOI2_IN14 14
#define XBARB3_OUT_AOI2_IN15 15


// 15.6: page 1142
#define IMXRT_XTALOSC24M	(*(IMXRT_REGISTER32_t *)IMXRT_XTALOSC24M_ADDRESS)
#define XTALOSC24M_MISC0		(IMXRT_XTALOSC24M.offset150)
#define XTALOSC24M_LOWPWR_CTRL		(IMXRT_XTALOSC24M.offset270)
#define XTALOSC24M_LOWPWR_CTRL_SET	(IMXRT_XTALOSC24M.offset274)
#define XTALOSC24M_LOWPWR_CTRL_CLR	(IMXRT_XTALOSC24M.offset278)
#define XTALOSC24M_LOWPWR_CTRL_TOG	(IMXRT_XTALOSC24M.offset27C)
#define XTALOSC24M_OSC_CONFIG0		(IMXRT_XTALOSC24M.offset2A0)
#define XTALOSC24M_OSC_CONFIG0_SET	(IMXRT_XTALOSC24M.offset2A4)
#define XTALOSC24M_OSC_CONFIG0_CLR	(IMXRT_XTALOSC24M.offset2A8)
#define XTALOSC24M_OSC_CONFIG0_TOG	(IMXRT_XTALOSC24M.offset2AC)
#define XTALOSC24M_OSC_CONFIG1		(IMXRT_XTALOSC24M.offset2B0)
#define XTALOSC24M_OSC_CONFIG1_SET	(IMXRT_XTALOSC24M.offset2B4)
#define XTALOSC24M_OSC_CONFIG1_CLR	(IMXRT_XTALOSC24M.offset2B8)
#define XTALOSC24M_OSC_CONFIG1_TOG	(IMXRT_XTALOSC24M.offset2BC)
#define XTALOSC24M_OSC_CONFIG2		(IMXRT_XTALOSC24M.offset2C0)
#define XTALOSC24M_OSC_CONFIG2_SET	(IMXRT_XTALOSC24M.offset2C4)
#define XTALOSC24M_OSC_CONFIG2_CLR	(IMXRT_XTALOSC24M.offset2C8)
#define XTALOSC24M_OSC_CONFIG2_TOG	(IMXRT_XTALOSC24M.offset2CC)


// 0 = highest priority
// Cortex-M7: 0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240
#define NVIC_SET_PRIORITY(irqnum, priority)  (*((volatile uint8_t *)0xE000E400 + (irqnum)) = (uint8_t)(priority))
#define NVIC_GET_PRIORITY(irqnum) (*((uint8_t *)0xE000E400 + (irqnum)))


#define __disable_irq() __asm__ volatile("CPSID i":::"memory");
#define __enable_irq()  __asm__ volatile("CPSIE i":::"memory");


// System Control Space (SCS), ARMv7 ref manual, B3.2, page 708
#define SCB_CPUID               (*(const    uint32_t *)0xE000ED00) // CPUID Base Register
#define SCB_ICSR                (*(volatile uint32_t *)0xE000ED04) // Interrupt Control and State
#define SCB_ICSR_NMIPENDSET             ((uint32_t)(1<<31))
#define SCB_ICSR_PENDSVSET              ((uint32_t)(1<<28))
#define SCB_ICSR_PENDSVCLR              ((uint32_t)(1<<27))
#define SCB_ICSR_PENDSTSET              ((uint32_t)(1<<26))
#define SCB_ICSR_PENDSTCLR              ((uint32_t)(1<<25))
#define SCB_ICSR_ISRPREEMPT             ((uint32_t)(1<<23))
#define SCB_ICSR_ISRPENDING             ((uint32_t)(1<<22))
#define SCB_ICSR_RETTOBASE              ((uint32_t)(1<<11))
#define SCB_VTOR                (*(volatile uint32_t *)0xE000ED08) // Vector Table Offset
#define SCB_AIRCR               (*(volatile uint32_t *)0xE000ED0C) // Application Interrupt & Reset
#define SCB_SCR                 (*(volatile uint32_t *)0xE000ED10) // System Control Register
#define SCB_SCR_SEVONPEND   ((uint8_t)0x10)        // Send Event on Pending bit
#define SCB_SCR_SLEEPDEEP   ((uint8_t)0x04)        // Sleep or Deep Sleep
#define SCB_SCR_SLEEPONEXIT ((uint8_t)0x02)        // Sleep-on-exit
#define SCB_CCR                 (*(volatile uint32_t *)0xE000ED14) // Configuration and Control
#define SCB_CCR_BP			((uint32_t)(1<<18))	// Branch prediction enable
#define SCB_CCR_IC			((uint32_t)(1<<17))	// Instruction caches enable
#define SCB_CCR_DC			((uint32_t)(1<<16))
#define SCB_CCR_STKALIGN		((uint32_t)(1<<9))
#define SCB_CCR_BFHFNMIGN		((uint32_t)(1<<8))
#define SCB_CCR_DIV_0_TRP		((uint32_t)(1<<4))
#define SCB_CCR_UNALIGN_TRP		((uint32_t)(1<<3))
#define SCB_CCR_USERSETMPEND		((uint32_t)(1<<1))
#define SCB_CCR_NONBASETHRDENA		((uint32_t)(1<<0))
#define SCB_SHPR1               (*(volatile uint32_t *)0xE000ED18) // System Handler Priority 1
#define SCB_SHPR2               (*(volatile uint32_t *)0xE000ED1C) // System Handler Priority 2
#define SCB_SHPR3               (*(volatile uint32_t *)0xE000ED20) // System Handler Priority 3
#define SCB_SHCSR               (*(volatile uint32_t *)0xE000ED24) // System Handler Control & State
#define SCB_SHCSR_MEMFAULTENA		((uint32_t)(1<<16))
#define SCB_SHCSR_BUSFAULTENA		((uint32_t)(1<<17))
#define SCB_SHCSR_USGFAULTENA		((uint32_t)(1<<18))
#define SCB_CFSR                (*(volatile uint32_t *)0xE000ED28) // Configurable Fault Status
#define SCB_HFSR                (*(volatile uint32_t *)0xE000ED2C) // HardFault Status
#define SCB_DFSR                (*(volatile uint32_t *)0xE000ED30) // Debug Fault Status
#define SCB_MMFAR               (*(volatile uint32_t *)0xE000ED34) // MemManage Fault Address
#define SCB_BFAR                (*(volatile uint32_t *)0xE000ED38) // Bus Fault Address
#define SCB_AFAR                (*(volatile uint32_t *)0xE000ED3C) // Aux Fault Address
#define SCB_ID_PFR0		(*(const    uint32_t *)0xE000ED40) // Processor Feature 0
#define SCB_ID_PFR1		(*(const    uint32_t *)0xE000ED44) // Processor Feature 1
#define SCB_ID_DFR0		(*(const    uint32_t *)0xE000ED48) // Debug Feature 0
#define SCB_ID_AFR0		(*(const    uint32_t *)0xE000ED4C) // Auxiliary Feature 0
#define SCB_ID_MMFR0		(*(const    uint32_t *)0xE000ED50) // Memory Model Feature 0
#define SCB_ID_MMFR1		(*(const    uint32_t *)0xE000ED54) // Memory Model Feature 1
#define SCB_ID_MMFR2		(*(const    uint32_t *)0xE000ED58) // Memory Model Feature 2
#define SCB_ID_MMFR3		(*(const    uint32_t *)0xE000ED5C) // Memory Model Feature 3
#define SCB_ID_ISAR0		(*(const    uint32_t *)0xE000ED60) // Instruction Set Attribute 0
#define SCB_ID_ISAR1		(*(const    uint32_t *)0xE000ED64) // Instruction Set Attribute 1
#define SCB_ID_ISAR2 		(*(const    uint32_t *)0xE000ED68) // Instruction Set Attribute 2
#define SCB_ID_ISAR3 		(*(const    uint32_t *)0xE000ED6C) // Instruction Set Attribute 3
#define SCB_ID_ISAR4 		(*(const    uint32_t *)0xE000ED70) // Instruction Set Attribute 4
#define SCB_ID_CLIDR		(*(const    uint32_t *)0xE000ED78) // Cache Level ID
#define SCB_ID_CTR		(*(const    uint32_t *)0xE000ED7C) // Cache Type
#define SCB_ID_CCSIDR		(*(const    uint32_t *)0xE000ED80) // Cache Size ID
#define SCB_ID_CSSELR		(*(volatile uint32_t *)0xE000ED84) // Cache Size Selection
#define SCB_CPACR               (*(volatile uint32_t *)0xE000ED88) // Coprocessor Access Control
#define SCB_FPCCR               (*(volatile uint32_t *)0xE000EF34) // FP Context Control
#define SCB_FPCAR               (*(volatile uint32_t *)0xE000EF38) // FP Context Address
#define SCB_FPDSCR              (*(volatile uint32_t *)0xE000EF3C) // FP Default Status Control
#define SCB_MVFR0               (*(volatile uint32_t *)0xE000EF40) // Media & FP Feature 0
#define SCB_MVFR1               (*(volatile uint32_t *)0xE000EF44) // Media & FP Feature 1
#define SCB_MVFR2               (*(volatile uint32_t *)0xE000EF48) // Media & FP Feature 2

#define SYST_CSR                (*(volatile uint32_t *)0xE000E010) // SysTick Control and Status
#define SYST_CSR_COUNTFLAG              ((uint32_t)(1<<16))
#define SYST_CSR_CLKSOURCE              ((uint32_t)(1<<2))
#define SYST_CSR_TICKINT                ((uint32_t)(1<<1))
#define SYST_CSR_ENABLE                 ((uint32_t)(1<<0))
#define SYST_RVR                (*(volatile uint32_t *)0xE000E014) // SysTick Reload Value Register
#define SYST_CVR                (*(volatile uint32_t *)0xE000E018) // SysTick Current Value Register
#define SYST_CALIB              (*(const    uint32_t *)0xE000E01C) // SysTick Calibration Value

// Nested Vectored Interrupt Controller, Table 3-4 & ARMv7 ref, appendix B3.4 (page 750)
#define NVIC_ISER0              (*(volatile uint32_t *)0xE000E100)
#define NVIC_ISER1              (*(volatile uint32_t *)0xE000E104)
#define NVIC_ISER2              (*(volatile uint32_t *)0xE000E108)
#define NVIC_ISER3              (*(volatile uint32_t *)0xE000E10C)
#define NVIC_ISER4              (*(volatile uint32_t *)0xE000E110)
#define NVIC_ICER0              (*(volatile uint32_t *)0xE000E180)
#define NVIC_ICER1              (*(volatile uint32_t *)0xE000E184)
#define NVIC_ICER2              (*(volatile uint32_t *)0xE000E188)
#define NVIC_ICER3              (*(volatile uint32_t *)0xE000E18C)
#define NVIC_ICER4              (*(volatile uint32_t *)0xE000E190)
#define NVIC_STIR		(*(volatile uint32_t *)0xE000EF00)
#define NVIC_ENABLE_IRQ(n)      (*(&NVIC_ISER0 + ((n) >> 5)) = (1 << ((n) & 31)))
#define NVIC_DISABLE_IRQ(n)     (*(&NVIC_ICER0 + ((n) >> 5)) = (1 << ((n) & 31)))
#define NVIC_SET_PENDING(n)     (*((volatile uint32_t *)0xE000E200 + ((n) >> 5)) = (1 << ((n) & 31)))
#define NVIC_CLEAR_PENDING(n)   (*((volatile uint32_t *)0xE000E280 + ((n) >> 5)) = (1 << ((n) & 31)))
#define NVIC_IS_ENABLED(n)      (*(&NVIC_ISER0 + ((n) >> 5)) & (1 << ((n) & 31)))
#define NVIC_IS_PENDING(n)      (*((volatile uint32_t *)0xE000E200 + ((n) >> 5)) & (1 << ((n) & 31)))
#define NVIC_IS_ACTIVE(n)       (*((volatile uint32_t *)0xE000E300 + ((n) >> 5)) & (1 << ((n) & 31)))
#define NVIC_TRIGGER_IRQ(n)     NVIC_STIR=(n)

#define ARM_DEMCR               (*(volatile uint32_t *)0xE000EDFC) // Debug Exception and Monitor Control
#define ARM_DEMCR_TRCENA                (1 << 24)        // Enable debugging & monitoring blocks
#define ARM_DWT_CTRL            (*(volatile uint32_t *)0xE0001000) // DWT control register
#define ARM_DWT_CTRL_CYCCNTENA          (1 << 0)                // Enable cycle count
#define ARM_DWT_CYCCNT          (*(volatile uint32_t *)0xE0001004) // Cycle count register

#define SCB_MPU_TYPE		(*(volatile uint32_t *)0xE000ED90) // 
#define SCB_MPU_CTRL		(*(volatile uint32_t *)0xE000ED94) // 
#define SCB_MPU_CTRL_PRIVDEFENA		((uint32_t)(1<<2)) // Enables default memory map
#define SCB_MPU_CTRL_HFNMIENA		((uint32_t)(1<<1)) // Use MPU for HardFault & NMI
#define SCB_MPU_CTRL_ENABLE		((uint32_t)(1<<0)) // Enables MPU
#define SCB_MPU_RNR		(*(volatile uint32_t *)0xE000ED98) // 
#define SCB_MPU_RBAR		(*(volatile uint32_t *)0xE000ED9C) // 
#define SCB_MPU_RBAR_ADDR_MASK		((uint32_t)(0xFFFFFFE0))
#define SCB_MPU_RBAR_VALID		((uint32_t)(1<<4))
#define SCB_MPU_RBAR_REGION(n)		((uint32_t)((n) & 15))
#define SCB_MPU_RASR		(*(volatile uint32_t *)0xE000EDA0) // ARM DDI0403E, pg 696
#define SCB_MPU_RASR_XN			((uint32_t)(1<<28))
#define SCB_MPU_RASR_AP(n)		((uint32_t)(((n) & 7) << 24))
#define SCB_MPU_RASR_TEX(n)		((uint32_t)(((n) & 7) << 19))
#define SCB_MPU_RASR_S			((uint32_t)(1<<18))
#define SCB_MPU_RASR_C			((uint32_t)(1<<17))
#define SCB_MPU_RASR_B			((uint32_t)(1<<16))
#define SCB_MPU_RASR_SRD(n)		((uint32_t)(((n) & 255) << 8))
#define SCB_MPU_RASR_SIZE(n)		((uint32_t)(((n) & 31) << 1))
#define SCB_MPU_RASR_ENABLE		((uint32_t)(1<<0))
#define SCB_MPU_RBAR_A1		(*(volatile uint32_t *)0xE000EDA4) // 
#define SCB_MPU_RASR_A1		(*(volatile uint32_t *)0xE000EDA8) // 
#define SCB_MPU_RBAR_A2		(*(volatile uint32_t *)0xE000EDAC) // 
#define SCB_MPU_RASR_A2		(*(volatile uint32_t *)0xE000EDB0) // 
#define SCB_MPU_RBAR_A3		(*(volatile uint32_t *)0xE000EDB4) // 
#define SCB_MPU_RASR_A3		(*(volatile uint32_t *)0xE000EDB8) // 

#define SCB_CACHE_ICIALLU	(*(volatile uint32_t *)0xE000EF50)
#define SCB_CACHE_ICIMVAU	(*(volatile uint32_t *)0xE000EF58)
#define SCB_CACHE_DCIMVAC	(*(volatile uint32_t *)0xE000EF5C)
#define SCB_CACHE_DCISW		(*(volatile uint32_t *)0xE000EF60)
#define SCB_CACHE_DCCMVAU	(*(volatile uint32_t *)0xE000EF64)
#define SCB_CACHE_DCCMVAC	(*(volatile uint32_t *)0xE000EF68)
#define SCB_CACHE_DCCSW		(*(volatile uint32_t *)0xE000EF6C)
#define SCB_CACHE_DCCIMVAC	(*(volatile uint32_t *)0xE000EF70)
#define SCB_CACHE_DCCISW	(*(volatile uint32_t *)0xE000EF74)
#define SCB_CACHE_BPIALL	(*(volatile uint32_t *)0xE000EF78)

// Flush data from cache to memory
//
// Normally arm_dcache_flush() is used when metadata written to memory
// will be used by a DMA or a bus-master peripheral.  Any data in the
// cache is written to memory.  A copy remains in the cache, so this is
// typically used with special fields you will want to quickly access
// in the future.  For data transmission, use arm_dcache_flush_delete().
__attribute__((always_inline, unused))
static inline void arm_dcache_flush(void *addr, uint32_t size)
{
	uint32_t location = (uint32_t)addr & 0xFFFFFFE0;
	uint32_t end_addr = (uint32_t)addr + size;
	asm volatile("": : :"memory");
	asm("dsb");
	do {
		SCB_CACHE_DCCMVAC = location;
		location += 32;
	} while (location < end_addr);
	asm("dsb");
	asm("isb");
}

// Delete data from the cache, without touching memory
//
// WARNING: This function is DANGEROUS!!  The address must be
// 32 byte aligned and the size must be a multiple of 32 bytes.
//
// DO NOT USE this function with arbitrarily aligned data,
// especially pointers from malloc() or C++ new.  The ARM cache
// can only delete with granularity of 32 byte cache rows.  If
// you attempt to delete improperly aligned data, any other
// cached variables shared within the same 32 byte cache row(s)
// will become collateral damage!
//
// If you wish to assure some variable or array or other data
// is not cached, use arm_dcache_flush_delete().  This
// arm_dcache_delete() should only be used for very special
// cases like DMA buffers or hardware testing & benchmarks.
//
// See this forum thread for more detail:
// https://forum.pjrc.com/threads/68100-BUG-in-arm_dcache_delete
//
// Normally arm_dcache_delete() is used before receiving data via
// DMA or from bus-master peripherals which write to memory.  You
// want to delete anything the cache may have stored, so your next
// read is certain to access the physical memory.
__attribute__((always_inline, unused))
static inline void arm_dcache_delete(void *addr, uint32_t size)
{
	uint32_t location = (uint32_t)addr & 0xFFFFFFE0;
	uint32_t end_addr = (uint32_t)addr + size;
	asm volatile("": : :"memory");
	asm("dsb");
	do {
		SCB_CACHE_DCIMVAC = location;
		location += 32;
	} while (location < end_addr);
	asm("dsb");
	asm("isb");
}

// Flush data from cache to memory, and delete it from the cache
//
// Normally arm_dcache_flush_delete() is used when transmitting data
// via DMA or bus-master peripherals which read from memory.  You want
// any cached data written to memory, and then removed from the cache,
// because you no longer need to access the data after transmission.
__attribute__((always_inline, unused))
static inline void arm_dcache_flush_delete(void *addr, uint32_t size)
{
	uint32_t location = (uint32_t)addr & 0xFFFFFFE0;
	uint32_t end_addr = (uint32_t)addr + size;
	asm volatile("": : :"memory");
	asm("dsb");
	do {
		SCB_CACHE_DCCIMVAC = location;
		location += 32;
	} while (location < end_addr);
	asm("dsb");
	asm("isb");
}

// Crash report info stored in the top 128 bytes of OCRAM (at 0x2027FF80)
struct arm_fault_info_struct {
	uint32_t len;  // all fields must be 32 bits
	uint32_t ipsr;
	uint32_t cfsr;
	uint32_t hfsr;
	uint32_t mmfar;
	uint32_t bfar;
	uint32_t ret;
	uint32_t xpsr;
	float  temp;
	uint32_t time;
	uint32_t crc;  // crc must be last
};


