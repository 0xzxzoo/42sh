/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_float(va_list args)
{
    const float f = (float) va_arg(args, double);

    return my_put_float(f, 6);
}
