#
# Target Output Details
#
LINUX_TARGET = specseek
WINDOWS_TARGET = specseek.exe

#
# Compilers for Differing Targets
#
GCC = gcc
MINGW = i686-w64-mingw32-gcc

#
# Flag Options for Compilers
# 
GCC_CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -O2 -m32
MINGW_CFLAGS = -Wall -Wextra -Werror -O2 -m32

#
# Output directories as variables
#
GCC_BIN_DIR = bin/gcc
GCC_OBJ_DIR = $(GCC_BIN_DIR)/obj

WIN_BIN_DIR = bin/win
WIN_OBJ_DIR = $(WIN_BIN_DIR)/obj

#
# Detect Source files in Code, this is very broad
# and will just compile anything it finds
#
SRCS = $(shell find src -name '*.c')

#
# Object files (Separated because it caused linking problems)
#
GCC_OBJS = $(patsubst src/%.c, $(GCC_OBJ_DIR)/%.gcc.o, $(SRCS))
WIN_OBJS = $(patsubst src/%.c, $(WIN_OBJ_DIR)/%.win.o, $(SRCS))

#
# Default Command (no args) GCC Build
#
all: $(LINUX_TARGET) $(WINDOWS_TARGET)

$(LINUX_TARGET): $(GCC_OBJS)
	@mkdir -p $(GCC_BIN_DIR)
	$(GCC) $(GCC_CFLAGS) -o $(GCC_BIN_DIR)/$(LINUX_TARGET) $^

#
# Windows Build `make windows` (mingw)
#
windows: $(WINDOWS_TARGET)

$(WINDOWS_TARGET): $(WIN_OBJS)
	@mkdir -p $(WIN_BIN_DIR)
	$(MINGW) $(MINGW_CFLAGS) -o $(WIN_BIN_DIR)/$(WINDOWS_TARGET) $^

#
# Object Construct Rules (Apply flags per Target)
#
$(GCC_OBJ_DIR)/%.gcc.o: src/%.c
	@mkdir -p $(dir $@)
	$(GCC) $(GCC_CFLAGS) -c $< -o $@

$(WIN_OBJ_DIR)/%.win.o: src/%.c
	@mkdir -p $(dir $@)
	$(MINGW) $(MINGW_CFLAGS) -c $< -o $@

#
# Make Run Command
#

# Detect platform
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	PLATFORM := linux
else ifeq ($(UNAME_S),Darwin)
	PLATFORM := mac
else
	PLATFORM := windows
endif

#
# Unified run command (automatic platform detection)
#
run:
ifeq ($(PLATFORM),linux)
	@$(MAKE) all
	@./$(GCC_BIN_DIR)/$(LINUX_TARGET)
else ifeq ($(PLATFORM),mac)
	@$(MAKE) all
	@./$(GCC_BIN_DIR)/$(LINUX_TARGET)
else
	@$(MAKE) windows
	@./$(WIN_BIN_DIR)/$(WINDOWS_TARGET)
endif

#
# Clean Source Dir
#
clean:
	rm -rf $(GCC_BIN_DIR) $(WIN_BIN_DIR)

.PHONY: all windows clean
