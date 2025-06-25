CC=arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
MACH=cortex-m4
CFLAGS=-mcpu=$(MACH)  -nostdlib -mthumb -mfloat-abi=soft  -std=gnu2x -Wall -O0 -g3
BUILD_DIR=build
LDFLAGS= -mcpu=$(MACH) -mthumb  -mfloat-abi=soft --specs=nano.specs -T linker.ld  -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/output.map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb  -mfloat-abi=soft --specs=rdimon.specs -T linker.ld  -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/output.map
TARGET=firmware
TARGET_SH=firmware_sh
C_SOURCES = $(shell find $(SRC_DIRS) -name "*.c")
ASM_SOURCES = $(shell find $(SRC_DIRS) -name "*.s") $(shell find $(SRC_DIRS) -name "*.S")
OBJS = $(C_SOURCES:%.c=$(BUILD_DIR)/%.o) $(ASM_SOURCES:%.s=$(BUILD_DIR)/%.o)
OBJS_SH = $(BUILD_DIR)/gpio.o $(BUILD_DIR)/main.o 
#LDFLAGS=-nostdlib -T linker.ld -Wl,--gc-sections
#LDFLAGS=-nostdlib -T linker.ld -Wl,--gc-sections -Wl,-Map=output.map
#LDFLAGS=-nostdlib -T linker.ld -Wl,--gc-sections -Wl,-Map=output.map -Wl,--start-group -lc -lgcc -lm -lnosys -Wl,--end-group

ifeq ($(origin UART_PRINTF), command line)
CFLAGS += -DUART_PRINTF=1
endif

ifeq ($(origin SEMIHOSTING), command line)
CFLAGS += -DSEMIHOSTING=1
endif


ifeq ($(origin __UART_PRINTF__), command line)
CFLAGS += -D__UART_PRINTF__=1
endif

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $< $(CFLAGS) -I$(SRC_DIRS) -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(BUILD_DIR)/$(TARGET_SH).elf: $(OBJS_SH)
	$(LD) $(OBJS_SH) -o $@ $(LDFLAGS_SH)
	$(SIZE) $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.bin $(BUILD_DIR)/*.hex $(BUILD_DIR)/*.map