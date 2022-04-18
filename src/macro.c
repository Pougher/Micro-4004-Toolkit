#include "macro.h"

Macro new_macro(char* name)
{
    Macro new_macro = {
        .name = malloc_copy(name),
        .tokens = NULL,
        .len = 0
    };
    return new_macro;
}

Macro find_macro_by_name(char* name, Macro* macros, uint32_t macro_len)
{
    unsigned int i = 0;
    while (i < macro_len) {
        if (strcmp(macros[i].name, name) == 0) {
            return macros[i];
        }
        i++;
    }
    return (Macro) {
        .name = NULL,
        .tokens = NULL,
        .len = 0
    };
}

void append_macro_tokens(Macro macro, AsmOp** tokens, uint32_t* len)
{
    for (uint32_t i = 0; i < macro.len; i++) {
        append_asmop(tokens, len, macro.tokens[i]);
    }
}

void free_macro(Macro* macro)
{
    macro->len = 0;
    free(macro->tokens);
}

void append_macro(Macro macro, Macro** macros, uint32_t* macro_len)
{
    *macros = realloc(*macros, sizeof(Macro) * (*macro_len + 2));
    (*macros)[*macro_len] = macro;
    (*macro_len)++;
}

void dump_macros(Macro* macros, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        printf("Macro: %s\n", macros[i].name);
        for (uint32_t j = 0; j < macros[i].len; j++) {
            printf("\tToken type: %d | Token value: %d\n", macros[i].tokens[j] >> 8, macros[i].tokens[j] & 0xFF);
        }
    }
}

void free_macro_list(Macro* macros, uint32_t macro_len)
{
    for (uint32_t i = 0; i < macro_len; i++) {
        free_macro(&macros[i]);
    }
}
