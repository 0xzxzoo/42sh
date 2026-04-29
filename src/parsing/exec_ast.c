/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** exec_ast
*/

#include "42sh/my_shell.h"
#include "42sh/job_control.h"
#include "42sh/ast.h"
#include "my.h"

static char **prepare_args(char *cmd, int *background)
{
    char *clean = trim_spaces(cmd);
    int len = my_strlen(clean);
    char **args;

    if (len > 0 && clean[len - 1] == '&') {
        clean[len - 1] = '\0';
        *background = 1;
    }
    args = advanced_split(clean);
    free(clean);
    return args;
}

static int handle_args(char **args, char ***env, job_list_t *jobs)
{
    int ret = 0;

    if (!args || !args[0]) {
        if (args)
            free_array(args);
        return 0;
    }
    clean_quotes(args);
    if (detect_cmd(args, &ret, env, jobs)) {
        free_array(args);
        return ret;
    }
    return -1;
}

static int launch_cmd(char **args, char ***env)
{
    int ret = 0;
    pid_t pid = fork();

    if (pid == 0)
        exit(exec_cmd(args, *env));
    waitpid(pid, &ret, 0);
    free_array(args);
    return WEXITSTATUS(ret);
}

static int execute_single_cmd(char *cmd, char ***env, job_list_t *jobs)
{
    char **args = advanced_split(cmd);
    int ret = 0;

    if (!args || !args[0]) {
        free_array(args);
        return 0;
    }
    clean_quotes(args);
    args = apply_globbing(args);
    if (!args)
        return 1;
    if (detect_cmd(args, &ret, env, jobs)) {
        free_array(args);
        return ret;
    }
    return launch_cmd(args, env);
}

static int exec_cmd_node(ast_node_t *node, char ***env, job_list_t *jobs)
{
    int status;

    if (node->type == NODE_SUBSHELL) {
        if (fork() == 0) {
            status = exec_ast(node->left, env, jobs);
            exit(status);
        }
        wait(&status);
        return WEXITSTATUS(status);
    }
    return execute_single_cmd(node->cmd, env, jobs);
}

int exec_ast(ast_node_t *node, char ***env, job_list_t *jobs)
{
    if (!node)
        return 0;
    if (node->type == NODE_SEMI) {
        exec_ast(node->left, env, jobs);
        return exec_ast(node->right, env, jobs);
    }
    if (node->type == NODE_AND || node->type == NODE_OR)
        return exec_and_or(node, env, jobs);
    if (node->type == NODE_PIPE)
        return exec_pipe_node(node, env, jobs);
    if (node->type == NODE_REDIR_OUT)
        return exec_redir_out(node, env, jobs);
    if (node->type == NODE_REDIR_APPEND)
        return exec_redir_append(node, env, jobs);
    if (node->type == NODE_REDIR_IN)
        return exec_redir_in(node, env, jobs);
    if (node->type == NODE_REDIR_HEREDOC)
        return exec_redir_heredoc(node, env, jobs);
    return exec_cmd_node(node, env, jobs);
}

int process_ast_line(char *line, char ***env, job_list_t *jobs)
{
    ast_node_t *ast = parse_expr(line);
    int status = exec_ast(ast, env, jobs);

    free_ast(ast);
    return status;
}
