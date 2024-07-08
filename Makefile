# Compiler
CC = gcc

# Directories
SRCDIR = src
BUILDDIR = build
INCDIR = include
CIMGUI_PATH = lib/cimgui
RAYLIB_CIMGUI_PATH = lib/raylib-cimgui

# Compiler flags
CFLAGS = -Wall -Wextra -I$(INCDIR) -I$(SRCDIR) -I$(CIMGUI_PATH) -I$(RAYLIB_CIMGUI_PATH)

# Linker flags
LDFLAGS = -L./lib/raylibs -L$(CIMGUI_PATH) -Wl,-rpath,$(CIMGUI_PATH) -lraylib -lm -lGL -lX11 -lpthread -ldl -lrt
LDLIBS = -L$(CIMGUI_PATH) -lcimgui -lstdc++

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c) $(RAYLIB_CIMGUI_PATH)/rlcimgui.c

# Object files
OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(SRCS)))

# Executable name
TARGET = main

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(RAYLIB_CIMGUI_PATH)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: all clean
