/*
** EPITECH PROJECT, 2026
** parser_redir.c
** File description:
** parser_redir
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

static int get_redir_t(char *s, int i, int *oplen, node_type_t *t)
{
    if (i > 0 && s[i - 1] == '>' && s[i] == '>') {
        *oplen = 2;
        *t = NODE_REDIR_APPEND;
        return 1;
    }
    if (i > 0 && s[i - 1] == '<' && s[i] == '<') {
        *oplen = 2;
        *t = NODE_REDIR_HEREDOC;
        return 1;
    }
    return 0;
}

static int check_redir_type(char *s, int i, int *oplen, node_type_t *t)
{
    if (get_redir_t(s, i, oplen, t))
        return 1;
    *oplen = 1;
    if (s[i] == '>') {
        *t = NODE_REDIR_OUT;
        return 1;
    }
    if (s[i] == '<') {
        *t = NODE_REDIR_IN;
        return 1;
    }
    return 0;
}

static void update_quotes(char c, int *q, int *dq, int *p)
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

static int find_redir_idx(char *str, int *oplen, node_type_t *type)
{
    int p = 0;
    int q = 0;
    int dq = 0;

    for (int i = my_strlen(str) - 1; i >= 0; i--) {
        update_quotes(str[i], &q, &dq, &p);
        if (p == 0 && !q && !dq && check_redir_type(str, i, oplen, type))
            return i - (*oplen - 1);
    }
    return -1;
}

ast_node_t *parse_redir(char *str)
{
    int oplen = 0;
    node_type_t t;
    int idx = find_redir_idx(str, &oplen, &t);
    char *s[3];
    ast_node_t *n;

    if (idx == -1)
        return parse_cmd(str);
    s[0] = my_strndup(str, idx);
    s[1] = my_strdup(str + idx + oplen);
    s[2] = trim_spaces(s[1]);
    n = create_node(t, NULL);
    n->left = parse_redir(s[0]);
    n->right = create_node(NODE_FILE, s[2]);
    free(s[0]);
    free(s[1]);
    free(s[2]);
    return n;
}
