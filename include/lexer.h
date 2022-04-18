#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "opcode.h"
#include "util.h"
#include "stringx.h"
#include "macro.h"
#include "dict.h"

typedef struct {
    AsmOp* tokens;
    Macro* macros;
    Stringx expr;
    uint32_t state;
    uint32_t token_count;
    uint32_t token_count_temp;
    uint32_t macro_count;
    AsmOp* tokens_temp;
} Lexer;

// Function to create a new pointer to a lexer.
Lexer* init_lexer();

// Function to free a lexer object from memory.
void free_lexer(Lexer* lexer);

// Function to perform lexical analysis on a char*
// string. The function produces a dynamic list in
// the form of the `tokens` variable.

void lex(Lexer* lexer, char* data);

// Function to app§end to the token list and to also clear
// the tokens variable.
void append_and_clear(Lexer* lex, Stringx* toks, AsmOp append);

// function to dump all of the tokens within the lexer
void dump_lexer(Lexer* lex);

#endif
