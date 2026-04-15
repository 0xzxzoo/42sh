/*
** EPITECH PROJECT, 2025
** square_root
** File description:
** delivery
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int i = 1;

    if (nb <= 0) {
        return 0;
    }
    for (; i * i < nb; ++i);
    if (i * i == nb){
        return i;
    }
    return 0;
}
