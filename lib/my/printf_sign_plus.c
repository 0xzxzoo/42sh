/*
** EPITECH PROJECT, 2025
** printf
** File description:
** printf_sign_plus
*/

#include "flag.h"
#include "my.h"

int printf_sign_plus(va_list args)
{
    const int n = va_arg(args, int);

    my_isneg_printf(n, 1);
    my_put_nbr(n < 0 ? -n : n);
    return 0;
}
