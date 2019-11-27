#include "imxrt.h"
#include "wiring.h"
#include "usb_dev.h"
#include "avr/pgmspace.h"

#include "debug/printf.h"

// from the linker
extern unsigned long _stextload;
extern unsigned long _stext;
extern unsigned long _etext;
extern unsigned long _sdataload;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _flexram_bank_config;
extern unsigned long _estack;

__attribute__ ((used, aligned(1024)))
void (* _VectorsRam[NVIC_NUM_INTERRUPTS+16])(void);

static void memory_copy(uint32_t *dest, const uint32_t *src, uint32_t *dest_end);
static void memory_clear(uint32_t *dest, uint32_t *dest_end);
static void configure_systick(void);
static void reset_PFD();
extern void systick_isr(void);
extern void pendablesrvreq_isr(void);
void configure_cache(void);
void unused_interrupt_vector(void);
void usb_pll_start();
extern void analog_init(void); // analog.c
extern void pwm_init(void); // pwm.c
extern void tempmon_init(void);  //tempmon.c
uint32_t set_arm_clock(uint32_t frequency); // clockspeed.c
extern void __libc_init_array(void); // C++ standard library


void startup_default_early_hook(void) {}
void startup_early_hook(void)		__attribute__ ((weak, alias("startup_default_early_hook")));
void startup_default_late_hook(void) {}
void startup_late_hook(void)		__attribute__ ((weak, alias("startup_default_late_hook")));
__attribute__((section(".startup"), optimize("no-tree-loop-distribute-patterns"), naked))
void ResetHandler(void)
{
	unsigned int i;

#if defined(__IMXRT1062__)
	IOMUXC_GPR_GPR17 = (uint32_t)&_flexram_bank_config;
	IOMUXC_GPR_GPR16 = 0x00000007;
	IOMUXC_GPR_GPR14 = 0x00AA0000;
	__asm__ volatile("mov sp, %0" : : "r" ((uint32_t)&_estack) : );
#endif
	// pin 13 - if startup crashes, use this to turn on the LED early for troubleshooting
	//IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5;
	//IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
	//IOMUXC_GPR_GPR27 = 0xFFFFFFFF;
	//GPIO7_GDIR |= (1<<3);
	//GPIO7_DR_SET = (1<<3); // digitalWrite(13, HIGH);

	// Initialize memory
	memory_copy(&_stext, &_stextload, &_etext);
	memory_copy(&_sdata, &_sdataload, &_edata);
	memory_clear(&_sbss, &_ebss);

	// enable FPU
	SCB_CPACR = 0x00F00000;

	// set up blank interrupt & exception vector table
	for (i=0; i < NVIC_NUM_INTERRUPTS + 16; i++) _VectorsRam[i] = &unused_interrupt_vector;
	for (i=0; i < NVIC_NUM_INTERRUPTS; i++) NVIC_SET_PRIORITY(i, 128);
	SCB_VTOR = (uint32_t)_VectorsRam;

	reset_PFD();
	
	// Configure clocks
	// TODO: make sure all affected peripherals are turned off!
	// PIT & GPT timers to run from 24 MHz clock (independent of CPU speed)
	CCM_CSCMR1 = (CCM_CSCMR1 & ~CCM_CSCMR1_PERCLK_PODF(0x3F)) | CCM_CSCMR1_PERCLK_CLK_SEL;
	// UARTs run from 24 MHz clock (works if PLL3 off or bypassed)
	CCM_CSCDR1 = (CCM_CSCDR1 & ~CCM_CSCDR1_UART_CLK_PODF(0x3F)) | CCM_CSCDR1_UART_CLK_SEL;

#if defined(__IMXRT1062__)
	// Use fast GPIO6, GPIO7, GPIO8, GPIO9
	IOMUXC_GPR_GPR26 = 0xFFFFFFFF;
	IOMUXC_GPR_GPR27 = 0xFFFFFFFF;
	IOMUXC_GPR_GPR28 = 0xFFFFFFFF;
	IOMUXC_GPR_GPR29 = 0xFFFFFFFF;
#endif

	// must enable PRINT_DEBUG_STUFF in debug/print.h
	printf_debug_init();
	printf("\n***********IMXRT Startup**********\n");
	printf("test %d %d %d\n", 1, -1234567, 3);

	configure_cache();
	configure_systick();
	usb_pll_start();	
	reset_PFD(); //TODO: is this really needed?
#ifdef F_CPU
	set_arm_clock(F_CPU);
#endif

	asm volatile("nop\n nop\n nop\n nop": : :"memory"); // why oh why?

	// Undo PIT timer usage by ROM startup
	CCM_CCGR1 |= CCM_CCGR1_PIT(CCM_CCGR_ON);
	PIT_MCR = 0;
	PIT_TCTRL0 = 0;
	PIT_TCTRL1 = 0;
	PIT_TCTRL2 = 0;
	PIT_TCTRL3 = 0;

	// initialize RTC
	if (!(SNVS_LPCR & SNVS_LPCR_SRTC_ENV)) {
		// if SRTC isn't running, start it with default Jan 1, 2019
		SNVS_LPSRTCLR = 1546300800u << 15;
		SNVS_LPSRTCMR = 1546300800u >> 17;
		SNVS_LPCR |= SNVS_LPCR_SRTC_ENV;
	}
	SNVS_HPCR |= SNVS_HPCR_RTC_EN | SNVS_HPCR_HP_TS;

	startup_early_hook();
	while (millis() < 20) ; // wait at least 20ms before starting USB
	usb_init();
	analog_init();
	pwm_init();
	tempmon_init();

	startup_late_hook();
	while (millis() < 300) ; // wait at least 300ms before calling user code
	//printf("before C++ constructors\n");
	__libc_init_array();
	//printf("after C++ constructors\n");
	//printf("before setup\n");
	setup();
	//printf("after setup\n");
	while (1) {
		//printf("loop\n");
		loop();
		yield();
	}
}




// ARM SysTick is used for most Ardiuno timing functions, delay(), millis(),
// micros().  SysTick can run from either the ARM core clock, or from an
// "external" clock.  NXP documents it as "24 MHz XTALOSC can be the external
// clock source of SYSTICK" (RT1052 ref manual, rev 1, page 411).  However,
// NXP actually hid an undocumented divide-by-240 circuit in the hardware, so
// the external clock is really 100 kHz.  We use this clock rather than the
// ARM clock, to allow SysTick to maintain correct timing even when we change
// the ARM clock to run at different speeds.
#define SYSTICK_EXT_FREQ 100000

extern volatile uint32_t systick_cycle_count;
static void configure_systick(void)
{
	_VectorsRam[14] = pendablesrvreq_isr;
	_VectorsRam[15] = systick_isr;
	SYST_RVR = (SYSTICK_EXT_FREQ / 1000) - 1;
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR_TICKINT | SYST_CSR_ENABLE;
	SCB_SHPR3 = 0x20200000;  // Systick, pendablesrvreq_isr = priority 32;
	ARM_DEMCR |= ARM_DEMCR_TRCENA;
	ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA; // turn on cycle counter
	systick_cycle_count = ARM_DWT_CYCCNT; // compiled 0, corrected w/1st systick
}


// concise defines for SCB_MPU_RASR and SCB_MPU_RBAR, ARM DDI0403E, pg 696
#define NOEXEC		SCB_MPU_RASR_XN
#define READONLY	SCB_MPU_RASR_AP(7)
#define READWRITE	SCB_MPU_RASR_AP(3)
#define NOACCESS	SCB_MPU_RASR_AP(0)
#define MEM_CACHE_WT	SCB_MPU_RASR_TEX(0) | SCB_MPU_RASR_C
#define MEM_CACHE_WB	SCB_MPU_RASR_TEX(0) | SCB_MPU_RASR_C | SCB_MPU_RASR_B
#define MEM_CACHE_WBWA	SCB_MPU_RASR_TEX(1) | SCB_MPU_RASR_C | SCB_MPU_RASR_B
#define MEM_NOCACHE	SCB_MPU_RASR_TEX(1)
#define DEV_NOCACHE	SCB_MPU_RASR_TEX(2)
#define SIZE_128K	(SCB_MPU_RASR_SIZE(16) | SCB_MPU_RASR_ENABLE)
#define SIZE_256K	(SCB_MPU_RASR_SIZE(17) | SCB_MPU_RASR_ENABLE)
#define SIZE_512K	(SCB_MPU_RASR_SIZE(18) | SCB_MPU_RASR_ENABLE)
#define SIZE_1M		(SCB_MPU_RASR_SIZE(19) | SCB_MPU_RASR_ENABLE)
#define SIZE_2M		(SCB_MPU_RASR_SIZE(20) | SCB_MPU_RASR_ENABLE)
#define SIZE_4M		(SCB_MPU_RASR_SIZE(21) | SCB_MPU_RASR_ENABLE)
#define SIZE_8M		(SCB_MPU_RASR_SIZE(22) | SCB_MPU_RASR_ENABLE)
#define SIZE_16M	(SCB_MPU_RASR_SIZE(23) | SCB_MPU_RASR_ENABLE)
#define SIZE_32M	(SCB_MPU_RASR_SIZE(24) | SCB_MPU_RASR_ENABLE)
#define SIZE_64M	(SCB_MPU_RASR_SIZE(25) | SCB_MPU_RASR_ENABLE)
#define REGION(n)	(SCB_MPU_RBAR_REGION(n) | SCB_MPU_RBAR_VALID)

FLASHMEM void configure_cache(void)
{
	//printf("MPU_TYPE = %08lX\n", SCB_MPU_TYPE);
	//printf("CCR = %08lX\n", SCB_CCR);

	// TODO: check if caches already active - skip?

	SCB_MPU_CTRL = 0; // turn off MPU

	SCB_MPU_RBAR = 0x00000000 | REGION(0); // ITCM
	SCB_MPU_RASR = MEM_NOCACHE | READWRITE | SIZE_512K;

	SCB_MPU_RBAR = 0x00200000 | REGION(1); // Boot ROM
	SCB_MPU_RASR = MEM_CACHE_WT | READONLY | SIZE_128K;

	SCB_MPU_RBAR = 0x20000000 | REGION(2); // DTCM
	SCB_MPU_RASR = MEM_NOCACHE | READWRITE | NOEXEC | SIZE_512K;

	SCB_MPU_RBAR = 0x20200000 | REGION(3); // RAM (AXI bus)
	SCB_MPU_RASR = MEM_CACHE_WBWA | READWRITE | NOEXEC | SIZE_1M;

	SCB_MPU_RBAR = 0x40000000 | REGION(4); // Peripherals
	SCB_MPU_RASR = DEV_NOCACHE | READWRITE | NOEXEC | SIZE_64M;

	SCB_MPU_RBAR = 0x60000000 | REGION(5); // QSPI Flash
	SCB_MPU_RASR = MEM_CACHE_WBWA | READONLY | SIZE_16M;

	// TODO: 32 byte sub-region at 0x00000000 with NOACCESS, to trap NULL pointer deref
	// TODO: protect access to power supply config
	// TODO: 32 byte sub-region at end of .bss section with NOACCESS, to trap stack overflow

	SCB_MPU_CTRL = SCB_MPU_CTRL_ENABLE;

	// cache enable, ARM DDI0403E, pg 628
	asm("dsb");
	asm("isb");
	SCB_CACHE_ICIALLU = 0;

	asm("dsb");
	asm("isb");
	SCB_CCR |= (SCB_CCR_IC | SCB_CCR_DC);
}


FLASHMEM void usb_pll_start()
{
	while (1) {
		uint32_t n = CCM_ANALOG_PLL_USB1; // pg 759
		printf("CCM_ANALOG_PLL_USB1=%08lX\n", n);
		if (n & CCM_ANALOG_PLL_USB1_DIV_SELECT) {
			printf("  ERROR, 528 MHz mode!\n"); // never supposed to use this mode!
			CCM_ANALOG_PLL_USB1_CLR = 0xC000;			// bypass 24 MHz
			CCM_ANALOG_PLL_USB1_SET = CCM_ANALOG_PLL_USB1_BYPASS;	// bypass
			CCM_ANALOG_PLL_USB1_CLR = CCM_ANALOG_PLL_USB1_POWER |	// power down
				CCM_ANALOG_PLL_USB1_DIV_SELECT |		// use 480 MHz
				CCM_ANALOG_PLL_USB1_ENABLE |			// disable
				CCM_ANALOG_PLL_USB1_EN_USB_CLKS;		// disable usb
			continue;
		}
		if (!(n & CCM_ANALOG_PLL_USB1_ENABLE)) {
			printf("  enable PLL\n");
			// TODO: should this be done so early, or later??
			CCM_ANALOG_PLL_USB1_SET = CCM_ANALOG_PLL_USB1_ENABLE;
			continue;
		}
		if (!(n & CCM_ANALOG_PLL_USB1_POWER)) {
			printf("  power up PLL\n");
			CCM_ANALOG_PLL_USB1_SET = CCM_ANALOG_PLL_USB1_POWER;
			continue;
		}
		if (!(n & CCM_ANALOG_PLL_USB1_LOCK)) {
			printf("  wait for lock\n");
			continue;
		}
		if (n & CCM_ANALOG_PLL_USB1_BYPASS) {
			printf("  turn off bypass\n");
			CCM_ANALOG_PLL_USB1_CLR = CCM_ANALOG_PLL_USB1_BYPASS;
			continue;
		}
		if (!(n & CCM_ANALOG_PLL_USB1_EN_USB_CLKS)) {
			printf("  enable USB clocks\n");
			CCM_ANALOG_PLL_USB1_SET = CCM_ANALOG_PLL_USB1_EN_USB_CLKS;
			continue;
		}
		return; // everything is as it should be  :-)
	}
}

FLASHMEM void reset_PFD()
{	
	//Reset PLL2 PFDs, set default frequencies:
	CCM_ANALOG_PFD_528_SET = (1 << 31) | (1 << 23) | (1 << 15) | (1 << 7);
	CCM_ANALOG_PFD_528 = 0x2018101B; // PFD0:352, PFD1:594, PFD2:396, PFD3:297 MHz 	
	//PLL3:
	CCM_ANALOG_PFD_480_SET = (1 << 31) | (1 << 23) | (1 << 15) | (1 << 7);	
	CCM_ANALOG_PFD_480 = 0x13110D0C; // PFD0:720, PFD1:664, PFD2:508, PFD3:454 MHz
}

// Stack frame
//  xPSR
//  ReturnAddress
//  LR (R14) - typically FFFFFFF9 for IRQ or Exception
//  R12
//  R3
//  R2
//  R1
//  R0
// Code from :: https://community.nxp.com/thread/389002
__attribute__((naked))
void unused_interrupt_vector(void)
{
  __asm( ".syntax unified\n"
         "MOVS R0, #4 \n"
         "MOV R1, LR \n"
         "TST R0, R1 \n"
         "BEQ _MSP \n"
         "MRS R0, PSP \n"
         "B HardFault_HandlerC \n"
         "_MSP: \n"
         "MRS R0, MSP \n"
         "B HardFault_HandlerC \n"
         ".syntax divided\n") ;
}

__attribute__((weak))
void HardFault_HandlerC(unsigned int *hardfault_args)
{
  volatile unsigned int nn ;
#ifdef PRINT_DEBUG_STUFF
  volatile unsigned int stacked_r0 ;
  volatile unsigned int stacked_r1 ;
  volatile unsigned int stacked_r2 ;
  volatile unsigned int stacked_r3 ;
  volatile unsigned int stacked_r12 ;
  volatile unsigned int stacked_lr ;
  volatile unsigned int stacked_pc ;
  volatile unsigned int stacked_psr ;
  volatile unsigned int _CFSR ;
  volatile unsigned int _HFSR ;
  volatile unsigned int _DFSR ;
  volatile unsigned int _AFSR ;
  volatile unsigned int _BFAR ;
  volatile unsigned int _MMAR ;
  volatile unsigned int addr ;

  stacked_r0 = ((unsigned int)hardfault_args[0]) ;
  stacked_r1 = ((unsigned int)hardfault_args[1]) ;
  stacked_r2 = ((unsigned int)hardfault_args[2]) ;
  stacked_r3 = ((unsigned int)hardfault_args[3]) ;
  stacked_r12 = ((unsigned int)hardfault_args[4]) ;
  stacked_lr = ((unsigned int)hardfault_args[5]) ;
  stacked_pc = ((unsigned int)hardfault_args[6]) ;
  stacked_psr = ((unsigned int)hardfault_args[7]) ;
  // Configurable Fault Status Register
  // Consists of MMSR, BFSR and UFSR
  //(n & ( 1 << k )) >> k
  _CFSR = (*((volatile unsigned int *)(0xE000ED28))) ;  
  // Hard Fault Status Register
  _HFSR = (*((volatile unsigned int *)(0xE000ED2C))) ;
  // Debug Fault Status Register
  _DFSR = (*((volatile unsigned int *)(0xE000ED30))) ;
  // Auxiliary Fault Status Register
  _AFSR = (*((volatile unsigned int *)(0xE000ED3C))) ;
  // Read the Fault Address Registers. These may not contain valid values.
  // Check BFARVALID/MMARVALID to see if they are valid values
  // MemManage Fault Address Register
  _MMAR = (*((volatile unsigned int *)(0xE000ED34))) ;
  // Bus Fault Address Register
  _BFAR = (*((volatile unsigned int *)(0xE000ED38))) ;
  //__asm("BKPT #0\n") ; // Break into the debugger // NO Debugger here.

  asm volatile("mrs %0, ipsr\n" : "=r" (addr)::);
  printf("\nFault irq %d\n", addr & 0x1FF);
  printf(" stacked_r0 ::  %x\n", stacked_r0);
  printf(" stacked_r1 ::  %x\n", stacked_r1);
  printf(" stacked_r2 ::  %x\n", stacked_r2);
  printf(" stacked_r3 ::  %x\n", stacked_r3);
  printf(" stacked_r12 ::  %x\n", stacked_r12);
  printf(" stacked_lr ::  %x\n", stacked_lr);
  printf(" stacked_pc ::  %x\n", stacked_pc);
  printf(" stacked_psr ::  %x\n", stacked_psr);
  printf(" _CFSR ::  %x\n", _CFSR);
 
  if(_CFSR > 0){
	  //Memory Management Faults
	  if((_CFSR & 1) == 1){
		printf("      (IACCVIOL) Instruction Access Violation\n");
	  } else  if(((_CFSR & (0x02))>>1) == 1){
		printf("      (DACCVIOL) Data Access Violation\n");
	  } else if(((_CFSR & (0x08))>>3) == 1){
		printf("      (MUNSTKERR) MemMange Fault on Unstacking\n");
	  } else if(((_CFSR & (0x10))>>4) == 1){
		printf("      (MSTKERR) MemMange Fault on stacking\n");
	  } else if(((_CFSR & (0x20))>>5) == 1){
		printf("      (MLSPERR) MemMange Fault on FP Lazy State\n");
	  }
	  if(((_CFSR & (0x80))>>7) == 1){
		printf("      (MMARVALID) MemMange Fault Address Valid\n");
	  }
	  //Bus Fault Status Register
	  if(((_CFSR & 0x100)>>8) == 1){
		printf("      (IBUSERR) Instruction Bus Error\n");
	  } else  if(((_CFSR & (0x200))>>9) == 1){
		printf("      (PRECISERR) Data bus error(address in BFAR)\n");
	  } else if(((_CFSR & (0x400))>>10) == 1){
		printf("      (IMPRECISERR) Data bus error but address not related to instruction\n");
	  } else if(((_CFSR & (0x800))>>11) == 1){
		printf("      (UNSTKERR) Bus Fault on unstacking for a return from exception \n");
	  } else if(((_CFSR & (0x1000))>>12) == 1){
		printf("      (STKERR) Bus Fault on stacking for exception entry\n");
	  } else if(((_CFSR & (0x2000))>>13) == 1){
		printf("      (LSPERR) Bus Fault on FP lazy state preservation\n");
	  }
	  if(((_CFSR & (0x8000))>>15) == 1){
		printf("      (BFARVALID) Bus Fault Address Valid\n");
	  }  
	  //Usuage Fault Status Register
	  if(((_CFSR & 0x10000)>>16) == 1){
		printf("      (UNDEFINSTR) Undefined instruction\n");
	  } else  if(((_CFSR & (0x20000))>>17) == 1){
		printf("      (INVSTATE) Instruction makes illegal use of EPSR)\n");
	  } else if(((_CFSR & (0x40000))>>18) == 1){
		printf("      (INVPC) Usage fault: invalid EXC_RETURN\n");
	  } else if(((_CFSR & (0x80000))>>19) == 1){
		printf("      (NOCP) No Coprocessor \n");
	  } else if(((_CFSR & (0x1000000))>>24) == 1){
		printf("      (UNALIGNED) Unaligned access UsageFault\n");
	  } else if(((_CFSR & (0x2000000))>>25) == 1){
		printf("      (DIVBYZERO) Divide by zero\n");
	  }
  }
  printf(" _HFSR ::  %x\n", _HFSR);
  if(_HFSR > 0){
	  //Memory Management Faults
	  if(((_HFSR & (0x02))>>1) == 1){
		printf("      (VECTTBL) Bus Fault on Vec Table Read\n");
	  } else if(((_HFSR & (0x40000000))>>30) == 1){
		printf("      (FORCED) Forced Hard Fault\n");
	  } else if(((_HFSR & (0x80000000))>>31) == 31){
		printf("      (DEBUGEVT) Reserved for Debug\n");
	  } 
  }
  printf(" _DFSR ::  %x\n", _DFSR);
  printf(" _AFSR ::  %x\n", _AFSR);
  printf(" _BFAR ::  %x\n", _BFAR);
  printf(" _MMAR ::  %x\n", _MMAR);
#endif

  IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5; // pin 13
  IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
  GPIO2_GDIR |= (1 << 3);
  GPIO2_DR_SET = (1 << 3);
  GPIO2_DR_CLEAR = (1 << 3); //digitalWrite(13, LOW);

  if ( F_CPU_ACTUAL >= 600000000 )
    set_arm_clock(300000000);

  while (1)
  {
    GPIO2_DR_SET = (1 << 3); //digitalWrite(13, HIGH);
    // digitalWrite(13, HIGH);
    for (nn = 0; nn < 2000000/2; nn++) ;
    GPIO2_DR_CLEAR = (1 << 3); //digitalWrite(13, LOW);
    // digitalWrite(13, LOW);
    for (nn = 0; nn < 18000000/2; nn++) ;
  }
}

__attribute__((weak))
void userDebugDump(){
	volatile unsigned int nn;
	printf("\nuserDebugDump() in startup.c ___ \n");

  while (1)
  {
    GPIO2_DR_SET = (1 << 3); //digitalWrite(13, HIGH);
    // digitalWrite(13, HIGH);
    for (nn = 0; nn < 2000000; nn++) ;
    GPIO2_DR_CLEAR = (1 << 3); //digitalWrite(13, LOW);
	// digitalWrite(13, LOW);
    for (nn = 0; nn < 18000000; nn++) ;
    GPIO2_DR_SET = (1 << 3); //digitalWrite(13, HIGH);
    // digitalWrite(13, HIGH);
    for (nn = 0; nn < 20000000; nn++) ;
    GPIO2_DR_CLEAR = (1 << 3); //digitalWrite(13, LOW);
	// digitalWrite(13, LOW);
    for (nn = 0; nn < 10000000; nn++) ;
  }
}

__attribute__((weak))
void PJRCunused_interrupt_vector(void)
{
	// TODO: polling Serial to complete buffered transmits
#ifdef PRINT_DEBUG_STUFF
	uint32_t addr;
	asm volatile("mrs %0, ipsr\n" : "=r" (addr)::);
	printf("\nirq %d\n", addr & 0x1FF);
	asm("ldr %0, [sp, #52]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #48]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #44]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #40]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #36]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #33]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #34]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #28]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #24]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #20]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #16]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #12]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #8]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #4]" : "=r" (addr) ::);
	printf(" %x\n", addr);
	asm("ldr %0, [sp, #0]" : "=r" (addr) ::);
	printf(" %x\n", addr);
#endif
#if 1
	if ( F_CPU_ACTUAL >= 600000000 )
		set_arm_clock(100000000);
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5; // pin 13
	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
	GPIO2_GDIR |= (1<<3);
	GPIO2_DR_SET = (1<<3);
	while (1) {
		volatile uint32_t n;
		GPIO2_DR_SET = (1<<3); //digitalWrite(13, HIGH);
		for (n=0; n < 2000000/6; n++) ;
		GPIO2_DR_CLEAR = (1<<3); //digitalWrite(13, LOW);
		for (n=0; n < 1500000/6; n++) ;
	}
#else
	if ( F_CPU_ACTUAL >= 600000000 )
		set_arm_clock(100000000);
	while (1) asm ("WFI");
#endif
}

__attribute__((section(".startup"), optimize("no-tree-loop-distribute-patterns")))
static void memory_copy(uint32_t *dest, const uint32_t *src, uint32_t *dest_end)
{
	if (dest == src) return;
	while (dest < dest_end) {
		*dest++ = *src++;
	}
}

__attribute__((section(".startup"), optimize("no-tree-loop-distribute-patterns")))
static void memory_clear(uint32_t *dest, uint32_t *dest_end)
{
	while (dest < dest_end) {
		*dest++ = 0;
	}
}



// syscall functions need to be in the same C file as the entry point "ResetVector"
// otherwise the linker will discard them in some cases.

#include <errno.h>

// from the linker script
extern unsigned long _heap_start;
extern unsigned long _heap_end;

char *__brkval = (char *)&_heap_start;

void * _sbrk(int incr)
{
        char *prev = __brkval;
        if (incr != 0) {
                if (prev + incr > (char *)&_heap_end) {
                        errno = ENOMEM;
                        return (void *)-1;
                }
                __brkval = prev + incr;
        }
        return prev;
}

__attribute__((weak))
int _read(int file, char *ptr, int len)
{
	return 0;
}

__attribute__((weak))
int _close(int fd)
{
	return -1;
}

#include <sys/stat.h>

__attribute__((weak))
int _fstat(int fd, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

__attribute__((weak))
int _isatty(int fd)
{
	return 1;
}

__attribute__((weak))
int _lseek(int fd, long long offset, int whence)
{
	return -1;
}

__attribute__((weak))
void _exit(int status)
{
	while (1) asm ("WFI");
}

__attribute__((weak))
void __cxa_pure_virtual()
{
	while (1) asm ("WFI");
}

__attribute__((weak))
int __cxa_guard_acquire (char *g)
{
	return !(*g);
}

__attribute__((weak))
void __cxa_guard_release(char *g)
{
	*g = 1;
}

__attribute__((weak))
void abort(void)
{
	while (1) asm ("WFI");
}
