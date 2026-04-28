/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_list
*/

#include "42sh/job_control.h"

job_list_t g_jobs = {0};

static int find_slot(void)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (g_jobs.jobs[i].id == 0)
            return i;
    }
    return -1;
}

static int next_id(void)
{
    int max = 0;

    for (int i = 0; i < MAX_JOBS; i++) {
        if (g_jobs.jobs[i].id > max)
            max = g_jobs.jobs[i].id;
    }
    return max + 1;
}

int jobs_add(pid_t pid, char *cmd)
{
    int slot = find_slot();

    if (slot == -1)
        return -1;
    g_jobs.jobs[slot].id = next_id();
    g_jobs.jobs[slot].pid = pid;
    g_jobs.jobs[slot].cmd = my_strdup(cmd);
    g_jobs.jobs[slot].status = JOB_RUNNING;
    g_jobs.jobs[slot].exit_code = 0;
    g_jobs.count++;
    return g_jobs.jobs[slot].id;
}

void jobs_remove(int id)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (g_jobs.jobs[i].id == id) {
            if (g_jobs.jobs[i].cmd)
                free(g_jobs.jobs[i].cmd);
            g_jobs.jobs[i].cmd = NULL;
            g_jobs.jobs[i].id = 0;
            g_jobs.jobs[i].pid = 0;
            g_jobs.count--;
            return;
        }
    }
}

job_t *find_jobs_id(int id)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (g_jobs.jobs[i].id == id)
            return &g_jobs.jobs[i];
    }
    return NULL;
}

job_t *find_jobs_pid(pid_t pid)
{
    for (int i = 0; i < MAX_JOBS; i++) {
        if (g_jobs.jobs[i].pid == pid)
            return &g_jobs.jobs[i];
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
