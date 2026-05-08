/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** where
*/

#include "42sh/my_shell.h"
#include "my.h"

static char *get_path_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            return env[i] + 5;
    }
    return NULL;
}

static char *build_path(char *dir, const char *cmd)
{
    int len1 = my_strlen(dir);
    int len2 = my_strlen(cmd);
    char *res = malloc(sizeof(char) * (len1 + len2 + 2));

    if (!res)
        return NULL;
    my_strcpy(res, dir);
    res[len1] = '/';
    res[len1 + 1] = '\0';
    my_strcat(res, cmd);
    return res;
}

static int find_all_in_path(const char *cmd, char **env)
{
    char *path_env = get_path_env(env);
    char **paths;
    char *full_path;
    int found = 0;

    if (!path_env)
        return 0;
    paths = my_str_to_word_array(path_env, ":");
    if (!paths)
        return 0;
    for (int i = 0; paths[i] != NULL; i++) {
        full_path = build_path(paths[i], cmd);
        if (full_path && access(full_path, X_OK) == 0) {
            my_printf("%s\n", full_path);
            found = 1;
        }
        free(full_path);
    }
    free_array(paths);
    return found;
}

int my_where(job_list_t *jobs, char **args, char ***env)
{
    int val = 0;

    (void) jobs;
    if (!args[1]) {
        put_error("where: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i] != NULL; i++) {
        if (!find_all_in_path(args[i], *env)) {
            val = 1;
        }
    }
    return val;
}
