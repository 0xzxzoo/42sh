/*
** EPITECH PROJECT, 2026
** exec.c
** File description:
** exec
*/

#include "42sh/my_shell.h"
#include "my.h"

void check_status(int status)
{
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
        my_printf("Segmentation fault (core dumped)\n");
}

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static int execute_command(char *cmd_path, char **args, char **env)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        return 84;
    if (pid == 0) {
        if (execve(cmd_path, args, env) == -1)
            perror("execve");
        exit(1);
    }
    waitpid(pid, &status, 0);
    check_status(status);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 1;
}

int exec_cmd(char **args, char **env)
{
    char *cmd_path = get_cmd_path(args, env);
    int return_val = 0;

    if (!cmd_path) {
        free_array(args);
        return 1;
    }
    return_val = execute_command(cmd_path, args, env);
    free(cmd_path);
    free_array(args);
    return return_val;
}
