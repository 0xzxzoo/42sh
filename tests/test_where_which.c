/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_where_which
*/

#include "42sh/job_control.h"
#include "42sh/my_shell.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

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

Test(builtin_which, no_args_fails, .init = cr_redirect_stderr)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", NULL};
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_which(&jobs, args, &env);
    cr_assert_neq(ret, 0, "which with no args must fail, got %d", ret);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "which") != NULL, "error must mention 'which', got: %s", buf);
    cr_assert(strstr(buf, "argument") != NULL || strstr(buf, "few") != NULL, "error must mention arguments, got: %s", buf);
    free_env(env);
}

Test(builtin_which, finds_existing_command, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "ls", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_which(&jobs, args, &env);
    cr_assert_eq(ret, 0, "which ls must succeed, got %d", ret);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ls") != NULL, "output must contain 'ls', got: %s", buf);
    free_env(env);
}

Test(builtin_which, not_found_prints_to_stdout, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "no_such_cmd_xyz", NULL};
    job_list_t jobs = {0};
    char buf[256];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_which(&jobs, args, &env);
    cr_assert_neq(ret, 0, "which on missing cmd must fail, got %d", ret);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "not found") != NULL || strstr(buf, "Command") != NULL || strstr(buf, "no_such_cmd_xyz") != NULL,
        "stdout must mention the command, got: %s", buf);
    free_env(env);
}

Test(builtin_which, not_found_nothing_on_stderr, .init = cr_redirect_stderr)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "no_such_cmd_xyz", NULL};
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;

    jobs_init(&jobs);
    my_which(&jobs, args, &env);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert_eq(n, 0, "which not-found must produce nothing on stderr, got: %s", buf);
    free_env(env);
}

Test(builtin_which, multiple_commands_all_found, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "ls", "cat", "grep", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_which(&jobs, args, &env);
    cr_assert_eq(ret, 0, "which ls cat grep must all succeed");
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ls") != NULL, "output must contain ls");
    cr_assert(strstr(buf, "cat") != NULL, "output must contain cat");
    cr_assert(strstr(buf, "grep") != NULL, "output must contain grep");
    free_env(env);
}

Test(builtin_which, mixed_found_and_not_found, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "ls", "no_such_cmd_xyz", "cat", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_which(&jobs, args, &env);
    cr_assert_neq(ret, 0, "which must fail when at least one cmd is not found");
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ls") != NULL, "output must still contain ls");
    cr_assert(strstr(buf, "cat") != NULL, "output must still contain cat");
    cr_assert(strstr(buf, "no_such_cmd_xyz") != NULL, "output must mention the missing command");
    free_env(env);
}

Test(builtin_which, no_path_in_env_fails, .init = cr_redirect_stdout)
{
    char *raw[] = {"HOME=/root", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "ls", NULL};
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_which(&jobs, args, &env);
    cr_assert_neq(ret, 0, "which must fail when PATH is not set");
    free_env(env);
}

Test(builtin_which, returns_only_first_match, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"which", "ls", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int count = 0;
    char *p;

    jobs_init(&jobs);
    my_which(&jobs, args, &env);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    p = buf;
    p = strstr(p, "\n");
    while (p != NULL) {
        count++;
        p++;
        p = strstr(p, "\n");
    }
    cr_assert_eq(count, 1, "which must return exactly one result, got %d lines", count);
    free_env(env);
}

Test(builtin_where, no_args_fails, .init = cr_redirect_stderr)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", NULL};
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_where(&jobs, args, &env);
    cr_assert_neq(ret, 0, "where with no args must fail, got %d", ret);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "where") != NULL, "error must mention 'where', got: %s", buf);
    cr_assert(strstr(buf, "argument") != NULL || strstr(buf, "few") != NULL, "error must mention arguments, got: %s", buf);
    free_env(env);
}

Test(builtin_where, finds_existing_command, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "ls", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_where(&jobs, args, &env);
    cr_assert_eq(ret, 0, "where ls must succeed, got %d", ret);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ls") != NULL, "output must contain 'ls', got: %s", buf);
    free_env(env);
}

Test(builtin_where, not_found_is_silent, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "no_such_cmd_xyz", NULL};
    job_list_t jobs = {0};
    char buf[256];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_where(&jobs, args, &env);
    cr_assert_neq(ret, 0, "where on missing cmd must return nonzero, got %d", ret);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert_eq(n, 0, "where not-found must produce no stdout output, got: %s", buf);
    free_env(env);
}

Test(builtin_where, not_found_nothing_on_stderr, .init = cr_redirect_stderr)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "no_such_cmd_xyz", NULL};
    job_list_t jobs = {0};
    char buf[256];
    FILE *err;
    ssize_t n;

    jobs_init(&jobs);
    my_where(&jobs, args, &env);
    err = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, err);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert_eq(n, 0, "where not-found must produce nothing on stderr, got: %s", buf);
    free_env(env);
}

Test(builtin_where, multiple_commands_all_found, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "ls", "cat", "grep", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_where(&jobs, args, &env);
    cr_assert_eq(ret, 0, "where ls cat grep must all succeed");
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ls") != NULL, "output must contain ls");
    cr_assert(strstr(buf, "cat") != NULL, "output must contain cat");
    cr_assert(strstr(buf, "grep") != NULL, "output must contain grep");
    free_env(env);
}

Test(builtin_where, mixed_found_and_not_found, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "ls", "no_such_cmd_xyz", "cat", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int ret;

    jobs_init(&jobs);
    ret = my_where(&jobs, args, &env);
    cr_assert_neq(ret, 0, "where must fail when at least one cmd is not found");
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "ls") != NULL, "output must still contain ls");
    cr_assert(strstr(buf, "cat") != NULL, "output must still contain cat");
    cr_assert(strstr(buf, "no_such_cmd_xyz") == NULL, "output must NOT mention the missing command");
    free_env(env);
}

Test(builtin_where, no_path_in_env_fails)
{
    char *raw[] = {"HOME=/root", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "ls", NULL};
    job_list_t jobs = {0};
    int ret;

    jobs_init(&jobs);
    ret = my_where(&jobs, args, &env);
    cr_assert_neq(ret, 0, "where must fail when PATH is not set");
    free_env(env);
}

Test(builtin_where, searches_all_path_dirs, .init = cr_redirect_stdout)
{
    char *raw[] = {"PATH=/usr/bin:/bin", NULL};
    char **env = make_env(raw);
    char **args = (char *[]) {"where", "ls", NULL};
    job_list_t jobs = {0};
    char buf[512];
    FILE *out;
    ssize_t n;
    int lines = 0;
    char *p;

    jobs_init(&jobs);
    my_where(&jobs, args, &env);
    out = cr_get_redirected_stdout();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    p = buf;
    p = strstr(p, "\n");
    while (p != NULL) {
        lines++;
        p++;
        p = strstr(p, "\n");
    }
    cr_assert_geq(lines, 1, "where must print at least one result per matching dir");
    free_env(env);
}
