/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:55:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/19 00:49:05 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

// Prints warning if EOF before delimiter is found
static void	end_of_file_heredoc(t_commande *cmd)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(history_length, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(cmd->cmds_split[0], STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static void	realloc_and_append(char *line, size_t *total_length,
		char **heredoc_data, t_vars *vars)
{
	size_t	new_length;
	char	*new_heredoc_data;

	new_length = *total_length + ft_strlen(line) + 1;
	new_heredoc_data = realloc(*heredoc_data, new_length + 1);
	if (new_heredoc_data == NULL)
	{
		free(line);
		free(*heredoc_data);
		display_error_and_exit("Memory allocation failed", vars);
	}
	*heredoc_data = new_heredoc_data;
	ft_strcpy(*heredoc_data + *total_length, line);
	ft_strcat(*heredoc_data, "\n");
	*total_length = new_length;
	free(line);
}

static int	get_data(t_commande *cmd, size_t *total_length, char **heredoc_data,
		t_vars *vars)
{
	char	*line;

	line = readline("> ");
	if (g_signal_received == SIGINT
		&& printf("signal recu  dans readline, on est dans le if\n")
		&& signal_readline_heredoc(vars) == true)
	{
		if (*heredoc_data != NULL)
			free(*heredoc_data);
		printf("get data return -1\n"); // DELETE
		return (-1);
	}
	if (line == NULL)
		return (end_of_file_heredoc(cmd), 1);
	if (ft_strcmp(line, cmd->cmds_split[0]) == 0)
		return (free(line), 1);
	realloc_and_append(line, total_length, heredoc_data, vars);
	return (0);
}

// Read lines until the delimiter is found
// At the end, expand the variables
static int	handle_this_heredoc(t_commande *cmd, t_vars *vars)
{
	size_t	total_length;
	char	*heredoc_data;
	int		ret;
	char	**variables;

	printf("handling a heredoc\n"); // DELETE
	total_length = 0;
	heredoc_data = NULL;
	while (true)
	{
		ret = get_data(cmd, &total_length, &heredoc_data, vars);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			break ;
	}
	if (heredoc_data != NULL)
		heredoc_data[total_length] = '\0';
	cmd->heredoc = heredoc_data;
	variables = stock_variables(cmd->heredoc);
	cmd->heredoc = illuminate_variables(cmd->heredoc, vars->envp_list,
			variables);
	ft_free_split(variables);
	return (0);
}

int	handle_all_heredocs(t_partition *head, t_vars *vars)
{
	t_partition	*current_partition;
	t_commande	*current_command;

	current_partition = head;
	while (current_partition != NULL)
	{
		current_command = current_partition->cmds;
		while (current_command != NULL)
		{
			if (current_command->id == LD_DIR)
			{
				if (handle_this_heredoc(current_command, vars) == -1)
					return (-1);
			}
			current_command = current_command->next;
		}
		current_partition = current_partition->next;
	}
	return (0);
}
