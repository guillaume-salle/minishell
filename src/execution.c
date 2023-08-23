/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/23 16:32:18 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_routine(int pipe_fd[2], t_commande *cmd, t_vars *vars)
{
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec_command(cmd, vars);
	exit(EXIT_SUCCESS);
}

void	parent_routine(int pipe_fd[2], t_commande *cmd)
{
	wait(NULL);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	pipe_and_fork(t_commande *cmd, t_vars *vars)
{
	int	pipe_fd[2];
	int	pid;

	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("minishell: pipe error");
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid == 0)
	{
		child_routine(pipe_fd, cmd, vars);
	}
	else if (pid > 0)
	{
		parent_routine(pipe_fd, cmd);
	}
	else
	{
		perror("minishell: fork error");
		exit(EXIT_FAILURE);
	}
}

void	exec_partition(t_partition *part, t_vars *vars)
{
	t_commande	*cmd;

	cmd = part->cmds;
	while (cmd != NULL)
	{
		pipe_and_fork(cmd, vars);
		cmd = cmd->next;
	}
}
