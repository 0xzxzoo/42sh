/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_control
*/

#ifndef JOB_CONTROL_H_
#define JOB_CONTROL_H_

    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <errno.h>
    #include "42sh/my_shell.h"
    #define MAX_JOBS 64

extern job_list_t g_jobs;

typedef enum job_status_e {
    JOB_RUNNING,
    JOB_STOPPED,
    JOB_DONE
} job_status_t;

typedef struct job_s {
    int id;
    pid_t pid;
    char *cmd;
    job_status_t status;
    int exit_code;
} job_t;

typedef struct job_list_s {
    job_t jobs[MAX_JOBS];
    int count;
} job_list_t;

void    jobs_init(void);
int     jobs_add(pid_t pid, char *cmd);
void    jobs_remove(int id);
job_t  *find_jobs_id(int id);
job_t  *find_jobs_pid(pid_t pid);
char   *job_status_str(job_status_t status);

void job_wait_fg(pid_t pid);
void jobs_update_all(void);

#endif /* !JOB_CONTROL_H_ */
