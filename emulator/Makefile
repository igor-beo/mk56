# MK56 Emulator Makefile

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -I../common -I../assembler
LDFLAGS = -lm -lncurses

TARGET = mk56emu
OBJS = mk56emu.o mk56ui.o main.o mk56_isa.o mk56asm.o

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c mk56emu.h ../common/mk56_isa.h
	$(CC) $(CFLAGS) -c -o $@ $<

mk56_isa.o: ../common/mk56_isa.c ../common/mk56_isa.h
	$(CC) $(CFLAGS) -c -o $@ $<

mk56asm.o: ../assembler/mk56asm.c ../assembler/mk56asm.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS)

# Tests live in ../tests
test: $(TARGET)
	$(MAKE) -C ../tests test


# Disassemble example
disasm: $(TARGET)
	./$(TARGET) ../asm/examples/sinh.asm -d

# Run with TUI
run: $(TARGET)
	./$(TARGET) ../asm/examples/sinh.asm

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
