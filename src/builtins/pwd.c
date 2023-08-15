/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 12:48:14 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/15 16:20:53 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}
