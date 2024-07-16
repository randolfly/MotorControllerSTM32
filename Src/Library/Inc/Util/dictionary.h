/**
 * @file dictionary.h
 * @brief dictionary.h is designed to provide an interface of a dictionary data structure
 * for storing and managing key-value pair data, where value type is variant
 * @author randolf (1665718426@qq.com)
 * @version 1.0.1
 * @date 2024-07-03
 *
 * @copyright Copyright (c) 2024  randolf
 *
 */
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <stdio.h>
#include <string.h>

#ifdef STM32H743xx
#include "main.h"
#endif
#include "Util/type_def_protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DICT_MAX_SIZE  80
#define KEY_MAX_LENGTH 50

typedef enum {
    UINT8_TYPE_RANDOLF,
    UINT16_TYPE_RANDOLF,
    UINT32_TYPE_RANDOLF,
    INT32_TYPE_RANDOLF,
    INT64_TYPE_RANDOLF,
    INT_TYPE_RANDOLF,
    FLOAT_TYPE_RANDOLF,
    DOUBLE_TYPE_RANDOLF
} value_type_t;

typedef struct {
    char key[KEY_MAX_LENGTH];
    void *value;
    value_type_t value_type;
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
 * @param  key: key string
 * @param  value: value pointer
 * @param  value_type: value type
 */
void add_key_value_pair(dictionary_t *dict, const char *key, void *value, value_type_t value_type);

/**
 * @brief Get the value object
 * @param  dict: dictionary instance
 * @param  key: key
 * @return double : target double value
 */
double get_dictionary_value(dictionary_t *dict, const char *key);

/**
 * @brief Set the dictionary value
 * @param  dict: dictionary instance
 * @param  key: key
 * @param  value: value to be set, always double type
 */
void set_dictionary_value(dictionary_t *dict, const char *key, double value);

/**
 * @brief Get the all keys in dictionary
 * @param  dict: dictionary instance
 * @param char*: keys string separated by "," e.g. "key1,key2,key3"
 */
void get_all_keys(dictionary_t *dict, char *all_keys);

#ifdef __cplusplus
}
#endif

#endif // !__DICTIONARY_H__
