#include "../minishell.h"

t_env *ft_env_handle(char **envp)
{
	t_env *new;
	t_env_eleme *new_element;
	t_env_eleme *temp;
	int z;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return NULL;
	z = 0;
	new->head = NULL;
	new->size = 0;
	for (int i = 0; envp[i] != NULL; i++)
	{
		new_element = malloc(sizeof(t_env_eleme));
		if (new_element == NULL)
			return NULL;
		z = ft_find_equal(envp[i]);
		if (z == -1)
		{
			free(new_element);
			continue;
		}
		new_element->variable = ft_substr(envp[i], 0, z + 1);
		new_element->value = ft_substr(envp[i], z + 1, ft_strlen(envp[i]) - z);
		if (!new_element->variable || !new_element->value)
		{
			free(new_element->variable);
			free(new_element->value);
			free(new_element);
			return NULL;
		}
		new_element->next = NULL;
		if (new->head == NULL)
			new->head = new_element;
		else
		{
			temp = new->head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_element;
		}
		new->size++;
	}
	return new;
}

t_env *ft_env_copy(t_env_eleme *head)
{
	t_env *new;
	t_env_eleme *new_element;
	t_env_eleme *current = head;
	t_env_eleme *temp;
	int z;
	if (head == NULL)
		return NULL;
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return NULL;
	z = 0;
	new->head = NULL;
	new->size = 0;
	for (int i = 0; current != NULL; i++)
	{
		new_element = malloc(sizeof(t_env_eleme));
		if (new_element == NULL)
			return NULL;
		z = ft_find_equal(current->variable);
		if (z == -1)
		{
			free(new_element);
			continue;
		}
		new_element->variable = ft_substr(current->variable, 0, z);
		new_element->value = ft_substr(current->value, 0, ft_strlen(current->value));
		if (!new_element->variable || !new_element->value)
		{
			free(new_element->variable);
			free(new_element->value);
			free(new_element);
			return NULL;
		}
		new_element->next = NULL;
		if (new->head == NULL)
			new->head = new_element;
		else
		{
			temp = new->head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_element;
		}
		new->size++;
		current = current->next;
	}
	return new;
}
