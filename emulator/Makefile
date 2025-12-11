# MK56 Emulator Makefile

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11
LDFLAGS = -lm -lncurses

TARGET = mk56emu
SRCS = mk56emu.c mk56ui.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c mk56emu.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)

# Test with sinh program
test: $(TARGET)
	@echo "=== Testing sinh(1) = 1.1752012 ==="
	./$(TARGET) ../asm/examples/sinh.bin -c -i 1
	@echo ""
	@echo "=== Testing factorial(5) = 120 ==="
	./$(TARGET) ../asm/examples/factorial.bin -c -i 5

# Disassemble example
disasm: $(TARGET)
	./$(TARGET) ../asm/examples/sinh.bin -d

# Run with TUI
run: $(TARGET)
	./$(TARGET) ../asm/examples/sinh.bin

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
