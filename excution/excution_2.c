#include "../minishell.h"
/*
*When a process calls waitpid to wait for a child process to change state (e.g., terminate), the kernel may put the calling process in a blocked state.
	If a signal is delivered to the process while it is waiting, the waitpid call may be interrupted.
	In such cases, waitpid returns -1, and errno is set to EINTR.
*/
int ft_open_file(t_m_shell *cmd)
{
	int fd = -1;

	if (!cmd)
		return print_error("minishell: error: The redirection command is NULL.\n"), -1;
	if (cmd->path_outfile != NULL && cmd->path_outfile->file == NULL)
		return print_error("minishell: error: path_outfile is NULL or has an invalid file.\n"), -1;
	else if (cmd->path_infile != NULL && cmd->path_infile->file == NULL)
		return print_error("minishell: error: path_infile file is NULL.\n"), -1;
	else if (cmd->here_doc != NULL && cmd->here_doc->file == NULL)
		return print_error("minishell: error: here_doc file is NULL.\n"), -1;
	else if (cmd->appand != NULL && cmd->appand->file == NULL)
		return print_error("minishell: error: appand file is NULL.\n"), -1;
	if (cmd->direction == NONE)
		return 0;
	else if (cmd->direction == INFILE && cmd->path_infile->redir == INFILE)
	{
		fd = open(cmd->path_infile->file, O_RDONLY);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else if (cmd->direction == OUTFILE && cmd->path_outfile->redir == OUTFILE)
	{
		fd = open(cmd->path_outfile->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else if (cmd->direction == HERE_DOC && cmd->here_doc->redir == HERE_DOC)
	{
		fd = open(cmd->here_doc->file, O_RDONLY);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else if (cmd->direction == APPAND && cmd->appand->redir == APPAND)
	{
		fd = open(cmd->appand->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else
		error_exit("Error: Unknown redirection type in ft_open_file.\n");
	return (fd);
}

int ft_redirection(int fd, t_m_shell *redir, t_pipe *direc, int size)
{
	static int m = 1;
	if (redir->direction == INFILE || redir->direction == HERE_DOC)
	{
		if (fd != 0 && dup2(fd, STDIN_FILENO) == -1)
			return error_exit("Function dup2() failed -1\n"), EXIT_FAILURE;
	}
	if (redir->direction == OUTFILE || redir->direction == APPAND)
	{
		if (fd != 0 && dup2(fd, STDOUT_FILENO) == -1)
			return error_exit("Function dup2() failed 0\n"), EXIT_FAILURE;
	}
	if (direc)
	{
		if (direc->i == 1)
		{
			if (dup2(direc->pip[1], STDOUT_FILENO) == -1)
				return error_exit("Function dup2() failed 1\n"), EXIT_FAILURE;
			close(direc->pip[0]);
			close(direc->pip[1]);
		}
		else if (direc->i != 1 && direc->prev_fd != -1)
		{
			if (dup2(direc->prev_fd, STDIN_FILENO) == -1)
				return error_exit("Function dup2() failed 2\n"), EXIT_FAILURE;
			close(direc->prev_fd);
			m = direc->i;
			if (size > m)
			{
				if (dup2(direc->pip[1], STDOUT_FILENO) == -1) // should be in pipe or standard?
					return error_exit("Function dup2() failed 3\n"), EXIT_FAILURE;
				close(direc->pip[0]);
				close(direc->pip[1]);
				m++;
			}
		}
	}
	return EXIT_SUCCESS;
}
int ft_find_bonus(char *s, char *sep)
{
	int i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == s[0])
			return (1);
		i++;
	}
	return (0);
}
int check_cdm(char *s)
{
	if (ft_find_bonus(s, "/.") == 1)
	{
		if (access(s, F_OK) == 0)
			return (1);
		else
			return (0);
	}
	return (1);
}
// 0-> slash
// 1-> space
int ft_praper_cmd(char **cmd, char **path, char **cmds)
{
	int i;
	char *full;

	i = 0;
	if (ft_find_bonus(cmds[0], "/."))
	{
		if (access(cmd[0], F_OK) == 0)
			return (*cmd = cmds[0], 1);
	}
	while (path[i])
	{
		full = ft_strjoin1(path[i], cmds[0], 0);
		if (access(full, F_OK) == 0)
		{
			if (access(full, X_OK) == 0)
			{
				*cmd = full;
				return (1);
			}
		}
		free(full);
		i++;
	}
	return (0);
}
int excute_cmd_p(char *cmd, char **cmds, t_env *env)
{
	int i = 0;
	char *comand;
	char **env_tab;
	if (env == NULL)
		return EXIT_FAILURE;
	env_tab = ft_tab_env(env);
	if (!env_tab || !*env_tab)
		return EXIT_FAILURE;
	char **path = find_path(env_tab);
	if (!path || !*path)
		return EXIT_FAILURE;
	if (!ft_praper_cmd(&comand, path, cmds))
		return EXIT_FAILURE;
	if (!check_cdm(cmds[0]))
		return EXIT_FAILURE;
	if (execve(comand, cmds, env_tab) == -1)
	{
		// free
		// handle exit status for commands
		// check the errno 127 or 126 then exit
		print_error("minishell: command not found\n");
		exit(0);
	}
	return EXIT_SUCCESS;
}
int ft_excute_cmd(t_m_shell *cmd, t_env *env, t_pipe *pip, t_shell_list *command)
{
	int pid;
	int fd;

	pid = fork();
	if (pid == -1)
		return print_error("Function fork() failed\n"), -1;
	if (pid == 0)
	{
		fd = ft_open_file(cmd);
		if (fd < 0)
			return -1;
		ft_redirection(fd, cmd, pip, command->cmd_size);
		if (cmd->type == BUILT_IN)
			ft_manage_cmd_build(env, cmd->args, cmd->args[0]);
		else
		{
			if (excute_cmd_p(cmd->args[0], cmd->args, env))
				return print_error("command not found\n"), -1;
		}
	}
	return (pid);
}
void ft_wait(int pid, int *status)
{
	int wait_id;

	while (1)
	{
		wait_id = waitpid(pid, status, 0);
		if (wait_id == -1 && errno == EINTR)
			continue;
		if (wait_id == -1)
			break;
	}
	// while (wait(NULL) > 0)
	// 	;
}
int ft_open_one_cmd(t_m_shell **cmd)
{
	int fd = -1;

	if (!cmd || !*cmd)
		return print_error("minishell: error: The redirection command is NULL.\n"), -1;
	if ((*cmd)->path_outfile != NULL && (*cmd)->path_outfile->file == NULL)
		return print_error("minishell: error: path_outfile is NULL or has an invalid file.\n"), -1;
	else if ((*cmd)->path_infile != NULL && (*cmd)->path_infile->file == NULL)
		return print_error("minishell: error: path_infile file is NULL.\n"), -1;
	else if ((*cmd)->here_doc != NULL && (*cmd)->here_doc->file == NULL)
		return print_error("minishell: error: here_doc file is NULL.\n"), -1;
	else if ((*cmd)->appand != NULL && (*cmd)->appand->file == NULL)
		return print_error("minishell: error: here_doc file is NULL.\n"), -1;
	else if ((*cmd)->direction == NONE)
		return 0;
	if ((*cmd)->direction == INFILE && (*cmd)->path_infile != NULL && (*cmd)->path_infile->redir == INFILE)
	{
		fd = open((*cmd)->path_infile->file, O_RDONLY);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else if ((*cmd)->direction == OUTFILE && (*cmd)->path_outfile->redir == 111)
	{
		fd = open((*cmd)->path_outfile->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else if ((*cmd)->direction == HERE_DOC && (*cmd)->here_doc != NULL && (*cmd)->here_doc->redir == HERE_DOC)
	{
		fd = open((*cmd)->here_doc->file, O_RDONLY);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else if ((*cmd)->direction == APPAND && (*cmd)->path_outfile != NULL && (*cmd)->path_outfile->redir == APPAND)
	{
		fd = open((*cmd)->path_outfile->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			return perror("fd"), fd;
	}
	else
		return error_exit("Error: Unknown redirection type in ft_open_one_cmd.\n"), -1;
	return fd;
}

int ft_excute_cmd_one(t_m_shell *cmd, t_env *envp)
{
	int pid;
	int fd;

	pid = fork();
	if (pid == -1)
		return print_error("Function fork() failed\n"), -1;
	if (pid == 0)
	{
		fd = ft_open_one_cmd(&cmd);
		if (fd < 0)
			return -1;
		ft_redirection(fd, cmd, NULL, 0);
		if (cmd->type == BUILT_IN)
			ft_manage_cmd_build(envp, cmd->args, cmd->args[0]);
		else
		{
			if (!excute_cmd_p(cmd->args[0], cmd->args, envp))
				return print_error("command not found\n"), -1;
		}
	}
	return pid;
}
void ft_excute(t_shell_list **command, t_env **env)
{
	t_m_shell *current;
	t_pipe *ppp = malloc(sizeof(t_pipe));
	if (!ppp)
		return;

	ppp->i = 1;
	ppp->prev_fd = -1;

	if (!command || !*command || !env)
		return;

	if ((*command)->cmd_size == 1)
	{
		ppp->pid = ft_excute_cmd_one((*command)->head, *env);
		ft_wait(ppp->pid, &(*env)->exit_status);
	}
	else
	{
		current = (*command)->head;
		while (current)
		{
			if ((*command)->cmd_size > ppp->i)
			{
				if (pipe(ppp->pip) == -1)
					return error_exit("Function pipe() failed\n");
			}
			ppp->pid = ft_excute_cmd(current, *env, ppp, *command);
			ft_wait(ppp->pid, &(*env)->exit_status);
			if ((*command)->cmd_size > ppp->i)
			{
				ppp->prev_fd = ppp->pip[0];
				// close(ppp->pip[0]);
				close(ppp->pip[1]);
			}
			if (current->next == NULL)
			{
				ppp->prev_fd = -1;
				close(ppp->pip[1]);
			}
			current = current->next;
			ppp->i++;
		}
	}
}
