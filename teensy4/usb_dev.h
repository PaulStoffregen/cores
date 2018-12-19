#pragma once
#include "imxrt.h"

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

void usb_init(void);
void usb_init_serialnumber(void);

void usb_prepare_transfer(transfer_t *transfer, const void *data, uint32_t len, uint32_t param);
void usb_transmit(int endpoint_number, transfer_t *transfer);


