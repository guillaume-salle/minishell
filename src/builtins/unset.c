/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:02:43 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/26 06:40:10 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int	remove_variable(const char *name, t_list **envp_list)
{
	t_list	*current;
	t_list	*prev;

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
	return (1);
}

int	unset(int argc, char *argv[], t_vars *vars)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (i < argc)
	{
		if (is_valid_variable_name(argv[i]))
			remove_variable(argv[i], &vars->envp_list);
		else
		{
			ret = 1;
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
		i++;
	}
	return (ret);
}
