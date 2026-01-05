# Variables
ASM = nasm
ASM_FLAGS = -f bin
SRC = tictactoe_assembly.asm
BUILD_DIR = ./bld
TARGET = $(BUILD_DIR)/tictactoe.bin

# Default command (make)
all: $(TARGET)

# Rule to create the build directory and compile the .asm file
$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(ASM) $(ASM_FLAGS) $(SRC) -o $(TARGET)

# Rule to run in QEMU
run: $(TARGET)
	qemu-system-i386 -drive format=raw,file=$(TARGET)

# Rule to clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
