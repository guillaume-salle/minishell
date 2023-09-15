/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:22:50 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/15 12:53:51 by kyacini          ###   ########.fr       */
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

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			c++;
		else
			c = 0;
		if ( (str[i] == '>' && str[i + 1] == '<') || (str[i] == '<' && str[i + 1] == '>'))
			return (printf("minishell: syntax error near unexpected token `%c'\n", str[i]), 0);
		if (c == 3 && str[i + 1] != str[i])
			return (printf("minishell: syntax error near unexpected token `%c'\n", str[i]), 0);
		else if(c > 3)
			return (printf("minishell: syntax error near unexpected token `%c%c'\n", str[i], str[i]), 0);
		i++;
	}
	return (1);
}
