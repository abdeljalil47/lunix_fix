#include "../minishell.h"

int ft_manage_cmd_build(t_env *env, char **args, char *cmd)
{
    if (ft_strcmp("echo", cmd) == EQUAL)
        return ft_echo(env, args), EXIT_SUCCESS;
    else if (ft_strcmp("cd", cmd) == EQUAL)
        return my_cd(env, args[1]), EXIT_SUCCESS;  
    else if (ft_strcmp("pwd", cmd) == EQUAL)
        return ft_pwd(env->head), EXIT_SUCCESS;
    else if (ft_strcmp("export", cmd) == EQUAL)
        return ft_export(env, args), EXIT_SUCCESS;
    else if (ft_strcmp("unset", cmd) == EQUAL)
        return ft_unset(args, env), EXIT_SUCCESS;
    else if (ft_strcmp("env", cmd) == EQUAL)
        return ft_env(env, args), EXIT_SUCCESS;
    else if (ft_strcmp("exit", cmd) == EQUAL)
        return ft_exit(env, args), EXIT_SUCCESS;
    else
        error_exit("command not found\n");
    return EXIT_SUCCESS;
}
