/*
** EPITECH PROJECT, 2025
** Project - my_printf
** File description:
** Header file for
** c
*/

#ifndef MY_PRINTF_H
    #define MY_PRINTF_H

    #include <stdarg.h>

typedef int (*handler_t)(va_list);

typedef struct dispatch_s {
    const char *flag;
    handler_t func;
} dispatch_t;

int my_printf(const char *format, ...);
void trailing_spaces(char *str);

#endif // MY_PRINTF_H
