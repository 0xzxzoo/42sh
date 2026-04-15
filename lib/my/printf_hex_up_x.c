/*
** EPITECH PROJECT, 2025
** printf_hax_X
** File description:
** dleivery
*/

#include "flag.h"
#include "my.h"

int printf_hex_up_x(va_list args)
{
    long c = va_arg(args, int);

    if (c < 0)
        c = 4294967296 + c;
    my_flag_up_x(c);
    return 0;
}
