/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parsing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "42sh/my_shell.h"

Test(read_line, reads_input)
{
    FILE *tmp = tmpfile();
    char *res;

    fputs("hello world\n", tmp);
    rewind(tmp);
    stdin = tmp;
    res = read_line();
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "hello world\n");
    free(res);
    fclose(tmp);
}

Test(read_line, handles_eof)
{
    FILE *tmp = tmpfile();
    char *res;

    rewind(tmp);
    stdin = tmp;
    res = read_line();
    cr_assert_null(res);
    fclose(tmp);
}

Test(read_line, handles_empty_input)
{
    FILE *tmp = tmpfile();
    char *res;

    fputs("\n", tmp);
    rewind(tmp);
    stdin = tmp;
    res = read_line();
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "\n");
    free(res);
    fclose(tmp);
}

Test(read_line, reads_multiple_words)
{
    FILE *tmp = tmpfile();
    char *res;

    fputs("echo hello world\n", tmp);
    rewind(tmp);
    stdin = tmp;
    res = read_line();
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "echo hello world\n");
    free(res);
    fclose(tmp);
}

Test(read_line, reads_only_first_line)
{
    FILE *tmp = tmpfile();
    char *res;

    fputs("first line\nsecond line\n", tmp);
    rewind(tmp);
    stdin = tmp;
    res = read_line();
    cr_assert_not_null(res);
    cr_assert_str_eq(res, "first line\n");
    free(res);
    fclose(tmp);
}

Test(read_line, newline_included_in_result)
{
    FILE *tmp = tmpfile();
    char *res;

    fputs("test\n", tmp);
    rewind(tmp);
    stdin = tmp;
    res = read_line();
    cr_assert_not_null(res);
    cr_assert_eq(res[4], '\n');
    free(res);
    fclose(tmp);
}

Test(my_strndup, basic)
{
    char *s = my_strndup("hello", 3);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "hel");
    free(s);
}

Test(my_strndup, full_length)
{
    char *s = my_strndup("hello", 5);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "hello");
    free(s);
}

Test(my_strndup, zero_length)
{
    char *s = my_strndup("hello", 0);

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "");
    free(s);
}

Test(my_strndup, null_terminator)
{
    char *s = my_strndup("hello", 3);

    cr_assert_not_null(s);
    cr_assert_eq(s[3], '\0');
    free(s);
}

Test(match_op, matches_at_start)
{
    cr_assert_eq(match_op("&&echo", 0, "&&"), 1);
}

Test(match_op, matches_at_offset)
{
    cr_assert_eq(match_op("echo&&ls", 4, "&&"), 1);
}

Test(match_op, no_match)
{
    cr_assert_eq(match_op("echo||ls", 4, "&&"), 0);
}

Test(match_op, single_char_op_match)
{
    cr_assert_eq(match_op("echo;ls", 4, ";"), 1);
}

Test(match_op, single_char_op_no_match)
{
    cr_assert_eq(match_op("echo|ls", 4, ";"), 0);
}

Test(match_op, pipe_match)
{
    cr_assert_eq(match_op("ls|grep", 2, "|"), 1);
}

Test(find_op, finds_and_and)
{
    int pos = find_op("echo hi&&ls", "&&");
    cr_assert_eq(pos, 7);
}

Test(find_op, finds_pipe)
{
    int pos = find_op("ls|grep foo", "|");
    cr_assert_eq(pos, 2);
}

Test(find_op, finds_semicolon)
{
    int pos = find_op("echo a;echo b", ";");
    cr_assert_eq(pos, 6);
}

Test(find_op, not_found)
{
    int pos = find_op("echo hello", "&&");
    cr_assert_eq(pos, -1);
}

Test(find_op, op_inside_single_quotes_ignored)
{
    int pos = find_op("echo '&&'", "&&");
    cr_assert_eq(pos, -1);
}

Test(find_op, op_inside_double_quotes_ignored)
{
    int pos = find_op("echo \"&&\"", "&&");
    cr_assert_eq(pos, -1);
}

Test(find_op, op_inside_parens_ignored)
{
    int pos = find_op("(echo&&ls)", "&&");
    cr_assert_eq(pos, -1);
}

Test(find_op, op_outside_parens_found)
{
    int pos = find_op("(echo hi)&&ls", "&&");
    cr_assert_eq(pos, 9);
}

Test(find_op, rightmost_op_returned)
{
    int pos = find_op("a&&b&&c", "&&");
    cr_assert_eq(pos, 4);
}

Test(find_op, empty_string)
{
    int pos = find_op("", "&&");
    cr_assert_eq(pos, -1);
}

Test(trim_spaces, leading_spaces)
{
    char *r = trim_spaces("   hello");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "hello");
    free(r);
}

Test(trim_spaces, trailing_spaces)
{
    char *r = trim_spaces("hello   ");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "hello");
    free(r);
}

Test(trim_spaces, both_sides)
{
    char *r = trim_spaces("  hello world  ");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "hello world");
    free(r);
}

Test(trim_spaces, tabs_and_newlines)
{
    char *r = trim_spaces("\t\nhello\n\t");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "hello");
    free(r);
}

Test(trim_spaces, no_whitespace)
{
    char *r = trim_spaces("hello");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "hello");
    free(r);
}

Test(trim_spaces, only_spaces)
{
    char *r = trim_spaces("     ");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "");
    free(r);
}

Test(trim_spaces, empty_string)
{
    char *r = trim_spaces("");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "");
    free(r);
}

Test(trim_spaces, single_char)
{
    char *r = trim_spaces("x");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "x");
    free(r);
}

Test(trim_spaces, preserves_inner_spaces)
{
    char *r = trim_spaces("  foo   bar  ");
    cr_assert_not_null(r);
    cr_assert_str_eq(r, "foo   bar");
    free(r);
}

Test(trim_spaces, null_returns_null)
{
    char *r = trim_spaces(NULL);
    cr_assert_null(r);
}
