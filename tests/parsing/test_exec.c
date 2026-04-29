/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_ast_exec
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "42sh/my_shell.h"

job_list_t *init_jobs(void)
{
    job_list_t *jobs = malloc(sizeof(job_list_t));

    if (!jobs)
        return NULL;
    jobs_init(jobs);
    return jobs;
}

void free_jobs(job_list_t *jobs)
{
    if (!jobs)
        return;
    for (int i = 0; i < jobs->count; i++) {
        free(jobs->jobs[i].cmd);
    }
    free(jobs);
}

Test(create_node, basic_cmd_node)
{
    ast_node_t *n = create_node(NODE_CMD, "echo hi");

    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    cr_assert_str_eq(n->cmd, "echo hi");
    cr_assert_null(n->left);
    cr_assert_null(n->right);
    free_ast(n);
}

Test(create_node, null_cmd_stored_as_null)
{
    ast_node_t *n = create_node(NODE_PIPE, NULL);

    cr_assert_not_null(n);
    cr_assert_null(n->cmd);
    free_ast(n);
}

Test(create_node, cmd_is_duplicated)
{
    char buf[] = "ls -la";
    ast_node_t *n = create_node(NODE_CMD, buf);

    buf[0] = 'X';
    cr_assert_str_eq(n->cmd, "ls -la");
    free_ast(n);
}

Test(create_node, all_node_types_allocate)
{
    node_type_t types[] = {
        NODE_CMD, NODE_PIPE, NODE_AND, NODE_OR,
        NODE_SEMI, NODE_SUBSHELL, NODE_REDIR_OUT,
        NODE_REDIR_IN, NODE_REDIR_APPEND, NODE_REDIR_HEREDOC, NODE_FILE
    };
    int len = sizeof(types) / sizeof(types[0]);
    ast_node_t *node;

    for (int i = 0; i < len; i++) {
        node = create_node(types[i], NULL);
        cr_assert_not_null(node, "create_node failed for type %d", types[i]);
        cr_assert_eq(node->type, types[i]);
        free_ast(node);
    }
}

Test(free_ast, null_safe)
{
    free_ast(NULL);
}

Test(free_ast, frees_full_tree)
{
    ast_node_t *root = create_node(NODE_AND, NULL);

    root->left = create_node(NODE_CMD, "/bin/true");
    root->right = create_node(NODE_CMD, "echo ok");
    free_ast(root);
}

Test(exec_and_or, and_runs_right_on_success)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_AND, NULL);
    int ret;

    root->left = create_node(NODE_CMD, "/bin/true");
    root->right = create_node(NODE_CMD, "/bin/true");
    ret = exec_and_or(root, (char ***)&env, jobs);
    cr_assert_eq(ret, 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_and_or, and_skips_right_on_failure)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_AND, NULL);
    int ret;

    root->left = create_node(NODE_CMD, "/bin/false");
    root->right = create_node(NODE_CMD, "/bin/true");
    ret = exec_and_or(root, (char ***)&env, jobs);
    cr_assert_neq(ret, 0, "AND must short-circuit on left failure");
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_and_or, or_skips_right_on_success)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_OR, NULL);
    int ret;

    root->left = create_node(NODE_CMD, "/bin/true");
    root->right = create_node(NODE_CMD, "/bin/false");
    ret = exec_and_or(root, (char ***)&env, jobs);
    cr_assert_eq(ret, 0, "OR must short-circuit when left succeeds");
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_and_or, or_runs_right_on_failure)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_OR, NULL);
    int ret;

    root->left = create_node(NODE_CMD, "/bin/false");
    root->right = create_node(NODE_CMD, "/bin/true");
    ret = exec_and_or(root, (char ***)&env, jobs);
    cr_assert_eq(ret, 0, "OR must run right side when left fails");
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_pipe_node, pipe_exit_status_is_right_side)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_PIPE, NULL);
    int ret;

    root->left = create_node(NODE_CMD, "echo hello");
    root->right = create_node(NODE_CMD, "cat");
    ret = exec_pipe_node(root, (char ***)&env, jobs);
    cr_assert_eq(ret, 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_pipe_node, pipe_right_failure_propagated)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_PIPE, NULL);
    int ret;

    root->left = create_node(NODE_CMD, "echo hello");
    root->right = create_node(NODE_CMD, "/bin/false");
    ret = exec_pipe_node(root, (char ***)&env, jobs);
    cr_assert_neq(ret, 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, null_node_returns_zero)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_eq(exec_ast(NULL, (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(exec_ast, semi_runs_both_sides)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_SEMI, NULL);

    root->left = create_node(NODE_CMD, "/bin/true");
    root->right = create_node(NODE_CMD, "/bin/true");
    cr_assert_eq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, semi_returns_right_side_status)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_SEMI, NULL);

    root->left = create_node(NODE_CMD, "/bin/true");
    root->right = create_node(NODE_CMD, "/bin/false");
    cr_assert_neq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, and_node_dispatched)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_AND, NULL);

    root->left = create_node(NODE_CMD, "/bin/true");
    root->right = create_node(NODE_CMD, "/bin/true");
    cr_assert_eq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, or_node_dispatched)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_OR, NULL);

    root->left = create_node(NODE_CMD, "/bin/false");
    root->right = create_node(NODE_CMD, "/bin/true");
    cr_assert_eq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, pipe_node_dispatched)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_PIPE, NULL);

    root->left = create_node(NODE_CMD, "echo hi");
    root->right = create_node(NODE_CMD, "cat");
    cr_assert_eq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, cmd_node_true_returns_zero)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_CMD, "/bin/true");

    cr_assert_eq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(exec_ast, cmd_node_false_returns_nonzero)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();
    ast_node_t *root = create_node(NODE_CMD, "/bin/false");

    cr_assert_neq(exec_ast(root, (char ***)&env, jobs), 0);
    free_ast(root);
    free_jobs(jobs);
}

Test(process_ast_line, simple_true)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_eq(process_ast_line("/bin/true", (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(process_ast_line, simple_false)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_neq(process_ast_line("/bin/false", (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(process_ast_line, semicolon_chain)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_eq(process_ast_line("/bin/true;/bin/true",
            (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(process_ast_line, and_chain_success)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_eq(process_ast_line("/bin/true&&/bin/true",
            (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(process_ast_line, and_chain_short_circuit)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_neq(process_ast_line("/bin/false&&/bin/true",
            (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(process_ast_line, or_chain_fallback)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_eq(process_ast_line("/bin/false||/bin/true",
            (char ***)&env, jobs), 0);
    free_jobs(jobs);
}

Test(process_ast_line, empty_string_returns_zero)
{
    char **env = NULL;
    job_list_t *jobs = init_jobs();

    cr_assert_eq(process_ast_line("", (char ***)&env, jobs), 0);
    free_jobs(jobs);
}
