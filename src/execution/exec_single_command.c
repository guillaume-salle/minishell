/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:47:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/30 15:45:21 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_non_builtin(char *argv[], t_vars *vars)
{
	char	*pathname;

	update_envp(vars);
	pathname = find_command_path(argv[0], vars);
	execve(pathname, argv, vars->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

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
	exit_status = 0;
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
		exec_non_builtin(argv, vars);
	update_exit_status(exit_status, vars);
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
