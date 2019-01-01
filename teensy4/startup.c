#include "imxrt.h"
#include "wiring.h"
#include "usb_dev.h"

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


__attribute__ ((used, aligned(1024)))
void (* _VectorsRam[160+16])(void);

static void memory_copy(uint32_t *dest, const uint32_t *src, uint32_t *dest_end);
static void memory_clear(uint32_t *dest, uint32_t *dest_end);
static void configure_systick(void);
extern void systick_isr(void);
extern void pendablesrvreq_isr(void);
void configure_cache(void);
void unused_interrupt_vector(void);
void usb_pll_start();
extern void analog_init(void);
extern void pwm_init(void);
uint32_t set_arm_clock(uint32_t frequency);


__attribute__((section(".startup"), optimize("no-tree-loop-distribute-patterns")))
void ResetHandler(void)
{
	unsigned int i;

	//force the stack to begin at some arbitrary location
	//__asm__ volatile("mov sp, %0" : : "r" (0x20010000) : );

	// pin 13 - if startup crashes, use this to turn on the LED early for troubleshooting
	//IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5;
	//IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
	//GPIO2_GDIR |= (1<<3);
	//GPIO2_DR_SET = (1<<3); // digitalWrite(13, HIGH);

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

	// Configure clocks
	// TODO: make sure all affected peripherals are turned off!
	// PIT & GPT timers to run from 24 MHz clock (independent of CPU speed)
	CCM_CSCMR1 = (CCM_CSCMR1 & ~CCM_CSCMR1_PERCLK_PODF(0x3F)) | CCM_CSCMR1_PERCLK_CLK_SEL;
	// UARTs run from 24 MHz clock (works if PLL3 off or bypassed)
	CCM_CSCDR1 = (CCM_CSCDR1 & ~CCM_CSCDR1_UART_CLK_PODF(0x3F)) | CCM_CSCDR1_UART_CLK_SEL;

	// must enable PRINT_DEBUG_STUFF in debug/print.h
	printf_debug_init();
	printf("\n***********IMXRT Startup**********\n");
	printf("test %d %d %d\n", 1, -1234567, 3);

	configure_cache();
	configure_systick();
	usb_pll_start();

	set_arm_clock(600000000);
	//set_arm_clock(984000000); Ludicrous Speed

	uint32_t armpll = CCM_ANALOG_PLL_ARM;
	uint32_t armdiv = CCM_CACRR;
	uint32_t cbcdr = CCM_CBCDR;
	uint32_t cbcmr = CCM_CBCMR;

	printf("ARM PLL = %u MHz\n", (armpll & 0x7F) * 12);
	printf("ARM divisor = %u\n", armdiv + 1);
	printf("AHB divisor = %u\n", ((cbcdr >> 10) & 7) + 1);
	printf("IPG divisor = %u\n", ((cbcdr >> 8) & 3) + 1);

	while (millis() < 20) ; // wait at least 20ms before starting USB
	usb_init();
	analog_init();
	pwm_init();

	while (millis() < 300) ; // wait at least 300ms before calling user code
	printf("before C++ constructors\n");
	__libc_init_array();
	printf("after C++ constructors\n");
	printf("before setup\n");
	setup();
	printf("after setup\n");
	while (1) {
		//printf("loop\n");
		loop();
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

static void configure_systick(void)
{
	_VectorsRam[14] = pendablesrvreq_isr;
	_VectorsRam[15] = systick_isr;
	SYST_RVR = (SYSTICK_EXT_FREQ / 1000) - 1;
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR_TICKINT | SYST_CSR_ENABLE;
	SCB_SHPR3 = 0x20000000;  // Systick = priority 32
	ARM_DEMCR |= ARM_DEMCR_TRCENA;
	ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA; // turn on cycle counter
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

__attribute__((section(".progmem")))
void configure_cache(void)
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


__attribute__((section(".progmem")))
void usb_pll_start()
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


// Stack frame
//  xPSR
//  ReturnAddress
//  LR (R14) - typically FFFFFFF9 for IRQ or Exception
//  R12
//  R3
//  R2
//  R1
//  R0
void unused_interrupt_vector(void)
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
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5; // pin 13
	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
	GPIO2_GDIR |= (1<<3);
	GPIO2_DR_SET = (1<<3);
	while (1) {
		volatile uint32_t n;
		GPIO2_DR_SET = (1<<3); //digitalWrite(13, HIGH);
		for (n=0; n < 2000000; n++) ;
		GPIO2_DR_CLEAR = (1<<3); //digitalWrite(13, LOW);
		for (n=0; n < 1500000; n++) ;
	}
#else
	while (1) {
	}
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
	while (1);
}

__attribute__((weak))
void __cxa_pure_virtual()
{
	while (1);
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
	while (1) ;
}

