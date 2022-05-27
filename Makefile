# Teensyduino Core Library
# http://www.pjrc.com/teensy/
# Copyright (c) 2019 PJRC.COM, LLC.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# 1. The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# 2. If the Software is incorporated into a build system that allows
# selection among a list of target devices, then similar target
# devices manufactured by PJRC.COM must be included in the list of
# target devices and selectable in the same manner.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

COMPILERPATH ?= /Applications/ARM/bin

CC = $(COMPILERPATH)/arm-none-eabi-gcc
CXX = $(COMPILERPATH)/arm-none-eabi-g++
LD = $(COMPILERPATH)/arm-none-eabi-ld
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
OBJDUMP = $(COMPILERPATH)/arm-none-eabi-objdump
SIZE = $(COMPILERPATH)/arm-none-eabi-size

LOADER = teensy_loader_cli

# checks
CPPCHECK = cppcheck
CPPLINT = cpplint
METRIXPP = python3 ~/Documents/git/metrixplusplus/metrix++.py

# options for checks
CPPCHECKFLAGS = . -D__imxrt1062__ -DARDUINO_TEENSY41
CPPLINTFLAGS =  --recursive --root=~/Documents/git/imxrt1062_cores/ */*
METRIXPP_COLLECT = collect --std.code.lines.code --std.code.complexity.cyclomatic --std.code.lines.code --std.code.lines.preprocessor --std.code.lines.comments --std.code.magic.numbers --std.code.member.globals --std.code.todo.comments --db-file=build/metrixpp.db
METRIXPP_REPORT = view --db-file=build/metrixpp.db

OUTFILE = firmware

BUILD_DIR = ./build
SRC_DIRS ?= ./user ./teensy4 ./libraries

SRCS := $(shell find $(SRC_DIRS) -name *.c -or -name *.s -or -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Use these lines for Teensy 4.0
#MCU = IMXRT1062
#MCU_LD = imxrt1062.ld
#MCU_DEF = ARDUINO_TEENSY40

# Use these lines for Teensy 4.1
MCU = IMXRT1062
MCU_LD = imxrt1062_t41.ld
MCU_DEF = ARDUINO_TEENSY41

# configurable options
OPTIONS = -DF_CPU=600000000 -DUSB_DUAL_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE
#
# USB Type configuration:
#   -DUSB_SERIAL
#   -DUSB_DUAL_SERIAL
#   -DUSB_TRIPLE_SERIAL
#   -DUSB_KEYBOARDONLY
#   -DUSB_TOUCHSCREEN
#   -DUSB_HID_TOUCHSCREEN
#   -DUSB_HID
#   -DUSB_SERIAL_HID
#   -DUSB_MIDI
#   -DUSB_MIDI4
#   -DUSB_MIDI16
#   -DUSB_MIDI_SERIAL
#   -DUSB_MIDI4_SERIAL
#   -DUSB_MIDI16_SERIAL
#   -DUSB_AUDIO
#   -DUSB_MIDI_AUDIO_SERIAL
#   -DUSB_MIDI16_AUDIO_SERIAL
#   -DUSB_MTPDISK
#   -DUSB_RAWHID
#   -DUSB_FLIGHTSIM
#   -DUSB_FLIGHTSIM_JOYSTICK

# options needed by many Arduino libraries to configure for Teensy model
OPTIONS += -D__$(MCU)__ -DARDUINO=10813 -DTEENSYDUINO=154 -D$(MCU_DEF) $(INC_FLAGS)

# for Cortex M7 with single & double precision FPU
CPUOPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

# use this for a smaller, no-float printf
#SPECS = --specs=nano.specs

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -O2 $(CPUOPTIONS) -MMD $(OPTIONS) -I. -ffunction-sections -fdata-sections

# compiler options for C++ only
CXXFLAGS = -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing

# compiler options for C only
CFLAGS =

# linker options
LDFLAGS = -Os -Wl,--gc-sections,--relax $(SPECS) $(CPUOPTIONS) -Tteensy4/$(MCU_LD)

# additional libraries to link
LIBS = -lm -lstdc++#-larm_cortexM7lfsp_math

# Other Makefiles and project templates for Teensy
#
# https://forum.pjrc.com/threads/57251?p=213332&viewfull=1#post213332
# https://github.com/apmorton/teensy-template
# https://github.com/xxxajk/Arduino_Makefile_master
# https://github.com/JonHylands/uCee


$(BUILD_DIR)/$(OUTFILE).hex: $(BUILD_DIR)/$(OUTFILE).elf
	@$(OBJCOPY) -O ihex -R .eeprom build/$(OUTFILE).elf build/$(OUTFILE).hex
	@$(OBJDUMP) -d -x build/$(OUTFILE).elf > build/$(OUTFILE).dis
	@$(OBJDUMP) -d -S -C build/$(OUTFILE).elf > build/$(OUTFILE).lst
	@$(SIZE) -G -d -t build/$(OUTFILE).elf

$(BUILD_DIR)/$(OUTFILE).elf: $(OBJS)
	@$(CC) $(CFLAGS) -Xlinker -Map=build/$(OUTFILE).map $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.s.o: %.s
	@$(MKDIR_P) $(dir $@)
	@echo \>\> Invoking as on $<
	@$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	@echo \>\> Invoking gcc on $<
	@$(CC) $(CPPFLAGS) $(CFLAGS)  -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	@echo \>\> Invoking g++ on $<
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	
.PHONY: static
static:
	@echo \>\>
	@echo \>\> Invoking CPPLINT - ignoring errors
	@$(CPPLINT) $(CPPLINTFLAGS) $< 2>> build/$(OUTFILE).ana || true

	@echo \>\>
	@echo \>\> Invoking CPPCHECK - ignoring errors
	@$(CPPCHECK) $(CPPCHECKFLAGS) $< 2>> build/$(OUTFILE).ana || true

.PHONY: metrics
metrics:
	@echo \>\>
	@echo \>\> Running METRIX++
	$(METRIXPP) $(METRIXPP_COLLECT)
	$(METRIXPP) $(METRIXPP_REPORT) >> build/$(OUTFILE).ana

.PHONY: checks
checks:
	@echo \>\>
	@echo \>\> Setup..!
	make clean

	@echo \>\>
	@echo \>\> Running checks..!
	make metrics
	make static

.PHONY: flashnew
flashnew: 
	@echo \>\>
	@echo \>\> Removing /build dir..
	@$(RM) -f -r $(BUILD_DIR)

	@echo \>\>
	@echo \>\> Beginning building..!
	make

	@echo \>\>
	@echo \>\> Beginning flashing process..
	$(LOADER) --mcu=TEENSY41 -w -s -v $(BUILD_DIR)/$(OUTFILE).hex
	@echo \>\> Device has been flashed!

.PHONY: flash
flash: 
	@echo \>\>
	@echo \>\> Beginning building..
	make

	@echo \>\>
	@echo \>\> Beginning flashing process..
	
	@echo \>\>
	$(LOADER) --mcu=TEENSY41 -w -s -v $(BUILD_DIR)/$(OUTFILE).hex
	@echo "Device has been flashed!"

.PHONY: flashonly
flashonly:
	@echo \>\>
	@echo \>\> Beginning flashing process..
	
	@echo \>\>
	$(LOADER) --mcu=TEENSY41 -w -s -v $(BUILD_DIR)/$(OUTFILE).hex
	@echo \>\> Device has been flashed!

.PHONY: delete
delete:
	@echo \>\>
	@echo \>\> Deleting /build dir..
	@$(RM) -f -r $(BUILD_DIR)

.PHONY: clean
clean:
	@echo \>\>
	@echo \>\> Deleting /build dir..
	@$(RM) -f -r $(BUILD_DIR)
	
	@echo \>\>
	@echo \>\> Beginning building..
	make

MKDIR_P ?= mkdir -p