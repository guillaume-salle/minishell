/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:54:05 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/15 18:25:49 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(const char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"cd",
		"echo",
		"env",
		"pwd",
		"export",
		"unset",
		NULL
	};

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	exec_builtin(int argc, char *argv[], t_vars *vars)
{
	int		ret;
	char	*cmd_name;

	cmd_name = argv[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		ret = echo(argc, argv, vars);
	if (ft_strcmp(cmd_name, "cd") == 0)
		ret = cd(argc, argv, vars);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		ret = pwd(argc, argv, vars);
	if (ft_strcmp(cmd_name, "export") == 0)
		ret = export(argc, argv, vars);
	if (ft_strcmp(cmd_name, "unset") == 0)
		ret = unset(argc, argv, vars);
	if (ft_strcmp(cmd_name, "env") == 0)
		ret = env(argc, argv, vars);
	return (ret);
}

static void	child_routine(t_commande *cmd, t_vars *vars)
{
	if (is_builtin(cmd->cmds_split[0]) 
		&& exec_builtin(cmd->argc, cmd->cmds_split, vars) == -1)
	{
		perror("builtin");
		exit(EXIT_FAILURE);
	}
	else if (execvp(cmd->cmds_split[0], cmd->cmds_split) == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

void	execute_command(t_commande *cmd, t_vars *vars)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		child_routine(cmd, vars);
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}
