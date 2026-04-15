/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** demo.c
*/

#include "42sh/my_shell.h"
#include "my.h"

int my_info(char **args, char ***env)
{
    struct utsname info;

    if (uname(&info) == -1) {
        return 84;
    }
    my_printf("\t   __ __ ___        __  \n");
    my_printf("\t  / // /|__ \\ _____/ /_ \n");
    my_printf("\t / // /___/ // ___/ __ \\ \n");
    my_printf("\t/__  __/ __/(__  ) / / /\n");
    my_printf("\t  /_/ /____/____/_/ /_/ \n");
    my_putchar('\n');
    my_printf("\t System: %s\n", info.sysname);
    my_printf("\t Kernel: %s\n", info.release);
    my_putchar('\n');
    return 0;
}
