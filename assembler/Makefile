# MK56-ASM Assembler (C) Makefile

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -I../common
LDFLAGS = -lm

TARGET = mk56asm
SRCS = mk56asm.c main.c ../common/mk56_isa.c
OBJS = mk56asm.o main.o mk56_isa.o

.PHONY: all clean test install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c mk56asm.h ../common/mk56_isa.h
	$(CC) $(CFLAGS) -c -o $@ $<

mk56_isa.o: ../common/mk56_isa.c ../common/mk56_isa.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) *.lst

# Tests live in ../tests
test: $(TARGET)
	$(MAKE) -C ../tests test

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
