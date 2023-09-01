/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/01 20:14:57 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_routine(int pipe_fd[2], t_commande *cmd, t_vars *vars)
{
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec_single_command(cmd, vars);
	exit(EXIT_SUCCESS);
}

static void	parent_routine(int pipe_fd[2], t_commande *cmd)
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
		child_routine(pipe_fd, cmd, vars);
	else if (pid > 0)
		parent_routine(pipe_fd, cmd);
	else
	{
		perror("minishell: fork error");
		exit(EXIT_FAILURE);
	}
}

void	exec_single_command(t_commande *cmd, t_vars *vars)
{
	if (!cmd)
		return ;
	if (cmd->id == WORD)
		my_execvp(cmd->cmds_split, vars);
	else if (cmd->id == R_DIR || cmd->id == RD_DIR)
		exec_r_rd(cmd, vars);
	else if (cmd->id == L_DIR)
		exec_l_dir(cmd, vars);
	else if (cmd->id == LD_DIR)
		exec_ld_dir(cmd, vars);
}
