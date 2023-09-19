/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:59:08 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/19 19:19:51 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int	kind_of_quote(char *str, int j)
{
	int	*tab;
	int	ret;

	tab = create_quote_rep(str);
	if (tab[j] == 0)
	{
		while (j < ft_strlen(str))
		{
			if (tab[j] == 2 || tab[j] == 3)
				return (ret = tab[j], free(tab), ret);
			j++;
		}
	}
	free(tab);
	return (0);
}

char	**stock_variables(char *str)
{
	char	*string;
	int		i;
	char	**variables;

	string = NULL;
	variables = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && kind_of_quote(str, i) != 2)
			variable(str, &i, &string);
		i++;
	}
	if (string)
	{
		variables = ft_split(string, ' ');
		free(string);
	}
	return (variables);
}

int	count_char(char **vars, t_list *var_env)
{
	int		res;
	int		len_var;
	int		i;
	t_list	*buff;

	init_vars_count(&i, &res, &len_var);
	buff = var_env;
	while (vars[i])
	{
		add_var_len(vars[i], var_env, &res);
		var_env = buff;
		len_var += ft_strlen(vars[i]) + 1;
		i++;
	}
	return (res - len_var);
}

void	replace_content(char *var, t_list *var_env, char *new, int *i)
{
	int		c;

	c = 0;
	while (var_env)
	{
		if (!ft_strcmp(var, var_env->name))
		{
			while (var_env->content[c])
			{
				new[*i + c] = var_env->content[c];
				c++;
			}
			break ;
		}
		var_env = var_env->next;
	}
	*i = *i + c - 1;
}

char	*illuminate_variables(char *str, t_list *var_env, char **vars)
{
	char	*new;
	int		i;
	int		j;
	int		c;

	init_var_illum(&i, &j, &c);
	if (!vars)
		return (ft_strdup(str));
	new = malloc(ft_strlen(str) + count_char(vars, var_env) + 1);
	if (!new)
		return (NULL);
	new[ft_strlen(str) + count_char(vars, var_env)] = '\0';
	while (++i < ft_strlen(str) + count_char(vars, var_env))
	{
		if (str[j] == '$' && kind_of_quote(str, j) != 2 && vars[c]
			&& boolean_test(j + 1))
		{
			replace_content(vars[c], var_env, new, &i);
			j += ft_strlen(vars[c]) + 1;
			c++;
		}
		else
			affect_casu_char(&new[i], str[j], &j);
	}
	return (free(str), new);
}
