#include "../include/dict.h"

void dict_init(Dict* dict)
{
    dict->values = calloc(0, sizeof(uint32_t));
    dict->val_len = 0;
    init_strx_dynarr(&dict->keys);
}

void dict_add(Dict* dict, char* key, uint32_t value)
{
    // resize the values array
    (dict->val_len) ++;
    dict->values = realloc(dict->values, sizeof(uint32_t) * dict->val_len);
    dict->values[dict->val_len - 1] = value;
    // append the key to the dynamic array
    append_strx_dynarr(&dict->keys, new_strx(key));
}

uint32_t dict_get(Dict* dict, char* key)
{
    for (unsigned int i = 0; i < dict->keys.len; i++) {
        if (strcmp(key, dict->keys.strs[i].str) == 0) {
            return dict->values[i];
        }
    }
    return 0;
}

bool dict_contains_key(Dict* dict, char* key)
{
    for (unsigned int i = 0; i < dict->keys.len; i++) {
        if (strcmp(key, dict->keys.strs[i].str) == 0) {
            return true;
        }
    }
    return false;
}

void dict_free(Dict* dict)
{
    free(dict->values);
    free_strx_dynarr(&dict->keys);
}
