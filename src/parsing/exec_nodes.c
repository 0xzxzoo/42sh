/*
** EPITECH PROJECT, 2026
** exec_nodes.c
** File description:
** exec_nodes
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

static void child_left(ast_node_t *n, int fd[2], char ***env)
{
    dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    exit(exec_ast(n, env));
}

static void child_right(ast_node_t *n, int fd[2], char ***env)
{
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);
    exit(exec_ast(n, env));
}

int exec_pipe_node(ast_node_t *node, char ***env)
{
    int fd[2];
    int status;
    pid_t p1;
    pid_t p2;

    pipe(fd);
    p1 = fork();
    if (p1 == 0)
        child_left(node->left, fd, env);
    p2 = fork();
    if (p2 == 0)
        child_right(node->right, fd, env);
    close(fd[0]);
    close(fd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, &status, 0);
    return WEXITSTATUS(status);
}

int exec_and_or(ast_node_t *node, char ***env)
{
    int left_status = exec_ast(node->left, env);

    if (node->type == NODE_AND) {
        if (left_status == 0)
            return exec_ast(node->right, env);
        return left_status;
    }
    if (node->type == NODE_OR) {
        if (left_status != 0)
            return exec_ast(node->right, env);
        return left_status;
    }
    return 0;
}
