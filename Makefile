# MK-56 toolchain: assembler, emulator, tests

.PHONY: all test clean

all:
	$(MAKE) -C assembler
	$(MAKE) -C emulator

test: all
	$(MAKE) -C tests test

clean:
	$(MAKE) -C assembler clean
	$(MAKE) -C emulator clean
	$(MAKE) -C tests clean
