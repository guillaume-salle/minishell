/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:22:53 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/09 16:45:02 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **argv)
{
	char	*str;

	str = ft_join_str(argv + 1, " ");
	if (str == NULL)
		return (1);
	ft_putendl_fd(str, 1);
	free(str);
	return (0);
}
