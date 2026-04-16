/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** my_shell
*/

// clang-format off
#ifndef MY_SHELL_H_
    #define MY_SHELL_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <sys/utsname.h>

typedef struct oldpwd_s {
    char *path;
    struct oldpwd_s *next;
} oldpwd_t;

typedef struct builtin_s {
    char *name;
    int (*func)(char **args, char ***env);
} builtin_t;

int detect_cmd(char **args, int *return_val, char ***env);
int detect_pipe(char *line, char ***env);
int exec_cmd(char **args, char **env);
int process_line(char *line, char ***env);
void print_tag(void);
int pid(char *line, char ***env);
char *read_line(void);
void free_array(char **array);
void check_status(int status);
char *get_full_path(char *paths, const char *command);
char *find_command_in_path(const char *command, char **env);
char *get_cmd_path(char **args, char **env);
int my_cd(char **args, char ***env);
int my_setenv(char **args, char ***env);
int my_unsetenv(char **args, char ***env);
int my_exit(char **args, char ***env);
void check_exit_in_pipe(char *cmd);
int my_pipe(char **args, int i, int pipe_count);
char *get_last_pwd(oldpwd_t *head);
void add_oldpwd_node(oldpwd_t **head, char *path);
void process_semicolons(char *line, char ***env);
int my_info(char **args, char ***env);
int my_which(char **args, char ***env);
int my_where(char **args, char ***env);

#endif /* !MY_SHELL_H_ */
