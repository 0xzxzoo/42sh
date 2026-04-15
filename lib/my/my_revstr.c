/*
** EPITECH PROJECT, 2025
** revstr
** File description:
** a
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "my.h"

static int my_strlen2(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}

char *my_revstr(char *str)
{
    int a = my_strlen2(str);
    int b = a / 2;
    char temp;

    for (int i = 0; i < b; i++) {
        temp = str[i];
        str[i] = str[a - 1 - i];
        str[a - 1 - i] = temp;
    }
    return str;
}
