#ifndef __MACRO_H__
#define __MACRO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "opcode.h"

typedef struct {
    char* name;
    AsmOp* tokens;
    uint32_t len;
} Macro;

// Function to create a new macro.
Macro new_macro(char* name);

// Function to find a macro by a name.
// If no macro is found, NULL is returned.
Macro find_macro_by_name(char* name, Macro* macros, uint32_t len);

// Inline to find a macro by name, and exits with an
// error if no macro is found.
inline Macro FIND_MACRO(char* name, Macro* macros, uint32_t len)
{
    Macro macro = find_macro_by_name(name, macros, len);
    if (macro.name == NULL) {
        fprintf(stderr, "Error: Macro '%s' not found.\n", name);
        exit(1);
    }
    return macro;
}

// Function to append all tokens in a macro to a list
// of tokens.
void append_macro_tokens(Macro macro, AsmOp** tokens, uint32_t* len);

// Function to a free a macro after use
void free_macro(Macro* macro);

// Function to append a macro to a list of macros.
void append_macro(Macro macro, Macro** macros, uint32_t* macro_len);

// Function to dump data inside of a list of macros
void dump_macros(Macro* macros, uint32_t len);

// function to free a list of macros
void free_macro_list(Macro* macros, uint32_t macro_len);

#endif
