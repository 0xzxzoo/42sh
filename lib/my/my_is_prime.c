/*
** EPITECH PROJECT, 2025
** is_prime
** File description:
** delivery
*/

#include "my.h"

int my_is_prime(int nb)
{
    if (nb < 1) {
        return 0;
    }
    for (int i = 2; i * i <= nb; ++i) {
        if ((nb % i) == 0)
            return 0;
    }
    return 1;
}
