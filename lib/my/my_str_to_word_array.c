/*
** EPITECH PROJECT, 2025
** Project - str_to_word_array
** File description:
** Implementation for
** c
*/

#include "my.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_separator(char c, char *separators)
{
    while (*separators) {
        if (c == *separators) {
            return true;
        }
        ++separators;
    }
    return false;
}

int count_words(char *str, char *separators)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (!is_separator(str[i], separators)
            && (i == 0 || is_separator(str[i - 1], separators)))
            ++count;
    }
    return count;
}

int count_word_length(char *string, char *separators)
{
    int lenght = 0;

    for (int i = 0; string[i] != '\0' &&
        (!is_separator(string[i], separators)); ++i) {
        ++lenght;
    }
    return lenght;
}

static int copy_word(char **tab, char *str, int line, char *separators)
{
    int wordl = count_word_length(str, separators);
    int c = 0;
    int chars_read = 0;

    tab[line] = malloc(sizeof(char) * (wordl + 1));
    while (!is_separator(str[chars_read], separators) &&
        str[chars_read] != '\0') {
        tab[line][c] = str[chars_read];
        chars_read++;
        c++;
    }
    tab[line][c] = '\0';
    return chars_read;
}

char **my_str_to_word_array(char *str, char *separators)
{
    char **tab = malloc(sizeof(char *) * (count_words(str, separators) + 1));
    int i = 0;
    int line = 0;

    while (is_separator(str[i], separators)) {
        i++;
    }
    for (; str[i] != '\0';) {
        i += copy_word(tab, &str[i], line, separators);
        line++;
        while (is_separator(str[i], separators))
            i++;
    }
    tab[line] = NULL;
    return tab;
}
