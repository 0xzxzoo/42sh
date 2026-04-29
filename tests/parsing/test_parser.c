/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parser
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "42sh/my_shell.h"

Test(parse_cmd, simple_command)
{
    ast_node_t *n = parse_cmd("echo hello");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    cr_assert_str_eq(n->cmd, "echo hello");
    free_ast(n);
}

Test(parse_cmd, trims_spaces)
{
    ast_node_t *n = parse_cmd("  ls -la  ");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    cr_assert_str_eq(n->cmd, "ls -la");
    free_ast(n);
}

Test(parse_cmd, subshell_detected)
{
    ast_node_t *n = parse_cmd("(echo hi)");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SUBSHELL);
    cr_assert_not_null(n->left);
    free_ast(n);
}

Test(parse_cmd, nested_subshell)
{
    ast_node_t *n = parse_cmd("((echo hi))");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SUBSHELL);
    cr_assert_not_null(n->left);
    cr_assert_eq(n->left->type, NODE_SUBSHELL);
    free_ast(n);
}

Test(parse_cmd, subshell_with_semicolon)
{
    ast_node_t *n = parse_cmd("(echo a;echo b)");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SUBSHELL);
    cr_assert_not_null(n->left);
    cr_assert_eq(n->left->type, NODE_SEMI);
    free_ast(n);
}

Test(parse_cmd, not_subshell_if_no_closing_paren)
{
    ast_node_t *n = parse_cmd("(echo hi");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    free_ast(n);
}

Test(parse_pipe, simple_pipe)
{
    ast_node_t *n = parse_pipe("ls|grep foo");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_PIPE);
    cr_assert_not_null(n->left);
    cr_assert_not_null(n->right);
    free_ast(n);
}

Test(parse_pipe, pipe_left_right_values)
{
    ast_node_t *n = parse_pipe("echo hi|cat");
    cr_assert_eq(n->type, NODE_PIPE);
    cr_assert_str_eq(n->left->cmd, "echo hi");
    cr_assert_str_eq(n->right->cmd, "cat");
    free_ast(n);
}

Test(parse_pipe, no_pipe_falls_through)
{
    ast_node_t *n = parse_pipe("echo hello");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    cr_assert_str_eq(n->cmd, "echo hello");
    free_ast(n);
}

Test(parse_pipe, pipe_inside_quotes_ignored)
{
    ast_node_t *n = parse_pipe("echo \"|\"");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    free_ast(n);
}

Test(parse_pipe, multiple_pipes_rightmost_split)
{
    ast_node_t *n = parse_pipe("a|b|c");
    cr_assert_eq(n->type, NODE_PIPE);
    cr_assert_eq(n->right->type, NODE_CMD);
    cr_assert_str_eq(n->right->cmd, "c");
    free_ast(n);
}

Test(parse_redir, redir_out)
{
    ast_node_t *n = parse_redir("echo hi>out.txt");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_REDIR_OUT);
    cr_assert_not_null(n->left);
    cr_assert_not_null(n->right);
    cr_assert_eq(n->right->type, NODE_FILE);
    cr_assert_str_eq(n->right->cmd, "out.txt");
    free_ast(n);
}

Test(parse_redir, redir_in)
{
    ast_node_t *n = parse_redir("cat<in.txt");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_REDIR_IN);
    cr_assert_str_eq(n->right->cmd, "in.txt");
    free_ast(n);
}

Test(parse_redir, redir_append)
{
    ast_node_t *n = parse_redir("echo hi>>out.txt");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_REDIR_APPEND);
    cr_assert_str_eq(n->right->cmd, "out.txt");
    free_ast(n);
}

Test(parse_redir, redir_heredoc)
{
    ast_node_t *n = parse_redir("cat<<EOF");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_REDIR_HEREDOC);
    cr_assert_str_eq(n->right->cmd, "EOF");
    free_ast(n);
}

Test(parse_redir, no_redir_falls_through_to_cmd)
{
    ast_node_t *n = parse_redir("echo hello");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    cr_assert_str_eq(n->cmd, "echo hello");
    free_ast(n);
}

Test(parse_redir, redir_trims_filename)
{
    ast_node_t *n = parse_redir("echo hi>  out.txt  ");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_REDIR_OUT);
    cr_assert_str_eq(n->right->cmd, "out.txt");
    free_ast(n);
}

Test(parse_redir, redir_inside_quotes_ignored)
{
    ast_node_t *n = parse_redir("echo \">\"");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    free_ast(n);
}

Test(parse_and_or, and_operator)
{
    ast_node_t *n = parse_and_or("/bin/true&&echo ok");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_AND);
    cr_assert_str_eq(n->left->cmd, "/bin/true");
    cr_assert_str_eq(n->right->cmd, "echo ok");
    free_ast(n);
}

Test(parse_and_or, or_operator)
{
    ast_node_t *n = parse_and_or("/bin/false||echo fallback");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_OR);
    cr_assert_str_eq(n->left->cmd, "/bin/false");
    cr_assert_str_eq(n->right->cmd, "echo fallback");
    free_ast(n);
}

Test(parse_and_or, and_takes_priority_over_or_when_rightmost)
{
    ast_node_t *n = parse_and_or("a||b&&c");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_AND);
    free_ast(n);
}

Test(parse_and_or, no_operator_falls_through)
{
    ast_node_t *n = parse_and_or("echo hello");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    free_ast(n);
}

Test(parse_and_or, operator_inside_quotes_ignored)
{
    ast_node_t *n = parse_and_or("echo \"&&\"");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    free_ast(n);
}

Test(parse_expr, semicolon_splits)
{
    ast_node_t *n = parse_expr("echo a;echo b");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SEMI);
    cr_assert_str_eq(n->left->cmd, "echo a");
    cr_assert_str_eq(n->right->cmd, "echo b");
    free_ast(n);
}

Test(parse_expr, multiple_semicolons_rightmost_split)
{
    ast_node_t *n = parse_expr("a;b;c");
    cr_assert_eq(n->type, NODE_SEMI);
    cr_assert_str_eq(n->right->cmd, "c");
    free_ast(n);
}

Test(parse_expr, no_semicolon_falls_through_to_and_or)
{
    ast_node_t *n = parse_expr("/bin/true&&/bin/false");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_AND);
    free_ast(n);
}

Test(parse_expr, simple_command)
{
    ast_node_t *n = parse_expr("echo hello");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    cr_assert_str_eq(n->cmd, "echo hello");
    free_ast(n);
}

Test(parse_expr, semicolon_in_quotes_ignored)
{
    ast_node_t *n = parse_expr("echo \";\"");
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_CMD);
    free_ast(n);
}

Test(parse_expr, mixed_pipe_and_semicolon)
{
    ast_node_t *n = parse_expr("ls|grep foo;echo done");
    cr_assert_eq(n->type, NODE_SEMI);
    cr_assert_eq(n->left->type, NODE_PIPE);
    cr_assert_str_eq(n->right->cmd, "echo done");
    free_ast(n);
}

Test(split_node, basic_split)
{
    ast_node_t *n = split_node("echo a;echo b", 6, 1, NODE_SEMI);
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SEMI);
    cr_assert_str_eq(n->left->cmd, "echo a");
    cr_assert_str_eq(n->right->cmd, "echo b");
    free_ast(n);
}

Test(split_node, two_char_op)
{
    ast_node_t *n = split_node("true&&false", 4, 2, NODE_AND);
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_AND);
    cr_assert_str_eq(n->left->cmd, "true");
    cr_assert_str_eq(n->right->cmd, "false");
    free_ast(n);
}

Test(split_node, left_is_empty_string)
{
    ast_node_t *n = split_node(";echo b", 0, 1, NODE_SEMI);
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SEMI);
    cr_assert_eq(n->left->type, NODE_CMD);
    free_ast(n);
}

Test(split_node, right_is_empty_string)
{
    ast_node_t *n = split_node("echo a;", 6, 1, NODE_SEMI);
    cr_assert_not_null(n);
    cr_assert_eq(n->type, NODE_SEMI);
    cr_assert_eq(n->right->type, NODE_CMD);
    free_ast(n);
}
