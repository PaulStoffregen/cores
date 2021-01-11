/* This library code is placed under the MIT license
   Copyright (c) 2020 Frank Bösing

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef SHOW_HARDFAULTS
#define SHOW_HARDFAULTS 1
#endif

#ifndef HARDFAULTSOUT
#define HARDFAULTSOUT Serial
#endif

#include <Arduino.h>

#if SHOW_HARDFAULTS

extern unsigned long _ebss;
	
static const uint32_t _marker = 0xfb2112fb;

typedef struct
{
  uint32_t marker;
  uint32_t ipsr;
  uint32_t cfsr;
  uint32_t hfsr;
  //uint32_t dfsr;
  uint32_t mmar;
  uint32_t bfar;
  //uint32_t afsr;
  uint32_t return_address;
  uint32_t xpsr;
  bool temperature;
  uint8_t unusedISR;
} _tRegInfo;

DMAMEM _tRegInfo _sRegInfo;

typedef struct {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t return_address;
  uint32_t xpsr;
} _tContextStateFrame;

extern "C" {
	
  FASTRUN __attribute__((used, noreturn, optimize("O0")))
  static void _hardfault_handler_c(_tContextStateFrame *frame) {

    //Read these both first:
    _sRegInfo.mmar = (*((volatile uint32_t *)(0xE000ED34)));     // MemManage Fault Address Register
    _sRegInfo.bfar = (*((volatile uint32_t *)(0xE000ED38)));     // Bus Fault Address Register
    asm volatile("mrs %0, ipsr\n" : "=r" (_sRegInfo.ipsr)::);
    volatile uint32_t *cfsr = (volatile uint32_t *)0xE000ED28;  // Configurable Fault Status Register

    _sRegInfo.return_address = frame->return_address;
    _sRegInfo.xpsr = frame->xpsr;

    _sRegInfo.hfsr = (*((volatile uint32_t *)(0xE000ED2C)));     // Hard Fault Status Register
    //_sRegInfo.dfsr = (*((volatile uint32_t *)(0xE000ED30)));     // Debug Fault Status Register
    //_sRegInfo.afsr = (*((volatile uint32_t *)(0xE000ED3C)));     // Auxiliary Fault Status Register
    _sRegInfo.cfsr = *cfsr;
    *cfsr |= *cfsr;

    _sRegInfo.temperature = 0;
    _sRegInfo.unusedISR = 0;
    _sRegInfo.marker = _marker;
    arm_dcache_flush((void*)&_sRegInfo, sizeof(_tRegInfo));

    //Reset:
    volatile uint32_t *aircr = (volatile uint32_t *)0xE000ED0C;
    *aircr = (0x05FA << 16) | 0x1 << 2;
    asm volatile("dsb");
    while (1) asm ("WFI");

  }

  FASTRUN __attribute__((naked, used))
  static void _hardfault_interrupt_vector(void)
  {
    __asm( ".syntax unified\n"
           "MOVS R0, #4 \n"
           "MOV R1, LR \n"
           "TST R0, R1 \n"
           "BEQ _MSP \n"
           "MRS R0, PSP \n"
           "B _hardfault_handler_c \n"
           "_MSP: \n"
           "MRS R0, MSP \n"
           "B _hardfault_handler_c \n"
           ".syntax divided\n") ;
  }

  FLASHMEM
  static void _fault_temp_isr(void) {
    _sRegInfo.temperature = true;
    _sRegInfo.unusedISR = 0;
    _sRegInfo.marker = _marker;
    arm_dcache_flush((void*)&_sRegInfo, sizeof(_tRegInfo));
    volatile uint32_t *aircr = (volatile uint32_t *)0xE000ED0C;
    *aircr = (0x05FA << 16) | 0x1 << 2;
    while (1) asm ("WFI");
  }

  FLASHMEM 
  void _unused_isr(int8_t isr) {
    _sRegInfo.temperature = 0;
    _sRegInfo.unusedISR = isr;
    _sRegInfo.marker = _marker;
    arm_dcache_flush((void*)&_sRegInfo, sizeof(_tRegInfo));
    volatile uint32_t *aircr = (volatile uint32_t *)0xE000ED0C;
    *aircr = (0x05FA << 16) | 0x1 << 2;
    while (1) asm ("WFI");
  }
  
} //extern "C"

FLASHMEM
static bool _show_hardfault(void)
{

  arm_dcache_delete((void*)&_sRegInfo, sizeof(_tRegInfo));
  bool found = (_sRegInfo.marker == _marker);
  if (!found) return false;

  Serial.begin(9600);

#if (HARDFAULTSOUT==Serial)
  while (!Serial && millis() < 3000) {}
#endif

  if (_sRegInfo.temperature) {
    HARDFAULTSOUT.println("Temperature Panic.\n Power down.\n");
    HARDFAULTSOUT.flush();
    delay(5);
    IOMUXC_GPR_GPR16 = 0x00000007;
    SNVS_LPCR |= SNVS_LPCR_TOP; //Switch off now
    while (1) asm ("wfi");
  }

  uint32_t isr = _sRegInfo.unusedISR;
  if (isr > 0) {
	HARDFAULTSOUT.print("Fault.\nUnused ISR No. ");
	HARDFAULTSOUT.print(isr);
	HARDFAULTSOUT.print(" called.");
  } else {

  HARDFAULTSOUT.print("Hardfault.\nReturn Address: 0x");
  HARDFAULTSOUT.println(_sRegInfo.return_address, HEX);

  //const bool non_usage_fault_occurred = (sRegInfo.cfsr & ~0xffff0000) != 0;
  const bool faulted_from_exception = ((_sRegInfo.xpsr & 0xFF) != 0);
  //if (non_usage_fault_occurred) HARDFAULTSOUT.println("non usage fault");
  if (faulted_from_exception) HARDFAULTSOUT.printf("Faulted from exception.\n");

  uint32_t _CFSR = _sRegInfo.cfsr;
  if (_CFSR > 0) {

    if ((_CFSR & 0xff) > 0) {
      //Memory Management Faults
      if ((_CFSR & 1) == 1) {
        HARDFAULTSOUT.println("\t(IACCVIOL) Instruction Access Violation");
      } else  if (((_CFSR & (0x02)) >> 1) == 1) {
        HARDFAULTSOUT.println("\t(DACCVIOL) Data Access Violation");
      } else if (((_CFSR & (0x08)) >> 3) == 1) {
        HARDFAULTSOUT.println("\t(MUNSTKERR) MemMange Fault on Unstacking");
      } else if (((_CFSR & (0x10)) >> 4) == 1) {
        HARDFAULTSOUT.println("\t(MSTKERR) MemMange Fault on stacking");
      } else if (((_CFSR & (0x20)) >> 5) == 1) {
        HARDFAULTSOUT.println("\t(MLSPERR) MemMange Fault on FP Lazy State");
      }
      if (((_CFSR & (0x80)) >> 7) == 1) {
        HARDFAULTSOUT.print("\t(MMARVALID) Accessed Address: 0x");
        HARDFAULTSOUT.print(_sRegInfo.mmar, HEX);
        if (_sRegInfo.mmar < 32) HARDFAULTSOUT.print(" (nullptr)");
        if ((_sRegInfo.mmar >= (uint32_t)&_ebss) && (_sRegInfo.mmar < (uint32_t)&_ebss + 32))
          HARDFAULTSOUT.print(" (Stack problem)\n\tCheck for stack overflows, array bounds, etc.");
        HARDFAULTSOUT.println();
      }
    }

    //Bus Fault Status Register BFSR
    if (((_CFSR & 0x100) >> 8) == 1) {
      HARDFAULTSOUT.println("\t(IBUSERR) Instruction Bus Error");
    } else  if (((_CFSR & (0x200)) >> 9) == 1) {
      HARDFAULTSOUT.println("\t(PRECISERR) Data bus error(address in BFAR)");
    } else if (((_CFSR & (0x400)) >> 10) == 1) {
      HARDFAULTSOUT.println("\t(IMPRECISERR) Data bus error but address not related to instruction");
    } else if (((_CFSR & (0x800)) >> 11) == 1) {
      HARDFAULTSOUT.println("\t(UNSTKERR) Bus Fault on unstacking for a return from exception");
    } else if (((_CFSR & (0x1000)) >> 12) == 1) {
      HARDFAULTSOUT.println("\t(STKERR) Bus Fault on stacking for exception entry");
    } else if (((_CFSR & (0x2000)) >> 13) == 1) {
      HARDFAULTSOUT.println("\t(LSPERR) Bus Fault on FP lazy state preservation");
    }
    if (((_CFSR & (0x8000)) >> 15) == 1) {
      HARDFAULTSOUT.print("\t(BFARVALID) Accessed Address: 0x");
      HARDFAULTSOUT.println(_sRegInfo.bfar, HEX);
    }


    //Usage Fault Status Register UFSR
    if (((_CFSR & 0x10000) >> 16) == 1) {
      HARDFAULTSOUT.println("\t(UNDEFINSTR) Undefined instruction");
    } else  if (((_CFSR & (0x20000)) >> 17) == 1) {
      HARDFAULTSOUT.println("\t(INVSTATE) Instruction makes illegal use of EPSR)");
    } else if (((_CFSR & (0x40000)) >> 18) == 1) {
      HARDFAULTSOUT.println("\t(INVPC) Usage fault: invalid EXC_RETURN");
    } else if (((_CFSR & (0x80000)) >> 19) == 1) {
      HARDFAULTSOUT.println("\t(NOCP) No Coprocessor");
    } else if (((_CFSR & (0x1000000)) >> 24) == 1) {
      HARDFAULTSOUT.println("\t(UNALIGNED) Unaligned access UsageFault");
    } else if (((_CFSR & (0x2000000)) >> 25) == 1) {
      HARDFAULTSOUT.println("\t(DIVBYZERO) Divide by zero");
    }
  }

  uint32_t _HFSR = _sRegInfo.hfsr;
  if (_HFSR > 0) {
    //Memory Management Faults
    if (((_HFSR & (0x02)) >> 1) == 1) {
      HARDFAULTSOUT.println("\t(VECTTBL) Bus Fault on Vec Table Read");
    } /* else if (((_HFSR & (0x40000000)) >> 30) == 1) {
       HARDFAULTSOUT.println("\t(FORCED) Forced Hard Fault");
    } else if (((_HFSR & (0x80000000)) >> 31) == 31) {
       HARDFAULTSOUT.println("\t(DEBUGEVT) Reserved for Debug");
    } */
  }
  }
  _sRegInfo.marker = 0;
  arm_dcache_flush_delete((void*)&_sRegInfo, 32);
  return true;
}

extern "C" {
  FLASHMEM
  void _hardfaults_init(void) {
    attachInterruptVector(IRQ_TEMPERATURE_PANIC, &_fault_temp_isr);
    _VectorsRam[3] = _hardfault_interrupt_vector;

    //SCB_CCR = 0x10; //Enable "Div By Zero" Hardfaults
    
    if (_show_hardfault()) delay(10000);
  }
}

#else
extern "C" void _hardfaults_init() {};
extern "C" void _unused_isr(int8_t isr) {};
#endif
