/*
** EPITECH PROJECT, 2025
** powerrec
** File description:
** s
*/

#include "my.h"

int my_compute_power_rec(int nb, int p)
{
    if (p < 0) {
        return 0;
    }
    if (p == 0) {
        return 1;
    }
    if (p % 2 == 0) {
        nb = my_compute_power_rec(nb, p / 2);
        return nb * nb;
    }
    --p;
    return (nb * my_compute_power_rec(nb, p));
}
