#include "../../minishell.h"

int check(int c)
{
	return (c == '$');
}

int check_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int ft_count_equa(char *tmp, bool *equal, int c)
{
	int i = 0;

	while (tmp[i])
	{
		if (tmp[i] == (char)c)
			return *equal = true, i;
		i++;
	}
	return i;
}
int change_env_va(t_env_eleme *current, char *args)
{
	free(current->value);
	current->value = ft_strdup(args);
	if (!current->value)
		return 0;
	return 1;
}
int ft_check_env_value(t_env_eleme *current, t_env_eleme *head, char *str)
{
	t_env_eleme *node;
	t_env_eleme *new;

	node = ft_find_element(head, current->value);
	if (node != NULL)
	{
		free(node->value);
		node->value = ft_strdup(str);
		if (!node->value)
			return 0;
	}
	else
		return 0;
	return 1;
}

int change_env(t_env_eleme *current, char *args, t_env_eleme **head)
{
	t_env_eleme *new;
	t_env_eleme *node;
	char *tmp;

	node = *head;
	if (ft_check_env_value(current, node, args))
		return 1;
	new = malloc(sizeof(t_env_eleme));
	if (new == NULL)
		return 0;
	tmp = ft_strjoin(current->value, "=");
	if (!tmp)
		return free(new), 0;
	new->variable = ft_strdup(tmp);
	if (!new->variable)
		return free(new), free(tmp), 0;
	new->value = ft_strdup(args);
	if (!new->value)
		return free(new->variable), free(tmp), free(new), 0;
	new->next = NULL;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
	return 1;
}
// fix this ??
int ft_value_value(t_env_eleme **cmd, char **args, int i)
{
	t_env_eleme *current;
	t_env_eleme *node;
	t_env_eleme *new;
	char *tmp;
	char *val;
	int z = 0;
	bool eul = false;

	node = *cmd;
	if (args[i][0] == '$')
	{
		z = ft_count_equa(args[i], &eul, '=');
		tmp = ft_substr(args[i], 1, z);
		val = ft_substr(args[i], z + 1, ft_strlen(args[i]));
		// printf("%s\n", tmp);
		// printf("%s\n", val);
		if (!tmp || !val)
			return 0;
		current = ft_find_element(node, tmp);
		if (current && !check_alpha(current->value[0]))
			return write_error("minishell: export: ", " not a valid identifier\n", current->value), 0;
		if (!change_env(current, val, cmd))
			return free(tmp), 0;
		free(tmp);
	}
	else if (args[i][0] != '$')
	{
		z = ft_count_equa(args[i], &eul, '=');
		tmp = ft_substr(args[i], 0, z);
		val = ft_substr(args[i], z + 1, ft_strlen(args[i]));
		if (!tmp || !val)
			return 0;
		current = ft_find_element(node, tmp);
		if (!change_env_va(current, val))
			return free(tmp), 0;
		free(tmp);
	}
	return 1;
}

// // int ft_find_env(t_env_eleme **cmd, char **args, int i)
// // {
// // 	t_env_eleme *current;
// // 	t_env_eleme *node;

// // 	if (i % 2 == 1)
// // 	{
// // 		node = *cmd;
// // 		current = ft_find_element(node, args[i]);
// // 		if (current != NULL)
// // 		{
// // 			free(current->value);
// // 			current->value = ft_strdup(args[++i]);
// // 			if (current->value)
// // 				return 0;
// // 		}
// // 	}
// // 	return 1;
// // }

int ft_count(char *s, bool *equal, int c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == (char)c)
			return (*equal = true, i);
		i++;
	}
	return *equal = true, i;
}

int ft_check_expo(t_env_eleme *cmd, char **args)
{
	int i;
	int z = 0;
	char *tmp;
	bool equal = false;

	if (!args || !args[0])
		return 0;
	i = 1;
	while (args[i])
	{
		z = 0;
		if (args[i] && args[i][0] == '$')
		{
			z = ft_count(args[i], &equal, '=');
			tmp = ft_substr(args[i], 1, z);
			if (!tmp)
				return 0;
			// printf("%s\n", tmp);
			if (!ft_find_element(cmd, tmp))
				return free(tmp), 0;
			free(tmp);
		}
		else if (args[i] && args[i][ft_strlen(args[i]) - 2] == '$')
			return 0;
		i++;
	}
	return 1;
}

int ft_alph_arg(char **args)
{
	int i;

	if (!args || !args[0])
		return 1;
	i = 1;
	while (args[i])
	{
		if (i % 2 == 1)
		{
			if (args[i][0] == '$')
			{
				i++;
				continue;
			}
			else if (!ft_isalpha(args[i][0]))
				return 0;
			else if (args[i][ft_strlen(args[i]) - 1] == '$')
				return 0;
		}
		i++;
	}
	return 1;
}

int ft_add_back(t_env **cmd, char *arg, char *tmp, bool eq)
{
	t_env_eleme *node;
	t_env_eleme *current;
	char *temp;

	if (!cmd || !(*cmd))
		return 0;
	current = malloc(sizeof(t_env_eleme));
	if (!current)
		return 0;
	if (!tmp)
	{
		free(current);
		return 0;
	}
	current->variable = ft_strdup(tmp);
	if (!current->variable)
	{
		free(current);
		return 0;
	}
	if (eq == false)
	{
		temp = ft_strjoin(current->variable, "=");
		if (!temp)
		{
			free(current->variable);
			free(current);
			return 0;
		}
		free(current->variable);
		current->variable = temp;
		current->value = ft_strdup("''");
		if (!current->value)
		{
			free(current->variable);
			free(current);
			return 0;
		}
		current->next = NULL;
		if (!(*cmd)->head)
			(*cmd)->head = current;
		else
		{
			node = (*cmd)->head;
			while (node->next)
				node = node->next;
			node->next = current;
		}
	}
	else
	{
		current->value = ft_strdup(arg);
		if (!current->value)
		{
			free(current->variable);
			free(current);
			return 0;
		}
		current->next = NULL;
		if (!(*cmd)->head)
			(*cmd)->head = current;
		else
		{
			node = (*cmd)->head;
			while (node->next)
				node = node->next;
			node->next = current;
		}
	}
	return 1;
}

int ft_check_env_variable(t_env_eleme *head, char *tmp, char *value)
{
	t_env_eleme *current;
	if (!tmp)
		return 0;
	current = ft_find_element(head, tmp);
	if (current != NULL)
	{
		if (value)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				return 0;
		}
	}
	else
		return 0;
	return 1;
}
int ft_add_env(t_env *cmd, char *arg, char *tmp, bool eq)
{
	if (!cmd || !tmp)
		return 0;
	if (ft_check_env_variable(cmd->head, tmp, arg))
		return 1;
	if (!ft_add_back(&cmd, arg, tmp, eq))
		return 0;
	return 1;
}
//if = do else no
void check_parc(t_env_eleme *cmd, char **args, int i, bool *status)
{
	char *tmp;
	int size = 0;
	bool eap = false;

	if (args[i] && args[i][0] == '$')
	{
		size = ft_count(args[i], &eap, '=');
		if (eap = false)
		{
			*status = false;
			print_error("minishell: export: not an identifier attribute\n");
			return ;
		}
		tmp = ft_substr(args[i], 1, size);
		if (!tmp)
		{
			*status = false;
			print_error("minishell: export: not an identifier attribute\n");
			return;
		}
		if (ft_find_element(cmd, tmp))
		{
			free(tmp);
			*status = true;
			return;
		}
		else
		{
			free(tmp);
			*status = false;
			print_error("minishell: export: not an identifier attribute\n");
			return;
		}
	}
}
void ft_check_equ(char *arg, bool *plus)
{
	int i = 0;

	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			*plus = true;
		i++;
	}
}
int ft_handle_equ(t_env *cmd, char *value, char *tmp)
{
	t_env_eleme *current = NULL;
	char *s;
	char *str;

	if (!tmp || !cmd || !value)
		return 1;
	str = ft_substr(tmp, 0, ft_strlen(tmp) - 2);
	// printf("%s\n", str);
	current = ft_find_element(cmd->head, str);
	if (current != NULL)
	{
		s = ft_strjoin(current->value, value);
		free(current->value);
		current->value = ft_strdup(s);
		free(s);
	}
	else
		return write_error("export: not valid in this context: ", "\n", tmp), 1;
	return 0;
}

int ft_add(int i, char **args, t_env *cmd)
{
	char *tmp;
	char *str;
	char *tmp1 = NULL;
	bool equal;
	bool status;
	bool plus = false;
	int z = 0;

	if (!args || !*args)
		return 0;
	tmp = ft_strjoin(args[i], NULL);
	if (!tmp)
		return 0;
	z = ft_count(tmp, &equal, '$');
	if (equal == true)
	{
		if (z == 0)
			return free(tmp), 0;
		if (z != ft_strlen(args[i]))
		{

			str = ft_substr(tmp, 0, z);
			if (!str)
				return free(tmp), 0;
			free(tmp);
			tmp = ft_strjoin(str, "=");
			if (!tmp)
				return free(str), 0;
			free(str);
		}
		equal = false;
		z = 0;
		z = ft_count_equa(tmp, &equal, '=');
		if (z == 0)
			return 0;
		ft_check_equ(tmp, &plus);
		if (plus == true)
		{
			if (ft_handle_equ(cmd, args[++i], tmp))
				return 0;
		}
		if (equal == true)
		{
			str = ft_substr(tmp, 0, z + 1);
			tmp1 = ft_substr(tmp, z + 1, ft_strlen(tmp));
			// printf("str: %s\n", str);
			// printf("tmp1: %s\n", tmp1);
			if (!ft_add_env(cmd, tmp1, str, equal))
				return 0;
		}
		else
		{
			if (!ft_add_env(cmd, tmp1, tmp, equal))
				return 0;
		}
		free(tmp);
	}
	return 1;
}

int ft_export_check(t_env *cmd, char **args)
{
	int i = 1;
	char *tmp;
	char *str;
	int z = 0;
	bool x;
	bool equal;

	equal = false;
	x = false;
	if (!ft_alph_arg(args)) // check if export aaaa$
		return print_error("minishell: export: not an identifier attribute\n"), 1;
	if (!ft_check_expo(cmd->head, args))
		return print_error("minishell: export: zsh: not found\n"), 1;
	while (args[i])
	{
		x = false;
		if (args[i][0] == '=')
		{
			write_error("minishell: export: `", "´: not a valid identifier\n", args[i]);
			i++;
		}
		if (x == false)
		{
			check_parc(cmd->head, args, i, &x);
			if (x == true)
				ft_value_value(&cmd->head, args, i);
		}
		if (!ft_add(i, args, cmd))
			return EXIT_FAILURE;
		i++;
	}
	return (EXIT_SUCCESS);
}
/*
** fix the command export `ppp mm= aaa´
*/