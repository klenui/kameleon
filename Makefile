# ------------------------------------------------
# Makefile (based on gcc)
# ------------------------------------------------

# Control build verbosity
#
#  V=1,2: Enable echo of commands
#  V=2:   Enable bug/verbose options in tools and scripts

ifeq ($(V),1)
export Q :=
else
ifeq ($(V),2)
export Q :=
else
export Q := @
endif
endif

######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og
# with bootloader
BOOTLOADER = 1

#######################################
# paths
#######################################

# Build path
BUILD_DIR = build

# -----------------------------------------------------------------------------
# Toolchain
# -----------------------------------------------------------------------------

# PREFIX = arm-none-eabi-
# CC = $(PREFIX)gcc
# AS = $(PREFIX)gcc -x assembler-with-cpp
# CP = $(PREFIX)objcopy
# AR = $(PREFIX)ar
# SZ = $(PREFIX)size
# HEX = $(CP) -O ihex
# BIN = $(CP) -O binary -S

# -----------------------------------------------------------------------------
# Target-specific
# -----------------------------------------------------------------------------

ifndef TARGET
TARGET = kameleon-core
endif

TARGET_DIR = targets/boards/$(TARGET)
SHARED_DIR = targets/shared

TARGET_ASM =
TARGET_SRC =
TARGET_INC =
TARGET_DEF =

TARGET_BIN = $(TARGET)

-include $(TARGET_DIR)/Make.def

# -----------------------------------------------------------------------------
# Jerryscript
# -----------------------------------------------------------------------------

JERRY_ROOT = deps/jerryscript

JERRY_HOST = $(JERRY_ROOT)/build/bin/jerry

JERRY_LIBDIR = $(JERRY_ROOT)/build/lib

JERRY_LIBS = \
$(JERRY_LIBDIR)/libjerry-core.a \
$(JERRY_LIBDIR)/libjerry-ext.a

JERRY_INC = \
-I${JERRY_ROOT}/jerry-core \
-I${JERRY_ROOT}/jerry-core/api \
-I${JERRY_ROOT}/jerry-core/debugger \
-I${JERRY_ROOT}/jerry-core/ecma/base \
-I${JERRY_ROOT}/jerry-core/ecma/builtin-objects \
-I${JERRY_ROOT}/jerry-core/ecma/builtin-objects/typedarray \
-I${JERRY_ROOT}/jerry-core/ecma/operations \
-I${JERRY_ROOT}/jerry-core/include \
-I${JERRY_ROOT}/jerry-core/jcontext \
-I${JERRY_ROOT}/jerry-core/jmem \
-I${JERRY_ROOT}/jerry-core/jrt \
-I${JERRY_ROOT}/jerry-core/lit \
-I${JERRY_ROOT}/jerry-core/parser/js \
-I${JERRY_ROOT}/jerry-core/parser/regexp \
-I${JERRY_ROOT}/jerry-core/vm \
-I${JERRY_ROOT}/jerry-ext/arg \
-I${JERRY_ROOT}/jerry-ext/include \
-I${JERRY_ROOT}/jerry-libm

JERRY_ARGS = \
--toolchain=cmake/${JERRY_TOOLCHAIN} \
--lto=OFF \
--error-messages=ON \
--js-parser=ON \
--mem-heap=${JERRY_HEAPSIZE} \
--mem-stats=ON \
--snapshot-exec=ON \
--line-info=ON \
--vm-exec-stop=ON \
--profile=es2015-subset \
--jerry-cmdline=OFF \
--cpointer-32bit=ON

# -----------------------------------------------------------------------------
# Kameleon
# -----------------------------------------------------------------------------

KAMELEON_GENERATED_C = \
src/gen/kameleon_modules.c \
src/gen/kameleon_magic_strings.c

KAMELEON_GENERATED_H = \
src/gen/kameleon_modules.h \
src/gen/kameleon_magic_strings.h

KAMELEON_GENERATED = $(KAMELEON_GENERATED_C) $(KAMELEON_GENERATED_H)

KAMELEON_DEF =

KAMELEON_ASM =

KAMELEON_SRC = \
src/utils.c \
src/base64.c \
src/io.c \
src/runtime.c \
src/repl.c \
src/jerry_port.c \
src/jerryxx.c \
src/global.c \
src/ymodem.c \
$(KAMELEON_GENERATED_C)

KAMELEON_INC = \
-Iinclude \
-Iinclude/port \
-Isrc/gen \
-Isrc/modules/net \
-Isrc/modules/wifi

# -----------------------------------------------------------------------------
# Kameleon Modules
# -----------------------------------------------------------------------------

ifdef KAMELEON_MODULE_PWM
KAMELEON_SRC += src/modules/pwm/module_pwm.c
KAMELEON_INC += -Isrc/modules/pwm
endif

ifdef KAMELEON_MODULE_I2C
KAMELEON_SRC += src/modules/i2c/module_i2c.c
KAMELEON_INC += -Isrc/modules/i2c
endif

ifdef KAMELEON_MODULE_SPI
KAMELEON_SRC += src/modules/spi/module_spi.c
KAMELEON_INC += -Isrc/modules/spi
endif

ifdef KAMELEON_MODULE_STORAGE
KAMELEON_SRC += src/modules/storage/module_storage.c
KAMELEON_INC += -Isrc/modules/storage
endif

ifdef KAMELEON_MODULE_UART
KAMELEON_SRC += src/modules/uart/module_uart.c
KAMELEON_INC += -Isrc/modules/uart
endif

ifdef KAMELEON_MODULE_GRAPHICS
KAMELEON_SRC += \
	src/modules/graphics/gc_cb_prims.c \
	src/modules/graphics/gc_1bit_prims.c \
	src/modules/graphics/gc_16bit_prims.c \
  src/modules/graphics/gc.c \
	src/modules/graphics/font_default.c \
  src/modules/graphics/module_graphics.c
KAMELEON_INC += -Isrc/modules/graphics
endif

# -----------------------------------------------------------------------------
# Default action: build all
# -----------------------------------------------------------------------------

all: $(BUILD_DIR)/$(TARGET_BIN).elf $(BUILD_DIR)/$(TARGET_BIN).hex $(BUILD_DIR)/$(TARGET_BIN).bin
	$(Q) ls -al $(BUILD_DIR)/$(TARGET_BIN).*
	@echo "Done."

# -----------------------------------------------------------------------------
# JS snapshot generation
# -----------------------------------------------------------------------------

$(KAMELEON_GENERATED):
	$(Q) python $(JERRY_ROOT)/tools/build.py --clean --jerry-cmdline-snapshot=ON --snapshot-save=ON --snapshot-exec=ON --profile=es2015-subset
	$(Q) node tools/js2c.js --modules=$(KAMELEON_MODULES) --target=$(TARGET)
	$(Q) -rm -rf deps/jerryscript/build

# -----------------------------------------------------------------------------
# Build app
# -----------------------------------------------------------------------------

# list of objects
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(CSRC:.c=.o)))
vpath %.c $(sort $(dir $(CSRC)))

# list of ASM program objects
OBJS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASRC:.s=.o)))
vpath %.s $(sort $(dir $(ASRC)))

$(BUILD_DIR)/%.o: %.c Makefile $(KAMELEON_GENERATED) | $(BUILD_DIR)
	@echo "compile:" $<
	$(Q) $(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "compile:" $<
	$(Q) $(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET_BIN).elf: $(OBJS) $(JERRY_LIBS) Makefile
	@echo "link:" $@
	$(Q) $(CC) $(OBJS) $(LDFLAGS) -o $@
	$(Q) $(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "hex:" $@
	$(Q) $(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@echo "bin:" $@
	$(Q) $(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

$(JERRY_LIBS):
	$(Q) python $(JERRY_ROOT)/tools/build.py --clean $(JERRY_ARGS)


clean:
	$(Q) -rm -rf deps/jerryscript/build
	$(Q) -rm $(KAMELEON_GENERATED)
	$(Q) -rm -fR $(BUILD_DIR)

flash:
	$(Q) st-flash write build/$(TARGET).bin 0x8008000

# *** EOF ***
