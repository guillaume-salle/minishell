/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:43:12 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/06 15:46:21 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	cd(int argc, char *argv[], t_vars *vars)
{
	char	*cwd;

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (-1);
	}
	else if (argc < 2)
		return (-1);
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (-1);
	}
	my_putenv("OLDPWD", my_getenv("PWD", vars), vars);
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		my_putenv("PWD", cwd, vars);
	else
	{
		perror("getcwd");
		return (-1);
	}
	return (0);
}
