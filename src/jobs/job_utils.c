/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_utils
*/

#include "42sh/job_control.h"

void jobs_init(job_list_t *jobs)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        jobs->jobs[i].id = 0;
        jobs->jobs[i].pid = 0;
        jobs->jobs[i].cmd = NULL;
        jobs->jobs[i].status = JOB_DONE;
        jobs->jobs[i].exit_code = 0;
    }
    jobs->count = 0;
    jobs->oldpwd = NULL;
}

void notify_done_jobs(job_list_t *jobs)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id == 0)
            continue;
        if (jobs->jobs[i].status == JOB_DONE) {
            my_printf("[%d] Done\t\t%s\n",
                jobs->jobs[i].id,
                jobs->jobs[i].cmd);
            jobs_remove(jobs, jobs->jobs[i].id);
        }
    }
}

int get_job_id(job_list_t *jobs, char *arg)
{
    if (arg) {
        if (arg[0] == '%')
            return my_getnbr(arg + 1);
        return my_getnbr(arg);
    }
    return get_last_job_id(jobs);
}

int get_last_job_id(job_list_t *jobs)
{
    int last_id;

    if (!jobs || jobs->count == 0)
        return 0;
    if (jobs->current >= 0 && jobs->current < MAX_JOBS &&
        jobs->jobs[jobs->current].id != 0)
        return jobs->jobs[jobs->current].id;
    last_id = 0;
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id > last_id)
            last_id = jobs->jobs[i].id;
    }
    return last_id;
}
