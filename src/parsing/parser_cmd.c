/*
** EPITECH PROJECT, 2026
** parser_cmd.c
** File description:
** parser_cmd
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

ast_node_t *parse_pipe(char *str)
{
    int idx = find_op(str, "|");

    if (idx != -1)
        return split_node(str, idx, 1, NODE_PIPE);
    return parse_redir(str);
}

ast_node_t *parse_cmd(char *str)
{
    char *clean = trim_spaces(str);
    int len = my_strlen(clean);
    ast_node_t *node;
    char *inner;

    if (clean[0] == '(' && clean[len - 1] == ')') {
        inner = my_strndup(clean + 1, len - 2);
        node = create_node(NODE_SUBSHELL, NULL);
        node->left = parse_expr(inner);
        free(inner);
        free(clean);
        return node;
    }
    node = create_node(NODE_CMD, clean);
    free(clean);
    return node;
}
