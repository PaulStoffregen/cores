#include <stdint.h>

#if !defined(KINETISL) && !defined(KINETISK)
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
        IRQ_BROWNOUT1 =         62,
        IRQ_TEMPERATURE =       63,
        IRQ_TEMPERATURE_PANIC = 64,
        IRQ_USBPHY0 =           65,
        IRQ_USBPHY1 =           66,
        IRQ_ADC1 =              67,
        IRQ_ADC2 =              68,
        IRQ_DCDC =              69,
        IRQ_Reserved1 =         70,
        IRQ_Reserved2 =         71,
        IRQ_GPIO1_INT0 =        72,
        IRQ_GPIO1_INT1 =        73,
        IRQ_GPIO1_INT2 =        74,
        IRQ_GPIO1_INT3 =        75,
        IRQ_GPIO1_INT4 =        76,
        IRQ_GPIO1_INT5 =        77,
        IRQ_GPIO1_INT6 =        78,
        IRQ_GPIO1_INT7 =        79,
        IRQ_GPI01_0_15 =        80,
        IRQ_GPIO1_16_31 =       81,
        IRQ_GPI02_0_15 =        82,
        IRQ_GPIO2_16_31 =       83,
        IRQ_GPI03_0_15 =        84,
        IRQ_GPIO3_16_31 =       85,
        IRQ_GPI04_0_15 =        86,
        IRQ_GPIO4_16_31 =       87,
        IRQ_GPI05_0_15 =        88,
        IRQ_GPIO5_16_31 =       89,
        IRQ_FLEXIO1 =           90,
        IRQ_FLEXIO2 =           91,
        IRQ_WDOG1 =             92,
        IRQ_WDOG3 =             93,
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
        IRQ_Reserved4 =         107,
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
        IRQ_ACMP0 =             123,
        IRQ_ACMP1 =             124,
        IRQ_ACMP2 =             125,
        IRQ_ACMP3 =             126,
        IRQ_Reserved5 =         127,
        IRQ_Reserved6 =         128,
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
        IRQ_Reserved7 =         152,
        IRQ_Reserved8 =         153,
        IRQ_Reserved9 =         154,
        IRQ_Reserved10 =        155,
        IRQ_Reserved11 =        156,
        IRQ_Reserved12 =        157,
        IRQ_SJC_DEBUG =         158,
        IRQ_NMI_WAKEUP =        159
};
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

// page 684
#define IMXRT_AIPSTZ1		(*(IMXRT_REGISTER32_t *)0x4007C000)
#define IMXRT_AIPSTZ2		(*(IMXRT_REGISTER32_t *)0x4017C000)
#define IMXRT_AIPSTZ3		(*(IMXRT_REGISTER32_t *)0x4027C000)
#define IMXRT_AIPSTZ4		(*(IMXRT_REGISTER32_t *)0x4037C000)
#define AIPSTZ1_MPR			(IMXRT_AIPSTZ1.offset000)
#define AIPSTZ1_OPACR			(IMXRT_AIPSTZ1.offset040)
#define AIPSTZ1_OPACR1			(IMXRT_AIPSTZ1.offset044)
#define AIPSTZ1_OPACR2			(IMXRT_AIPSTZ1.offset048)
#define AIPSTZ1_OPACR3			(IMXRT_AIPSTZ1.offset04C)
#define AIPSTZ1_OPACR4			(IMXRT_AIPSTZ1.offset050)
#define AIPSTZ2_MPR			(IMXRT_AIPSTZ2.offset000)
#define AIPSTZ2_OPACR			(IMXRT_AIPSTZ2.offset040)
#define AIPSTZ2_OPACR1			(IMXRT_AIPSTZ2.offset044)
#define AIPSTZ2_OPACR2			(IMXRT_AIPSTZ2.offset048)
#define AIPSTZ2_OPACR3			(IMXRT_AIPSTZ2.offset04C)
#define AIPSTZ2_OPACR4			(IMXRT_AIPSTZ2.offset050)
#define AIPSTZ3_MPR			(IMXRT_AIPSTZ3.offset000)
#define AIPSTZ3_OPACR			(IMXRT_AIPSTZ3.offset040)
#define AIPSTZ3_OPACR1			(IMXRT_AIPSTZ3.offset044)
#define AIPSTZ3_OPACR2			(IMXRT_AIPSTZ3.offset048)
#define AIPSTZ3_OPACR3			(IMXRT_AIPSTZ3.offset04C)
#define AIPSTZ3_OPACR4			(IMXRT_AIPSTZ3.offset050)
#define AIPSTZ4_MPR			(IMXRT_AIPSTZ4.offset000)
#define AIPSTZ4_OPACR			(IMXRT_AIPSTZ4.offset040)
#define AIPSTZ4_OPACR1			(IMXRT_AIPSTZ4.offset044)
#define AIPSTZ4_OPACR2			(IMXRT_AIPSTZ4.offset048)
#define AIPSTZ4_OPACR3			(IMXRT_AIPSTZ4.offset04C)
#define AIPSTZ4_OPACR4			(IMXRT_AIPSTZ4.offset050)

// page 706  (offsets are wrong)
#define IMXRT_AOI1		(*(IMXRT_REGISTER16_t *)0x403B4000)
#define AOI1_BFCRT010			(IMXRT_AOI1.offset000)
#define AOI1_BFCRT230			(IMXRT_AOI1.offset002)
#define AOI1_BFCRT011			(IMXRT_AOI1.offset004)
#define AOI1_BFCRT231			(IMXRT_AOI1.offset006)
#define AOI1_BFCRT012			(IMXRT_AOI1.offset008)
#define AOI1_BFCRT232			(IMXRT_AOI1.offset00A)
#define AOI1_BFCRT013			(IMXRT_AOI1.offset00C)
#define AOI1_BFCRT233			(IMXRT_AOI1.offset00E)
#define IMXRT_AOI2		(*(IMXRT_REGISTER16_t *)0x403B8000)
#define AOI2_BFCRT010			(IMXRT_AOI2.offset000)
#define AOI2_BFCRT230			(IMXRT_AOI2.offset002)
#define AOI2_BFCRT011			(IMXRT_AOI2.offset004)
#define AOI2_BFCRT231			(IMXRT_AOI2.offset006)
#define AOI2_BFCRT012			(IMXRT_AOI2.offset008)
#define AOI2_BFCRT232			(IMXRT_AOI2.offset00A)
#define AOI2_BFCRT013			(IMXRT_AOI2.offset00C)
#define AOI2_BFCRT233			(IMXRT_AOI2.offset00E)

// page 708
#define IMXRT_CCM		(*(IMXRT_REGISTER32_t *)0x400FC000)
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
#define CCM_CMEOR			(IMXRT_CCM.offset088)
#define CCM_CCR_RBC_EN				((uint32_t)0x08000000)
#define CCM_CCR_REG_BYPASS_COUNT(n)		((uint32_t)(((n) & 0x3F) << 21))
#define CCM_CCR_COSC_EN				((uint32_t)0x00001000)
#define CCM_CCR_OSCNT(n)			((uint32_t)(((n) & 0xFF) << 0))
#define CCM_CSR_COSC_READY			((uint32_t)0x00000020)
#define CCM_CSR_CAMP2_READY			((uint32_t)0x00000008)
#define CCM_CSR_REF_EN_B			((uint32_t)0x00000001)
#define CCM_CCSR_PLL3_SW_CLK_SEL		((uint32_t)0x00000001)
#define CCM_CACRR_ARM_PODF(n)			((uint32_t)(((n) & 0x07) << 0))
#define CCM_CBCDR_PERIPH_CLK2_PODF(n)		((uint32_t)(((n) & 0x07) << 27))
#define CCM_CBCDR_PERIPH_CLK_SEL		((uint32_t)0x02000000)
#define CCM_CBCDR_SEMC_PODF(n)			((uint32_t)(((n) & 0x07) << 16))
#define CCM_CBCDR_AHB_PODF(n)			((uint32_t)(((n) & 0x07) << 10))
#define CCM_CBCDR_IPG_PODF(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CBCDR_SEMC_ALT_CLK_SEL		((uint32_t)0x00000080)
#define CCM_CBCDR_SEMC_CLK_SEL			((uint32_t)0x00000040)
#define CCM_CBCMR_LPSPI_PODF(n)			((uint32_t)(((n) & 0x07) << 26))
#define CCM_CBCMR_LCDIF_PODF(n)			((uint32_t)(((n) & 0x07) << 23))
#define CCM_CBCMR_PRE_PERIPH_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 18))
#define CCM_CBCMR_TRACE_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 14))
#define CCM_CBCMR_PERIPH_CLK2_SEL(n)		((uint32_t)(((n) & 0x03) << 12))
#define CCM_CBCMR_LPSPI_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 5))
#define CCM_CSCMR1_FLEXSPI_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 29))
#define CCM_CSCMR1_FLEXSPI_PODF(n)		((uint32_t)(((n) & 0x07) << 23))
#define CCM_CSCMR1_USDHC2_CLK_SEL		((uint32_t)0x00020000)
#define CCM_CSCMR1_USDHC1_CLK_SEL		((uint32_t)0x00010000)
#define CCM_CSCMR1_SAI3_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 14))
#define CCM_CSCMR1_SAI2_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 12))
#define CCM_CSCMR1_SAI1_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 10))
#define CCM_CSCMR1_PERCLK_CLK_SEL		((uint32_t)0x00000040)
#define CCM_CSCMR1_PERCLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 0))
#define CCM_CSCMR2_FLEXIO2_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 19))
#define CCM_CSCMR2_CAN_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 8))
#define CCM_CSCMR2_CAN_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 2))
#define CCM_CSCDR1_TRACE_PODF(n)		((uint32_t)(((n) & 0x07) << 25))
#define CCM_CSCDR1_USDHC2_PODF(n)		((uint32_t)(((n) & 0x07) << 16))
#define CCM_CSCDR1_USDHC1_PODF(n)		((uint32_t)(((n) & 0x07) << 11))
#define CCM_CSCDR1_UART_CLK_SEL			((uint32_t)0x00000040)
#define CCM_CSCDR1_UART_CLK_PODF(n)		((uint32_t)(((n) & 0x1F) << 0))
#define CCM_CS1CDR_FLEXIO2_CLK_PODF(n)		((uint32_t)(((n) & 0x07) << 25))
#define CCM_CS1CDR_SAI3_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 22))
#define CCM_CS1CDR_SAI3_CLK_PODF(n)		((uint32_t)(((n) & 0x1F) << 16))
#define CCM_CS1CDR_FLEXIO2_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 9))
#define CCM_CS1CDR_SAI1_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 6))
#define CCM_CS1CDR_SAI1_CLK_PODF(n)		((uint32_t)(((n) & 0x1F) << 0))
#define CCM_CS2CDR_SAI2_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 6))
#define CCM_CS2CDR_SAI2_CLK_PODF(n)		((uint32_t)(((n) & 0x3F) << 0))
#define CCM_CDCDR_SPDIF0_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 25))
#define CCM_CDCDR_SPDIF0_CLK_PODF(n)		((uint32_t)(((n) & 0x07) << 22))
#define CCM_CDCDR_SPDIF0_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 20))
#define CCM_CDCDR_FLEXIO1_CLK_PRED(n)		((uint32_t)(((n) & 0x07) << 12))
#define CCM_CDCDR_FLEXIO1_CLK_PODF(n)		((uint32_t)(((n) & 0x07) << 9))
#define CCM_CDCDR_FLEXIO1_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 7))
#define CCM_CSCDR2_LPI2C_CLK_PODF(n)		((uint32_t)(((n) & 0x1F) << 19))
#define CCM_CSCDR2_LPI2C_CLK_SEL		((uint32_t)0x00040000)
#define CCM_CSCDR2_LCDIF_PRE_CLK_SEL(n)		((uint32_t)(((n) & 0x07) << 15))
#define CCM_CSCDR2_LCDIF_PRED(n)		((uint32_t)(((n) & 0x07) << 12))
#define CCM_CSCDR2_LCDIF_CLK_SEL(n)		((uint32_t)(((n) & 0x07) << 9))
#define CCM_CSCDR3_CSI_PODF(n)			((uint32_t)(((n) & 0x07) << 11))
#define CCM_CSCDR3_CSI_CLK_SEL(n)		((uint32_t)(((n) & 0x03) << 9))
#define CCM_CDHIPR_ARM_PODF_BUSY		((uint32_t)0x00010000)
#define CCM_CDHIPR_PERIPH_CLK_SEL_BUSY		((uint32_t)0x00000020)
#define CCM_CDHIPR_PERIPH2_CLK_SEL_BUSY		((uint32_t)0x00000008)
#define CCM_CDHIPR_AHB_PODF_BUSY		((uint32_t)0x00000002)
#define CCM_CDHIPR_SEMC_PODF_BUSY		((uint32_t)0x00000001)
#define CCM_CLPCR_MASK_L2CC_IDLE		((uint32_t)0x08000000)
#define CCM_CLPCR_MASK_SCU_IDLE			((uint32_t)0x04000000)
#define CCM_CLPCR_MASK_CORE0_WFI		((uint32_t)0x00400000)
#define CCM_CLPCR_BYPASS_LPM_HS0		((uint32_t)0x00200000)
#define CCM_CLPCR_BYPASS_LPM_HS1		((uint32_t)0x00080000)
#define CCM_CLPCR_COSC_PWRDOWN			((uint32_t)0x00000800)
#define CCM_CLPCR_STBY_COUNT(n)			((uint32_t)(((n) & 0x03) << 9))
#define CCM_CLPCR_VSTBY				((uint32_t)0x00000100)
#define CCM_CLPCR_DIS_REF_OSC			((uint32_t)0x00000080)
#define CCM_CLPCR_SBYOS				((uint32_t)0x00000040)
#define CCM_CLPCR_ARM_CLK_DIS_ON_LPM		((uint32_t)0x00000020)
#define CCM_CLPCR_LPM(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CISR_ARM_PODF_LOADED		((uint32_t)0x04000000)
#define CCM_CISR_PERIPH_CLK_SEL_LOADED		((uint32_t)0x00400000)
#define CCM_CISR_AHB_PODF_LOADED		((uint32_t)0x00100000)
#define CCM_CISR_PERIPH2_CLK_SEL_LOADED		((uint32_t)0x00080000)
#define CCM_CISR_SEMC_PODF_LOADED		((uint32_t)0x00020000)
#define CCM_CISR_COSC_READY			((uint32_t)0x00000040)
#define CCM_CISR_LRF_PLL			((uint32_t)0x00000001)
#define CCM_CIMR_ARM_PODF_LOADED		((uint32_t)0x04000000)
#define CCM_CIMR_MASK_PERIPH_CLK_SEL_LOADED	((uint32_t)0x00400000)
#define CCM_CIMR_MASK_AHB_PODF_LOADED		((uint32_t)0x00100000)
#define CCM_CIMR_MASK_PERIPH2_CLK_SEL_LOADED	((uint32_t)0x00080000)
#define CCM_CIMR_MASK_SEMC_PODF_LOADED		((uint32_t)0x00020000)
#define CCM_CIMR_MASK_COSC_READY		((uint32_t)0x00000040)
#define CCM_CIMR_MASK_LRF_PLL			((uint32_t)0x00000001)
#define CCM_CCOSR_CLKO2_EN			((uint32_t)0x01000000)
#define CCM_CCOSR_CLKO2_DIV(n)			((uint32_t)(((n) & 0x07) << 21))
#define CCM_CCOSR_CLKO2_SEL(n)			((uint32_t)(((n) & 0x1F) << 16))
#define CCM_CCOSR_CLK_OUT_SEL			((uint32_t)0x00000100)
#define CCM_CCOSR_CLKO1_EN			((uint32_t)0x00000080)
#define CCM_CCOSR_CLKO1_DIV(n)			((uint32_t)(((n) & 0x07) << 4))
#define CCM_CCOSR_CLKO1_SEL(n)			((uint32_t)(((n) & 0x0F) << 0))
#define CCM_CGPR_INT_MEM_CLK_LPM		((uint32_t)0x00020000)
#define CCM_CGPR_FPL				((uint32_t)0x00010000)
#define CCM_CGPR_SYS_MEM_DS_CTRL(n)		((uint32_t)(((n) & 0x03) << 14))
#define CCM_CGPR_EFUSE_PROG_SUPPLY_GATE		((uint32_t)0x00000010)
#define CCM_CGPR_PMIC_DELAY_SCALER		((uint32_t)0x00000001)
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
#define CCM_CCGR0_CAN1_SERIAl(n)		((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR0_CAN1(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR0_LPUART3(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR0_DCP(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR0_MQS_HMCLK(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR0_AIPS_TZ2(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR0_aips_tz1(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CCGR1_CSU(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR1_GPIO1(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR1_LPUART4(n)			((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR1_GPT_SERIAL(n)			((uint32_t)(((n) & 0x03) << 22))
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
#define CCM_CCGR2_(n)				((uint32_t)(((n) & 0x03) << 0))
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
#define CCM_CCGR6_TIMER3(n)			((uint32_t)(((n) & 0x03) << 30))
#define CCM_CCGR6_TIMER2(n)			((uint32_t)(((n) & 0x03) << 28))
#define CCM_CCGR6_TIMER1(n)			((uint32_t)(((n) & 0x03) << 26))
#define CCM_CCGR6_LPI2C4_SERIAL(n)		((uint32_t)(((n) & 0x03) << 24))
#define CCM_CCGR6_ANADIG(n)			((uint32_t)(((n) & 0x03) << 22))
#define CCM_CCGR6_SIM_PER(n)			((uint32_t)(((n) & 0x03) << 20))
#define CCM_CCGR6_AIPS_TZ3(n)			((uint32_t)(((n) & 0x03) << 18))
#define CCM_CCGR6_TIMER4(n)			((uint32_t)(((n) & 0x03) << 16))
#define CCM_CCGR6_LPUART8(n)			((uint32_t)(((n) & 0x03) << 14))
#define CCM_CCGR6_TRNG(n)			((uint32_t)(((n) & 0x03) << 12))
#define CCM_CCGR6_FLEXSPi(n)			((uint32_t)(((n) & 0x03) << 10))
#define CCM_CCGR6_IPMUX4(n)			((uint32_t)(((n) & 0x03) << 8))
#define CCM_CCGR6_DCDC(n)			((uint32_t)(((n) & 0x03) << 6))
#define CCM_CCGR6_USDHC2(n)			((uint32_t)(((n) & 0x03) << 4))
#define CCM_CCGR6_USDHC1(n)			((uint32_t)(((n) & 0x03) << 2))
#define CCM_CCGR6_USBOH3(n)			((uint32_t)(((n) & 0x03) << 0))
#define CCM_CMEOR_MOD_EN_OV_CAN1_CPI		((uint32_t)0x40000000)
#define CCM_CMEOR_MOD_EN_OV_CAN2_CPI		((uint32_t)0x10000000)
#define CCM_CMEOR_MOD_EN_OV_TRNG		((uint32_t)0x00000200)
#define CCM_CMEOR_MOD_EN_USDHC			((uint32_t)0x00000080)
#define CCM_CMEOR_MOD_EN_OV_PIT			((uint32_t)0x00000040)
#define CCM_CMEOR_MOD_EN_OV_GPT			((uint32_t)0x00000020)

// page 796
#define IMXRT_CCM_ANALOG	(*(IMXRT_REGISTER32_t *)0x400D8000)
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
#define CCM_ANALOG_PLL_ENET		(IMXRT_CCM_ANALOG.offset0EC)
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

// page 852
#define IMXRT_CSI		(*(IMXRT_REGISTER32_t *)0x402BC000)
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
#define CSI_CSICR18			(IMXRT_CSI.offset038)
#define CSI_CSICR19			(IMXRT_CSI.offset03C)

// page 878
#define IMXRT_DCDC		(*(IMXRT_REGISTER32_t *)0x40080000)
#define DCDC_REG0			(IMXRT_DCDC.offset000)
#define DCDC_REG1			(IMXRT_DCDC.offset004)
#define DCDC_REG2			(IMXRT_DCDC.offset008)
#define DCDC_REG3			(IMXRT_DCDC.offset00C)

// page 489
#define IMXRT_CMP1		(*(IMXRT_REGISTER8_t *)0x40094000)
#define CMP1_CR0			(IMXRT_CMP1.offset00)
#define CMP1_CR1			(IMXRT_CMP1.offset01)
#define CMP1_FPR			(IMXRT_CMP1.offset02)
#define CMP1_SCR			(IMXRT_CMP1.offset03)
#define CMP1_DACCR			(IMXRT_CMP1.offset04)
#define CMP1_MUXCR			(IMXRT_CMP1.offset05)
#define IMXRT_CMP2		(*(IMXRT_REGISTER8_t *)0x40094008)
#define CMP2_CR0			(IMXRT_CMP2.offset00)
#define CMP2_CR1			(IMXRT_CMP2.offset01)
#define CMP2_FPR			(IMXRT_CMP2.offset02)
#define CMP2_SCR			(IMXRT_CMP2.offset03)
#define CMP2_DACCR			(IMXRT_CMP2.offset04)
#define CMP2_MUXCR			(IMXRT_CMP2.offset05)
#define IMXRT_CMP3		(*(IMXRT_REGISTER8_t *)0x40094010)
#define CMP3_CR0			(IMXRT_CMP3.offset00)
#define CMP3_CR1			(IMXRT_CMP3.offset01)
#define CMP3_FPR			(IMXRT_CMP3.offset02)
#define CMP3_SCR			(IMXRT_CMP3.offset03)
#define CMP3_DACCR			(IMXRT_CMP3.offset04)
#define CMP3_MUXCR			(IMXRT_CMP3.offset05)
#define IMXRT_CMP4		(*(IMXRT_REGISTER8_t *)0x40094018)
#define CMP4_CR0			(IMXRT_CMP4.offset00)
#define CMP4_CR1			(IMXRT_CMP4.offset01)
#define CMP4_FPR			(IMXRT_CMP4.offset02)
#define CMP4_SCR			(IMXRT_CMP4.offset03)
#define CMP4_DACCR			(IMXRT_CMP4.offset04)
#define CMP4_MUXCR			(IMXRT_CMP4.offset05)

// page 538
#define IMXRT_ADC1		(*(IMXRT_REGISTER32_t *)0x400C4000)
#define ADC1_HC0			(IMXRT_ADC1.offset000)
#define ADC1_HC1			(IMXRT_ADC1.offset004)
#define ADC1_HS				(IMXRT_ADC1.offset008)
#define ADC1_R0				(IMXRT_ADC1.offset00C)
#define ADC1_R1				(IMXRT_ADC1.offset010)
#define ADC1_CFG			(IMXRT_ADC1.offset014)
#define ADC1_GC				(IMXRT_ADC1.offset018)
#define ADC1_GS				(IMXRT_ADC1.offset01C)
#define ADC1_CV				(IMXRT_ADC1.offset020)
#define ADC1_OFS			(IMXRT_ADC1.offset024)
#define ADC1_CAL			(IMXRT_ADC1.offset028)

// page 552
#define IMXRT_ADC2		(*(IMXRT_REGISTER32_t *)0x400C8000)
#define ADC2_HC0			(IMXRT_ADC2.offset000)
#define ADC2_HC1			(IMXRT_ADC2.offset004)
#define ADC2_HC2			(IMXRT_ADC2.offset008)
#define ADC2_HC3			(IMXRT_ADC2.offset00C)
#define ADC2_HC4			(IMXRT_ADC2.offset010)
#define ADC2_HS				(IMXRT_ADC2.offset014)
#define ADC2_R0				(IMXRT_ADC2.offset018)
#define ADC2_R1				(IMXRT_ADC2.offset01C)
#define ADC2_R2				(IMXRT_ADC2.offset020)
#define ADC2_R3				(IMXRT_ADC2.offset024)
#define ADC2_R4				(IMXRT_ADC2.offset028)
#define ADC2_CFG			(IMXRT_ADC2.offset02C)
#define ADC2_GC				(IMXRT_ADC2.offset030)
#define ADC2_GS				(IMXRT_ADC2.offset034)
#define ADC2_CV				(IMXRT_ADC2.offset038)
#define ADC2_OFS			(IMXRT_ADC2.offset03C)
#define ADC2_CAL			(IMXRT_ADC2.offset040)

// page 891
#define IMXRT_DMAMUX		(*(IMXRT_REGISTER32_t *)0x400EC000)
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

// page 906
// TODO: DMA is complicated...

// page 1063 (offsets are wrong)
#define IMXRT_ENC1		(*(IMXRT_REGISTER16_t *)0x403C8000)
#define ENC1_CTRL			(IMXRT_ENC1.offset000)
#define ENC1_FILT			(IMXRT_ENC1.offset002)
#define ENC1_WTR			(IMXRT_ENC1.offset004)
#define ENC1_POSD			(IMXRT_ENC1.offset006)
#define ENC1_POSDH			(IMXRT_ENC1.offset008)
#define ENC1_REV			(IMXRT_ENC1.offset00A)
#define ENC1_REVH			(IMXRT_ENC1.offset00C)
#define ENC1_UPOS			(IMXRT_ENC1.offset00E)
#define ENC1_LPOS			(IMXRT_ENC1.offset010)
#define ENC1_UPOSH			(IMXRT_ENC1.offset012)
#define ENC1_LPOSH			(IMXRT_ENC1.offset014)
#define ENC1_UINIT			(IMXRT_ENC1.offset016)
#define ENC1_LINIT			(IMXRT_ENC1.offset018)
#define ENC1_IMR			(IMXRT_ENC1.offset01A)
#define ENC1_TST			(IMXRT_ENC1.offset01C)
#define ENC1_CTRL2			(IMXRT_ENC1.offset01E)
#define ENC1_UMOD			(IMXRT_ENC1.offset020)
#define ENC1_LMOD			(IMXRT_ENC1.offset022)
#define ENC1_UCOMP			(IMXRT_ENC1.offset024)
#define ENC1_LCOMP			(IMXRT_ENC1.offset026)
#define IMXRT_ENC2		(*(IMXRT_REGISTER16_t *)0x403CC000)
#define ENC2_CTRL			(IMXRT_ENC2.offset000)
#define ENC2_FILT			(IMXRT_ENC2.offset002)
#define ENC2_WTR			(IMXRT_ENC2.offset004)
#define ENC2_POSD			(IMXRT_ENC2.offset006)
#define ENC2_POSDH			(IMXRT_ENC2.offset008)
#define ENC2_REV			(IMXRT_ENC2.offset00A)
#define ENC2_REVH			(IMXRT_ENC2.offset00C)
#define ENC2_UPOS			(IMXRT_ENC2.offset00E)
#define ENC2_LPOS			(IMXRT_ENC2.offset010)
#define ENC2_UPOSH			(IMXRT_ENC2.offset012)
#define ENC2_LPOSH			(IMXRT_ENC2.offset014)
#define ENC2_UINIT			(IMXRT_ENC2.offset016)
#define ENC2_LINIT			(IMXRT_ENC2.offset018)
#define ENC2_IMR			(IMXRT_ENC2.offset01A)
#define ENC2_TST			(IMXRT_ENC2.offset01C)
#define ENC2_CTRL2			(IMXRT_ENC2.offset01E)
#define ENC2_UMOD			(IMXRT_ENC2.offset020)
#define ENC2_LMOD			(IMXRT_ENC2.offset022)
#define ENC2_UCOMP			(IMXRT_ENC2.offset024)
#define ENC2_LCOMP			(IMXRT_ENC2.offset026)
#define IMXRT_ENC3		(*(IMXRT_REGISTER16_t *)0x403D0000)
#define ENC3_CTRL			(IMXRT_ENC3.offset000)
#define ENC3_FILT			(IMXRT_ENC3.offset002)
#define ENC3_WTR			(IMXRT_ENC3.offset004)
#define ENC3_POSD			(IMXRT_ENC3.offset006)
#define ENC3_POSDH			(IMXRT_ENC3.offset008)
#define ENC3_REV			(IMXRT_ENC3.offset00A)
#define ENC3_REVH			(IMXRT_ENC3.offset00C)
#define ENC3_UPOS			(IMXRT_ENC3.offset00E)
#define ENC3_LPOS			(IMXRT_ENC3.offset010)
#define ENC3_UPOSH			(IMXRT_ENC3.offset012)
#define ENC3_LPOSH			(IMXRT_ENC3.offset014)
#define ENC3_UINIT			(IMXRT_ENC3.offset016)
#define ENC3_LINIT			(IMXRT_ENC3.offset018)
#define ENC3_IMR			(IMXRT_ENC3.offset01A)
#define ENC3_TST			(IMXRT_ENC3.offset01C)
#define ENC3_CTRL2			(IMXRT_ENC3.offset01E)
#define ENC3_UMOD			(IMXRT_ENC3.offset020)
#define ENC3_LMOD			(IMXRT_ENC3.offset022)
#define ENC3_UCOMP			(IMXRT_ENC3.offset024)
#define ENC3_LCOMP			(IMXRT_ENC3.offset026)
#define IMXRT_ENC4		(*(IMXRT_REGISTER16_t *)0x403D4000)
#define ENC4_CTRL			(IMXRT_ENC4.offset000)
#define ENC4_FILT			(IMXRT_ENC4.offset002)
#define ENC4_WTR			(IMXRT_ENC4.offset004)
#define ENC4_POSD			(IMXRT_ENC4.offset006)
#define ENC4_POSDH			(IMXRT_ENC4.offset008)
#define ENC4_REV			(IMXRT_ENC4.offset00A)
#define ENC4_REVH			(IMXRT_ENC4.offset00C)
#define ENC4_UPOS			(IMXRT_ENC4.offset00E)
#define ENC4_LPOS			(IMXRT_ENC4.offset010)
#define ENC4_UPOSH			(IMXRT_ENC4.offset012)
#define ENC4_LPOSH			(IMXRT_ENC4.offset014)
#define ENC4_UINIT			(IMXRT_ENC4.offset016)
#define ENC4_LINIT			(IMXRT_ENC4.offset018)
#define ENC4_IMR			(IMXRT_ENC4.offset01A)
#define ENC4_TST			(IMXRT_ENC4.offset01C)
#define ENC4_CTRL2			(IMXRT_ENC4.offset01E)
#define ENC4_UMOD			(IMXRT_ENC4.offset020)
#define ENC4_LMOD			(IMXRT_ENC4.offset022)
#define ENC4_UCOMP			(IMXRT_ENC4.offset024)
#define ENC4_LCOMP			(IMXRT_ENC4.offset026)

// page 1088
#define IMXRT_ENET		(*(IMXRT_REGISTER32_t *)0x402D8000)
#define IMXRT_ENET_TIMER	(*(IMXRT_REGISTER32_t *)0x402D8400)
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

// page 1226
#define IMXRT_EWM		(*(IMXRT_REGISTER8_t *)0x402D8000)
#define EWM_CTRL			(IMXRT_EWM.offset00)
#define EWM_SERV			(IMXRT_EWM.offset01)
#define EWM_CMPL			(IMXRT_EWM.offset02)
#define EWM_CMPH			(IMXRT_EWM.offset03)
#define EWM_CLKCTRL			(IMXRT_EWM.offset04)
#define EWM_CLKPRESCALER		(IMXRT_EWM.offset05)

// page 1277
#define IMXRT_FLEXCAN1		(*(IMXRT_REGISTER32_t *)0x401D0000)
#define IMXRT_FLEXCAN1_MASK	(*(IMXRT_REGISTER32_t *)0x401D0800)
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
#define IMXRT_FLEXCAN2		(*(IMXRT_REGISTER32_t *)0x401D4000)
#define IMXRT_FLEXCAN2_MASK	(*(IMXRT_REGISTER32_t *)0x401D4800)
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

// page 1320
#define IMXRT_FLEXIO1		(*(IMXRT_REGISTER32_t *)0x401AC000)
#define IMXRT_FLEXIO1_b		(*(IMXRT_REGISTER32_t *)0x401AC400)
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
#define FLEXIO1_SHIFTCFG0		(IMXRT_FLEXIO1.offset100)
#define FLEXIO1_SHIFTCFG1		(IMXRT_FLEXIO1.offset104)
#define FLEXIO1_SHIFTCFG2		(IMXRT_FLEXIO1.offset108)
#define FLEXIO1_SHIFTCFG3		(IMXRT_FLEXIO1.offset10C)
#define FLEXIO1_SHIFTBUF0		(IMXRT_FLEXIO1.offset200)
#define FLEXIO1_SHIFTBUF1		(IMXRT_FLEXIO1.offset204)
#define FLEXIO1_SHIFTBUF2		(IMXRT_FLEXIO1.offset208)
#define FLEXIO1_SHIFTBUF3		(IMXRT_FLEXIO1.offset20C)
#define FLEXIO1_SHIFTBUFBIS0		(IMXRT_FLEXIO1.offset280)
#define FLEXIO1_SHIFTBUFBIS1		(IMXRT_FLEXIO1.offset284)
#define FLEXIO1_SHIFTBUFBIS2		(IMXRT_FLEXIO1.offset288)
#define FLEXIO1_SHIFTBUFBIS3		(IMXRT_FLEXIO1.offset28C)
#define FLEXIO1_SHIFTBUFBYS0		(IMXRT_FLEXIO1.offset300)
#define FLEXIO1_SHIFTBUFBYS1		(IMXRT_FLEXIO1.offset304)
#define FLEXIO1_SHIFTBUFBYS2		(IMXRT_FLEXIO1.offset308)
#define FLEXIO1_SHIFTBUFBYS3		(IMXRT_FLEXIO1.offset30C)
#define FLEXIO1_SHIFTBUFBBS0		(IMXRT_FLEXIO1.offset380)
#define FLEXIO1_SHIFTBUFBBS1		(IMXRT_FLEXIO1.offset384)
#define FLEXIO1_SHIFTBUFBBS2		(IMXRT_FLEXIO1.offset388)
#define FLEXIO1_SHIFTBUFBBS3		(IMXRT_FLEXIO1.offset38C)
#define FLEXIO1_TIMCTL0			(IMXRT_FLEXIO1_b.offset000)
#define FLEXIO1_TIMCTL1			(IMXRT_FLEXIO1_b.offset004)
#define FLEXIO1_TIMCTL2			(IMXRT_FLEXIO1_b.offset008)
#define FLEXIO1_TIMCTL3			(IMXRT_FLEXIO1_b.offset00C)
#define FLEXIO1_TIMCFG0			(IMXRT_FLEXIO1_b.offset080)
#define FLEXIO1_TIMCFG1			(IMXRT_FLEXIO1_b.offset084)
#define FLEXIO1_TIMCFG2			(IMXRT_FLEXIO1_b.offset088)
#define FLEXIO1_TIMCFG3			(IMXRT_FLEXIO1_b.offset08C)
#define FLEXIO1_TIMCMP0			(IMXRT_FLEXIO1_b.offset100)
#define FLEXIO1_TIMCMP1			(IMXRT_FLEXIO1_b.offset104)
#define FLEXIO1_TIMCMP2			(IMXRT_FLEXIO1_b.offset108)
#define FLEXIO1_TIMCMP3			(IMXRT_FLEXIO1_b.offset10C)
#define FLEXIO1_SHIFTBUFNBS0		(IMXRT_FLEXIO1_b.offset280)
#define FLEXIO1_SHIFTBUFNBS1		(IMXRT_FLEXIO1_b.offset284)
#define FLEXIO1_SHIFTBUFNBS2		(IMXRT_FLEXIO1_b.offset288)
#define FLEXIO1_SHIFTBUFNBS3		(IMXRT_FLEXIO1_b.offset28C)
#define FLEXIO1_SHIFTBUFHWS0		(IMXRT_FLEXIO1_b.offset300)
#define FLEXIO1_SHIFTBUFHWS1		(IMXRT_FLEXIO1_b.offset304)
#define FLEXIO1_SHIFTBUFHWS2		(IMXRT_FLEXIO1_b.offset308)
#define FLEXIO1_SHIFTBUFHWS3		(IMXRT_FLEXIO1_b.offset30C)
#define FLEXIO1_SHIFTBUFNIS0		(IMXRT_FLEXIO1_b.offset380)
#define FLEXIO1_SHIFTBUFNIS1		(IMXRT_FLEXIO1_b.offset384)
#define FLEXIO1_SHIFTBUFNIS2		(IMXRT_FLEXIO1_b.offset388)
#define FLEXIO1_SHIFTBUFNIS3		(IMXRT_FLEXIO1_b.offset38C)
#define IMXRT_FLEXIO2		(*(IMXRT_REGISTER32_t *)0x401B0000)
#define IMXRT_FLEXIO2_b		(*(IMXRT_REGISTER32_t *)0x401B0400)
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
#define FLEXIO2_SHIFTCFG0		(IMXRT_FLEXIO2.offset100)
#define FLEXIO2_SHIFTCFG1		(IMXRT_FLEXIO2.offset104)
#define FLEXIO2_SHIFTCFG2		(IMXRT_FLEXIO2.offset108)
#define FLEXIO2_SHIFTCFG3		(IMXRT_FLEXIO2.offset10C)
#define FLEXIO2_SHIFTBUF0		(IMXRT_FLEXIO2.offset200)
#define FLEXIO2_SHIFTBUF1		(IMXRT_FLEXIO2.offset204)
#define FLEXIO2_SHIFTBUF2		(IMXRT_FLEXIO2.offset208)
#define FLEXIO2_SHIFTBUF3		(IMXRT_FLEXIO2.offset20C)
#define FLEXIO2_SHIFTBUFBIS0		(IMXRT_FLEXIO2.offset280)
#define FLEXIO2_SHIFTBUFBIS1		(IMXRT_FLEXIO2.offset284)
#define FLEXIO2_SHIFTBUFBIS2		(IMXRT_FLEXIO2.offset288)
#define FLEXIO2_SHIFTBUFBIS3		(IMXRT_FLEXIO2.offset28C)
#define FLEXIO2_SHIFTBUFBYS0		(IMXRT_FLEXIO2.offset300)
#define FLEXIO2_SHIFTBUFBYS1		(IMXRT_FLEXIO2.offset304)
#define FLEXIO2_SHIFTBUFBYS2		(IMXRT_FLEXIO2.offset308)
#define FLEXIO2_SHIFTBUFBYS3		(IMXRT_FLEXIO2.offset30C)
#define FLEXIO2_SHIFTBUFBBS0		(IMXRT_FLEXIO2.offset380)
#define FLEXIO2_SHIFTBUFBBS1		(IMXRT_FLEXIO2.offset384)
#define FLEXIO2_SHIFTBUFBBS2		(IMXRT_FLEXIO2.offset388)
#define FLEXIO2_SHIFTBUFBBS3		(IMXRT_FLEXIO2.offset38C)
#define FLEXIO2_TIMCTL0			(IMXRT_FLEXIO2_b.offset000)
#define FLEXIO2_TIMCTL1			(IMXRT_FLEXIO2_b.offset004)
#define FLEXIO2_TIMCTL2			(IMXRT_FLEXIO2_b.offset008)
#define FLEXIO2_TIMCTL3			(IMXRT_FLEXIO2_b.offset00C)
#define FLEXIO2_TIMCFG0			(IMXRT_FLEXIO2_b.offset080)
#define FLEXIO2_TIMCFG1			(IMXRT_FLEXIO2_b.offset084)
#define FLEXIO2_TIMCFG2			(IMXRT_FLEXIO2_b.offset088)
#define FLEXIO2_TIMCFG3			(IMXRT_FLEXIO2_b.offset08C)
#define FLEXIO2_TIMCMP0			(IMXRT_FLEXIO2_b.offset100)
#define FLEXIO2_TIMCMP1			(IMXRT_FLEXIO2_b.offset104)
#define FLEXIO2_TIMCMP2			(IMXRT_FLEXIO2_b.offset108)
#define FLEXIO2_TIMCMP3			(IMXRT_FLEXIO2_b.offset10C)
#define FLEXIO2_SHIFTBUFNBS0		(IMXRT_FLEXIO2_b.offset280)
#define FLEXIO2_SHIFTBUFNBS1		(IMXRT_FLEXIO2_b.offset284)
#define FLEXIO2_SHIFTBUFNBS2		(IMXRT_FLEXIO2_b.offset288)
#define FLEXIO2_SHIFTBUFNBS3		(IMXRT_FLEXIO2_b.offset28C)
#define FLEXIO2_SHIFTBUFHWS0		(IMXRT_FLEXIO2_b.offset300)
#define FLEXIO2_SHIFTBUFHWS1		(IMXRT_FLEXIO2_b.offset304)
#define FLEXIO2_SHIFTBUFHWS2		(IMXRT_FLEXIO2_b.offset308)
#define FLEXIO2_SHIFTBUFHWS3		(IMXRT_FLEXIO2_b.offset30C)
#define FLEXIO2_SHIFTBUFNIS0		(IMXRT_FLEXIO2_b.offset380)
#define FLEXIO2_SHIFTBUFNIS1		(IMXRT_FLEXIO2_b.offset384)
#define FLEXIO2_SHIFTBUFNIS2		(IMXRT_FLEXIO2_b.offset388)
#define FLEXIO2_SHIFTBUFNIS3		(IMXRT_FLEXIO2_b.offset38C)

// page 1382
#define IMXRT_FLEXPWM1		(*(IMXRT_REGISTER16_t *)0x403DC000)
#define FLEXPWM1_SM0CNT			(IMXRT_FLEXPWM1.offset000)
#define FLEXPWM1_SM0INIT		(IMXRT_FLEXPWM1.offset002)
#define FLEXPWM1_SM0CTRL2		(IMXRT_FLEXPWM1.offset004)
#define FLEXPWM1_SM0CTRL		(IMXRT_FLEXPWM1.offset006)
#define FLEXPWM1_SM0VAL0		(IMXRT_FLEXPWM1.offset008)
#define FLEXPWM1_SM0FRACVAL1		(IMXRT_FLEXPWM1.offset00A)
#define FLEXPWM1_SM0VAL1		(IMXRT_FLEXPWM1.offset00C)
#define FLEXPWM1_SM0FRACVAL2		(IMXRT_FLEXPWM1.offset00E)
#define FLEXPWM1_SM0VAL2		(IMXRT_FLEXPWM1.offset010)
#define FLEXPWM1_SM0FRACVAL3		(IMXRT_FLEXPWM1.offset012)
#define FLEXPWM1_SM0VAL3		(IMXRT_FLEXPWM1.offset014)
#define FLEXPWM1_SM0FRACVAL4		(IMXRT_FLEXPWM1.offset016)
#define FLEXPWM1_SM0VAL4		(IMXRT_FLEXPWM1.offset018)
#define FLEXPWM1_SM0FRACVAL5		(IMXRT_FLEXPWM1.offset01A)
#define FLEXPWM1_SM0VAL5		(IMXRT_FLEXPWM1.offset01C)
#define FLEXPWM1_SM0FRCTRL		(IMXRT_FLEXPWM1.offset01E)
#define FLEXPWM1_SM0OCTRL		(IMXRT_FLEXPWM1.offset020)
#define FLEXPWM1_SM0STS			(IMXRT_FLEXPWM1.offset022)
#define FLEXPWM1_SM0INTEN		(IMXRT_FLEXPWM1.offset024)
#define FLEXPWM1_SM0DMAEN		(IMXRT_FLEXPWM1.offset026)
#define FLEXPWM1_SM0TCTRL		(IMXRT_FLEXPWM1.offset028)
#define FLEXPWM1_SM0DISMAP0		(IMXRT_FLEXPWM1.offset02A)
#define FLEXPWM1_SM0DISMAP1		(IMXRT_FLEXPWM1.offset02C)
#define FLEXPWM1_SM0DTCNT0		(IMXRT_FLEXPWM1.offset02E)
#define FLEXPWM1_SM0DTCNT1		(IMXRT_FLEXPWM1.offset030)
#define FLEXPWM1_SM0CAPTCTRLA		(IMXRT_FLEXPWM1.offset032)
#define FLEXPWM1_SM0CAPTCOMPA		(IMXRT_FLEXPWM1.offset034)
#define FLEXPWM1_SM0CAPTCTRLB		(IMXRT_FLEXPWM1.offset036)
#define FLEXPWM1_SM0CAPTCOMPB		(IMXRT_FLEXPWM1.offset038)
#define FLEXPWM1_SM0CAPTCTRLX		(IMXRT_FLEXPWM1.offset03A)
#define FLEXPWM1_SM0CAPTCOMPX		(IMXRT_FLEXPWM1.offset03C)
#define FLEXPWM1_SM0CVAL0		(IMXRT_FLEXPWM1.offset03E)
#define FLEXPWM1_SM0CVAL0CYC		(IMXRT_FLEXPWM1.offset040)
#define FLEXPWM1_SM0CVAL1		(IMXRT_FLEXPWM1.offset042)
#define FLEXPWM1_SM0CVAL1CYC		(IMXRT_FLEXPWM1.offset044)
#define FLEXPWM1_SM0CVAL2		(IMXRT_FLEXPWM1.offset046)
#define FLEXPWM1_SM0CVAL2CYC		(IMXRT_FLEXPWM1.offset048)
#define FLEXPWM1_SM0CVAL3		(IMXRT_FLEXPWM1.offset04A)
#define FLEXPWM1_SM0CVAL3CYC		(IMXRT_FLEXPWM1.offset04C)
#define FLEXPWM1_SM0CVAL4		(IMXRT_FLEXPWM1.offset04E)
#define FLEXPWM1_SM0CVAL4CYC		(IMXRT_FLEXPWM1.offset050)
#define FLEXPWM1_SM0CVAL5		(IMXRT_FLEXPWM1.offset052)
#define FLEXPWM1_SM0CVAL5CYC		(IMXRT_FLEXPWM1.offset054)
#define FLEXPWM1_SM1CNT			(IMXRT_FLEXPWM1.offset060)
#define FLEXPWM1_SM1INIT		(IMXRT_FLEXPWM1.offset062)
#define FLEXPWM1_SM1CTRL2		(IMXRT_FLEXPWM1.offset064)
#define FLEXPWM1_SM1CTRL		(IMXRT_FLEXPWM1.offset066)
#define FLEXPWM1_SM1VAL0		(IMXRT_FLEXPWM1.offset068)
#define FLEXPWM1_SM1FRACVAL1		(IMXRT_FLEXPWM1.offset06A)
#define FLEXPWM1_SM1VAL1		(IMXRT_FLEXPWM1.offset06C)
#define FLEXPWM1_SM1FRACVAL2		(IMXRT_FLEXPWM1.offset06E)
#define FLEXPWM1_SM1VAL2		(IMXRT_FLEXPWM1.offset070)
#define FLEXPWM1_SM1FRACVAL3		(IMXRT_FLEXPWM1.offset072)
#define FLEXPWM1_SM1VAL3		(IMXRT_FLEXPWM1.offset074)
#define FLEXPWM1_SM1FRACVAL4		(IMXRT_FLEXPWM1.offset076)
#define FLEXPWM1_SM1VAL4		(IMXRT_FLEXPWM1.offset078)
#define FLEXPWM1_SM1FRACVAL5		(IMXRT_FLEXPWM1.offset07A)
#define FLEXPWM1_SM1VAL5		(IMXRT_FLEXPWM1.offset07C)
#define FLEXPWM1_SM1FRCTRL		(IMXRT_FLEXPWM1.offset07E)
#define FLEXPWM1_SM1OCTRL		(IMXRT_FLEXPWM1.offset080)
#define FLEXPWM1_SM1STS			(IMXRT_FLEXPWM1.offset082)
#define FLEXPWM1_SM1INTEN		(IMXRT_FLEXPWM1.offset084)
#define FLEXPWM1_SM1DMAEN		(IMXRT_FLEXPWM1.offset086)
#define FLEXPWM1_SM1TCTRL		(IMXRT_FLEXPWM1.offset088)
#define FLEXPWM1_SM1DISMAP0		(IMXRT_FLEXPWM1.offset08A)
#define FLEXPWM1_SM1DISMAP1		(IMXRT_FLEXPWM1.offset08C)
#define FLEXPWM1_SM1DTCNT0		(IMXRT_FLEXPWM1.offset08E)
#define FLEXPWM1_SM1DTCNT1		(IMXRT_FLEXPWM1.offset090)
#define FLEXPWM1_SM1CAPTCTRLA		(IMXRT_FLEXPWM1.offset092)
#define FLEXPWM1_SM1CAPTCOMPA		(IMXRT_FLEXPWM1.offset094)
#define FLEXPWM1_SM1CAPTCTRLB		(IMXRT_FLEXPWM1.offset096)
#define FLEXPWM1_SM1CAPTCOMPB		(IMXRT_FLEXPWM1.offset098)
#define FLEXPWM1_SM1CAPTCTRLX		(IMXRT_FLEXPWM1.offset09A)
#define FLEXPWM1_SM1CAPTCOMPX		(IMXRT_FLEXPWM1.offset09C)
#define FLEXPWM1_SM1CVAL0		(IMXRT_FLEXPWM1.offset09E)
#define FLEXPWM1_SM1CVAL0CYC		(IMXRT_FLEXPWM1.offset0A0)
#define FLEXPWM1_SM1CVAL1		(IMXRT_FLEXPWM1.offset0A2)
#define FLEXPWM1_SM1CVAL1CYC		(IMXRT_FLEXPWM1.offset0A4)
#define FLEXPWM1_SM1CVAL2		(IMXRT_FLEXPWM1.offset0A6)
#define FLEXPWM1_SM1CVAL2CYC		(IMXRT_FLEXPWM1.offset0A8)
#define FLEXPWM1_SM1CVAL3		(IMXRT_FLEXPWM1.offset0AA)
#define FLEXPWM1_SM1CVAL3CYC		(IMXRT_FLEXPWM1.offset0AC)
#define FLEXPWM1_SM1CVAL4		(IMXRT_FLEXPWM1.offset0AE)
#define FLEXPWM1_SM1CVAL4CYC		(IMXRT_FLEXPWM1.offset0B0)
#define FLEXPWM1_SM1CVAL5		(IMXRT_FLEXPWM1.offset0B2)
#define FLEXPWM1_SM1CVAL5CYC		(IMXRT_FLEXPWM1.offset0B4)
#define FLEXPWM1_SM2CNT			(IMXRT_FLEXPWM1.offset0C0)
#define FLEXPWM1_SM2INIT		(IMXRT_FLEXPWM1.offset0C2)
#define FLEXPWM1_SM2CTRL2		(IMXRT_FLEXPWM1.offset0C4)
#define FLEXPWM1_SM2CTRL		(IMXRT_FLEXPWM1.offset0C6)
#define FLEXPWM1_SM2VAL0		(IMXRT_FLEXPWM1.offset0C8)
#define FLEXPWM1_SM2FRACVAL1		(IMXRT_FLEXPWM1.offset0CA)
#define FLEXPWM1_SM2VAL1		(IMXRT_FLEXPWM1.offset0CC)
#define FLEXPWM1_SM2FRACVAL2		(IMXRT_FLEXPWM1.offset0CE)
#define FLEXPWM1_SM2VAL2		(IMXRT_FLEXPWM1.offset0D0)
#define FLEXPWM1_SM2FRACVAL3		(IMXRT_FLEXPWM1.offset0D2)
#define FLEXPWM1_SM2VAL3		(IMXRT_FLEXPWM1.offset0D4)
#define FLEXPWM1_SM2FRACVAL4		(IMXRT_FLEXPWM1.offset0D6)
#define FLEXPWM1_SM2VAL4		(IMXRT_FLEXPWM1.offset0D8)
#define FLEXPWM1_SM2FRACVAL5		(IMXRT_FLEXPWM1.offset0DA)
#define FLEXPWM1_SM2VAL5		(IMXRT_FLEXPWM1.offset0DC)
#define FLEXPWM1_SM2FRCTRL		(IMXRT_FLEXPWM1.offset0DE)
#define FLEXPWM1_SM2OCTRL		(IMXRT_FLEXPWM1.offset0E0)
#define FLEXPWM1_SM2STS			(IMXRT_FLEXPWM1.offset0E2)
#define FLEXPWM1_SM2INTEN		(IMXRT_FLEXPWM1.offset0E4)
#define FLEXPWM1_SM2DMAEN		(IMXRT_FLEXPWM1.offset0E6)
#define FLEXPWM1_SM2TCTRL		(IMXRT_FLEXPWM1.offset0E8)
#define FLEXPWM1_SM2DISMAP0		(IMXRT_FLEXPWM1.offset0EA)
#define FLEXPWM1_SM2DISMAP1		(IMXRT_FLEXPWM1.offset0EC)
#define FLEXPWM1_SM2DTCNT0		(IMXRT_FLEXPWM1.offset0EE)
#define FLEXPWM1_SM2DTCNT1		(IMXRT_FLEXPWM1.offset0F0)
#define FLEXPWM1_SM2CAPTCTRLA		(IMXRT_FLEXPWM1.offset0F2)
#define FLEXPWM1_SM2CAPTCOMPA		(IMXRT_FLEXPWM1.offset0F4)
#define FLEXPWM1_SM2CAPTCTRLB		(IMXRT_FLEXPWM1.offset0F6)
#define FLEXPWM1_SM2CAPTCOMPB		(IMXRT_FLEXPWM1.offset0F8)
#define FLEXPWM1_SM2CAPTCTRLX		(IMXRT_FLEXPWM1.offset0FA)
#define FLEXPWM1_SM2CAPTCOMPX		(IMXRT_FLEXPWM1.offset0FC)
#define FLEXPWM1_SM2CVAL0		(IMXRT_FLEXPWM1.offset0FE)
#define FLEXPWM1_SM2CVAL0CYC		(IMXRT_FLEXPWM1.offset100)
#define FLEXPWM1_SM2CVAL1		(IMXRT_FLEXPWM1.offset102)
#define FLEXPWM1_SM2CVAL1CYC		(IMXRT_FLEXPWM1.offset104)
#define FLEXPWM1_SM2CVAL2		(IMXRT_FLEXPWM1.offset106)
#define FLEXPWM1_SM2CVAL2CYC		(IMXRT_FLEXPWM1.offset108)
#define FLEXPWM1_SM2CVAL3		(IMXRT_FLEXPWM1.offset10A)
#define FLEXPWM1_SM2CVAL3CYC		(IMXRT_FLEXPWM1.offset10C)
#define FLEXPWM1_SM2CVAL4		(IMXRT_FLEXPWM1.offset10E)
#define FLEXPWM1_SM2CVAL4CYC		(IMXRT_FLEXPWM1.offset110)
#define FLEXPWM1_SM2CVAL5		(IMXRT_FLEXPWM1.offset112)
#define FLEXPWM1_SM2CVAL5CYC		(IMXRT_FLEXPWM1.offset114)
#define FLEXPWM1_SM3CNT			(IMXRT_FLEXPWM1.offset120)
#define FLEXPWM1_SM3INIT		(IMXRT_FLEXPWM1.offset122)
#define FLEXPWM1_SM3CTRL2		(IMXRT_FLEXPWM1.offset124)
#define FLEXPWM1_SM3CTRL		(IMXRT_FLEXPWM1.offset126)
#define FLEXPWM1_SM3VAL0		(IMXRT_FLEXPWM1.offset128)
#define FLEXPWM1_SM3FRACVAL1		(IMXRT_FLEXPWM1.offset12A)
#define FLEXPWM1_SM3VAL1		(IMXRT_FLEXPWM1.offset12C)
#define FLEXPWM1_SM3FRACVAL2		(IMXRT_FLEXPWM1.offset12E)
#define FLEXPWM1_SM3VAL2		(IMXRT_FLEXPWM1.offset130)
#define FLEXPWM1_SM3FRACVAL3		(IMXRT_FLEXPWM1.offset132)
#define FLEXPWM1_SM3VAL3		(IMXRT_FLEXPWM1.offset134)
#define FLEXPWM1_SM3FRACVAL4		(IMXRT_FLEXPWM1.offset136)
#define FLEXPWM1_SM3VAL4		(IMXRT_FLEXPWM1.offset138)
#define FLEXPWM1_SM3FRACVAL5		(IMXRT_FLEXPWM1.offset13A)
#define FLEXPWM1_SM3VAL5		(IMXRT_FLEXPWM1.offset13C)
#define FLEXPWM1_SM3FRCTRL		(IMXRT_FLEXPWM1.offset13E)
#define FLEXPWM1_SM3OCTRL		(IMXRT_FLEXPWM1.offset140)
#define FLEXPWM1_SM3STS			(IMXRT_FLEXPWM1.offset142)
#define FLEXPWM1_SM3INTEN		(IMXRT_FLEXPWM1.offset144)
#define FLEXPWM1_SM3DMAEN		(IMXRT_FLEXPWM1.offset146)
#define FLEXPWM1_SM3TCTRL		(IMXRT_FLEXPWM1.offset148)
#define FLEXPWM1_SM3DISMAP0		(IMXRT_FLEXPWM1.offset14A)
#define FLEXPWM1_SM3DISMAP1		(IMXRT_FLEXPWM1.offset14C)
#define FLEXPWM1_SM3DTCNT0		(IMXRT_FLEXPWM1.offset15E)
#define FLEXPWM1_SM3DTCNT1		(IMXRT_FLEXPWM1.offset150)
#define FLEXPWM1_SM3CAPTCTRLA		(IMXRT_FLEXPWM1.offset152)
#define FLEXPWM1_SM3CAPTCOMPA		(IMXRT_FLEXPWM1.offset154)
#define FLEXPWM1_SM3CAPTCTRLB		(IMXRT_FLEXPWM1.offset156)
#define FLEXPWM1_SM3CAPTCOMPB		(IMXRT_FLEXPWM1.offset158)
#define FLEXPWM1_SM3CAPTCTRLX		(IMXRT_FLEXPWM1.offset15A)
#define FLEXPWM1_SM3CAPTCOMPX		(IMXRT_FLEXPWM1.offset15C)
#define FLEXPWM1_SM3CVAL0		(IMXRT_FLEXPWM1.offset15E)
#define FLEXPWM1_SM3CVAL0CYC		(IMXRT_FLEXPWM1.offset160)
#define FLEXPWM1_SM3CVAL1		(IMXRT_FLEXPWM1.offset162)
#define FLEXPWM1_SM3CVAL1CYC		(IMXRT_FLEXPWM1.offset164)
#define FLEXPWM1_SM3CVAL2		(IMXRT_FLEXPWM1.offset166)
#define FLEXPWM1_SM3CVAL2CYC		(IMXRT_FLEXPWM1.offset168)
#define FLEXPWM1_SM3CVAL3		(IMXRT_FLEXPWM1.offset16A)
#define FLEXPWM1_SM3CVAL3CYC		(IMXRT_FLEXPWM1.offset16C)
#define FLEXPWM1_SM3CVAL4		(IMXRT_FLEXPWM1.offset16E)
#define FLEXPWM1_SM3CVAL4CYC		(IMXRT_FLEXPWM1.offset170)
#define FLEXPWM1_SM3CVAL5		(IMXRT_FLEXPWM1.offset172)
#define FLEXPWM1_SM3CVAL5CYC		(IMXRT_FLEXPWM1.offset174)
#define FLEXPWM1_OUTEN			(IMXRT_FLEXPWM1.offset180)
#define FLEXPWM1_MASK			(IMXRT_FLEXPWM1.offset182)
#define FLEXPWM1_SWCOUT			(IMXRT_FLEXPWM1.offset184)
#define FLEXPWM1_DTSRCSEL		(IMXRT_FLEXPWM1.offset186)
#define FLEXPWM1_MCTRL			(IMXRT_FLEXPWM1.offset188)
#define FLEXPWM1_MCTRL2			(IMXRT_FLEXPWM1.offset18A)
#define FLEXPWM1_FCTRL0			(IMXRT_FLEXPWM1.offset18C)
#define FLEXPWM1_FSTS0			(IMXRT_FLEXPWM1.offset18E)
#define FLEXPWM1_FFILT0			(IMXRT_FLEXPWM1.offset190)
#define FLEXPWM1_FTST0			(IMXRT_FLEXPWM1.offset192)
#define FLEXPWM1_FCTRL20		(IMXRT_FLEXPWM1.offset194)
#define IMXRT_FLEXPWM2		(*(IMXRT_REGISTER16_t *)0x403E0000)
#define FLEXPWM2_SM0CNT			(IMXRT_FLEXPWM2.offset000)
#define FLEXPWM2_SM0INIT		(IMXRT_FLEXPWM2.offset002)
#define FLEXPWM2_SM0CTRL2		(IMXRT_FLEXPWM2.offset004)
#define FLEXPWM2_SM0CTRL		(IMXRT_FLEXPWM2.offset006)
#define FLEXPWM2_SM0VAL0		(IMXRT_FLEXPWM2.offset008)
#define FLEXPWM2_SM0FRACVAL1		(IMXRT_FLEXPWM2.offset00A)
#define FLEXPWM2_SM0VAL1		(IMXRT_FLEXPWM2.offset00C)
#define FLEXPWM2_SM0FRACVAL2		(IMXRT_FLEXPWM2.offset00E)
#define FLEXPWM2_SM0VAL2		(IMXRT_FLEXPWM2.offset010)
#define FLEXPWM2_SM0FRACVAL3		(IMXRT_FLEXPWM2.offset012)
#define FLEXPWM2_SM0VAL3		(IMXRT_FLEXPWM2.offset014)
#define FLEXPWM2_SM0FRACVAL4		(IMXRT_FLEXPWM2.offset016)
#define FLEXPWM2_SM0VAL4		(IMXRT_FLEXPWM2.offset018)
#define FLEXPWM2_SM0FRACVAL5		(IMXRT_FLEXPWM2.offset01A)
#define FLEXPWM2_SM0VAL5		(IMXRT_FLEXPWM2.offset01C)
#define FLEXPWM2_SM0FRCTRL		(IMXRT_FLEXPWM2.offset01E)
#define FLEXPWM2_SM0OCTRL		(IMXRT_FLEXPWM2.offset020)
#define FLEXPWM2_SM0STS			(IMXRT_FLEXPWM2.offset022)
#define FLEXPWM2_SM0INTEN		(IMXRT_FLEXPWM2.offset024)
#define FLEXPWM2_SM0DMAEN		(IMXRT_FLEXPWM2.offset026)
#define FLEXPWM2_SM0TCTRL		(IMXRT_FLEXPWM2.offset028)
#define FLEXPWM2_SM0DISMAP0		(IMXRT_FLEXPWM2.offset02A)
#define FLEXPWM2_SM0DISMAP1		(IMXRT_FLEXPWM2.offset02C)
#define FLEXPWM2_SM0DTCNT0		(IMXRT_FLEXPWM2.offset02E)
#define FLEXPWM2_SM0DTCNT1		(IMXRT_FLEXPWM2.offset030)
#define FLEXPWM2_SM0CAPTCTRLA		(IMXRT_FLEXPWM2.offset032)
#define FLEXPWM2_SM0CAPTCOMPA		(IMXRT_FLEXPWM2.offset034)
#define FLEXPWM2_SM0CAPTCTRLB		(IMXRT_FLEXPWM2.offset036)
#define FLEXPWM2_SM0CAPTCOMPB		(IMXRT_FLEXPWM2.offset038)
#define FLEXPWM2_SM0CAPTCTRLX		(IMXRT_FLEXPWM2.offset03A)
#define FLEXPWM2_SM0CAPTCOMPX		(IMXRT_FLEXPWM2.offset03C)
#define FLEXPWM2_SM0CVAL0		(IMXRT_FLEXPWM2.offset03E)
#define FLEXPWM2_SM0CVAL0CYC		(IMXRT_FLEXPWM2.offset040)
#define FLEXPWM2_SM0CVAL1		(IMXRT_FLEXPWM2.offset042)
#define FLEXPWM2_SM0CVAL1CYC		(IMXRT_FLEXPWM2.offset044)
#define FLEXPWM2_SM0CVAL2		(IMXRT_FLEXPWM2.offset046)
#define FLEXPWM2_SM0CVAL2CYC		(IMXRT_FLEXPWM2.offset048)
#define FLEXPWM2_SM0CVAL3		(IMXRT_FLEXPWM2.offset04A)
#define FLEXPWM2_SM0CVAL3CYC		(IMXRT_FLEXPWM2.offset04C)
#define FLEXPWM2_SM0CVAL4		(IMXRT_FLEXPWM2.offset04E)
#define FLEXPWM2_SM0CVAL4CYC		(IMXRT_FLEXPWM2.offset050)
#define FLEXPWM2_SM0CVAL5		(IMXRT_FLEXPWM2.offset052)
#define FLEXPWM2_SM0CVAL5CYC		(IMXRT_FLEXPWM2.offset054)
#define FLEXPWM2_SM1CNT			(IMXRT_FLEXPWM2.offset060)
#define FLEXPWM2_SM1INIT		(IMXRT_FLEXPWM2.offset062)
#define FLEXPWM2_SM1CTRL2		(IMXRT_FLEXPWM2.offset064)
#define FLEXPWM2_SM1CTRL		(IMXRT_FLEXPWM2.offset066)
#define FLEXPWM2_SM1VAL0		(IMXRT_FLEXPWM2.offset068)
#define FLEXPWM2_SM1FRACVAL1		(IMXRT_FLEXPWM2.offset06A)
#define FLEXPWM2_SM1VAL1		(IMXRT_FLEXPWM2.offset06C)
#define FLEXPWM2_SM1FRACVAL2		(IMXRT_FLEXPWM2.offset06E)
#define FLEXPWM2_SM1VAL2		(IMXRT_FLEXPWM2.offset070)
#define FLEXPWM2_SM1FRACVAL3		(IMXRT_FLEXPWM2.offset072)
#define FLEXPWM2_SM1VAL3		(IMXRT_FLEXPWM2.offset074)
#define FLEXPWM2_SM1FRACVAL4		(IMXRT_FLEXPWM2.offset076)
#define FLEXPWM2_SM1VAL4		(IMXRT_FLEXPWM2.offset078)
#define FLEXPWM2_SM1FRACVAL5		(IMXRT_FLEXPWM2.offset07A)
#define FLEXPWM2_SM1VAL5		(IMXRT_FLEXPWM2.offset07C)
#define FLEXPWM2_SM1FRCTRL		(IMXRT_FLEXPWM2.offset07E)
#define FLEXPWM2_SM1OCTRL		(IMXRT_FLEXPWM2.offset080)
#define FLEXPWM2_SM1STS			(IMXRT_FLEXPWM2.offset082)
#define FLEXPWM2_SM1INTEN		(IMXRT_FLEXPWM2.offset084)
#define FLEXPWM2_SM1DMAEN		(IMXRT_FLEXPWM2.offset086)
#define FLEXPWM2_SM1TCTRL		(IMXRT_FLEXPWM2.offset088)
#define FLEXPWM2_SM1DISMAP0		(IMXRT_FLEXPWM2.offset08A)
#define FLEXPWM2_SM1DISMAP1		(IMXRT_FLEXPWM2.offset08C)
#define FLEXPWM2_SM1DTCNT0		(IMXRT_FLEXPWM2.offset08E)
#define FLEXPWM2_SM1DTCNT1		(IMXRT_FLEXPWM2.offset090)
#define FLEXPWM2_SM1CAPTCTRLA		(IMXRT_FLEXPWM2.offset092)
#define FLEXPWM2_SM1CAPTCOMPA		(IMXRT_FLEXPWM2.offset094)
#define FLEXPWM2_SM1CAPTCTRLB		(IMXRT_FLEXPWM2.offset096)
#define FLEXPWM2_SM1CAPTCOMPB		(IMXRT_FLEXPWM2.offset098)
#define FLEXPWM2_SM1CAPTCTRLX		(IMXRT_FLEXPWM2.offset09A)
#define FLEXPWM2_SM1CAPTCOMPX		(IMXRT_FLEXPWM2.offset09C)
#define FLEXPWM2_SM1CVAL0		(IMXRT_FLEXPWM2.offset09E)
#define FLEXPWM2_SM1CVAL0CYC		(IMXRT_FLEXPWM2.offset0A0)
#define FLEXPWM2_SM1CVAL1		(IMXRT_FLEXPWM2.offset0A2)
#define FLEXPWM2_SM1CVAL1CYC		(IMXRT_FLEXPWM2.offset0A4)
#define FLEXPWM2_SM1CVAL2		(IMXRT_FLEXPWM2.offset0A6)
#define FLEXPWM2_SM1CVAL2CYC		(IMXRT_FLEXPWM2.offset0A8)
#define FLEXPWM2_SM1CVAL3		(IMXRT_FLEXPWM2.offset0AA)
#define FLEXPWM2_SM1CVAL3CYC		(IMXRT_FLEXPWM2.offset0AC)
#define FLEXPWM2_SM1CVAL4		(IMXRT_FLEXPWM2.offset0AE)
#define FLEXPWM2_SM1CVAL4CYC		(IMXRT_FLEXPWM2.offset0B0)
#define FLEXPWM2_SM1CVAL5		(IMXRT_FLEXPWM2.offset0B2)
#define FLEXPWM2_SM1CVAL5CYC		(IMXRT_FLEXPWM2.offset0B4)
#define FLEXPWM2_SM2CNT			(IMXRT_FLEXPWM2.offset0C0)
#define FLEXPWM2_SM2INIT		(IMXRT_FLEXPWM2.offset0C2)
#define FLEXPWM2_SM2CTRL2		(IMXRT_FLEXPWM2.offset0C4)
#define FLEXPWM2_SM2CTRL		(IMXRT_FLEXPWM2.offset0C6)
#define FLEXPWM2_SM2VAL0		(IMXRT_FLEXPWM2.offset0C8)
#define FLEXPWM2_SM2FRACVAL1		(IMXRT_FLEXPWM2.offset0CA)
#define FLEXPWM2_SM2VAL1		(IMXRT_FLEXPWM2.offset0CC)
#define FLEXPWM2_SM2FRACVAL2		(IMXRT_FLEXPWM2.offset0CE)
#define FLEXPWM2_SM2VAL2		(IMXRT_FLEXPWM2.offset0D0)
#define FLEXPWM2_SM2FRACVAL3		(IMXRT_FLEXPWM2.offset0D2)
#define FLEXPWM2_SM2VAL3		(IMXRT_FLEXPWM2.offset0D4)
#define FLEXPWM2_SM2FRACVAL4		(IMXRT_FLEXPWM2.offset0D6)
#define FLEXPWM2_SM2VAL4		(IMXRT_FLEXPWM2.offset0D8)
#define FLEXPWM2_SM2FRACVAL5		(IMXRT_FLEXPWM2.offset0DA)
#define FLEXPWM2_SM2VAL5		(IMXRT_FLEXPWM2.offset0DC)
#define FLEXPWM2_SM2FRCTRL		(IMXRT_FLEXPWM2.offset0DE)
#define FLEXPWM2_SM2OCTRL		(IMXRT_FLEXPWM2.offset0E0)
#define FLEXPWM2_SM2STS			(IMXRT_FLEXPWM2.offset0E2)
#define FLEXPWM2_SM2INTEN		(IMXRT_FLEXPWM2.offset0E4)
#define FLEXPWM2_SM2DMAEN		(IMXRT_FLEXPWM2.offset0E6)
#define FLEXPWM2_SM2TCTRL		(IMXRT_FLEXPWM2.offset0E8)
#define FLEXPWM2_SM2DISMAP0		(IMXRT_FLEXPWM2.offset0EA)
#define FLEXPWM2_SM2DISMAP1		(IMXRT_FLEXPWM2.offset0EC)
#define FLEXPWM2_SM2DTCNT0		(IMXRT_FLEXPWM2.offset0EE)
#define FLEXPWM2_SM2DTCNT1		(IMXRT_FLEXPWM2.offset0F0)
#define FLEXPWM2_SM2CAPTCTRLA		(IMXRT_FLEXPWM2.offset0F2)
#define FLEXPWM2_SM2CAPTCOMPA		(IMXRT_FLEXPWM2.offset0F4)
#define FLEXPWM2_SM2CAPTCTRLB		(IMXRT_FLEXPWM2.offset0F6)
#define FLEXPWM2_SM2CAPTCOMPB		(IMXRT_FLEXPWM2.offset0F8)
#define FLEXPWM2_SM2CAPTCTRLX		(IMXRT_FLEXPWM2.offset0FA)
#define FLEXPWM2_SM2CAPTCOMPX		(IMXRT_FLEXPWM2.offset0FC)
#define FLEXPWM2_SM2CVAL0		(IMXRT_FLEXPWM2.offset0FE)
#define FLEXPWM2_SM2CVAL0CYC		(IMXRT_FLEXPWM2.offset100)
#define FLEXPWM2_SM2CVAL1		(IMXRT_FLEXPWM2.offset102)
#define FLEXPWM2_SM2CVAL1CYC		(IMXRT_FLEXPWM2.offset104)
#define FLEXPWM2_SM2CVAL2		(IMXRT_FLEXPWM2.offset106)
#define FLEXPWM2_SM2CVAL2CYC		(IMXRT_FLEXPWM2.offset108)
#define FLEXPWM2_SM2CVAL3		(IMXRT_FLEXPWM2.offset10A)
#define FLEXPWM2_SM2CVAL3CYC		(IMXRT_FLEXPWM2.offset10C)
#define FLEXPWM2_SM2CVAL4		(IMXRT_FLEXPWM2.offset10E)
#define FLEXPWM2_SM2CVAL4CYC		(IMXRT_FLEXPWM2.offset110)
#define FLEXPWM2_SM2CVAL5		(IMXRT_FLEXPWM2.offset112)
#define FLEXPWM2_SM2CVAL5CYC		(IMXRT_FLEXPWM2.offset114)
#define FLEXPWM2_SM3CNT			(IMXRT_FLEXPWM2.offset120)
#define FLEXPWM2_SM3INIT		(IMXRT_FLEXPWM2.offset122)
#define FLEXPWM2_SM3CTRL2		(IMXRT_FLEXPWM2.offset124)
#define FLEXPWM2_SM3CTRL		(IMXRT_FLEXPWM2.offset126)
#define FLEXPWM2_SM3VAL0		(IMXRT_FLEXPWM2.offset128)
#define FLEXPWM2_SM3FRACVAL1		(IMXRT_FLEXPWM2.offset12A)
#define FLEXPWM2_SM3VAL1		(IMXRT_FLEXPWM2.offset12C)
#define FLEXPWM2_SM3FRACVAL2		(IMXRT_FLEXPWM2.offset12E)
#define FLEXPWM2_SM3VAL2		(IMXRT_FLEXPWM2.offset130)
#define FLEXPWM2_SM3FRACVAL3		(IMXRT_FLEXPWM2.offset132)
#define FLEXPWM2_SM3VAL3		(IMXRT_FLEXPWM2.offset134)
#define FLEXPWM2_SM3FRACVAL4		(IMXRT_FLEXPWM2.offset136)
#define FLEXPWM2_SM3VAL4		(IMXRT_FLEXPWM2.offset138)
#define FLEXPWM2_SM3FRACVAL5		(IMXRT_FLEXPWM2.offset13A)
#define FLEXPWM2_SM3VAL5		(IMXRT_FLEXPWM2.offset13C)
#define FLEXPWM2_SM3FRCTRL		(IMXRT_FLEXPWM2.offset13E)
#define FLEXPWM2_SM3OCTRL		(IMXRT_FLEXPWM2.offset140)
#define FLEXPWM2_SM3STS			(IMXRT_FLEXPWM2.offset142)
#define FLEXPWM2_SM3INTEN		(IMXRT_FLEXPWM2.offset144)
#define FLEXPWM2_SM3DMAEN		(IMXRT_FLEXPWM2.offset146)
#define FLEXPWM2_SM3TCTRL		(IMXRT_FLEXPWM2.offset148)
#define FLEXPWM2_SM3DISMAP0		(IMXRT_FLEXPWM2.offset14A)
#define FLEXPWM2_SM3DISMAP1		(IMXRT_FLEXPWM2.offset14C)
#define FLEXPWM2_SM3DTCNT0		(IMXRT_FLEXPWM2.offset15E)
#define FLEXPWM2_SM3DTCNT1		(IMXRT_FLEXPWM2.offset150)
#define FLEXPWM2_SM3CAPTCTRLA		(IMXRT_FLEXPWM2.offset152)
#define FLEXPWM2_SM3CAPTCOMPA		(IMXRT_FLEXPWM2.offset154)
#define FLEXPWM2_SM3CAPTCTRLB		(IMXRT_FLEXPWM2.offset156)
#define FLEXPWM2_SM3CAPTCOMPB		(IMXRT_FLEXPWM2.offset158)
#define FLEXPWM2_SM3CAPTCTRLX		(IMXRT_FLEXPWM2.offset15A)
#define FLEXPWM2_SM3CAPTCOMPX		(IMXRT_FLEXPWM2.offset15C)
#define FLEXPWM2_SM3CVAL0		(IMXRT_FLEXPWM2.offset15E)
#define FLEXPWM2_SM3CVAL0CYC		(IMXRT_FLEXPWM2.offset160)
#define FLEXPWM2_SM3CVAL1		(IMXRT_FLEXPWM2.offset162)
#define FLEXPWM2_SM3CVAL1CYC		(IMXRT_FLEXPWM2.offset164)
#define FLEXPWM2_SM3CVAL2		(IMXRT_FLEXPWM2.offset166)
#define FLEXPWM2_SM3CVAL2CYC		(IMXRT_FLEXPWM2.offset168)
#define FLEXPWM2_SM3CVAL3		(IMXRT_FLEXPWM2.offset16A)
#define FLEXPWM2_SM3CVAL3CYC		(IMXRT_FLEXPWM2.offset16C)
#define FLEXPWM2_SM3CVAL4		(IMXRT_FLEXPWM2.offset16E)
#define FLEXPWM2_SM3CVAL4CYC		(IMXRT_FLEXPWM2.offset170)
#define FLEXPWM2_SM3CVAL5		(IMXRT_FLEXPWM2.offset172)
#define FLEXPWM2_SM3CVAL5CYC		(IMXRT_FLEXPWM2.offset174)
#define FLEXPWM2_OUTEN			(IMXRT_FLEXPWM2.offset180)
#define FLEXPWM2_MASK			(IMXRT_FLEXPWM2.offset182)
#define FLEXPWM2_SWCOUT			(IMXRT_FLEXPWM2.offset184)
#define FLEXPWM2_DTSRCSEL		(IMXRT_FLEXPWM2.offset186)
#define FLEXPWM2_MCTRL			(IMXRT_FLEXPWM2.offset188)
#define FLEXPWM2_MCTRL2			(IMXRT_FLEXPWM2.offset18A)
#define FLEXPWM2_FCTRL0			(IMXRT_FLEXPWM2.offset18C)
#define FLEXPWM2_FSTS0			(IMXRT_FLEXPWM2.offset18E)
#define FLEXPWM2_FFILT0			(IMXRT_FLEXPWM2.offset190)
#define FLEXPWM2_FTST0			(IMXRT_FLEXPWM2.offset192)
#define FLEXPWM2_FCTRL20		(IMXRT_FLEXPWM2.offset194)
#define IMXRT_FLEXPWM3		(*(IMXRT_REGISTER16_t *)0x403E4000)
#define FLEXPWM3_SM0CNT			(IMXRT_FLEXPWM3.offset000)
#define FLEXPWM3_SM0INIT		(IMXRT_FLEXPWM3.offset002)
#define FLEXPWM3_SM0CTRL2		(IMXRT_FLEXPWM3.offset004)
#define FLEXPWM3_SM0CTRL		(IMXRT_FLEXPWM3.offset006)
#define FLEXPWM3_SM0VAL0		(IMXRT_FLEXPWM3.offset008)
#define FLEXPWM3_SM0FRACVAL1		(IMXRT_FLEXPWM3.offset00A)
#define FLEXPWM3_SM0VAL1		(IMXRT_FLEXPWM3.offset00C)
#define FLEXPWM3_SM0FRACVAL2		(IMXRT_FLEXPWM3.offset00E)
#define FLEXPWM3_SM0VAL2		(IMXRT_FLEXPWM3.offset010)
#define FLEXPWM3_SM0FRACVAL3		(IMXRT_FLEXPWM3.offset012)
#define FLEXPWM3_SM0VAL3		(IMXRT_FLEXPWM3.offset014)
#define FLEXPWM3_SM0FRACVAL4		(IMXRT_FLEXPWM3.offset016)
#define FLEXPWM3_SM0VAL4		(IMXRT_FLEXPWM3.offset018)
#define FLEXPWM3_SM0FRACVAL5		(IMXRT_FLEXPWM3.offset01A)
#define FLEXPWM3_SM0VAL5		(IMXRT_FLEXPWM3.offset01C)
#define FLEXPWM3_SM0FRCTRL		(IMXRT_FLEXPWM3.offset01E)
#define FLEXPWM3_SM0OCTRL		(IMXRT_FLEXPWM3.offset020)
#define FLEXPWM3_SM0STS			(IMXRT_FLEXPWM3.offset022)
#define FLEXPWM3_SM0INTEN		(IMXRT_FLEXPWM3.offset024)
#define FLEXPWM3_SM0DMAEN		(IMXRT_FLEXPWM3.offset026)
#define FLEXPWM3_SM0TCTRL		(IMXRT_FLEXPWM3.offset028)
#define FLEXPWM3_SM0DISMAP0		(IMXRT_FLEXPWM3.offset02A)
#define FLEXPWM3_SM0DISMAP1		(IMXRT_FLEXPWM3.offset02C)
#define FLEXPWM3_SM0DTCNT0		(IMXRT_FLEXPWM3.offset02E)
#define FLEXPWM3_SM0DTCNT1		(IMXRT_FLEXPWM3.offset030)
#define FLEXPWM3_SM0CAPTCTRLA		(IMXRT_FLEXPWM3.offset032)
#define FLEXPWM3_SM0CAPTCOMPA		(IMXRT_FLEXPWM3.offset034)
#define FLEXPWM3_SM0CAPTCTRLB		(IMXRT_FLEXPWM3.offset036)
#define FLEXPWM3_SM0CAPTCOMPB		(IMXRT_FLEXPWM3.offset038)
#define FLEXPWM3_SM0CAPTCTRLX		(IMXRT_FLEXPWM3.offset03A)
#define FLEXPWM3_SM0CAPTCOMPX		(IMXRT_FLEXPWM3.offset03C)
#define FLEXPWM3_SM0CVAL0		(IMXRT_FLEXPWM3.offset03E)
#define FLEXPWM3_SM0CVAL0CYC		(IMXRT_FLEXPWM3.offset040)
#define FLEXPWM3_SM0CVAL1		(IMXRT_FLEXPWM3.offset042)
#define FLEXPWM3_SM0CVAL1CYC		(IMXRT_FLEXPWM3.offset044)
#define FLEXPWM3_SM0CVAL2		(IMXRT_FLEXPWM3.offset046)
#define FLEXPWM3_SM0CVAL2CYC		(IMXRT_FLEXPWM3.offset048)
#define FLEXPWM3_SM0CVAL3		(IMXRT_FLEXPWM3.offset04A)
#define FLEXPWM3_SM0CVAL3CYC		(IMXRT_FLEXPWM3.offset04C)
#define FLEXPWM3_SM0CVAL4		(IMXRT_FLEXPWM3.offset04E)
#define FLEXPWM3_SM0CVAL4CYC		(IMXRT_FLEXPWM3.offset050)
#define FLEXPWM3_SM0CVAL5		(IMXRT_FLEXPWM3.offset052)
#define FLEXPWM3_SM0CVAL5CYC		(IMXRT_FLEXPWM3.offset054)
#define FLEXPWM3_SM1CNT			(IMXRT_FLEXPWM3.offset060)
#define FLEXPWM3_SM1INIT		(IMXRT_FLEXPWM3.offset062)
#define FLEXPWM3_SM1CTRL2		(IMXRT_FLEXPWM3.offset064)
#define FLEXPWM3_SM1CTRL		(IMXRT_FLEXPWM3.offset066)
#define FLEXPWM3_SM1VAL0		(IMXRT_FLEXPWM3.offset068)
#define FLEXPWM3_SM1FRACVAL1		(IMXRT_FLEXPWM3.offset06A)
#define FLEXPWM3_SM1VAL1		(IMXRT_FLEXPWM3.offset06C)
#define FLEXPWM3_SM1FRACVAL2		(IMXRT_FLEXPWM3.offset06E)
#define FLEXPWM3_SM1VAL2		(IMXRT_FLEXPWM3.offset070)
#define FLEXPWM3_SM1FRACVAL3		(IMXRT_FLEXPWM3.offset072)
#define FLEXPWM3_SM1VAL3		(IMXRT_FLEXPWM3.offset074)
#define FLEXPWM3_SM1FRACVAL4		(IMXRT_FLEXPWM3.offset076)
#define FLEXPWM3_SM1VAL4		(IMXRT_FLEXPWM3.offset078)
#define FLEXPWM3_SM1FRACVAL5		(IMXRT_FLEXPWM3.offset07A)
#define FLEXPWM3_SM1VAL5		(IMXRT_FLEXPWM3.offset07C)
#define FLEXPWM3_SM1FRCTRL		(IMXRT_FLEXPWM3.offset07E)
#define FLEXPWM3_SM1OCTRL		(IMXRT_FLEXPWM3.offset080)
#define FLEXPWM3_SM1STS			(IMXRT_FLEXPWM3.offset082)
#define FLEXPWM3_SM1INTEN		(IMXRT_FLEXPWM3.offset084)
#define FLEXPWM3_SM1DMAEN		(IMXRT_FLEXPWM3.offset086)
#define FLEXPWM3_SM1TCTRL		(IMXRT_FLEXPWM3.offset088)
#define FLEXPWM3_SM1DISMAP0		(IMXRT_FLEXPWM3.offset08A)
#define FLEXPWM3_SM1DISMAP1		(IMXRT_FLEXPWM3.offset08C)
#define FLEXPWM3_SM1DTCNT0		(IMXRT_FLEXPWM3.offset08E)
#define FLEXPWM3_SM1DTCNT1		(IMXRT_FLEXPWM3.offset090)
#define FLEXPWM3_SM1CAPTCTRLA		(IMXRT_FLEXPWM3.offset092)
#define FLEXPWM3_SM1CAPTCOMPA		(IMXRT_FLEXPWM3.offset094)
#define FLEXPWM3_SM1CAPTCTRLB		(IMXRT_FLEXPWM3.offset096)
#define FLEXPWM3_SM1CAPTCOMPB		(IMXRT_FLEXPWM3.offset098)
#define FLEXPWM3_SM1CAPTCTRLX		(IMXRT_FLEXPWM3.offset09A)
#define FLEXPWM3_SM1CAPTCOMPX		(IMXRT_FLEXPWM3.offset09C)
#define FLEXPWM3_SM1CVAL0		(IMXRT_FLEXPWM3.offset09E)
#define FLEXPWM3_SM1CVAL0CYC		(IMXRT_FLEXPWM3.offset0A0)
#define FLEXPWM3_SM1CVAL1		(IMXRT_FLEXPWM3.offset0A2)
#define FLEXPWM3_SM1CVAL1CYC		(IMXRT_FLEXPWM3.offset0A4)
#define FLEXPWM3_SM1CVAL2		(IMXRT_FLEXPWM3.offset0A6)
#define FLEXPWM3_SM1CVAL2CYC		(IMXRT_FLEXPWM3.offset0A8)
#define FLEXPWM3_SM1CVAL3		(IMXRT_FLEXPWM3.offset0AA)
#define FLEXPWM3_SM1CVAL3CYC		(IMXRT_FLEXPWM3.offset0AC)
#define FLEXPWM3_SM1CVAL4		(IMXRT_FLEXPWM3.offset0AE)
#define FLEXPWM3_SM1CVAL4CYC		(IMXRT_FLEXPWM3.offset0B0)
#define FLEXPWM3_SM1CVAL5		(IMXRT_FLEXPWM3.offset0B2)
#define FLEXPWM3_SM1CVAL5CYC		(IMXRT_FLEXPWM3.offset0B4)
#define FLEXPWM3_SM2CNT			(IMXRT_FLEXPWM3.offset0C0)
#define FLEXPWM3_SM2INIT		(IMXRT_FLEXPWM3.offset0C2)
#define FLEXPWM3_SM2CTRL2		(IMXRT_FLEXPWM3.offset0C4)
#define FLEXPWM3_SM2CTRL		(IMXRT_FLEXPWM3.offset0C6)
#define FLEXPWM3_SM2VAL0		(IMXRT_FLEXPWM3.offset0C8)
#define FLEXPWM3_SM2FRACVAL1		(IMXRT_FLEXPWM3.offset0CA)
#define FLEXPWM3_SM2VAL1		(IMXRT_FLEXPWM3.offset0CC)
#define FLEXPWM3_SM2FRACVAL2		(IMXRT_FLEXPWM3.offset0CE)
#define FLEXPWM3_SM2VAL2		(IMXRT_FLEXPWM3.offset0D0)
#define FLEXPWM3_SM2FRACVAL3		(IMXRT_FLEXPWM3.offset0D2)
#define FLEXPWM3_SM2VAL3		(IMXRT_FLEXPWM3.offset0D4)
#define FLEXPWM3_SM2FRACVAL4		(IMXRT_FLEXPWM3.offset0D6)
#define FLEXPWM3_SM2VAL4		(IMXRT_FLEXPWM3.offset0D8)
#define FLEXPWM3_SM2FRACVAL5		(IMXRT_FLEXPWM3.offset0DA)
#define FLEXPWM3_SM2VAL5		(IMXRT_FLEXPWM3.offset0DC)
#define FLEXPWM3_SM2FRCTRL		(IMXRT_FLEXPWM3.offset0DE)
#define FLEXPWM3_SM2OCTRL		(IMXRT_FLEXPWM3.offset0E0)
#define FLEXPWM3_SM2STS			(IMXRT_FLEXPWM3.offset0E2)
#define FLEXPWM3_SM2INTEN		(IMXRT_FLEXPWM3.offset0E4)
#define FLEXPWM3_SM2DMAEN		(IMXRT_FLEXPWM3.offset0E6)
#define FLEXPWM3_SM2TCTRL		(IMXRT_FLEXPWM3.offset0E8)
#define FLEXPWM3_SM2DISMAP0		(IMXRT_FLEXPWM3.offset0EA)
#define FLEXPWM3_SM2DISMAP1		(IMXRT_FLEXPWM3.offset0EC)
#define FLEXPWM3_SM2DTCNT0		(IMXRT_FLEXPWM3.offset0EE)
#define FLEXPWM3_SM2DTCNT1		(IMXRT_FLEXPWM3.offset0F0)
#define FLEXPWM3_SM2CAPTCTRLA		(IMXRT_FLEXPWM3.offset0F2)
#define FLEXPWM3_SM2CAPTCOMPA		(IMXRT_FLEXPWM3.offset0F4)
#define FLEXPWM3_SM2CAPTCTRLB		(IMXRT_FLEXPWM3.offset0F6)
#define FLEXPWM3_SM2CAPTCOMPB		(IMXRT_FLEXPWM3.offset0F8)
#define FLEXPWM3_SM2CAPTCTRLX		(IMXRT_FLEXPWM3.offset0FA)
#define FLEXPWM3_SM2CAPTCOMPX		(IMXRT_FLEXPWM3.offset0FC)
#define FLEXPWM3_SM2CVAL0		(IMXRT_FLEXPWM3.offset0FE)
#define FLEXPWM3_SM2CVAL0CYC		(IMXRT_FLEXPWM3.offset100)
#define FLEXPWM3_SM2CVAL1		(IMXRT_FLEXPWM3.offset102)
#define FLEXPWM3_SM2CVAL1CYC		(IMXRT_FLEXPWM3.offset104)
#define FLEXPWM3_SM2CVAL2		(IMXRT_FLEXPWM3.offset106)
#define FLEXPWM3_SM2CVAL2CYC		(IMXRT_FLEXPWM3.offset108)
#define FLEXPWM3_SM2CVAL3		(IMXRT_FLEXPWM3.offset10A)
#define FLEXPWM3_SM2CVAL3CYC		(IMXRT_FLEXPWM3.offset10C)
#define FLEXPWM3_SM2CVAL4		(IMXRT_FLEXPWM3.offset10E)
#define FLEXPWM3_SM2CVAL4CYC		(IMXRT_FLEXPWM3.offset110)
#define FLEXPWM3_SM2CVAL5		(IMXRT_FLEXPWM3.offset112)
#define FLEXPWM3_SM2CVAL5CYC		(IMXRT_FLEXPWM3.offset114)
#define FLEXPWM3_SM3CNT			(IMXRT_FLEXPWM3.offset120)
#define FLEXPWM3_SM3INIT		(IMXRT_FLEXPWM3.offset122)
#define FLEXPWM3_SM3CTRL2		(IMXRT_FLEXPWM3.offset124)
#define FLEXPWM3_SM3CTRL		(IMXRT_FLEXPWM3.offset126)
#define FLEXPWM3_SM3VAL0		(IMXRT_FLEXPWM3.offset128)
#define FLEXPWM3_SM3FRACVAL1		(IMXRT_FLEXPWM3.offset12A)
#define FLEXPWM3_SM3VAL1		(IMXRT_FLEXPWM3.offset12C)
#define FLEXPWM3_SM3FRACVAL2		(IMXRT_FLEXPWM3.offset12E)
#define FLEXPWM3_SM3VAL2		(IMXRT_FLEXPWM3.offset130)
#define FLEXPWM3_SM3FRACVAL3		(IMXRT_FLEXPWM3.offset132)
#define FLEXPWM3_SM3VAL3		(IMXRT_FLEXPWM3.offset134)
#define FLEXPWM3_SM3FRACVAL4		(IMXRT_FLEXPWM3.offset136)
#define FLEXPWM3_SM3VAL4		(IMXRT_FLEXPWM3.offset138)
#define FLEXPWM3_SM3FRACVAL5		(IMXRT_FLEXPWM3.offset13A)
#define FLEXPWM3_SM3VAL5		(IMXRT_FLEXPWM3.offset13C)
#define FLEXPWM3_SM3FRCTRL		(IMXRT_FLEXPWM3.offset13E)
#define FLEXPWM3_SM3OCTRL		(IMXRT_FLEXPWM3.offset140)
#define FLEXPWM3_SM3STS			(IMXRT_FLEXPWM3.offset142)
#define FLEXPWM3_SM3INTEN		(IMXRT_FLEXPWM3.offset144)
#define FLEXPWM3_SM3DMAEN		(IMXRT_FLEXPWM3.offset146)
#define FLEXPWM3_SM3TCTRL		(IMXRT_FLEXPWM3.offset148)
#define FLEXPWM3_SM3DISMAP0		(IMXRT_FLEXPWM3.offset14A)
#define FLEXPWM3_SM3DISMAP1		(IMXRT_FLEXPWM3.offset14C)
#define FLEXPWM3_SM3DTCNT0		(IMXRT_FLEXPWM3.offset15E)
#define FLEXPWM3_SM3DTCNT1		(IMXRT_FLEXPWM3.offset150)
#define FLEXPWM3_SM3CAPTCTRLA		(IMXRT_FLEXPWM3.offset152)
#define FLEXPWM3_SM3CAPTCOMPA		(IMXRT_FLEXPWM3.offset154)
#define FLEXPWM3_SM3CAPTCTRLB		(IMXRT_FLEXPWM3.offset156)
#define FLEXPWM3_SM3CAPTCOMPB		(IMXRT_FLEXPWM3.offset158)
#define FLEXPWM3_SM3CAPTCTRLX		(IMXRT_FLEXPWM3.offset15A)
#define FLEXPWM3_SM3CAPTCOMPX		(IMXRT_FLEXPWM3.offset15C)
#define FLEXPWM3_SM3CVAL0		(IMXRT_FLEXPWM3.offset15E)
#define FLEXPWM3_SM3CVAL0CYC		(IMXRT_FLEXPWM3.offset160)
#define FLEXPWM3_SM3CVAL1		(IMXRT_FLEXPWM3.offset162)
#define FLEXPWM3_SM3CVAL1CYC		(IMXRT_FLEXPWM3.offset164)
#define FLEXPWM3_SM3CVAL2		(IMXRT_FLEXPWM3.offset166)
#define FLEXPWM3_SM3CVAL2CYC		(IMXRT_FLEXPWM3.offset168)
#define FLEXPWM3_SM3CVAL3		(IMXRT_FLEXPWM3.offset16A)
#define FLEXPWM3_SM3CVAL3CYC		(IMXRT_FLEXPWM3.offset16C)
#define FLEXPWM3_SM3CVAL4		(IMXRT_FLEXPWM3.offset16E)
#define FLEXPWM3_SM3CVAL4CYC		(IMXRT_FLEXPWM3.offset170)
#define FLEXPWM3_SM3CVAL5		(IMXRT_FLEXPWM3.offset172)
#define FLEXPWM3_SM3CVAL5CYC		(IMXRT_FLEXPWM3.offset174)
#define FLEXPWM3_OUTEN			(IMXRT_FLEXPWM3.offset180)
#define FLEXPWM3_MASK			(IMXRT_FLEXPWM3.offset182)
#define FLEXPWM3_SWCOUT			(IMXRT_FLEXPWM3.offset184)
#define FLEXPWM3_DTSRCSEL		(IMXRT_FLEXPWM3.offset186)
#define FLEXPWM3_MCTRL			(IMXRT_FLEXPWM3.offset188)
#define FLEXPWM3_MCTRL2			(IMXRT_FLEXPWM3.offset18A)
#define FLEXPWM3_FCTRL0			(IMXRT_FLEXPWM3.offset18C)
#define FLEXPWM3_FSTS0			(IMXRT_FLEXPWM3.offset18E)
#define FLEXPWM3_FFILT0			(IMXRT_FLEXPWM3.offset190)
#define FLEXPWM3_FTST0			(IMXRT_FLEXPWM3.offset192)
#define FLEXPWM3_FCTRL20		(IMXRT_FLEXPWM3.offset194)
#define IMXRT_FLEXPWM4		(*(IMXRT_REGISTER16_t *)0x403E8000)
#define FLEXPWM4_SM0CNT			(IMXRT_FLEXPWM4.offset000)
#define FLEXPWM4_SM0INIT		(IMXRT_FLEXPWM4.offset002)
#define FLEXPWM4_SM0CTRL2		(IMXRT_FLEXPWM4.offset004)
#define FLEXPWM4_SM0CTRL		(IMXRT_FLEXPWM4.offset006)
#define FLEXPWM4_SM0VAL0		(IMXRT_FLEXPWM4.offset008)
#define FLEXPWM4_SM0FRACVAL1		(IMXRT_FLEXPWM4.offset00A)
#define FLEXPWM4_SM0VAL1		(IMXRT_FLEXPWM4.offset00C)
#define FLEXPWM4_SM0FRACVAL2		(IMXRT_FLEXPWM4.offset00E)
#define FLEXPWM4_SM0VAL2		(IMXRT_FLEXPWM4.offset010)
#define FLEXPWM4_SM0FRACVAL3		(IMXRT_FLEXPWM4.offset012)
#define FLEXPWM4_SM0VAL3		(IMXRT_FLEXPWM4.offset014)
#define FLEXPWM4_SM0FRACVAL4		(IMXRT_FLEXPWM4.offset016)
#define FLEXPWM4_SM0VAL4		(IMXRT_FLEXPWM4.offset018)
#define FLEXPWM4_SM0FRACVAL5		(IMXRT_FLEXPWM4.offset01A)
#define FLEXPWM4_SM0VAL5		(IMXRT_FLEXPWM4.offset01C)
#define FLEXPWM4_SM0FRCTRL		(IMXRT_FLEXPWM4.offset01E)
#define FLEXPWM4_SM0OCTRL		(IMXRT_FLEXPWM4.offset020)
#define FLEXPWM4_SM0STS			(IMXRT_FLEXPWM4.offset022)
#define FLEXPWM4_SM0INTEN		(IMXRT_FLEXPWM4.offset024)
#define FLEXPWM4_SM0DMAEN		(IMXRT_FLEXPWM4.offset026)
#define FLEXPWM4_SM0TCTRL		(IMXRT_FLEXPWM4.offset028)
#define FLEXPWM4_SM0DISMAP0		(IMXRT_FLEXPWM4.offset02A)
#define FLEXPWM4_SM0DISMAP1		(IMXRT_FLEXPWM4.offset02C)
#define FLEXPWM4_SM0DTCNT0		(IMXRT_FLEXPWM4.offset02E)
#define FLEXPWM4_SM0DTCNT1		(IMXRT_FLEXPWM4.offset030)
#define FLEXPWM4_SM0CAPTCTRLA		(IMXRT_FLEXPWM4.offset032)
#define FLEXPWM4_SM0CAPTCOMPA		(IMXRT_FLEXPWM4.offset034)
#define FLEXPWM4_SM0CAPTCTRLB		(IMXRT_FLEXPWM4.offset036)
#define FLEXPWM4_SM0CAPTCOMPB		(IMXRT_FLEXPWM4.offset038)
#define FLEXPWM4_SM0CAPTCTRLX		(IMXRT_FLEXPWM4.offset03A)
#define FLEXPWM4_SM0CAPTCOMPX		(IMXRT_FLEXPWM4.offset03C)
#define FLEXPWM4_SM0CVAL0		(IMXRT_FLEXPWM4.offset03E)
#define FLEXPWM4_SM0CVAL0CYC		(IMXRT_FLEXPWM4.offset040)
#define FLEXPWM4_SM0CVAL1		(IMXRT_FLEXPWM4.offset042)
#define FLEXPWM4_SM0CVAL1CYC		(IMXRT_FLEXPWM4.offset044)
#define FLEXPWM4_SM0CVAL2		(IMXRT_FLEXPWM4.offset046)
#define FLEXPWM4_SM0CVAL2CYC		(IMXRT_FLEXPWM4.offset048)
#define FLEXPWM4_SM0CVAL3		(IMXRT_FLEXPWM4.offset04A)
#define FLEXPWM4_SM0CVAL3CYC		(IMXRT_FLEXPWM4.offset04C)
#define FLEXPWM4_SM0CVAL4		(IMXRT_FLEXPWM4.offset04E)
#define FLEXPWM4_SM0CVAL4CYC		(IMXRT_FLEXPWM4.offset050)
#define FLEXPWM4_SM0CVAL5		(IMXRT_FLEXPWM4.offset052)
#define FLEXPWM4_SM0CVAL5CYC		(IMXRT_FLEXPWM4.offset054)
#define FLEXPWM4_SM1CNT			(IMXRT_FLEXPWM4.offset060)
#define FLEXPWM4_SM1INIT		(IMXRT_FLEXPWM4.offset062)
#define FLEXPWM4_SM1CTRL2		(IMXRT_FLEXPWM4.offset064)
#define FLEXPWM4_SM1CTRL		(IMXRT_FLEXPWM4.offset066)
#define FLEXPWM4_SM1VAL0		(IMXRT_FLEXPWM4.offset068)
#define FLEXPWM4_SM1FRACVAL1		(IMXRT_FLEXPWM4.offset06A)
#define FLEXPWM4_SM1VAL1		(IMXRT_FLEXPWM4.offset06C)
#define FLEXPWM4_SM1FRACVAL2		(IMXRT_FLEXPWM4.offset06E)
#define FLEXPWM4_SM1VAL2		(IMXRT_FLEXPWM4.offset070)
#define FLEXPWM4_SM1FRACVAL3		(IMXRT_FLEXPWM4.offset072)
#define FLEXPWM4_SM1VAL3		(IMXRT_FLEXPWM4.offset074)
#define FLEXPWM4_SM1FRACVAL4		(IMXRT_FLEXPWM4.offset076)
#define FLEXPWM4_SM1VAL4		(IMXRT_FLEXPWM4.offset078)
#define FLEXPWM4_SM1FRACVAL5		(IMXRT_FLEXPWM4.offset07A)
#define FLEXPWM4_SM1VAL5		(IMXRT_FLEXPWM4.offset07C)
#define FLEXPWM4_SM1FRCTRL		(IMXRT_FLEXPWM4.offset07E)
#define FLEXPWM4_SM1OCTRL		(IMXRT_FLEXPWM4.offset080)
#define FLEXPWM4_SM1STS			(IMXRT_FLEXPWM4.offset082)
#define FLEXPWM4_SM1INTEN		(IMXRT_FLEXPWM4.offset084)
#define FLEXPWM4_SM1DMAEN		(IMXRT_FLEXPWM4.offset086)
#define FLEXPWM4_SM1TCTRL		(IMXRT_FLEXPWM4.offset088)
#define FLEXPWM4_SM1DISMAP0		(IMXRT_FLEXPWM4.offset08A)
#define FLEXPWM4_SM1DISMAP1		(IMXRT_FLEXPWM4.offset08C)
#define FLEXPWM4_SM1DTCNT0		(IMXRT_FLEXPWM4.offset08E)
#define FLEXPWM4_SM1DTCNT1		(IMXRT_FLEXPWM4.offset090)
#define FLEXPWM4_SM1CAPTCTRLA		(IMXRT_FLEXPWM4.offset092)
#define FLEXPWM4_SM1CAPTCOMPA		(IMXRT_FLEXPWM4.offset094)
#define FLEXPWM4_SM1CAPTCTRLB		(IMXRT_FLEXPWM4.offset096)
#define FLEXPWM4_SM1CAPTCOMPB		(IMXRT_FLEXPWM4.offset098)
#define FLEXPWM4_SM1CAPTCTRLX		(IMXRT_FLEXPWM4.offset09A)
#define FLEXPWM4_SM1CAPTCOMPX		(IMXRT_FLEXPWM4.offset09C)
#define FLEXPWM4_SM1CVAL0		(IMXRT_FLEXPWM4.offset09E)
#define FLEXPWM4_SM1CVAL0CYC		(IMXRT_FLEXPWM4.offset0A0)
#define FLEXPWM4_SM1CVAL1		(IMXRT_FLEXPWM4.offset0A2)
#define FLEXPWM4_SM1CVAL1CYC		(IMXRT_FLEXPWM4.offset0A4)
#define FLEXPWM4_SM1CVAL2		(IMXRT_FLEXPWM4.offset0A6)
#define FLEXPWM4_SM1CVAL2CYC		(IMXRT_FLEXPWM4.offset0A8)
#define FLEXPWM4_SM1CVAL3		(IMXRT_FLEXPWM4.offset0AA)
#define FLEXPWM4_SM1CVAL3CYC		(IMXRT_FLEXPWM4.offset0AC)
#define FLEXPWM4_SM1CVAL4		(IMXRT_FLEXPWM4.offset0AE)
#define FLEXPWM4_SM1CVAL4CYC		(IMXRT_FLEXPWM4.offset0B0)
#define FLEXPWM4_SM1CVAL5		(IMXRT_FLEXPWM4.offset0B2)
#define FLEXPWM4_SM1CVAL5CYC		(IMXRT_FLEXPWM4.offset0B4)
#define FLEXPWM4_SM2CNT			(IMXRT_FLEXPWM4.offset0C0)
#define FLEXPWM4_SM2INIT		(IMXRT_FLEXPWM4.offset0C2)
#define FLEXPWM4_SM2CTRL2		(IMXRT_FLEXPWM4.offset0C4)
#define FLEXPWM4_SM2CTRL		(IMXRT_FLEXPWM4.offset0C6)
#define FLEXPWM4_SM2VAL0		(IMXRT_FLEXPWM4.offset0C8)
#define FLEXPWM4_SM2FRACVAL1		(IMXRT_FLEXPWM4.offset0CA)
#define FLEXPWM4_SM2VAL1		(IMXRT_FLEXPWM4.offset0CC)
#define FLEXPWM4_SM2FRACVAL2		(IMXRT_FLEXPWM4.offset0CE)
#define FLEXPWM4_SM2VAL2		(IMXRT_FLEXPWM4.offset0D0)
#define FLEXPWM4_SM2FRACVAL3		(IMXRT_FLEXPWM4.offset0D2)
#define FLEXPWM4_SM2VAL3		(IMXRT_FLEXPWM4.offset0D4)
#define FLEXPWM4_SM2FRACVAL4		(IMXRT_FLEXPWM4.offset0D6)
#define FLEXPWM4_SM2VAL4		(IMXRT_FLEXPWM4.offset0D8)
#define FLEXPWM4_SM2FRACVAL5		(IMXRT_FLEXPWM4.offset0DA)
#define FLEXPWM4_SM2VAL5		(IMXRT_FLEXPWM4.offset0DC)
#define FLEXPWM4_SM2FRCTRL		(IMXRT_FLEXPWM4.offset0DE)
#define FLEXPWM4_SM2OCTRL		(IMXRT_FLEXPWM4.offset0E0)
#define FLEXPWM4_SM2STS			(IMXRT_FLEXPWM4.offset0E2)
#define FLEXPWM4_SM2INTEN		(IMXRT_FLEXPWM4.offset0E4)
#define FLEXPWM4_SM2DMAEN		(IMXRT_FLEXPWM4.offset0E6)
#define FLEXPWM4_SM2TCTRL		(IMXRT_FLEXPWM4.offset0E8)
#define FLEXPWM4_SM2DISMAP0		(IMXRT_FLEXPWM4.offset0EA)
#define FLEXPWM4_SM2DISMAP1		(IMXRT_FLEXPWM4.offset0EC)
#define FLEXPWM4_SM2DTCNT0		(IMXRT_FLEXPWM4.offset0EE)
#define FLEXPWM4_SM2DTCNT1		(IMXRT_FLEXPWM4.offset0F0)
#define FLEXPWM4_SM2CAPTCTRLA		(IMXRT_FLEXPWM4.offset0F2)
#define FLEXPWM4_SM2CAPTCOMPA		(IMXRT_FLEXPWM4.offset0F4)
#define FLEXPWM4_SM2CAPTCTRLB		(IMXRT_FLEXPWM4.offset0F6)
#define FLEXPWM4_SM2CAPTCOMPB		(IMXRT_FLEXPWM4.offset0F8)
#define FLEXPWM4_SM2CAPTCTRLX		(IMXRT_FLEXPWM4.offset0FA)
#define FLEXPWM4_SM2CAPTCOMPX		(IMXRT_FLEXPWM4.offset0FC)
#define FLEXPWM4_SM2CVAL0		(IMXRT_FLEXPWM4.offset0FE)
#define FLEXPWM4_SM2CVAL0CYC		(IMXRT_FLEXPWM4.offset100)
#define FLEXPWM4_SM2CVAL1		(IMXRT_FLEXPWM4.offset102)
#define FLEXPWM4_SM2CVAL1CYC		(IMXRT_FLEXPWM4.offset104)
#define FLEXPWM4_SM2CVAL2		(IMXRT_FLEXPWM4.offset106)
#define FLEXPWM4_SM2CVAL2CYC		(IMXRT_FLEXPWM4.offset108)
#define FLEXPWM4_SM2CVAL3		(IMXRT_FLEXPWM4.offset10A)
#define FLEXPWM4_SM2CVAL3CYC		(IMXRT_FLEXPWM4.offset10C)
#define FLEXPWM4_SM2CVAL4		(IMXRT_FLEXPWM4.offset10E)
#define FLEXPWM4_SM2CVAL4CYC		(IMXRT_FLEXPWM4.offset110)
#define FLEXPWM4_SM2CVAL5		(IMXRT_FLEXPWM4.offset112)
#define FLEXPWM4_SM2CVAL5CYC		(IMXRT_FLEXPWM4.offset114)
#define FLEXPWM4_SM3CNT			(IMXRT_FLEXPWM4.offset120)
#define FLEXPWM4_SM3INIT		(IMXRT_FLEXPWM4.offset122)
#define FLEXPWM4_SM3CTRL2		(IMXRT_FLEXPWM4.offset124)
#define FLEXPWM4_SM3CTRL		(IMXRT_FLEXPWM4.offset126)
#define FLEXPWM4_SM3VAL0		(IMXRT_FLEXPWM4.offset128)
#define FLEXPWM4_SM3FRACVAL1		(IMXRT_FLEXPWM4.offset12A)
#define FLEXPWM4_SM3VAL1		(IMXRT_FLEXPWM4.offset12C)
#define FLEXPWM4_SM3FRACVAL2		(IMXRT_FLEXPWM4.offset12E)
#define FLEXPWM4_SM3VAL2		(IMXRT_FLEXPWM4.offset130)
#define FLEXPWM4_SM3FRACVAL3		(IMXRT_FLEXPWM4.offset132)
#define FLEXPWM4_SM3VAL3		(IMXRT_FLEXPWM4.offset134)
#define FLEXPWM4_SM3FRACVAL4		(IMXRT_FLEXPWM4.offset136)
#define FLEXPWM4_SM3VAL4		(IMXRT_FLEXPWM4.offset138)
#define FLEXPWM4_SM3FRACVAL5		(IMXRT_FLEXPWM4.offset13A)
#define FLEXPWM4_SM3VAL5		(IMXRT_FLEXPWM4.offset13C)
#define FLEXPWM4_SM3FRCTRL		(IMXRT_FLEXPWM4.offset13E)
#define FLEXPWM4_SM3OCTRL		(IMXRT_FLEXPWM4.offset140)
#define FLEXPWM4_SM3STS			(IMXRT_FLEXPWM4.offset142)
#define FLEXPWM4_SM3INTEN		(IMXRT_FLEXPWM4.offset144)
#define FLEXPWM4_SM3DMAEN		(IMXRT_FLEXPWM4.offset146)
#define FLEXPWM4_SM3TCTRL		(IMXRT_FLEXPWM4.offset148)
#define FLEXPWM4_SM3DISMAP0		(IMXRT_FLEXPWM4.offset14A)
#define FLEXPWM4_SM3DISMAP1		(IMXRT_FLEXPWM4.offset14C)
#define FLEXPWM4_SM3DTCNT0		(IMXRT_FLEXPWM4.offset15E)
#define FLEXPWM4_SM3DTCNT1		(IMXRT_FLEXPWM4.offset150)
#define FLEXPWM4_SM3CAPTCTRLA		(IMXRT_FLEXPWM4.offset152)
#define FLEXPWM4_SM3CAPTCOMPA		(IMXRT_FLEXPWM4.offset154)
#define FLEXPWM4_SM3CAPTCTRLB		(IMXRT_FLEXPWM4.offset156)
#define FLEXPWM4_SM3CAPTCOMPB		(IMXRT_FLEXPWM4.offset158)
#define FLEXPWM4_SM3CAPTCTRLX		(IMXRT_FLEXPWM4.offset15A)
#define FLEXPWM4_SM3CAPTCOMPX		(IMXRT_FLEXPWM4.offset15C)
#define FLEXPWM4_SM3CVAL0		(IMXRT_FLEXPWM4.offset15E)
#define FLEXPWM4_SM3CVAL0CYC		(IMXRT_FLEXPWM4.offset160)
#define FLEXPWM4_SM3CVAL1		(IMXRT_FLEXPWM4.offset162)
#define FLEXPWM4_SM3CVAL1CYC		(IMXRT_FLEXPWM4.offset164)
#define FLEXPWM4_SM3CVAL2		(IMXRT_FLEXPWM4.offset166)
#define FLEXPWM4_SM3CVAL2CYC		(IMXRT_FLEXPWM4.offset168)
#define FLEXPWM4_SM3CVAL3		(IMXRT_FLEXPWM4.offset16A)
#define FLEXPWM4_SM3CVAL3CYC		(IMXRT_FLEXPWM4.offset16C)
#define FLEXPWM4_SM3CVAL4		(IMXRT_FLEXPWM4.offset16E)
#define FLEXPWM4_SM3CVAL4CYC		(IMXRT_FLEXPWM4.offset170)
#define FLEXPWM4_SM3CVAL5		(IMXRT_FLEXPWM4.offset172)
#define FLEXPWM4_SM3CVAL5CYC		(IMXRT_FLEXPWM4.offset174)
#define FLEXPWM4_OUTEN			(IMXRT_FLEXPWM4.offset180)
#define FLEXPWM4_MASK			(IMXRT_FLEXPWM4.offset182)
#define FLEXPWM4_SWCOUT			(IMXRT_FLEXPWM4.offset184)
#define FLEXPWM4_DTSRCSEL		(IMXRT_FLEXPWM4.offset186)
#define FLEXPWM4_MCTRL			(IMXRT_FLEXPWM4.offset188)
#define FLEXPWM4_MCTRL2			(IMXRT_FLEXPWM4.offset18A)
#define FLEXPWM4_FCTRL0			(IMXRT_FLEXPWM4.offset18C)
#define FLEXPWM4_FSTS0			(IMXRT_FLEXPWM4.offset18E)
#define FLEXPWM4_FFILT0			(IMXRT_FLEXPWM4.offset190)
#define FLEXPWM4_FTST0			(IMXRT_FLEXPWM4.offset192)
#define FLEXPWM4_FCTRL20		(IMXRT_FLEXPWM4.offset194)

// page 1470
#define IMXRT_FLEXRAM		(*(IMXRT_REGISTER32_t *)0x400B0000)
#define FLEXRAM_TCM_CTRL		(IMXRT_FLEXRAM.offset000)
#define FLEXRAM_OCRAM_MAGIC_ADDR	(IMXRT_FLEXRAM.offset004)
#define FLEXRAM_DTCM_MAGIC_ADDR		(IMXRT_FLEXRAM.offset008)
#define FLEXRAM_ITCM_MAGIC_ADDR		(IMXRT_FLEXRAM.offset00C)
#define FLEXRAM_INT_STATUS		(IMXRT_FLEXRAM.offset010)
#define FLEXRAM_INT_STAT_EN		(IMXRT_FLEXRAM.offset014)
#define FLEXRAM_INT_SIG_EN		(IMXRT_FLEXRAM.offset018)
#define FLEXRAM_TCM_CTRL_FORCE_CLK_ON			((uint32_t)0x00000004)
#define FLEXRAM_TCM_CTRL_TCM_RWAIT_EN			((uint32_t)0x00000002)
#define FLEXRAM_TCM_CTRL_TCM_WWAIT_EN			((uint32_t)0x00000001)
#define FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS		((uint32_t)0x00000020)
#define FLEXRAM_INT_STATUS_DTCM_ERR_STATUS		((uint32_t)0x00000010)
#define FLEXRAM_INT_STATUS_ITCM_ERR_STATUS		((uint32_t)0x00000008)
#define FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN		((uint32_t)0x00000020)
#define FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN		((uint32_t)0x00000010)
#define FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN		((uint32_t)0x00000008)
#define FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN		((uint32_t)0x00000020)
#define FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN		((uint32_t)0x00000010)
#define FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN		((uint32_t)0x00000008)

// page 1583
#define IMXRT_FLEXSPI		(*(IMXRT_REGISTER32_t *)0x400B0000)
#define FLEXSPI_MCR0			(IMXRT_FLEXSPI.offset000)
#define FLEXSPI_MCR1			(IMXRT_FLEXSPI.offset004)
#define FLEXSPI_MCR2			(IMXRT_FLEXSPI.offset008)
#define FLEXSPI_AHBCR			(IMXRT_FLEXSPI.offset00C)
#define FLEXSPI_INTEN			(IMXRT_FLEXSPI.offset010)
#define FLEXSPI_INTR			(IMXRT_FLEXSPI.offset014)
#define FLEXSPI_LUTKEY			(IMXRT_FLEXSPI.offset018)
#define FLEXSPI_LUTCR			(IMXRT_FLEXSPI.offset01C)
#define FLEXSPI_AHBRXBUF0CR0		(IMXRT_FLEXSPI.offset020)
#define FLEXSPI_AHBRXBUF1CR0		(IMXRT_FLEXSPI.offset024)
#define FLEXSPI_AHBRXBUF2CR0		(IMXRT_FLEXSPI.offset028)
#define FLEXSPI_AHBRXBUF3CR0		(IMXRT_FLEXSPI.offset02C)
#define FLEXSPI_FLSHA1CR0		(IMXRT_FLEXSPI.offset060)
#define FLEXSPI_FLSHA2CR0		(IMXRT_FLEXSPI.offset064)
#define FLEXSPI_FLSHB1CR0		(IMXRT_FLEXSPI.offset068)
#define FLEXSPI_FLSHB2CR0		(IMXRT_FLEXSPI.offset06C)
#define FLEXSPI_FLSHA1CR1		(IMXRT_FLEXSPI.offset070)
#define FLEXSPI_FLSHA2CR1		(IMXRT_FLEXSPI.offset074)
#define FLEXSPI_FLSHB1CR1		(IMXRT_FLEXSPI.offset078)
#define FLEXSPI_FLSHB2CR1		(IMXRT_FLEXSPI.offset07C)
#define FLEXSPI_FLSHA1CR2		(IMXRT_FLEXSPI.offset080)
#define FLEXSPI_FLSHA2CR2		(IMXRT_FLEXSPI.offset084)
#define FLEXSPI_FLSHB1CR2		(IMXRT_FLEXSPI.offset088)
#define FLEXSPI_FLSHB2CR2		(IMXRT_FLEXSPI.offset08C)
#define FLEXSPI_IPCR0			(IMXRT_FLEXSPI.offset0A0)
#define FLEXSPI_IPCR1			(IMXRT_FLEXSPI.offset0A4)
#define FLEXSPI_IPCMD			(IMXRT_FLEXSPI.offset0B0)
#define FLEXSPI_DLPR			(IMXRT_FLEXSPI.offset0B4)
#define FLEXSPI_IPRXFCR			(IMXRT_FLEXSPI.offset0B8)
#define FLEXSPI_IPTXFCR			(IMXRT_FLEXSPI.offset0BC)
#define FLEXSPI_DLLACR			(IMXRT_FLEXSPI.offset0C0)
#define FLEXSPI_DLLBCR			(IMXRT_FLEXSPI.offset0C4)
#define FLEXSPI_STS0			(IMXRT_FLEXSPI.offset0E0)
#define FLEXSPI_STS1			(IMXRT_FLEXSPI.offset0E4)
#define FLEXSPI_STS2			(IMXRT_FLEXSPI.offset0E8)
#define FLEXSPI_AHBSPNDSTS		(IMXRT_FLEXSPI.offset0EC)
#define FLEXSPI_IPRXFSTS		(IMXRT_FLEXSPI.offset0F0)
#define FLEXSPI_IPTXFSTS		(IMXRT_FLEXSPI.offset0F4)
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

// page 1595
#define IMXRT_GPC		(*(IMXRT_REGISTER32_t *)0x400F4000)
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
#define GPC_CNTR_PDRAM0_PGE				((uint32_t)0x00400000)
#define GPC_CNTR_MEGA_PUP_REQ				((uint32_t)0x00000008)
#define GPC_CNTR_MEGA_PDN_REQ				((uint32_t)0x00000004)
// page 1602
#define PGC_MEGA_CTRL			(IMXRT_GPC.offset220)
#define PGC_MEGA_PUPSCR			(IMXRT_GPC.offset224)
#define PGC_MEGA_PDNSCR			(IMXRT_GPC.offset228)
#define PGC_MEGA_SR			(IMXRT_GPC.offset22C)
#define PGC_CPU_CTRL			(IMXRT_GPC.offset2A0)
#define PGC_CPU_PUPSCR			(IMXRT_GPC.offset2A4)
#define PGC_CPU_PDNSCR			(IMXRT_GPC.offset2A8)
#define PGC_CPU_SR			(IMXRT_GPC.offset2AC)
#define PGC_MEGA_CTRL_PCR				((uint32_t)0x00000001)
#define PGC_MEGA_PUPSCR_SW2ISO(n)			((uint32_t)(((n) & 0x3F) << 8))
#define PGC_MEGA_PUPSCR_SW(n)				((uint32_t)(((n) & 0x3F) << 0))
#define PGC_MEGA_PDNSCR_ISO2SW(n)			((uint32_t)(((n) & 0x3F) << 8))
#define PGC_MEGA_PDNSCR_ISO(n)				((uint32_t)(((n) & 0x3F) << 0))
#define PGC_MEGA_SR_PSR					((uint32_t)0x00000001)
#define PGC_CPU_CTRL_PCR				((uint32_t)0x00000001)
#define PGC_CPU_PUPSCR_SW2ISO(n)			((uint32_t)(((n) & 0x3F) << 8))
#define PGC_CPU_PUPSCR_SW(n)				((uint32_t)(((n) & 0x3F) << 0))
#define PGC_CPU_PDNSCR_ISO2SW(n)			((uint32_t)(((n) & 0x3F) << 8))
#define PGC_CPU_PDNSCR_ISO(n)				((uint32_t)(((n) & 0x3F) << 0))
#define PGC_CPU_SR_PSR					((uint32_t)0x00000001)


// page 1658
#define IMXRT_GPIO1		(*(IMXRT_REGISTER32_t *)0x401B8000)
#define GPIO1_DR			(IMXRT_GPIO1.offset000)
#define GPIO1_GDIR			(IMXRT_GPIO1.offset004)
#define GPIO1_PSR			(IMXRT_GPIO1.offset008)
#define GPIO1_ICR1			(IMXRT_GPIO1.offset00C)
#define GPIO1_ICR2			(IMXRT_GPIO1.offset010)
#define GPIO1_IMR			(IMXRT_GPIO1.offset014)
#define GPIO1_ISR			(IMXRT_GPIO1.offset018)
#define GPIO1_EDGE_SEL			(IMXRT_GPIO1.offset01C)
#define IMXRT_GPIO2		(*(IMXRT_REGISTER32_t *)0x401BC000)
#define GPIO2_DR			(IMXRT_GPIO2.offset000)
#define GPIO2_GDIR			(IMXRT_GPIO2.offset004)
#define GPIO2_PSR			(IMXRT_GPIO2.offset008)
#define GPIO2_ICR1			(IMXRT_GPIO2.offset00C)
#define GPIO2_ICR2			(IMXRT_GPIO2.offset010)
#define GPIO2_IMR			(IMXRT_GPIO2.offset014)
#define GPIO2_ISR			(IMXRT_GPIO2.offset018)
#define GPIO2_EDGE_SEL			(IMXRT_GPIO2.offset01C)
#define IMXRT_GPIO3		(*(IMXRT_REGISTER32_t *)0x401C0000)
#define GPIO3_DR			(IMXRT_GPIO3.offset000)
#define GPIO3_GDIR			(IMXRT_GPIO3.offset004)
#define GPIO3_PSR			(IMXRT_GPIO3.offset008)
#define GPIO3_ICR1			(IMXRT_GPIO3.offset00C)
#define GPIO3_ICR2			(IMXRT_GPIO3.offset010)
#define GPIO3_IMR			(IMXRT_GPIO3.offset014)
#define GPIO3_ISR			(IMXRT_GPIO3.offset018)
#define GPIO3_EDGE_SEL			(IMXRT_GPIO3.offset01C)
#define IMXRT_GPIO4		(*(IMXRT_REGISTER32_t *)0x401C4000)
#define GPIO4_DR			(IMXRT_GPIO4.offset000)
#define GPIO4_GDIR			(IMXRT_GPIO4.offset004)
#define GPIO4_PSR			(IMXRT_GPIO4.offset008)
#define GPIO4_ICR1			(IMXRT_GPIO4.offset00C)
#define GPIO4_ICR2			(IMXRT_GPIO4.offset010)
#define GPIO4_IMR			(IMXRT_GPIO4.offset014)
#define GPIO4_ISR			(IMXRT_GPIO4.offset018)
#define GPIO4_EDGE_SEL			(IMXRT_GPIO4.offset01C)
#define IMXRT_GPIO5		(*(IMXRT_REGISTER32_t *)0x400C0000)
#define GPIO5_DR			(IMXRT_GPIO5.offset000)
#define GPIO5_GDIR			(IMXRT_GPIO5.offset004)
#define GPIO5_PSR			(IMXRT_GPIO5.offset008)
#define GPIO5_ICR1			(IMXRT_GPIO5.offset00C)
#define GPIO5_ICR2			(IMXRT_GPIO5.offset010)
#define GPIO5_IMR			(IMXRT_GPIO5.offset014)
#define GPIO5_ISR			(IMXRT_GPIO5.offset018)
#define GPIO5_EDGE_SEL			(IMXRT_GPIO5.offset01C)

// page 1686
#define IMXRT_GPT1		(*(IMXRT_REGISTER32_t *)0x401EC000)
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
#define IMXRT_GPT2		(*(IMXRT_REGISTER32_t *)0x401F0000)
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

// page 1669
#define IMXRT_IOMUXC_GPR	(*(IMXRT_REGISTER32_t *)0x400AC000)
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
#define IOMUXC_GPR_GPR1_CM7_FORCE_HCLK_EN		((uint32_t)0x80000000)
#define IOMUXC_GPR_GPR1_ENET_IPG_CLK_S_EN		((uint32_t)0x00800000)
#define IOMUXC_GPR_GPR1_EXC_MON				((uint32_t)0x00400000)
#define IOMUXC_GPR_GPR1_SAI3_MCLK_DIR			((uint32_t)0x00200000)
#define IOMUXC_GPR_GPR1_SAI2_MCLK_DIR			((uint32_t)0x00100000)
#define IOMUXC_GPR_GPR1_SAI1_MCLK_DIR			((uint32_t)0x00080000)
#define IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR		((uint32_t)0x00020000)
#define IOMUXC_GPR_GPR1_USB_EXP_MODE			((uint32_t)0x00008000)
#define IOMUXC_GPR_GPR1_ENET1_CLK_SEL			((uint32_t)0x00002000)
#define IOMUXC_GPR_GPR1_GINT				((uint32_t)0x00001000)
#define IOMUXC_GPR_GPR1_SAI3_MCLK3_SEL(n)		((uint32_t)(((n) & 0x03) << 10))
#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL(n)		((uint32_t)(((n) & 0x03) << 8))
#define IOMUXC_GPR_GPR1_SAI1_MCLK3_SEL(n)		((uint32_t)(((n) & 0x03) << 6))
#define IOMUXC_GPR_GPR1_SAI1_MCLK2_SEL(n)		((uint32_t)(((n) & 0x07) << 3))
#define IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(n)		((uint32_t)(((n) & 0x07) << 0))
#define IOMUXC_GPR_GPR1_SAI3_MCLK3_SEL_MASK		IOMUXC_GPR_GPR1_SAI3_MCLK3_SEL(3)
#define IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL_MASK		IOMUXC_GPR_GPR1_SAI2_MCLK3_SEL(3)
#define IOMUXC_GPR_GPR1_SAI1_MCLK3_SEL_MASK		IOMUXC_GPR_GPR1_SAI1_MCLK3_SEL(3)
#define IOMUXC_GPR_GPR1_SAI1_MCLK2_SEL_MASK		IOMUXC_GPR_GPR1_SAI1_MCLK2_SEL(7)
#define IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL_MASK		IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(7)
#define IOMUXC_GPR_GPR2_QTIMER4_TMR_CNTS_FREEZE		((uint32_t)0x80000000)
#define IOMUXC_GPR_GPR2_QTIMER3_TMR_CNTS_FREEZE		((uint32_t)0x40000000)
#define IOMUXC_GPR_GPR2_QTIMER2_TMR_CNTS_FREEZE		((uint32_t)0x20000000)
#define IOMUXC_GPR_GPR2_QTIMER1_TMR_CNTS_FREEZE		((uint32_t)0x10000000)
#define IOMUXC_GPR_GPR2_MQS_OVERSAMPLE			((uint32_t)0x04000000)
#define IOMUXC_GPR_GPR2_MQS_EN				((uint32_t)0x02000000)
#define IOMUXC_GPR_GPR2_MQS_SW_RST			((uint32_t)0x01000000)
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV(n)			((uint32_t)(((n) & 0xFF) << 16))
#define IOMUXC_GPR_GPR2_L2_MEM_DEEPSLEEP		((uint32_t)0x00004000)
#define IOMUXC_GPR_GPR2_L2_MEM_EN_POWERSAVING		((uint32_t)0x00001000)
#define IOMUXC_GPR_GPR2_MQS_CLK_DIV_MASK		IOMUXC_GPR_GPR2_MQS_CLK_DIV(255)
#define IOMUXC_GPR_GPR3_OCRAM_STATUS(n)			((uint32_t)(((n) & 0x0F) << 16))
#define IOMUXC_GPR_GPR3_DCP_KEY_SEL			((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR3_OCRAM_CTL(n)			((uint32_t)(((n) & 0x0F) << 0))
#define IOMUXC_GPR_GPR4_FLEXIO2_STOP_ACK		((uint32_t)0x20000000)
#define IOMUXC_GPR_GPR4_FLEXIO1_STOP_ACK		((uint32_t)0x10000000)
#define IOMUXC_GPR_GPR4_FLEXSPI_STOP_ACK		((uint32_t)0x08000000)
#define IOMUXC_GPR_GPR4_PIT_STOP_ACK			((uint32_t)0x04000000)
#define IOMUXC_GPR_GPR4_SEMC_STOP_ACK			((uint32_t)0x02000000)
#define IOMUXC_GPR_GPR4_SAI3_STOP_ACK			((uint32_t)0x00800000)
#define IOMUXC_GPR_GPR4_SAI2_STOP_ACK			((uint32_t)0x00400000)
#define IOMUXC_GPR_GPR4_SAI1_STOP_ACK			((uint32_t)0x00200000)
#define IOMUXC_GPR_GPR4_ENET_STOP_ACK			((uint32_t)0x00100000)
#define IOMUXC_GPR_GPR4_TRNG_STOP_ACK			((uint32_t)0x00080000)
#define IOMUXC_GPR_GPR4_CAN2_STOP_ACK			((uint32_t)0x00040000)
#define IOMUXC_GPR_GPR4_CAN1_STOP_ACK			((uint32_t)0x00020000)
#define IOMUXC_GPR_GPR4_EDMA_STOP_ACK			((uint32_t)0x00010000)
#define IOMUXC_GPR_GPR4_FLEXIO2_STOP_REQ		((uint32_t)0x00002000)
#define IOMUXC_GPR_GPR4_FLEXIO1_STOP_REQ		((uint32_t)0x00001000)
#define IOMUXC_GPR_GPR4_FLEXSPI_STOP_REQ		((uint32_t)0x00000800)
#define IOMUXC_GPR_GPR4_PIT_STOP_REQ			((uint32_t)0x00000400)
#define IOMUXC_GPR_GPR4_SEMC_STOP_REQ			((uint32_t)0x00000200)
#define IOMUXC_GPR_GPR4_SAI3_STOP_REQ			((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR4_SAI2_STOP_REQ			((uint32_t)0x00000040)
#define IOMUXC_GPR_GPR4_SAI1_STOP_REQ			((uint32_t)0x00000020)
#define IOMUXC_GPR_GPR4_ENET_STOP_REQ			((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR4_TRNG_STOP_REQ			((uint32_t)0x00000008)
#define IOMUXC_GPR_GPR4_CAN2_STOP_REQ			((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR4_CAN1_STOP_REQ			((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR4_EDMA_STOP_REQ			((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT2		((uint32_t)0x20000000)
#define IOMUXC_GPR_GPR5_VREF_1M_CLK_GPT1		((uint32_t)0x10000000)
#define IOMUXC_GPR_GPR5_ENET_EVENT3IN_SEL		((uint32_t)0x02000000)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN2_SEL			((uint32_t)0x01000000)
#define IOMUXC_GPR_GPR5_GPT2_CAPIN1_SEL			((uint32_t)0x00800000)
#define IOMUXC_GPR_GPR5_WDOG2_MASK			((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR5_WDOG1_MASK			((uint32_t)0x00000040)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_19		((uint32_t)0x80000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_18		((uint32_t)0x40000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_17		((uint32_t)0x20000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_16		((uint32_t)0x10000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_15		((uint32_t)0x08000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_14		((uint32_t)0x04000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_13		((uint32_t)0x02000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_12		((uint32_t)0x01000000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_11		((uint32_t)0x00800000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_10		((uint32_t)0x00400000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_9		((uint32_t)0x00200000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_8		((uint32_t)0x00100000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_7		((uint32_t)0x00080000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_6		((uint32_t)0x00040000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_5		((uint32_t)0x00020000)
#define IOMUXC_GPR_GPR6_IOMUXC_XBAR_DIR_SEL_4		((uint32_t)0x00010000)
#define IOMUXC_GPR_GPR6_QTIMER4_TRM3_INPUT_SEL		((uint32_t)0x00008000)
#define IOMUXC_GPR_GPR6_QTIMER4_TRM2_INPUT_SEL		((uint32_t)0x00004000)
#define IOMUXC_GPR_GPR6_QTIMER4_TRM1_INPUT_SEL		((uint32_t)0x00002000)
#define IOMUXC_GPR_GPR6_QTIMER4_TRM0_INPUT_SEL		((uint32_t)0x00001000)
#define IOMUXC_GPR_GPR6_QTIMER3_TRM3_INPUT_SEL		((uint32_t)0x00000800)
#define IOMUXC_GPR_GPR6_QTIMER3_TRM2_INPUT_SEL		((uint32_t)0x00000400)
#define IOMUXC_GPR_GPR6_QTIMER3_TRM1_INPUT_SEL		((uint32_t)0x00000200)
#define IOMUXC_GPR_GPR6_QTIMER3_TRM0_INPUT_SEL		((uint32_t)0x00000100)
#define IOMUXC_GPR_GPR6_QTIMER2_TRM3_INPUT_SEL		((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR6_QTIMER2_TRM2_INPUT_SEL		((uint32_t)0x00000040)
#define IOMUXC_GPR_GPR6_QTIMER2_TRM1_INPUT_SEL		((uint32_t)0x00000020)
#define IOMUXC_GPR_GPR6_QTIMER2_TRM0_INPUT_SEL		((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR6_QTIMER1_TRM3_INPUT_SEL		((uint32_t)0x00000008)
#define IOMUXC_GPR_GPR6_QTIMER1_TRM2_INPUT_SEL		((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR6_QTIMER1_TRM1_INPUT_SEL		((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR6_QTIMER1_TRM0_INPUT_SEL		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR7_LPUART8_STOP_ACK		((uint32_t)0x80000000)
#define IOMUXC_GPR_GPR7_LPUART7_STOP_ACK		((uint32_t)0x40000000)
#define IOMUXC_GPR_GPR7_LPUART6_STOP_ACK		((uint32_t)0x20000000)
#define IOMUXC_GPR_GPR7_LPUART5_STOP_ACK		((uint32_t)0x10000000)
#define IOMUXC_GPR_GPR7_LPUART4_STOP_ACK		((uint32_t)0x08000000)
#define IOMUXC_GPR_GPR7_LPUART3_STOP_ACK		((uint32_t)0x04000000)
#define IOMUXC_GPR_GPR7_LPUART2_STOP_ACK		((uint32_t)0x02000000)
#define IOMUXC_GPR_GPR7_LPUART1_STOP_ACK		((uint32_t)0x01000000)
#define IOMUXC_GPR_GPR7_LPSPI4_STOP_ACK			((uint32_t)0x00800000)
#define IOMUXC_GPR_GPR7_LPSPI3_STOP_ACK			((uint32_t)0x00400000)
#define IOMUXC_GPR_GPR7_LPSPI2_STOP_ACK			((uint32_t)0x00200000)
#define IOMUXC_GPR_GPR7_LPSPI1_STOP_ACK			((uint32_t)0x00100000)
#define IOMUXC_GPR_GPR7_LPI2C4_STOP_ACK			((uint32_t)0x00080000)
#define IOMUXC_GPR_GPR7_LPI2C3_STOP_ACK			((uint32_t)0x00040000)
#define IOMUXC_GPR_GPR7_LPI2C2_STOP_ACK			((uint32_t)0x00020000)
#define IOMUXC_GPR_GPR7_LPI2C1_STOP_ACK			((uint32_t)0x00010000)
#define IOMUXC_GPR_GPR7_LPUART8_STOP_REQ		((uint32_t)0x00008000)
#define IOMUXC_GPR_GPR7_LPUART7_STOP_REQ		((uint32_t)0x00004000)
#define IOMUXC_GPR_GPR7_LPUART6_STOP_REQ		((uint32_t)0x00002000)
#define IOMUXC_GPR_GPR7_LPUART5_STOP_REQ		((uint32_t)0x00001000)
#define IOMUXC_GPR_GPR7_LPUART4_STOP_REQ		((uint32_t)0x00000800)
#define IOMUXC_GPR_GPR7_LPUART3_STOP_REQ		((uint32_t)0x00000400)
#define IOMUXC_GPR_GPR7_LPUART2_STOP_REQ		((uint32_t)0x00000200)
#define IOMUXC_GPR_GPR7_LPUART1_STOP_REQ		((uint32_t)0x00000100)
#define IOMUXC_GPR_GPR7_LPSPI4_STOP_REQ			((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR7_LPSPI3_STOP_REQ			((uint32_t)0x00000040)
#define IOMUXC_GPR_GPR7_LPSPI2_STOP_REQ			((uint32_t)0x00000020)
#define IOMUXC_GPR_GPR7_LPSPI1_STOP_REQ			((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR7_LPI2C4_STOP_REQ			((uint32_t)0x00000008)
#define IOMUXC_GPR_GPR7_LPI2C3_STOP_REQ			((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR7_LPI2C2_STOP_REQ			((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR7_LPI2C1_STOP_REQ			((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR8_LPUART8_IPG_DOZE		((uint32_t)0x80000000)
#define IOMUXC_GPR_GPR8_LPUART8_IPG_STOP_MODE		((uint32_t)0x40000000)
#define IOMUXC_GPR_GPR8_LPUART7_IPG_DOZE		((uint32_t)0x20000000)
#define IOMUXC_GPR_GPR8_LPUART7_IPG_STOP_MODE		((uint32_t)0x10000000)
#define IOMUXC_GPR_GPR8_LPUART6_IPG_DOZE		((uint32_t)0x08000000)
#define IOMUXC_GPR_GPR8_LPUART6_IPG_STOP_MODE		((uint32_t)0x04000000)
#define IOMUXC_GPR_GPR8_LPUART5_IPG_DOZE		((uint32_t)0x02000000)
#define IOMUXC_GPR_GPR8_LPUART5_IPG_STOP_MODE		((uint32_t)0x01000000)
#define IOMUXC_GPR_GPR8_LPUART4_IPG_DOZE		((uint32_t)0x00800000)
#define IOMUXC_GPR_GPR8_LPUART4_IPG_STOP_MODE		((uint32_t)0x00400000)
#define IOMUXC_GPR_GPR8_LPUART3_IPG_DOZE		((uint32_t)0x00200000)
#define IOMUXC_GPR_GPR8_LPUART3_IPG_STOP_MODE		((uint32_t)0x00100000)
#define IOMUXC_GPR_GPR8_LPUART2_IPG_DOZE		((uint32_t)0x00080000)
#define IOMUXC_GPR_GPR8_LPUART2_IPG_STOP_MODE		((uint32_t)0x00040000)
#define IOMUXC_GPR_GPR8_LPUART1_IPG_DOZE		((uint32_t)0x00020000)
#define IOMUXC_GPR_GPR8_LPUART1_IPG_STOP_MODE		((uint32_t)0x00010000)
#define IOMUXC_GPR_GPR8_LPSPI4_IPG_DOZE			((uint32_t)0x00008000)
#define IOMUXC_GPR_GPR8_LPSPI4_IPG_STOP_MODE		((uint32_t)0x00004000)
#define IOMUXC_GPR_GPR8_LPSPI3_IPG_DOZE			((uint32_t)0x00002000)
#define IOMUXC_GPR_GPR8_LPSPI3_IPG_STOP_MODE		((uint32_t)0x00001000)
#define IOMUXC_GPR_GPR8_LPSPI2_IPG_DOZE			((uint32_t)0x00000800)
#define IOMUXC_GPR_GPR8_LPSPI2_IPG_STOP_MODE		((uint32_t)0x00000400)
#define IOMUXC_GPR_GPR8_LPSPI1_IPG_DOZE			((uint32_t)0x00000200)
#define IOMUXC_GPR_GPR8_LPSPI1_IPG_STOP_MODE		((uint32_t)0x00000100)
#define IOMUXC_GPR_GPR8_LPI2C4_IPG_DOZE			((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR8_LPI2C4_IPG_STOP_MODE		((uint32_t)0x00000040)
#define IOMUXC_GPR_GPR8_LPI2C3_IPG_DOZE			((uint32_t)0x00000020)
#define IOMUXC_GPR_GPR8_LPI2C3_IPG_STOP_MODE		((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR8_LPI2C2_IPG_DOZE			((uint32_t)0x00000008)
#define IOMUXC_GPR_GPR8_LPI2C2_IPG_STOP_MODE		((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR8_LPI2C1_IPG_DOZE			((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR8_LPI2C1_IPG_STOP_MODE		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR10_LOCK_OCRAM_TZ_ADDR(n)		((uint32_t)(((n) & 0x7F) << 25))
#define IOMUXC_GPR_GPR10_LOCK_OCRAM_TZ_EN		((uint32_t)0x01000000)
#define IOMUXC_GPR_GPR10_LOCK_DCPKEY_OCOTP_OR_KEYMUX	((uint32_t)0x00100000)
#define IOMUXC_GPR_GPR10_LOCK_SEC_ERR_RESP		((uint32_t)0x00040000)
#define IOMUXC_GPR_GPR10_LOCK_DBG_EN			((uint32_t)0x00020000)
#define IOMUXC_GPR_GPR10_LOCK_NIDEN			((uint32_t)0x00010000)
#define IOMUXC_GPR_GPR10_OCRAM_TZ_ADDR(n)		((uint32_t)(((n) & 0x7F) << 9))
#define IOMUXC_GPR_GPR10_OCRAM_TZ_EN			((uint32_t)0x00000100)
#define IOMUXC_GPR_GPR10_DCPKEY_OCOTP_OR_KEYMUX		((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR10_SEC_ERR_RESP			((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR10_DBG_EN				((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR10_NIDEN				((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR11_LOCK_BEE_DE_RX_EN(n)		((uint32_t)(((n) & 0x0F) << 24))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R3_CTRL(n)	((uint32_t)(((n) & 0x03) << 22))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R2_CTRL(n)	((uint32_t)(((n) & 0x03) << 20))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R1_CTRL(n)	((uint32_t)(((n) & 0x03) << 18))
#define IOMUXC_GPR_GPR11_LOCK_M7_APC_AC_R0_CTRL(n)	((uint32_t)(((n) & 0x03) << 16))
#define IOMUXC_GPR_GPR11_BEE_DE_RX_EN(n)		((uint32_t)(((n) & 0x0F) << 8))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R3_CTRL(n)		((uint32_t)(((n) & 0x03) << 6))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R2_CTRL(n)		((uint32_t)(((n) & 0x03) << 4))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R1_CTRL(n)		((uint32_t)(((n) & 0x03) << 2))
#define IOMUXC_GPR_GPR11_M7_APC_AC_R0_CTRL(n)		((uint32_t)(((n) & 0x03) << 0))
#define IOMUXC_GPR_GPR12_ACMP_IPG_STOP_MODE		((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR12_FLEXIO2_IPG_DOZE		((uint32_t)0x00000008)
#define IOMUXC_GPR_GPR12_FLEXIO2_IPG_STOP_MODE		((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR12_FLEXIO1_IPG_DOZE		((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR12_FLEXIO1_IPG_STOP_MODE		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR13_CACHE_USB			((uint32_t)0x00002000)
#define IOMUXC_GPR_GPR13_CACHE_ENET			((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR13_AWCACHE_USDHC			((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR13_ARCACHE_USDHC			((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR14_CM7_MX6RT_CFGDTCMSZ(n)		((uint32_t)(((n) & 0x0F) << 20))
#define IOMUXC_GPR_GPR14_CM7_MX6RT_CFGITCMSZ(n)		((uint32_t)(((n) & 0x0F) << 16))
#define IOMUXC_GPR_GPR14_ACMP4_SAMPLE_SYNC_EN		((uint32_t)0x00000800)
#define IOMUXC_GPR_GPR14_ACMP3_SAMPLE_SYNC_EN		((uint32_t)0x00000400)
#define IOMUXC_GPR_GPR14_ACMP2_SAMPLE_SYNC_EN		((uint32_t)0x00000200)
#define IOMUXC_GPR_GPR14_ACMP1_SAMPLE_SYNC_EN		((uint32_t)0x00000100)
#define IOMUXC_GPR_GPR14_ACMP4_CMP_IGEN_TRIM_UP		((uint32_t)0x00000080)
#define IOMUXC_GPR_GPR14_ACMP3_CMP_IGEN_TRIM_UP		((uint32_t)0x00000040)
#define IOMUXC_GPR_GPR14_ACMP2_CMP_IGEN_TRIM_UP		((uint32_t)0x00000020)
#define IOMUXC_GPR_GPR14_ACMP1_CMP_IGEN_TRIM_UP		((uint32_t)0x00000010)
#define IOMUXC_GPR_GPR14_ACMP4_CMP_IGEN_TRIM_DN		((uint32_t)0x00000008)
#define IOMUXC_GPR_GPR14_ACMP3_CMP_IGEN_TRIM_DN		((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR14_ACMP2_CMP_IGEN_TRIM_DN		((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR14_ACMP1_CMP_IGEN_TRIM_DN		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR16_CM7_INIT_VTOR(n)		((uint32_t)(((n) & 0x1FFFFFF) << 7))
#define IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL		((uint32_t)0x00000004)
#define IOMUXC_GPR_GPR16_INIT_DTCM_EN			((uint32_t)0x00000002)
#define IOMUXC_GPR_GPR16_INIT_ITCM_EN			((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR18_M7_APC_AC_R0_BOT(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR18_LOCK_M7_APC_AC_R0_BOT		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR19_M7_APC_AC_R0_TOP(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR19_LOCK_M7_APC_AC_R0_TOP		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR20_M7_APC_AC_R1_BOT(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR20_LOCK_M7_APC_AC_R1_BOT		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR21_M7_APC_AC_R1_TOP(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR21_LOCK_M7_APC_AC_R1_TOP		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR22_M7_APC_AC_R2_BOT(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR22_LOCK_M7_APC_AC_R2_BOT		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR23_M7_APC_AC_R2_TOP(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR23_LOCK_M7_APC_AC_R2_TOP		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR24_M7_APC_AC_R3_BOT(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR24_LOCK_M7_APC_AC_R3_BOT		((uint32_t)0x00000001)
#define IOMUXC_GPR_GPR25_M7_APC_AC_R3_TOP(n)		((uint32_t)(((n) & 0x1FFFFFFF) << 3))
#define IOMUXC_GPR_GPR25_LOCK_M7_APC_AC_R3_TOP		((uint32_t)0x00000001)

// page 1750
#define IMXRT_IOMUXC_SNVS	(*(IMXRT_REGISTER32_t *)0x400A8000)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP		(IMXRT_IOMUXC_SNVS.offset000)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ		(IMXRT_IOMUXC_SNVS.offset004)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ	(IMXRT_IOMUXC_SNVS.offset008)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE		(IMXRT_IOMUXC_SNVS.offset00C)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B		(IMXRT_IOMUXC_SNVS.offset010)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF		(IMXRT_IOMUXC_SNVS.offset014)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP		(IMXRT_IOMUXC_SNVS.offset018)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ		(IMXRT_IOMUXC_SNVS.offset01C)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ	(IMXRT_IOMUXC_SNVS.offset020)

// page 1765
#define IMXRT_IOMUXC_SNVS_GPR	(*(IMXRT_REGISTER32_t *)0x400A4000)
#define IOMUXC_SNVS_GPR_GPR0		(IMXRT_IOMUXC_SNVS_GPR.offset000)
#define IOMUXC_SNVS_GPR_GPR1		(IMXRT_IOMUXC_SNVS_GPR.offset004)
#define IOMUXC_SNVS_GPR_GPR2		(IMXRT_IOMUXC_SNVS_GPR.offset008)
#define IOMUXC_SNVS_GPR_GPR3		(IMXRT_IOMUXC_SNVS_GPR.offset00C)

// page 1769
#define IMXRT_IOMUXC		(*(IMXRT_REGISTER32_t *)0x401F8000)
#define IMXRT_IOMUXC_b		(*(IMXRT_REGISTER32_t *)0x401F8400)
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

// page 2356
#define IMXRT_KPP		(*(IMXRT_REGISTER16_t *)0x401FC000)
#define KPP_KPCR			(IMXRT_KPP.offset000)
#define KPP_KPSR			(IMXRT_KPP.offset002)
#define KPP_KDDR			(IMXRT_KPP.offset004)
#define KPP_KPDR			(IMXRT_KPP.offset006)

// page 2380
#define IMXRT_LCDIF		(*(IMXRT_REGISTER32_t *)0x402B8000)
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
#define IMXRT_LCDIF_b		(*(IMXRT_REGISTER32_t *)0x402B8800)
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

// page 2415
#define IMXRT_LPI2C1		(*(IMXRT_REGISTER32_t *)0x403F0000)
#define LPI2C1_VERID			(IMXRT_LPI2C1.offset000)
#define LPI2C1_PARAM			(IMXRT_LPI2C1.offset004)
#define LPI2C1_MCR			(IMXRT_LPI2C1.offset010)
#define LPI2C1_MSR			(IMXRT_LPI2C1.offset014)
#define LPI2C1_MIER			(IMXRT_LPI2C1.offset018)
#define LPI2C1_MDER			(IMXRT_LPI2C1.offset01C)
#define LPI2C1_MCFGR0			(IMXRT_LPI2C1.offset020)
#define LPI2C1_MCFGR1			(IMXRT_LPI2C1.offset024)
#define LPI2C1_MCFGR2			(IMXRT_LPI2C1.offset028)
#define LPI2C1_MCFGR3			(IMXRT_LPI2C1.offset02C)
#define LPI2C1_MDMR			(IMXRT_LPI2C1.offset040)
#define LPI2C1_MCCR0			(IMXRT_LPI2C1.offset048)
#define LPI2C1_MCCR1			(IMXRT_LPI2C1.offset050)
#define LPI2C1_MFCR			(IMXRT_LPI2C1.offset058)
#define LPI2C1_MFSR			(IMXRT_LPI2C1.offset05C)
#define LPI2C1_MTDR			(IMXRT_LPI2C1.offset060)
#define LPI2C1_MRDR			(IMXRT_LPI2C1.offset070)
#define LPI2C1_SCR			(IMXRT_LPI2C1.offset110)
#define LPI2C1_SSR			(IMXRT_LPI2C1.offset114)
#define LPI2C1_SIER			(IMXRT_LPI2C1.offset118)
#define LPI2C1_SDER			(IMXRT_LPI2C1.offset11C)
#define LPI2C1_SCFGR1			(IMXRT_LPI2C1.offset124)
#define LPI2C1_SCFGR2			(IMXRT_LPI2C1.offset128)
#define LPI2C1_SAMR			(IMXRT_LPI2C1.offset140)
#define LPI2C1_SASR			(IMXRT_LPI2C1.offset150)
#define LPI2C1_STAR			(IMXRT_LPI2C1.offset154)
#define LPI2C1_STDR			(IMXRT_LPI2C1.offset160)
#define LPI2C1_SRDR			(IMXRT_LPI2C1.offset170)
#define IMXRT_LPI2C2		(*(IMXRT_REGISTER32_t *)0x403F4000)
#define LPI2C2_VERID			(IMXRT_LPI2C2.offset000)
#define LPI2C2_PARAM			(IMXRT_LPI2C2.offset004)
#define LPI2C2_MCR			(IMXRT_LPI2C2.offset010)
#define LPI2C2_MSR			(IMXRT_LPI2C2.offset014)
#define LPI2C2_MIER			(IMXRT_LPI2C2.offset018)
#define LPI2C2_MDER			(IMXRT_LPI2C2.offset01C)
#define LPI2C2_MCFGR0			(IMXRT_LPI2C2.offset020)
#define LPI2C2_MCFGR1			(IMXRT_LPI2C2.offset024)
#define LPI2C2_MCFGR2			(IMXRT_LPI2C2.offset028)
#define LPI2C2_MCFGR3			(IMXRT_LPI2C2.offset02C)
#define LPI2C2_MDMR			(IMXRT_LPI2C2.offset040)
#define LPI2C2_MCCR0			(IMXRT_LPI2C2.offset048)
#define LPI2C2_MCCR1			(IMXRT_LPI2C2.offset050)
#define LPI2C2_MFCR			(IMXRT_LPI2C2.offset058)
#define LPI2C2_MFSR			(IMXRT_LPI2C2.offset05C)
#define LPI2C2_MTDR			(IMXRT_LPI2C2.offset060)
#define LPI2C2_MRDR			(IMXRT_LPI2C2.offset070)
#define LPI2C2_SCR			(IMXRT_LPI2C2.offset110)
#define LPI2C2_SSR			(IMXRT_LPI2C2.offset114)
#define LPI2C2_SIER			(IMXRT_LPI2C2.offset118)
#define LPI2C2_SDER			(IMXRT_LPI2C2.offset11C)
#define LPI2C2_SCFGR1			(IMXRT_LPI2C2.offset124)
#define LPI2C2_SCFGR2			(IMXRT_LPI2C2.offset128)
#define LPI2C2_SAMR			(IMXRT_LPI2C2.offset140)
#define LPI2C2_SASR			(IMXRT_LPI2C2.offset150)
#define LPI2C2_STAR			(IMXRT_LPI2C2.offset154)
#define LPI2C2_STDR			(IMXRT_LPI2C2.offset160)
#define LPI2C2_SRDR			(IMXRT_LPI2C2.offset170)
#define IMXRT_LPI2C3		(*(IMXRT_REGISTER32_t *)0x403F8000)
#define LPI2C3_VERID			(IMXRT_LPI2C3.offset000)
#define LPI2C3_PARAM			(IMXRT_LPI2C3.offset004)
#define LPI2C3_MCR			(IMXRT_LPI2C3.offset010)
#define LPI2C3_MSR			(IMXRT_LPI2C3.offset014)
#define LPI2C3_MIER			(IMXRT_LPI2C3.offset018)
#define LPI2C3_MDER			(IMXRT_LPI2C3.offset01C)
#define LPI2C3_MCFGR0			(IMXRT_LPI2C3.offset020)
#define LPI2C3_MCFGR1			(IMXRT_LPI2C3.offset024)
#define LPI2C3_MCFGR2			(IMXRT_LPI2C3.offset028)
#define LPI2C3_MCFGR3			(IMXRT_LPI2C3.offset02C)
#define LPI2C3_MDMR			(IMXRT_LPI2C3.offset040)
#define LPI2C3_MCCR0			(IMXRT_LPI2C3.offset048)
#define LPI2C3_MCCR1			(IMXRT_LPI2C3.offset050)
#define LPI2C3_MFCR			(IMXRT_LPI2C3.offset058)
#define LPI2C3_MFSR			(IMXRT_LPI2C3.offset05C)
#define LPI2C3_MTDR			(IMXRT_LPI2C3.offset060)
#define LPI2C3_MRDR			(IMXRT_LPI2C3.offset070)
#define LPI2C3_SCR			(IMXRT_LPI2C3.offset110)
#define LPI2C3_SSR			(IMXRT_LPI2C3.offset114)
#define LPI2C3_SIER			(IMXRT_LPI2C3.offset118)
#define LPI2C3_SDER			(IMXRT_LPI2C3.offset11C)
#define LPI2C3_SCFGR1			(IMXRT_LPI2C3.offset124)
#define LPI2C3_SCFGR2			(IMXRT_LPI2C3.offset128)
#define LPI2C3_SAMR			(IMXRT_LPI2C3.offset140)
#define LPI2C3_SASR			(IMXRT_LPI2C3.offset150)
#define LPI2C3_STAR			(IMXRT_LPI2C3.offset154)
#define LPI2C3_STDR			(IMXRT_LPI2C3.offset160)
#define LPI2C3_SRDR			(IMXRT_LPI2C3.offset170)
#define IMXRT_LPI2C4		(*(IMXRT_REGISTER32_t *)0x403FC000)
#define LPI2C4_VERID			(IMXRT_LPI2C4.offset000)
#define LPI2C4_PARAM			(IMXRT_LPI2C4.offset004)
#define LPI2C4_MCR			(IMXRT_LPI2C4.offset010)
#define LPI2C4_MSR			(IMXRT_LPI2C4.offset014)
#define LPI2C4_MIER			(IMXRT_LPI2C4.offset018)
#define LPI2C4_MDER			(IMXRT_LPI2C4.offset01C)
#define LPI2C4_MCFGR0			(IMXRT_LPI2C4.offset020)
#define LPI2C4_MCFGR1			(IMXRT_LPI2C4.offset024)
#define LPI2C4_MCFGR2			(IMXRT_LPI2C4.offset028)
#define LPI2C4_MCFGR3			(IMXRT_LPI2C4.offset02C)
#define LPI2C4_MDMR			(IMXRT_LPI2C4.offset040)
#define LPI2C4_MCCR0			(IMXRT_LPI2C4.offset048)
#define LPI2C4_MCCR1			(IMXRT_LPI2C4.offset050)
#define LPI2C4_MFCR			(IMXRT_LPI2C4.offset058)
#define LPI2C4_MFSR			(IMXRT_LPI2C4.offset05C)
#define LPI2C4_MTDR			(IMXRT_LPI2C4.offset060)
#define LPI2C4_MRDR			(IMXRT_LPI2C4.offset070)
#define LPI2C4_SCR			(IMXRT_LPI2C4.offset110)
#define LPI2C4_SSR			(IMXRT_LPI2C4.offset114)
#define LPI2C4_SIER			(IMXRT_LPI2C4.offset118)
#define LPI2C4_SDER			(IMXRT_LPI2C4.offset11C)
#define LPI2C4_SCFGR1			(IMXRT_LPI2C4.offset124)
#define LPI2C4_SCFGR2			(IMXRT_LPI2C4.offset128)
#define LPI2C4_SAMR			(IMXRT_LPI2C4.offset140)
#define LPI2C4_SASR			(IMXRT_LPI2C4.offset150)
#define LPI2C4_STAR			(IMXRT_LPI2C4.offset154)
#define LPI2C4_STDR			(IMXRT_LPI2C4.offset160)
#define LPI2C4_SRDR			(IMXRT_LPI2C4.offset170)

// page 2479
#define IMXRT_LPSPI1		(*(IMXRT_REGISTER32_t *)0x40394000)
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
#define IMXRT_LPSPI2		(*(IMXRT_REGISTER32_t *)0x40398000)
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
#define IMXRT_LPSPI3		(*(IMXRT_REGISTER32_t *)0x4039C000)
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
#define IMXRT_LPSPI4		(*(IMXRT_REGISTER32_t *)0x403A0000)
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

// page 2486
#define IMXRT_LPUART1		(*(IMXRT_REGISTER32_t *)0x40184000)
#define LPUART1_VERID			(IMXRT_LPUART1.offset000)
#define LPUART1_PARAM			(IMXRT_LPUART1.offset004)
#define LPUART1_GLOBAL			(IMXRT_LPUART1.offset008)
#define LPUART1_PINCFG			(IMXRT_LPUART1.offset00C)
#define LPUART1_BAUD			(IMXRT_LPUART1.offset010)
#define LPUART1_STAT			(IMXRT_LPUART1.offset014)
#define LPUART1_CTRL			(IMXRT_LPUART1.offset018)
#define LPUART1_DATA			(IMXRT_LPUART1.offset01C)
#define LPUART1_MATCH			(IMXRT_LPUART1.offset020)
#define LPUART1_MODIR			(IMXRT_LPUART1.offset024)
#define LPUART1_FIFO			(IMXRT_LPUART1.offset028)
#define LPUART1_WATER			(IMXRT_LPUART1.offset02C)
#define IMXRT_LPUART2		(*(IMXRT_REGISTER32_t *)0x40188000)
#define LPUART2_VERID			(IMXRT_LPUART2.offset000)
#define LPUART2_PARAM			(IMXRT_LPUART2.offset004)
#define LPUART2_GLOBAL			(IMXRT_LPUART2.offset008)
#define LPUART2_PINCFG			(IMXRT_LPUART2.offset00C)
#define LPUART2_BAUD			(IMXRT_LPUART2.offset010)
#define LPUART2_STAT			(IMXRT_LPUART2.offset014)
#define LPUART2_CTRL			(IMXRT_LPUART2.offset018)
#define LPUART2_DATA			(IMXRT_LPUART2.offset01C)
#define LPUART2_MATCH			(IMXRT_LPUART2.offset020)
#define LPUART2_MODIR			(IMXRT_LPUART2.offset024)
#define LPUART2_FIFO			(IMXRT_LPUART2.offset028)
#define LPUART2_WATER			(IMXRT_LPUART2.offset02C)
#define IMXRT_LPUART3		(*(IMXRT_REGISTER32_t *)0x4018C000)
#define LPUART3_VERID			(IMXRT_LPUART3.offset000)
#define LPUART3_PARAM			(IMXRT_LPUART3.offset004)
#define LPUART3_GLOBAL			(IMXRT_LPUART3.offset008)
#define LPUART3_PINCFG			(IMXRT_LPUART3.offset00C)
#define LPUART3_BAUD			(IMXRT_LPUART3.offset010)
#define LPUART3_STAT			(IMXRT_LPUART3.offset014)
#define LPUART3_CTRL			(IMXRT_LPUART3.offset018)
#define LPUART3_DATA			(IMXRT_LPUART3.offset01C)
#define LPUART3_MATCH			(IMXRT_LPUART3.offset020)
#define LPUART3_MODIR			(IMXRT_LPUART3.offset024)
#define LPUART3_FIFO			(IMXRT_LPUART3.offset028)
#define LPUART3_WATER			(IMXRT_LPUART3.offset02C)
#define IMXRT_LPUART4		(*(IMXRT_REGISTER32_t *)0x40190000)
#define LPUART4_VERID			(IMXRT_LPUART4.offset000)
#define LPUART4_PARAM			(IMXRT_LPUART4.offset004)
#define LPUART4_GLOBAL			(IMXRT_LPUART4.offset008)
#define LPUART4_PINCFG			(IMXRT_LPUART4.offset00C)
#define LPUART4_BAUD			(IMXRT_LPUART4.offset010)
#define LPUART4_STAT			(IMXRT_LPUART4.offset014)
#define LPUART4_CTRL			(IMXRT_LPUART4.offset018)
#define LPUART4_DATA			(IMXRT_LPUART4.offset01C)
#define LPUART4_MATCH			(IMXRT_LPUART4.offset020)
#define LPUART4_MODIR			(IMXRT_LPUART4.offset024)
#define LPUART4_FIFO			(IMXRT_LPUART4.offset028)
#define LPUART4_WATER			(IMXRT_LPUART4.offset02C)
#define IMXRT_LPUART5		(*(IMXRT_REGISTER32_t *)0x40194000)
#define LPUART5_VERID			(IMXRT_LPUART5.offset000)
#define LPUART5_PARAM			(IMXRT_LPUART5.offset004)
#define LPUART5_GLOBAL			(IMXRT_LPUART5.offset008)
#define LPUART5_PINCFG			(IMXRT_LPUART5.offset00C)
#define LPUART5_BAUD			(IMXRT_LPUART5.offset010)
#define LPUART5_STAT			(IMXRT_LPUART5.offset014)
#define LPUART5_CTRL			(IMXRT_LPUART5.offset018)
#define LPUART5_DATA			(IMXRT_LPUART5.offset01C)
#define LPUART5_MATCH			(IMXRT_LPUART5.offset020)
#define LPUART5_MODIR			(IMXRT_LPUART5.offset024)
#define LPUART5_FIFO			(IMXRT_LPUART5.offset028)
#define LPUART5_WATER			(IMXRT_LPUART5.offset02C)
#define IMXRT_LPUART6		(*(IMXRT_REGISTER32_t *)0x40198000)
#define LPUART6_VERID			(IMXRT_LPUART6.offset000)
#define LPUART6_PARAM			(IMXRT_LPUART6.offset004)
#define LPUART6_GLOBAL			(IMXRT_LPUART6.offset008)
#define LPUART6_PINCFG			(IMXRT_LPUART6.offset00C)
#define LPUART6_BAUD			(IMXRT_LPUART6.offset010)
#define LPUART6_STAT			(IMXRT_LPUART6.offset014)
#define LPUART6_CTRL			(IMXRT_LPUART6.offset018)
#define LPUART6_DATA			(IMXRT_LPUART6.offset01C)
#define LPUART6_MATCH			(IMXRT_LPUART6.offset020)
#define LPUART6_MODIR			(IMXRT_LPUART6.offset024)
#define LPUART6_FIFO			(IMXRT_LPUART6.offset028)
#define LPUART6_WATER			(IMXRT_LPUART6.offset02C)
#define IMXRT_LPUART7		(*(IMXRT_REGISTER32_t *)0x4019C000)
#define LPUART7_VERID			(IMXRT_LPUART7.offset000)
#define LPUART7_PARAM			(IMXRT_LPUART7.offset004)
#define LPUART7_GLOBAL			(IMXRT_LPUART7.offset008)
#define LPUART7_PINCFG			(IMXRT_LPUART7.offset00C)
#define LPUART7_BAUD			(IMXRT_LPUART7.offset010)
#define LPUART7_STAT			(IMXRT_LPUART7.offset014)
#define LPUART7_CTRL			(IMXRT_LPUART7.offset018)
#define LPUART7_DATA			(IMXRT_LPUART7.offset01C)
#define LPUART7_MATCH			(IMXRT_LPUART7.offset020)
#define LPUART7_MODIR			(IMXRT_LPUART7.offset024)
#define LPUART7_FIFO			(IMXRT_LPUART7.offset028)
#define LPUART7_WATER			(IMXRT_LPUART7.offset02C)
#define IMXRT_LPUART8		(*(IMXRT_REGISTER32_t *)0x401A0000)
#define LPUART8_VERID			(IMXRT_LPUART8.offset000)
#define LPUART8_PARAM			(IMXRT_LPUART8.offset004)
#define LPUART8_GLOBAL			(IMXRT_LPUART8.offset008)
#define LPUART8_PINCFG			(IMXRT_LPUART8.offset00C)
#define LPUART8_BAUD			(IMXRT_LPUART8.offset010)
#define LPUART8_STAT			(IMXRT_LPUART8.offset014)
#define LPUART8_CTRL			(IMXRT_LPUART8.offset018)
#define LPUART8_DATA			(IMXRT_LPUART8.offset01C)
#define LPUART8_MATCH			(IMXRT_LPUART8.offset020)
#define LPUART8_MODIR			(IMXRT_LPUART8.offset024)
#define LPUART8_FIFO			(IMXRT_LPUART8.offset028)
#define LPUART8_WATER			(IMXRT_LPUART8.offset02C)
#define LPUART_VERID_MAJOR(n)				((uint32_t)(((n) & 0xFF) << 24))
#define LPUART_VERID_MINOR(n)				((uint32_t)(((n) & 0xFF) << 16))
#define LPUART_VERID_FEATURE(n)				((uint32_t)(((n) & 0xFFFF) << 0))
#define LPUART_PARAM_RXFIFO(n)				((uint32_t)(((n) & 0xFF) << 8))
#define LPUART_PARAM_TXFIFO(n)				((uint32_t)(((n) & 0xFF) << 0))
#define LPUART_GLOBAL_RST				((uint32_t)0x00000002)
#define LPUART_PINCFG_TRGSEL(n)				((uint32_t)(((n) & 0x03) << 0))
#define LPUART_BAUD_MAEN1				((uint32_t)0x80000000)
#define LPUART_BAUD_MAEN2				((uint32_t)0x40000000)
#define LPUART_BAUD_M10					((uint32_t)0x20000000)
#define LPUART_BAUD_OSR(n)				((uint32_t)(((n) & 0x1F) << 24))
#define LPUART_BAUD_TDMAE				((uint32_t)0x00800000)
#define LPUART_BAUD_RDMAE				((uint32_t)0x00200000)
#define LPUART_BAUD_MATCFG(n)				((uint32_t)(((n) & 0x03) << 18))
#define LPUART_BAUD_BOTHEDGE				((uint32_t)0x00020000)
#define LPUART_BAUD_RESYNCDIS				((uint32_t)0x00010000)
#define LPUART_BAUD_LBKDIE				((uint32_t)0x00008000)
#define LPUART_BAUD_RXEDGIE				((uint32_t)0x00004000)
#define LPUART_BAUD_SBNS				((uint32_t)0x00002000)
#define LPUART_BAUD_SBR(n)				((uint32_t)(((n) & 0x01FFF) << 0))
#define LPUART_STAT_LBKDIF				((uint32_t)0x80000000)
#define LPUART_STAT_RXEDGIF				((uint32_t)0x40000000)
#define LPUART_STAT_MSBF				((uint32_t)0x20000000)
#define LPUART_STAT_RXINV				((uint32_t)0x10000000)
#define LPUART_STAT_RWUID				((uint32_t)0x08000000)
#define LPUART_STAT_BRK13				((uint32_t)0x04000000)
#define LPUART_STAT_LBKDE				((uint32_t)0x02000000)
#define LPUART_STAT_RAF					((uint32_t)0x01000000)
#define LPUART_STAT_TDRE				((uint32_t)0x00800000)
#define LPUART_STAT_TC					((uint32_t)0x00400000)
#define LPUART_STAT_RDRF				((uint32_t)0x00200000)
#define LPUART_STAT_IDLE				((uint32_t)0x00100000)
#define LPUART_STAT_OR					((uint32_t)0x00080000)
#define LPUART_STAT_NF					((uint32_t)0x00040000)
#define LPUART_STAT_FE					((uint32_t)0x00020000)
#define LPUART_STAT_PF					((uint32_t)0x00010000)
#define LPUART_STAT_MA1F				((uint32_t)0x00008000)
#define LPUART_STAT_MA2F				((uint32_t)0x00004000)
#define LPUART_CTRL_R8T9				((uint32_t)0x80000000)
#define LPUART_CTRL_R9T8				((uint32_t)0x40000000)
#define LPUART_CTRL_TXDIR				((uint32_t)0x20000000)
#define LPUART_CTRL_TXINV				((uint32_t)0x10000000)
#define LPUART_CTRL_ORIE				((uint32_t)0x08000000)
#define LPUART_CTRL_NEIE				((uint32_t)0x04000000)
#define LPUART_CTRL_FEIE				((uint32_t)0x02000000)
#define LPUART_CTRL_PEIE				((uint32_t)0x01000000)
#define LPUART_CTRL_TIE					((uint32_t)0x00800000)
#define LPUART_CTRL_TCIE				((uint32_t)0x00400000)
#define LPUART_CTRL_RIE					((uint32_t)0x00200000)
#define LPUART_CTRL_ILIE				((uint32_t)0x00100000)
#define LPUART_CTRL_TE					((uint32_t)0x00080000)
#define LPUART_CTRL_RE					((uint32_t)0x00040000)
#define LPUART_CTRL_RWU					((uint32_t)0x00020000)
#define LPUART_CTRL_SBK					((uint32_t)0x00010000)
#define LPUART_CTRL_MA1IE				((uint32_t)0x00008000)
#define LPUART_CTRL_MA2IE				((uint32_t)0x00004000)
#define LPUART_CTRL_M7					((uint32_t)0x00000800)
#define LPUART_CTRL_IDLECFG(n)				((uint32_t)(((n) & 0x07) << 8))
#define LPUART_CTRL_LOOPS				((uint32_t)0x00000080)
#define LPUART_CTRL_DOZEEN				((uint32_t)0x00000040)
#define LPUART_CTRL_RSRC				((uint32_t)0x00000020)
#define LPUART_CTRL_M					((uint32_t)0x00000010)
#define LPUART_CTRL_WAKE				((uint32_t)0x00000008)
#define LPUART_CTRL_ILT					((uint32_t)0x00000004)
#define LPUART_CTRL_PE					((uint32_t)0x00000002)
#define LPUART_CTRL_PT					((uint32_t)0x00000001)
#define LPUART_DATA_NOISY				((uint32_t)0x00008000)
#define LPUART_DATA_PARITYE				((uint32_t)0x00004000)
#define LPUART_DATA_FRETSC				((uint32_t)0x00002000)
#define LPUART_DATA_RXEMPT				((uint32_t)0x00001000)
#define LPUART_DATA_IDLINE				((uint32_t)0x00000800)
#define LPUART_MATCH_MA2(n)				((uint32_t)(((n) & 0x3FF) << 16))
#define LPUART_MATCH_MA1(n)				((uint32_t)(((n) & 0x3FF) << 0))
#define LPUART_MODIR_IREN				((uint32_t)0x00040000)
#define LPUART_MODIR_TNP(n)				((uint32_t)(((n) & 0x03) << 16))
#define LPUART_MODIR_RTSWATER(n)			((uint32_t)(((n) & 0x03) << 8))
#define LPUART_MODIR_TXCTSSRC				((uint32_t)0x00000020)
#define LPUART_MODIR_TXCTSC				((uint32_t)0x00000010)
#define LPUART_MODIR_RXRTSE				((uint32_t)0x00000008)
#define LPUART_MODIR_TXRTSPOL				((uint32_t)0x00000004)
#define LPUART_MODIR_TXRTSE				((uint32_t)0x00000002)
#define LPUART_MODIR_TXCTSE				((uint32_t)0x00000001)
#define LPUART_FIFO_TXEMPT				((uint32_t)0x00800000)
#define LPUART_FIFO_RXEMPT				((uint32_t)0x00400000)
#define LPUART_FIFO_TXOF				((uint32_t)0x00020000)
#define LPUART_FIFO_RXUF				((uint32_t)0x00010000)
#define LPUART_FIFO_TXFLUSH				((uint32_t)0x00008000)
#define LPUART_FIFO_RXFLUSH				((uint32_t)0x00004000)
#define LPUART_FIFO_RXIDEN(n)				((uint32_t)(((n) & 0x07) << 10))
#define LPUART_FIFO_TXOFE				((uint32_t)0x00000200)
#define LPUART_FIFO_RXUFE				((uint32_t)0x00000100)
#define LPUART_FIFO_TXFE				((uint32_t)0x00000080)
#define LPUART_FIFO_TXFIFOSIZE(n)			((uint32_t)(((n) & 0x07) << 4))
#define LPUART_FIFO_RXFE				((uint32_t)0x00000008)
#define LPUART_FIFO_RXFIFOSIZE(n)			((uint32_t)(((n) & 0x07) << 0))
#define LPUART_WATER_RXCOUNT(n)				((uint32_t)(((n) & 0x07) << 24))
#define LPUART_WATER_RXWATER(n)				((uint32_t)(((n) & 0x03) << 16))
#define LPUART_WATER_TXCOUNT(n)				((uint32_t)(((n) & 0x07) << 8))
#define LPUART_WATER_TXWATER(n)				((uint32_t)(((n) & 0x03) << 0))


// page 2558
#define IMXRT_OCOTP		(*(IMXRT_REGISTER32_t *)0x401F4000)
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
#define IMXRT_OCOTP_VALUE	(*(IMXRT_REGISTER32_t *)0x401F4400)
#define HW_OCOTP_LOCK			(IMXRT_OCOTP_VALUE.offset000)
#define HW_OCOTP_CFG0			(IMXRT_OCOTP_VALUE.offset010)
#define HW_OCOTP_CFG1			(IMXRT_OCOTP_VALUE.offset020)
#define HW_OCOTP_CFG2			(IMXRT_OCOTP_VALUE.offset030)
#define HW_OCOTP_CFG3			(IMXRT_OCOTP_VALUE.offset040)
#define HW_OCOTP_CFG4			(IMXRT_OCOTP_VALUE.offset050)
#define HW_OCOTP_CFG5			(IMXRT_OCOTP_VALUE.offset060)
#define HW_OCOTP_CFG6			(IMXRT_OCOTP_VALUE.offset070)
#define HW_OCOTP_MEM0			(IMXRT_OCOTP_VALUE.offset080)
#define HW_OCOTP MEM1			(IMXRT_OCOTP_VALUE.offset090)
#define HW_OCOTP_MEM2			(IMXRT_OCOTP_VALUE.offset0A0)
#define HW_OCOTP_MEM3			(IMXRT_OCOTP_VALUE.offset0B0)
#define HW_OCOTP_MEM4			(IMXRT_OCOTP_VALUE.offset0C0)
#define HW_OCOTP_ANA0			(IMXRT_OCOTP_VALUE.offset0D0)
#define HW_OCOTP_ANA1			(IMXRT_OCOTP_VALUE.offset0E0)
#define HW_OCOTP_ANA2			(IMXRT_OCOTP_VALUE.offset0F0)
#define HW_OCOTP_SRK0			(IMXRT_OCOTP_VALUE.offset180)
#define HW_OCOTP_SRK1			(IMXRT_OCOTP_VALUE.offset190)
#define HW_OCOTP_SRK2			(IMXRT_OCOTP_VALUE.offset1A0)
#define HW_OCOTP_SRK3			(IMXRT_OCOTP_VALUE.offset1B0)
#define HW_OCOTP_SRK4			(IMXRT_OCOTP_VALUE.offset1C0)
#define HW_OCOTP_SRK5			(IMXRT_OCOTP_VALUE.offset1D0)
#define HW_OCOTP_SRK6			(IMXRT_OCOTP_VALUE.offset1E0)
#define HW_OCOTP_SRK7			(IMXRT_OCOTP_VALUE.offset1F0)
#define HW_OCOTP_SJC_RESP0		(IMXRT_OCOTP_VALUE.offset200)
#define HW_OCOTP_SJC_RESP1		(IMXRT_OCOTP_VALUE.offset210)
#define HW_OCOTP_MAC0			(IMXRT_OCOTP_VALUE.offset220)
#define HW_OCOTP_MAC1			(IMXRT_OCOTP_VALUE.offset230)
#define HW_OCOTP_GP3			(IMXRT_OCOTP_VALUE.offset240)
#define HW_OCOTP_GP1			(IMXRT_OCOTP_VALUE.offset260)
#define HW_OCOTP_GP2			(IMXRT_OCOTP_VALUE.offset270)
#define HW_OCOTP_SW_GP1			(IMXRT_OCOTP_VALUE.offset280)
#define HW_OCOTP_SW_GP20		(IMXRT_OCOTP_VALUE.offset290)
#define HW_OCOTP_SW_GP21		(IMXRT_OCOTP_VALUE.offset2A0)
#define HW_OCOTP_SW_GP22		(IMXRT_OCOTP_VALUE.offset2B0)
#define HW_OCOTP_SW_GP23		(IMXRT_OCOTP_VALUE.offset2C0)
#define HW_OCOTP_MISC_CONF0		(IMXRT_OCOTP_VALUE.offset2D0)
#define HW_OCOTP_MISC_CONF1		(IMXRT_OCOTP_VALUE.offset2E0)
#define HW_OCOTP_SRK_REVOKE		(IMXRT_OCOTP_VALUE.offset2F0)

// page 2631
#define IMXRT_PIT		(*(IMXRT_REGISTER32_t *)0x40084000)
#define PIT_MCR				(IMXRT_PIT.offset000)
#define PIT_LTMR64H			(IMXRT_PIT.offset0E0)
#define PIT_LTMR64L			(IMXRT_PIT.offset0E4)
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

// page 2646
#define IMXRT_PMU		(*(IMXRT_REGISTER32_t *)0x400D8000)
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

// page 2728
#define IMXRT_PXP		(*(IMXRT_REGISTER32_t *)0x402B4000)
#define PXP_HW_PXP_CTRL
#define PXP_HW_PXP_CTRL_SET
#define PXP_HW_PXP_CTRL_CLR
#define PXP_HW_PXP_CTRL_TOG
#define PXP_HW_PXP_STAT
#define PXP_HW_PXP_STAT_SET
#define PXP_HW_PXP_STAT_CLR
#define PXP_HW_PXP_STAT_TOG
#define PXP_HW_PXP_OUT_CTRL
#define PXP_HW_PXP_OUT_CTRL_SET
#define PXP_HW_PXP_OUT_CTRL_CLR
#define PXP_HW_PXP_OUT_CTRL_TOG
#define PXP_HW_PXP_OUT_BUF
#define PXP_HW_PXP_OUT_BUF2
#define PXP_HW_PXP_OUT_PITCH
#define PXP_HW_PXP_OUT_LRC
#define PXP_HW_PXP_OUT_PS_ULC
#define PXP_HW_PXP_OUT_PS_LRC
#define PXP_HW_PXP_OUT_AS_ULC
#define PXP_HW_PXP_OUT_AS_LRC
#define PXP_HW_PXP_PS_CTRL
#define PXP_HW_PXP_PS_CTRL_SET
#define PXP_HW_PXP_PS_CTRL_CLR
#define PXP_HW_PXP_PS_CTRL_TOG
#define PXP_HW_PXP_PS_BUF
#define PXP_HW_PXP_PS_UBUF
#define PXP_HW_PXP_PS_VBUF
#define PXP_HW_PXP_PS_PITCH
#define PXP_HW_PXP_PS_BACKGROUND_0
#define PXP_HW_PXP_PS_SCALE
#define PXP_HW_PXP_PS_OFFSET
#define PXP_HW_PXP_PS_CLRKEYLOW_0
#define PXP_HW_PXP_PS_CLRKEYHIGH_0
#define PXP_HW_PXP_AS_CTRL
#define PXP_HW_PXP_AS_BUF
#define PXP_HW_PXP_AS_PITCH
#define PXP_HW_PXP_AS_CLRKEYLOW_0
#define PXP_HW_PXP_AS_CLRKEYHIGH_0
#define PXP_HW_PXP_CSC1_COEF0
#define PXP_HW_PXP_CSC1_COEF1
#define PXP_HW_PXP_CSC1_COEF2
#define PXP_HW_PXP_CSC2_CTRL
#define PXP_HW_PXP_CSC2_COEF0
#define PXP_HW_PXP_CSC2_COEF1
#define PXP_HW_PXP_CSC2_COEF2
#define PXP_HW_PXP_CSC2_COEF3
#define PXP_HW_PXP_CSC2_COEF4
#define PXP_HW_PXP_CSC2_COEF5
#define PXP_HW_PXP_LUT_CTRL
#define PXP_HW_PXP_LUT_ADDR
#define PXP_HW_PXP_LUT_DATA
#define PXP_HW_PXP_LUT_EXTMEM
#define PXP_HW_PXP_CFA
#define PXP_HW_PXP_ALPHA_A_CTRL
#define PXP_HW_PXP_PS_BACKGROUND_1
#define PXP_HW_PXP_PS_CLRKEYLOW_1
#define PXP_HW_PXP_PS_CLRKEYHIGH_1
#define PXP_HW_PXP_AS_CLRKEYLOW_1
#define PXP_HW_PXP_AS_CLRKEYHIGH_1
#define PXP_HW_PXP_CTRL2
#define PXP_HW_PXP_CTRL2_SET
#define PXP_HW_PXP_CTRL2_CLR
#define PXP_HW_PXP_CTRL2_TOG
#define PXP_HW_PXP_POWER_REG0
#define PXP_HW_PXP_POWER_REG1
#define PXP_HW_PXP_DATA_PATH_CTRL0
#define PXP_HW_PXP_DATA_PATH_CTRL0_SET
#define PXP_HW_PXP_DATA_PATH_CTRL0_CLR
#define PXP_HW_PXP_DATA_PATH_CTRL0_TOG
#define PXP_HW_PXP_DATA_PATH_CTRL1
#define PXP_HW_PXP_DATA_PATH_CTRL1_SET
#define PXP_HW_PXP_DATA_PATH_CTRL1_CLR
#define PXP_HW_PXP_DATA_PATH_CTRL1_TOG
#define PXP_HW_PXP_INIT_MEM_CTRL
#define PXP_HW_PXP_INIT_MEM_CTRL_SET

#define PXP_HW_PXP_INIT_MEM_CTRL_CLR
#define PXP_HW_PXP_INIT_MEM_CTRL_TOG
#define PXP_HW_PXP_INIT_MEM_DATA
#define PXP_HW_PXP_INIT_MEM_DATA_HIGH
#define PXP_HW_PXP_IRQ_MASK
#define PXP_HW_PXP_IRQ_MASK_SET
#define PXP_HW_PXP_IRQ_MASK_CLR
#define PXP_HW_PXP_IRQ_MASK_TOG
#define PXP_HW_PXP_IRQ
#define PXP_HW_PXP_IRQ_SET
#define PXP_HW_PXP_IRQ_CLR
#define PXP_HW_PXP_IRQ_TOG
#define PXP_HW_PXP_NEXT_EN
#define PXP_HW_PXP_NEXT_EN_SET
#define PXP_HW_PXP_NEXT_EN_CLR
#define PXP_HW_PXP_NEXT_EN_TOG
#define PXP_HW_PXP_NEXT
#define PXP_HW_PXP_DEBUGCTRL
#define PXP_HW_PXP_DEBUG
#define PXP_HW_PXP_VERSION
#define PXP_HW_PXP_DITHER_STORE_SIZE_CH0
#define PXP_HW_PXP_WFB_FETCH_CTRL

#define PXP_HW_PXP_WFB_FETCH_CTRL_SET
#define PXP_HW_PXP_WFB_FETCH_CTRL_CLR
#define PXP_HW_PXP_WFB_FETCH_CTRL_TOG
#define PXP_HW_PXP_WFB_FETCH_BUF1_ADDR
#define PXP_HW_PXP_WFB_FETCH_BUF1_PITCH
#define PXP_HW_PXP_WFB_FETCH_BUF1_SIZE
#define PXP_HW_PXP_WFB_FETCH_BUF2_ADDR
#define PXP_HW_PXP_WFB_FETCH_BUF2_PITCH
#define PXP_HW_PXP_WFB_FETCH_BUF2_SIZE
#define PXP_HW_PXP_WFB_ARRAY_PIXEL0_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL1_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL2_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL3_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL4_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL5_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL6_MASK
#define PXP_HW_PXP_WFB_ARRAY_PIXEL7_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG0_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG1_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG2_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG3_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG4_MASK

#define PXP_HW_PXP_WFB_ARRAY_FLAG5_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG6_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG7_MASK
#define PXP_HW_PXP_WFB_FETCH_BUF1_CORD
#define PXP_HW_PXP_WFB_FETCH_BUF2_CORD
#define PXP_HW_PXP_WFB_ARRAY_FLAG8_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG9_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG10_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG11_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG12_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG13_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG14_MASK
#define PXP_HW_PXP_WFB_ARRAY_FLAG15_MASK
#define PXP_HW_PXP_WFB_ARRAY_REG0
#define PXP_HW_PXP_WFB_ARRAY_REG1
#define PXP_HW_PXP_WFB_ARRAY_REG2
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH0
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH0_SET
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH0_CLR
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH0_TOG
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH1
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH1_SET

#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH1_CLR
#define PXP_HW_PXP_WFE_B_STORE_CTRL_CH1_TOG
#define PXP_HW_PXP_WFE_B_STORE_STATUS_CH0
#define PXP_HW_PXP_WFE_B_STORE_STATUS_CH1
#define PXP_HW_PXP_WFE_B_STORE_SIZE_CH0
#define PXP_HW_PXP_WFE_B_STORE_SIZE_CH1
#define PXP_HW_PXP_WFE_B_STORE_PITCH
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH0
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH0_SET
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH0_CLR
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH0_TOG
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH1
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH1_SET
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH1_CLR
#define PXP_HW_PXP_WFE_B_STORE_SHIFT_CTRL_CH1_TOG
#define PXP_HW_PXP_WFE_B_STORE_ADDR_0_CH0
#define PXP_HW_PXP_WFE_B_STORE_ADDR_1_CH0
#define PXP_HW_PXP_WFE_B_STORE_FILL_DATA_CH0
#define PXP_HW_PXP_WFE_B_STORE_ADDR_0_CH1
#define PXP_HW_PXP_WFE_B_STORE_ADDR_1_CH1
#define PXP_HW_PXP_WFE_B_STORE_D_MASK0_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK0_L_CH0

#define PXP_HW_PXP_WFE_B_STORE_D_MASK1_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK1_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK2_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK2_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK3_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK3_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK4_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK4_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK5_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK5_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK6_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK6_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK7_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_MASK7_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_SHIFT_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_D_SHIFT_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_F_SHIFT_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_F_SHIFT_H_CH0
#define PXP_HW_PXP_WFE_B_STORE_F_MASK_L_CH0
#define PXP_HW_PXP_WFE_B_STORE_F_MASK_H_CH0
#define PXP_HW_PXP_FETCH_WFE_B_DEBUG
#define PXP_HW_PXP_DITHER_CTRL

#define PXP_HW_PXP_DITHER_CTRL_SET
#define PXP_HW_PXP_DITHER_CTRL_CLR
#define PXP_HW_PXP_DITHER_CTRL_TOG
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA0
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA0_SET
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA0_CLR
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA0_TOG
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA1
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA1_SET
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA1_CLR
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA1_TOG
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA2
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA2_SET
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA2_CLR
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA2_TOG
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA3
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA3_SET
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA3_CLR
#define PXP_HW_PXP_DITHER_FINAL_LUT_DATA3_TOG
#define PXP_HW_PXP_WFE_B_CTRL
#define PXP_HW_PXP_WFE_B_CTRL_SET
#define PXP_HW_PXP_WFE_B_CTRL_CLR

#define PXP_HW_PXP_WFE_B_CTRL_TOG
#define PXP_HW_PXP_WFE_B_DIMENSIONS
#define PXP_HW_PXP_WFE_B_OFFSET
#define PXP_HW_PXP_WFE_B_SW_DATA_REGS
#define PXP_HW_PXP_WFE_B_SW_FLAG_REGS
#define PXP_HW_PXP_WFE_B_STAGE1_MUX0
#define PXP_HW_PXP_WFE_B_STAGE1_MUX0_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX0_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX0_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX1
#define PXP_HW_PXP_WFE_B_STAGE1_MUX1_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX1_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX1_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX2
#define PXP_HW_PXP_WFE_B_STAGE1_MUX2_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX2_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX2_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX3
#define PXP_HW_PXP_WFE_B_STAGE1_MUX3_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX3_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX3_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX4

#define PXP_HW_PXP_WFE_B_STAGE1_MUX4_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX4_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX4_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX5
#define PXP_HW_PXP_WFE_B_STAGE1_MUX5_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX5_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX5_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX6
#define PXP_HW_PXP_WFE_B_STAGE1_MUX6_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX6_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX6_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX7
#define PXP_HW_PXP_WFE_B_STAGE1_MUX7_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX7_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX7_TOG
#define PXP_HW_PXP_WFE_B_STAGE1_MUX8
#define PXP_HW_PXP_WFE_B_STAGE1_MUX8_SET
#define PXP_HW_PXP_WFE_B_STAGE1_MUX8_CLR
#define PXP_HW_PXP_WFE_B_STAGE1_MUX8_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX0
#define PXP_HW_PXP_WFE_B_STAGE2_MUX0_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX0_CLR

#define PXP_HW_PXP_WFE_B_STAGE2_MUX0_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX1
#define PXP_HW_PXP_WFE_B_STAGE2_MUX1_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX1_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX1_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX2
#define PXP_HW_PXP_WFE_B_STAGE2_MUX2_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX2_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX2_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX3
#define PXP_HW_PXP_WFE_B_STAGE2_MUX3_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX3_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX3_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX4
#define PXP_HW_PXP_WFE_B_STAGE2_MUX4_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX4_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX4_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX5
#define PXP_HW_PXP_WFE_B_STAGE2_MUX5_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX5_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX5_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX6

#define PXP_HW_PXP_WFE_B_STAGE2_MUX6_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX6_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX6_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX7
#define PXP_HW_PXP_WFE_B_STAGE2_MUX7_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX7_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX7_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX8
#define PXP_HW_PXP_WFE_B_STAGE2_MUX8_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX8_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX8_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX9
#define PXP_HW_PXP_WFE_B_STAGE2_MUX9_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX9_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX9_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX10
#define PXP_HW_PXP_WFE_B_STAGE2_MUX10_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX10_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX10_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX11
#define PXP_HW_PXP_WFE_B_STAGE2_MUX11_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX11_CLR

#define PXP_HW_PXP_WFE_B_STAGE2_MUX11_TOG
#define PXP_HW_PXP_WFE_B_STAGE2_MUX12
#define PXP_HW_PXP_WFE_B_STAGE2_MUX12_SET
#define PXP_HW_PXP_WFE_B_STAGE2_MUX12_CLR
#define PXP_HW_PXP_WFE_B_STAGE2_MUX12_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX0
#define PXP_HW_PXP_WFE_B_STAGE3_MUX0_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX0_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX0_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX1
#define PXP_HW_PXP_WFE_B_STAGE3_MUX1_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX1_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX1_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX2
#define PXP_HW_PXP_WFE_B_STAGE3_MUX2_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX2_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX2_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX3
#define PXP_HW_PXP_WFE_B_STAGE3_MUX3_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX3_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX3_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX4

#define PXP_HW_PXP_WFE_B_STAGE3_MUX4_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX4_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX4_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX5
#define PXP_HW_PXP_WFE_B_STAGE3_MUX5_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX5_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX5_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX6
#define PXP_HW_PXP_WFE_B_STAGE3_MUX6_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX6_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX6_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX7
#define PXP_HW_PXP_WFE_B_STAGE3_MUX7_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX7_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX7_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX8
#define PXP_HW_PXP_WFE_B_STAGE3_MUX8_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX8_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX8_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX9
#define PXP_HW_PXP_WFE_B_STAGE3_MUX9_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX9_CLR

#define PXP_HW_PXP_WFE_B_STAGE3_MUX9_TOG
#define PXP_HW_PXP_WFE_B_STAGE3_MUX10
#define PXP_HW_PXP_WFE_B_STAGE3_MUX10_SET
#define PXP_HW_PXP_WFE_B_STAGE3_MUX10_CLR
#define PXP_HW_PXP_WFE_B_STAGE3_MUX10_TOG
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_0
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_1
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_2
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_3
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_4
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_5
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_6
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT0_7
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_0
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_1
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_2
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_3
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_4
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_5
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_6
#define PXP_HW_PXP_WFE_B_STG1_5X8_OUT1_7
#define PXP_HW_PXP_WFE_B_STAGE1_5X8_MASKS_0

#define PXP_HW_PXP_WFE_B_STG1_5X1_OUT0
#define PXP_HW_PXP_WFE_B_STG1_5X1_MASKS
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_0
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_1
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_2
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_3
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_4
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_5
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_6
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT0_7
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_0
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_1
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_2
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_3
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_4
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_5
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_6
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT1_7
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_0
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_1
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_2
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_3

#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_4
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_5
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_6
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT2_7
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_0
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_1
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_2
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_3
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_4
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_5
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_6
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT3_7
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_0
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_1
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_2
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_3
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_4
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_5
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_6
#define PXP_HW_PXP_WFE_B_STG1_8X1_OUT4_7
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_0
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_1

#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_2
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_3
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_4
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_5
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_6
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT0_7
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_0
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_1
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_2
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_3
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_4
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_5
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_6
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT1_7
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_0
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_1
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_2
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_3
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_4
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_5
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_6
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT2_7

#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_0
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_1
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_2
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_3
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_4
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_5
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_6
#define PXP_HW_PXP_WFE_B_STG2_5X6_OUT3_7
#define PXP_HW_PXP_WFE_B_STAGE2_5X6_MASKS_0
#define PXP_HW_PXP_WFE_B_STAGE2_5X6_ADDR_0
#define PXP_HW_PXP_WFE_B_STG2_5X1_OUT0
#define PXP_HW_PXP_WFE_B_STG2_5X1_OUT1
#define PXP_HW_PXP_WFE_B_STG2_5X1_OUT2
#define PXP_HW_PXP_WFE_B_STG2_5X1_OUT3
#define PXP_HW_PXP_WFE_B_STG2_5X1_MASKS
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_0
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_1
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_2
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_3
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_4
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_5
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_6

#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT0_7
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_0
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_1
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_2
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_3
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_4
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_5
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_6
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT1_7
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_0
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_1
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_2
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_3
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_4
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_5
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_6
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT2_7
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_0
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_1
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_2
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_3
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_4

#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_5
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_6
#define PXP_HW_PXP_WFE_B_STG3_F8X1_OUT3_7
#define PXP_HW_PXP_WFE_B_STG3_F8X1_MASKS
#define PXP_HW_PXP_ALU_B_CTRL
#define PXP_HW_PXP_ALU_B_CTRL_SET
#define PXP_HW_PXP_ALU_B_CTRL_CLR
#define PXP_HW_PXP_ALU_B_CTRL_TOG
#define PXP_HW_PXP_ALU_B_BUF_SIZE
#define PXP_HW_PXP_ALU_B_INST_ENTRY
#define PXP_HW_PXP_ALU_B_PARAM
#define PXP_HW_PXP_ALU_B_CONFIG
#define PXP_HW_PXP_ALU_B_LUT_CONFIG
#define PXP_HW_PXP_ALU_B_LUT_CONFIG_SET
#define PXP_HW_PXP_ALU_B_LUT_CONFIG_CLR
#define PXP_HW_PXP_ALU_B_LUT_CONFIG_TOG
#define PXP_HW_PXP_ALU_B_LUT_DATA0
#define PXP_HW_PXP_ALU_B_LUT_DATA1
#define PXP_HW_PXP_ALU_B_DBG
#define PXP_HW_PXP_HIST_A_CTRL
#define PXP_HW_PXP_HIST_A_MASK
#define PXP_HW_PXP_HIST_A_BUF_SIZE

#define PXP_HW_PXP_HIST_A_TOTAL_PIXEL
#define PXP_HW_PXP_HIST_A_ACTIVE_AREA_X
#define PXP_HW_PXP_HIST_A_ACTIVE_AREA_Y
#define PXP_HW_PXP_HIST_A_RAW_STAT0
#define PXP_HW_PXP_HIST_A_RAW_STAT1
#define PXP_HW_PXP_HIST_B_CTRL
#define PXP_HW_PXP_HIST_B_MASK
#define PXP_HW_PXP_HIST_B_BUF_SIZE
#define PXP_HW_PXP_HIST_B_TOTAL_PIXEL
#define PXP_HW_PXP_HIST_B_ACTIVE_AREA_X
#define PXP_HW_PXP_HIST_B_ACTIVE_AREA_Y
#define PXP_HW_PXP_HIST_B_RAW_STAT0
#define PXP_HW_PXP_HIST_B_RAW_STAT1
#define PXP_HW_PXP_HIST2_PARAM
#define PXP_HW_PXP_HIST4_PARAM
#define PXP_HW_PXP_HIST8_PARAM0
#define PXP_HW_PXP_HIST8_PARAM1
#define PXP_HW_PXP_HIST16_PARAM0
#define PXP_HW_PXP_HIST16_PARAM1
#define PXP_HW_PXP_HIST16_PARAM2
#define PXP_HW_PXP_HIST16_PARAM3
#define PXP_HW_PXP_HIST32_PARAM0

#define PXP_HW_PXP_HIST32_PARAM1
#define PXP_HW_PXP_HIST32_PARAM2
#define PXP_HW_PXP_HIST32_PARAM3
#define PXP_HW_PXP_HIST32_PARAM4
#define PXP_HW_PXP_HIST32_PARAM5
#define PXP_HW_PXP_HIST32_PARAM6
#define PXP_HW_PXP_HIST32_PARAM7
#define PXP_HW_PXP_HANDSHAKE_READY_MUX0
#define PXP_HW_PXP_HANDSHAKE_DONE_MUX0


// page 3147
#define IMXRT_TMR1		(*(IMXRT_REGISTER16_t *)0x401DC000)
#define TMR1_COMP10			(IMXRT_TMR1.offset000)
#define TMR1_COMP20			(IMXRT_TMR1.offset002)
#define TMR1_CAPT0			(IMXRT_TMR1.offset004)
#define TMR1_LOAD0			(IMXRT_TMR1.offset006)
#define TMR1_HOLD0			(IMXRT_TMR1.offset008)
#define TMR1_CNTR0			(IMXRT_TMR1.offset00A)
#define TMR1_CTRL0			(IMXRT_TMR1.offset00C)
#define TMR1_SCTRL0			(IMXRT_TMR1.offset00E)
#define TMR1_CMPLD10			(IMXRT_TMR1.offset010)
#define TMR1_CMPLD20			(IMXRT_TMR1.offset012)
#define TMR1_CSCTRL0			(IMXRT_TMR1.offset014)
#define TMR1_FILT0			(IMXRT_TMR1.offset016)
#define TMR1_DMA0			(IMXRT_TMR1.offset018)
#define TMR1_ENBL			(IMXRT_TMR1.offset01E)
#define TMR1_COMP11			(IMXRT_TMR1.offset020)
#define TMR1_COMP21			(IMXRT_TMR1.offset022)
#define TMR1_CAPT1			(IMXRT_TMR1.offset024)
#define TMR1_LOAD1			(IMXRT_TMR1.offset026)
#define TMR1_HOLD1			(IMXRT_TMR1.offset028)
#define TMR1_CNTR1			(IMXRT_TMR1.offset02A)
#define TMR1_CTRL1			(IMXRT_TMR1.offset02C)
#define TMR1_SCTRL1			(IMXRT_TMR1.offset02E)
#define TMR1_CMPLD11			(IMXRT_TMR1.offset030)
#define TMR1_CMPLD21			(IMXRT_TMR1.offset032)
#define TMR1_CSCTRL1			(IMXRT_TMR1.offset034)
#define TMR1_FILT1			(IMXRT_TMR1.offset036)
#define TMR1_DMA1			(IMXRT_TMR1.offset038)
#define TMR1_COMP12			(IMXRT_TMR1.offset040)
#define TMR1_COMP22			(IMXRT_TMR1.offset042)
#define TMR1_CAPT2			(IMXRT_TMR1.offset044)
#define TMR1_LOAD2			(IMXRT_TMR1.offset046)
#define TMR1_HOLD2			(IMXRT_TMR1.offset048)
#define TMR1_CNTR2			(IMXRT_TMR1.offset04A)
#define TMR1_CTRL2			(IMXRT_TMR1.offset04C)
#define TMR1_SCTRL2			(IMXRT_TMR1.offset04E)
#define TMR1_CMPLD12			(IMXRT_TMR1.offset050)
#define TMR1_CMPLD22			(IMXRT_TMR1.offset052)
#define TMR1_CSCTRL2			(IMXRT_TMR1.offset054)
#define TMR1_FILT2			(IMXRT_TMR1.offset056)
#define TMR1_DMA2			(IMXRT_TMR1.offset058)
#define TMR1_COMP13			(IMXRT_TMR1.offset060)
#define TMR1_COMP23			(IMXRT_TMR1.offset062)
#define TMR1_CAPT3			(IMXRT_TMR1.offset064)
#define TMR1_LOAD3			(IMXRT_TMR1.offset066)
#define TMR1_HOLD3			(IMXRT_TMR1.offset068)
#define TMR1_CNTR3			(IMXRT_TMR1.offset06A)
#define TMR1_CTRL3			(IMXRT_TMR1.offset06C)
#define TMR1_SCTRL3			(IMXRT_TMR1.offset06E)
#define TMR1_CMPLD13			(IMXRT_TMR1.offset070)
#define TMR1_CMPLD23			(IMXRT_TMR1.offset072)
#define TMR1_CSCTRL3			(IMXRT_TMR1.offset074)
#define TMR1_FILT3			(IMXRT_TMR1.offset076)
#define TMR1_DMA3			(IMXRT_TMR1.offset078)
#define IMXRT_TMR2		(*(IMXRT_REGISTER16_t *)0x401E0000)
#define TMR2_COMP10			(IMXRT_TMR2.offset000)
#define TMR2_COMP20			(IMXRT_TMR2.offset002)
#define TMR2_CAPT0			(IMXRT_TMR2.offset004)
#define TMR2_LOAD0			(IMXRT_TMR2.offset006)
#define TMR2_HOLD0			(IMXRT_TMR2.offset008)
#define TMR2_CNTR0			(IMXRT_TMR2.offset00A)
#define TMR2_CTRL0			(IMXRT_TMR2.offset00C)
#define TMR2_SCTRL0			(IMXRT_TMR2.offset00E)
#define TMR2_CMPLD10			(IMXRT_TMR2.offset010)
#define TMR2_CMPLD20			(IMXRT_TMR2.offset012)
#define TMR2_CSCTRL0			(IMXRT_TMR2.offset014)
#define TMR2_FILT0			(IMXRT_TMR2.offset016)
#define TMR2_DMA0			(IMXRT_TMR2.offset018)
#define TMR2_ENBL			(IMXRT_TMR2.offset01E)
#define TMR2_COMP11			(IMXRT_TMR2.offset020)
#define TMR2_COMP21			(IMXRT_TMR2.offset022)
#define TMR2_CAPT1			(IMXRT_TMR2.offset024)
#define TMR2_LOAD1			(IMXRT_TMR2.offset026)
#define TMR2_HOLD1			(IMXRT_TMR2.offset028)
#define TMR2_CNTR1			(IMXRT_TMR2.offset02A)
#define TMR2_CTRL1			(IMXRT_TMR2.offset02C)
#define TMR2_SCTRL1			(IMXRT_TMR2.offset02E)
#define TMR2_CMPLD11			(IMXRT_TMR2.offset030)
#define TMR2_CMPLD21			(IMXRT_TMR2.offset032)
#define TMR2_CSCTRL1			(IMXRT_TMR2.offset034)
#define TMR2_FILT1			(IMXRT_TMR2.offset036)
#define TMR2_DMA1			(IMXRT_TMR2.offset038)
#define TMR2_COMP12			(IMXRT_TMR2.offset040)
#define TMR2_COMP22			(IMXRT_TMR2.offset042)
#define TMR2_CAPT2			(IMXRT_TMR2.offset044)
#define TMR2_LOAD2			(IMXRT_TMR2.offset046)
#define TMR2_HOLD2			(IMXRT_TMR2.offset048)
#define TMR2_CNTR2			(IMXRT_TMR2.offset04A)
#define TMR2_CTRL2			(IMXRT_TMR2.offset04C)
#define TMR2_SCTRL2			(IMXRT_TMR2.offset04E)
#define TMR2_CMPLD12			(IMXRT_TMR2.offset050)
#define TMR2_CMPLD22			(IMXRT_TMR2.offset052)
#define TMR2_CSCTRL2			(IMXRT_TMR2.offset054)
#define TMR2_FILT2			(IMXRT_TMR2.offset056)
#define TMR2_DMA2			(IMXRT_TMR2.offset058)
#define TMR2_COMP13			(IMXRT_TMR2.offset060)
#define TMR2_COMP23			(IMXRT_TMR2.offset062)
#define TMR2_CAPT3			(IMXRT_TMR2.offset064)
#define TMR2_LOAD3			(IMXRT_TMR2.offset066)
#define TMR2_HOLD3			(IMXRT_TMR2.offset068)
#define TMR2_CNTR3			(IMXRT_TMR2.offset06A)
#define TMR2_CTRL3			(IMXRT_TMR2.offset06C)
#define TMR2_SCTRL3			(IMXRT_TMR2.offset06E)
#define TMR2_CMPLD13			(IMXRT_TMR2.offset070)
#define TMR2_CMPLD23			(IMXRT_TMR2.offset072)
#define TMR2_CSCTRL3			(IMXRT_TMR2.offset074)
#define TMR2_FILT3			(IMXRT_TMR2.offset076)
#define TMR2_DMA3			(IMXRT_TMR2.offset078)
#define IMXRT_TMR3		(*(IMXRT_REGISTER16_t *)0x401E4000)
#define TMR3_COMP10			(IMXRT_TMR3.offset000)
#define TMR3_COMP20			(IMXRT_TMR3.offset002)
#define TMR3_CAPT0			(IMXRT_TMR3.offset004)
#define TMR3_LOAD0			(IMXRT_TMR3.offset006)
#define TMR3_HOLD0			(IMXRT_TMR3.offset008)
#define TMR3_CNTR0			(IMXRT_TMR3.offset00A)
#define TMR3_CTRL0			(IMXRT_TMR3.offset00C)
#define TMR3_SCTRL0			(IMXRT_TMR3.offset00E)
#define TMR3_CMPLD10			(IMXRT_TMR3.offset010)
#define TMR3_CMPLD20			(IMXRT_TMR3.offset012)
#define TMR3_CSCTRL0			(IMXRT_TMR3.offset014)
#define TMR3_FILT0			(IMXRT_TMR3.offset016)
#define TMR3_DMA0			(IMXRT_TMR3.offset018)
#define TMR3_ENBL			(IMXRT_TMR3.offset01E)
#define TMR3_COMP11			(IMXRT_TMR3.offset020)
#define TMR3_COMP21			(IMXRT_TMR3.offset022)
#define TMR3_CAPT1			(IMXRT_TMR3.offset024)
#define TMR3_LOAD1			(IMXRT_TMR3.offset026)
#define TMR3_HOLD1			(IMXRT_TMR3.offset028)
#define TMR3_CNTR1			(IMXRT_TMR3.offset02A)
#define TMR3_CTRL1			(IMXRT_TMR3.offset02C)
#define TMR3_SCTRL1			(IMXRT_TMR3.offset02E)
#define TMR3_CMPLD11			(IMXRT_TMR3.offset030)
#define TMR3_CMPLD21			(IMXRT_TMR3.offset032)
#define TMR3_CSCTRL1			(IMXRT_TMR3.offset034)
#define TMR3_FILT1			(IMXRT_TMR3.offset036)
#define TMR3_DMA1			(IMXRT_TMR3.offset038)
#define TMR3_COMP12			(IMXRT_TMR3.offset040)
#define TMR3_COMP22			(IMXRT_TMR3.offset042)
#define TMR3_CAPT2			(IMXRT_TMR3.offset044)
#define TMR3_LOAD2			(IMXRT_TMR3.offset046)
#define TMR3_HOLD2			(IMXRT_TMR3.offset048)
#define TMR3_CNTR2			(IMXRT_TMR3.offset04A)
#define TMR3_CTRL2			(IMXRT_TMR3.offset04C)
#define TMR3_SCTRL2			(IMXRT_TMR3.offset04E)
#define TMR3_CMPLD12			(IMXRT_TMR3.offset050)
#define TMR3_CMPLD22			(IMXRT_TMR3.offset052)
#define TMR3_CSCTRL2			(IMXRT_TMR3.offset054)
#define TMR3_FILT2			(IMXRT_TMR3.offset056)
#define TMR3_DMA2			(IMXRT_TMR3.offset058)
#define TMR3_COMP13			(IMXRT_TMR3.offset060)
#define TMR3_COMP23			(IMXRT_TMR3.offset062)
#define TMR3_CAPT3			(IMXRT_TMR3.offset064)
#define TMR3_LOAD3			(IMXRT_TMR3.offset066)
#define TMR3_HOLD3			(IMXRT_TMR3.offset068)
#define TMR3_CNTR3			(IMXRT_TMR3.offset06A)
#define TMR3_CTRL3			(IMXRT_TMR3.offset06C)
#define TMR3_SCTRL3			(IMXRT_TMR3.offset06E)
#define TMR3_CMPLD13			(IMXRT_TMR3.offset070)
#define TMR3_CMPLD23			(IMXRT_TMR3.offset072)
#define TMR3_CSCTRL3			(IMXRT_TMR3.offset074)
#define TMR3_FILT3			(IMXRT_TMR3.offset076)
#define TMR3_DMA3			(IMXRT_TMR3.offset078)
#define IMXRT_TMR4		(*(IMXRT_REGISTER16_t *)0x401E8000)
#define TMR4_COMP10			(IMXRT_TMR4.offset000)
#define TMR4_COMP20			(IMXRT_TMR4.offset002)
#define TMR4_CAPT0			(IMXRT_TMR4.offset004)
#define TMR4_LOAD0			(IMXRT_TMR4.offset006)
#define TMR4_HOLD0			(IMXRT_TMR4.offset008)
#define TMR4_CNTR0			(IMXRT_TMR4.offset00A)
#define TMR4_CTRL0			(IMXRT_TMR4.offset00C)
#define TMR4_SCTRL0			(IMXRT_TMR4.offset00E)
#define TMR4_CMPLD10			(IMXRT_TMR4.offset010)
#define TMR4_CMPLD20			(IMXRT_TMR4.offset012)
#define TMR4_CSCTRL0			(IMXRT_TMR4.offset014)
#define TMR4_FILT0			(IMXRT_TMR4.offset016)
#define TMR4_DMA0			(IMXRT_TMR4.offset018)
#define TMR4_ENBL			(IMXRT_TMR4.offset01E)
#define TMR4_COMP11			(IMXRT_TMR4.offset020)
#define TMR4_COMP21			(IMXRT_TMR4.offset022)
#define TMR4_CAPT1			(IMXRT_TMR4.offset024)
#define TMR4_LOAD1			(IMXRT_TMR4.offset026)
#define TMR4_HOLD1			(IMXRT_TMR4.offset028)
#define TMR4_CNTR1			(IMXRT_TMR4.offset02A)
#define TMR4_CTRL1			(IMXRT_TMR4.offset02C)
#define TMR4_SCTRL1			(IMXRT_TMR4.offset02E)
#define TMR4_CMPLD11			(IMXRT_TMR4.offset030)
#define TMR4_CMPLD21			(IMXRT_TMR4.offset032)
#define TMR4_CSCTRL1			(IMXRT_TMR4.offset034)
#define TMR4_FILT1			(IMXRT_TMR4.offset036)
#define TMR4_DMA1			(IMXRT_TMR4.offset038)
#define TMR4_COMP12			(IMXRT_TMR4.offset040)
#define TMR4_COMP22			(IMXRT_TMR4.offset042)
#define TMR4_CAPT2			(IMXRT_TMR4.offset044)
#define TMR4_LOAD2			(IMXRT_TMR4.offset046)
#define TMR4_HOLD2			(IMXRT_TMR4.offset048)
#define TMR4_CNTR2			(IMXRT_TMR4.offset04A)
#define TMR4_CTRL2			(IMXRT_TMR4.offset04C)
#define TMR4_SCTRL2			(IMXRT_TMR4.offset04E)
#define TMR4_CMPLD12			(IMXRT_TMR4.offset050)
#define TMR4_CMPLD22			(IMXRT_TMR4.offset052)
#define TMR4_CSCTRL2			(IMXRT_TMR4.offset054)
#define TMR4_FILT2			(IMXRT_TMR4.offset056)
#define TMR4_DMA2			(IMXRT_TMR4.offset058)
#define TMR4_COMP13			(IMXRT_TMR4.offset060)
#define TMR4_COMP23			(IMXRT_TMR4.offset062)
#define TMR4_CAPT3			(IMXRT_TMR4.offset064)
#define TMR4_LOAD3			(IMXRT_TMR4.offset066)
#define TMR4_HOLD3			(IMXRT_TMR4.offset068)
#define TMR4_CNTR3			(IMXRT_TMR4.offset06A)
#define TMR4_CTRL3			(IMXRT_TMR4.offset06C)
#define TMR4_SCTRL3			(IMXRT_TMR4.offset06E)
#define TMR4_CMPLD13			(IMXRT_TMR4.offset070)
#define TMR4_CMPLD23			(IMXRT_TMR4.offset072)
#define TMR4_CSCTRL3			(IMXRT_TMR4.offset074)
#define TMR4_FILT3			(IMXRT_TMR4.offset076)
#define TMR4_DMA3			(IMXRT_TMR4.offset078)

#define IMXRT_ROMC		(*(IMXRT_REGISTER32_t *)0x40180000)
#define ROMC_ROMPATCH7D			(IMXRT_ROMC.offset0D4)
#define ROMC_ROMPATCH6D			(IMXRT_ROMC.offset0D8)
#define ROMC_ROMPATCH5D			(IMXRT_ROMC.offset0DC)
#define ROMC_ROMPATCH4D			(IMXRT_ROMC.offset0E0)
#define ROMC_ROMPATCH3D			(IMXRT_ROMC.offset0E4)
#define ROMC_ROMPATCH2D			(IMXRT_ROMC.offset0E8)
#define ROMC_ROMPATCH1D			(IMXRT_ROMC.offset0EC)
#define ROMC_ROMPATCH0D			(IMXRT_ROMC.offset0F0)
#define ROMC_ROMPATCHCNTL		(IMXRT_ROMC.offset0F4)
#define ROMC_ROMPATCHENH		(IMXRT_ROMC.offset0F8)
#define ROMC_ROMPATCHENL		(IMXRT_ROMC.offset0FC)
#define ROMC_ROMPATCH0A			(IMXRT_ROMC.offset100)
#define ROMC_ROMPATCH1A			(IMXRT_ROMC.offset104)
#define ROMC_ROMPATCH2A			(IMXRT_ROMC.offset108)
#define ROMC_ROMPATCH3A			(IMXRT_ROMC.offset10C)
#define ROMC_ROMPATCH4A			(IMXRT_ROMC.offset110)
#define ROMC_ROMPATCH5A			(IMXRT_ROMC.offset114)
#define ROMC_ROMPATCH6A			(IMXRT_ROMC.offset118)
#define ROMC_ROMPATCH7A			(IMXRT_ROMC.offset11C)
#define ROMC_ROMPATCH8A			(IMXRT_ROMC.offset120)
#define ROMC_ROMPATCH9A			(IMXRT_ROMC.offset124)
#define ROMC_ROMPATCH10A		(IMXRT_ROMC.offset128)
#define ROMC_ROMPATCH11A		(IMXRT_ROMC.offset12C)
#define ROMC_ROMPATCH12A		(IMXRT_ROMC.offset130)
#define ROMC_ROMPATCH13A		(IMXRT_ROMC.offset134)
#define ROMC_ROMPATCH14A		(IMXRT_ROMC.offset138)
#define ROMC_ROMPATCH15A		(IMXRT_ROMC.offset13C)
#define ROMC_ROMPATCHSR			(IMXRT_ROMC.offset208)


// page 3216
#define IMXRT_I2S1		(*(IMXRT_REGISTER32_t *)0x40384000)
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
#define IMXRT_I2S2		(*(IMXRT_REGISTER32_t *)0x40388000)
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
#define IMXRT_I2S3		(*(IMXRT_REGISTER32_t *)0x4038C000)
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

// page 3290
#define IMXRT_SEMC		(*(IMXRT_REGISTER32_t *)0x402F0000)
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

// page 3398
#define IMXRT_SNVS		(*(IMXRT_REGISTER32_t *)0x400D4000)
#define SNVS_HPLR			(IMXRT_SNVS.offset000)
#define SNVS_HPCOMR			(IMXRT_SNVS.offset004)
#define SNVS_HPCR			(IMXRT_SNVS.offset008)
#define SNVS_HPSR			(IMXRT_SNVS.offset014)
#define SNVS_HPRTCMR			(IMXRT_SNVS.offset024)
#define SNVS_HPRTCLR			(IMXRT_SNVS.offset028)
#define SNVS_HPTAMR			(IMXRT_SNVS.offset02C)
#define SNVS_HPTALR			(IMXRT_SNVS.offset030)
#define SNVS_LPLR			(IMXRT_SNVS.offset034)
#define SNVS_LPCR			(IMXRT_SNVS.offset038)
#define SNVS_LPSR			(IMXRT_SNVS.offset04C)
#define SNVS_LPSMCMR			(IMXRT_SNVS.offset05C)
#define SNVS_LPSMCLR			(IMXRT_SNVS.offset060)
#define SNVS_LPGPR			(IMXRT_SNVS.offset068)
#define IMXRT_SNVS_b		(*(IMXRT_REGISTER32_t *)0x400D4800)
#define SNVS_HPVIDR1			(IMXRT_SNVS_b.offset3F8)
#define SNVS_HPVIDR2			(IMXRT_SNVS_b.offset3FC)

// page 3500
#define IMXRT_SPDIF		(*(IMXRT_REGISTER32_t *)0x400D4000)
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

// page 3521
#define IMXRT_SRC		(*(IMXRT_REGISTER32_t *)0x400F8000)
#define SRC_SCR				(IMXRT_SRC.offset000)
#define SRC_SBMR1			(IMXRT_SRC.offset004)
#define SRC_SRSR			(IMXRT_SRC.offset008)
#define SRC_SISR			(IMXRT_SRC.offset014)
#define SRC_SBMR2			(IMXRT_SRC.offset01C)
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

// page 3554
#define IMXRT_TSC		(*(IMXRT_REGISTER32_t *)0x400E0000)
#define TSC_BASIC_SETTING		(IMXRT_TSC.offset000)
#define TSC_PS_INPUT_BUFFER_ADDR	(IMXRT_TSC.offset010)
#define TSC_FLOW_CONTROL		(IMXRT_TSC.offset020)
#define TSC_MEASEURE_VALUE		(IMXRT_TSC.offset030)
#define TSC_INT_EN			(IMXRT_TSC.offset040)
#define TSC_INT_SIG_EN			(IMXRT_TSC.offset050)
#define TSC_INT_STATUS			(IMXRT_TSC.offset060)
#define TSC_DEBUG_MODE			(IMXRT_TSC.offset070)
#define TSC_DEBUG_MODE2			(IMXRT_TSC.offset080)

// page 3575
#define IMXRT_USB1		(*(IMXRT_REGISTER32_t *)0x402E0000)
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
#define IMXRT_USB2		(*(IMXRT_REGISTER32_t *)0x402DC000)
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

// page 3835
#define IMXRT_USBPHY1		(*(IMXRT_REGISTER32_t *)0x400D9000)
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
#define IMXRT_USBPHY2		(*(IMXRT_REGISTER32_t *)0x400DA000)
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

// page 3926
#define IMXRT_USDHC1		(*(IMXRT_REGISTER32_t *)0x402C0000)
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
#define IMXRT_USDHC2		(*(IMXRT_REGISTER32_t *)0x402C4000)
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

// page 4009
#define IMXRT_WDOG1		(*(IMXRT_REGISTER16_t *)0x400B8000)
#define WDOG1_WCR			(IMXRT_WDOG1.offset000)
#define WDOG1_WSR			(IMXRT_WDOG1.offset002)
#define WDOG1_WRSR			(IMXRT_WDOG1.offset004)
#define WDOG1_WICR			(IMXRT_WDOG1.offset006)
#define WDOG1_WMCR			(IMXRT_WDOG1.offset008)
#define IMXRT_WDOG2		(*(IMXRT_REGISTER16_t *)0x400D0000)
#define WDOG2_WCR			(IMXRT_WDOG2.offset000)
#define WDOG2_WSR			(IMXRT_WDOG2.offset002)
#define WDOG2_WRSR			(IMXRT_WDOG2.offset004)
#define WDOG2_WICR			(IMXRT_WDOG2.offset006)
#define WDOG2_WMCR			(IMXRT_WDOG2.offset008)

// page 4017
#define IMXRT_WDOG3		(*(IMXRT_REGISTER32_t *)0x400BC000)
#define WDOG3_CS			(IMXRT_WDOG3.offset000)
#define WDOG3_CNT			(IMXRT_WDOG3.offset004)
#define WDOG3_TOVAL			(IMXRT_WDOG3.offset008)
#define WDOG3_WIN			(IMXRT_WDOG3.offset00C)

// page 4036
#define IMXRT_XBARA1		(*(IMXRT_REGISTER16_t *)0x403BC000)
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
#define XBARA1_CTRL0			(IMXRT_XBARA1.offset03C)
#define XBARA1_CTRL1			(IMXRT_XBARA1.offset03E)

// page 4059
#define IMXRT_XBARB2		(*(IMXRT_REGISTER16_t *)0x403C0000)
#define XBARB2_SEL0			(IMXRT_XBARB2.offset000)
#define XBARB2_SEL1			(IMXRT_XBARB2.offset002)
#define XBARB2_SEL2			(IMXRT_XBARB2.offset004)
#define XBARB2_SEL3			(IMXRT_XBARB2.offset006)
#define XBARB2_SEL4			(IMXRT_XBARB2.offset008)
#define XBARB2_SEL5			(IMXRT_XBARB2.offset00A)
#define XBARB2_SEL6			(IMXRT_XBARB2.offset00C)
#define XBARB2_SEL7			(IMXRT_XBARB2.offset00E)
#define IMXRT_XBARB3		(*(IMXRT_REGISTER16_t *)0x403C4000)
#define XBARB3_SEL0			(IMXRT_XBARB3.offset000)
#define XBARB3_SEL1			(IMXRT_XBARB3.offset002)
#define XBARB3_SEL2			(IMXRT_XBARB3.offset004)
#define XBARB3_SEL3			(IMXRT_XBARB3.offset006)
#define XBARB3_SEL4			(IMXRT_XBARB3.offset008)
#define XBARB3_SEL5			(IMXRT_XBARB3.offset00A)
#define XBARB3_SEL6			(IMXRT_XBARB3.offset00C)
#define XBARB3_SEL7			(IMXRT_XBARB3.offset00E)

// page 4069
#define IMXRT_XTALOSC24M	(*(IMXRT_REGISTER32_t *)0x400D8000)
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









