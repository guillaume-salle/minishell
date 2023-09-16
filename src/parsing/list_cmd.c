/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:22:21 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/16 12:08:30 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_commande	*create_lstcmd(char *str, t_vars *var_env)
{
	char		**div;
	int			i;
	int			*tab;
	t_commande	*c;

	i = 0;
	div = ft_split(str, ' ');
	while (div[i])
		i++;
	tab = malloc(i * sizeof(int));
	if (!tab)
		return (free_double_char(div), NULL);
	create_type_table(div, tab);
	c = ft_lst_newcmd(create_word(div, tab, var_env), 0);
	fill_lstcmd(div, tab, c, var_env);
	return (free(div), free(tab), c);
}

t_commande	*ft_lst_newcmd(char *cmd, int id)
{
	t_commande	*c;

	c = malloc(sizeof(t_commande));
	if (!c || !cmd)
		return (NULL);
	c->cmd = cmd;
	c->id = id;
	c->cmds_split = ft_split(cmd, ' ');
	clean_del(c->cmds_split);
	c->heredoc = NULL;
	c->next = NULL;
	return (c);
}

char	*create_word(char **str, int *tab, t_vars *var_env)
{
	int		i;
	char	*word;
	char	*buff;

	word = NULL;
	i = 0;
	while (str[i])
	{
		if (tab[i] == 0)
		{
			buff = supp_quotes(str[i], var_env);
			word = ft_strjoin(word, buff);
			free(buff);
			word = ft_strjoin(word, " ");
		}
		i++;
	}
	if (word)
	{
		buff = ft_substr(word, 0, ft_strlen(word) - 1);
		free(word);
	}
	return (buff);
}

void	ft_lstadd_backcmd(t_commande **lst, t_commande *new)
{
	t_commande	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlastcmd(*lst);
	last->next = new;
}

t_commande	*ft_lstlastcmd(t_commande *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
