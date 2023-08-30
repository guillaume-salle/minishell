/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:52:54 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/30 15:47:48 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_full_path(const char *path, const char *command)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(command) + 2;
	full_path = malloc(len);
	if (full_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	full_path[0] = '\0';
	ft_strlcat(full_path, path, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, command, len);
	return (full_path);
}

char	*find_command_path(const char *command, t_vars *vars)
{
	char		*path_var;
	char		**dirs;
	char		*full_path;
	struct stat	st;
	int			i;

	path_var = my_getenv("PATH", vars);
	if (path_var == NULL)
		return (NULL);
	dirs = ft_split(path_var, ':');
	i = 0;
	while (dirs[i] != NULL)
	{
		full_path = make_full_path(dirs[i], command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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
