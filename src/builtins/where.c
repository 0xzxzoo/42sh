/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** where
*/

#include "42sh/my_shell.h"
#include "my.h"

static int check_builtin_where(char *cmd)
{
    for (int i = 0; BUILTIN[i].name != NULL; i++) {
        if (my_strcmp(cmd, BUILTIN[i].name) == 0) {
            my_printf("%s is a shell built-in\n", cmd);
            return 1;
        }
    }
    return 0;
}

static char *get_path_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            return env[i] + 5;
    }
    return NULL;
}

static int check_executable_in_paths(char **paths, const char *cmd)
{
    char *full;
    int found = 0;

    for (int i = 0; paths[i]; i++) {
        full = malloc(my_strlen(paths[i]) + my_strlen(cmd) + 2);
        if (!full)
            continue;
        my_strcpy(full, paths[i]);
        my_strcat(full, "/");
        my_strcat(full, cmd);
        if (access(full, X_OK) == 0) {
            my_printf("%s\n", full);
            found = 1;
        }
        free(full);
    }
    return found;
}

static int find_all_in_path(const char *cmd, char **env)
{
    char *path_env = get_path_env(env);
    char **paths;
    int found = 0;

    if (!path_env)
        return 0;
    paths = my_str_to_word_array(path_env, ":");
    if (!paths)
        return 0;
    found = check_executable_in_paths(paths, cmd);
    free_array(paths);
    return found;
}

int my_where(job_list_t *jobs, char **args, char ***env)
{
    int val = 0;
    int found;

    (void) jobs;
    if (!args[1]) {
        put_error("where: Too few arguments.\n");
        return 1;
    }
    for (int i = 1; args[i]; i++) {
        found = check_builtin_where(args[i]);
        found += find_all_in_path(args[i], *env);
        if (!found)
            val = 1;
    }
    return val;
}
