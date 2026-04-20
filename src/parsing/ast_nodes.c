/*
** EPITECH PROJECT, 2026
** ast_nodes.c
** File description:
** ast_nodes
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

ast_node_t *create_node(node_type_t type, char *cmd)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (!node)
        return NULL;
    node->type = type;
    node->cmd = cmd ? my_strdup(cmd) : NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_ast(ast_node_t *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    if (node->cmd)
        free(node->cmd);
    free(node);
}
