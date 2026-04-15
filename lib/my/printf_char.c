/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_char(va_list args)
{
    const char c = va_arg(args, int);

    my_putchar(c);
    return 1;
}
