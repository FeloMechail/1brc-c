# Compiler and flags
CC = gcc
CFLAGS = -O3 -funroll-loops -m64 -march=native -std=c17 -mtune=native -flto -Wall -Wextra -Wconversion -Wformat -Wformat=2 -Wimplicit-fallthrough -Wvla

# Target executable
TARGET = bin/myprogram

# Source files
SRCS = main2.c hash.c

# Object files
OBJS = $(patsubst %.c,bin/%.o,$(SRCS))

# Header files
HEADERS = hash.h

# Default target
all: $(TARGET)

# Rule to create the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to create object files
bin/%.o: %.c $(HEADERS)
	mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

#build with -pg for gprof:
gprof: CFLAGS += -pg
gprof: all

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
