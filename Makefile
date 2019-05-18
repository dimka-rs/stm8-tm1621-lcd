#######
# makefile for STM8S_StdPeriph_Lib and SDCC compiler
#
# Customized by MightyPork 1/2017
#
# usage:
#   1. if SDCC not in PATH set path -> CC_ROOT
#   2. set correct STM8 device -> DEVICE
#   3. set project paths -> PRJ_ROOT, PRJ_SRC_DIR, PRJ_INC_DIR
#   4. set SPL root path -> SPL_ROOT
#   5. include required SPL modules -> SPL_SOURCE
#
#######

# STM8 device (default is STM8 discovery board)
DEVICE=STM8S103
DEVICE_FLASH=stm8s103f3

# trap handling requires SDCC >=v3.4.3
SKIP_TRAPS = 0

# set compiler path & parameters 
CC_ROOT = /home/dimka/apps/sdcc/bin
CC      = $(CC_ROOT)/sdcc
CFLAGS  = -mstm8 -lstm8 --opt-code-size --std-c99

# required for some examples for STM8S EVAL board
#CFLAGS += -DUSE_STM8_128_EVAL

# set output folder and target name
OUTPUT_DIR = ./build
TARGET     = $(OUTPUT_DIR)/$(DEVICE).hex

# set project folder and files (all *.c)
PRJ_ROOT    = .
PRJ_SRC_DIR = $(PRJ_ROOT)/src
PRJ_INC_DIR = $(PRJ_ROOT)/inc
# all project sources included by default
PRJ_SOURCE  = $(notdir $(wildcard $(PRJ_SRC_DIR)/*.c))
PRJ_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(PRJ_SOURCE:.c=.rel))

# set SPL paths
SPL_SRC_DIR = ./STM8S_StdPeriph_Driver/src
SPL_INC_DIR = ./STM8S_StdPeriph_Driver/inc
# add all library sources used here
SPL_SOURCE  = stm8s_gpio.c stm8s_i2c.c stm8s_spi.c
SPL_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(SPL_SOURCE:.c=.rel))

# collect all include folders
INCLUDE = -I$(PRJ_INC_DIR) -I$(SPL_INC_DIR) 

# collect all source directories
VPATH=$(PRJ_SRC_DIR):$(SPL_SRC_DIR)

.PHONY: clean flash

all: $(TARGET)

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) -D$(DEVICE) $(INCLUDE) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $?

$(OUTPUT_DIR)/%.rel: %.c
	$(CC) $(CFLAGS) -D$(DEVICE) $(INCLUDE) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $? -o $@

$(TARGET): $(PRJ_OBJECTS) $(SPL_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

flash: all
	~/apps/stm8flash -c stlinkv2 -p $(DEVICE_FLASH) -s flash -w $(TARGET)

clean:
	rm $(OUTPUT_DIR)/*
