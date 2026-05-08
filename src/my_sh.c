/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** my_sh
*/

#include "42sh/my_shell.h"
#include "42sh/job_control.h"
#include "my.h"

static void init_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}

static char **copy_env(char **env)
{
    int len = 0;
    char **new_env;

    while (env && env[len])
        len++;
    new_env = malloc(sizeof(char *) * (len + 1));
    if (!new_env)
        return NULL;
    for (int i = 0; i < len; i++)
        new_env[i] = my_strdup(env[i]);
    new_env[len] = NULL;
    return new_env;
}

int main(int argc, char **argv, char **env)
{
    job_list_t jobs = {0};
    char *line;
    char **my_env = copy_env(env);

    init_signals();
    jobs_init(&jobs);
    line = read_line();
    while (line) {
        add_to_history(line, my_env);
        jobs_update_all(&jobs);
        notify_done_jobs(&jobs);
        process_ast_line(line, &my_env, &jobs);
        free(line);
        line = read_line();
    }
    free_array(my_env);
    return 0;
}
