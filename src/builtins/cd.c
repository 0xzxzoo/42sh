/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** cd
*/

#include "42sh/my_shell.h"
#include "my.h"
#include <sys/stat.h>

static char *find_home_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "HOME=", 5) == 0)
            return env[i] + 5;
    }
    put_error("cd: HOME not set\n");
    return NULL;
}

static char *get_target_dir(job_list_t *jobs, char **args, char **env)
{
    char *dir = args[1];

    if (!dir || my_strcmp(dir, "~") == 0)
        return find_home_env(env);
    if (my_strcmp(dir, "-") == 0)
        return get_last_pwd(jobs->oldpwd);
    return dir;
}

static void print_cd_error(char *dir)
{
    put_error(dir);
    if (errno == ENOTDIR)
        put_error(": Not a directory.\n");
    else if (errno == EACCES)
        put_error(": Permission denied.\n");
    else
        put_error(": No such file or directory.\n");
}

static int do_chdir(job_list_t *jobs, char *dir)
{
    char cwd[PATH_MAX];

    if (!getcwd(cwd, sizeof(cwd)))
        return 1;
    if (chdir(dir) != 0) {
        print_cd_error(dir);
        return 1;
    }
    add_oldpwd_node(&jobs->oldpwd, cwd);
    return 0;
}

int my_cd(job_list_t *jobs, char **args, char ***env)
{
    char *dir = get_target_dir(jobs, args, *env);

    if (!dir)
        return 1;
    return do_chdir(jobs, dir);
}
