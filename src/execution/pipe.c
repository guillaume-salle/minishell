/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:10:16 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/24 14:46:12 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// exit_status in case execve fails and returns
static void	exec_first_partition_pipe(t_partition *head, int first_pipe[2],
		t_vars *vars)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid < 0)
		display_error_and_exit("fork", vars);
	else if (pid == 0)
	{
		close(vars->saved_stdin);
		close(first_pipe[0]);
		if (dup2(first_pipe[1], STDOUT_FILENO) == -1)
		{
			close(first_pipe[1]);
			display_error_and_exit("dup2", vars);
		}
		safe_close(first_pipe[1], vars);
		setup_signal_handlers_default(vars);
		exit_status = exec_command_list(head->cmds, vars, 1);
		free_vars(vars);
		exit(exit_status);
	}
	vars->last_pid = pid;
	vars->exist_children = true;
}

// Should have same checks on dup2, but norm
static void	exec_middle_partition_pipe(t_partition *head, int first_pipe[2],
		int second_pipe[2], t_vars *vars)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid < 0)
		display_error_and_exit("fork", vars);
	else if (pid == 0)
	{
		close(vars->saved_stdin);
		close(second_pipe[0]);
		dup2(first_pipe[0], STDIN_FILENO);
		close(first_pipe[0]);
		dup2(second_pipe[1], STDOUT_FILENO);
		safe_close(second_pipe[1], vars);
		setup_signal_handlers_default(vars);
		exit_status = exec_command_list(head->cmds, vars, 1);
		free_vars(vars);
		exit(exit_status);
	}
	vars->last_pid = pid;
	vars->exist_children = true;
}

static void	exec_last_partition_pipe(t_partition *head, int first_pipe[2],
		t_vars *vars)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid < 0)
		display_error_and_exit("fork", vars);
	else if (pid == 0)
	{
		close(vars->saved_stdin);
		if (dup2(first_pipe[0], STDIN_FILENO) == -1)
		{
			close(first_pipe[0]);
			display_error_and_exit("dup2", vars);
		}
		safe_close(first_pipe[0], vars);
		setup_signal_handlers_default(vars);
		exit_status = exec_command_list(head->cmds, vars, 1);
		free_vars(vars);
		exit(exit_status);
	}
	vars->last_pid = pid;
	vars->exist_children = true;
}

void	exec_partition_with_pipe(t_partition *head, t_vars *vars)
{
	int	first_pipe[2];
	int	second_pipe[2];

	safe_pipe(first_pipe, vars);
	exec_first_partition_pipe(head, first_pipe, vars);
	safe_close(first_pipe[1], vars);
	head = head->next;
	while (head != NULL && head->next != NULL)
	{
		safe_pipe(second_pipe, vars);
		exec_middle_partition_pipe(head, first_pipe, second_pipe, vars);
		safe_close(first_pipe[0], vars);
		safe_close(second_pipe[1], vars);
		first_pipe[0] = second_pipe[0];
		head = head->next;
	}
	exec_last_partition_pipe(head, first_pipe, vars);
	safe_close(first_pipe[0], vars);
}
