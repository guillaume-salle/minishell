/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partition_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/27 20:50:04 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Checks if this simple command (i.e. no pipe) is a builtin.
bool	is_builtin_command(t_commande *cmd_list)
{
	t_commande	*current;
	char		*cmd_name;

	current = cmd_list;
	while (current != NULL)
	{
		if (current->id == WORD && current->cmds_split != NULL)
		{
			cmd_name = current->cmds_split[0];
			if (is_builtin(cmd_name))
				return (true);
			else
				return (false);
		}
		current = current->next;
	}
	return (false);
}

static void	exec_partition_no_pipe(t_partition *head, t_vars *vars)
{
	pid_t	pid;
	int		exit_status;

	if (is_builtin_command(head->cmds) == true)
	{
		vars->last_exit_status = exec_command_list(head->cmds, vars, 0);
		return ;
	}
	pid = fork();
	if (pid < 0)
		display_error_and_exit("fork", vars);
	else if (pid == 0)
	{
		setup_signal_handlers_default(vars);
		exit_status = exec_command_list(head->cmds, vars, 1);
		free_vars(vars);
		exit(exit_status);
	}
	vars->last_pid = pid;
	vars->exist_children = true;
}

void	exec_partition_list(t_partition *head, t_vars *vars)
{
	char	*status_str;

	if (head == NULL)
		return ;
	if (head->next != NULL)
		vars->exist_pipe = true;
	if (handle_all_heredocs(head, vars) == -1)
		return ;
	setup_signal_handlers_parent(vars);
	if (head->next != NULL)
		exec_partition_with_pipe(head, vars);
	else
		exec_partition_no_pipe(head, vars);
	if (vars->exist_children)
		wait_for_children(vars);
	status_str = ft_itoa(vars->last_exit_status);
	if (status_str == NULL)
		display_error_and_exit("malloc", vars);
	my_putenv("?", status_str, vars);
	free(status_str);
}
