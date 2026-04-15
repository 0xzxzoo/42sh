/*
** EPITECH PROJECT, 2025
** Project - atoi
** File description:
** Implementation for
** c
*/
int my_atoi(char *str)
{
    int result = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}
