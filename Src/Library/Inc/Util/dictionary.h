#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <stdio.h>
#include <string.h>

#ifdef STM32H743xx
#include "main.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DICT_MAX_SIZE 50

typedef struct
{
    char key[20];
    float *value;
} key_value_pair_t;

typedef struct
{
    key_value_pair_t pairs[DICT_MAX_SIZE];
    int size;
} dictionary_t;

/**
 * @brief initialize the dictionary
 * @param  dict
 */
void init_dictionary(dictionary_t *dict);

/**
 * @brief add key value pair to the dictionary
 * @param  dict: dictionary instance
 * @param  key: key
 * @param  value: value
 */
void add_key_value_pair(dictionary_t *dict, const char *key, float *value);

/**
 * @brief Get the value object
 * @param  dict: dictionary instance
 * @param  key: key
 * @return float* : value
 */
float *get_value(dictionary_t *dict, const char *key);

#ifdef __cplusplus
}
#endif

#endif // !__DICTIONARY_H__
