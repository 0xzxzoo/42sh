/*
** EPITECH PROJECT, 2025
** Project - flag e pritnf
** File description:
** Implementation for
** c
*/

#include "my.h"

static int nb_conditions(float nb, int precision)
{
    if (nb != nb) {
        my_putstr("NaN");
        return 0;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb == 0) {
        my_putchar('0');
        my_putchar('.');
        for (int i = 0; i < precision; ++i)
            my_putchar('0');
        my_putstr("e+00");
        return 1;
    }
    return 0;
}

static int moove(float nb)
{
    int exp = 0;

    while (nb >= 10.0) {
        nb /= 10.0;
        exp++;
    }
    while (nb < 1.0) {
        nb *= 10.0;
        exp--;
    }
    return exp;
}

int my_flag_e(float nb, const int precision)
{
    int exp;
    int integer;

    integer = (int)nb;
    my_put_nbr(integer);
    my_putchar('.');
    for (int i = 0; i < precision; ++i) {
        nb = nb - (int)nb;
        nb *= 10;
        my_put_nbr((int)nb);
    }
    my_put_nbr(exp);
    if (nb_conditions(nb, precision))
        return 0;
    my_put_nbr(exp);
    return 0;
}
