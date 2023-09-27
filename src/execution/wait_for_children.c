/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:56:31 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/27 20:27:32 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static bool	case_terminated_by_signal(int status, pid_t wait_pid, t_vars *vars)
{
	int		signal_number;

	signal_number = WTERMSIG(status);
	if (signal_number == SIGINT)
		return (true);
	if (wait_pid == vars->last_pid)
	{
		vars->last_exit_status = 128 + signal_number;
		if (signal_number == SIGINT)
			return (true);
		if (__WCOREDUMP(status))
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else
			ft_putstr_fd("Terminated\n", STDERR_FILENO);
	}
	return (false);
}

void	wait_for_children_2(pid_t wait_pid, bool newline, t_vars *vars)
{
	if (wait_pid < 0 && errno != ECHILD)
		display_error_and_exit("wait", vars);
	if (newline == true)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	wait_for_children(t_vars *vars)
{
	int		status;
	pid_t	wait_pid;
	bool	newline;

	newline = false;
	wait_pid = wait(&status);
	while (wait_pid > 0)
	{
		if (WIFEXITED(status) && wait_pid > 0 && wait_pid == vars->last_pid)
			vars->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (newline == false)
				newline = case_terminated_by_signal(status, wait_pid, vars);
		}
		wait_pid = wait(&status);
		if (wait_pid > 0)
			newline = false;
	}
	if (wait_pid < 0 && errno == EINTR)
	{
		my_putenv("?", "130", vars);
		return ;
	}
	wait_for_children_2(wait_pid, newline, vars);
}
