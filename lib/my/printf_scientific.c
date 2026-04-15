/*
** EPITECH PROJECT, 2025
** printf
** File description:
** printf_scientific
*/

#include "flag.h"
#include "my.h"

int printf_scientific(va_list args)
{
    const float f = (float) va_arg(args, double);

    return my_flag_e(f, 6);
}
