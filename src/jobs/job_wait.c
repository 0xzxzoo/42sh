/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_wait
*/

#include "42sh/job_control.h"

static void handle_job_done(job_list_t *jobs, job_t *job, int status)
{
    job->status = JOB_DONE;
    if (WIFEXITED(status))
        job->exit_code = WEXITSTATUS(status);
    else
        job->exit_code = 1;
}

void jobs_update_all(job_list_t *jobs)
{
    int status;
    pid_t pid;
    job_t *job;

    while (1) {
        pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
        if (pid <= 0)
            break;
        job = find_jobs_pid(jobs, pid);
        if (!job)
            continue;
        if (WIFSTOPPED(status))
            job->status = JOB_STOPPED;
        if (WIFEXITED(status) || WIFSIGNALED(status))
            handle_job_done(jobs, job, status);
    }
}

void job_wait_fg(job_list_t *jobs, pid_t pid)
{
    int status;
    pid_t ret;
    job_t *job;

    tcsetpgrp(STDIN_FILENO, pid);
    while (1) {
        ret = waitpid(pid, &status, WUNTRACED);
        if (ret != -1 || errno != EINTR)
            break;
    }
    tcsetpgrp(STDIN_FILENO, getpgrp());
    if (ret == -1)
        return;
    job = find_jobs_pid(jobs, pid);
    if (!job)
        return;
    if (WIFSTOPPED(status))
        job->status = JOB_STOPPED;
    else
        handle_job_done(jobs, job, status);
}
