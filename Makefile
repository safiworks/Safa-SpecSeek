#
# Target Output Details
#
LINUX_TARGET = specseek
WINDOWS_TARGET = specseek.exe

#
# Compilers for Differing Targets
#
GCC = gcc
MINGW = x86_64-w64-mingw32-gcc

#
# Flag Options for Compilers
# 
GCC_CFLAGS = -Wall -Wextra -Werror -Wno-unused-parameter -O2 -m32
MINGW_CFLAGS = -Wall -Wextra -Werror -O2 -m32

#
# Detect Source files in Code, this is very broad
# and will just compile anything it finds
#
SRCS = $(shell find src -name '*.c')

#
# Object files (Seperated because it caused linking problems)
#
GCC_OBJS = $(SRCS:.c=.gcc.o)
WIN_OBJS = $(SRCS:.c=.win.o)

#
# Default Command (no args) GCC Build
#
all: $(LINUX_TARGET)

$(LINUX_TARGET): $(GCC_OBJS)
	$(GCC) $(GCC_CFLAGS) -o bin/$(LINUX_TARGET) $^

#
# Windows Build `make windows` (mingw)
#
windows: $(WINDOWS_TARGET)

$(WINDOWS_TARGET): $(WIN_OBJS)
	$(MINGW) $(MINGW_CFLAGS) -o bin/$(WINDOWS_TARGET) $^

#
# Object Construct Rules (Apply flags per Target)
#
%.gcc.o: %.c
	$(GCC) $(GCC_CFLAGS) -c $< -o $@

%.win.o: %.c
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
	@./bin/$(LINUX_TARGET)
else ifeq ($(PLATFORM),mac)
	@$(MAKE) all
	@./bin/$(LINUX_TARGET)
else
	@$(MAKE) windows
	@./bin/$(WINDOWS_TARGET)
endif

#
# Clean Source Dir
#
clean:
	rm -f bin/$(LINUX_TARGET) bin/$(WINDOWS_TARGET)
	find . -name '*.gcc.o' -delete
	find . -name '*.win.o' -delete

.PHONY: all windows clean run
