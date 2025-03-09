#include "minishell.h"

t_m_shell *create_node(char *cmd)
{
	t_m_shell *new_node = malloc(sizeof(t_m_shell));
	if (!new_node)
		return NULL;

	new_node->cmd = strdup(cmd);
	new_node->args = ft_split(cmd, ' ');
	new_node->type = COMMAND;
	new_node->direction = NONE;
	new_node->path_infile = NULL;
	new_node->path_outfile = NULL;
	new_node->here_doc = NULL;
	new_node->appand = NULL;
	new_node->next = NULL;

	return new_node;
}

// Function to add redirection
void add_redirection(t_m_shell *node, t_enum type, char *file)
{
	t_redirction *redir = malloc(sizeof(t_redirction));
	if (!redir)
		return;

	redir->redir = type;
	redir->file = strdup(file);

	if (type == INFILE)
		node->path_infile = redir;
	else if (type == OUTFILE)
		node->path_outfile = redir;
}

// Fixed add_back function (uses t_shell_list)
void add_back(t_shell_list *list, t_m_shell *new_node)
{
	if (!list || !new_node)
	{
		fprintf(stderr, "Error: NULL pointer in add_back()\n");
		return;
	}

	if (list->head == NULL) // If the list is empty, set head to the new node
	{
		list->head = new_node;
	}
	else
	{
		t_m_shell *temp = list->head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}

	list->cmd_size++; // Properly increment size at the list level
}

// Function to free all nodes and redirections
void free_list(t_m_shell *head)
{
	t_m_shell *temp;
	while (head)
	{
		temp = head;
		head = head->next;

		free(temp->cmd);
		if (temp->path_infile)
		{
			free(temp->path_infile->file);
			free(temp->path_infile);
		}
		if (temp->path_outfile)
		{
			free(temp->path_outfile->file);
			free(temp->path_outfile);
		}
		if (temp->here_doc)
		{
			free(temp->here_doc->file);
			free(temp->here_doc);
		}
		if (temp->appand)
		{
			free(temp->appand->file);
			free(temp->appand);
		}
		free(temp);
	}
}

// Fix init_data to properly allocate memory
void init_data(t_main **mm, t_shell_list **shell_list, t_env **env_list, char **envp)
{
	*mm = malloc(sizeof(t_main));
	if (!*mm)
	{
		fprintf(stderr, "Memory allocation failed for mm\n");
		exit(EXIT_FAILURE);
	}

	*shell_list = malloc(sizeof(t_shell_list));
	if (!*shell_list)
	{
		fprintf(stderr, "Memory allocation failed for shell_list\n");
		exit(EXIT_FAILURE);
	}
	(*shell_list)->head = NULL;
	(*shell_list)->cmd_size = 0;
	if (envp)
	{
		*env_list = ft_env_handle(envp);
		if (!*env_list)
		{
			fprintf(stderr, "Failed to initialize environment list\n");
			exit(EXIT_FAILURE);
		}
	}
	(*env_list)->env = malloc(sizeof(t_main));
	if (!(*env_list)->env)
	{
		fprintf(stderr, "Memory allocation failed for env_list->env\n");
		exit(EXIT_FAILURE);
	}
}

int main(int ac, char **av, char **envp)
{
    t_main *mm = NULL;
    t_shell_list *shell_list = NULL;
    t_env *env_list = NULL;
    char *input;
    
    // Initialize data once at the start
    init_data(&mm, &shell_list, &env_list, envp);
    if (!env_list)
    {
        fprintf(stderr, "Failed to initialize environment\n");
        return 1;
    }

    mm->ac = ac;
    mm->av = av;
    mm->envp = envp;
    env_list->env->ac = ac;
    env_list->env->av = av;
    env_list->env->envp = envp;

    while (1)
    {
        // Reset shell state variables
        env_list->exit_status = 0;
        shell_list->cmd_size = 0;

        input = readline("\033[1;32mminishell\033[0m\033[1;34m[]~> \033[0m");
        if (!input)
        {
            printf("\nExiting shell...\n");
            break;
        }

        if (ft_strlen(input) > 0)
            add_history(input);

        // Tokenize input into commands using '|'
        char **res = ft_split(input, '|');
        if (!res)
        {
            free(input);
            continue;
        }

        // Parse commands and add them to shell_list
        for (int i = 0; res[i]; i++)
        {
            t_m_shell *new_node = create_node(res[i]);
            if (!new_node)
            {
                fprintf(stderr, "Error: Failed to create command node\n");
                break;
            }
            add_back(shell_list, new_node);
        }

        ft_excute(&shell_list, &env_list);

        // Free tokenized input array
        // for (int i = 0; res[i]; i++)
        //     free(res[i]);
        free(res);
        free(input);

        // Free the command list after execution to avoid memory leaks
        free_list(shell_list->head);
        shell_list->head = NULL; // Prevent dangling pointer
        shell_list->cmd_size = 0;
    }

    // Free memory before exiting
    free(shell_list);
    free(env_list->env);
    free(env_list);
    free(mm);

    return 0;
}
