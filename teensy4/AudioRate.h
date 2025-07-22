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
#ifndef AudioRate_h
#define AudioRate_h

#ifndef AUDIO_SAMPLE_RATE
#define AUDIO_SAMPLE_RATE (44100)
#endif

#ifdef AUDIO_SAMPLE_RATE_EXACT
#error You must set AUDIO_SAMPLE_RATE to an integer, not AUDIO_SAMPLE_RATE_EXACT to a float.  This is a change due to preprocess #if rate== stuff.  Probably can be worked around, but this is expedient.
#endif

#define AUDIO_SAMPLE_RATE_EXACT (AUDIO_SAMPLE_RATE * 1.0f)

#ifndef USB_AUDIO_TX_CHANNELS
#define USB_AUDIO_TX_CHANNELS (2U) /* NUMBER OF CHANNELS IN ISO_IN transactions */
#endif

#ifndef USB_AUDIO_RX_CHANNELS
#define USB_AUDIO_RX_CHANNELS (2U) /* NUMBER OF CHANNELS IN ISO_OUT transactions */
#endif

#ifndef USB_AUDIO_BYTES_PER_SAMPLE
#define USB_AUDIO_BYTES_PER_SAMPLE 2
#endif

// The number of RX data pins used for SAI reception.  
// SAI1 on teensy 4 has 4 possible pins for each of TX/RX
// They are shared, and can't be used simultaneously.
// On Teensy They are

// pin#  | TEENSY  | USE     | PAD
//       | NAME    |         |
//-------|---------|---------|---------- 
//  7    | OUT1A   | TX1     | GPIO_B1_01_ALT3
// 32    | OUT1B   | TX2 RX4 | GPIO_B0_12_ALT3
//  9    | OUT1C   | TX3 RX3 | GPIO_B0_11_ALT3
//  6    | OUT1D   | TX4 RX2 | GPIO_B0_10_ALT3
//  8    | IN1     |     RX1 | GPIO_B1_00_ALT3
#ifndef AUDIO_N_SAI1_RX_DATAPINS
#define AUDIO_N_SAI1_RX_DATAPINS 1
#endif

#ifndef AUDIO_N_SAI1_TX_DATAPINS
#define AUDIO_N_SAI1_TX_DATAPINS 1
#endif

# if (AUDIO_N_SAI1_RX_DATAPINS > 4  || AUDIO_N_SAI1_RX_DATAPINS < 1)
#error SAI1 may have between 1 and 4 (inclusive) data pins for RX
#endif
# if (AUDIO_N_SAI1_TX_DATAPINS > 4  || AUDIO_N_SAI1_TX_DATAPINS < 1)
#error SAI1 may have between 1 and 4 (inclusive) data pins for TX
#endif

#if (AUDIO_N_SAI1_RX_DATAPINS + AUDIO_N_SAI1_TX_DATAPINS > 5)
#error SAI1 has only 5 data pins.  You ve asked for too many.
#endif

#define USB_AUDIO_BYTES_PER_SAMPLE 2 /* warning... don't change this... it's not easily changeable yet, */
#define USB_AUDIO_BYTES_PER_TX_FRAME (USB_AUDIO_TX_CHANNELS*USB_AUDIO_BYTES_PER_SAMPLE)
#define USB_AUDIO_BYTES_PER_RX_FRAME (USB_AUDIO_RX_CHANNELS*USB_AUDIO_BYTES_PER_SAMPLE)

/* This isn't a parameter... yet.  Don't change it.. */
#define TDM_CHANNELS_PER_PIN 16

/*
  AUDIO_TX_SIZE and AUDIO_RX_SIZE are the maximum TX and RX sizes
  respectively, IN BYTES.  
   
  for 44.1khz, 16-bits, the number of bytes per 1ms usb frame is
     44100 af     sec        2 channels    2 bytes      176.4 bytes
   ----------- * -------- * ---------- * ------------ = -----------
      sec         1000 uf     audio_frame    sample      uf

  where:
     af     : audio_frame (i.e. what you typically call a sample)
     sample : an actual, single sample representing one channel, at one time
     uf     : usb frame.  1khz for full speed
     channel: channel is made up of 1 sample for every channel in the stream

  for 44.1khz, you must transmit an average of 176.4 bytes, which is
  44.1 audio_frame per usb_frame, so sometimes you need to transmit 44
  and somteims you need to transmit 45. So buffer sizes need to be 

  45 * 2 channels * 2 bytes = 180 bytes.
  
  For 48000, it's exactly 48000/1000 = 48 audio_frames/usb_frame.
  Unfortunately, the USB 1khz rate isn't exactly the same as the
  audio's 1khz rate, so you might sometimes need to transmit one extra
  'makeup' frame sometimes, depening on the synchronization method.
  
  In which case it would be
  (48+1) audio_frames * 2 channels * 2 bytes = 192 bytes
*/

#if AUDIO_SAMPLE_RATE == 44100
  #define AUDIO_BASEFRAMES (44)
// Send an extra frame every 10 usb frames */
  #define AUDIO_BASEFRAMES_EXTRA (10)
#elif AUDIO_SAMPLE_RATE == 48000
#define AUDIO_BASEFRAMES (48)
#elif AUDIO_SAMPLE_RATE == 32000
  #define AUDIO_BASEFRAMES (32)
#elif AUDIO_SAMPLE_RATE == 16000
  #define AUDIO_BASEFRAMES (16)
#elif AUDIO_SAMPLE_RATE ==  8000
  #define AUDIO_BASEFRAMES (8)
#else
#error UNSUPPORTED SAMPLE RATE, or you have specified a FLOAT.  Currently supported rates are 44100, 48000, 32000, 16000, 8000.   Set AUDIO_SAMPLE_RATE=<one of the above>
#endif

#ifndef AUDIO_BASEFRAMES_EXTRA
// the even multiples of 1kHz don't need any extra frames typically.
#define AUDIO_BASEFRAMES_EXTRA 0
#endif

// We still need a +1 to BASEFRAMES because we still need the ability to transmit
// one extra frame when the USB host is consuming frames too quickly.
#define AUDIO_TX_SIZE         ((AUDIO_BASEFRAMES+1) * USB_AUDIO_TX_CHANNELS * USB_AUDIO_BYTES_PER_SAMPLE)
#define AUDIO_RX_SIZE         ((AUDIO_BASEFRAMES+1) * USB_AUDIO_RX_CHANNELS * USB_AUDIO_BYTES_PER_SAMPLE)

#ifndef AUDIO_N_SAI1_RX_DATAPINS
#    define AUDIO_N_SAI1_RX_DATAPINS (1)
#endif

#ifndef AUDIO_N_SAI1_TX_DATAPINS
#    define AUDIO_N_SAI1_TX_DATAPINS (1)
#endif

#ifndef TDM_CHANNELS_PER_PIN
#define TDM_CHANNELS_PER_PIN (16)
#endif

#endif
