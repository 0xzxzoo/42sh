/*
** EPITECH PROJECT, 2026
** detect.c
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
    {"where", my_where},
    {"which", my_which},
    {NULL, NULL}
};

int detect_cmd(char **args, int *return_val, char ***env)
{
    for (int i = 0; BUILTIN[i].name != NULL; i++) {
        if (my_strcmp(args[0], BUILTIN[i].name) == 0) {
            *return_val = BUILTIN[i].func(args, env);
            return 1;
        }
    }
    return 0;
}
