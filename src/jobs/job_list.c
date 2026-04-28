/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_list
*/

#include "42sh/job_control.h"

static int find_slot(job_list_t *jobs)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id == 0)
            return i;
    }
    return -1;
}

static int next_id(job_list_t *jobs)
{
    int max = 0;

    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id > max)
            max = jobs->jobs[i].id;
    }
    return max + 1;
}

int jobs_add(job_list_t *jobs, pid_t pid, char *cmd)
{
    int slot = find_slot(jobs);
    int new_id = next_id(jobs);

    if (slot == -1)
        return -1;
    jobs->jobs[slot].id = new_id;
    jobs->jobs[slot].pid = pid;
    jobs->jobs[slot].cmd = my_strdup(cmd);
    jobs->jobs[slot].status = JOB_RUNNING;
    jobs->jobs[slot].exit_code = 0;
    jobs->previous = jobs->current;
    jobs->current = slot;
    jobs->count++;
    return new_id;
}

static void clear_job(job_list_t *jobs, int i)
{
    if (jobs->jobs[i].cmd)
        free(jobs->jobs[i].cmd);
    jobs->jobs[i].cmd = NULL;
    jobs->jobs[i].id = 0;
    jobs->jobs[i].pid = 0;
    jobs->count--;
}

void jobs_remove(job_list_t *jobs, int id)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id == id) {
            clear_job(jobs, i);
            return;
        }
    }
}

job_t *find_jobs_id(job_list_t *jobs, int id)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].id == id)
            return &jobs->jobs[i];
    }
    return NULL;
}

job_t *find_jobs_pid(job_list_t *jobs, pid_t pid)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (jobs->jobs[i].pid == pid)
            return &jobs->jobs[i];
    }
    return NULL;
}

char *job_status_str(job_status_t status)
{
    if (status == JOB_RUNNING)
        return "Running";
    if (status == JOB_STOPPED)
        return "Stopped";
    return "Done";
}
