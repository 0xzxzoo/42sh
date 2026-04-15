/*
** EPITECH PROJECT, 2025
** strcopy
** File description:
** delivery
*/

#include <stdio.h>
#include "my.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (i = 0; src[i]; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
