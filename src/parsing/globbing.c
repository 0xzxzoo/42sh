/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** globbing
*/

#include "42sh/my_shell.h"
#include "my.h"
#include <glob.h>
#include <stdlib.h>

static int count_new_args(char **args)
{
    glob_t g;
    int count = 0;

    for (int i = 0; args[i]; i++) {
        if (glob(args[i], GLOB_NOCHECK | GLOB_NOMAGIC, NULL, &g) == 0) {
            count += g.gl_pathc;
            globfree(&g);
        } else {
            count++;
        }
    }
    return count;
}

static void fill_glob(char **n_args, int *idx, glob_t *g)
{
    for (size_t j = 0; j < g->gl_pathc; j++) {
        n_args[*idx] = my_strdup(g->gl_pathv[j]);
        (*idx)++;
    }
    globfree(g);
}

char **apply_globbing(char **args)
{
    char **n_args = malloc(sizeof(char *) * (count_new_args(args) + 1));
    glob_t g;
    int idx = 0;

    if (!n_args)
        return NULL;
    for (int i = 0; args[i]; i++) {
        if (glob(args[i], GLOB_NOCHECK | GLOB_NOMAGIC, NULL, &g) == 0)
            fill_glob(n_args, &idx, &g);
        else
            n_args[idx++] = my_strdup(args[i]);
    }
    n_args[idx] = NULL;
    free_array(args);
    return n_args;
}
