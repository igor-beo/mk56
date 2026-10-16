# MK-56 test suite

CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11 -I../emulator -I../common -I../assembler
LDFLAGS = -lm

.PHONY: test clean asm-sync

PROGRAMS = $(wildcard ../asm/examples/*.asm ../programs/listings/*.mk56 ../programs/asm/*.asm) notation.mk56
LISTINGS = $(wildcard ../programs/listings/*.mk56)
MK56ASM = ../assembler/mk56asm

test: test_core mk56test asm-sync
	./test_core
	./mk56test $(PROGRAMS)

# programs/asm/*.asm must be what mk56asm -s makes from programs/listings/
asm-sync:
	@stale=0; for f in $(LISTINGS); do \
	  b=$$(basename $$f .mk56); \
	  $(MK56ASM) $$f -o /dev/null -s - 2>&1 | cmp -s - ../programs/asm/$$b.asm \
	    || { echo "  STALE programs/asm/$$b.asm (run: make asm-library)"; stale=1; }; \
	done; test $$stale = 0 && echo "programs/asm in sync with programs/listings"

CORE = ../emulator/mk56emu.c ../common/mk56_isa.c

test_core: test_core.c $(CORE) ../emulator/mk56emu.h ../common/mk56_isa.h
	$(CC) $(CFLAGS) -o $@ test_core.c $(CORE) $(LDFLAGS)

mk56test: mk56test.c $(CORE) ../assembler/mk56asm.c ../assembler/mk56asm.h
	$(CC) $(CFLAGS) -o $@ mk56test.c $(CORE) ../assembler/mk56asm.c $(LDFLAGS)

clean:
	rm -f test_core mk56test
