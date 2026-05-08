/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** which
*/

#include "42sh/my_shell.h"
#include "my.h"

extern const builtin_t BUILTIN[];

static int check_builtin_which(char *cmd)
{
    for (int i = 0; BUILTIN[i].name != NULL; i++) {
        if (my_strcmp(cmd, BUILTIN[i].name) == 0) {
            my_printf("%s: shell built-in command.\n", cmd);
            return 1;
        }
    }
    return 0;
}

static int process_which_cmd(char *cmd, char ***env)
{
    char *path = NULL;

    if (check_builtin_which(cmd))
        return 0;
    path = find_command_in_path(cmd, *env);
    if (path) {
        my_printf("%s\n", path);
        free(path);
        return 0;
    }
    my_printf("%s: Command not found.\n", cmd);
    return 1;
}

int my_which(job_list_t *jobs, char **args, char ***env)
{
    int val = 0;

    (void)jobs;
    if (!args[1]) {
        put_error("which: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i]; i++)
        val |= process_which_cmd(args[i], env);
    return val;
}
