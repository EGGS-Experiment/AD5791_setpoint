#
# Makefile
#
# Copyright 2013--2016 
#  Christian Schneider <software(at)chschneider(dot)eu>
#  Peter Yu <ucla(dot)eshop(at)gmail(dot)com>
#
# This file is part of the MOTion trap control unit firmware
# (called "program" in the following).
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 3 as
# published by the Free Software Foundation, *not* any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

export PATH := /opt/tfs/4.0.0/x86_64-avr/bin:$(PATH)

# file list
SRCFILES   := $(wildcard *.c)
SRCFILESCPP:= $(wildcard *.cpp)
HDRFILES   := $(wildcard *.h)
HDRFILESCPP:= $(wildcard *.hpp)
OBJFILES   := $(patsubst %.c,%.o,$(SRCFILES))
OBJFILESCPP:= $(patsubst %.cpp,%.o,$(SRCFILESCPP))
A2RUNFILE  := apache2_is_running

# target for normal firmware
TARGET     := out

# target for bootloader
TARGET_BL  := arduino_mega2560_bootloader_2011-06-29

# microcontroller
MCU        := atmega2560

# clock frequency with crystal oscillator
CPU_FREQ   := 16000000UL

# clock frequency with external clock = 125 MHz / 8
# (DOES NOT WORK WITH THE CURRENT HARDWARE!!!) 
#CPU_FREQ   := 15625000UL

# serial communication
#BAUDRATE   := 9600
BAUDRATE   := 38400

# default values for atmega2560
#LFUSE      := 0x62
#HFUSE      := 0x99
#EFUSE      := 0xff

# values for 16MHz crystal oscillator
# ("plain" atmega2560 without bootloader)
#LFUSE      := 0xff
#HFUSE      := 0x99
#EFUSE      := 0xff

# values for Arduino Mega2560 bootloader with crystal oscillator
LFUSE      := 0xff
HFUSE      := 0xd0
EFUSE      := 0xfd

# values for Arduino Mega2560 bootloader with external clock
# (DOES NOT WORK WITH THE CURRENT HARDWARE!!!) 
#LFUSE      := 0xe0
#HFUSE      := 0xd0
#EFUSE      := 0xfd

# programming normal firmware over bootloader via USB serial console
PORT       := $(firstword $(wildcard /dev/ttyUSB* /dev/ttyACM*))
PROGRAMMER := stk500

# programming bootloader to plain atmega2560 with AVR ISP II
PORT_BL       := usb
PROGRAMMER_BL := avrisp2

# serial console port
CONSOLE_PORT := $(firstword $(wildcard /dev/ttyUSB* /dev/ttyACM*))

# toolchain
CC         := avr-gcc
CXX        := avr-g++
LD         := avr-ld
OBJCOPY    := avr-objcopy
AVRDUDE    := avrdude
FTDI       := ./ft232r_util_s
MINICOM    := minicom

override CFLAGS  := -O2 -Wall -pedantic -std=iso9899:1999 \
                    -mmcu=$(MCU) -DF_CPU=$(CPU_FREQ) -DBAUD=$(BAUDRATE) \
                    $(CFLAGS)
override CXXFLAGS:= -O2 -Wall -pedantic -std=c++11 \
                    -mmcu=$(MCU) -DF_CPU=$(CPU_FREQ) -DBAUD=$(BAUDRATE) \
                    $(CXXFLAGS)
override LDFLAGS := -mmcu=$(MCU) -lm \
                    -Wl,-u,vfprintf -lprintf_flt \
                    -Wl,-u,vfscanf -lscanf_flt $(LDFLAGS)

# for programming normal firmware over bootloader
AVRDUDE_FLAGS    := -p $(MCU) -P $(PORT) -c $(PROGRAMMER)
# for initial programming of bootloader
AVRDUDE_FLAGS_BL := -p $(MCU) -P $(PORT_BL) -c $(PROGRAMMER_BL)

.PHONY: all install install-pre install-post program writefuses readfuses clean console program_bl

%.o: %.c $(HDRFILES)
	$(CC) $(CFLAGS) -c  -o$@ $<

%.o: %.cpp $(HDRFILES) $(HDRFILESCPP)
	$(CXX) $(CXXFLAGS) -c  -o$@ $<

%.elf: $(OBJFILES) $(OBJFILESCPP)
	$(CXX) $(LDFLAGS) -o$@ $^

$(TARGET).hex: %.hex: %.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.eep: %.elf
	-$(OBJCOPY) -O ihex -j .eeprom \
	  --set-section-flags=.eeprom="alloc,load" \
	  --change-section-lma .eeprom=0 $< $@

all: $(TARGET).hex $(TARGET).eep

install: install-pre program install-post

install-pre:
	{ service apache2 status && touch $(A2RUNFILE); } || /bin/true
	service apache2 stop || { echo "NOTE: \`apache2' is not installed." >&2; }
	killall motion_daemon || /bin/true

install-post:
	{ [ -f "$(A2RUNFILE)" ] && service apache2 start; } || /bin/true
	$(RM) $(A2RUNFILE)

program: $(TARGET).hex #$(TARGET).eep
# write flash
	$(FTDI) -r && $(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(TARGET).hex
# write flash and eeprom
#	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$(TARGET).hex \
#	  -U eeprom:w:$(TARGET).eep

$(TARGET_BL).hex:
	wget -O $@ https://raw.githubusercontent.com/arduino/Arduino/master/hardware/arduino/avr/bootloaders/stk500v2/Mega2560-prod-firmware-2011-06-29.hex

program_bl: $(TARGET_BL).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS_BL) -U flash:w:$(TARGET_BL).hex

clean:
	$(RM) $(OBJFILES) $(TARGET).elf $(TARGET).hex $(TARGET).eep $(A2RUNFILE)

console:
	$(MINICOM) -D $(CONSOLE_PORT) -o -8 -b $(BAUDRATE)

writefuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS_BL) -U lfuse:w:$(LFUSE):m \
                                       -U hfuse:w:$(HFUSE):m \
                                       -U efuse:w:$(EFUSE):m
readfuses:
	$(AVRDUDE) $(AVRDUDE_FLAGS_BL) -U lfuse:r:/dev/stdout:h \
                                       -U hfuse:r:/dev/stdout:h \
                                       -U efuse:r:/dev/stdout:h 
