/*
** EPITECH PROJECT, 2025
** putchar
** File description:
** delivery
*/

#include "my.h"
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
