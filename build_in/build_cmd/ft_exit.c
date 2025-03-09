#include "../../minishell.h"

int ft_check_arg(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int num_arg(char **args)
{
	int i = 0;
	int size = 0;

	while (args[i])
	{
		size++;
		i++;
	}
	return size;
}
int	ft_check_exit_st(t_env *cmd, char **args)
{
	if (args[0] && !args[1])
	{
		exit(EXIT_SUCCESS);
	}
	if (num_arg(args) > 2)
	{
		print_error("exit\nminishell: exit: too many arguments\n");
		cmd->exit_status = 1;
		return 0;
	}
	if (!ft_check_arg(args[1]))
	{
		print_error("minishell: exit: numeric argument required\n");
		cmd->exit_status = 255;
		exit(255);
	}
	return 0;
}
int ft_exit(t_env *cmd, char **args)
{
	if (ft_check_exit_st(cmd, args))
		return 1;
	exit(cmd->exit_status);
	return EXIT_SUCCESS;
}
