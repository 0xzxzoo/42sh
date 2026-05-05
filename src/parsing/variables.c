/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** variables
*/

#include "42sh/my_shell.h"
#include "my.h"
#include <stdlib.h>

void update_last_status(int status, char ***env)
{
    char *s_str = my_itoa(status);
    char *args[4] = {"setenv", "LAST_STATUS", s_str, NULL};

    my_setenv(NULL, args, env);
    free(s_str);
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
    char *val;

    if (my_strcmp(arg, "$?") == 0) {
        val = get_env_value("LAST_STATUS", env);
        if (val[0] == '\0') {
            free(val);
            return my_strdup("0");
        }
        return val;
    }
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
