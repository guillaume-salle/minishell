/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:02:34 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 12:18:21 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int	check_empty_redirection(t_commande *cmd)
{
	if ((cmd->id == R_DIR || cmd->id == RD_DIR || cmd->id == L_DIR)
		&& ft_strcmp(cmd->cmd, "") == 0)
	{
		if (ft_strcmp(cmd->without_exp, "") == 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->without_exp, STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
			return (-1);
		}
		else
		{
			ft_putstr_fd("minishell : : No such file or directory\n",
				STDERR_FILENO);
			return (-1);
		}
	}
	return (0);
}

static int	case_r_rd_dir(t_commande *cmd, t_vars *vars)
{
	int	fd;

	if (cmd->id == R_DIR)
		fd = open(cmd->cmds_split[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->id == RD_DIR)
		fd = open(cmd->cmds_split[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->cmds_split[0]);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		display_error_and_exit("dup2", vars);
	close(fd);
	return (0);
}

static int	case_l_dir(t_commande *cmd, t_vars *vars)
{
	int	fd;

	fd = open(cmd->cmds_split[0], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->cmds_split[0]);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		display_error_and_exit("dup2", vars);
	close(fd);
	return (0);
}

static int	case_ld_dir(t_commande *cmd, t_vars *vars)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		display_error_and_exit("pipe", vars);
	write(pipefd[1], cmd->heredoc, ft_strlen(cmd->heredoc));
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		display_error_and_exit("dup2", vars);
	close(pipefd[0]);
	return (0);
}

int	handle_redirection(t_commande *cmd, t_vars *vars)
{
	if (check_empty_redirection(cmd) == -1)
		return (-1);
	if (cmd->id == R_DIR || cmd->id == RD_DIR)
		return (case_r_rd_dir(cmd, vars));
	else if (cmd->id == L_DIR)
		return (case_l_dir(cmd, vars));
	else if (cmd->id == LD_DIR)
		return (case_ld_dir(cmd, vars));
	else
	{
		display_error_and_exit("Invalid redirection type", vars);
		return (-1);
	}
}
