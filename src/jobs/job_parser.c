/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job_parser
*/

#include "42sh/job_control.h"
#include "42sh/ast.h"

static int is_isolated_ampersand(char *str, int i, int len)
{
    if (i > 0 && str[i - 1] == '&')
        return 0;
    if (i < len - 1 && str[i + 1] == '&')
        return 0;
    return 1;
}

static void update_state(char c, int *p, int *q, int *dq)
{
    if (c == '"' && !(*q))
        *dq = !(*dq);
    if (c == '\'' && !(*dq))
        *q = !(*q);
    if (c == ')' && !(*q) && !(*dq))
        (*p)++;
    if (c == '(' && !(*q) && !(*dq))
        (*p)--;
}

int find_background_op(char *str)
{
    int p = 0;
    int q = 0;
    int dq = 0;
    int len = my_strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        update_state(str[i], &p, &q, &dq);
        if (p != 0 || q || dq || str[i] != '&')
            continue;
        if (is_isolated_ampersand(str, i, len))
            return i;
    }
    return -1;
}

int exec_background(ast_node_t *node, char ***env, job_list_t *jobs)
{
    pid_t pid = fork();
    char *label;

    if (pid == 0) {
        setpgid(0, 0);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        _exit(exec_ast(node->left, env, jobs));
    }
    setpgid(pid, pid);
    label = (node->left && node->left->cmd) ? node->left->cmd : "";
    jobs_add(jobs, pid, label);
    if (node->right)
        return exec_ast(node->right, env, jobs);
    return 0;
}
