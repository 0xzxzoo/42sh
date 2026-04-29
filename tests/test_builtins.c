/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtins
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "42sh/my_shell.h"
#include "42sh/job_control.h"

static char **make_env(char **raw)
{
    int len = 0;
    char **env;

    while (raw[len])
        len++;
    env = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; i++)
        env[i] = strdup(raw[i]);
    env[len] = NULL;
    return env;
}

static void free_env(char **env)
{
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}

Test(builtin_cd, no_home_var_fails, .init = cr_redirect_stderr)
{
    char *raw[] = {"PWD=/", "OLDPWD=", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "cd", NULL };
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_cd(&jobs, args, &env);
    cr_assert_neq(ret, 0, "cd with no HOME must fail, got %d", ret);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "home") != NULL || strstr(buf, "HOME") != NULL,
        "got: %s", buf);
    free_env(env);
}

Test(builtin_cd, no_args_goes_home)
{
    char *raw[] = {"HOME=/tmp", "PWD=/", "OLDPWD=", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "cd", NULL };
    job_list_t jobs = {0};
    char buf[4096];
    int ret;

    jobs_init(&jobs);
    ret = my_cd(&jobs, args, &env);
    cr_assert_eq(ret, 0, "cd with no args must succeed");
    cr_assert_str_eq(getcwd(buf, sizeof(buf)), "/tmp");
    chdir("/");
    free_env(env);
}

Test(builtin_cd, tilde_goes_home)
{
    char *raw[] = {"HOME=/tmp", "PWD=/", "OLDPWD=", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "cd", "~", NULL };
    job_list_t jobs = {0};
    char buf[4096];
    int ret;

    jobs_init(&jobs);
    ret = my_cd(&jobs, args, &env);
    cr_assert_eq(ret, 0, "cd ~ must succeed");
    cr_assert_str_eq(getcwd(buf, sizeof(buf)), "/tmp");
    chdir("/");
    free_env(env);
}

Test(builtin_cd, valid_dir_succeeds)
{
    char *raw[] = {"HOME=/tmp", "PWD=/", "OLDPWD=", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "cd", "/tmp", NULL };
    job_list_t jobs = {0};
    char buf[4096];
    int ret;

    jobs_init(&jobs);
    ret = my_cd(&jobs, args, &env);
    cr_assert_eq(ret, 0, "cd /tmp must succeed");
    cr_assert_str_eq(getcwd(buf, sizeof(buf)), "/tmp");
    chdir("/");
    free_env(env);
}

Test(builtin_cd, invalid_dir_returns_nonzero, .init = cr_redirect_stderr)
{
    char *raw[] = {"HOME=/tmp", "PWD=/", "OLDPWD=", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "cd", "/42", NULL };
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_cd(&jobs, args, &env);
    cr_assert_neq(ret, 0, "cd to non-existent dir must fail, got %d", ret);
    free_env(env);
}

Test(builtin_demo, info_succeeds, .init = cr_redirect_stdout)
{
    char *raw[] = {NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "info", NULL };
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_info(&jobs, args, &env);
    cr_assert_eq(ret, 0, "my_info must return 0 on success");
    free_env(env);
}

Test(builtin_exit, exits_with_given_code, .exit_code = 42)
{
    char *raw[] = {"HOME=/root", NULL};
    char **env = make_env(raw);
    char **args = malloc(sizeof(char *) * 3);
    job_list_t jobs = {0};

    jobs_init(&jobs);
    args[0] = strdup("exit");
    args[1] = strdup("42");
    args[2] = NULL;
    my_exit(&jobs, args, &env);
}

Test(builtin_exit, exits_with_zero_when_no_arg, .exit_code = 0)
{
    char *raw[] = {"HOME=/root", NULL};
    char **env = make_env(raw);
    char **args = malloc(sizeof(char *) * 2);
    job_list_t jobs = {0};

    jobs_init(&jobs);
    args[0] = strdup("exit");
    args[1] = NULL;
    my_exit(&jobs, args, &env);
}

Test(builtin_setenv, no_args_prints_env, .init = cr_redirect_stdout)
{
    char *raw[] = {"ABC=bar", "BAZ=qux", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", NULL };
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_eq(ret, 0,
        "setenv with no args must succeed, got %d", ret);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ABC=bar") != NULL,
        "output must contain ABC=bar, got: %s", buf);
    free_env(env);
}

Test(builtin_setenv, too_many_args_fails, .init = cr_redirect_stderr)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", "A", "B", "C", NULL };
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_neq(ret, 0, "setenv with too many args must fail, got %d", ret);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "many") != NULL || strstr(buf, "argument") != NULL,
        "error must mention arguments, got: %s", buf);
    free_env(env);
}

Test(builtin_setenv, invalid_name_starts_with_digit, .init = cr_redirect_stderr)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", "1BAD", "val", NULL };
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_neq(ret, 0, "setenv with name starting with digit must fail");
    free_env(env);
}

Test(builtin_setenv, invalid_name_special_char, .init = cr_redirect_stderr)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", "IN-VALID", "val", NULL };
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_neq(ret, 0,
        "setenv with special char in name must fail");
    free_env(env);
}

Test(builtin_setenv, sets_new_variable)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", "NEWVAR", "hello", NULL };
    job_list_t jobs = {0};
    int found = 0;
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "setenv NEWVAR hello must succeed");
    for (int i = 0; env[i]; i++) {
        if (strcmp(env[i], "NEWVAR=hello") == 0)
            found = 1;
    }
    cr_assert(found, "NEWVAR=hello must be in env after setenv");
    free_env(env);
}

Test(builtin_setenv, updates_existing_variable)
{
    char *raw[] = {"ABC=old", "BAR=keep", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", "ABC", "new", NULL };
    job_list_t jobs = {0};
    int found = 0;
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "setenv ABC new must succeed");
    for (int i = 0; env[i]; i++) {
        if (strcmp(env[i], "ABC=new") == 0)
            found = 1;
    }
    cr_assert(found, "ABC=new must be in env after update");
    free_env(env);
}

Test(builtin_setenv, sets_variable_with_empty_value)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "setenv", "EMPTY", NULL };
    job_list_t jobs = {0};
    int found = 0;
    int ret;

    jobs_init(&jobs);
    ret = my_setenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "setenv EMPTY must succeed with empty value");
    for (int i = 0; env[i]; i++) {
        if (strcmp(env[i], "EMPTY=") == 0)
            found = 1;
    }
    cr_assert(found, "EMPTY= must be in env");
    free_env(env);
}

Test(builtin_unsetenv, no_args_returns_error, .init = cr_redirect_stderr)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "unsetenv", NULL };
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_unsetenv(&jobs, args, &env);
    cr_assert_neq(ret, 0, "unsetenv with no args must fail, got %d", ret);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "argument") != NULL || strstr(buf, "few") != NULL,
        "error must mention arguments, got: %s", buf);
    free_env(env);
}

Test(builtin_unsetenv, removes_first_variable)
{
    char *raw[] = {"ABC=bar", "BAZ=qux", "LAST=val", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "unsetenv", "ABC", NULL };
    job_list_t jobs = {0};
    int found = 0;
    int ret;

    jobs_init(&jobs);
    ret = my_unsetenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "unsetenv ABC must succeed");
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "ABC=", 4) == 0)
            found = 1;
    }
    cr_assert_eq(found, 0, "ABC must be absent after unsetenv");
    free_env(env);
}

Test(builtin_unsetenv, removes_middle_variable)
{
    char *raw[] = {"FIRST=a", "MID=b", "LAST=c", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "unsetenv", "MID", NULL };
    job_list_t jobs = {0};
    int found = 0;
    int ret;

    jobs_init(&jobs);
    ret = my_unsetenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "unsetenv MID must succeed");
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "MID=", 4) == 0)
            found = 1;
    }
    cr_assert_eq(found, 0, "MID must be absent after unsetenv");
    free_env(env);
}

Test(builtin_unsetenv, removes_last_variable)
{
    char *raw[] = {"FIRST=a", "LAST=b", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "unsetenv", "LAST", NULL };
    job_list_t jobs = {0};
    int found = 0;
    int ret;

    jobs_init(&jobs);
    ret = my_unsetenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "unsetenv LAST must succeed");
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "LAST=", 5) == 0)
            found = 1;
    }
    cr_assert_eq(found, 0, "LAST must be absent after unsetenv");
    free_env(env);
}

Test(builtin_unsetenv, silently_ignores_missing_variable)
{
    char *raw[] = {"ABC=bar", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "unsetenv", "DOES_NOT_EXIST", NULL };
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_unsetenv(&jobs, args, &env);
    cr_assert_eq(ret, 0,
        "unsetenv of non-existent var must succeed silently");
    free_env(env);
}

Test(builtin_unsetenv, removes_multiple_variables)
{
    char *raw[] = {"A=1", "B=2", "C=3", NULL};
    char **env = make_env(raw);
    char **args = (char *[]){ "unsetenv", "A", "C", NULL };
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_unsetenv(&jobs, args, &env);
    cr_assert_eq(ret, 0, "unsetenv A C must succeed");
    for (int i = 0; env[i]; i++) {
        cr_assert(strncmp(env[i], "A=", 2) != 0, "A must be gone");
        cr_assert(strncmp(env[i], "C=", 2) != 0, "C must be gone");
    }
    free_env(env);
}
