/*
** EPITECH PROJECT, 2025
** my_put_ocatal
** File description:
** delivery
*/

#include "my.h"

int my_put_octal(unsigned int n)
{
    if (n >= 8)
        my_put_octal(n / 8);
    my_putchar((n % 8) + '0');
    return 0;
}
