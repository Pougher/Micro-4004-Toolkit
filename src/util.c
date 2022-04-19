#include "../include/util.h"

void clear_char_wlen(char** argument, uint32_t* len)
{
    free(*argument);
    *argument = calloc(1, sizeof(char));
    *len = 0;
}

char* malloc_copy(char* str)
{
    char* copy = calloc(strlen(str) + 1, sizeof(char));
    strcpy(copy, str);
    return copy;
}

void append_asmop(AsmOp** array, uint32_t* len, AsmOp op)
{
    *array = realloc(*array, sizeof(AsmOp) * (*len + 1));
    (*array)[*len] = op;
    (*len)++;
}

int is_hex(char* str)
{
    int is_hex_ = 1;

    for (unsigned int i = 0; i < strnlen(str, 256); i++) {
        if (isxdigit(str[i]) == 0) {
            is_hex_ = 0;
            break;
        }
    }
    return is_hex_;
}

void delay( int millis )
{
    #ifdef _WIN32
        Sleep( millis );
    #else
        uint64_t time = (uint64_t)((((double)clock() / CLOCKS_PER_SEC)) * 1000 + millis);
        while ((uint64_t)((((double)clock() / CLOCKS_PER_SEC)) * 1000) < time);
    #endif
}
