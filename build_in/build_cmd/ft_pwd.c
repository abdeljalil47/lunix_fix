#include "../../minishell.h"

void    ft_pwd(t_env_eleme *head)
{
    char buffer[1024];
    char *cwd;

    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd)
        printf("%s\n",buffer);
    else
    {
        t_env_eleme *currnet = ft_find_element(head, "OLDPWD");
        printf("%s\n", currnet->value);
    }
}
