/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_intoctal(va_list args)
{
    const unsigned int i = va_arg(args, unsigned int);

    my_put_octal(i);
    return 0;
}
