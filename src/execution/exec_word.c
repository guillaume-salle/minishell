/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:14:10 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/03 20:38:22 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	return (false);
}

static void	exec_non_builtin(char *argv[], t_vars *vars)
{
	char	*pathname;

	update_envp(vars);
	pathname = find_command_path(argv[0], vars);
	execve(pathname, argv, vars->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	update_exit_status(int exit_status, t_vars *vars)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(exit_status);
	my_putenv("?", exit_status_str, vars);
	free(exit_status_str);
}

// exit_status??
static void	exec_builtin(char *argv[], t_vars *vars)
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
	update_exit_status(exit_status, vars);
}

void	exec_word(t_commande *cmd, t_vars *vars)
{
	char	*cmd_name;

	cmd_name = cmd->cmds_split[0];
	if (is_builtin(cmd_name))
		exec_builtin(cmd->cmds_split, vars);
	else
		exec_non_builtin(cmd->cmds_split, vars);
}
