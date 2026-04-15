/*
** EPITECH PROJECT, 2025
** flag p
** File description:
** delivery
*/

#include "my.h"
#include <stdio.h>
#include <unistd.h>

static void print_flag_p(unsigned long u)
{
    char c;
    unsigned long d = u % 16;

    if (u >= 16) {
        print_flag_p(u / 16);
        print_flag_p(u % 16);
        return;
    }
    if (d < 10)
        c = '0' + d;
    else
        c = 'a' + (d - 10);
    write(1, &c, 1);
}

int my_flag_p(unsigned long val)
{
    if (val == 0) {
        write(1, "0x0", 3);
        return 0;
    }
    write(1, "0x", 2);
    print_flag_p(val);
    return 0;
}
