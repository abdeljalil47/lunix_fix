#include "../../minishell.h"

int ft_env(t_env *cmd, char **av)
{
	t_env_eleme *current;

	if (!cmd->head)
		return (cmd->exit_status = EXIT_FAILURE, EXIT_FAILURE);
	if (!av[1])
	{
		current = cmd->head;
		while (current != NULL)
		{
			if (current->variable && current->value)
				printf("%s%s\n", current->variable, current->value);
			current = current->next;
		}
	}
	else
	{
		print_error("minishell: env: Too many arguments.\n");
		return (cmd->exit_status = EXIT_FAILURE, EXIT_FAILURE);
	}
	cmd->exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
