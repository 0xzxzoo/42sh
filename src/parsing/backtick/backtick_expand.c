/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** backtick_expand
*/

#include "42sh/my_shell.h"
#include "my.h"

char *expand_backticks(char *str, char ***env, job_list_t *jobs)
{
    char *current = my_strdup(str);
    char *next;

    while (find_backtick(current) != -1) {
        next = replace_backtick(current, env, jobs);
        free(current);
        if (!next) {
            put_error("42sh: unmatched '`'.\n");
            return NULL;
        }
        current = next;
    }
    return current;
}
