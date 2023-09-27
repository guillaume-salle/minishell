/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:16:29 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/19 19:20:00 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	free_parsing(t_partition **partition)
{
	t_partition	*buff;
	t_commande	*buff_cmd;

	if (*partition)
	{
		while ((*partition))
		{
			buff = (*partition)->next;
			while ((*partition)->cmds)
			{
				buff_cmd = (*partition)->cmds->next;
				free((*partition)->cmds->cmd);
				if ((*partition)->cmds->cmds_split)
					free_double_char((*partition)->cmds->cmds_split);
				free((*partition)->cmds);
				(*partition)->cmds = buff_cmd;
			}
			(*partition)->cmds = NULL;
			free(*partition);
			(*partition) = buff;
		}
		(*partition) = NULL;
	}
}

char	*char_to_string(char c)
{
	char	*string;

	string = malloc(2);
	if (!string)
		return (NULL);
	string[0] = c;
	string[1] = '\0';
	return (string);
}

char	*join_char(char *s1, char c)
{
	char	*new_chain;
	int		i;

	i = 0;
	if (!s1)
		return (char_to_string(c));
	new_chain = malloc(ft_strlen(s1) + 1 + 1);
	if (!new_chain)
		return (free(s1), NULL);
	new_chain[ft_strlen(s1) + 1] = '\0';
	while (i < ft_strlen(s1))
	{
		new_chain[i] = s1[i];
		i++;
	}
	new_chain[i] = c;
	free(s1);
	return (new_chain);
}

int	boolean_test(char c)
{
	return (c != '\"' && c != (char)177 && c != '=' && c != ':');
}

void	variable(char *str, int *i, char **new)
{
	int	c;

	c = 1;
	if (!str[*i + c])
		return ;
	if (!ft_isalpha(str[*i + c]) && (str[*i + c] != '_')
		&& boolean_test(str[*i + c]))
	{
		*new = join_char(*new, str[*i + c]);
		*new = ft_strjoin(*new, " ");
		*i = *i + 1;
	}
	else
	{
		while (str[*i + c] && (ft_isalnum(str[*i + c]) || str[*i + c] == '_'))
		{
			*new = join_char(*new, str[*i + c]);
			c++;
		}
		*new = ft_strjoin(*new, " ");
	}
}
