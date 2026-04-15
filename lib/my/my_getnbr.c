/*
** EPITECH PROJECT, 2025
** getnbr
** File description:
** delivery
*/

#include "my.h"

int my_getnbr(char const *str)
{
    int i = 0;
    int signe = 1;
    long long nb = 0;

    for (; str[i] == '-' || str[i] == '+'; i++) {
        if (str[i] == '-')
            signe = signe * -1;
    }
    for (; str[i] != 0 && str[i] >= '0' && str[i] <= '9'; i++) {
        nb = nb * 10 + (str[i] - '0');
        if ((signe == 1 && nb > 2147483647) ||
            (signe == -1 && nb < -2147483648))
            return 0;
    }
    return nb * signe;
}
