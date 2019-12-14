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

#include <avr/pgmspace.h>
#include <stdint.h>

#include "keylayouts.h"

#ifdef M
#undef M
#endif
#define M(n) ((n) & KEYCODE_MASK)

const KEYCODE_TYPE keycodes_ascii[] = {
        M(ASCII_20), M(ASCII_21), M(ASCII_22), M(ASCII_23),
        M(ASCII_24), M(ASCII_25), M(ASCII_26), M(ASCII_27),
        M(ASCII_28), M(ASCII_29), M(ASCII_2A), M(ASCII_2B),
        M(ASCII_2C), M(ASCII_2D), M(ASCII_2E), M(ASCII_2F),
        M(ASCII_30), M(ASCII_31), M(ASCII_32), M(ASCII_33),
        M(ASCII_34), M(ASCII_35), M(ASCII_36), M(ASCII_37),
        M(ASCII_38), M(ASCII_39), M(ASCII_3A), M(ASCII_3B),
        M(ASCII_3C), M(ASCII_3D), M(ASCII_3E), M(ASCII_3F),
        M(ASCII_40), M(ASCII_41), M(ASCII_42), M(ASCII_43),
        M(ASCII_44), M(ASCII_45), M(ASCII_46), M(ASCII_47),
        M(ASCII_48), M(ASCII_49), M(ASCII_4A), M(ASCII_4B),
        M(ASCII_4C), M(ASCII_4D), M(ASCII_4E), M(ASCII_4F),
        M(ASCII_50), M(ASCII_51), M(ASCII_52), M(ASCII_53),
        M(ASCII_54), M(ASCII_55), M(ASCII_56), M(ASCII_57),
        M(ASCII_58), M(ASCII_59), M(ASCII_5A), M(ASCII_5B),
        M(ASCII_5C), M(ASCII_5D), M(ASCII_5E), M(ASCII_5F),
        M(ASCII_60), M(ASCII_61), M(ASCII_62), M(ASCII_63),
        M(ASCII_64), M(ASCII_65), M(ASCII_66), M(ASCII_67),
        M(ASCII_68), M(ASCII_69), M(ASCII_6A), M(ASCII_6B),
        M(ASCII_6C), M(ASCII_6D), M(ASCII_6E), M(ASCII_6F),
        M(ASCII_70), M(ASCII_71), M(ASCII_72), M(ASCII_73),
        M(ASCII_74), M(ASCII_75), M(ASCII_76), M(ASCII_77),
        M(ASCII_78), M(ASCII_79), M(ASCII_7A), M(ASCII_7B),
        M(ASCII_7C), M(ASCII_7D), M(ASCII_7E), M(ASCII_7F)
};

#ifdef ISO_8859_1_A0
const KEYCODE_TYPE keycodes_iso_8859_1[] = {
        M(ISO_8859_1_A0), M(ISO_8859_1_A1), M(ISO_8859_1_A2), M(ISO_8859_1_A3),
        M(ISO_8859_1_A4), M(ISO_8859_1_A5), M(ISO_8859_1_A6), M(ISO_8859_1_A7),
        M(ISO_8859_1_A8), M(ISO_8859_1_A9), M(ISO_8859_1_AA), M(ISO_8859_1_AB),
        M(ISO_8859_1_AC), M(ISO_8859_1_AD), M(ISO_8859_1_AE), M(ISO_8859_1_AF),
        M(ISO_8859_1_B0), M(ISO_8859_1_B1), M(ISO_8859_1_B2), M(ISO_8859_1_B3),
        M(ISO_8859_1_B4), M(ISO_8859_1_B5), M(ISO_8859_1_B6), M(ISO_8859_1_B7),
        M(ISO_8859_1_B8), M(ISO_8859_1_B9), M(ISO_8859_1_BA), M(ISO_8859_1_BB),
        M(ISO_8859_1_BC), M(ISO_8859_1_BD), M(ISO_8859_1_BE), M(ISO_8859_1_BF),
        M(ISO_8859_1_C0), M(ISO_8859_1_C1), M(ISO_8859_1_C2), M(ISO_8859_1_C3),
        M(ISO_8859_1_C4), M(ISO_8859_1_C5), M(ISO_8859_1_C6), M(ISO_8859_1_C7),
        M(ISO_8859_1_C8), M(ISO_8859_1_C9), M(ISO_8859_1_CA), M(ISO_8859_1_CB),
        M(ISO_8859_1_CC), M(ISO_8859_1_CD), M(ISO_8859_1_CE), M(ISO_8859_1_CF),
        M(ISO_8859_1_D0), M(ISO_8859_1_D1), M(ISO_8859_1_D2), M(ISO_8859_1_D3),
        M(ISO_8859_1_D4), M(ISO_8859_1_D5), M(ISO_8859_1_D6), M(ISO_8859_1_D7),
        M(ISO_8859_1_D8), M(ISO_8859_1_D9), M(ISO_8859_1_DA), M(ISO_8859_1_DB),
        M(ISO_8859_1_DC), M(ISO_8859_1_DD), M(ISO_8859_1_DE), M(ISO_8859_1_DF),
        M(ISO_8859_1_E0), M(ISO_8859_1_E1), M(ISO_8859_1_E2), M(ISO_8859_1_E3),
        M(ISO_8859_1_E4), M(ISO_8859_1_E5), M(ISO_8859_1_E6), M(ISO_8859_1_E7),
        M(ISO_8859_1_E8), M(ISO_8859_1_E9), M(ISO_8859_1_EA), M(ISO_8859_1_EB),
        M(ISO_8859_1_EC), M(ISO_8859_1_ED), M(ISO_8859_1_EE), M(ISO_8859_1_EF),
        M(ISO_8859_1_F0), M(ISO_8859_1_F1), M(ISO_8859_1_F2), M(ISO_8859_1_F3),
        M(ISO_8859_1_F4), M(ISO_8859_1_F5), M(ISO_8859_1_F6), M(ISO_8859_1_F7),
        M(ISO_8859_1_F8), M(ISO_8859_1_F9), M(ISO_8859_1_FA), M(ISO_8859_1_FB),
        M(ISO_8859_1_FC), M(ISO_8859_1_FD), M(ISO_8859_1_FE), M(ISO_8859_1_FF)
};
#endif // ISO_8859_1_A0

