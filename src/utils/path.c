/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** path
*/

#include "42sh/my_shell.h"
#include "my.h"

static void fill_path(char *res, char *dir, int len, const char *command)
{
    int i = 0;
    int j = 0;

    while (i < len) {
        res[i] = dir[i];
        i++;
    }
    res[i] = '/';
    i++;
    while (command[j]) {
        res[i] = command[j];
        i++;
        j++;
    }
    res[i] = '\0';
}

static char *combine_path(char *dir, int len, const char *command)
{
    int cmd_len = my_strlen(command);
    char *res;

    res = malloc(sizeof(char) * (len + cmd_len + 2));
    if (!res)
        return NULL;
    fill_path(res, dir, len, command);
    return res;
}

static char *check_path_segment(char *paths, int start,
    int end, const char *cmd)
{
    char *full_path = combine_path(&paths[start], end - start, cmd);

    if (full_path && access(full_path, X_OK) == 0)
        return full_path;
    free(full_path);
    return NULL;
}

char *get_full_path(char *paths, const char *command)
{
    char *full_path = NULL;
    int start = 0;
    int i = 0;

    if (!paths || !command)
        return NULL;
    while (paths[i] != '\0') {
        if (paths[i] != ':') {
            i++;
            continue;
        }
        full_path = check_path_segment(paths, start, i, command);
        if (full_path)
            return full_path;
        start = i + 1;
        i++;
    }
    return check_path_segment(paths, start, i, command);
}

char *find_command_in_path(const char *command, char **env)
{
    char *paths = NULL;
    char *res = NULL;
    int i = 0;

    for (i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            paths = my_strdup(env[i] + 5);
            break;
        }
    }
    if (!paths)
        return NULL;
    res = get_full_path(paths, command);
    free(paths);
    return res;
}

char *get_cmd_path(char **args, char **env)
{
    char *cmd_path = NULL;

    for (int i = 0; args[0][i] != '\0'; i++) {
        if (args[0][i] == '/')
            return my_strdup(args[0]);
    }
    cmd_path = find_command_in_path(args[0], env);
    if (!cmd_path)
        my_printf("%s: Command not found.\n", args[0]);
    return cmd_path;
}
