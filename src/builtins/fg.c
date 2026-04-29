/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** fg
*/

#include "42sh/job_control.h"

int my_fg(job_list_t *jobs, char **args, char ***env)
{
    int id = get_job_id(jobs, args[1]);
    job_t *job = find_jobs_id(jobs, id);

    (void)env;
    if (!job) {
        put_error("fg: no such job\n");
        return 1;
    }
    job->status = JOB_RUNNING;
    kill(-job->pid, SIGCONT);
    tcsetpgrp(STDIN_FILENO, job->pid);
    job_wait_fg(jobs, job->pid);
    return 0;
}
