# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Linker flags
LDFLAGS = -lraylib -lm

# Source directory
SRCDIR = src

# Build directory
BUILDDIR = build

# Include directory
INCDIR = include

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

# Executable name
TARGET = main

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Phony targets
.PHONY: all clean
