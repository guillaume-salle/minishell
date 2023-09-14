/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:14:10 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/14 12:20:15 by gusalle          ###   ########.fr       */
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

	(void) forking; //???
	argv = cmd->cmds_split;
	cmd_name = argv[0];
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
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			if (forking)
			{
				printf("freeing in child\n"); //REMOVE
				free_vars(vars);
			}
			return (127); //??
		}
		execve(pathname, argv, vars->envp);
		free(pathname);
	//	close_fd(vars); ??
		display_error_and_exit("execve", vars);
		return (-1);
	}
}
