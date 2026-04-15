/*
** EPITECH PROJECT, 2025
** my_flag_x
** File description:
** delivery
*/

#include "my.h"
#include <stdio.h>
#include <unistd.h>

static void print_hex_u(unsigned int u)
{
    char c;
    unsigned int d = u % 16;

    if (u >= 16)
        print_hex_u(u / 16);
    if (d < 10)
        c = '0' + d;
    else
        c = 'a' + (d - 10);
    write(1, &c, 1);
}

int my_flag_x(int val)
{
    unsigned int u = (unsigned int)val;

    if (u == 0) {
        my_putchar('0');
        return 0;
    }
    print_hex_u(u);
    return 0;
}
