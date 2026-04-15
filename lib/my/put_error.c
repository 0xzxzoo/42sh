/*
** EPITECH PROJECT, 2025
** puterror
** File description:
** a
*/

#include "my.h"
#include <unistd.h>

void put_error(const char *str)
{
    (void) write(2, str, (size_t) my_strlen(str));
}
