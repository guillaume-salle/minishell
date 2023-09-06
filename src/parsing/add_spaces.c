/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:22:37 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/05 20:30:19 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*create_quote_rep(char *str)
{
	int	*ret;
	int	i;
	int	switch_b;
	int	switch_a;

	ret = init_var_createquote(&switch_a, &switch_b, &i, str);
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"' && switch_b && !switch_a)
			fill_quote_tab(&ret[i], &switch_b, 0, 3);
		else if (str[i] == '\"' && !switch_b && !switch_a)
			fill_quote_tab(&ret[i], &switch_b, 1, 3);
		else if (str[i] == '\'' && switch_a && !switch_b)
			fill_quote_tab(&ret[i], &switch_a, 0, 2);
		else if (str[i] == '\'' && !switch_a && !switch_b)
			fill_quote_tab(&ret[i], &switch_a, 1, 2);
		else if (switch_a || switch_b)
			ret[i] = 0;
		else
			ret[i] = 1;
		i++;
	}
	return (ret[i] = 4, ret);
}

int	*create_add_space(int *tab, int position, int size)
{
	int	*ret;
	int	i;

	i = 0;
	ret = malloc((size + 1) * sizeof(int));
	if (!ret)
		return (NULL);
	while (i < size)
	{
		ret[i] = tab[i];
		i++;
	}
	ret[i] = position;
	free(tab);
	return (ret);
}

char	*add_final(char *str, int *tab, int size, int *quotes)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc((size + 1) * sizeof(int));
	if (!new)
		return (free(str), NULL);
	new[size] = '\0';
	while (i < size)
	{
		if (tab[i] == 1)
			new[i] = ' ';
		else
		{
			new[i] = str[j];
			j++;
		}
		i++;
	}
	return (free(str), free(tab), free(quotes), new);
}

char	*add_spaces(char *str)
{
	int	i;
	int	*tab_spaces;
	int	*quotes;
	int	c;

	tab_spaces = malloc(1 * sizeof(int));
	if (!tab_spaces)
		return (NULL);
	init_var_addspace(&i, &c, tab_spaces);
	quotes = create_quote_rep(str);
	while (str[i])
	{
		if (((str[i] == '>' || str[i] == '<') && str[i + 1] != '>'
		&& str[i + 1] != '<' && quotes[i] != 0 && str[i + 1] != ' ')
		|| ((str[i + 1] == '>' || str[i + 1] == '<') && str[i] != '>'
		&& str[i] != '<' && str[i] != ' ' && quotes[i + 1] != 0))
			new_tab_with_spaces(&tab_spaces, &c);
		else
			tab_spaces = create_add_space(tab_spaces, 0, c);
		i++;
		c++;
	}
	if (c > 0)
		str = add_final(str, tab_spaces, c, quotes);
	return (ft_strdup(str));
}
