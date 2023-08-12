/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:54:05 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/12 20:28:25 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(int argc, char *argv[], t_vars *vars)
{
	int		ret;
	char	*cmd_name;

	cmd_name = argv[0];
	if (ft_cmd_namecmp(cmd_name, "echo") == 0)
		ret = echo(argc, argv, vars);
	if (ft_cmd_namecmp(cmd_name, "cd") == 0)
		ret = cd(argc, argv, vars);
	if (ft_cmd_namecmp(cmd_name, "pwd") == 0)
		ret = pwd(argc, argv, vars);
	if (ft_cmd_namecmp(cmd_name, "export") == 0)
		ret = export(argc, argv, vars);
	if (ft_cmd_namecmp(cmd_name, "unset") == 0)
		ret = unset(argc, argv, vars);
	if (ft_cmd_namecmp(cmd_name, "env") == 0)
		ret = env(argc, argv, vars);
	if (ft_cmd_namecmp(cmd_name, "exit") == 0)
		ret = exit(argc, argv, vars);
	return (ret);
}
