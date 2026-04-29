/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** which
*/

#include "42sh/my_shell.h"
#include "my.h"

int my_which(job_list_t *jobs, char **args, char ***env)
{
    int val = 0;
    char *cmd_path = NULL;

    if (!args[1]) {
        put_error("which: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i] != NULL; i++) {
        cmd_path = find_command_in_path(args[i], *env);
        if (cmd_path) {
            my_printf("%s\n", cmd_path);
            free(cmd_path);
        } else {
            my_printf("%s: Command not found.\n", args[i]);
            val = 1;
        }
    }
    return val;
}
