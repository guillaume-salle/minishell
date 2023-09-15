/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:14:10 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/16 00:33:09 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int	exec_builtin(char *argv[], t_vars *vars)
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
//	else if (ft_strcmp(cmd_name, "exit") == 0)
//		exit_status = exit(argc, argv, vars);
//	if (ft_strcmp(cmd_name, "exit") == 0)
//		free_vars(vars);   ??
	return (exit_status);
}

int	exec_word(t_commande *cmd, t_vars *vars, bool forking)
{
	char	*cmd_name;
	char	**argv;
	int		exit_status;
	char	*pathname;

	argv = cmd->cmds_split;
	if (argv != NULL)
		cmd_name = argv[0];
	else
		cmd_name = cmd->cmd;
	if (is_builtin(cmd_name))
	{
		exit_status = exec_builtin(argv, vars);
		return (exit_status);
	}
	else
	{
		update_envp(vars);
		pathname = find_command_path(cmd_name, vars);
		if (pathname == NULL)
		{
			ft_putstr_fd(cmd_name, 2);
			ft_putstr_fd(": command not found\n", 2);
			if (forking)
			{
				free_vars(vars);
			//	close_fd(vars); ??
			}
			exit(127);
		}
		execve(pathname, argv, vars->envp);
		free(pathname);
		display_error_and_exit("execve", vars);
		return (-1);
	}
}
