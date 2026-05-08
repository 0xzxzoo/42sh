/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** env
*/

#include "42sh/my_shell.h"

char *env_get(char **env, const char *name)
{
    char *new_name = strdup(name);
    size_t len = strlen(name);

    new_name[len] = '=';
    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], new_name, len) != 0)
            continue;
        free(new_name);
        return env[i] + len + 1;
    }
    free(new_name);
    return NULL;
}
