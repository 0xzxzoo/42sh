/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** termios_setup
*/

#include "42sh/my_shell.h"

void set_raw_mode(struct termios *orig_termios)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void restore_termios(struct termios *orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}
