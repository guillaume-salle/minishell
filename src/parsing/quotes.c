/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:15:21 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/13 19:46:15 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

char	last_character(char *str)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			c = i;
		i++;
	}
	if (str[c] == '>' || str[c] == '<' || str[c] == '|')
		return (str[c]);
	return ('\0');
}

void	splitable(char *str)
{
	int	i;
	int	*tab;

	i = 0;
	tab = create_quote_rep(str);
	while (str[i])
	{
		if (str[i] == ' ' && tab[i] == 0)
			str[i] = (char) 177;
		i++;
	}
	free(tab);
}

void	clean_del(char **str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i][c])
		{
			if (str[i][c] == (char) 177)
				str[i][c] = ' ';
			c++;
		}
		c = 0;
		i++;
	}
}

char	*first_transformation(char *commande, t_list *var_env)
{
	char	*new;
	char	**vars;

	new = NULL;
	if (ft_strcmp(commande, "") == 0)
		return ("");
	if (last_character(commande) || !check_unique(commande))
	{
		printf("Error near \'%c\'\n", last_character(commande));
		free(commande);
		return (NULL);
	}
	new = add_spaces(commande);
	vars = stock_variables(new);
	new = illuminate_variables(new, var_env, vars);
	if (vars)
		free_double_char(vars);
	if (last_character(new))
		return (printf("Error near \'%c\'\n", last_character(commande)), free(new), NULL);
	return (splitable(new), new);
}
