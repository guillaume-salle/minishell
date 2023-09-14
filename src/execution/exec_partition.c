/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/14 20:55:12 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

static bool	is_builtin_command_list(t_commande *cmd_list)
{
	t_commande	*current;
   
	current = cmd_list;
	while (current != NULL)
	{
		if (current->id == WORD) 
		{
			if (current->cmds_split)
				return (is_builtin(current->cmds_split[0]));
			else
				return (false);
		}
		current = current->next;
	}
	return (false);
}

static int	wait_for_children(t_vars *vars)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
		pid = wait(&status);
	if (pid < 0 && errno != ECHILD)
			display_error_and_exit("wait", vars);
	return (status);
}

void	exec_partition_list(t_partition *head, t_vars *vars)
{
	int		pipefd[2];
	pid_t	pid;
	int		last_fd;
	int		last_exit_status;
	bool	is_last_command_builtin;


//	Handle heredocs first
	handle_heredocs(head, vars);
	last_fd = 0;
	last_exit_status = 0;
	is_last_command_builtin = false;
	while (head)
	{
		if (is_builtin_command_list(head->cmds))
		{
			last_exit_status = exec_command_list(head->cmds, vars, 0);
			is_last_command_builtin = true;
			head = head->next;
			continue;
		}
		is_last_command_builtin = false;
		if (pipe(pipefd) == -1)
			display_error_and_exit("pipe", vars);
		pid = fork();
		if (pid < 0)
			display_error_and_exit("fork", vars);
		else if (pid == 0)
		{
			if (last_fd)
			{
				dup2(last_fd, STDIN_FILENO);
				close(last_fd);
			}
			if (head->next)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			exec_command_list(head->cmds, vars, 1);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipefd[1]);
			if (last_fd)
				close(last_fd);
			last_fd = pipefd[0];
		}
		head = head->next;
	}
	if (!is_last_command_builtin)
		last_exit_status = wait_for_children(vars);
	else
		wait_for_children(vars);
	char *status_str = ft_itoa(last_exit_status);
	if (status_str == NULL)
		display_error_and_exit("Memory allocation failed", vars);
	my_putenv("?", status_str, vars);
	free(status_str);
}
