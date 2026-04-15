/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** semicolone
*/

#include "42sh/my_shell.h"
#include "my.h"

void process_semicolons(char *line, char ***env)
{
    char **cmds = my_str_to_word_array(line, ";");

    if (!cmds)
        return;
    for (int i = 0; cmds[i] != NULL; i++)
        process_line(cmds[i], env);
    free_array(cmds);
}
