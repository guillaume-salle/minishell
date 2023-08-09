/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:43:12 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/09 16:14:47 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_vars;

int	cd(int argc, char *argv[])
{
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
	my_putenv("PWD", getenv("PWD"));
	my_putenv("OLDPWD", getenv("OLDPWD"));
	return (0);
}
