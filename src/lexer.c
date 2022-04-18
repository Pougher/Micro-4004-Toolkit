#include "../include/lexer.h"

Lexer* init_lexer()
{
    Lexer* new_lexer = (Lexer*) malloc(sizeof(Lexer));
    new_lexer->state = 0;
    new_lexer->token_count = 0;
    new_lexer->tokens = calloc(0, 2);
    new_lexer->macros = calloc(0, sizeof(Macro));
    new_lexer->macro_count = 0;
    new_lexer->expr = new_strx("");
    return new_lexer;
}

void free_lexer(Lexer* lexer)
{
    // @NOTE: Don't need to free tokens state as it's not
    //        a pointer
    free(lexer->tokens);
    free(lexer);
}

void lex(Lexer* lexer, char* data)
{
    Stringx toks = new_strx("");
    Dict labels;
    Dict symbols;

    dict_init(&labels);
    dict_init(&symbols);

    unsigned int i = 0;
    unsigned int line = 1;
    unsigned int current_lbl_id = 0;

    bool bypass = false;
    bool macro = false;
    bool comment = false;

    unsigned int ram_ptr = 0;

    Macro current_macro = {0};

    while (data[i]) { // stop at null char
        if (NOTDELIM(data[i])) append_char_strx(&toks, data[i]);
        if (data[i] == '\n') {
            line++; 
            append_asmop(&lexer->tokens, &lexer->token_count, new_token(TOKEN_NEWLINE, 0));
            if (comment) {
                comment = false;
                clear_char_wlen(&toks.str, &toks.len);
            }
        }
        if (comment) { i++; continue; }

        if (!(NOTDELIM(data[i])) && toks.len > 0 && !bypass && !macro && !lexer->state) {
            if (data[i + 1] != ':') {
                Macro mac = find_macro_by_name(toks.str, lexer->macros, lexer->macro_count);
                if (mac.name != NULL) {
                    // expand the macro
                    append_macro_tokens(mac, &lexer->tokens, &lexer->token_count);
                    clear_char_wlen(&toks.str, &toks.len);
                } else if (dict_contains_key(&labels, toks.str)) {
                    // append the label id
                    append_and_clear(lexer, &toks, new_token(TOKEN_LABEL_REF, dict_get(&labels, toks.str)));
                } else if (dict_contains_key(&symbols, toks.str)) {
                    // append the symbol data
                    append_and_clear(lexer, &toks, new_token(TOKEN_INT, dict_get(&symbols, toks.str)));
                } else {
                    fprintf(stderr, "Line %d: Error: Syntax error: '%s'.\n", line, toks.str);
                    exit(1);
                }
            }
        }

        if (lexer->state == 1 && !bypass) {
            if (NOTDELIM(data[i])) {
                append_char_strx(&lexer->expr, data[i]);
            } else {
                // check for a redefinition of a previous macro
                if (lexer->macro_count > 0) {
                    if (dict_contains_key(&symbols, toks.str) || dict_contains_key(&labels, toks.str) || find_macro_by_name(toks.str, lexer->macros, lexer->macro_count).name != NULL) {
                        fprintf(stderr, "Line %d: Error: Identifier '%s' previously defined.\n", line, toks.str);
                        exit(1);
                    }
                }
                lexer->state = 0;
                current_macro.name = malloc_copy(lexer->expr.str);
                clear_char_wlen(&lexer->expr.str, &lexer->expr.len);
                clear_char_wlen(&toks.str, &toks.len);
                
                // perform a token buffer swap
                lexer->tokens_temp = lexer->tokens;
                lexer->tokens = calloc(0, 2);
                lexer->token_count_temp = lexer->token_count;
                lexer->token_count = 0;
                macro = true;
            }
        }

        if (lexer->state == 8 && !bypass) {
            if (NOTDELIM(data[i])) {
                append_char_strx(&lexer->expr, data[i]);
            } else {
                lexer->state = 0;
                if (dict_contains_key(&symbols, toks.str) || dict_contains_key(&labels, toks.str) || find_macro_by_name(toks.str, lexer->macros, lexer->macro_count).name != NULL) {
                    fprintf(stderr, "Line %d: Error: Identifier '%s' previously defined.\n", line, toks.str);
                    exit(1);
                }
                if (STRINGEQ(toks.str, "")) {
                    fprintf(stderr, "Line %d: Error: .offset without identifier.\n", line);
                    exit(1);
                }
                dict_add(&symbols, lexer->expr.str, ram_ptr + 0xf0);
                if (ram_ptr == 16) {
                    fprintf(stderr, "Line %d: Error: Out of memory allocation slots (max. 16 bytes).\n", line);
                    exit(1);
                }
                ram_ptr++;
                clear_char_wlen(&lexer->expr.str, &lexer->expr.len);
                clear_char_wlen(&toks.str, &toks.len);
            }
        }

        if (bypass) bypass = false;

        // directives
        if (STRINGEQ(toks.str, ".macro")) {
            clear_char_wlen(&toks.str, &toks.len);
            lexer->state = 1;
            bypass = true;
        }
        
        if (STRINGEQ(toks.str, ".offset")) {
            clear_char_wlen(&toks.str, &toks.len);
            lexer->state = 8;
            bypass = true;
        }

        if (STRINGEQ(toks.str, ".end")) {
            if (!macro) {
                fprintf(stderr, "Line %d: Error: .end without .macro.\n", line);
                exit(1);
            }
            clear_char_wlen(&toks.str, &toks.len);
            current_macro.tokens = lexer->tokens;
            current_macro.len = lexer->token_count;
            // perform yet another token buffer swap
            lexer->tokens = lexer->tokens_temp;
            lexer->token_count = lexer->token_count_temp;
            // append macro to macro list
            append_macro(current_macro, &lexer->macros, &lexer->macro_count);
            macro = false;
        }

        if (data[i] ==  ';') {
            comment = true;
            clear_char_wlen(&toks.str, &toks.len);
        }

        // opcodes
        if (STRINGEQ(toks.str, "lda")) append_and_clear(lexer, &toks, new_token(TOKEN_LDA, 0));
        if (STRINGEQ(toks.str, "ldx")) append_and_clear(lexer, &toks, new_token(TOKEN_LDX, 0));
        if (STRINGEQ(toks.str, "lra"))  append_and_clear(lexer, &toks, new_token(TOKEN_LRA, 0));
        if (STRINGEQ(toks.str, "lrx"))  append_and_clear(lexer, &toks, new_token(TOKEN_LRX, 0));
        if (STRINGEQ(toks.str, "sta")) append_and_clear(lexer, &toks, new_token(TOKEN_STA, 0));
        if (STRINGEQ(toks.str, "xor")) append_and_clear(lexer, &toks, new_token(TOKEN_XOR, 0));
        if (STRINGEQ(toks.str, "add")) append_and_clear(lexer, &toks, new_token(TOKEN_ADD, 0));
        if (STRINGEQ(toks.str, "sub")) append_and_clear(lexer, &toks, new_token(TOKEN_SUB, 0));
        if (STRINGEQ(toks.str, "and")) append_and_clear(lexer, &toks, new_token(TOKEN_AND, 0));
        if (STRINGEQ(toks.str, "or"))  append_and_clear(lexer, &toks, new_token(TOKEN_OR, 0));
        if (STRINGEQ(toks.str, "not")) append_and_clear(lexer, &toks, new_token(TOKEN_NOT, 0));
        if (STRINGEQ(toks.str, "jmp")) append_and_clear(lexer, &toks, new_token(TOKEN_JMP, 0));
        if (STRINGEQ(toks.str, "jz"))  append_and_clear(lexer, &toks, new_token(TOKEN_JZ, 0));
        if (STRINGEQ(toks.str, "jc"))  append_and_clear(lexer, &toks, new_token(TOKEN_JC, 0));
        if (STRINGEQ(toks.str, "tax")) append_and_clear(lexer, &toks, new_token(TOKEN_TAX, 0));
        if (STRINGEQ(toks.str, "txa")) append_and_clear(lexer, &toks, new_token(TOKEN_TXA, 0));
        
        // registers
        if (STRINGEQ(toks.str, "%ra")) append_and_clear(lexer, &toks, new_token(TOKEN_REG_A, 0));
        if (STRINGEQ(toks.str, "%rx")) append_and_clear(lexer, &toks, new_token(TOKEN_REG_X, 0));

        // integer handling (hex)
        if (toks.len > 0) {
            if (toks.str[toks.len - 1] == 'h') {
                // check if the token is a valid hex number
                char* copy = malloc_copy(toks.str);
                copy[toks.len - 1] = '\0';
                if (is_hex(copy)) {
                    if (toks.len == 1) {
                        fprintf(stderr, "Line %d: Error: Hex literal without value.\n", line);
                        exit(1);
                    }
                    uint8_t value = (uint8_t) strtoul(copy, NULL, 16);
                    append_and_clear(lexer, &toks, new_token(TOKEN_INT, value));
                }
                free(copy);
            } else if (toks.str[toks.len - 1] == ':') {
                if (toks.len == 1) {
                    fprintf(stderr, "Line %d: Error: Label without identifier.\n", line);
                    exit(1);
                }
                toks.str[toks.len - 1] = '\0';
                if (dict_contains_key(&symbols, toks.str) || dict_contains_key(&labels, toks.str) || find_macro_by_name(toks.str, lexer->macros, lexer->macro_count).name != NULL) {
                    fprintf(stderr, "Line %d: Error: Identifier '%s' previously defined.\n", line, toks.str);
                    exit(1);
                }
                dict_add(&labels, toks.str, current_lbl_id);
                append_and_clear(lexer, &toks, new_token(TOKEN_LABEL_DECL, current_lbl_id));
                current_lbl_id++;
            }
        }
        i++;
    }

    // clean up (can't have any memory leaks in here!)
    free_macro_list(lexer->macros, lexer->macro_count);
    free_strx(&toks);
    dict_free(&symbols);
    dict_free(&labels);
}

void append_and_clear(Lexer* lex, Stringx* toks, AsmOp append)
{
    append_asmop(&lex->tokens, &lex->token_count, append);
    clear_char_wlen(&toks->str, &toks->len);
}

void dump_lexer(Lexer* lex)
{
    for (uint32_t i = 0; i < lex->token_count; i++) {
        printf("Token type: %d | Token value: %d\n", lex->tokens[i] >> 8, lex->tokens[i] & 0xff);
    }
}
