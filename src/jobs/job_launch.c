/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_launch
*/

#include "42sh/job_control.h"

static void job_child_process(char **argv)
{
    setpgid(0, 0);
    signal(SIGINT,  SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    execvp(argv[0], argv);
    perror(argv[0]);
    _exit(127);
}

pid_t job_launch(char **argv, int background)
{
    pid_t pid = fork();
    int job_id;

    if (pid < 0) {
        perror("fork");
        return -1;
    }
    if (pid == 0)
        job_child_process(argv);
    setpgid(pid, pid);
    job_id = jobs_add(pid, argv[0]);
    if (background) {
        printf("[%d] %d\n", job_id, pid);
    } else {
        job_wait_fg(pid);
    }
    return pid;
}
