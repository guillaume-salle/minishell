/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_func_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:26:10 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/05 19:34:16 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void fill_lstcmd(char **div, int *tab, t_commande *c)
{
	int i;

	i = 0;
	while (div[i])
	{
		if (tab[i] == 1)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(supp_quotes(div[i]), 1));
		else if (tab[i] == 2)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(supp_quotes(div[i]), 2));
		else if (tab[i] == 3)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(supp_quotes(div[i]), 3));
		else if (tab[i] == 4)
			ft_lstadd_backcmd(&c, ft_lst_newcmd(supp_quotes(div[i]), 4));
		else if(tab[i] == 5)
			free(div[i]);
		i++;
	}
}

void init_vars_count(int *i, int *res, int *len_var, char **pid)
{
    *i = 0;
    *res = 0;
    *len_var = 0;
    *pid = ft_itoa(getpid());
}

void add_var_len(char *var, t_list *var_env, int *res)
{
    while (var_env)
    {
        if (!ft_strcmp(var, var_env->name))
                *res = *res + ft_strlen(var_env->content);
            var_env = var_env->next;
    }
}

void init_var_illum(int *i, int *c, int *j)
{
	*j = 0;
	*i = 0;
	*c = 0;
}

void affect_casu_char(char *new, char str, int *j)
{
    *new = str;
    *j = *j + 1;
}

