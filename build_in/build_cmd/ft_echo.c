#include "../../minishell.h"

int ft_op(char *cmd)
{
	int i = 1;

	if (cmd[0] != '-')
		return 0;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}
bool ft_find_echo(char *cmd)
{
	int i = 0;

	while (cmd[i])
	{
		if (!ft_op(cmd))
			return false;
		i++;
	}
	return true;
}

int ft_echo(t_env *node, char **cmd)
{
	bool op;
	t_env_eleme *current;
	char *tmp;
	int i;

	op = false;
	current = NULL;
	if (!cmd[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		node->exit_status = EXIT_SUCCESS;
		return EXIT_SUCCESS;
	}
	op = ft_find_echo(cmd[1]);
	if (op)
	{
		// no new line -n exist;
		i = 2;
		// if (cmd[i][0] == '$')
		// {
		// 	tmp = ft_substr(cmd[i], 1, ft_strlen(cmd[i]));
		// 	current = ft_find_element(node->head, tmp);
		// 	if (current != NULL)
		// 	{
		// 		free(tmp);
		// 		write(STDOUT_FILENO, current->value, ft_strlen(current->value));
		// 		if (cmd[i + 1] != NULL)
		// 			write(STDOUT_FILENO, " ", 1);
		// 		node->exit_status = EXIT_SUCCESS;
		// 	}
		// 	else
		// 	{
		// 		free(tmp);
		// 		node->exit_status = EXIT_FAILURE;
		// 	}
		// }
		// else
		// {
		// 	write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		// 	if (cmd[i + 1] != NULL)
		// 		write(STDOUT_FILENO, " ", 1);
		// 	node->exit_status = EXIT_SUCCESS;
		// }
		// tmp = ft_expand(&node, cmd, i);
		// if (!tmp)
		// {
		// 	node->exit_status = EXIT_FAILURE;
		// 	return EXIT_FAILURE;
		// }
		// write(STDOUT_FILENO, tmp, ft_strlen(tmp));
		if (!cmd[i])
			return printf("aaaa\n"), -1;
		while (cmd[i])
		{
			write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
			i++;
		}
	}
	else if (!op)
	{
		i = 1;
		// while (cmd[i])
		// {
		// 	if (cmd[i][0] == '$')
		// 	{
		// 		tmp = ft_substr(cmd[i], 1, ft_strlen(cmd[i]));
		// 		current = ft_find_element(node->head, tmp);
		// 		if (current != NULL)
		// 		{
		// 			free(tmp);
		// 			write(STDOUT_FILENO, current->value, ft_strlen(current->value));
		// 			if (cmd[i + 1] != NULL)
		// 				write(STDOUT_FILENO, " ", 1);
		// 			node->exit_status = EXIT_SUCCESS;
		// 		}
		// 		else
		// 		{
		// 			free(tmp);
		// 			node->exit_status = EXIT_FAILURE;
		// 		}
		// 	}
		// 	else
		// 	{
		// 		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		// 		if (cmd[i + 1] != NULL)
		// 			write(STDOUT_FILENO, " ", 1);
		// 		node->exit_status = EXIT_SUCCESS;
		// 	}
		// 	i++;
		// }
		// tmp = ft_expand(&node, cmd, i);
		// if (!tmp)
		// {
		// 	node->exit_status = EXIT_FAILURE;
		// 	return EXIT_FAILURE;
		// }
		while (cmd[i])
		{
			write(STDOUT_FILENO, tmp, ft_strlen(tmp));
			i++;
		}
		write(STDOUT_FILENO, "\n", 1);
	}
	node->exit_status = EXIT_SUCCESS;
	return EXIT_SUCCESS;
}
