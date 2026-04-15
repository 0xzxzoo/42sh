/*
** EPITECH PROJECT, 2025
** strcmp
** File description:
** s
*/

#include "my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] > s2[i])
            return (s1[i] - s2[i]);
        if (s1[i] < s2[i])
            return (s1[i] - s2[i]);
        else
            ++i;
    }
    return (0);
}
