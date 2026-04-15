/*
** EPITECH PROJECT, 2025
** printf_hex
** File description:
** delivery
*/

#include "flag.h"
#include "my.h"

int printf_hex(va_list args)
{
    long c = va_arg(args, int);

    if (c < 0)
        c = 4294967296 + c;
    my_flag_x(c);
    return 0;
}
