/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partition_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/21 18:42:32 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Checks if this simple command (i.e. no pipe) is a builtin.
// fork for exit if there is a pipe
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

// Don't fork for builtin
static void	fork_before_exec(t_partition *head, int saved_stdin,
		int saved_stdout, t_vars *vars)
{
	int		exit_status;
	pid_t	pid;

	if (vars->forking)
	{
		pid = fork();
		if (pid < 0)
			display_error_and_exit("fork", vars);
		else if (pid == 0)
		{
			set_default_handling_signals();
			safe_close(saved_stdin, vars);
			safe_close(saved_stdout, vars);
			exit_status = exec_command_list(head->cmds, vars, 1);
			free_vars(vars);
			exit(exit_status);
		}
		vars->last_pid = pid;
		vars->exist_children = true;
	}
	else
	{
		vars->last_exit_status = exec_command_list(head->cmds, vars, 0);
		vars->last_pid = 0;
	}
}

static void	exec_one_partition(t_partition *head, int *last_fd, t_vars *vars)
{
	int	saved_stdin;
	int	saved_stdout;
	int	pipefd[2];

	saved_stdin = safe_dup(STDIN_FILENO, vars);
	saved_stdout = safe_dup(STDOUT_FILENO, vars);
	if (*last_fd != 0)
	{
		safe_dup2(*last_fd, STDIN_FILENO, vars);
		safe_close(*last_fd, vars);
		*last_fd = 0;
	}
	if (head->next != NULL)
	{
		safe_pipe(pipefd, vars);
		safe_dup2(pipefd[1], STDOUT_FILENO, vars);
		safe_close(pipefd[1], vars);
		*last_fd = pipefd[0];
	}
	fork_before_exec(head, saved_stdin, saved_stdout, vars);
	safe_dup2(saved_stdin, STDIN_FILENO, vars);
	safe_dup2(saved_stdout, STDOUT_FILENO, vars);
	safe_close(saved_stdin, vars);
	safe_close(saved_stdout, vars);
}

void	exec_partition_list(t_partition *head, t_vars *vars)
{
	char	*status_str;
	int		last_fd;

	if (handle_all_heredocs(head, vars) == -1)
		return ;
	if ((head != NULL && head->next != NULL) || (head->next == NULL
			&& is_builtin_command(head->cmds) == false))
		vars->forking = true;
	else
		vars->forking = false;
	last_fd = 0;
	while (head)
	{
		exec_one_partition(head, &last_fd, vars);
		head = head->next;
	}
	if (vars->exist_children)
		wait_for_children(vars);
	status_str = ft_itoa(vars->last_exit_status);
	if (status_str == NULL)
		display_error_and_exit("Memory allocation failed", vars);
	my_putenv("?", status_str, vars);
	free(status_str);
}
