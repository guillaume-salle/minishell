/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:22:50 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/19 19:59:56 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_partition	*create_partition(char **partitions, t_vars *var_env)
{
	t_partition	*part;
	int			i;

	i = 1;
	part = ft_lstnew_partition(partitions[0], var_env);
	while (partitions[i])
	{
		ft_lstadd_back_partition(&part,
			ft_lstnew_partition(partitions[i], var_env));
		i++;
	}
	return (part);
}

void	splitable_pipe(char *str)
{
	int	i;
	int	*tab;

	i = 0;
	tab = create_quote_rep(str);
	while (str[i])
	{
		if (str[i] == '|' && tab[i] == 0)
			str[i] = (char) 29;
		i++;
	}
	free(tab);
}

void	clean_del_pipe(char **str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i][c])
		{
			if (str[i][c] == (char) 29)
				str[i][c] = '|';
			c++;
		}
		c = 0;
		i++;
	}
}

t_partition	*parsing(char *line, t_vars *var_env)
{
	char		**partitions;
	t_partition	*part;

	if (!line || !ft_strcmp(line, ""))
		return (NULL);
	splitable_pipe(line);
	partitions = ft_split(line, '|');
	clean_del_pipe(partitions);
	part = create_partition(partitions, var_env);
	free_double_char(partitions);
	return (part);
}

int	check_red(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			c++;
		else
			c = 0;
		if ((s[i] == '>' && s[i + 1] == '<') || (s[i] == '<' && s[i + 1] == '>')
			|| (c == 3 && s[i] != s[i + 1]))
			return (print_err_token(), ft_putchar_fd(s[i], 2),
				ft_putstr_fd("'\n", 2), 0);
		else if (c > 3)
		{
			print_err_token();
			ft_putchar_fd(s[i], STDERR_FILENO);
			return (ft_putchar_fd(s[i], 2), ft_putstr_fd("'\n", 2), 0);
		}
		i++;
	}
	return (1);
}
