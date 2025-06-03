#
# Target Output Details
#
TARGET = specseek_64

#
# Compilers for Differing Targets
#
CC ?= gcc

#
# Flag Options
# 
CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -O2 -I include

#
# Output directories as variables
#
GCC_BIN_DIR_64 = bin
GCC_OBJ_DIR_64 = $(GCC_BIN_DIR_64)/obj

#
# Detect Source files in Code, this is very broad
# and will just compile anything it finds
#
SRCS = $(shell find src -name '*.c')

#
# Object files per arch
#
GCC_OBJS_64 = $(patsubst src/%.c, $(GCC_OBJ_DIR_64)/%.gcc.o, $(SRCS))

#
# Default Command (no args) Build all 4 binaries
#
all: $(TARGET) 

#
# GCC 64-bit build
#
$(TARGET): $(GCC_OBJS_64)
	@mkdir -p $(GCC_BIN_DIR_64)
	$(CC) $(CFLAGS) -o $(GCC_BIN_DIR_64)/$(TARGET) $^


#
# Object build rules per architecture
#
$(GCC_OBJ_DIR_64)/%.gcc.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#
# Clean
#
clean:
	rm -rf bin

.PHONY: all clean