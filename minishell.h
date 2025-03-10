#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

typedef struct s_main t_main;

typedef struct s_env_eleme
{
	char *variable;
	char *value;
	struct s_env_eleme *next;
} t_env_eleme;

typedef struct s_env
{
	t_env_eleme *head;
	t_main		*env;
	int size;
	int exit_status;
} t_env;

typedef enum s_enum
{
	EQUAL = 0,
	COMMAND,
	INFILE,
	OUTFILE,
	HERE_DOC,
	APPAND,
	REDRICTION,
	NONE,
	BUILT_IN,
} t_enum;
//redirection: in out appand here_doc 

typedef struct s_redirction
{
	t_enum redir;
	char *file;
} t_redirction;

typedef struct minishell
{
	char *cmd;
	char **args;
	t_enum type;
	t_enum direction;
	t_redirction *path_infile;
	t_redirction *path_outfile;
	t_redirction *here_doc;
	t_redirction *appand;
	struct minishell *next;
} t_m_shell;

typedef struct s_shell_list
{
    t_m_shell *head;
    int cmd_size;
} t_shell_list;


typedef struct s_main
{
	int ac;
	char **av;
	char **envp;
	t_env *env;
}	t_main;

typedef struct s_cmd
{
	t_env_eleme *envp;
	t_main 	*main;
	t_env	*env;
	int flag;
}	t_cmd;



typedef struct s_pipe
{
	int	pid;
	int	pip[2];
	int	i;
	int	prev_fd;
}	t_pipe;



void		error_exit(const char *str);
void		print_error(const char *str);
void		write_error(char *str, char *s, char *err);

int			ft_manage_cmd_build(t_env *env, char **args, char *cmd);

int			ft_find_equal(char *env);
t_env_eleme	*ft_find_element(t_env_eleme *envp, const char *eleme);
t_env		*ft_env_handle(char **envp);
t_env		*ft_env_copy(t_env_eleme *head);
void		ft_delete_env(t_env_eleme *envp);

void		ft_pwd(t_env_eleme *head);
int			ft_env(t_env *cmd, char **av);
int			my_cd(t_env *env, const char *path);
int			ft_echo(t_env *cmd, char **args);
t_env		*ft_unset(char **cmd, t_env *envp);
int			ft_exit(t_env *cmd, char **args);
int			ft_export(t_env *cmd, char **args);

int			ft_export_check(t_env *cmd, char **args);
char		*ft_expand(t_env **cmd, char **args, int i);

char		**ft_tab_env(t_env *env);
char		**find_path(char **env);
void		ft_excute(t_shell_list **cmd, t_env **env);

#endif
