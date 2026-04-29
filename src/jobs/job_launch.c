/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_launch
*/

#include "42sh/job_control.h"

static void job_child_process(char **argv, char **env)
{
    setpgid(0, 0);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    execvp(argv[0], argv);
    perror(argv[0]);
    _exit(127);
}

static int launch_background(job_list_t *jobs, pid_t pid, char **argv)
{
    int job_id = jobs_add(jobs, pid, argv[0]);

    my_printf("[%d] %d\n", job_id, pid);
    return 0;
}

static int launch_foreground(pid_t pid)
{
    int status = 0;

    tcsetpgrp(STDIN_FILENO, pid);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 1;
    return 0;
}

pid_t job_launch(job_list_t *jobs, char **argv, char **env, int background)
{
    pid_t pid = fork();

    if (pid == 0)
        job_child_process(argv, env);
    setpgid(pid, pid);
    if (background)
        return launch_background(jobs, pid, argv);
    return launch_foreground(pid);
}
