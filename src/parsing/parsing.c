/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:22:50 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/15 11:30:43 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_partition	*create_partition(char **partitions)
{
	t_partition	*part;
	int			i;

	i = 1;
	part = ft_lstnew_partition(partitions[0]);
	while (partitions[i])
	{
		ft_lstadd_back_partition(&part, ft_lstnew_partition(partitions[i]));
		i++;
	}
	return (part);
}

t_partition	*parsing(char *line)
{
	char		**partitions;
	t_partition	*part;

	if (!line || !ft_strcmp(line, ""))
		return (NULL);
	partitions = ft_split(line, '|');
	part = create_partition(partitions);
	free_double_char(partitions);
	return (part);
}

int	check_red(char *str)
{
	int	i;
	int	c;
	int	d;

	i = 0;
	c = 0;
	d = 0;
	while (str[i])
	{
		if (str[i] == '<')
			d++;
		else
			d = 0;
		if (str[i] == '>')
			c++;
		else
			c = 0;
		if (c > 2 || d > 2 || (str[i] == '>' && str[i + 1] == '<')
			|| (str[i] == '<' && str[i + 1] == '>'))
			return (printf("Error near '%c'\n", str[i]), 0);
		i++;
	}
	return (1);
}
