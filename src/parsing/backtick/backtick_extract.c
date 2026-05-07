/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** backtick_extract
*/

#include "42sh/my_shell.h"

char *extract_backtick_cmd(char *str, int start)
{
    int i = start + 1;
    int end = -1;

    for (; str[i]; i++) {
        if (str[i] == '`') {
            end = i;
            break;
        }
    }
    if (end == -1)
        return NULL;
    return my_strndup(str + start + 1, end - start - 1);
}
