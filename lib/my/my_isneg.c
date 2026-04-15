/*
** EPITECH PROJECT, 2025
** isneg
** File description:
** delivery
*/

#include "my.h"

void my_isneg(int nb)
{
    if (nb < 0) {
        my_putchar('N');
    } else {
        my_putchar('P');
    }
}
