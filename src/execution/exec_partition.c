/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/16 00:59:04 by gusalle          ###   ########.fr       */
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

// Checks if this simple command (i.e. no pipe) is a builtin
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

static int	wait_norm(int *wait_pid, int *status)
{
	*wait_pid = wait(status);
	return (*wait_pid);
}

static void	wait_for_children(t_vars *vars)
{
	int		status;
	pid_t	wait_pid;

	while (wait_norm(&wait_pid, &status) > 0) 
	{
		if (WIFEXITED(status) && wait_pid > 0 && wait_pid == vars->last_pid)
			vars->last_exit_status= WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 3)
			{
				if (g_sigint == 0)
				{
					ft_putstr_fd("Quit (core dumped)\n", 2);
					g_sigint = 1;
				}
			}
			else if (__WCOREDUMP(status))
			{
				ft_putstr_fd("minishell: process ", 2);
				ft_putnbr_fd(wait_pid, 2);
				ft_putstr_fd(" terminated by a signal (", 2);
				ft_putnbr_fd(WTERMSIG(status), 2);
				ft_putstr_fd(")\n", 2);
			}
			if (vars->last_pid != 0 && wait_pid == vars->last_pid)
				vars->last_exit_status = 128 + WTERMSIG(status);
		}
	}
	if (wait_pid < 0 && errno != ECHILD)
		display_error_and_exit("wait", vars);
}

void	exec_partition_list(t_partition *head, t_vars *vars)
{
	int		pipefd[2];
	pid_t	pid;
	int		last_fd;
	bool	exist_children;


//	Handle heredocs first
	handle_heredocs(head, vars);
	last_fd = 0;
	exist_children = false;
	while (head)
	{
		if (is_builtin_command_list(head->cmds))
		{
			vars->last_exit_status = exec_command_list(head->cmds, vars, 0);
			vars->last_pid = 0;
			head = head->next;
			continue;
		}
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
		close(pipefd[1]);
		if (last_fd)
			close(last_fd);
		last_fd = pipefd[0];
		vars->last_pid = pid;
		exist_children = true;
		head = head->next;
	}
	if (exist_children)
		wait_for_children(vars);
	char *status_str = ft_itoa(vars->last_exit_status);
	if (status_str == NULL)
		display_error_and_exit("Memory allocation failed", vars);
	my_putenv("?", status_str, vars);
	free(status_str);
}
