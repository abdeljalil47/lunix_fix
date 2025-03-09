#include "../../minishell.h"
/*
*The ‘export’ command is one of the essential built-in commands in the Bash shell,
* allowing users to manage environment variables effectively.
*Only export print env but in ascinding order first UP then LOW "declare -x "
*export [variable=value] if variable in UP ascinding or LOW ascinding in buttom
*It change the variable env value
*If '$' it search on env then change the value but the value shouls be alpha;
*If not '$' it add on env variable and value;
** if $ mean value else mean variable;
*/

t_env_eleme	*ft_sort_env(t_env_eleme *env)
{
	t_env_eleme *current;
	t_env_eleme *small = NULL;
	int swap = 1;
	char *variable;
	char *value;

	while (swap)
	{
		swap = 0;
		current = env;
		while (current->next != small)
		{
			if (ft_strcmp(current->variable, current->next->variable) > 0)
			{
				variable = current->variable;
				value = current->value;

				current->variable = current->next->variable;
				current->value = current->next->value;

				current->next->variable = variable;
				current->next->value = value;
				swap = 1;
			}
			current = current->next;
		}
		small = current;
	}
	return (env);
}

void    ft_print_env(t_env_eleme *envp, int size)
{
	t_env_eleme *ascind;

	ascind = ft_sort_env(envp);
	while (ascind != NULL)
	{
		printf("declare -x %s=%s\n", ascind->variable, ascind->value);
		ascind = ascind->next;
	}
}

int num_arg_exp(char **args)
{
	int i = 0;
	int size = 0;

	while (args[i])
	{
		i++;
	}
	return i;
}

int ft_export(t_env *cmd, char **args)
{
	char **envpp = cmd->env->envp;
	if (envpp == NULL)
		return print_error("minishell: environment variables are not set\n"), 1;
	t_env *env = ft_env_copy(cmd->head);
	if (env == NULL)
		return print_error("minishell: failed to copy env\n"), 1;
	if (num_arg_exp(args) == 1)
		ft_print_env(env->head, env->size);
	if (num_arg_exp(args) > 1)
	{
		if (ft_export_check(cmd, args))
			return 0;
	}
	return 1;
}
