/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** backtick_replace
*/

#include "42sh/my_shell.h"
#include "my.h"

static int find_closing(char *str, int start)
{
    for (int i = start + 1; str[i]; i++) {
        if (str[i] == '`')
            return i;
    }
    return -1;
}

static char *build_result(char *str, int open, int close, char *output)
{
    int before_len = open;
    int output_len = my_strlen(output);
    int after_len = my_strlen(str + close + 1);
    char *res = malloc(before_len + output_len + after_len + 1);

    if (!res)
        return NULL;
    my_strncpy(res, str, before_len);
    my_strcpy(res + before_len, output);
    my_strcpy(res + before_len + output_len, str + close + 1);
    return res;
}

char *replace_backtick(char *str, char ***env, job_list_t *jobs)
{
    int open = find_backtick(str);
    int close;
    char *cmd;
    char *output;
    char *result;

    if (open == -1)
        return my_strdup(str);
    close = find_closing(str, open);
    if (close == -1)
        return NULL;
    cmd = my_strndup(str + open + 1, close - open - 1);
    output = capture_cmd_output(cmd, env, jobs);
    free(cmd);
    if (!output)
        return my_strdup(str);
    result = build_result(str, open, close, output);
    free(output);
    return result;
}
