/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** readline
*/

#include "42sh/my_shell.h"
#include "my.h"

char *read_line(void)
{
    char *line;
    size_t bufsize;

    line = NULL;
    my_printf("> ");
    if (getline(&line, &bufsize, stdin) == -1) {
        line = NULL;
        my_printf("exit\n");
    }
    return line;
}
