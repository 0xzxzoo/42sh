/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** backtick_exec
*/

#include "42sh/my_shell.h"
#include "my.h"

static void strip(char *buf)
{
    int i = my_strlen(buf) - 1;

    while (i >= 0 && buf[i] == '\n')
        i--;
    buf[i + 1] = '\0';
}

static char *read_from_pipe(int fd)
{
    char *buf = malloc(4096);
    int total = 0;
    int n;

    if (!buf)
        return NULL;
    n = read(fd, buf + total, 4095 - total);
    while (n > 0) {
        total += n;
        n = read(fd, buf + total, 4095 - total);
    }
    if (n < 0) {
        free(buf);
        return NULL;
    }
    buf[total] = '\0';
    strip(buf);
    return buf;
}

static char **dup_env(char **env)
{
    int len = 0;
    char **copy;

    while (env && env[len])
        len++;
    copy = malloc(sizeof(char *) * (len + 1));
    if (!copy)
        return NULL;
    for (int i = 0; i < len; i++)
        copy[i] = my_strdup(env[i]);
    copy[len] = NULL;
    return copy;
}

static void run_child(char *cmd, char ***env, job_list_t *jobs, int fd)
{
    char **env_copy = dup_env(*env);

    dup2(fd, 1);
    close(fd);
    _exit(process_ast_line(cmd, &env_copy, jobs));
}

char *capture_cmd_output(char *cmd, char ***env, job_list_t *jobs)
{
    int pfd[2];
    pid_t pid;
    char *result;
    int status;

    if (pipe(pfd) == -1)
        return NULL;
    pid = fork();
    if (pid == 0) {
        close(pfd[0]);
        run_child(cmd, env, jobs, pfd[1]);
    }
    close(pfd[1]);
    result = read_from_pipe(pfd[0]);
    close(pfd[0]);
    waitpid(pid, &status, 0);
    return result;
}
