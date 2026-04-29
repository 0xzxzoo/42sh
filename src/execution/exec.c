/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** exec
*/

#include "42sh/my_shell.h"
#include "my.h"
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

void check_status(int status)
{
    int sig;

    if (!WIFSIGNALED(status))
        return;
    sig = WTERMSIG(status);
    if (sig == SIGSEGV)
        write(2, "Segmentation fault", 18);
    if (sig == SIGFPE)
        write(2, "Floating exception", 18);
    if (sig == SIGSEGV || sig == SIGFPE) {
        if (WCOREDUMP(status))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
}

static int execute_command(char *cmd_path, char **args, char **env)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1) return 84;
    if (pid == 0) {
        if (execve(cmd_path, args, env) == -1) {
            if (errno == ENOEXEC) {
                write(2, cmd_path, my_strlen(cmd_path));
                write(2, ": Exec format error. Binary file not executable.\n", 49);
            } else
                perror(cmd_path);
            exit(1);
        }
    }
    waitpid(pid, &status, 0);
    check_status(status);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

static int check_directory(char *path)
{
    struct stat st;

    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        write(2, path, my_strlen(path));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    return 0;
}

int exec_cmd(char **args, char **env)
{
    char *cmd_path = get_cmd_path(args, env);
    int return_val = 0;

    if (!cmd_path) {
        free_array(args);
        return 1;
    }
    if (check_directory(cmd_path)) {
        free(cmd_path);
        free_array(args);
        return 1;
    }
    return_val = execute_command(cmd_path, args, env);
    free(cmd_path);
    free_array(args);
    return return_val;
}
