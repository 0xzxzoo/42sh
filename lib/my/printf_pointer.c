/*
** EPITECH PROJECT, 2025
** Project - decimal
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_pointer(va_list args)
{
    unsigned long val = va_arg(args, unsigned long);

    my_flag_p(val);
    return 0;
}
