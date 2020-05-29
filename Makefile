DEBUG=0
LAGFIX=1
TARGET_NAME = snes9x2002

TARGET := snes9x2002

PREFIX  = arm-linux

CXX	= $(PREFIX)-g++
CC	= $(PREFIX)-gcc
STRIP	= $(PREFIX)-strip
AS	= $(PREFIX)-as
GASM	= $(PREFIX)-g++

SYSROOT := $(shell $(CC) --print-sysroot)
SDL_CFLAGS := $(shell $(SYSROOT)/usr/bin/sdl-config --cflags)
SDL_LIBS := $(shell $(SYSROOT)/usr/bin/sdl-config --libs)

STATIC_LINKING := 1
fpic := -fno-PIC
SHARED := -Wl,--as-needed -Wl,--gc-sections -s
CFLAGS += -ffast-math -march=armv5te -mtune=arm926ej-s -marm
CFLAGS += -fno-builtin -fno-exceptions
CFLAGS += $(SDL_CFLAGS)
ARM_ASM = 0
ASM_CPU = 0
ASM_SPC700 = 0

CORE_DIR := ./src

ifeq ($(DEBUG), 1)
DEFINES += -O0 -g
else
DEFINES += -Ofast -DNDEBUG=1
endif

LDFLAGS += $(LIBM) $(SDL_LIBS) -lz

include Makefile.common

OBJECTS := $(SOURCES:.c=.o) $(SOURCES_ASM:.S=.o)

CFLAGS += $(DEFINES) $(COMMON_DEFINES) $(INCLUDES)

LDFLAGS += $(fpic)

FLAGS += $(fpic)

OBJOUT	= -o
LINKOUT	= -o
LD	= $(CC)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LINKOUT)$@ $(SHARED) $(OBJECTS) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $(OBJOUT)$@ $<

%.o: %.S
	$(CC) $(CFLAGS) -Wa,-I./src/ -c $(OBJOUT)$@ $<

format:
	find . -regex '.*\.\(c\|h\|cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean format
