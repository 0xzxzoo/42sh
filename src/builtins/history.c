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

static int count_lines(const char *filename)
{
    int fd = open(filename, O_RDONLY);
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

static char *get_line_at(const char *filename, int target)
{
    int fd = open(filename, O_RDONLY);
    int current = 1;
    char buffer[1];
    char *result = NULL;

    if (fd == -1)
        return (NULL);
    while (current < target && read(fd, buffer, 1) > 0) {
        if (buffer[0] == '\n')
            current++;
    }
    result = extract_line(fd);
    close(fd);
    return (result);
}

char *exec_history_expansion(const char *input)
{
    const char *file = ".shell_history";
    int target = 0;

    if (!input || input[0] != '!')
        return (NULL);
    if (input[1] == '!') {
        target = count_lines(file);
        return (get_line_at(file, target));
    }
    if (input[1] >= '0' && input[1] <= '9') {
        target = atoi(&input[1]);
        return (get_line_at(file, target));
    }
    return (NULL);
}
