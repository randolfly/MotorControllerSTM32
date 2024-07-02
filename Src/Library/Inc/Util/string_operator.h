#ifndef __STRING_OPERATOR_H__
#define __STRING_OPERATOR_H__

#include <string.h>
/**
 * @brief seperate a string with delimiter ","
 * @param  src_string: target string
 * @param  dst_string_list: result string list
 * @param  num: number of the result string
 */
void seperate_string(char *src_string, char *dst_string_list[], int *num);

#endif // !__STRING_OPERATOR_H__
