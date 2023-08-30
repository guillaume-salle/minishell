/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:47:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/30 11:56:00 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exit_status(int exit_status, t_vars *vars)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(exit_status);
	my_putenv("?", exit_status_str, vars);
	free(exit_status_str);
}

void	my_execvp(char *argv[], t_vars *vars)
{
	int		exit_status;
	int		argc;
	char	*cmd_name;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	cmd_name = argv[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		exit_status = echo(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		exit_status = cd(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		exit_status = pwd(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "export") == 0)
		exit_status = export(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		exit_status = unset(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "env") == 0)
		exit_status = env(argc, argv, vars);
	else
		exit_status = execvp(argv[0], argv);
	update_exit_status(exit_status, vars);
}

static void	exec_r_rd(t_commande *cmd, t_vars *vars)
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

static void	exec_l_dir(t_commande *cmd, t_vars *vars)
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
