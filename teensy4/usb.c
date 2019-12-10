#include "usb_dev.h"
#define USB_DESC_LIST_DEFINE
#include "usb_desc.h"
#include "usb_serial.h"
#include "usb_seremu.h"
#include "usb_keyboard.h"
#include "usb_mouse.h"
#include "usb_joystick.h"
#include "usb_touch.h"
#include "usb_midi.h"
#include "core_pins.h" // for delay()
#include "avr/pgmspace.h"
#include <string.h>
#include "debug/printf.h"

//#define LOG_SIZE  20
//uint32_t transfer_log_head=0;
//uint32_t transfer_log_count=0;
//uint32_t transfer_log[LOG_SIZE];

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
volatile uint8_t usb_configuration = 0; // non-zero when USB host as configured device
volatile uint8_t usb_high_speed = 0;    // non-zero if running at 480 Mbit/sec speed
static uint8_t endpoint0_buffer[8];
static uint8_t sof_usage = 0;
static uint8_t usb_reboot_timer = 0;

extern uint8_t usb_descriptor_buffer[]; // defined in usb_desc.c
extern const uint8_t usb_config_descriptor_480[];
extern const uint8_t usb_config_descriptor_12[];

void (*usb_timer0_callback)(void) = NULL;
void (*usb_timer1_callback)(void) = NULL;

static void isr(void);
static void endpoint0_setup(uint64_t setupdata);
static void endpoint0_transmit(const void *data, uint32_t len, int notify);
static void endpoint0_receive(void *data, uint32_t len, int notify);
static void endpoint0_complete(void);


static void run_callbacks(endpoint_t *ep);


FLASHMEM void usb_init(void)
{
	// TODO: only enable when VBUS detected
	// TODO: return to low power mode when VBUS removed
	// TODO: protect PMU access with MPU
	PMU_REG_3P0 = PMU_REG_3P0_OUTPUT_TRG(0x0F) | PMU_REG_3P0_BO_OFFSET(6)
		| PMU_REG_3P0_ENABLE_LINREG;

	usb_init_serialnumber();

	// assume PLL3 is already running - already done by usb_pll_start() in main.c

	CCM_CCGR6 |= CCM_CCGR6_USBOH3(CCM_CCGR_ON); // turn on clocks to USB peripheral
	
	printf("BURSTSIZE=%08lX\n", USB1_BURSTSIZE);
	//USB1_BURSTSIZE = USB_BURSTSIZE_TXPBURST(4) | USB_BURSTSIZE_RXPBURST(4);
	USB1_BURSTSIZE = 0x0404;
	printf("BURSTSIZE=%08lX\n", USB1_BURSTSIZE);
	printf("USB1_TXFILLTUNING=%08lX\n", USB1_TXFILLTUNING);

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
	USB1_USBCMD = USB_USBCMD_RS;
	//transfer_log_head = 0;
	//transfer_log_count = 0;
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
			completestatus &= endpointN_notify_mask;
			if (completestatus) {
				int i;   // TODO: optimize with __builtin_ctz()
				for (i=2; i <= NUM_ENDPOINTS; i++) {
					if (completestatus & (1 << i)) { // receive
						run_callbacks(endpoint_queue_head + i * 2);
					}
					if (completestatus & (1 << (i + 16))) { // transmit
						run_callbacks(endpoint_queue_head + i * 2 + 1);
					}
				}
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
		#if defined(CDC_STATUS_INTERFACE) && defined(CDC_DATA_INTERFACE)
		usb_serial_reset();
		#endif
		endpointN_notify_mask = 0;
		// TODO: Free all allocated dTDs
		//if (++reset_count >= 3) {
			// shut off USB - easier to see results in protocol analyzer
			//USB1_USBCMD &= ~USB_USBCMD_RS;
			//printf("shut off USB\n");
		//}
	}
	if (status & USB_USBSTS_TI0) {
		if (usb_timer0_callback != NULL) usb_timer0_callback();
	}
	if (status & USB_USBSTS_TI1) {
		if (usb_timer1_callback != NULL) usb_timer1_callback();
	}
	if (status & USB_USBSTS_PCI) {
		if (USB1_PORTSC1 & USB_PORTSC1_HSP) {
			//printf("port at 480 Mbit\n");
			usb_high_speed = 1;
		} else {
			//printf("port at 12 Mbit\n");
			usb_high_speed = 0;
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
				usb_stop_sof_interrupts(NUM_INTERFACE);
				asm("bkpt #251"); // run bootloader
			}
		}
		#ifdef MIDI_INTERFACE
		usb_midi_flush_output();
		#endif
	}
}


void usb_start_sof_interrupts(int interface)
{
	__disable_irq();
	sof_usage |= (1 << interface);
	uint32_t intr = USB1_USBINTR;
	if (!(intr & USB_USBINTR_SRE)) {
		USB1_USBSTS = USB_USBSTS_SRI; // clear prior SOF before SOF IRQ enable
		USB1_USBINTR = intr | USB_USBINTR_SRE;
	}
	__enable_irq();
}

void usb_stop_sof_interrupts(int interface)
{
	sof_usage &= ~(1 << interface);
	if (sof_usage == 0) {
		USB1_USBINTR &= ~USB_USBINTR_SRE;
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

static uint8_t reply_buffer[8];

static void endpoint0_setup(uint64_t setupdata)
{
	setup_t setup;
	uint32_t endpoint, dir, ctrl;
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
		#if defined(ENDPOINT2_CONFIG)
		USB1_ENDPTCTRL2 = ENDPOINT2_CONFIG;
		#endif
		#if defined(ENDPOINT3_CONFIG)
		USB1_ENDPTCTRL3 = ENDPOINT3_CONFIG;
		#endif
		#if defined(ENDPOINT4_CONFIG)
		USB1_ENDPTCTRL4 = ENDPOINT4_CONFIG;
		#endif
		#if defined(ENDPOINT5_CONFIG)
		USB1_ENDPTCTRL5 = ENDPOINT5_CONFIG;
		#endif
		#if defined(ENDPOINT6_CONFIG)
		USB1_ENDPTCTRL6 = ENDPOINT6_CONFIG;
		#endif
		#if defined(ENDPOINT7_CONFIG)
		USB1_ENDPTCTRL7 = ENDPOINT7_CONFIG;
		#endif
		#if defined(CDC_STATUS_INTERFACE) && defined(CDC_DATA_INTERFACE)
		usb_serial_configure();
		#elif defined(SEREMU_INTERFACE)
		usb_seremu_configure();
		#endif
		#if defined(RAWHID_INTERFACE)
		usb_rawhid_configure();
		#endif
		#if defined(KEYBOARD_INTERFACE)
		usb_keyboard_configure();
		#endif
		#if defined(MOUSE_INTERFACE)
		usb_mouse_configure();
		#endif
		#if defined(JOYSTICK_INTERFACE)
		usb_joystick_configure();
		#endif
		#if defined(MULTITOUCH_INTERFACE)
		usb_touchscreen_configure();
		#endif
		#if defined(MIDI_INTERFACE)
		usb_midi_configure();
		#endif
		endpoint0_receive(NULL, 0, 0);
		return;
	  case 0x0880: // GET_CONFIGURATION
		reply_buffer[0] = usb_configuration;
		endpoint0_transmit(reply_buffer, 1, 0);
		return;
	  case 0x0080: // GET_STATUS (device)
		reply_buffer[0] = 0;
		reply_buffer[1] = 0;
		endpoint0_transmit(reply_buffer, 2, 0);
		return;
	  case 0x0082: // GET_STATUS (endpoint)
		endpoint = setup.wIndex & 0x7F;
		if (endpoint > 7) break;
		dir = setup.wIndex & 0x80;
		ctrl = *((uint32_t *)&USB1_ENDPTCTRL0 + endpoint);
		reply_buffer[0] = 0;
		reply_buffer[1] = 0;
		if ((dir && (ctrl & USB_ENDPTCTRL_TXS)) || (!dir && (ctrl & USB_ENDPTCTRL_RXS))) {
			reply_buffer[0] = 1;
		}
		endpoint0_transmit(reply_buffer, 2, 0);
		return;
	  case 0x0302: // SET_FEATURE (endpoint)
		endpoint = setup.wIndex & 0x7F;
		if (endpoint > 7) break;
		dir = setup.wIndex & 0x80;
		if (dir) {
			*((volatile uint32_t *)&USB1_ENDPTCTRL0 + endpoint) |= USB_ENDPTCTRL_TXS;
		} else {
			*((volatile uint32_t *)&USB1_ENDPTCTRL0 + endpoint) |= USB_ENDPTCTRL_RXS;
		}
		endpoint0_receive(NULL, 0, 0);
		return;
	  case 0x0102: // CLEAR_FEATURE (endpoint)
		endpoint = setup.wIndex & 0x7F;
		if (endpoint > 7) break;
		dir = setup.wIndex & 0x80;
		if (dir) {
			*((volatile uint32_t *)&USB1_ENDPTCTRL0 + endpoint) &= ~USB_ENDPTCTRL_TXS;
		} else {
			*((volatile uint32_t *)&USB1_ENDPTCTRL0 + endpoint) &= ~USB_ENDPTCTRL_RXS;
		}
		endpoint0_receive(NULL, 0, 0);
		return;
	  case 0x0680: // GET_DESCRIPTOR
	  case 0x0681:
		for (list = usb_descriptor_list; list->addr != NULL; list++) {
			if (setup.wValue == list->wValue && setup.wIndex == list->wIndex) {
				uint32_t datalen;
				if ((setup.wValue >> 8) == 3) {
					// for string descriptors, use the descriptor's
					// length field, allowing runtime configured length.
					datalen = *(list->addr);
				} else {
					datalen = list->length;
				}
				if (datalen > setup.wLength) datalen = setup.wLength;

				// copy the descriptor, from PROGMEM to DMAMEM
				if (setup.wValue == 0x200) {
					// config descriptor needs to adapt to speed
					const uint8_t *src = usb_config_descriptor_12;
					if (usb_high_speed) src = usb_config_descriptor_480;
					memcpy(usb_descriptor_buffer, src, datalen);
				} else if (setup.wValue == 0x700) {
					// other speed config also needs to adapt
					const uint8_t *src = usb_config_descriptor_480;
					if (usb_high_speed) src = usb_config_descriptor_12;
					memcpy(usb_descriptor_buffer, src, datalen);
					usb_descriptor_buffer[1] = 7;
				} else {
					memcpy(usb_descriptor_buffer, list->addr, datalen);
				}
				// prep transmit
				arm_dcache_flush_delete(usb_descriptor_buffer, datalen);
				endpoint0_transmit(usb_descriptor_buffer, datalen, 0);
				return;
			}
		}
		break;
#if defined(CDC_STATUS_INTERFACE)
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
#endif
#if defined(SEREMU_INTERFACE) || defined(KEYBOARD_INTERFACE)
	  case 0x0921: // HID SET_REPORT
		if (setup.wLength <= sizeof(endpoint0_buffer)) {
			//printf("hid set report %x %x\n", setup.word1, setup.word2);
			endpoint0_setupdata.bothwords = setup.bothwords;
			endpoint0_buffer[0] = 0xE9;
			endpoint0_receive(endpoint0_buffer, setup.wLength, 1);
			return;
		}
		break;
#endif
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
	USB1_ENDPTCOMPLETE |= (1<<0) | (1<<16);
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
	USB1_ENDPTCOMPLETE |= (1<<0) | (1<<16);
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
	//printf("complete %x %x %x\n", setup.word1, setup.word2, endpoint0_buffer[0]);
#ifdef CDC_STATUS_INTERFACE
	if (setup.wRequestAndType == 0x2021 /*CDC_SET_LINE_CODING*/) {
		memcpy(usb_cdc_line_coding, endpoint0_buffer, 7);
		printf("usb_cdc_line_coding, baud=%u\n", usb_cdc_line_coding[0]);
		if (usb_cdc_line_coding[0] == 134) {
			usb_start_sof_interrupts(NUM_INTERFACE);
			usb_reboot_timer = 80; // TODO: 10 if only 12 Mbit/sec
		}
	}
#endif
#ifdef SEREMU_INTERFACE
	if (setup.word1 == 0x03000921 && setup.word2 == ((4<<16)|SEREMU_INTERFACE)
	  && endpoint0_buffer[0] == 0xA9 && endpoint0_buffer[1] == 0x45
	  && endpoint0_buffer[2] == 0xC2 && endpoint0_buffer[3] == 0x6B) {
		printf("seremu reboot request\n");
		usb_start_sof_interrupts(NUM_INTERFACE);
		usb_reboot_timer = 80; // TODO: 10 if only 12 Mbit/sec
	}
#endif
}

static void usb_endpoint_config(endpoint_t *qh, uint32_t config, void (*callback)(transfer_t *))
{
	memset(qh, 0, sizeof(endpoint_t));
	qh->config = config;
	qh->next = 1; // Terminate bit = 1
	qh->callback_function = callback;
}

void usb_config_rx(uint32_t ep, uint32_t packet_size, int do_zlp, void (*cb)(transfer_t *))
{
	uint32_t config = (packet_size << 16) | (do_zlp ? 0 : (1 << 29));
	if (ep < 2 || ep > NUM_ENDPOINTS) return;
	usb_endpoint_config(endpoint_queue_head + ep * 2, config, cb);
	if (cb) endpointN_notify_mask |= (1 << ep);
}

void usb_config_tx(uint32_t ep, uint32_t packet_size, int do_zlp, void (*cb)(transfer_t *))
{
	uint32_t config = (packet_size << 16) | (do_zlp ? 0 : (1 << 29));
	if (ep < 2 || ep > NUM_ENDPOINTS) return;
	usb_endpoint_config(endpoint_queue_head + ep * 2 + 1, config, cb);
	if (cb) endpointN_notify_mask |= (1 << (ep + 16));
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

#if 0
void usb_print_transfer_log(void)
{
	uint32_t i, count;
	printf("log %d transfers\n", transfer_log_count);
	count = transfer_log_count;
	if (count > LOG_SIZE) count = LOG_SIZE;

	for (i=0; i < count; i++) {
		if (transfer_log_head == 0) transfer_log_head = LOG_SIZE;
		transfer_log_head--;
		uint32_t log = transfer_log[transfer_log_head];
		printf(" %c %X\n", log >> 8, (int)(log & 255));
	}
}
#endif

static void schedule_transfer(endpoint_t *endpoint, uint32_t epmask, transfer_t *transfer)
{
	// when we stop at 6, why is the last transfer missing from the USB output?
	//if (transfer_log_count >= 6) return;

	//uint32_t ret = (*(const uint8_t *)transfer->pointer0) << 8;
	if (endpoint->callback_function) {
		transfer->status |= (1<<15);
	}
	__disable_irq();
	//digitalWriteFast(1, HIGH);
	// Executing A Transfer Descriptor, page 2468 (RT1060 manual, Rev 1, 12/2018)
	transfer_t *last = endpoint->last_transfer;
	if (last) {
		last->next = (uint32_t)transfer;
		if (USB1_ENDPTPRIME & epmask) goto end;
		//digitalWriteFast(2, HIGH);
		//ret |= 0x01;
		uint32_t status;
		do {
			USB1_USBCMD |= USB_USBCMD_ATDTW;
			status = USB1_ENDPTSTATUS;
		} while (!(USB1_USBCMD & USB_USBCMD_ATDTW));
		//USB1_USBCMD &= ~USB_USBCMD_ATDTW;
		if (status & epmask) goto end;
		//ret |= 0x02;
	}
	//digitalWriteFast(4, HIGH);
	endpoint->next = (uint32_t)transfer;
	endpoint->status = 0;
	USB1_ENDPTPRIME |= epmask;
	endpoint->first_transfer = transfer;
end:
	endpoint->last_transfer = transfer;
	__enable_irq();
	//digitalWriteFast(4, LOW);
	//digitalWriteFast(3, LOW);
	//digitalWriteFast(2, LOW);
	//digitalWriteFast(1, LOW);
	//if (transfer_log_head > LOG_SIZE) transfer_log_head = 0;
	//transfer_log[transfer_log_head++] = ret;
	//transfer_log_count++;
}
	// ENDPTPRIME -  Software should write a one to the corresponding bit when
	//		 posting a new transfer descriptor to an endpoint queue head.
	//		 Hardware automatically uses this bit to begin parsing for a
	//		 new transfer descriptor from the queue head and prepare a
	//		 transmit buffer. Hardware clears this bit when the associated
	//		 endpoint(s) is (are) successfully primed.
	//		 Momentarily set by hardware during hardware re-priming
	//		 operations when a dTD is retired, and the dQH is updated.

	// ENDPTSTATUS - Transmit Buffer Ready - set to one by the hardware as a
	//		 response to receiving a command from a corresponding bit
	//		 in the ENDPTPRIME register.  . Buffer ready is cleared by
	//		 USB reset, by the USB DMA system, or through the ENDPTFLUSH
	//		 register.  (so 0=buffer ready, 1=buffer primed for transmit)

	//  USBCMD.ATDTW - This bit is used as a semaphore to ensure proper addition
	//		   of a new dTD to an active (primed) endpoint's linked list.
	//		   This bit is set and cleared by software.
	//		   This bit would also be cleared by hardware when state machine
	//		   is hazard region for which adding a dTD to a primed endpoint
	//		    may go unrecognized.

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

static void run_callbacks(endpoint_t *ep)
{
	//printf("run_callbacks\n");
	transfer_t *first = ep->first_transfer;
	if (first == NULL) return;

	// count how many transfers are completed, then remove them from the endpoint's list
	uint32_t count = 0;
	transfer_t *t = first;
	while (1) {
		if (t->status & (1<<7)) {
			// found a still-active transfer, new list begins here
			//printf(" still active\n");
			ep->first_transfer = t;
			break;
		}
		count++;
		t = (transfer_t *)t->next;
		if ((uint32_t)t == 1) {
			// reached end of list, all need callbacks, new list is empty
			//printf(" end of list\n");
			ep->first_transfer = NULL;
			ep->last_transfer = NULL;
			break;
		}
	}
	// do all the callbacks
	while (count) {
		transfer_t *next = (transfer_t *)first->next;
		ep->callback_function(first);
		first = next;
		count--;
	}
}

void usb_transmit(int endpoint_number, transfer_t *transfer)
{
	if (endpoint_number < 2 || endpoint_number > NUM_ENDPOINTS) return;
	endpoint_t *endpoint = endpoint_queue_head + endpoint_number * 2 + 1;
	uint32_t mask = 1 << (endpoint_number + 16);
	schedule_transfer(endpoint, mask, transfer);
}

void usb_receive(int endpoint_number, transfer_t *transfer)
{
	if (endpoint_number < 2 || endpoint_number > NUM_ENDPOINTS) return;
	endpoint_t *endpoint = endpoint_queue_head + endpoint_number * 2;
	uint32_t mask = 1 << endpoint_number;
	schedule_transfer(endpoint, mask, transfer);
}

uint32_t usb_transfer_status(const transfer_t *transfer)
{
#if 0
	uint32_t status, cmd;
	//int count=0;
	cmd = USB1_USBCMD;
	while (1) {
		__disable_irq();
		USB1_USBCMD = cmd | USB_USBCMD_ATDTW;
		status = transfer->status;
		cmd = USB1_USBCMD;
		__enable_irq();
		if (cmd & USB_USBCMD_ATDTW) return status;
		//if (!(cmd & USB_USBCMD_ATDTW)) continue;
		//if (status & 0x80) break; // for still active, only 1 reading needed
		//if (++count > 1) break; // for completed, check 10 times
	}
#else
	return transfer->status;
#endif
}


