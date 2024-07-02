#include "Util/dictionary.h"

void init_dictionary(dictionary_t *dict)
{
    dict->size = 0;
}

void add_key_value_pair(dictionary_t *dict, const char *key, float *value)
{
    if (dict->size < DICT_MAX_SIZE) {
        strcpy(dict->pairs[dict->size].key, key);
        dict->pairs[dict->size].value = value;
        dict->size++;
    }
}

float *get_value(dictionary_t *dict, const char *key)
{
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return (dict->pairs[i].value);
        }
    }
    return NULL;
}

void get_all_keys(dictionary_t *dict, char *all_keys)
{
    all_keys[0] = '\0';

    for (int i = 0; i < dict->size; i++) {
        strcat(all_keys, dict->pairs[i].key);
        if (i < dict->size - 1) {
            strcat(all_keys, ",");
        }
    }
}