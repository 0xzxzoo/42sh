/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_utils
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "42sh/my_shell.h"

Test(oldpwd, get_last_pwd_null_list)
{
    char *res = get_last_pwd(NULL);

    cr_assert_null(res, "get_last_pwd(NULL) must return NULL");
}

Test(oldpwd, add_one_node)
{
    oldpwd_t *list = NULL;

    add_oldpwd_node(&list, "/tmp");
    cr_assert_not_null(list, "list must not be NULL after add");
    cr_assert_str_eq(get_last_pwd(list), "/tmp",
        "get_last_pwd must return /tmp");
    free(list->path);
    free(list);
}

Test(oldpwd, add_two_nodes_last_is_second)
{
    oldpwd_t *list = NULL;

    add_oldpwd_node(&list, "/first");
    add_oldpwd_node(&list, "/second");
    cr_assert_str_eq(get_last_pwd(list), "/second",
        "get_last_pwd must return /second");
    free(list->next->path);
    free(list->next);
    free(list->path);
    free(list);
}

Test(oldpwd, add_three_nodes_last_is_third)
{
    oldpwd_t *list = NULL;
    oldpwd_t *tmp;

    add_oldpwd_node(&list, "/a");
    add_oldpwd_node(&list, "/b");
    add_oldpwd_node(&list, "/c");
    cr_assert_str_eq(get_last_pwd(list), "/c",
        "get_last_pwd must return /c");
    while (list) {
        tmp = list->next;
        free(list->path);
        free(list);
        list = tmp;
    }
}

Test(oldpwd, add_empty_path)
{
    oldpwd_t *list = NULL;

    add_oldpwd_node(&list, "");
    cr_assert_not_null(list, "node must be created even for empty path");
    cr_assert_str_eq(get_last_pwd(list), "",
        "get_last_pwd must return empty string");
    free(list->path);
    free(list);
}

Test(oldpwd, simulates_cd_history)
{
    oldpwd_t *list = NULL;
    oldpwd_t *tmp;

    add_oldpwd_node(&list, "/home");
    add_oldpwd_node(&list, "/tmp");
    add_oldpwd_node(&list, "/var");
    cr_assert_str_eq(get_last_pwd(list), "/var",
        "last pwd must be /var after three pushes");
    while (list) {
        tmp = list->next;
        free(list->path);
        free(list);
        list = tmp;
    }
}

Test(path, get_full_path_null_paths)
{
    char *res = get_full_path(NULL, "ls");

    cr_assert_null(res, "get_full_path(NULL, cmd) must return NULL");
}

Test(path, get_full_path_null_command)
{
    char *paths = "/usr/bin:/bin";
    char *res = get_full_path(paths, NULL);

    cr_assert_null(res, "get_full_path(paths, NULL) must return NULL");
}

Test(path, get_full_path_finds_ls_in_bin)
{
    char paths[] = "/bin";
    char *res = get_full_path(paths, "ls");

    cr_assert_not_null(res, "get_full_path must find ls in /bin");
    cr_assert(strstr(res, "ls") != NULL,
        "result must contain 'ls', got: %s", res);
    free(res);
}

Test(path, get_full_path_finds_in_second_segment)
{
    char paths[] = "/nonexistent_xyz:/bin";
    char *res = get_full_path(paths, "ls");

    cr_assert_not_null(res,
        "get_full_path must find ls in second segment");
    cr_assert(strstr(res, "ls") != NULL,
        "result must contain 'ls', got: %s", res);
    free(res);
}

Test(path, get_full_path_returns_null_when_not_found)
{
    char paths[] = "/nonexistent_xyz:/also_nonexistent_abc";
    char *res = get_full_path(paths, "ls");

    cr_assert_null(res,
        "get_full_path must return NULL when command not found");
}

Test(path, get_full_path_finds_in_last_segment)
{
    char paths[] = "/nonexistent_xyz:/usr/bin";
    char *res = get_full_path(paths, "env");

    cr_assert_not_null(res,
        "get_full_path must find env in /usr/bin");
    cr_assert(strstr(res, "env") != NULL,
        "result must contain 'env', got: %s", res);
    free(res);
}

Test(path, find_command_no_path_var)
{
    char *env[] = {"HOME=/root", "USER=me", NULL};
    char *res = find_command_in_path("ls", env);

    cr_assert_null(res,
        "find_command_in_path must return NULL when PATH absent");
}

Test(path, find_command_finds_ls)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char *res = find_command_in_path("ls", env);

    cr_assert_not_null(res,
        "find_command_in_path must find ls");
    cr_assert(strstr(res, "ls") != NULL,
        "result must contain 'ls', got: %s", res);
    free(res);
}

Test(path, find_command_not_found)
{
    char *env[] = {"PATH=/nonexistent_xyz", NULL};
    char *res = find_command_in_path("ls", env);

    cr_assert_null(res,
        "find_command_in_path must return NULL when command not found");
}

Test(path, get_cmd_path_absolute, .init = cr_redirect_stdout)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char *args[] = {"/bin/ls", NULL};
    char *res = get_cmd_path(args, env);

    cr_assert_not_null(res, "get_cmd_path with absolute path must return it");
    cr_assert_str_eq(res, "/bin/ls",
        "get_cmd_path must return the absolute path unchanged");
    free(res);
}

Test(path, get_cmd_path_found_in_path, .init = cr_redirect_stdout)
{
    char *env[] = {"PATH=/bin:/usr/bin", NULL};
    char *args[] = {"ls", NULL};
    char *res = get_cmd_path(args, env);

    cr_assert_not_null(res,
        "get_cmd_path must find ls in PATH");
    cr_assert(strstr(res, "ls") != NULL,
        "result must contain 'ls', got: %s", res);
    free(res);
}

Test(path, get_cmd_path_not_found, .init = cr_redirect_stderr)
{
    char *env[] = {"PATH=/nonexistent_xyz", NULL};
    char *args[] = {"no_such_cmd_xyz", NULL};
    char buf[256];
    FILE *out;
    ssize_t n;
    char *res = get_cmd_path(args, env);

    cr_assert_null(res,
        "get_cmd_path must return NULL for unknown command");
    out = cr_get_redirected_stderr();
    n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[(n > 0) ? n : 0] = '\0';
    cr_assert(strstr(buf, "not found") != NULL ||
        strstr(buf, "Command") != NULL ||
        strstr(buf, "no_such_cmd_xyz") != NULL,
        "error must mention the command, got: %s", buf);
}

Test(env_get, variable_not_found)
{
    char *env[] = {
        "bonjour=",
        "aurevoir=test",
        NULL,
    };

    cr_assert_eq(env_get(env, "test"), NULL);
}

Test(env_get, existing_variable)
{
    char *env[] = {
        "bonjour=",
        "aurevoir=test",
        NULL,
    };

    cr_assert_str_eq(env_get(env, "aurevoir"), "test");
}

Test(env_get, empty_variable)
{
    char *env[] = {
        "bonjour=",
        "aurevoir=test",
        NULL,
    };

    cr_assert_str_eq(env_get(env, "bonjour"), "");
}