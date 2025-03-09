#include "../minishell.h"

char **ft_tab_env(t_env *env)
{
	char **tab;
	char *tmp;
	int i = 0;
	int y = 0;
	int z = env->size;
	t_env_eleme *current;

	if (!env || !env->head)
		return NULL;
	tab = malloc((z + 1) * sizeof(char *));
	if (!tab)
		return NULL;
	tab[z] = NULL;
	current = env->head;
	while (i < z)
	{
		y = ft_strlen(current->variable) + ft_strlen(current->value);
		tab[i] = malloc(y + 2);
		if (!tab[i])
		{
			while (i-- > 0)
				free(tab[i]);
			free(tab);
			return NULL;
		}
		ft_strlcpy(tab[i], current->variable, y + 2);
		ft_strlcat(tab[i], current->value, y + 2);
		current = current->next;
		i++;
	}
	return tab;
}

char **find_path(char **env)
{
	int i;
	char *str;
	char **res;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH=", 5);
		if (str)
			break ;
		i++;
	}
	if (!str)
		return (NULL);
	res = ft_split(str + 5, ':');
	if (!res)
		return NULL;
	return (res);
}
