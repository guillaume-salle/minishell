/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:56:31 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 13:03:11 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	case_terminated_by_signal(int status, pid_t wait_pid, t_vars *vars)
{
	if (WTERMSIG(status) == 3)
	{
		if (g_sigint == 0)
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_sigint = 1;
		}
	}
	else if (__WCOREDUMP(status))
	{
		ft_putstr_fd("minishell: process ", STDERR_FILENO);
		ft_putnbr_fd(wait_pid, STDERR_FILENO);
		ft_putstr_fd(" terminated by a signal (", STDERR_FILENO);
		ft_putnbr_fd(WTERMSIG(status), STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
	}
	if (vars->last_pid != 0 && wait_pid == vars->last_pid)
		vars->last_exit_status = 128 + WTERMSIG(status);
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
	if (wait_pid < 0 && errno != ECHILD)
		display_error_and_exit("wait", vars);
}
