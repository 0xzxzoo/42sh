/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** readline
*/

#include "42sh/my_shell.h"
#include "my.h"

void add_char_to_line(char **line, char c)
{
    int len = my_strlen(*line);
    char *new_line = malloc(sizeof(char) * (len + 2));

    if (!new_line)
        return;
    my_strcpy(new_line, *line);
    new_line[len] = c;
    new_line[len + 1] = '\0';
    free(*line);
    *line = new_line;
    write(1, &c, 1);
}

void remove_char_from_line(char **line)
{
    int len = my_strlen(*line);

    if (len > 0) {
        (*line)[len - 1] = '\0';
        write(1, "\b \b", 3);
    }
}

int process_input(char c, history_t **hist, char **line)
{
    if (check_escape_sequence(c, hist, line) == 1)
        return 1;
    if (c >= 32 && c <= 126)
        add_char_to_line(line, c);
    if (c == 127)
        remove_char_from_line(line);
    return 0;
}

char *read_line(history_t **hist)
{
    struct termios orig_termios;
    char *line = my_strdup("");
    char c;

    my_printf("> ");
    set_raw_mode(&orig_termios);
    while (read(0, &c, 1) > 0 && c != '\n') {
        if (c == 4 && my_strlen(line) == 0) {
            my_printf("exit\n");
            free(line);
            restore_termios(&orig_termios);
            return NULL;
        }
        process_input(c, hist, &line);
    }
    restore_termios(&orig_termios);
    if (line)
        write(1, "\n", 1);
    return line;
}
