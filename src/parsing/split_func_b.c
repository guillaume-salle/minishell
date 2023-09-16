/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:26:10 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/16 16:35:02 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	fill_lstcmd(char **div, int *tab, t_commande *c, t_vars *var_env)
{
	int		i;
	char	*without_exp;

	i = 0;
	while (div[i])
	{
		if (tab[i] != 0)
			without_exp = ft_strdup3(div[i]);
		if (tab[i] == 1)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(without_exp, supp_quotes(div[i], var_env), 1));
		else if (tab[i] == 2)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(without_exp, supp_quotes(div[i], var_env), 2));
		else if (tab[i] == 3)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(without_exp, supp_quotes(div[i], var_env), 3));
		else if (tab[i] == 4)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(without_exp, supp_quotes(div[i], var_env), 4));
		else if (tab[i] == 5)
		{
			free(without_exp);
			free(div[i]);
		}
		i++;
	}
}

void	init_vars_count(int *i, int *res, int *len_var)
{
	*i = 0;
	*res = 0;
	*len_var = 0;
}

void	add_var_len(char *var, t_list *var_env, int *res)
{
	while (var_env)
	{
		if (!ft_strcmp(var, var_env->name))
				*res = *res + ft_strlen(var_env->content);
			var_env = var_env->next;
	}
}

void	init_var_illum(int *i, int *c, int *j)
{
	*j = 0;
	*i = 0;
	*c = 0;
}

void	affect_casu_char(char *new, char str, int *j)
{
	*new = str;
	*j = *j + 1;
}
