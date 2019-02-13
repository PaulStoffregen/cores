#include "usb_dev.h"
#define USB_DESC_LIST_DEFINE
#include "usb_desc.h"
#include "usb_serial.h"
#include "core_pins.h" // for delay()
#include <string.h>
#include "debug/printf.h"

// device mode, page 3155

typedef struct endpoint_struct endpoint_t;

struct endpoint_struct {
	uint32_t config;
	uint32_t current;
	uint32_t next;
	uint32_t status;
	uint32_t pointer0;
	uint32_t pointer1;
	uint32_t pointer2;
	uint32_t pointer3;
	uint32_t pointer4;
	uint32_t reserved;
	uint32_t setup0;
	uint32_t setup1;
	transfer_t *first_transfer;
	transfer_t *last_transfer;
	void (*callback_function)(transfer_t *completed_transfer);
	uint32_t unused1;
};

/*struct transfer_struct {
	uint32_t next;
	uint32_t status;
	uint32_t pointer0;
	uint32_t pointer1;
	uint32_t pointer2;
	uint32_t pointer3;
	uint32_t pointer4;
	uint32_t callback_param;
};*/

endpoint_t endpoint_queue_head[(NUM_ENDPOINTS+1)*2] __attribute__ ((used, aligned(4096)));

transfer_t endpoint0_transfer_data __attribute__ ((used, aligned(32)));
transfer_t endpoint0_transfer_ack  __attribute__ ((used, aligned(32)));


typedef union {
 struct {
  union {
   struct {
        uint8_t bmRequestType;
        uint8_t bRequest;
   };
        uint16_t wRequestAndType;
  };
        uint16_t wValue;
        uint16_t wIndex;
        uint16_t wLength;
 };
 struct {
        uint32_t word1;
        uint32_t word2;
 };
	uint64_t bothwords;
} setup_t;

static setup_t endpoint0_setupdata;
static uint32_t endpoint0_notify_mask=0;
static uint32_t endpointN_notify_mask=0;
//static int reset_count=0;
volatile uint8_t usb_configuration = 0;
static uint8_t endpoint0_buffer[8];
static uint8_t usb_reboot_timer = 0;


static void isr(void);
static void endpoint0_setup(uint64_t setupdata);
static void endpoint0_transmit(const void *data, uint32_t len, int notify);
static void endpoint0_receive(void *data, uint32_t len, int notify);
static void endpoint0_complete(void);



__attribute__((section(".progmem")))
void usb_init(void)
{
	// TODO: only enable when VBUS detected
	// TODO: return to low power mode when VBUS removed
	// TODO: protect PMU access with MPU
	PMU_REG_3P0 = PMU_REG_3P0_OUTPUT_TRG(0x0F) | PMU_REG_3P0_BO_OFFSET(6)
		| PMU_REG_3P0_ENABLE_LINREG;

	usb_init_serialnumber();

	// assume PLL3 is already running - already done by usb_pll_start() in main.c

	CCM_CCGR6 |= CCM_CCGR6_USBOH3(CCM_CCGR_ON); // turn on clocks to USB peripheral
	
	// Before programming this register, the PHY clocks must be enabled in registers
	// USBPHYx_CTRLn and CCM_ANALOG_USBPHYx_PLL_480_CTRLn.

	//printf("USBPHY1_PWD=%08lX\n", USBPHY1_PWD);
	//printf("USBPHY1_TX=%08lX\n", USBPHY1_TX);
	//printf("USBPHY1_RX=%08lX\n", USBPHY1_RX);
	//printf("USBPHY1_CTRL=%08lX\n", USBPHY1_CTRL);
	//printf("USB1_USBMODE=%08lX\n", USB1_USBMODE);

	// turn on PLL3, wait for 480 MHz lock?
	// turn on CCM clock gates?  CCGR6[CG0]
#if 1
	if ((USBPHY1_PWD & (USBPHY_PWD_RXPWDRX | USBPHY_PWD_RXPWDDIFF | USBPHY_PWD_RXPWD1PT1
	  | USBPHY_PWD_RXPWDENV | USBPHY_PWD_TXPWDV2I | USBPHY_PWD_TXPWDIBIAS
	  | USBPHY_PWD_TXPWDFS)) || (USB1_USBMODE & USB_USBMODE_CM_MASK)) {
		// USB controller is turned on from previous use
		// reset needed to turn it off & start from clean slate
		USBPHY1_CTRL_SET = USBPHY_CTRL_SFTRST; // USBPHY1_CTRL page 3292
		USB1_USBCMD |= USB_USBCMD_RST; // reset controller
		int count=0;
		while (USB1_USBCMD & USB_USBCMD_RST) count++;
		NVIC_CLEAR_PENDING(IRQ_USB1);
		USBPHY1_CTRL_CLR = USBPHY_CTRL_SFTRST; // reset PHY
		//USB1_USBSTS = USB1_USBSTS; // TODO: is this needed?
		printf("USB reset took %d loops\n", count);
		//delay(10);
		//printf("\n");
		//printf("USBPHY1_PWD=%08lX\n", USBPHY1_PWD);
		//printf("USBPHY1_TX=%08lX\n", USBPHY1_TX);
		//printf("USBPHY1_RX=%08lX\n", USBPHY1_RX);
		//printf("USBPHY1_CTRL=%08lX\n", USBPHY1_CTRL);
		//printf("USB1_USBMODE=%08lX\n", USB1_USBMODE);
		delay(25);
	}
#endif
	// Device Controller Initialization, page 3161
	// USBCMD	pg 3216
	// USBSTS	pg 3220
	// USBINTR	pg 3224
	// DEVICEADDR	pg 3227
	// ENDPTLISTADDR   3229
	// USBMODE	pg 3244
	// ENDPTSETUPSTAT  3245
	// ENDPTPRIME	pg 3246
	// ENDPTFLUSH	pg 3247
	// ENDPTSTAT	pg 3247
	// ENDPTCOMPLETE   3248
	// ENDPTCTRL0	pg 3249

	USBPHY1_CTRL_CLR = USBPHY_CTRL_CLKGATE;
	USBPHY1_PWD = 0;
	//printf("USBPHY1_PWD=%08lX\n", USBPHY1_PWD);
	//printf("USBPHY1_CTRL=%08lX\n", USBPHY1_CTRL);

	USB1_USBMODE = USB_USBMODE_CM(2) | USB_USBMODE_SLOM;
	memset(endpoint_queue_head, 0, sizeof(endpoint_queue_head));
	endpoint_queue_head[0].config = (64 << 16) | (1 << 15);
	endpoint_queue_head[1].config = (64 << 16);
	USB1_ENDPOINTLISTADDR = (uint32_t)&endpoint_queue_head;
	//  Recommended: enable all device interrupts including: USBINT, USBERRINT,
	// Port Change Detect, USB Reset Received, DCSuspend.
	USB1_USBINTR = USB_USBINTR_UE | USB_USBINTR_UEE | /* USB_USBINTR_PCE | */
		USB_USBINTR_URE | USB_USBINTR_SLE;
	//_VectorsRam[IRQ_USB1+16] = &isr;
	attachInterruptVector(IRQ_USB1, &isr);
	NVIC_ENABLE_IRQ(IRQ_USB1);
	//printf("USB1_ENDPTCTRL0=%08lX\n", USB1_ENDPTCTRL0);
	//printf("USB1_ENDPTCTRL1=%08lX\n", USB1_ENDPTCTRL1);
	//printf("USB1_ENDPTCTRL2=%08lX\n", USB1_ENDPTCTRL2);
	//printf("USB1_ENDPTCTRL3=%08lX\n", USB1_ENDPTCTRL3);
	USB1_USBCMD |= USB_USBCMD_RS;
}


static void isr(void)
{
	//printf("*");

	//  Port control in device mode is only used for
	//  status port reset, suspend, and current connect status.
	uint32_t status = USB1_USBSTS;
	USB1_USBSTS = status;

	// USB_USBSTS_SLI - set to 1 when enters a suspend state from an active state
	// USB_USBSTS_SRI - set at start of frame
	// USB_USBSTS_SRI - set when USB reset detected

	if (status & USB_USBSTS_UI) {
		//printf("data\n");
		uint32_t setupstatus = USB1_ENDPTSETUPSTAT;
		//printf("USB1_ENDPTSETUPSTAT=%X\n", setupstatus);
		while (setupstatus) {
			USB1_ENDPTSETUPSTAT = setupstatus;
			setup_t s;
			do {
				USB1_USBCMD |= USB_USBCMD_SUTW;
				s.word1 = endpoint_queue_head[0].setup0;
				s.word2 = endpoint_queue_head[0].setup1;
			} while (!(USB1_USBCMD & USB_USBCMD_SUTW));
			USB1_USBCMD &= ~USB_USBCMD_SUTW;
			//printf("setup %08lX %08lX\n", s.word1, s.word2);
			USB1_ENDPTFLUSH = (1<<16) | (1<<0); // page 3174
			while (USB1_ENDPTFLUSH & ((1<<16) | (1<<0))) ;
			endpoint0_notify_mask = 0;
			endpoint0_setup(s.bothwords);
			setupstatus = USB1_ENDPTSETUPSTAT; // page 3175
		}
		uint32_t completestatus = USB1_ENDPTCOMPLETE;
		if (completestatus) {
			USB1_ENDPTCOMPLETE = completestatus;
			//printf("USB1_ENDPTCOMPLETE=%lX\n", completestatus);
			if (completestatus & endpoint0_notify_mask) {
				endpoint0_notify_mask = 0;
				endpoint0_complete();
			}
			if (completestatus & endpointN_notify_mask) {
				// TODO: callback functions...
			}
		}
	}
	if (status & USB_USBSTS_URI) { // page 3164
		USB1_ENDPTSETUPSTAT = USB1_ENDPTSETUPSTAT; // Clear all setup token semaphores
		USB1_ENDPTCOMPLETE = USB1_ENDPTCOMPLETE; // Clear all the endpoint complete status
		while (USB1_ENDPTPRIME != 0) ; // Wait for any endpoint priming
		USB1_ENDPTFLUSH = 0xFFFFFFFF;  // Cancel all endpoint primed status
		if ((USB1_PORTSC1 & USB_PORTSC1_PR)) {
			//printf("reset\n");
		} else {
			// we took too long to respond :(
			// TODO; is this ever really a problem?
			//printf("reset too slow\n");
		}
		// TODO: Free all allocated dTDs 
		//if (++reset_count >= 3) {
			// shut off USB - easier to see results in protocol analyzer
			//USB1_USBCMD &= ~USB_USBCMD_RS;
			//printf("shut off USB\n");
		//}
	}
	if (status & USB_USBSTS_PCI) {
		if (USB1_PORTSC1 & USB_PORTSC1_HSP) {
			//printf("port at 480 Mbit\n");
		} else {
			//printf("port at 12 Mbit\n");
		}
	}
	if (status & USB_USBSTS_SLI) { // page 3165
		//printf("suspend\n");
	}
	if (status & USB_USBSTS_UEI) {
		//printf("error\n");
	}
	if ((USB1_USBINTR & USB_USBINTR_SRE) && (status & USB_USBSTS_SRI)) {
		printf("sof %d\n", usb_reboot_timer);
		if (usb_reboot_timer) {
			if (--usb_reboot_timer == 0) {
				asm("bkpt #251"); // run bootloader
			}
		} else {
			// turn off the SOF interrupt if nothing using it
			USB1_USBINTR &= ~USB_USBINTR_SRE;
		}
	}
}


/*
struct transfer_struct { // table 55-60, pg 3159
	uint32_t next;
	uint32_t status;
	uint32_t pointer0;
	uint32_t pointer1;
	uint32_t pointer2;
	uint32_t pointer3;
	uint32_t pointer4;
	uint32_t unused1;
};
transfer_t endpoint0_transfer_data __attribute__ ((aligned(32)));;
transfer_t endpoint0_transfer_ack  __attribute__ ((aligned(32)));;
*/

static void endpoint0_setup(uint64_t setupdata)
{
	setup_t setup;
	uint32_t datalen = 0;
	const usb_descriptor_list_t *list;

	setup.bothwords = setupdata;
	switch (setup.wRequestAndType) {
	  case 0x0500: // SET_ADDRESS
		endpoint0_receive(NULL, 0, 0);
		USB1_DEVICEADDR = USB_DEVICEADDR_USBADR(setup.wValue) | USB_DEVICEADDR_USBADRA;
		return;
	  case 0x0900: // SET_CONFIGURATION
		usb_configuration = setup.wValue;
		// configure all other endpoints
		volatile uint32_t *reg = &USB1_ENDPTCTRL1;
		const uint32_t *cfg = usb_endpoint_config_table;
		int i;
		for (i=0; i < NUM_ENDPOINTS; i++) {
			uint32_t n = *cfg++;
			*reg = n;
			// TODO: do the TRX & RXR bits self clear??
			uint32_t m = n & ~(USB_ENDPTCTRL_TXR | USB_ENDPTCTRL_RXR);
			*reg = m;
			//uint32_t p = *reg;
			//printf(" ep=%d: cfg=%08lX - %08lX - %08lX\n", i + 1, n, m, p);
			reg++;
		}
		// TODO: configure all queue heads with max packet length, zlt & mult
		endpoint_queue_head[CDC_ACM_ENDPOINT*2+1].config = (CDC_ACM_ENDPOINT << 16);
		endpoint_queue_head[CDC_RX_ENDPOINT*2+0].config = (CDC_RX_SIZE << 16) | (1 << 29);
		endpoint_queue_head[CDC_TX_ENDPOINT*2+1].config = (CDC_TX_SIZE << 16) | (1 << 29);

		// TODO: de-allocate any pending transfers?
		endpoint0_receive(NULL, 0, 0);
		return;

	  case 0x0680: // GET_DESCRIPTOR
	  case 0x0681:
		//printf("desc:\n");  // yay - sending device descriptor now works!!!!
		for (list = usb_descriptor_list; list->addr != NULL; list++) {
			if (setup.wValue == list->wValue && setup.wIndex == list->wIndex) {
				if ((setup.wValue >> 8) == 3) {
					// for string descriptors, use the descriptor's
					// length field, allowing runtime configured length.
					datalen = *(list->addr);
				} else {
					datalen = list->length;
				}
				if (datalen > setup.wLength) datalen = setup.wLength;
				endpoint0_transmit(list->addr, datalen, 0);
				return;
			}
		}
		break;
	  case 0x2221: // CDC_SET_CONTROL_LINE_STATE
		usb_cdc_line_rtsdtr_millis = systick_millis_count;
		usb_cdc_line_rtsdtr = setup.wValue;
	  case 0x2321: // CDC_SEND_BREAK
		endpoint0_receive(NULL, 0, 0);
		return;
	  case 0x2021: // CDC_SET_LINE_CODING
		if (setup.wLength != 7) break;
		endpoint0_setupdata.bothwords = setupdata;
		endpoint0_receive(endpoint0_buffer, 7, 1);
		return;
	}
	USB1_ENDPTCTRL0 = 0x000010001; // stall
}

static void endpoint0_transmit(const void *data, uint32_t len, int notify)
{
	//printf("tx %lu\n", len);
	if (len > 0) {
		// Executing A Transfer Descriptor, page 3182
		endpoint0_transfer_data.next = 1;
		endpoint0_transfer_data.status = (len << 16) | (1<<7);
		uint32_t addr = (uint32_t)data;
		endpoint0_transfer_data.pointer0 = addr; // format: table 55-60, pg 3159
		endpoint0_transfer_data.pointer1 = addr + 4096;
		endpoint0_transfer_data.pointer2 = addr + 8192;
		endpoint0_transfer_data.pointer3 = addr + 12288;
		endpoint0_transfer_data.pointer4 = addr + 16384;
		//  Case 1: Link list is empty, page 3182
		endpoint_queue_head[1].next = (uint32_t)&endpoint0_transfer_data;
		endpoint_queue_head[1].status = 0;
		USB1_ENDPTPRIME |= (1<<16);
		while (USB1_ENDPTPRIME) ;
	}
	endpoint0_transfer_ack.next = 1;
	endpoint0_transfer_ack.status = (1<<7) | (notify ? (1 << 15) : 0);
	endpoint0_transfer_ack.pointer0 = 0;
	endpoint_queue_head[0].next = (uint32_t)&endpoint0_transfer_ack;
	endpoint_queue_head[0].status = 0;
	USB1_ENDPTPRIME |= (1<<0);
	endpoint0_notify_mask = (notify ? (1 << 0) : 0);
	while (USB1_ENDPTPRIME) ;
}

static void endpoint0_receive(void *data, uint32_t len, int notify)
{
	//printf("rx %lu\n", len);
	if (len > 0) {
		// Executing A Transfer Descriptor, page 3182
		endpoint0_transfer_data.next = 1;
		endpoint0_transfer_data.status = (len << 16) | (1<<7);
		uint32_t addr = (uint32_t)data;
		endpoint0_transfer_data.pointer0 = addr; // format: table 55-60, pg 3159
		endpoint0_transfer_data.pointer1 = addr + 4096;
		endpoint0_transfer_data.pointer2 = addr + 8192;
		endpoint0_transfer_data.pointer3 = addr + 12288;
		endpoint0_transfer_data.pointer4 = addr + 16384;
		//  Case 1: Link list is empty, page 3182
		endpoint_queue_head[0].next = (uint32_t)&endpoint0_transfer_data;
		endpoint_queue_head[0].status = 0;
		USB1_ENDPTPRIME |= (1<<0);
		while (USB1_ENDPTPRIME) ;
	}
	endpoint0_transfer_ack.next = 1;
	endpoint0_transfer_ack.status = (1<<7) | (notify ? (1 << 15) : 0);
	endpoint0_transfer_ack.pointer0 = 0;
	endpoint_queue_head[1].next = (uint32_t)&endpoint0_transfer_ack;
	endpoint_queue_head[1].status = 0;
	USB1_ENDPTPRIME |= (1<<16);
	endpoint0_notify_mask = (notify ? (1 << 16) : 0);
	while (USB1_ENDPTPRIME) ;
}

/*typedef union {
 struct {
  union {
   struct {
        uint8_t bmRequestType;
        uint8_t bRequest;
   };
        uint16_t wRequestAndType;
  };
        uint16_t wValue;
        uint16_t wIndex;
        uint16_t wLength;
 };
 struct {
        uint32_t word1;
        uint32_t word2;
 };
	uint64_t bothwords;
} setup_t; */


static void endpoint0_complete(void)
{
	setup_t setup;

	setup.bothwords = endpoint0_setupdata.bothwords;
	//printf("complete\n");
#ifdef CDC_STATUS_INTERFACE
	if (setup.wRequestAndType == 0x2021 /*CDC_SET_LINE_CODING*/) {
		memcpy(usb_cdc_line_coding, endpoint0_buffer, 7);
		printf("usb_cdc_line_coding, baud=%u\n", usb_cdc_line_coding[0]);
		if (usb_cdc_line_coding[0] == 134) {
			USB1_USBINTR |= USB_USBINTR_SRE;
			usb_reboot_timer = 80; // TODO: 10 if only 12 Mbit/sec
		}
	}
#endif
}

void usb_prepare_transfer(transfer_t *transfer, const void *data, uint32_t len, uint32_t param)
{
	transfer->next = 1;
	transfer->status = (len << 16) | (1<<7);
	uint32_t addr = (uint32_t)data;
	transfer->pointer0 = addr;
	transfer->pointer1 = addr + 4096;
	transfer->pointer2 = addr + 8192;
	transfer->pointer3 = addr + 12288;
	transfer->pointer4 = addr + 16384;
	transfer->callback_param = param;
}

void usb_transmit(int endpoint_number, transfer_t *transfer)
{
	// endpoint 0 reserved for control
	// endpoint 1 reserved for debug
//printf("usb_transmit %d\n", endpoint_number);
	if (endpoint_number < 2 || endpoint_number > NUM_ENDPOINTS) return;
	endpoint_t *endpoint = &endpoint_queue_head[endpoint_number * 2 + 1];
	if (endpoint->callback_function) {
		transfer->status |= (1<<15);
	} else {
		//transfer->status |= (1<<15);
		// remove all inactive transfers
	}
	uint32_t mask = 1 << (endpoint_number + 16);
	__disable_irq();
#if 0
	if (endpoint->last_transfer) {
		if (!(endpoint->last_transfer->status & (1<<7))) {
			endpoint->last_transfer->next = (uint32_t)transfer;
		} else {
			// Case 2: Link list is not empty, page 3182
			endpoint->last_transfer->next = (uint32_t)transfer;
			if (USB1_ENDPTPRIME & mask) {
				endpoint->last_transfer = transfer;
				__enable_irq();
				printf(" case 2a\n");
				return;
			}
			uint32_t stat;
			uint32_t cmd = USB1_USBCMD;
			do {
				USB1_USBCMD = cmd | USB_USBCMD_ATDTW;
				stat = USB1_ENDPTSTATUS;
			} while (!(USB1_USBCMD & USB_USBCMD_ATDTW));
			USB1_USBCMD = cmd & ~USB_USBCMD_ATDTW;
			if (stat & mask) {
				endpoint->last_transfer = transfer;
				__enable_irq();
				printf(" case 2b\n");
				return;
			}
		}
	} else {
		endpoint->first_transfer = transfer;
	}
	endpoint->last_transfer = transfer;
#endif
	// Case 1: Link list is empty, page 3182
	endpoint->next = (uint32_t)transfer;
	endpoint->status = 0;
	USB1_ENDPTPRIME |= mask;
	while (USB1_ENDPTPRIME & mask) ;
	__enable_irq();
	//printf(" case 1\n");


	// ENDPTPRIME - momentarily set by hardware during hardware re-priming
	//		 operations when a dTD is retired, and the dQH is updated.

	// ENDPTSTAT -   Transmit Buffer Ready - set to one by the hardware as a
	//		 response to receiving a command from a corresponding bit
	//		 in the ENDPTPRIME register.  . Buffer ready is cleared by
	//		 USB reset, by the USB DMA system, or through the ENDPTFLUSH
	//		 register.  (so 0=buffer ready, 1=buffer primed for transmit)

}

/*struct endpoint_struct {
	uint32_t config;
	uint32_t current;
	uint32_t next;
	uint32_t status;
	uint32_t pointer0;
	uint32_t pointer1;
	uint32_t pointer2;
	uint32_t pointer3;
	uint32_t pointer4;
	uint32_t reserved;
	uint32_t setup0;
	uint32_t setup1;
	transfer_t *first_transfer;
	transfer_t *last_transfer;
	void (*callback_function)(transfer_t *completed_transfer);
	uint32_t unused1;
};*/





























