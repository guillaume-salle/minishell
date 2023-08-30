/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:34:24 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/30 13:34:50 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_r_rd(t_commande *cmd, t_vars *vars)
{
	int	fd;
	int	flags;

	if (cmd->id == R_DIR)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (cmd->id == RD_DIR)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return ;
	fd = open(cmd->cmds_split[1], flags, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	my_execvp(cmd->cmds_split, vars);
}

void	exec_l_dir(t_commande *cmd, t_vars *vars)
{
	int	fd;

	fd = open(cmd->cmds_split[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		exit(1);
	}
	close(fd);
	my_execvp(cmd->cmds_split, vars);
}
