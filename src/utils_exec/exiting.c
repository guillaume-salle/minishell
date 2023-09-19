/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:47:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/19 10:23:53 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	free_vars(t_vars *vars)
{
	if (vars->envp_list != NULL)
	{
		free_list2(vars->envp_list);
		vars->envp_list = NULL;
	}
	if (vars->envp != NULL)
	{
		ft_free_split(vars->envp);
		vars->envp = NULL;
	}
	if (vars->parse_result != NULL)
	{
		free_partition(vars->parse_result);
		vars->parse_result = NULL;
	}
	if (vars->line != NULL)
	{
		free(vars->line);
		vars->line = NULL;
	}
}

void	display_error_and_exit(char *str, t_vars *vars)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	free_vars(vars);
	exit(errno);
}
