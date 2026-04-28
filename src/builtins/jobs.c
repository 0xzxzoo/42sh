/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** jobs
*/

#include "42sh/job_control.h"

int my_jobs(job_list_t *jobs, char **args, char ***env)
{
    (void)args;
    (void)env;
    if (jobs->count == 0)
        return 0;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id == 0)
            continue;
        my_printf("[%d] %s\t\t%s\n",
            jobs->jobs[i].id,
            job_status_str(jobs->jobs[i].status),
            jobs->jobs[i].cmd);
    }
    return 0;
}
