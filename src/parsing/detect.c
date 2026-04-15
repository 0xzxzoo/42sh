/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** detect
*/

#include "42sh/my_shell.h"
#include "my.h"

static const builtin_t BUILTIN[] = {
    {"cd", my_cd},
    {"setenv", my_setenv},
    {"unsetenv", my_unsetenv},
    {"exit", my_exit},
    {"shinfo", my_info},
    {NULL, NULL}
};

int detect_pipe(char *line, char ***env)
{
    char **cmds;

    cmds = my_str_to_word_array(line, "|");
    if (!cmds || !cmds[0])
        return 0;
    if (cmds[1] != NULL)
        process_line(line, env);
    else
        pid(cmds[0], env);
    free_array(cmds);
    return 0;
}

int detect_cmd(char **args, int *return_val, char ***env)
{
    for (int i = 0; BUILTIN[i].name != NULL; i++) {
        if (my_strcmp(args[0], BUILTIN[i].name) == 0) {
            *return_val = BUILTIN[i].func(args, env);
            free_array(args);
            return 1;
        }
    }
    return 0;
}
