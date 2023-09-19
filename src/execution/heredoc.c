/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:55:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/19 18:36:06 by gusalle          ###   ########.fr       */
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

static void	realloc_and_append(char *saved_line, size_t *total_length,
		char **heredoc_data, t_vars *vars)
{
	size_t	new_length;
	char	*new_heredoc_data;

	new_length = *total_length + ft_strlen(vars->line) + 1;
	new_heredoc_data = realloc(*heredoc_data, new_length + 1);
	new_heredoc_data = malloc(new_length + 1);
	if (new_heredoc_data == NULL)
	{
		free(saved_line);
		free(*heredoc_data);
		display_error_and_exit("Memory allocation failed", vars);
	}
	ft_strcpy(new_heredoc_data, *heredoc_data);
	ft_strcat(new_heredoc_data, saved_line);
	ft_strcat(new_heredoc_data, "\n");
	*heredoc_data = new_heredoc_data;
	*total_length = new_length;
	free(*heredoc_data);
	free(saved_line);
}

static int	get_data(t_commande *cmd, size_t *total_length, char **heredoc_data,
		t_vars *vars)
{
	char	*saved_line;
	bool	stop;

	stop = false;
	saved_line = vars->line;
	vars->line = readline("> ");
	if (g_signal_received != 0)
	{
		stop = signal_in_readline(vars);
		if (stop == true)
		{
			if (saved_line != NULL)
				free(saved_line);
			return (-1);
		}
	}
	if (vars->line == NULL)
		return (end_of_file_heredoc(cmd), 1);
	if (ft_strcmp(vars->line, cmd->cmds_split[0]) == 0)
		return (free(vars->line), 1);
	realloc_and_append(saved_line, total_length, heredoc_data, vars);
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
