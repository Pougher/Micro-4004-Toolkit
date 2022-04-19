CC=gcc
INCLUDE=include
CFLAGS=-Wall -Werror -Wextra -O2 -pedantic -ffunction-sections -fdata-sections

REQUISITES_AS=src/assembler.c src/fileio.c src/util.c \
		      src/argument.c src/opcode.c src/lexer.c \
		      src/stringx.c src/macro.c src/dict.c \
		   	  src/parser.c src/expected.c

REQUISITES_EM=src/emulator.c src/fileio.c src/cpu.c \
			  src/opcode.c src/util.c

all: bin/m4004as bin/m4004emu

bin/m4004emu: $(REQUISITES_EM)
	$(CC) -I $(INCLUDE) $^ -o $@ $(CFLAGS)
bin/m4004as: $(REQUISITES_AS)
	$(CC) -I $(INCLUDE) $^ -o $@ $(CFLAGS)
