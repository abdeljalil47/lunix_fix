#include "../../minishell.h"

void	ft_delete_env(t_env_eleme *envp)
{
	t_env_eleme *tmp;
	t_env_eleme *node;

	node = envp;
	while (node)
	{
		tmp = node->next;
        if (node->variable)
		    free(node->variable);
        if (node->value)
		    free(node->value);
        if (node)
		    free(node);
		node = tmp;
	}
	free(node);
}

t_env_eleme *ft_find_element(t_env_eleme *envp, const char *eleme)
{
	t_env_eleme *current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->variable, eleme) == 0 ||
            ft_strncmp(current->variable, eleme, ft_strlen(eleme)) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}
void	ft_delete_element(t_env_eleme *node, t_env *cmd)
{
	t_env_eleme *prev;
	if (!node || !cmd || cmd->size == 0)
		return ;
	if (cmd->head == node)
		cmd->head = node->next;
	else
	{
		prev = cmd->head;
		while (prev && prev->next != node)
			prev = prev->next;
		if (prev)
			prev->next = node->next;
	}
	cmd->size--;
	free(node->variable);
	free(node->value);
	free(node);
}
int unste_env(t_env_eleme *envp, const char *str, t_env *cmd)
{
	t_env_eleme *remove;

	remove = ft_find_element(envp, str);
	if (remove != NULL)
        ft_delete_element(remove, cmd);
	else
		return print_error("unset: not a valid identifier\n"), 0;
	return 1;
}

t_env *ft_unset(char **cmd, t_env *envp)
{
	int i;
	t_env_eleme *current;

	i = 1;
	current = envp->head;
	while (cmd[i])
	{
		if (unste_env(envp->head, cmd[i], envp) == 0)
			return NULL;
		i++;
	}
	return envp;
}
