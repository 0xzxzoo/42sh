/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_control
*/

#ifndef JOB_CONTROL_H_
    #define JOB_CONTROL_H_

    #include <sys/types.h>
    #include <signal.h>
    #include <sys/wait.h>
    #include <stdio.h>
    #include <errno.h>
    #include "42sh/my_shell.h"
    #define MAX_JOBS 64

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


typedef struct oldpwd_s oldpwd_t;

typedef struct job_list_s {
    job_t jobs[MAX_JOBS];
    int count;
    int current;
    int previous;
    oldpwd_t *oldpwd;
} job_list_t;

void notify_done_jobs(job_list_t *jobs);
void jobs_init(job_list_t *jobs);
int get_job_id(job_list_t *jobs, char *arg);
int jobs_add(job_list_t *jobs, pid_t pid, char *cmd);
void jobs_remove(job_list_t *jobs, int id);
job_t *find_jobs_id(job_list_t *jobs, int id);
job_t *find_jobs_pid(job_list_t *jobs, pid_t pid);
void jobs_update_all(job_list_t *jobs);
pid_t job_launch(job_list_t *jobs, char **argv, char **env, int background);
void job_wait_fg(job_list_t *jobs, pid_t pid);
char *job_status_str(job_status_t status);
int get_last_job_id(job_list_t *jobs);

#endif /* !JOB_CONTROL_H_ */
