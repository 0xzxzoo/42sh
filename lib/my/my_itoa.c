/*
** EPITECH PROJECT, 2026
** my_itoa.c
** File description:
** my_itoa
*/

#include "my.h"
#include <stdlib.h>

static int get_nb_len(long n)
{
    int len = 0;

    if (n == 0)
        return 1;
    if (n < 0) {
        len++;
        n = -n;
    }
    while (n > 0) {
        len++;
        n /= 10;
    }
    return len;
}

char *my_itoa(int nb)
{
    long n = nb;
    int len = get_nb_len(n);
    char *str = malloc(len + 1);

    if (!str)
        return NULL;
    str[len] = '\0';
    if (n == 0)
        str[0] = '0';
    if (n < 0) {
        str[0] = '-';
        n = -n;
    }
    while (n > 0) {
        len--;
        str[len] = (n % 10) + '0';
        n /= 10;
    }
    return str;
}
