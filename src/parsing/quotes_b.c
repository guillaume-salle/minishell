/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:24:21 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/15 22:24:29 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int	check_unique(char *str)
{
	int	*tab;
	int	i;

	if (!ft_strcmp(str, "\"") || !ft_strcmp(str, "\'"))
		return (printf("Error with a single quote\n"), 0);
	tab = create_quote_rep(str);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (tab[i] == 3 || tab[i] == 2)
		{
			if (i != 0 && tab[i + 1] != 0 && tab[i - 1] != 0
				&& tab[i] != tab[i + 1] && tab[i] != tab[i - 1])
				return (printf("Error with a single quote\n"), free(tab), 0);
		}
		i++;
	}
	if (tab[i - 1] == 0)
		return (printf("Error with a single quote\n"), free(tab), 0);
	free(tab);
	return (1);
}

int	have_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*supp_quotes(char *str, t_vars *var_env)
{
	char	*new;
	int		i;
	int		c;
	int		*quotes;
	char 	**vars;

	i = 0;
	c = 0;
	vars = stock_variables(str);
	str = illuminate_variables(str, var_env->envp_list, vars);
	printf("%s\n", str);
	if (vars)
		free_double_char(vars);
	if (!have_quotes(str))
		return (ft_strdup(str));
	quotes = create_quote_rep(str);
	while (i < ft_strlen(str))
	{
		if (quotes[i] == 2 || quotes[i] == 3)
			c++;
		i++;
	}
	new = malloc(ft_strlen(str) - c + 1);
	if (!new)
		return (free(quotes), free(str), NULL);
	return (new[ft_strlen(str) - c] = '\0', fill_tab(str, quotes, new), free(quotes), free(str), new);
}
