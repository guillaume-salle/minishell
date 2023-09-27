/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:55:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/27 19:41:51 by gusalle          ###   ########.fr       */
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

static void	realloc_and_append(t_commande *cmd, char *line, t_vars *vars)
{
	size_t	new_length;
	char	*temp_heredoc;

	new_length = ft_strlen(cmd->heredoc) + ft_strlen(line) + 1;
	temp_heredoc = malloc(new_length + 1);
	if (temp_heredoc == NULL)
		display_error_and_exit("Memory allocation failed", vars);
	ft_strcpy(temp_heredoc, cmd->heredoc);
	ft_strcat(temp_heredoc, line);
	ft_strcat(temp_heredoc, "\n");
	free(cmd->heredoc);
	free(vars->line);
	vars->line = NULL;
	cmd->heredoc = temp_heredoc;
}

static int	get_heredoc_data(t_commande *cmd, t_vars *vars)
{
	free(vars->line);
	vars->line = NULL;
	vars->line = readline("> ");
	if (g_signal_received != 0)
	{
		if (stop_signal_heredoc(vars) == true)
			return (-1);
	}
	if (vars->line == NULL)
		return (end_of_file_heredoc(cmd), 1);
	if (ft_strcmp(vars->line, cmd->cmds_split[0]) == 0)
	{
		free(vars->line);
		vars->line = NULL;
		return (1);
	}
	realloc_and_append(cmd, vars->line, vars);
	return (0);
}

// Read lines until the delimiter is found
// At the end, expand the variables
static int	handle_this_heredoc(t_commande *cmd, t_vars *vars)
{
	int		ret;
	char	**variables;

	cmd->heredoc = malloc(1);
	if (cmd->heredoc == NULL)
		display_error_and_exit("malloc", vars);
	cmd->heredoc[0] = '\0';
	while (true)
	{
		ret = get_heredoc_data(cmd, vars);
		if (ret == -1)
		{
			free_and_nullify(&cmd->heredoc);
			return (-1);
		}
		else if (ret == 1)
			break ;
	}
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

	setup_signal_handlers_heredoc(vars);
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
