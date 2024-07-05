#include "Util/dictionary.h"

void init_dictionary(dictionary_t *dict)
{
    dict->size = 0;
}

void add_key_value_pair(dictionary_t *dict, const char *key, void *value, value_type_t value_type)
{
    if (dict->size < DICT_MAX_SIZE) {
        strcpy(dict->pairs[dict->size].key, key);
        dict->pairs[dict->size].value      = value;
        dict->pairs[dict->size].value_type = value_type;
        dict->size++;
    }
}

void set_dictionary_value(dictionary_t *dict, const char *key, float value)
{
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            switch (dict->pairs[i].value_type) {
                case UINT16_TYPE_RANDOLF:
                    *((uint16_t *)dict->pairs[i].value) = (uint16_t)value;
                    break;
                case UINT32_TYPE_RANDOLF:
                    *((uint32_t *)dict->pairs[i].value) = (uint32_t)value;
                    break;
                case INT32_TYPE_RANDOLF:
                    *((int32_t *)dict->pairs[i].value) = (int32_t)value;
                    break;
                case INT64_TYPE_RANDOLF:
                    *((int64_t *)dict->pairs[i].value) = (int64_t)value;
                    break;
                case INT_TYPE_RANDOLF:
                    *((int *)dict->pairs[i].value) = (int)value;
                    break;
                case DOUBLE_TYPE_RANDOLF:
                    *((double *)dict->pairs[i].value) = (double)value;
                    break;
                default:
                    *((float *)dict->pairs[i].value) = value;
                    break;
            }
        }
    }
}

float get_dictionary_value(dictionary_t *dict, const char *key)
{
    float tmp = 0;
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            switch (dict->pairs[i].value_type) {
                case UINT16_TYPE_RANDOLF:
                    tmp = (float)(*((uint16_t *)dict->pairs[i].value));
                    break;
                case UINT32_TYPE_RANDOLF:
                    tmp = (float)(*((uint32_t *)dict->pairs[i].value));
                    break;
                case INT32_TYPE_RANDOLF:
                    tmp = (float)(*((int32_t *)dict->pairs[i].value));
                    break;
                case INT64_TYPE_RANDOLF:
                    tmp = (float)(*((int64_t *)dict->pairs[i].value));
                    break;
                case INT_TYPE_RANDOLF:
                    tmp = (float)(*((int *)dict->pairs[i].value));
                    break;
                case DOUBLE_TYPE_RANDOLF:
                    tmp = (float)(*((double *)dict->pairs[i].value));
                    break;
                default:
                    tmp = *((float *)dict->pairs[i].value);
                    break;
            }
            return tmp;
        }
    }
    return 0;
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