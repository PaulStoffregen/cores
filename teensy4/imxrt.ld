MEMORY
{
	ITCM (rwx):  ORIGIN = 0x00000000, LENGTH = 128K
	DTCM (rwx):  ORIGIN = 0x20000000, LENGTH = 128K
	RAM (rwx):   ORIGIN = 0x20200000, LENGTH = 256K
	FLASH (rwx): ORIGIN = 0x60000000, LENGTH = 1536K
}

ENTRY(ImageVectorTable)

SECTIONS
{
	.text.progmem : {
		KEEP(*(.flashconfig))
		FILL(0xFF)
		. = ORIGIN(FLASH) + 0x1000;
		KEEP(*(.ivt))
		KEEP(*(.bootdata))
		KEEP(*(.vectors))
		KEEP(*(.startup))
		*(.progmem*)
                . = ALIGN(4);
/*
		TODO: how much of this C++ stuff is really needed?
                KEEP(*(.init))
                . = ALIGN(4);
                __preinit_array_start = .;
                KEEP (*(.preinit_array))
                __preinit_array_end = .;
                __init_array_start = .;
                KEEP (*(SORT(.init_array.*)))
                KEEP (*(.init_array))
                __init_array_end = .;
*/
		. = ALIGN(16);
	} > FLASH

	.text : {
		. = . + 32; /* MPU to trap NULL pointer deref */
		*(.fastrun)
		*(.text*)
		. = ALIGN(16);
	} > ITCM  AT> FLASH

	.data : {
		*(.rodata*)
		*(.data*)
		. = ALIGN(16);
	} > DTCM  AT> FLASH

	.bss : {
		*(.bss*)
		*(COMMON)
		. = ALIGN(32);
		. = . + 32; /* MPU to trap stack overflow */
	} > DTCM

	.bss.dma : {
		*(.dmabuffers)
		. = ALIGN(16);
	} > RAM

	_stext = ADDR(.text);
	_etext = ADDR(.text) + SIZEOF(.text);
	_stextload = LOADADDR(.text);

	_sdata = ADDR(.data);
	_edata = ADDR(.data) + SIZEOF(.data);
	_sdataload = LOADADDR(.data);

	_estack = ORIGIN(DTCM) + LENGTH(DTCM);

	_sbss = ADDR(.bss);
	_ebss = ADDR(.bss) + SIZEOF(.bss);

	_flashimagelen = SIZEOF(.text.progmem) + SIZEOF(.text) + SIZEOF(.data);
	_teensy_model_identifier = 0x23;

	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }

}
