/*
** EPITECH PROJECT, 2025
** swap
** File description:
** delivery
*/

#include <stdio.h>
#include "my.h"

void my_swap(int *a, int *b)
{
    int parameter = *a;

    *a = *b;
    *b = parameter;
}
