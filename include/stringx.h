#ifndef __STRINGX_H__
#define __STRINGX_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "util.h"

typedef struct {
    char* str;
    uint32_t len;
} Stringx;

typedef struct {
    Stringx* strs;
    uint32_t len;
} StringxDynamicArray;

// function to create a new string
Stringx new_strx(char* data);

// Append a character to a string
void append_char_strx(Stringx* str, char c);

// Append a string to another string
void append_string_strx(Stringx* str, const char* str2);

// Free(s) the string data within the struct.
void free_strx(Stringx* str);

// Create a new dynamic array of strings
void init_strx_dynarr(StringxDynamicArray* arr);

// Free the dynamic array of strings
void free_strx_dynarr(StringxDynamicArray* arr);

// Append a string to the dynamic array
void append_strx_dynarr(StringxDynamicArray* arr, Stringx str);

#endif
