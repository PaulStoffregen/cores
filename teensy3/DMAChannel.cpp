#include "DMAChannel.h"

// The channel allocation bitmask is accessible from "C" namespace,
// so C-only code can reserve DMA channels
uint16_t dma_channel_allocated_mask = 0;

DMAChannel::DMAChannel(uint8_t channelRequest) : TCD(*(TCD_t *)0), channel(16)
{
	uint8_t next, ch=channelRequest;

	__disable_irq();
	while (1) {
		if (!(dma_channel_allocated_mask & (1 << ch))) {
			dma_channel_allocated_mask |= (1 << ch);
			__enable_irq();
			break;
		}
		next = (ch + 1) & 15;
		if (next == channelRequest) {
			__enable_irq();
			return; // no more channels available
			// attempts to use this object will hardfault
		}
	}
	channel = ch;
	TCD = *(TCD_t *)(0x40009000 + ch * 32);
	TCD.CSR = 0;
	TCD.ATTR = 0;
	TCD.NBYTES = 0;
	TCD.BITER = 0;
	TCD.CITER = 0;
	SIM_SCGC7 |= SIM_SCGC7_DMA;
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX;
	DMA_CR = 0;
}

