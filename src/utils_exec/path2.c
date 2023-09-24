/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:27:46 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/24 10:25:41 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

char	*make_full_path(const char *path, const char *command, t_vars *vars)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(command) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
		display_error_and_exit("malloc", vars);
	full_path[0] = '\0';
	ft_strlcat(full_path, path, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, command, len);
	return (full_path);
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

void	path_is_a_directory(char *pathname, t_vars *vars)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(pathname, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	free_and_nullify(&pathname);
	free_vars(vars);
	exit(126);
}
