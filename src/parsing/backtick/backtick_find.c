/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** backtick_find
*/

#include "42sh/my_shell.h"
#include "my.h"

int find_backtick(char *str)
{
    int sq = 0;
    int dq = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\'' && !dq)
            sq = !sq;
        if (str[i] == '"' && !sq)
            dq = !dq;
        if (str[i] == '`' && !sq && !dq)
            return i;
    }
    return -1;
}
