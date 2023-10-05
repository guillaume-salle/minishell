/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:01:21 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/29 00:25:38 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	increment_shlvl(t_vars *vars)
{
	char	*str;
	int		shlvl;

	str = my_getenv("SHLVL", vars);
	if (str == NULL)
		my_putenv("SHLVL", "1", vars);
	else
	{
		shlvl = ft_atoi(str);
		shlvl++;
		str = ft_itoa(shlvl);
		if (str == NULL)
			display_error_and_exit("ft_itoa", vars);
		my_putenv("SHLVL", str, vars);
		free(str);
	}
	}

static void	init_pwd(t_vars *vars)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str != NULL)
	{
		my_putenv("PWD", str, vars);
		vars->pwd = ft_strdup3(str);
		free(str);
	}
	else
	{
		ft_putstr_fd("shell-init: error retrieving current directory:",
				STDERR_FILENO);
		ft_putstr_fd(" getcwd: cannot access parent directories:",
				STDERR_FILENO);
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		ft_putstr_fd("sh: 0: getcwd() failed: No such file or directory\n",
				STDERR_FILENO);
	}
}

void	init_vars(t_vars *vars)
{
	increment_shlvl(vars);
	init_pwd(vars);
}
