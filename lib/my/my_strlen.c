/*
** EPITECH PROJECT, 2025
** strlen
** File description:
** delivery
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "my.h"

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}
