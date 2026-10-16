# MK-56 test suite

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -I../emulator -I../common -I../assembler
LDFLAGS = -lm

.PHONY: test clean

PROGRAMS = $(wildcard ../asm/examples/*.asm ../programs/listings/*.mk56) notation.mk56

test: test_core mk56test
	./test_core
	./mk56test $(PROGRAMS)

CORE = ../emulator/mk56emu.c ../common/mk56_isa.c

test_core: test_core.c $(CORE) ../emulator/mk56emu.h ../common/mk56_isa.h
	$(CC) $(CFLAGS) -o $@ test_core.c $(CORE) $(LDFLAGS)

mk56test: mk56test.c $(CORE) ../assembler/mk56asm.c ../assembler/mk56asm.h
	$(CC) $(CFLAGS) -o $@ mk56test.c $(CORE) ../assembler/mk56asm.c $(LDFLAGS)

clean:
	rm -f test_core mk56test
