/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** my_sh
*/

#include "42sh/my_shell.h"
#include "my.h"

static char **copy_env(char **env)
{
    int len = 0;
    char **new_env;

    while (env && env[len])
        len++;
    new_env = malloc(sizeof(char *) * (len + 1));
    if (!new_env)
        return NULL;
    for (int i = 0; i < len; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[len] = NULL;
    return new_env;
}

int main(int argc, char **argv, char **env)
{
    char *line;
    char **my_env = copy_env(env);

    line = read_line();
    while (line) {
        process_ast_line(line, &my_env);
        free(line);
        line = read_line();
    }
    free_array(my_env);
    return 0;
}
