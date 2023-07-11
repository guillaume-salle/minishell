/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:22:53 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/11 16:13:51 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str, char *options)
{
	int	i;

	if (str[0] == '-'){
		i = 1;
		while (str + i && ft_strchr(ECHO_OPTIONS, str[i]))
		{
			if (!ft_strchr(options, str[i]))
				ft_strlcat(options, str + i, OPTIONS_SIZE);
			i++;
		}
		if (str[i] == 0)
			return (1);
	}
	return (0);
}

int	echo(int argc, char **argv)
{
	int		i;
	char	options[OPTIONS_SIZE];

	char[0] = 0;
	i = 1;
	while (i < argc && is_option(argv[i]))
		i++;
	while (i < argc)
	{
		if (i + 1 < argc)
			ft_printf("%s ", argv[i]);
		else
			ft_printf("%s", argv[i]);
		i++;
	}
	if (ft_strchr(options, 'n'))
		ft_printf("\n");
	return (0);
}
