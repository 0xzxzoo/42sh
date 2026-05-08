/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** history
*/

#include "42sh/my_shell.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

int open_h_file(char **env, int mode)
{
    char *dirname = env_get(env, "HOME");
    char *path;
    int fd;

    if (!dirname)
        return -1;
    path = combine_path(dirname, strlen(dirname), HISTORY_FILE);
    fd = open(path, mode, 0644);
    free(path);
    return fd;
}

static int count_lines(char **env)
{
    int fd = open_h_file(env, O_RDONLY);
    int count = 0;
    char buffer[1];

    if (fd == -1)
        return (0);
    while (read(fd, buffer, 1) > 0) {
        if (buffer[0] == '\n')
            count++;
    }
    close(fd);
    return (count);
}

static char *extract_line(int fd)
{
    char *line = malloc(sizeof(char) * 4096);
    char buffer[1];
    int i = 0;

    if (!line)
        return (NULL);
    while (read(fd, buffer, 1) > 0 && buffer[0] != '\n') {
        line[i] = buffer[0];
        i++;
    }
    line[i] = '\0';
    return (line);
}

static char *get_line_at(char **env, int target)
{
    int fd = open_h_file(env, O_RDONLY);
    int current = 1;
    char buffer[1];
    char *result = NULL;

    if (fd == -1)
        return (NULL);
    while (current < target && read(fd, buffer, 1) > 0) {
        if (buffer[0] == '\n')
            current++;
    }
    if (current < target) {
        close(fd);
        return NULL;
    }
    result = extract_line(fd);
    close(fd);
    return (result);
}

char *expand_history(const char *input, char **env)
{
    int target = 0;

    if (!input || input[0] != '!')
        return (NULL);
    if (input[1] == '!') {
        target = count_lines(env);
        return (get_line_at(env, target));
    }
    if (input[1] >= '0' && input[1] <= '9') {
        target = atoi(&input[1]);
        return (get_line_at(env, target));
    }
    return (NULL);
}

static bool is_empty(const char *line)
{
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' || line[i] != '\t')
            return false;
    }
    return true;
}

void add_to_history(const char *line, char **env)
{
    int fd;

    if (is_empty(line))
        return;
    fd = open_h_file(env, O_WRONLY | O_APPEND | O_CREAT);
    if (fd < 0)
        return;
    write(fd, line, strlen(line));
    close(fd);
}

int my_history(job_list_t *jobs, char **args, char ***env)
{
    char *line = get_line_at(*env, 1);
    int count = 1;

    while (line) {
        if (!is_empty(line))
            printf("%4d     %s\n", count, line);
        count++;
        free(line);
        line = get_line_at(*env, count);
    }
    return 0;
}
