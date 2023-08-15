/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:02:43 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/15 16:20:39 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_variable(const char *name, t_list2 **envp_list)
{
	t_list2	*current;
	t_list2	*prev;

	current = *envp_list;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*envp_list = current->next;
			free(current->name);
			free(current->content);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

int	unset(int argc, char *argv[], t_vars *vars)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		remove_variable(argv[i], &vars->envp_list);
		i++;
	}
	return (0);
}
