/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Implementation for
** c
*/

#include "my_printf.h"
#include "flag.h"
#include "my.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* function pointer declaration
* returns an integer, takes a va_list
*/

/**
* dispatcher s truct
* takes a flag & a function pointer
*/
// clang-format off

static const dispatch_t g_dispatch_func[] = {{"c", printf_char},
    {"s", printf_string},
    {"d", printf_decimal},
    {"i", printf_decimal},
    {"%", printf_modulo},
    {"u", printf_unsdecimal},
    {"o", printf_intoctal},
    {"x", printf_hex},
    {"X", printf_hex_up_x},
    {"f", printf_float},
    {"F", printf_float},
    {"p", printf_pointer},
    {"e", printf_scientific},
    {"+", printf_sign_plus},
    {NULL, NULL}};

// clang-format off

// get the global dispatcher size
static const size_t g_dispatch_size = sizeof(g_dispatch_func)
    / sizeof(g_dispatch_func[0]);
static int subpf(const char *format, va_list args)
{
    size_t flag_lenght = 0;

    for (size_t i = 0; i < g_dispatch_size - 1; ++i) {
        flag_lenght = my_strlen(g_dispatch_func[i].flag);
        if (my_strncmp(format, g_dispatch_func[i].flag, flag_lenght) == 0) {
            g_dispatch_func[i].func(args);
            return flag_lenght;
        }
    }
    return 0;
}

int my_printf(const char *format, ...)
{
    va_list args;

    if (!format || !*format)
        return 255;
    va_start(args, format);
    while (*format) {
        if (*format == '%' && *(format + 1) != '\0') {
            ++format;
            subpf(format, args);
            ++format;
        } else {
            my_putchar(*format);
            ++format;
        }
    }
    va_end(args);
    return 0;
}
