CPUARCH = cortex-m7
DEFS = -DUSB_SERIAL -D__IMXRT1052__ -DTEENSYDUINO=145 -DARDUINO=10808 -DF_CPU=396000000 -DLAYOUT_US_ENGLISH
SECTIONS = -ffunction-sections -fdata-sections
CPPFLAGS = -Wall -g -O2 $(SECTIONS) -mcpu=$(CPUARCH) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -I. $(DEFS)
CXXFLAGS = -std=gnu++14 -felide-constructors -fno-exceptions -fno-rtti
LDFLAGS = -Wl,--gc-sections,--print-gc-sections,--print-memory-usage --specs=nano.specs -nostdlib -nostartfiles -Timxrt.ld

C_FILES := $(wildcard *.c)
CPP_FILES := $(wildcard *.cpp)

OBJS := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)

ARDUINOPATH = /home/paul/teensy/arduino-1.8.8
COMPILERPATH = $(abspath $(ARDUINOPATH)/hardware/tools/arm/bin)
CC = $(COMPILERPATH)/arm-none-eabi-gcc
CXX = $(COMPILERPATH)/arm-none-eabi-g++
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
OBJDUMP = $(COMPILERPATH)/arm-none-eabi-objdump
SIZE = $(COMPILERPATH)/arm-none-eabi-size
AR = $(COMPILERPATH)/arm-none-eabi-gcc-ar

all: Blink.elf

Blink.elf: Blink.o core.a
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ -lm
	#$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ Blink.o $(OBJS) -lm
	$(OBJDUMP) -d -S -C $@ > Blink.lst
	$(OBJDUMP) -t -C $@ > Blink.sym
	$(OBJCOPY) -O ihex -R .eeprom $@ Blink.hex
	$(SIZE) $@

core.a: $(OBJS)
	$(AR) rcs core.a $(OBJS)


clean:
	rm -f *.o *.d core.a *.elf *.lst *.sym *.hex

