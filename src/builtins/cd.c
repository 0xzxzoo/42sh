/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** cd
*/

#include "42sh/my_shell.h"
#include "my.h"

static char *find_home_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "HOME=", 5) == 0)
            return env[i] + 5;
    }
    return NULL;
}

static char *cd_home(char **env)
{
    char *home = find_home_env(env);

    if (!home) {
        put_error("cd: HOME not set\n");
        return NULL;
    }
    return home;
}

static char *cd_oldpwd(oldpwd_t *oldpwd_list)
{
    char *oldpwd = get_last_pwd(oldpwd_list);

    if (!oldpwd) {
        put_error(": No such file or directory.\n");
        return NULL;
    }
    return oldpwd;
}

static int execute_cd(char *dir, oldpwd_t **oldpwd_list)
{
    char cwd[4096];

    if (!getcwd(cwd, 4096))
        return 1;
    if (chdir(dir) != 0) {
        put_error(dir);
        put_error(": Not a directory.\n");
        return 1;
    }
    add_oldpwd_node(oldpwd_list, cwd);
    return 0;
}

int my_cd(char **args, char ***env)
{
    oldpwd_t *oldpwd_list;
    char *dir = args[1];

    oldpwd_list = NULL;
    if (!dir || (dir && my_strcmp(dir, "~") == 0)) {
        dir = cd_home(*env);
    }
    if (dir && my_strcmp(dir, "-") == 0) {
        dir = cd_oldpwd(oldpwd_list);
    }
    if (chdir(dir) != 0) {
        put_error("cd: cannot access directory\n");
        return 1;
    }
    return 0;
}
