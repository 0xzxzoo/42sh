/*
** EPITECH PROJECT, 2025
** printf
** File description:
** my_isneg_printf
*/

#include "my.h"

void my_isneg_printf(int nb, int plus_flag)
{
    if (nb < 0) {
        my_putchar('-');
    } else if (plus_flag) {
        my_putchar('+');
    }
}
