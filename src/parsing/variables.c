/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** variables
*/

#include "42sh/my_shell.h"
#include "my.h"
#include <stdlib.h>

int last_status_manager(int status, int mode)
{
    static int last_status = 0;

    if (mode == 1)
        last_status = status;
    return last_status;
}

static char *get_env_value(char *var, char **env)
{
    int len = my_strlen(var);

    if (len == 0)
        return my_strdup("$");
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            return my_strdup(env[i] + len + 1);
    }
    return my_strdup("");
}

static char *expand_single_arg(char *arg, char **env)
{
    if (my_strcmp(arg, "$?") == 0)
        return my_itoa(last_status_manager(0, 0));
    if (arg[0] == '$' && arg[1] != '\0')
        return get_env_value(arg + 1, env);
    return my_strdup(arg);
}

char **apply_variables(char **args, char **env)
{
    int count = 0;
    char **new_args;

    while (args[count])
        count++;
    new_args = malloc(sizeof(char *) * (count + 1));
    if (!new_args)
        return NULL;
    for (int i = 0; i < count; i++)
        new_args[i] = expand_single_arg(args[i], env);
    new_args[count] = NULL;
    free_array(args);
    return new_args;
}
