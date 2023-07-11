/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:22:53 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/11 17:54:01 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str, char *options)
{
	int	i;
	int len;

	if (str[0] != '-')
		return (0);
	// Check if options are valid
	i = 1;
	while (str[i])
	{
		if (!ft_strchr(ECHO_OPTIONS, str[i]))
			return (0);
		i++;
	}
	// Add options to the string 'options'
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

int	echo(int argc, char **argv)
{
	int		i;
	char	options[OPTIONS_SIZE];

	options[0] = '\0';
	i = 1;
	while (i < argc && is_option(argv[i], options))
		i++;
	while (i < argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i + 1 < argc)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!ft_strchr(options, 'n'))
		ft_putstr_fd("\n", 1);
	return (0);
}
