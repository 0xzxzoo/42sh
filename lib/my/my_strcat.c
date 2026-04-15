/*
** EPITECH PROJECT, 2025
** strcat
** File description:
** c
*/

#include "my.h"
#include <string.h>
#include <stdio.h>

char *my_strcat(char *dest, char const *src)
{
    int len;
    int i;

    len = my_strlen(dest);
    i = 0;
    while (src[i] != '\0') {
        dest[len + i] = src[i];
        ++i;
    }
    dest[len + i] = '\0';
    return (dest);
}
