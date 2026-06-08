 #pragma once

// PinName values: 32 bit top 16 - offset in EMC table, low 8 bits 0-4 GPIO PIN 5-7 On Port #
typedef enum {
	AD_B0_00 = 0x0BC0000, AD_B0_01 = 0x0C00001, AD_B0_02 = 0x0C40002, AD_B0_03 = 0x0C80003, AD_B0_04 = 0x0CC0004, AD_B0_05 = 0x0D00005, AD_B0_06 = 0x0D40006, AD_B0_07 = 0x0D80007,
	AD_B0_08 = 0x0DC0008, AD_B0_09 = 0x0E00009, AD_B0_10 = 0x0E4000A, AD_B0_11 = 0x0E8000B, AD_B0_12 = 0x0EC000C, AD_B0_13 = 0x0F0000D, AD_B0_14 = 0x0F4000E, AD_B0_15 = 0x0F8000F,
	AD_B1_00 = 0x0FC0010, AD_B1_01 = 0x1000011, AD_B1_02 = 0x1040012, AD_B1_03 = 0x1080013, AD_B1_04 = 0x10C0014, AD_B1_05 = 0x1100015, AD_B1_06 = 0x1140016, AD_B1_07 = 0x1180017,
	AD_B1_08 = 0x11C0018, AD_B1_09 = 0x1200019, AD_B1_10 = 0x124001A, AD_B1_11 = 0x128001B, AD_B1_12 = 0x12C001C, AD_B1_13 = 0x130001D, AD_B1_14 = 0x134001D, AD_B1_15 = 0x138001F,
	B0_00 = 0x13C0020, B0_01 = 0x1400021, B0_02 = 0x1440022, B0_03 = 0x1480023, B0_04 = 0x14C0024, B0_05 = 0x1500025, B0_06 = 0x1540026, B0_07 = 0x1580027,
	B0_08 = 0x15C0028, B0_09 = 0x1600029, B0_10 = 0x164002A, B0_11 = 0x168002B, B0_12 = 0x16C002C, B0_13 = 0x170002D, B0_14 = 0x174002E, B0_15 = 0x178002F,
	B1_00 = 0x17C0030, B1_01 = 0x1800031, B1_02 = 0x1840032, B1_03 = 0x1880033, B1_04 = 0x18C0034, B1_05 = 0x1900035, B1_06 = 0x1940036, B1_07 = 0x1980037,
	B1_08 = 0x19C0038, B1_09 = 0x1A00039, B1_10 = 0x1A4003A, B1_11 = 0x1A8003B, B1_12 = 0x1AC003C, B1_13 = 0x1B0003D, B1_14 = 0x1B4003D, B1_15 = 0x1B8003F,
	EMC_00 = 0x0140060, EMC_01 = 0x0180061, EMC_02 = 0x01C0062, EMC_03 = 0x0200063, EMC_04 = 0x0240064, EMC_05 = 0x0280065, EMC_06 = 0x02C0066, EMC_07 = 0x0300067,
	EMC_08 = 0x0340068, EMC_09 = 0x0380069, EMC_10 = 0x03C006A, EMC_11 = 0x040006B, EMC_12 = 0x044006C, EMC_13 = 0x048006D, EMC_14 = 0x04C006E, EMC_15 = 0x050006F,
	EMC_16 = 0x0540070, EMC_17 = 0x0580071, EMC_18 = 0x05C0072, EMC_19 = 0x0600073, EMC_20 = 0x0640074, EMC_21 = 0x0680075, EMC_22 = 0x06C0076, EMC_23 = 0x0700077,
	EMC_24 = 0x0740078, EMC_25 = 0x0780079, EMC_26 = 0x07C007A, EMC_27 = 0x080007B, EMC_28 = 0x084007C, EMC_29 = 0x088007D, EMC_30 = 0x08C007D, EMC_31 = 0x090007F,
	EMC_32 = 0x0940052, EMC_33 = 0x0980053, EMC_34 = 0x09C0054, EMC_35 = 0x0A00055, EMC_36 = 0x0A40056, EMC_37 = 0x0A80057, EMC_38 = 0x0AC0058, EMC_39 = 0x0B00059,
	EMC_40 = 0x0B4005A, EMC_41 = 0x0B8005B, SD_B0_00 = 0x1BC004C, SD_B0_01 = 0x1C0004D, SD_B0_02 = 0x1C4004E, SD_B0_03 = 0x1C8004F, SD_B0_04 = 0x1CC0050, SD_B0_05 = 0x1D00051,
	SD_B1_00 = 0x1D40040, SD_B1_01 = 0x1D80041, SD_B1_02 = 0x1DC0042, SD_B1_03 = 0x1E00043, SD_B1_04 = 0x1E40044, SD_B1_05 = 0x1E80045, SD_B1_06 = 0x1EC0046, SD_B1_07 = 0x1F00047,
	SD_B1_08 = 0x1F40048, SD_B1_09 = 0x1F80049, SD_B1_10 = 0x1FC004A, SD_B1_11 = 0x200004B
} IMXRT_PIN_t;

//#define digitalPinToPort(pin)    (pin)
inline uint32_t digitalPinNameToBitMask(IMXRT_PIN_t pin_name) 				{return  1 << (pin_name & 0x1f);}
inline uint32_t digitalPinNameToBit(IMXRT_PIN_t pin_name) 					{return  (pin_name & 0x1f); }
//inline volatile uint32_t * pinNamePortOutputRegister(IMXRT_PIN_t pin_name) { return }
inline volatile uint32_t * pinNamePortSetRegister(IMXRT_PIN_t pin_name) 	{ return (volatile uint32_t*)((uint8_t *)&GPIO6_DR_SET + 0x4000 * ((pin_name >> 5) & 0x7));}
inline volatile uint32_t * pinNamePortClearRegister(IMXRT_PIN_t pin_name) 	{ return (volatile uint32_t*)((uint8_t *)&GPIO6_DR_CLEAR + 0x4000 * ((pin_name >> 5) & 0x7));}
inline volatile uint32_t * pinNamePortToggleRegister(IMXRT_PIN_t pin_name) 	{ return (volatile uint32_t*)((uint8_t *)&GPIO6_DR_TOGGLE + 0x4000 * ((pin_name >> 5) & 0x7));}
inline volatile uint32_t * pinNamePortInputRegister(IMXRT_PIN_t pin_name) { return (volatile uint32_t*)((uint8_t *)&GPIO6_PSR + 0x4000 * ((pin_name >> 5) & 0x7));}
inline volatile uint32_t * pinNamePortModeRegister(IMXRT_PIN_t pin_name) { return (volatile uint32_t *)(IMXRT_IOMUXC_ADDRESS + (pin_name >> 16));}
inline volatile uint32_t * pinNamePortConfigRegister(IMXRT_PIN_t pin_name) { return (volatile uint32_t *)(IMXRT_IOMUXC_ADDRESS + (pin_name >> 16) + 0x1f0);}
//inline volatile uint32_t * pinNamePortControlRegister(IMXRT_PIN_t pin_name) { return }
//#define digitalPinToPortReg(pin) (portOutputRegister(pin))

inline void digitalWrite(IMXRT_PIN_t pin_name, uint8_t val) {
	uint32_t mask = 1 << (pin_name & 0x1f);
	if (val) {
		volatile uint32_t *reg = (volatile uint32_t*)((uint8_t *)&GPIO6_DR_SET + 0x4000 * ((pin_name >> 5) & 0x7));
		*reg = mask;
	} else {
		volatile uint32_t *reg = (volatile uint32_t*)((uint8_t *)&GPIO6_DR_CLEAR + 0x4000 * ((pin_name >> 5) & 0x7));
		*reg = mask;
	}
}
inline void digitalToggle(IMXRT_PIN_t pin_name) {
	uint32_t mask = 1 << (pin_name & 0x1f);
	volatile uint32_t *reg = (volatile uint32_t*)((uint8_t *)&GPIO6_DR_TOGGLE + 0x4000 * ((pin_name >> 5) & 0x7));
	//Serial.printf("Toggle %x Reg:%x mask:%x\n", pin_name, reg, mask);
	*reg = mask;
}

inline uint8_t digitalRead(IMXRT_PIN_t pin_name) {
	return (*pinNamePortInputRegister(pin_name) & digitalPinNameToBitMask(pin_name))? 1 : 0;
}

void pinMode(IMXRT_PIN_t pin_name, uint8_t mode)
{
	// generate PAD and MUX register from name...
	volatile uint32_t *mux = (volatile uint32_t *)(IMXRT_IOMUXC_ADDRESS + (pin_name >> 16));
	volatile uint32_t *pad = (volatile uint32_t *)(IMXRT_IOMUXC_ADDRESS + (pin_name >> 16) + 0x1f0);
	volatile uint32_t *gdir = (volatile uint32_t*)((uint8_t *)&GPIO6_GDIR + 0x4000 * ((pin_name >> 5) & 0x7));
	uint32_t mask = 1 << (pin_name & 0x1f);

	Serial.printf("pinMode %x mux:%p pad:%p gdir:%p mask:%x\n", pin_name, mux, pad, gdir, mask);

	if (mode == OUTPUT || mode == OUTPUT_OPENDRAIN) {
		*gdir |= mask; // TODO: atomic
		if (mode == OUTPUT) {
			*pad = IOMUXC_PAD_DSE(7);
		} else { // OUTPUT_OPENDRAIN
			*pad = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_ODE;
		}
	} else {
		*gdir &= ~(mask); // TODO: atomic
		if (mode == INPUT) {
			*pad = IOMUXC_PAD_DSE(7);
		} else if (mode == INPUT_PULLUP) {
			*pad = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(3) | IOMUXC_PAD_HYS;
		} else if (mode == INPUT_PULLDOWN) {
			*pad = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_PKE | IOMUXC_PAD_PUE | IOMUXC_PAD_PUS(0) | IOMUXC_PAD_HYS;
		} else { // INPUT_DISABLE
			*pad = IOMUXC_PAD_DSE(7) | IOMUXC_PAD_HYS;
		}
	}
	*mux = (uint8_t)(5 | 0x10);
}
