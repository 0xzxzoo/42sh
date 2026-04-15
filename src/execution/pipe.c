/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** pipe
*/

#include "42sh/my_shell.h"
#include "my.h"

int exec_parsed_cmd(char *cmd_str, char ***env)
{
    char **args = my_str_to_word_array(cmd_str, " \t\n");
    int ret = 0;

    if (!args || !args[0])
        return 0;
    if (detect_cmd(args, &ret, env))
        return ret;
    return exec_cmd(args, *env);
}

static void child_process(int fd, int *pfd, int next)
{
    if (fd != 0) {
        dup2(fd, 0);
        close(fd);
    }
    if (next) {
        dup2(pfd[1], 1);
        close(pfd[0]);
        close(pfd[1]);
    }
    return;
}

static void parent_process(int *fd, int *pfd, int next)
{
    if (next)
        close(pfd[1]);
    if (*fd != 0)
        close(*fd);
    if (next)
        *fd = pfd[0];
}

int execute_pipes(char **cmds, char ***env)
{
    int pfd[2];
    int fd = 0;
    int i = 0;

    for (; cmds[i] != NULL; i++) {
        check_exit_in_pipe(cmds[i]);
        if (cmds[i + 1] != NULL)
            pipe(pfd);
        if (fork() == 0) {
            child_process(fd, pfd, cmds[i + 1] != NULL);
            exit(exec_parsed_cmd(cmds[i], env));
        }
        parent_process(&fd, pfd, cmds[i + 1] != NULL);
    }
    for (; i > 0; i--)
        wait(NULL);
    return 0;
}

int process_line(char *line, char ***env)
{
    char **cmds = my_str_to_word_array(line, "|");
    char **args;
    int ret = 0;

    if (!cmds || !cmds[0])
        return 0;
    if (cmds[1] == NULL) {
        args = my_str_to_word_array(cmds[0], " \t\n");
        if (args && args[0] && detect_cmd(args, &ret, env)) {
            free_array(cmds);
            return ret;
        }
        if (args)
            free_array(args);
    }
    execute_pipes(cmds, env);
    free_array(cmds);
    return 0;
}
