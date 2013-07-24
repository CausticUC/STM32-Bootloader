# Basic Makefile
# Reminder, GNU Make uses hard tabs not spaces

# House keeping
BUILDDIR = $(PROJECT_LOC)/build

# Compiler and settings
CC = arm-none-eabi-gcc
DEBUG = -g
OPTIM = -O0
OBJCOPY = arm-none-eabi-objcopy
LDSCRIPT = standalone.ld
OBJS = $(SOURCE:.c=.o)
CFLAGS = $(DEBUG)

# Device Specifications for the compiler
MCU_GCC_DEF = GCC_ARMCM3_STM32F10X

# Linker Flags
LINKER_FLAGS = -nostartfiles -Xlinker -oF3DisDem.axf -Xlinker -M -Xlinker -Map=f3disdem.map -Xlinker --no-gc-sections

# Project-wide Libraries needed
RTOS_SOURCE_DIR=$(FreeRTOS_ROOT)/Source
STM32_DRIVER_DIR = $(PROJECT_LOC)/../F3DiscoveryDemo-crossworks/Demo/CORTEX_STM32F3Discovery_GCC_Rowley/Libraries/STM32F30x_StdPeriph_Driver
CMSIS_DIR = /home/caustic/git/Indep/STM32F30x_DSP_StdPeriph_Lib_V1.0.0/Libraries/CMSIS/Device/ST/STM32F30x/Include

LIBS = -I . \
       -I $(CMSIS_DIR) \
       -I $(RTOS_SOURCE_DIR)/include \
       -I $(RTOS_SOURCE_DIR)/portable/GCC/ARM_CM3 \
       -I $(STM32_DRIVER_DIR) 


CFLAGS=$(DEBUG) $(LIBS) \
        -D $(MCU_GCC_DEF ) -D inline= -mthumb -mcpu=cortex-m3 $(OPTIM) \
        -T$(LDSCRIPT) \
        -D PACK_STRUCT_END=__attribute\(\(packed\)\) -D ALIGN_STRUCT_END=__attribute\(\(aligned\(4\)\)\) \
        -ffunction-sections -fdata-sections 


all: main

clean:
	rm -f $(BUILDDIR)/build

main: main.c Makefile
	mkdir $(BUILDDIR)
	$(CC) -c $(CFLAGS) -O1 main.c -o $(BUILDDIR)/build/main.o
    
.PHONY: all clean
