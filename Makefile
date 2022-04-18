CC=gcc
INCLUDE=include
CFLAGS=-Wall -Werror -Wextra -O2

REQUISITES=src/assembler.c src/fileio.c src/util.c \
		   src/argument.c src/opcode.c src/lexer.c \
		   src/stringx.c src/macro.c src/dict.c \
		   src/parser.c src/expected.c

bin/m4004as: $(REQUISITES)
	$(CC) -I $(INCLUDE) $^ -o $@ -Wall -Werror -Wextra -pedantic -O2 -ffunction-sections -fdata-sections
