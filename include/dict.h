#ifndef __DICT_H__
#define __DICT_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stringx.h"

typedef struct {
    StringxDynamicArray keys;
    uint32_t* values;
    uint32_t val_len;
} Dict;

// dictionary init function
void dict_init(Dict* dict);

// dictionary add function
void dict_add(Dict* dict, char* key, uint32_t value);

// dictionary get function
uint32_t dict_get(Dict* dict, char* key);

// dictionary contains key function - returns
// false if the dictionary does not contain the
// specified key, true otherwise.
bool dict_contains_key(Dict* dict, char* key);

// dictionary free function
void dict_free(Dict* dict);
#endif
