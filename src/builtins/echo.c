/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:22:53 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/17 21:45:25 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str, char *options)
{
	int	i;
	int	len;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_strchr(ECHO_OPTIONS, str[i]))
			return (0);
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
	return (1);
}

void	echo(int argc, char **argv)
{
	int		i;
	char	options[OPTIONS_SIZE];

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
}
