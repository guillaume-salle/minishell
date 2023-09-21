/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:27:46 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/20 23:35:29 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	path_is_a_directory(char *pathname, t_vars *vars)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	free_and_nullify(&pathname);
	free_vars(vars);
	exit(126);
}

bool	check_this_path(const char *path_base, const char *path_end,
		char **full_path, t_vars *vars)
{
	struct stat	st;

	*full_path = make_full_path(path_base, path_end, vars);
	if (stat(*full_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == 1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(*full_path, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			free(*full_path);
			exit(126);
		}
		else if (st.st_mode & S_IXUSR)
			return (true);
	}
	free(*full_path);
	return (false);
}

void	permission_denied(char *full_path, t_vars *vars)
{	
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(full_path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		free(full_path);
		free_vars(vars);
		exit(126);
	}
}
