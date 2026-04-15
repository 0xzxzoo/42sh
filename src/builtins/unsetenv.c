/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** unsetenv
*/

#include "42sh/my_shell.h"
#include "my.h"

static void shift_env(char ***env, int index)
{
    free((*env)[index]);
    for (int i = index; (*env)[i] != NULL; i++) {
        (*env)[i] = (*env)[i + 1];
    }
}

static void remove_env_var(char ***env, char *name)
{
    int len = my_strlen(name);

    for (int i = 0; (*env)[i] != NULL; i++) {
        if (my_strncmp((*env)[i], name, len) == 0 &&
            (*env)[i][len] == '=') {
            shift_env(env, i);
            return;
        }
    }
}

int my_unsetenv(char **args, char ***env)
{
    int len = 0;

    while (args[len])
        len++;
    if (len == 1) {
        put_error("unsetenv: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i] != NULL; i++) {
        remove_env_var(env, args[i]);
    }
    return 0;
}
