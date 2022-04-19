/********************************************/
/* Micro 4004 Macro Assembler v1.1          */
/* Part of the Micro 4004 Toolkit           */
/*                                          */
/* MIT License, redistributable             */
/********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "../include/util.h"
#include "../include/argument.h"
#include "../include/fileio.h"
#include "../include/dict.h"
#include "../include/lexer.h"
#include "../include/parser.h"

// Main function - execution starts here.
int main(int argc, char** argv)
{
    printf("Micro4004 Macro Assembler [Version 1.1]\n"); 
    if (argc == 1) {
        printf("Usage: %s [-i <input file>] [-o <output file>]\n", argv[0]);
        exit(1);
    } else {
        Arguments args = parse_args(argc - 1, argv + 1);

        Lexer* lexer = init_lexer();
        char* open_file = load_file(args.in_file);
        lex(lexer, open_file);

        unsigned char* output = parse(lexer->tokens, lexer->token_count);
        write_binary_file(args.out_file, output, 256);
        free_lexer(lexer);
    }
    return 0;
}
