#include "../include/stringx.h"

Stringx new_strx(char* data)
{
    Stringx new_str = {
        .str = malloc_copy(data),
        .len = strlen(data)
    };
    return new_str;
}

void append_char_strx(Stringx* str, char c)
{
    str->len ++;
    str->str = realloc(str->str, str->len + 1);
    str->str[str->len - 1] = c;
    str->str[str->len] = '\0';
}

void append_string_strx(Stringx* str, const char* str2)
{
    str->len += strlen(str2);
    str->str = realloc(str->str, str->len + 1);
    strcat(str->str, str2);
}

void free_strx(Stringx* str)
{
    free(str->str);
}

void init_strx_dynarr(StringxDynamicArray* arr)
{
    arr->len = 0;
    arr->strs = calloc(0, sizeof(Stringx));
}

void free_strx_dynarr(StringxDynamicArray* arr)
{
    for (unsigned int i = 0; i < arr->len; i++) {
        free_strx(&arr->strs[i]);
    }
    free(arr->strs);
}

void append_strx_dynarr(StringxDynamicArray* arr, Stringx str)
{
    arr->len ++;
    arr->strs = realloc(arr->strs, arr->len * sizeof(Stringx));
    arr->strs[arr->len - 1] = str;
}
