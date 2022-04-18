#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "opcode.h"

#define NOTDELIM(c) c != ',' && c != '\n' && c != ' ' && c != '\r' && c != '\t'
#define STRINGEQ(s1, s2) strcmp(s1, s2) == 0

// function to clear a character array and to also
// reset its length.
void clear_char_wlen(char** str, uint32_t* len);

// Copies a string into another malloc'd buffer.
char* malloc_copy(char* str);

// Function to append an AsmOp to a dynamic array of AsmOps.
void append_asmop(AsmOp** array, uint32_t* len, AsmOp op);

// Function to check if a hex string is valid.
int is_hex(char* str);

#endif
