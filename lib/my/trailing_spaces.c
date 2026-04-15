/*
** EPITECH PROJECT, 2025
** printf
** File description:
** trailing_spaces
*/

#include "my.h"

void trailing_spaces(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    i--;
    while (i >= 0 && str[i] == ' ')
        i--;
    str[i + 1] = '\0';
}
