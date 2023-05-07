###############################################################################
# Makefile for project 
###############################################################################
## General options
# RST_PIN	:=	8
# CS_PIN	:=	10
# DC_PIN	:=	9

# ARDUINO_PATH = "D:\PROGRA~1\PROTEU~1\Tools\ARDUINO"
# AVRDUDE_CONF_PATH = "D:\PROGRA~1\Arduino\hardware\tools\avr\etc\avrdude.conf"
mksketch = $(MKSKETCH_HOME)"\mksketch.exe"

UPLOAD_PORT = COM3
UPLOAD_BAUD = 115200
UPLOAD_PROGRAMER = arduino

## General options
PROJECT = 
COMPILER = "Arduino AVR (Proteus)"
TARGET = Debug
SHELL = C:\Windows\system32\cmd.exe
BUILD_DIR = bin

BOARD = pro328
MCU = ATmega8
MMCU = atmega8
F_CPU = 16000000
OPTIMIZE = Os

SRCS = $(wildcard *.c) 
OBJS =$(SRCS:%.c=$(BUILD_DIR)/%.o)
SRCSCPP =$(wildcard *.cpp)
OBJSCPP =$(SRCSCPP:%.cpp=$(BUILD_DIR)/%.o)
THIS_DIR = $(abspath .)
CURR_FOLDER_NAME =$(lastword $(notdir $(THIS_DIR)))


## Tools general options
## -T -D 添加宏
## -U    添加自定义库上层目录
APPFLAGS=-C $(BOARD) \
		 -N $(MMCU) \
		 -F $(F_CPU) \
	     -T -std=gnu11 \
		 -T -fno-threadsafe-statics


CCFLAGS=-Wall -gdwarf-2 -fno-exceptions \
		-DF_CPU=$(F_CPU) \
		-DARDUINO_ARCH_AVR \
		-$(OPTIMIZE) \
		-mmcu=$(MMCU) \
		-I . \
		-I .. \
		@$(BUILD_DIR)/arduino/libs.inc \

CFLAGS := $(CCFLAGS)

CCFLAGS += -std=gnu++11 -fno-threadsafe-statics
CFLAGS += -std=gnu11

LDFLAGS = -Wl,--gc-sections \
		  -mmcu=$(MMCU) \
		  -L $(BUILD_DIR) \
		  -L $(BUILD_DIR)/arduino	

##编译到boot区
# LDFLAGS += -Wl,--section-start=.text=0x3800
##指定代码中用__attribute__((section(".xxx")))修饰的函数编译到指定位置
# LDFLAGS += -Wl,--section=.xxx=0x3800

## for Release
CCFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -ffunction-sections -fdata-sections

## Processing Tools
FLOWCHART=
APP=$(mksketch)
CC=avr-gcc
ASM=avr-gcc
LD=avr-gcc


# .PHONY: test
# test:
# 	@echo $(SRCS)
# 	@echo $(OBJS)
	
# Build tree:
all:	Debug

.PHONY: upload
upload: 
	avrdude -C$(AVRDUDE_CONF_PATH) -v \
	-p$(MCU) -c$(UPLOAD_PROGRAMER) -P$(UPLOAD_PORT) -b$(UPLOAD_BAUD) -D -Uflash:w:$(BUILD_DIR)/Debug.hex:i

Debug: $(BUILD_DIR)/Debug.elf 
	avr-size "$(BUILD_DIR)/Debug.ELF"

$(BUILD_DIR)/Debug.elf: $(BUILD_DIR)/main.o $(OBJS)  $(OBJSCPP)
	$(LD) $(LDFLAGS) -o $@ $(addprefix -l:,$(notdir $^)) -l:arduino.a -lm 
	avr-objcopy -O ihex -R .eeprom "$(BUILD_DIR)/Debug.elf" "$(BUILD_DIR)/Debug.hex"
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex "$(BUILD_DIR)/Debug.elf" "$(BUILD_DIR)/Debug.eep" || exit 0 
	avr-objcopy -O binary -R .eeprom "$(BUILD_DIR)/Debug.elf" "$(BUILD_DIR)/Debug.bin"
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O binary "$(BUILD_DIR)/Debug.elf" "$(BUILD_DIR)/Debug.eepb" || exit 0 
#bin文件没有代码的位置信息，所以起始地址都是从0开始：
#如果只有boot区，或者只app区，编译出来的文件就会小一点
#如果代码boot区跟app区都有，那么编译出来的文件将从0一直覆盖到boot区，文件偏大；

$(BUILD_DIR)/main.o: $(BUILD_DIR)/main.cpp 
	$(CC) $(CCFLAGS) -o $@ -c $<

$(BUILD_DIR)/main.cpp:	main.ino 
	-mkdir "$(BUILD_DIR)"
	$(APP) $(APPFLAGS) -A $(ARDUINO_PATH) -M $(BUILD_DIR)/arduino -O $@ $<
	make -f $(BUILD_DIR)/arduino/Makefile all

$(BUILD_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $< 

$(BUILD_DIR)/%.o: %.cpp %.h
	$(CC) $(CCFLAGS) -o $@ -c $< 

# bootloader - attach bootloader to the firmware
bootloader:
	avr-objcopy -O ihex -R .eeprom "$(BUILD_DIR)/Debug.elf" "$(BUILD_DIR)/Debug.hex"
	copy /b bootloader.hex+"$(BUILD_DIR)/Debug.hex" "with.bootloader.hex"

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf $(BUILD_DIR)/*.d
	-make -f $(BUILD_DIR)/arduino/Makefile tidy

# cleanup - delete all generated files
clean:	tidy
	rm -rf $(BUILD_DIR)/*.elf
	rm -rf $(BUILD_DIR)/*.cpp
	rm -rf $(BUILD_DIR)/*.o
	-make -f $(BUILD_DIR)/arduino/Makefile clean

OBJTREE := $(BUILD_DIR)


