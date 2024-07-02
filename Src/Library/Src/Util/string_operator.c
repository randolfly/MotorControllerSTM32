#include "Util/string_operator.h"

void seperate_string(char *src_string, char *dst_string_list[], int *num)
{
    int i       = 0;
    char *token = strtok(src_string, ",");
    while (token != NULL) {
        dst_string_list[i] = token;
        token              = strtok(NULL, ",");
        i++;
    }
    *num = i;
}