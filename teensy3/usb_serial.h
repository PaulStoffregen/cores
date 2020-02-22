/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef USBserial_h_
#define USBserial_h_

#include "usb_desc.h"

#if (defined(CDC_STATUS_INTERFACE) && defined(CDC_DATA_INTERFACE)) || defined(USB_DISABLED)
#define USB_SERIAL_SUFFIX	/* none */
#define SERIAL_CLASS_SUFFIX	/* none */

#include "usb_serial_template.h"

#define usb_cdc_line_coding		usb_serial_instance.cdc_line_coding
#define usb_cdc_line_rtsdtr_millis	usb_serial_instance.cdc_line_rtsdtr_millis
#define usb_cdc_line_rtsdtr		usb_serial_instance.cdc_line_rtsdtr
#define usb_cdc_transmit_flush_timer	usb_serial_instance.cdc_transmit_flush_timer
#endif // CDC_STATUS_INTERFACE && CDC_DATA_INTERFACE

#endif // USBserial_h_
