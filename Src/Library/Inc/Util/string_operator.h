#ifndef __STRING_OPERATOR_H__
#define __STRING_OPERATOR_H__

#include <string.h>
/**
 * @brief seperate a string with delimiter ","(notice that the raw string will be modified, ","->"\0")
 * @param  src_string: target string
 * @param  dst_string_list: result string list
 * @param  num: number of the result string
 */
void seperate_string(char *src_string, char *dst_string_list[], int *num);

/**
 * @brief join a string list into a string with delimiter ","
 * @param  src_string_list: source string list
 * @param  dst_string: result string
 * @param  num: number of the source string list
 */
void join_string(char *src_string_list[], char *dst_string, int num);

#endif // !__STRING_OPERATOR_H__
