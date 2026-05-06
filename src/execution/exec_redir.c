/*
** EPITECH PROJECT, 2026
** exec_redir.c
** File description:
** exec_redir
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

int exec_redir_out(ast_node_t *n, char ***env, job_list_t *jobs)
{
    int save = dup(1);
    int fd = open(n->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int st;

    if (fd == -1) {
        perror(n->right->cmd);
        return 1;
    }
    dup2(fd, 1);
    close(fd);
    st = exec_ast(n->left, env, jobs);
    dup2(save, 1);
    close(save);
    return st;
}

int exec_redir_append(ast_node_t *n, char ***env, job_list_t *jobs)
{
    int save = dup(1);
    int fd = open(n->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
    int st;

    if (fd == -1) {
        perror(n->right->cmd);
        return 1;
    }
    dup2(fd, 1);
    close(fd);
    st = exec_ast(n->left, env, jobs);
    dup2(save, 1);
    close(save);
    return st;
}

int exec_redir_in(ast_node_t *n, char ***env, job_list_t *jobs)
{
    int save = dup(0);
    int fd = open(n->right->cmd, O_RDONLY);
    int st;

    if (fd == -1) {
        perror(n->right->cmd);
        return 1;
    }
    dup2(fd, 0);
    close(fd);
    st = exec_ast(n->left, env, jobs);
    dup2(save, 0);
    close(save);
    return st;
}

static void write_heredoc(char *delim, int fd)
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        my_printf("? ");
        if (getline(&line, &len, stdin) == -1)
            break;
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (my_strcmp(line, delim) == 0)
            break;
        write(fd, line, my_strlen(line));
        write(fd, "\n", 1);
    }
    free(line);
}

int exec_redir_heredoc(ast_node_t *n, char ***env, job_list_t *jobs)
{
    int pfd[2];
    int save = dup(0);
    int st;

    pipe(pfd);
    write_heredoc(n->right->cmd, pfd[1]);
    close(pfd[1]);
    dup2(pfd[0], 0);
    close(pfd[0]);
    st = exec_ast(n->left, env, jobs);
    dup2(save, 0);
    close(save);
    return st;
}
