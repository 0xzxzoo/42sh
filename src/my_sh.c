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

static void add_to_history(history_t **head, history_t **cur, char *cmd)
{
    history_t *node = malloc(sizeof(history_t));

    if (!node)
        return;
    node->cmd = my_strdup(cmd);
    node->next = NULL;
    node->prev = *cur;
    if (*cur)
        (*cur)->next = node;
    else
        *head = node;
    *cur = node;
}

static void shell_loop(char **my_env, job_list_t *jobs,
    history_t **hist_head, history_t **hist_cur)
{
    char *line = read_line(hist_cur);

    while (line) {
        jobs_update_all(jobs);
        notify_done_jobs(jobs);
        if (my_strlen(line) > 0)
            add_to_history(hist_head, hist_cur, line);
        process_ast_line(line, &my_env, jobs);
        free(line);
        line = read_line(hist_cur);
    }
    free_array(my_env);
}

int main(int argc, char **argv, char **env)
{
    job_list_t jobs = {0};
    char **my_env = copy_env(env);
    history_t *hist_head = NULL;
    history_t *hist_cur = NULL;

    (void)argc;
    (void)argv;
    init_signals();
    jobs_init(&jobs);
    shell_loop(my_env, &jobs, &hist_head, &hist_cur);
    return 0;
}
