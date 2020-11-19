#pragma once
#include "imxrt.h"

#if !defined(USB_DISABLED)

typedef struct transfer_struct transfer_t;
struct transfer_struct {
        uint32_t next;
        volatile uint32_t status;
        uint32_t pointer0;
        uint32_t pointer1;
        uint32_t pointer2;
        uint32_t pointer3;
        uint32_t pointer4;
        uint32_t callback_param;
};

#ifdef __cplusplus
extern "C" {
#endif

void usb_init(void);
void usb_init_serialnumber(void);

void usb_config_rx(uint32_t ep, uint32_t packet_size, int do_zlp, void (*cb)(transfer_t *));
void usb_config_tx(uint32_t ep, uint32_t packet_size, int do_zlp, void (*cb)(transfer_t *));
void usb_config_rx_iso(uint32_t ep, uint32_t packet_size, int mult, void (*cb)(transfer_t *));
void usb_config_tx_iso(uint32_t ep, uint32_t packet_size, int mult, void (*cb)(transfer_t *));

void usb_prepare_transfer(transfer_t *transfer, const void *data, uint32_t len, uint32_t param);
void usb_transmit(int endpoint_number, transfer_t *transfer);
void usb_receive(int endpoint_number, transfer_t *transfer);
uint32_t usb_transfer_status(const transfer_t *transfer);

void usb_start_sof_interrupts(int interface);
void usb_stop_sof_interrupts(int interface);

extern void (*usb_timer0_callback)(void);
extern void (*usb_timer1_callback)(void);

#ifdef __cplusplus
}
#endif

#else // !defined(USB_DISABLED)

#ifdef __cplusplus
extern "C" {
#endif

void usb_init(void);

#ifdef __cplusplus
}
#endif


#endif // !defined(USB_DISABLED)
