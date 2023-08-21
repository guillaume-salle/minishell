/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:34:43 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/21 21:31:10 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//bool	is_builtin(const char *cmd)
//{
//	int			i;
//	const char	*builtins[] = {
//		"cd",
//		"echo",
//		"env",
//		"pwd",
//		"export",
//		"unset",
//		NULL
//	};
//
//	i = 0;
//	while (builtins[i])
//	{
//		if (ft_strcmp(cmd, builtins[i]) == 0)
//		{
//			return (true);
//		}
//		i++;
//	}
//	return (false);
//}

int	my_execvp(char *argv[], t_vars *vars)
{
	int		ret;
	int		argc;
	char	*cmd_name;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	cmd_name = argv[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		ret = echo(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		ret = cd(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		ret = pwd(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "export") == 0)
		ret = export(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		ret = unset(argc, argv, vars);
	else if (ft_strcmp(cmd_name, "env") == 0)
		ret = env(argc, argv, vars);
	else
		ret = execvp(argv[0], argv);
	return (ret);
}

void	exec_command(t_commande *cmd, t_vars *vars)
{
	if (cmd->id == WORD)
	{
		if (my_execvp(cmd->cmds_split, vars) == -1)
			;
	}
}
// Further redirection cases and other id types can be handled here
// E.g., R_DIR, L_DIR, etc.
