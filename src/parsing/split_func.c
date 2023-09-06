/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:33:41 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/06 15:55:26 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	fill_tab(char *str, int *quotes, char *new)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (quotes[i] != 2 && quotes[i] != 3)
		{
			new[c] = str[i];
			c++;
		}
		i++;
	}
}

void	new_tab_with_spaces(int **tab, int *c)
{
	*tab = create_add_space(*tab, 0, *c);
	*c = *c + 1;
	*tab = create_add_space(*tab, 1, *c);
}

void	init_var_addspace(int *i, int *c, int *tab)
{
	*i = 0;
	*c = 0;
	tab[0] = 0;
}

void	fill_quote_tab(int *cases, int *switch_ab, int a, int b)
{
	*switch_ab = a;
	*cases = b;
}

int	*init_var_createquote(int *a, int *b, int *i, char *str)
{
	int	*new;

	*a = 0;
	*b = 0;
	*i = 0;
	new = malloc((ft_strlen(str) + 1) * sizeof(int));
	if (!new)
		return (NULL);
	return (new);
}
