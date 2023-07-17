/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:43:12 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/17 16:12:49 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_vars;

int	cd(int argc, char *argv[])
{
	char	*path;

	if (argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", stderr);
		return (-1);
	}
	if (argc == 1)
	{
		path = my_getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", stderr);
			return (-1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}
