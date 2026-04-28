/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_init
*/

#include "42sh/job_control.h"

void jobs_init(void)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        g_jobs.jobs[i].id = 0;
        g_jobs.jobs[i].pid = 0;
        g_jobs.jobs[i].cmd = NULL;
        g_jobs.jobs[i].status = JOB_DONE;
        g_jobs.jobs[i].exit_code = 0;
    }
    g_jobs.count = 0;
}
