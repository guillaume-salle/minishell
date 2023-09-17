/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:47:55 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 10:42:46 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static bool	is_absolute_path(const char *command)
{
	struct stat	st;

	if (command[0] != '/')
		return (false);
	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
		return (true);
	return (false);
}

static char	*make_full_path(const char *path, const char *command, t_vars *vars)
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

static char	*find_absolute_path(const char *command, t_vars *vars)
{
	char	*full_path;

	full_path = ft_strdup3(command);
	if (full_path == NULL)
		display_error_and_exit("ft_strdup3", vars);
	return (full_path);
}

static char	*find_relative_path(const char *command, t_vars *vars)
{
	char		*full_path;
	char		*path_var;
	char		**dirs;
	struct stat	st;
	int			i;

	path_var = my_getenv("PATH", vars);
	if (path_var == NULL)
		return (NULL);
	dirs = ft_split(path_var, ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = make_full_path(dirs[i], command, vars);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			return (ft_free_split(dirs), full_path);
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

// Finds command path wether 'command' is a relative or absolute path
// Does not free command parameter and return a allocated full path
char	*find_command_path(const char *command, t_vars *vars)
{
	if (command == NULL)
		return (NULL);
	if (is_absolute_path(command))
		return (find_absolute_path(command, vars));
	else
		return (find_relative_path(command, vars));
}
