/*
** EPITECH PROJECT, 2026
** parser_utils.c
** File description:
** parser_utils
*/

#include "42sh/my_shell.h"
#include "42sh/ast.h"
#include "my.h"

char *my_strndup(char *str, int n)
{
    char *new_str = malloc(sizeof(char) * (n + 1));

    if (!new_str)
        return NULL;
    for (int i = 0; i < n; i++)
        new_str[i] = str[i];
    new_str[n] = '\0';
    return new_str;
}

int match_op(char *s, int i, char *op)
{
    int len = my_strlen(op);

    for (int j = 0; j < len; j++) {
        if (s[i + j] != op[j])
            return 0;
    }
    return 1;
}

int find_op(char *str, char *op)
{
    int p = 0;
    int q = 0;
    int dq = 0;

    for (int i = my_strlen(str) - 1; i >= 0; i--) {
        if (str[i] == '"' && !q)
            dq = !dq;
        if (str[i] == '\'' && !dq)
            q = !q;
        if (str[i] == ')' && !q && !dq)
            p++;
        if (str[i] == '(' && !q && !dq)
            p--;
        if (p == 0 && !q && !dq && match_op(str, i, op))
            return i;
    }
    return -1;
}

char *trim_spaces(char *str)
{
    int s = 0;
    int e;
    char *res;

    if (!str)
        return NULL;
    e = my_strlen(str) - 1;
    while (str[s] == ' ' || str[s] == '\t' || str[s] == '\n')
        s++;
    while (e >= s && (str[e] == ' ' || str[e] == '\t' || str[e] == '\n'))
        e--;
    res = malloc(sizeof(char) * (e - s + 2));
    if (!res)
        return NULL;
    for (int i = 0; i <= e - s; i++)
        res[i] = str[s + i];
    res[e - s + 1] = '\0';
    return res;
}
