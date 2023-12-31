/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:44:41 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/28 10:43:51 by gusalle          ###   ########.fr       */
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
	else if (ft_strcmp(cmd_name, "exit") == 0)
		exit_status = my_exit(argc, argv, vars);
	return (exit_status);
}

static void	exec_non_builtin(char *cmd_name, char **argv, t_vars *vars)
{
	char	*pathname;

	update_envp(vars);
	pathname = find_command_path(cmd_name, vars);
	if (pathname == NULL)
	{
		if (vars->is_a_tty == false)
		{
			ft_putstr_fd("minishell: line ", STDERR_FILENO);
			ft_putnbr_fd(vars->nb_line, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_vars(vars);
		exit(127);
	}
	execve(pathname, argv, vars->envp);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(pathname);
	free(pathname);
	free_vars(vars);
	exit(127);
}

// always forking in this function is called
static bool	exec_empty_cmd(const char *cmd_name, t_vars *vars)
{
	if (ft_strcmp(cmd_name, ":") == 0
		|| ft_strcmp(cmd_name, "!") == 0
		|| (ft_strcmp(cmd_name, "") == 0 && ft_strchr(vars->line, '\'') == NULL
			&& ft_strchr(vars->line, '\"') == NULL))
	{
		free_vars(vars);
		exit(EXIT_SUCCESS);
		return (true);
	}
	return (false);
}

int	exec_word(t_commande *cmd, t_vars *vars, bool forking)
{
	char	*cmd_name;
	int		exit_status;
	char	**argv;

	argv = cmd->cmds_split;
	if (argv != NULL && argv[0] != NULL)
		cmd_name = argv[0];
	else
		cmd_name = cmd->cmd;
	if (is_builtin_command(cmd) == true && forking == true)
	{
		exit_status = exec_builtin(argv, vars);
		free_vars(vars);
		exit(exit_status);
	}
	else if (is_builtin_command(cmd) == true && forking == false)
		return (exec_builtin(argv, vars));
	else if (exec_empty_cmd(cmd_name, vars) == true)
		return (EXIT_FAILURE);
	else
		exec_non_builtin(cmd_name, argv, vars);
	return (EXIT_FAILURE);
}
