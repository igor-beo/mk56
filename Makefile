# MK-56 toolchain: assembler, emulator, tests

.PHONY: all test clean asm-library

all:
	$(MAKE) -C assembler
	$(MAKE) -C emulator

test: all
	$(MAKE) -C tests test

# Regenerate the MK56-ASM form of every book listing
asm-library: all
	@for f in programs/listings/*.mk56; do \
	  ./assembler/mk56asm $$f -o /dev/null -s programs/asm/$$(basename $$f .mk56).asm >/dev/null || exit 1; \
	done; echo "programs/asm regenerated"

clean:
	$(MAKE) -C assembler clean
	$(MAKE) -C emulator clean
	$(MAKE) -C tests clean
