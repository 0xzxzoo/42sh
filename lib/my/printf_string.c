/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "flag.h"
#include "my.h"

int printf_string(va_list args)
{
    const char *str = va_arg(args, const char *);

    if (!str) {
        my_putstr("(null)");
        return 0;
    }
    my_putstr(str);
    return my_strlen(str);
}
