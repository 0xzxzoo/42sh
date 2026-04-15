/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** oldpwd
*/

#include "42sh/my_shell.h"
#include "my.h"

#include <stdlib.h>

void add_oldpwd_node(oldpwd_t **head, char *path)
{
    oldpwd_t *new_node = malloc(sizeof(oldpwd_t));
    oldpwd_t *tmp = *head;

    if (!new_node)
        return;
    new_node->path = my_strdup(path);
    new_node->next = NULL;
    if (!*head) {
        *head = new_node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

char *get_last_pwd(oldpwd_t *head)
{
    oldpwd_t *tmp = head;

    if (!tmp)
        return NULL;
    while (tmp->next)
        tmp = tmp->next;
    return tmp->path;
}
