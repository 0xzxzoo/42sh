/*
** EPITECH PROJECT, 2026
** word_array.c
** File description:
** word_array
*/

#include "42sh/my_shell.h"
#include "my.h"

static int count_args(char *str)
{
    int cnt = 0;
    int sq = 0;
    int dq = 0;
    int in = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\'' && !dq)
            sq = !sq;
        if (str[i] == '"' && !sq)
            dq = !dq;
        if ((str[i] == ' ' || str[i] == '\t') && !sq && !dq)
            in = 0;
        if (((str[i] != ' ' && str[i] != '\t') || sq || dq) && !in) {
            cnt++;
            in = 1;
        }
    }
    return cnt;
}

static char *get_word(char *str, int *i)
{
    char *word = malloc(sizeof(char) * (my_strlen(str) + 1));
    int sq = 0;
    int dq = 0;
    int j = 0;

    while (str[*i]) {
        if (str[*i] == '\'' && !dq)
            sq = !sq;
        if (str[*i] == '"' && !sq)
            dq = !dq;
        if ((str[*i] == ' ' || str[*i] == '\t') && !sq && !dq)
            break;
        word[j] = str[*i];
        j++;
        (*i)++;
    }
    word[j] = '\0';
    return word;
}

static void clean_single_word(char *str)
{
    int k = 0;
    char q = 0;

    for (int j = 0; str[j]; j++) {
        if ((str[j] == '\'' || str[j] == '"') && !q) {
            q = str[j];
            continue;
        }
        if (str[j] == q) {
            q = 0;
            continue;
        }
        str[k] = str[j];
        k++;
    }
    str[k] = '\0';
}

void clean_quotes(char **args)
{
    if (!args)
        return;
    for (int i = 0; args[i]; i++)
        clean_single_word(args[i]);
}

char **advanced_split(char *str)
{
    int words = count_args(str);
    char **arr = malloc(sizeof(char *) * (words + 1));
    int idx = 0;
    int i = 0;

    if (!arr)
        return NULL;
    while (str[i]) {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (!str[i])
            break;
        arr[idx] = get_word(str, &i);
        idx++;
    }
    arr[idx] = NULL;
    return arr;
}
