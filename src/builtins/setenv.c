/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** setenv
*/

#include "42sh/my_shell.h"
#include "my.h"

static int is_alphanum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    if (c >= '0' && c <= '9')
        return 1;
    if (c == '_')
        return 1;
    return 0;
}

static int check_env_name_format(char *name)
{
    if (!is_alphanum(name[0]) || (name[0] >= '0' && name[0] <= '9')) {
        put_error("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    for (int i = 0; name[i]; i++) {
        if (!is_alphanum(name[i])) {
            put_error("setenv: Variable name must contain "
                "alphanumeric characters.\n");
            return 1;
        }
    }
    return 0;
}

static int check_setenv_args(char **args)
{
    int len = 0;

    while (args[len])
        len++;
    if (len == 1)
        return 2;
    if (len > 3) {
        put_error("setenv: Too many arguments.\n");
        return 1;
    }
    return check_env_name_format(args[1]);
}

static char *create_env_str(char *name, char *value)
{
    int len1 = my_strlen(name);
    int len2 = value ? my_strlen(value) : 0;
    char *res = malloc(sizeof(char) * (len1 + len2 + 2));

    if (!res)
        return NULL;
    my_strcpy(res, name);
    res[len1] = '=';
    res[len1 + 1] = '\0';
    if (value)
        my_strcat(res, value);
    return res;
}

static void update_or_add_env(char ***env, char *name, char *value)
{
    int i = 0;
    int len = my_strlen(name);
    char *new_str = create_env_str(name, value);
    char **new_env;

    for (i = 0; (*env)[i]; i++) {
        if (my_strncmp((*env)[i], name, len) == 0 && (*env)[i][len] == '=') {
            free((*env)[i]);
            (*env)[i] = new_str;
            return;
        }
    }
    new_env = malloc(sizeof(char *) * (i + 2));
    for (i = 0; (*env)[i]; i++)
        new_env[i] = (*env)[i];
    new_env[i] = new_str;
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
}

int my_setenv(job_list_t *jobs, char **args, char ***env)
{
    int check = check_setenv_args(args);

    if (check == 1)
        return 1;
    if (check == 2) {
        for (int i = 0; (*env)[i]; i++)
            my_printf("%s\n", (*env)[i]);
        return 0;
    }
    update_or_add_env(env, args[1], args[2] ? args[2] : "");
    return 0;
}
