PROJECT = baremetal-bluepill
BUILD_DIR = bin

CFILES = firmware.c
CFILES += system.c
CFILES += api.c

AFILES += api-asm.S

SHARED_SRC_DIR = ../shared/src
SHARED_SRC_CORE_DIR = ../shared/src/core
SHARED_INC_DIR = ../shared/inc
INC_DIR = inc

# TODO - you will need to edit these two lines!
DEVICE=stm32f103c8t6
OOCD_FILE = board/stm32f103c8t6.cfg

# You shouldn't have to edit anything below here.
VPATH += ../shared/src
VPATH += ../shared/src/core

INCLUDES += -I$(INC_DIR)
INCLUDES += -I$(SHARED_INC_DIR)
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
