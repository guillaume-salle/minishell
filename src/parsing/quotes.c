/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:15:21 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/15 12:58:21 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_exec.h"

int	check_pips(char *str)
{
	int	i;
	int	turn;

	i = 0;
	turn = 0;
	while (str[i])
	{
		if (str[i] == '|' && turn == 1)
			return (printf("Error near \'|\'\n"), 0);
		else if (str[i] == '|' && turn == 0)
			turn = 1;
		else if (str[i] != ' ')
			turn = 0;
		i++;
	}
	return (1);
}

int	last_character(char *str)
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
		return (printf("minishell : syntax error near unexpected token `newline'\n"), 1);
	return (0);
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

char	*first_transformation(char *commande, t_vars *var_env)
{
	char	*new;
	char	**vars;

	new = NULL;
	if (ft_strcmp(commande, "") == 0)
		return (free(commande), NULL);
	if (!check_red(commande)|| !check_unique(commande)
		|| !check_pips(commande) || last_character(commande))
		return (my_putenv("?", "1", var_env), free(commande), NULL);
	new = add_spaces(commande);
	vars = stock_variables(new);
	new = illuminate_variables(new, var_env->envp_list, vars);
	if (vars)
		free_double_char(vars);
	if (last_character(new))
		return (my_putenv("?", "1", var_env), free(new), NULL);
	return (my_putenv("?", "0", var_env), splitable(new), new);
}
