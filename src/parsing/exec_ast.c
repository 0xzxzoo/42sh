/*
** EPITECH PROJECT, 2026
** exec_ast.c
** File description:
** exec_ast
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

static int execute_single_cmd(char *cmd, char ***env)
{
    char **args = advanced_split(cmd);
    int ret = 0;
    pid_t pid;

    if (!args || !args[0]) {
        if (args)
            free_array(args);
        return 0;
    }
    clean_quotes(args);
    if (detect_cmd(args, &ret, env)) {
        free_array(args);
        return ret;
    }
    pid = fork();
    if (pid == 0)
        exit(exec_cmd(args, *env));
    waitpid(pid, &ret, 0);
    free_array(args);
    return WEXITSTATUS(ret);
}

static int exec_cmd_node(ast_node_t *node, char ***env)
{
    int status;

    if (node->type == NODE_SUBSHELL) {
        if (fork() == 0) {
            status = exec_ast(node->left, env);
            exit(status);
        }
        wait(&status);
        return WEXITSTATUS(status);
    }
    return execute_single_cmd(node->cmd, env);
}

int exec_ast(ast_node_t *node, char ***env)
{
    if (!node)
        return 0;
    if (node->type == NODE_SEMI) {
        exec_ast(node->left, env);
        return exec_ast(node->right, env);
    }
    if (node->type == NODE_AND || node->type == NODE_OR)
        return exec_and_or(node, env);
    if (node->type == NODE_PIPE)
        return exec_pipe_node(node, env);
    if (node->type == NODE_REDIR_OUT)
        return exec_redir_out(node, env);
    if (node->type == NODE_REDIR_APPEND)
        return exec_redir_append(node, env);
    if (node->type == NODE_REDIR_IN)
        return exec_redir_in(node, env);
    if (node->type == NODE_REDIR_HEREDOC)
        return exec_redir_heredoc(node, env);
    return exec_cmd_node(node, env);
}

int process_ast_line(char *line, char ***env)
{
    ast_node_t *ast = parse_expr(line);
    int status = exec_ast(ast, env);

    free_ast(ast);
    return status;
}
