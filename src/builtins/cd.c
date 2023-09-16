/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:43:12 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/16 18:46:51 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	cd(int argc, char *argv[], t_vars *vars)
{
	char	*cwd;
	char	*dir;

	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (argc == 1)
	{
		dir = my_getenv("HOME", vars);
		if (dir == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
	}
	else
		dir = argv[1];
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(dir);
		return (1);
	}
	my_putenv("OLDPWD", my_getenv("PWD", vars), vars);
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		my_putenv("PWD", cwd, vars);
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}
