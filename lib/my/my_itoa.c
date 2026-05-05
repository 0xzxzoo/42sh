/*
** EPITECH PROJECT, 2026
** my_itoa.c
** File description:
** my_itoa
*/

#include "my.h"
#include <stddef.h>
#include <stdlib.h>

char *my_itoa(int nb)
{
    char *str = malloc(12);
    int i = 0;
    long n = nb;

    if (!str) return NULL;
    if (n == 0) str[i++] = '0';
    if (n < 0) {
        str[i++] = '-';
        n = -n;
    }
    int start = i;
    while (n > 0) {
        str[i++] = (n % 10) + '0';
        n /= 10;
    }
    str[i] = '\0';
    for (int j = 0; j < (i - start) / 2; j++) {
        char tmp = str[start + j];
        str[start + j] = str[i - 1 - j];
        str[i - 1 - j] = tmp;
    }
    return str;
}
