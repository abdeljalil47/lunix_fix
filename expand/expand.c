#include "../minishell.h"

int is_alphanum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
t_env_eleme *ft_find_element_env(t_env_eleme *envp, const char *eleme)
{
	t_env_eleme *current;
    char *tmp;

	current = envp;
	while (current != NULL)
	{
        tmp = ft_strtrim(current->variable, "=");
		if (ft_strcmp(tmp, eleme) == 0)
			return free(tmp), current;
		current = current->next;
        free(tmp);
	}
	return NULL;
}
char *ft_search_var(char *key, t_env **cmd)
{
	t_env_eleme *current = NULL;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa((*cmd)->exit_status));
	current = ft_find_element_env((*cmd)->head, key);
	if (current == NULL)
		return NULL;
	return (ft_strdup(current->value));
}

char *ft_get_va_env(char *str, t_env **cmd)
{
    char key[1024];
    int x = 0;

    if (*str == '?')
    {
        str++;
        return ft_itoa((*cmd)->exit_status);
    }
    while (*str && is_alphanum(*str) && x < 1023)
        key[x++] = (*str++);
    key[x] = '\0';
    return ft_search_var(key, cmd);
}

char *ft_handle_value(t_env **cmd, char *arg)
{
    char *res = malloc(1024);
    char *value;
    int y = 0, j = 0;

    if (!arg || !res)
        return NULL;
    while (arg[j] && y < 1023)
    {
        if (arg[j] == '$' && arg[j + 1] != '$')
        {
            j++;
            if (arg[j] == '?')
            {
                j++;
                value = ft_itoa((*cmd)->exit_status);
            }
            else if (is_alphanum(arg[j]))
            {
                value = ft_get_va_env(&arg[j], cmd);
                while (arg[j] && is_alphanum(arg[j]))
                    j++;
            }
            else
                value = NULL;
            if (value)
            {
                int m = 0;
                while (value[m] && y < 1023)
                    res[y++] = value[m++];
                free(value);
            }
            // else
            // {
            //     res[y++] = '$';
			// 	// j++;
            // }
        }
        else
            res[y++] = arg[j++];
        if (y >= 1023)
            break;
    }
    res[y] = '\0';
    return res;
}
void    ft_check(char *arg, bool *flag)
{
    if (arg[0] == '\"')
        *flag = true;
}
char *ft_expand(t_env **cmd, char **args, int i)
{
    char *value;
    char *old = NULL;
    bool flag = false;
    char *res = ft_strdup("");

    if (!res)
        return NULL;
    ft_check(args[i], &flag);
    if (flag == true)
    {
        while (args[i])
        {
            old = res;
            value = ft_handle_value(cmd, args[i]);
            if (!value)
                return NULL;
            
            res = ft_strjoin(res, value);
            free(old);
            free(value);

            if (args[i + 1] != NULL)
            {
                old = res;
                res = ft_strjoin(res, " ");
                free(old);
            }
            i++;
        }
    }
    else
    {
        while (args[i])
        {
            old = res;
            res = ft_strjoin(res, args[i]);
            free(old);

            if (args[i + 1] != NULL)
            {
                old = res;
                res = ft_strjoin(res, " ");
                free(old);
            }
            i++;
        }
    }
    return (res);
}
