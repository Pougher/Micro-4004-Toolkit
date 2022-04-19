#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


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

// Function to delay execution for a specified number of milliseconds.
void delay(int millis);

#endif
