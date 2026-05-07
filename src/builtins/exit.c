/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** exit
*/

#include "42sh/my_shell.h"
#include "my.h"

int my_exit(job_list_t *jobs, char **args, char ***env)
{
    int val = 0;

    (void)env;
    if (jobs) {
        jobs_update_all(jobs);
        notify_done_jobs(jobs);
    }
    if (args[1] != NULL)
        val = my_getnbr(args[1]);
    free_array(args);
    exit(val);
    return val;
}

void check_exit_in_pipe(char *cmd)
{
    char **args = my_str_to_word_array(cmd, " \t\n");
    int val = 0;

    if (args && args[0] && my_strcmp(args[0], "exit") == 0) {
        if (args[1])
            val = my_getnbr(args[1]);
        free_array(args);
        exit(val);
    }
    if (args)
        free_array(args);
}
