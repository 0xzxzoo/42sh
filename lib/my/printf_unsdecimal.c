/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_unsdecimal(va_list args)
{
    const unsigned int i = va_arg(args, unsigned int);

    my_put_unsigned_nbr(i);
    return 0;
}
