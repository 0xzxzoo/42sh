/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** delivery
*/
// clang-format off
#ifndef MY_H_
    #define MY_H_

void my_putchar(char c);
void my_isneg(int nb);
void my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nombre);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int nb);
char *my_revstr(char *str);
char *my_strstr(char *str, char *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int nb);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
void my_showstr(char const *str);
void my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int sum_numbers(int n, ...);
int sum_strings_length(int n, ...);
void disp_stdarg(char *s, ...);
int my_put_unsigned_nbr(unsigned int nb);
int my_put_octal(unsigned int n);
int my_put_float(float nb, const int precision);
int my_flag_x(int val);
int my_flag_up_x(int val);
int my_flag_p(unsigned long val);
int my_flag_e(float nb, const int precision);
void trailing_spaces(char *str);
void my_isneg_printf(int nb, int plus_flag);
int my_printf(const char *format, ...);
void put_error(const char *str);
int my_put_nbr_in_str(int nbr, char *buffer, int start);
char **my_str_to_word_array(char *str, char *separators);
char *my_strdup(char const *src);
char *my_itoa(int nb);

#endif
