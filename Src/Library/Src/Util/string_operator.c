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

void join_string(char *src_string_list[], char *dst_string, int num)
{
    dst_string[0] = '\0';
    for (int i = 0; i < num; i++) {
        strcat(dst_string, src_string_list[i]);
        if (i < num - 1) {
            strcat(dst_string, ",");
        }
    }
}