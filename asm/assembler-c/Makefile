# MK56-ASM Assembler (C) Makefile

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11
LDFLAGS = -lm

TARGET = mk56asm
SRCS = mk56asm.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean test install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c mk56asm.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) *.lst

test: $(TARGET)
	@echo "=== Testing sinh.asm ==="
	./$(TARGET) ../examples/sinh.asm -v -l sinh_test.lst
	@echo ""
	@echo "=== Testing factorial.asm ==="
	./$(TARGET) ../examples/factorial.asm -v
	@echo ""
	@echo "=== All tests passed ==="

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
