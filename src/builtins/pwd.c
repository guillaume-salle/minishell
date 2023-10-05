/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:48:14 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/29 00:27:20 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	pwd(int argc, char *argv[], t_vars *vars)
{
	char	*cwd;

	(void) argc;
	(void) argv;
	(void) vars;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	else if (vars->pwd !=NULL)
		ft_putendl_fd(vars->pwd, STDOUT_FILENO);
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}
