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

#######################################
# paths
#######################################

# Build path
BUILD_DIR = build

# -----------------------------------------------------------------------------
# Toolchain
# -----------------------------------------------------------------------------

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


# -----------------------------------------------------------------------------
# Duktape
# -----------------------------------------------------------------------------


DUKTAPE_INC = \
-Isrc/duktape

DUKTAPE_SRC = \
src/duktape/duktape.c

# -----------------------------------------------------------------------------
# Kameleon
# -----------------------------------------------------------------------------

KAMELEON_DEF =

KAMELEON_ASM = 

KAMELEON_SRC = \
src/main.c
# src/utils.c \
# src/io.c \
# src/runtime.c \
# src/repl.c \
# src/jerry_port.c \
# src/jerryxx.c \
# src/global.c \
# src/target.c

KAMELEON_INC = \
-Iinclude \
-Iinclude/port
# -Isrc/gen \
# -Isrc/modules

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

TARGET_BIN = kameleon

-include $(TARGET_DIR)/Make.def

# -----------------------------------------------------------------------------
# CFLAGS
# -----------------------------------------------------------------------------

# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mlittle-endian -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =

# C defines
C_DEFS = $(TARGET_DEF)

ASRC = $(KAMELEON_ASM) $(TARGET_ASM)
AINC =

CSRC = $(TARGET_SRC) $(KAMELEON_SRC) $(DUKTAPE_SRC)
CINC = $(TARGET_INC) $(KAMELEON_INC) $(DUKTAPE_INC)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AINC) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(CINC) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

#######################################
# LDFLAGS
#######################################

# libraries
LIBS = -lc -lnosys -lm
LDFLAGS = $(MCU) -specs=nano.specs -u _printf_float -T$(TARGET_LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


# -----------------------------------------------------------------------------
# Default action: build all
# -----------------------------------------------------------------------------

all: $(BUILD_DIR)/$(TARGET_BIN).elf $(BUILD_DIR)/$(TARGET_BIN).hex $(BUILD_DIR)/$(TARGET_BIN).bin
	$(Q) ls -al $(BUILD_DIR)/$(TARGET_BIN).*
	@echo "Done."

# -----------------------------------------------------------------------------
# Build app
# -----------------------------------------------------------------------------

# list of objects
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(CSRC:.c=.o)))
vpath %.c $(sort $(dir $(CSRC)))

# list of ASM program objects
OBJS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASRC:.s=.o)))
vpath %.s $(sort $(dir $(ASRC)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@echo "compile:" $<
	$(Q) $(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "compile:" $<
	$(Q) $(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET_BIN).elf: $(OBJS) Makefile
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

clean:
	$(Q) -rm -rf deps/jerryscript/build
	$(Q) -rm -fR $(BUILD_DIR)

flash:
	$(Q) st-flash write build/kameleon.bin 0x8000000

# *** EOF ***
