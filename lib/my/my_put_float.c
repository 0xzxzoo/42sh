/*
** EPITECH PROJECT, 2025
** Project - put_float
** File description:
** Implementation for
** c
*/

#include "my.h"

static void my_put_float_decimals(float nb, const int precision)
{
    int digit;
    int i = 0;

    while (i < precision) {
        nb = nb - (int)nb;
        nb *= 10;
        digit = (int)nb;
        if (digit < 0) {
            digit = -digit;
        }
        my_put_nbr(digit);
        i = i + 1;
    }
}

int my_put_float(float nb, const int precision)
{
    int integer;

    if (nb != nb) {
        my_putstr("NaN");
        return 0;
    }
    integer = (int)nb;
    if (integer == 0 && nb < 0) {
        my_putchar('-');
    }
    my_put_nbr(integer);
    my_putchar('.');
    my_put_float_decimals(nb, precision);
    return 0;
}
