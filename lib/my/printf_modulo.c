/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_modulo(va_list args)
{
    int m = va_arg(args, int);

    m = '%';
    my_putchar(m);
    return 1;
}
