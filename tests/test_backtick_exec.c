/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_backtick_exec
*/

#include <criterion/criterion.h>
#include "42sh/my_shell.h"

static job_list_t *make_jobs(void)
{
    job_list_t *jobs = malloc(sizeof(job_list_t));

    jobs_init(jobs);
    return jobs;
}

Test(backtick_exec, captures_echo_output)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char **e = env;
    job_list_t *jobs = make_jobs();
    char *out = capture_cmd_output("echo hello", &e, jobs);

    cr_assert_not_null(out);
    cr_assert_str_eq(out, "hello");
    free(out);
    free(jobs);
}

Test(backtick_exec, strips_trailing_newline)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char **e = env;
    job_list_t *jobs = make_jobs();
    char *out = capture_cmd_output("echo hello", &e, jobs);

    cr_assert_not_null(out);
    cr_assert(out[my_strlen(out) - 1] != '\n',
        "trailing newline must be stripped");
    free(out);
    free(jobs);
}

Test(backtick_exec, captures_multiword_output)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char **e = env;
    job_list_t *jobs = make_jobs();
    char *out = capture_cmd_output("echo hello world", &e, jobs);

    cr_assert_not_null(out);
    cr_assert_str_eq(out, "hello world");
    free(out);
    free(jobs);
}

Test(backtick_exec, empty_cmd_returns_empty_string)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char **e = env;
    job_list_t *jobs = make_jobs();
    char *out = capture_cmd_output("", &e, jobs);

    cr_assert_not_null(out);
    cr_assert_str_eq(out, "");
    free(out);
    free(jobs);
}

Test(backtick_exec, failed_cmd_returns_empty_string)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char **e = env;
    job_list_t *jobs = make_jobs();
    char *out = capture_cmd_output("/bin/false", &e, jobs);

    cr_assert_not_null(out);
    cr_assert_str_eq(out, "");
    free(out);
    free(jobs);
}

Test(backtick_exec, captures_piped_cmd)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char **e = env;
    job_list_t *jobs = make_jobs();
    char *out = capture_cmd_output("echo hello|cat", &e, jobs);

    cr_assert_not_null(out);
    cr_assert_str_eq(out, "hello");
    free(out);
    free(jobs);
}
