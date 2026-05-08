/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** my_shell
*/

#ifndef MY_SHELL_H_
    #define MY_SHELL_H_

    #include "my.h"
    #include "ast.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <sys/utsname.h>
    #include <signal.h>
    #include <fcntl.h>
    #include <string.h>
    #define PATH_MAX 4096
    #define HISTORY_FILE ".shell_history"

typedef struct job_list_s job_list_t;

typedef struct oldpwd_s {
    char *path;
    struct oldpwd_s *next;
} oldpwd_t;

typedef struct builtin_s {
    char *name;
    int (*func)(job_list_t *jobs, char **args, char ***env);
} builtin_t;

int detect_cmd(char **args, int *return_val, char ***env, job_list_t *jobs);
int exec_cmd(char **args, char **env);
void print_tag(void);
char *read_line(void);
void free_array(char **array);
void check_status(int status);
char *combine_path(char *dir, int len, const char *filename);
char *get_full_path(char *paths, const char *command);
char *find_command_in_path(const char *command, char **env);
char *get_cmd_path(char **args, char **env);
int my_cd(job_list_t *jobs, char **args, char ***env);
int my_setenv(job_list_t *jobs, char **args, char ***env);
int my_unsetenv(job_list_t *jobs, char **args, char ***env);
int my_exit(job_list_t *jobs, char **args, char ***env);
char *get_last_pwd(oldpwd_t *head);
void add_oldpwd_node(oldpwd_t **head, char *path);
int my_info(job_list_t *jobs, char **args, char ***env);
int my_which(job_list_t *jobs, char **args, char ***env);
int my_where(job_list_t *jobs, char **args, char ***env);
char **advanced_split(char *str);
void clean_quotes(char **args);
int my_jobs(job_list_t *jobs, char **args, char ***env);
int my_bg(job_list_t *jobs, char **args, char ***env);
int my_fg(job_list_t *jobs, char **args, char ***env);
int get_job_id(job_list_t *jobs, char *arg);
void my_put_error(const char *str);
char *env_get(char **env, const char *name);
char **apply_globbing(char **args);
char **apply_variables(char **args, char **env);
void update_last_status(int status, char ***env);
int my_history(job_list_t *jobs, char **args, char ***env);
void add_to_history(const char *line, char **env);

#endif /* !MY_SHELL_H_ */
