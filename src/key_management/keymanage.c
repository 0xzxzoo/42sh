/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** keymanage
*/

#include "42sh/my_shell.h"

static void redraw_line(char *line)
{
    write(1, "\r\033[K> ", 6);
    my_putstr(line);
}

static void nav_up(history_t **hist, char **current_input)
{
    if (!hist || !(*hist))
        return;
    if ((*hist)->prev) {
        *hist = (*hist)->prev;
        free(*current_input);
        *current_input = my_strdup((*hist)->cmd);
        redraw_line(*current_input);
    }
}

static void nav_down(history_t **hist, char **current_input)
{
    if (!hist || !(*hist))
        return;
    if ((*hist)->next) {
        *hist = (*hist)->next;
        free(*current_input);
        *current_input = my_strdup((*hist)->cmd);
        redraw_line(*current_input);
    }
}

static int is_arrow_key(char seq[2], history_t **hist, char **cur)
{
    if (seq[0] == '[' && seq[1] == 'A') {
        nav_up(hist, cur);
        return 1;
    }
    if (seq[0] == '[' && seq[1] == 'B') {
        nav_down(hist, cur);
        return 1;
    }
    return 0;
}

int check_escape_sequence(char c, history_t **hist, char **current_input)
{
    char seq[2];

    if (c != 27)
        return 0;
    if (read(0, &seq[0], 1) <= 0 || read(0, &seq[1], 1) <= 0)
        return 1;
    return is_arrow_key(seq, hist, current_input);
}
