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
