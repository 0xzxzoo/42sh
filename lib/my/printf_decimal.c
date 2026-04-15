/*
** EPITECH PROJECT, 2025
** Project - decimal
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_decimal(va_list args)
{
    const int n = va_arg(args, int);

    my_put_nbr(n);
    return 0;
}
