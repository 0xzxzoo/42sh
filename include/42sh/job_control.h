/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_control
*/

#ifndef JOB_CONTROL_H_
#define JOB_CONTROL_H_

    #include <sys/types.h>
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

typedef struct job_list_s {
    job_t jobs[MAX_JOBS];
    int count;
} job_list_t;


#endif /* !JOB_CONTROL_H_ */
