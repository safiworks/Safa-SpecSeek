#
# Target Output Details
#
LINUX_TARGET_32 = specseek_32
LINUX_TARGET_64 = specseek_64
WINDOWS_TARGET_32 = specseek_32.exe
WINDOWS_TARGET_64 = specseek_64.exe

#
# Compilers for Differing Targets
#
GCC_32 = gcc -m32
GCC_64 = gcc -m64

MINGW_32 = i686-w64-mingw32-gcc
MINGW_64 = x86_64-w64-mingw32-gcc

#
# Flag Options for Compilers
# 
COMMON_CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -O2

#
# Output directories as variables
#
GCC_BIN_DIR_32 = bin/gcc/32
GCC_BIN_DIR_64 = bin/gcc/64
GCC_OBJ_DIR_32 = $(GCC_BIN_DIR_32)/obj
GCC_OBJ_DIR_64 = $(GCC_BIN_DIR_64)/obj

WIN_BIN_DIR_32 = bin/win/32
WIN_BIN_DIR_64 = bin/win/64
WIN_OBJ_DIR_32 = $(WIN_BIN_DIR_32)/obj
WIN_OBJ_DIR_64 = $(WIN_BIN_DIR_64)/obj

#
# Detect Source files in Code, this is very broad
# and will just compile anything it finds
#
SRCS = $(shell find src -name '*.c')

#
# Object files per arch
#
GCC_OBJS_32 = $(patsubst src/%.c, $(GCC_OBJ_DIR_32)/%.gcc.o, $(SRCS))
GCC_OBJS_64 = $(patsubst src/%.c, $(GCC_OBJ_DIR_64)/%.gcc.o, $(SRCS))

WIN_OBJS_32 = $(patsubst src/%.c, $(WIN_OBJ_DIR_32)/%.win.o, $(SRCS))
WIN_OBJS_64 = $(patsubst src/%.c, $(WIN_OBJ_DIR_64)/%.win.o, $(SRCS))

#
# Default Command (no args) Build all 4 binaries
#
all: $(LINUX_TARGET_32) $(LINUX_TARGET_64) $(WINDOWS_TARGET_32) $(WINDOWS_TARGET_64)

#
# Linux 32-bit build
#
$(LINUX_TARGET_32): $(GCC_OBJS_32)
	@mkdir -p $(GCC_BIN_DIR_32)
	$(GCC_32) $(COMMON_CFLAGS) -o $(GCC_BIN_DIR_32)/$(LINUX_TARGET_32) $^

#
# Linux 64-bit build
#
$(LINUX_TARGET_64): $(GCC_OBJS_64)
	@mkdir -p $(GCC_BIN_DIR_64)
	$(GCC_64) $(COMMON_CFLAGS) -o $(GCC_BIN_DIR_64)/$(LINUX_TARGET_64) $^

#
# Windows 32-bit build
#
$(WINDOWS_TARGET_32): $(WIN_OBJS_32)
	@mkdir -p $(WIN_BIN_DIR_32)
	$(MINGW_32) $(COMMON_CFLAGS) -o $(WIN_BIN_DIR_32)/$(WINDOWS_TARGET_32) $^

#
# Windows 64-bit build
#
$(WINDOWS_TARGET_64): $(WIN_OBJS_64)
	@mkdir -p $(WIN_BIN_DIR_64)
	$(MINGW_64) $(COMMON_CFLAGS) -o $(WIN_BIN_DIR_64)/$(WINDOWS_TARGET_64) $^

#
# Object build rules per architecture
#
$(GCC_OBJ_DIR_32)/%.gcc.o: src/%.c
	@mkdir -p $(dir $@)
	$(GCC_32) $(COMMON_CFLAGS) -c $< -o $@

$(GCC_OBJ_DIR_64)/%.gcc.o: src/%.c
	@mkdir -p $(dir $@)
	$(GCC_64) $(COMMON_CFLAGS) -c $< -o $@

$(WIN_OBJ_DIR_32)/%.win.o: src/%.c
	@mkdir -p $(dir $@)
	$(MINGW_32) $(COMMON_CFLAGS) -c $< -o $@

$(WIN_OBJ_DIR_64)/%.win.o: src/%.c
	@mkdir -p $(dir $@)
	$(MINGW_64) $(COMMON_CFLAGS) -c $< -o $@

#
# Run targets (Linux only)
#
run_32: $(LINUX_TARGET_32)
	@./$(GCC_BIN_DIR_32)/specseek

run_64: $(LINUX_TARGET_64)
	@./$(GCC_BIN_DIR_64)/specseek

#
# Clean
#
clean:
	rm -rf bin

.PHONY: all clean run_32 run_64
