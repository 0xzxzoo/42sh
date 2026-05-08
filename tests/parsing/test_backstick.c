/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_backstick
*/

#include <criterion/criterion.h>
#include "42sh/my_shell.h"

Test(backtick_find, no_backtick)
{
    cr_assert_eq(find_backtick("echo hello"), -1);
}

Test(backtick_find, simple_backtick)
{
    cr_assert_eq(find_backtick("echo `date`"), 5);
}

Test(backtick_find, backtick_at_start)
{
    cr_assert_eq(find_backtick("`date`"), 0);
}

Test(backtick_find, backtick_at_end)
{
    cr_assert_eq(find_backtick("echo `date`"), 5);
}

Test(backtick_find, backtick_in_single_quotes_ignored)
{
    cr_assert_eq(find_backtick("echo '`date`'"), -1);
}

Test(backtick_find, backtick_in_double_quotes_ignored)
{
    cr_assert_eq(find_backtick("echo \"`date`\""), -1);
}

Test(backtick_find, first_backtick_returned_when_multiple)
{
    cr_assert_eq(find_backtick("echo `date` `uname`"), 5);
}

Test(backtick_find, empty_string)
{
    cr_assert_eq(find_backtick(""), -1);
}

Test(backtick_find, only_backtick)
{
    cr_assert_eq(find_backtick("`"), 0);
}

Test(backtick_find, single_quote_closed_before_backtick)
{
    cr_assert_eq(find_backtick("'hello' `date`"), 8);
}

Test(backtick_find, double_quote_closed_before_backtick)
{
    cr_assert_eq(find_backtick("\"hello\" `date`"), 8);
}

Test(backtick_extract, simple_cmd)
{
    char *cmd = extract_backtick_cmd("echo `date`", 5);

    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd, "date");
    free(cmd);
}

Test(backtick_extract, cmd_at_start)
{
    char *cmd = extract_backtick_cmd("`date`", 0);

    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd, "date");
    free(cmd);
}

Test(backtick_extract, cmd_with_args)
{
    char *cmd = extract_backtick_cmd("echo `ls -R`", 5);

    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd, "ls -R");
    free(cmd);
}

Test(backtick_extract, no_closing_backtick_returns_null)
{
    char *cmd = extract_backtick_cmd("echo `date", 5);

    cr_assert_null(cmd);
}

Test(backtick_extract, empty_cmd)
{
    char *cmd = extract_backtick_cmd("echo ``", 5);

    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd, "");
    free(cmd);
}


Test(backtick_extract, multiword_cmd)
{
    char *cmd = extract_backtick_cmd("x=`echo hello world`", 2);

    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd, "echo hello world");
    free(cmd);
}

Test(backtick_extract, only_extracts_up_to_first_closing)
{
    char *cmd = extract_backtick_cmd("`date` `uname`", 0);

    cr_assert_not_null(cmd);
    cr_assert_str_eq(cmd, "date");
    free(cmd);
}
