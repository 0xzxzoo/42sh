/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** bg
*/

#include "42sh/job_control.h"

int my_bg(job_list_t *jobs, char **args, char ***env)
{
    int id = get_job_id(jobs, args[1]);
    job_t *job = find_jobs_id(jobs, id);

    (void)env;
    if (!job) {
        if (args[1])
            put_error("bg: No such job.\n");
        else
            put_error("bg: No current job.\n");
        return 1;
    }
    if (job->status == JOB_RUNNING) {
        my_printf("[%d] %d\n", job->id, job->pid);
        return 0;
    }
    job->status = JOB_RUNNING;
    kill(-job->pid, SIGCONT);
    my_printf("[%d] %d\n", job->id, job->pid);
    return 0;
}
