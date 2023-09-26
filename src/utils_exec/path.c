/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:47:55 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/26 06:41:51 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static bool	is_relative_path(const char *path, t_vars *vars)
{
	int	i;

	if (path[0] != '.')
		return (false);
	if (path[1] == '\0')
	{
		ft_putstr_fd("minishell: .: filename argument required\n",
			STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		free_vars(vars);
		exit(2);
	}
	i = 1;
	while (path[i] == '.')
		i++;
	if (path[i] != '/')
		return (false);
	else
		return (true);
}

static char	*find_absolute_path(const char *command, t_vars *vars)
{
	char		*full_path;
	struct stat	st;

	full_path = ft_strdup3(command);
	if (full_path == NULL)
		display_error_and_exit("ft_strdup3", vars);
	if (stat(full_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == 1)
			path_is_a_directory(full_path, vars);
		else if (access(full_path, X_OK) == -1)
			permission_denied(full_path, vars);
		else if ((st.st_mode & S_IXUSR) == 0)
			permission_denied(full_path, vars);
		else
			return (full_path);
	}
	else
	{
		perror(full_path);
		free(full_path);
		free_vars(vars);
		exit(127);
	}
	return (NULL);
}

static bool	check_this_path(const char *full_path)
{
	struct stat	st;

	if (stat(full_path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == 1)
			return (false);
		else if (st.st_mode & S_IXUSR)
			return (true);
	}
	return (false);
}

static char	*find_in_path_env(const char *command, t_vars *vars)
{
	char	*full_path;
	char	*path_var;
	char	**dirs;
	int		i;

	path_var = my_getenv("PATH", vars);
	if (path_var == NULL)
		return (NULL);
	dirs = ft_split(path_var, ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = make_full_path(dirs[i], command, vars);
		if (check_this_path(full_path) == true)
		{
			ft_free_split(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

// Finds command path wether 'command' is a relative or absolute path
// or a command in PATH environment variable
// Does not free command parameter and return an allocated path
char	*find_command_path(const char *command, t_vars *vars)
{
	char	*path;

	if (command == NULL)
		return (NULL);
	if (command[0] == '/')
		return (find_absolute_path(command, vars));
	else if (is_relative_path(command, vars))
	{
		path = ft_strdup3(command);
		if (path == NULL)
			display_error_and_exit("ft_strdup", vars);
		return (path);
	}
	else
		return (find_in_path_env(command, vars));
}
