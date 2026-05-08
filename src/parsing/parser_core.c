/*
** EPITECH PROJECT, 2026
** parser_core.c
** File description:
** parser_core
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

ast_node_t *split_node(char *str, int idx, int oplen, node_type_t type)
{
    ast_node_t *node = create_node(type, NULL);
    char *left_str = my_strndup(str, idx);
    char *right_str = my_strdup(str + idx + oplen);

    node->left = parse_expr(left_str);
    node->right = parse_expr(right_str);
    free(left_str);
    free(right_str);
    return node;
}

static int find_and_or(char *str, int *oplen, node_type_t *type)
{
    int idx_and = find_op(str, "&&");
    int idx_or = find_op(str, "||");

    if (idx_and > idx_or) {
        *oplen = 2;
        *type = NODE_AND;
        return idx_and;
    }
    if (idx_or != -1) {
        *oplen = 2;
        *type = NODE_OR;
        return idx_or;
    }
    return -1;
}

ast_node_t *parse_and_or(char *str)
{
    int oplen = 0;
    node_type_t type;
    int idx = find_and_or(str, &oplen, &type);

    if (idx != -1)
        return split_node(str, idx, oplen, type);
    return parse_pipe(str);
}

ast_node_t *parse_expr(char *str)
{
    int idx;

    idx = find_op(str, "&&");
    if (idx == -1)
        idx = find_op(str, "&");
    idx = find_background_op(str);
    if (idx != -1)
        return split_node(str, idx, 1, NODE_BACKGROUND);
    idx = find_op(str, ";");
    if (idx != -1)
        return split_node(str, idx, 1, NODE_SEMI);
    return parse_and_or(str);
}
