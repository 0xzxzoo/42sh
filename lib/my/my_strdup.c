/*
** EPITECH PROJECT, 2026
** G-CPE-110-STG-1-1-secured-9
** File description:
** my_strdup
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    char *str;
    int len;

    len = my_strlen(src);
    str = malloc(sizeof(char) * ((unsigned long)len + 1));
    if (str == NULL)
        return NULL;
    my_strcpy(str, src);
    return str;
}
