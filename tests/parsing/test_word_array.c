/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_word_array
*/
#include <criterion/criterion.h>
#include "42sh/my_shell.h"

static void free_args(char **args)
{
    if (!args)
        return;
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

static int count_arr(char **arr)
{
    int i = 0;

    while (arr[i])
        i++;
    return i;
}

Test(advanced_split, simple_words)
{
    char **a = advanced_split("echo hello world");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 3);
    cr_assert_str_eq(a[0], "echo");
    cr_assert_str_eq(a[1], "hello");
    cr_assert_str_eq(a[2], "world");
    free_args(a);
}

Test(advanced_split, single_word)
{
    char **a = advanced_split("ls");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 1);
    cr_assert_str_eq(a[0], "ls");
    free_args(a);
}

Test(advanced_split, leading_spaces)
{
    char **a = advanced_split("   echo hi");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 2);
    cr_assert_str_eq(a[0], "echo");
    free_args(a);
}

Test(advanced_split, trailing_spaces)
{
    char **a = advanced_split("echo hi   ");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 2);
    cr_assert_str_eq(a[1], "hi");
    free_args(a);
}

Test(advanced_split, multiple_spaces_between_words)
{
    char **a = advanced_split("echo    hi");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 2);
    cr_assert_str_eq(a[0], "echo");
    cr_assert_str_eq(a[1], "hi");
    free_args(a);
}

Test(advanced_split, tabs_as_separator)
{
    char **a = advanced_split("echo\thi\tworld");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 3);
    cr_assert_str_eq(a[0], "echo");
    cr_assert_str_eq(a[2], "world");
    free_args(a);
}

Test(advanced_split, empty_string)
{
    char **a = advanced_split("");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 0);
    cr_assert_null(a[0]);
    free_args(a);
}

Test(advanced_split, only_spaces)
{
    char **a = advanced_split("     ");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 0);
    free_args(a);
}

Test(advanced_split, null_terminated)
{
    char **a = advanced_split("echo hi");
    cr_assert_not_null(a);
    cr_assert_null(a[count_arr(a)]);
    free_args(a);
}

Test(advanced_split, single_quoted_space_kept)
{
    char **a = advanced_split("'hello world'");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 1);
    cr_assert_str_eq(a[0], "'hello world'");
    free_args(a);
}

Test(advanced_split, double_quoted_space_kept)
{
    char **a = advanced_split("\"hello world\"");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 1);
    cr_assert_str_eq(a[0], "\"hello world\"");
    free_args(a);
}

Test(advanced_split, mixed_quoted_and_unquoted)
{
    char **a = advanced_split("echo \"hello world\" foo");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 3);
    cr_assert_str_eq(a[1], "\"hello world\"");
    cr_assert_str_eq(a[2], "foo");
    free_args(a);
}

Test(advanced_split, nested_double_in_single)
{
    char **a = advanced_split("'hello \"world\"'");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 1);
    free_args(a);
}

Test(advanced_split, nested_single_in_double)
{
    char **a = advanced_split("\"it's fine\"");
    cr_assert_not_null(a);
    cr_assert_eq(count_arr(a), 1);
    free_args(a);
}

Test(clean_quotes, removes_single_quotes)
{
    char **a = advanced_split("'hello'");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "hello");
    free_args(a);
}

Test(clean_quotes, removes_double_quotes)
{
    char **a = advanced_split("\"hello\"");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "hello");
    free_args(a);
}

Test(clean_quotes, preserves_content_inside_quotes)
{
    char **a = advanced_split("\"hello world\"");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "hello world");
    free_args(a);
}

Test(clean_quotes, no_quotes_unchanged)
{
    char **a = advanced_split("hello");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "hello");
    free_args(a);
}

Test(clean_quotes, multiple_words_all_cleaned)
{
    char **a = advanced_split("'foo' \"bar\" baz");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "foo");
    cr_assert_str_eq(a[1], "bar");
    cr_assert_str_eq(a[2], "baz");
    free_args(a);
}

Test(clean_quotes, mixed_quotes_in_one_word)
{
    char **a = advanced_split("'hel'\"lo\"");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "hello");
    free_args(a);
}

Test(clean_quotes, double_quote_inside_single)
{
    char **a = advanced_split("'\"'");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "\"");
    free_args(a);
}

Test(clean_quotes, single_quote_inside_double)
{
    char **a = advanced_split("\"'\"");
    cr_assert_not_null(a);
    clean_quotes(a);
    cr_assert_str_eq(a[0], "'");
    free_args(a);
}

Test(clean_quotes, null_input_safe)
{
    clean_quotes(NULL);
}

Test(clean_quotes, empty_word_stays_empty)
{
    char *arr[] = { strdup("''"), NULL };
    clean_quotes(arr);
    cr_assert_str_eq(arr[0], "");
    free(arr[0]);
}
