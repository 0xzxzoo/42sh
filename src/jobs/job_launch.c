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

pid_t job_launch(job_list_t *jobs, char **argv, char **env, int background)
{
    pid_t pid = fork();
    int job_id;
    job_t *job;

    if (pid == 0)
        job_child_process(argv, env);
    setpgid(pid, pid);
    if (background) {
        job_id = jobs_add(jobs, pid, argv[0]);
        my_printf("[%d] %d\n", job_id, pid);
        return 0;
    }
    job_wait_fg(jobs, pid);
    return 0;
}
