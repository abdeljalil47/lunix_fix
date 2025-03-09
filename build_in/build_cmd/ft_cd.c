#include "../../minishell.h"
/*
** chdir()
** getcwd()
*/

int ft_find_equal(char *env)
{
	int i = 0;

	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return -1;
}

t_env_eleme	*find_env_var(t_env *env, const char *var)
{
	t_env_eleme *current = env->head;
	while (current)
	{
		if (ft_strcmp(current->variable, var) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void update_env_var(t_env **env, const char *var, const char *new_value)
{
	t_env_eleme *entry = find_env_var(*env, var);

	if (entry)
	{
		free(entry->value);
		entry->value = ft_strdup(new_value);
	}
	else
	{
		t_env_eleme *new_var = malloc(sizeof(t_env_eleme));
		if (!new_var)
			return;
		new_var->variable = ft_strdup(var);
		new_var->value = ft_strdup(new_value);
		new_var->next = (*env)->head;
		(*env)->head = new_var;
		(*env)->size++;
	}
}
void free_env(t_env *env)
{
	if (env == NULL)
		return ;
	t_env_eleme *current = env->head;
	t_env_eleme *next;
	while (current != NULL)
	{
		next = current->next;
		free(current->variable);
		free(current->value);
		free(current);
		current = next;
	}
	free(env);
}
int my_cd(t_env *env, const char *path)
{
	t_env *new_env;
	char old_path[1024];
	char new_path[1024];

	getcwd(old_path, sizeof(old_path));
	// {
	// 	perror("getcwd");
	// 	env->exit_status = EXIT_FAILURE;
	// 	return (-1);
	// }
	if (!path || ft_strcmp(path, "~") == 0)
	{
		t_env_eleme *home_var = find_env_var(env, "HOME=");
		if (!home_var || !home_var->value)
		{
			fprintf(stderr, "cd: HOME not set here\n");
			env->exit_status = EXIT_FAILURE;
			return (-1);
		}
		path = home_var->value;
	}
	else if (ft_strcmp(path, "-") == 0)//cd -
	{
		t_env_eleme *oldpwd_var = find_env_var(env, "OLDPWD=");
		if (!oldpwd_var || !oldpwd_var->value)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			env->exit_status = EXIT_FAILURE;
			return -1;
		}
		path = oldpwd_var->value;
		printf("%s\n", path);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		env->exit_status = EXIT_FAILURE;
		return -1;
	}
	getcwd(new_path, sizeof(new_path));
	// {
	// 	perror("getcwd");
	// 	env->exit_status = EXIT_FAILURE;
	// 	return -1;
	// }
	update_env_var(&env, "PWD=", new_path);
	update_env_var(&env, "OLDPWD=", old_path);
	env->exit_status = EXIT_SUCCESS;
	return EXIT_SUCCESS;
}
