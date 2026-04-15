/*
** EPITECH PROJECT, 2025
** strncmp
** File description:
** s
*/

#include "my.h"

int my_strncmp(char const *s1, char const *s2, int nb)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] && s2[i] && i < nb) {
        i = i + 1;
    }
    if ((s1[i] == '\0' && s2[i] == '\0') || i == nb) {
        return (0);
    } else if (s1[i] > s2[i]) {
        return (1);
    } else {
        return (-1);
    }
}
