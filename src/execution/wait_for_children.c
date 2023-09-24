/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:56:31 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/24 16:15:31 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	case_terminated_by_signal(int status, pid_t wait_pid, t_vars *vars)
{
	int	signal_number;

	signal_number = WTERMSIG(status);
	if (wait_pid == vars->last_pid)
	{
		vars->last_exit_status = 128 + signal_number;
		if (signal_number == SIGINT)
			return ;
		if (__WCOREDUMP(status))
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		else
			ft_putstr_fd("Terminated\n", STDERR_FILENO);
	}
}

void	wait_for_children(t_vars *vars)
{
	int		status;
	pid_t	wait_pid;

	wait_pid = wait(&status);
	while (wait_pid > 0)
	{
		if (WIFEXITED(status) && wait_pid > 0 && wait_pid == vars->last_pid)
			vars->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			case_terminated_by_signal(status, wait_pid, vars);
		wait_pid = wait(&status);
	}
	if (wait_pid < 0 && errno == EINTR)
	{
		my_putenv("?", "130", vars);
		return ;
	}
	if (wait_pid < 0 && errno != ECHILD)
		display_error_and_exit("wait", vars);
}
