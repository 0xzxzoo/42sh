/*
** EPITECH PROJECT, 2025
** Project - put_uns_nbr
** File description:
** Implementation for
** c
*/

#include "my.h"

int my_put_unsigned_nbr(unsigned int nb)
{
    int count = 0;

    if (nb >= 10)
        count += my_put_unsigned_nbr(nb / 10);
    my_putchar((nb % 10) + '0');
    count++;
    return count;
}
