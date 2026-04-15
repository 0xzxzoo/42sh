/*
** EPITECH PROJECT, 2025
** strncopy
** File description:
** delivery
*/

#include <unistd.h>
#include <stdio.h>
#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    for (; i < n; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
