/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 20:23:43 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Checks if this simple command (i.e. no pipe) is a builtin
static bool	is_forking_command_list(t_commande *cmd_list, bool exist_pipe)
{
	t_commande	*current;
	char		*cmd_name;

	current = cmd_list;
	while (current != NULL)
	{
		if (current->id == WORD && current->cmds_split)
		{
			cmd_name = current->cmds_split[0];
			if (is_builtin(cmd_name) && (ft_strcmp(cmd_name, "exit") != 0
					|| !exist_pipe))
				return (false);
			else
				return (true);
		}
		current = current->next;
	}
	return (true);
}

static void	exec_partition_non_forking(t_partition *head, int *last_fd,
		t_vars *vars)
{
	int	saved_stdin;
	int	saved_stdout;
	int	pipefd[2];

	saved_stdin = safe_dup(STDIN_FILENO, vars);
	saved_stdout = safe_dup(STDOUT_FILENO, vars);
	if (*last_fd)
	{
		safe_dup2(*last_fd, STDIN_FILENO, vars);
		safe_close(*last_fd, vars);
		*last_fd = 0;
	}
	if (head->next)
	{
		safe_pipe(pipefd, vars);
		safe_dup2(pipefd[1], STDOUT_FILENO, vars);
		safe_close(pipefd[1], vars);
		*last_fd = pipefd[0];
	}
	vars->last_exit_status = exec_command_list(head->cmds, vars, 0);
	vars->last_pid = 0;
	safe_dup2(saved_stdin, STDIN_FILENO, vars);
	safe_dup2(saved_stdout, STDOUT_FILENO, vars);
	safe_close(saved_stdin, vars);
	safe_close(saved_stdout, vars);
}

static void	child_routine(t_partition *head, int *last_fd,
		int pipefd[2], t_vars *vars)
{
	int	exit_status;

	set_default_handling_signals();
	if (*last_fd)
	{
		safe_dup2(*last_fd, STDIN_FILENO, vars);
		safe_close(*last_fd, vars);
	}
	if (head->next)
		safe_dup2(pipefd[1], STDOUT_FILENO, vars);
	safe_close(pipefd[0], vars);
	safe_close(pipefd[1], vars);
	exit_status = exec_command_list(head->cmds, vars, 1);
	free_vars(vars);
	exit(exit_status);
}

static void	exec_partition_forking(t_partition *head, int *last_fd,
		t_vars *vars)
{
	int		pipefd[2];
	pid_t	pid;

	safe_pipe(pipefd, vars);
	pid = fork();
	if (pid < 0)
		display_error_and_exit("fork", vars);
	else if (pid == 0)
		child_routine(head, last_fd, pipefd, vars);
	safe_close(pipefd[1], vars);
	if (*last_fd)
		safe_close(*last_fd, vars);
	*last_fd = pipefd[0];
	vars->last_pid = pid;
	vars->exist_children = true;
}

void	exec_partition_list(t_partition *head, t_vars *vars)
{
	char	*status_str;
	int		last_fd;

	if (handle_all_heredocs(head, vars) == -1)
		return ;
	if (head && head->next)
		vars->exist_pipe = true;
	last_fd = 0;
	while (head)
	{
		if (is_forking_command_list(head->cmds, vars->exist_pipe) == false)
			exec_partition_non_forking(head, &last_fd, vars);
		else
			exec_partition_forking(head, &last_fd, vars);
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
