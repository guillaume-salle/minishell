/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:22:53 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 12:52:20 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static bool	is_option(char *str, char *options)
{
	int	i;
	int	len;

	if (str[0] != '-' || str[1] == '\0')
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_strchr(ECHO_OPTIONS, str[i]))
			return (false);
		i++;
	}
	i = 1;
	while (str[i])
	{
		if (!ft_strchr(options, str[i]))
		{
			len = ft_strlen(options);
			options[len] = str[i];
			options[len + 1] = '\0';
		}
		i++;
	}
	return (true);
}

int	echo(int argc, char **argv, t_vars *vars)
{
	int		i;
	char	options[OPTIONS_SIZE];

	(void) vars;
	options[0] = '\0';
	i = 1;
	while (i < argc && is_option(argv[i], options))
		i++;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i + 1 < argc)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!ft_strchr(options, 'n'))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
