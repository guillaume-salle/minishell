/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:01:29 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/15 18:09:41 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	print_env(const char *prefix, t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (prefix != NULL)
			ft_putstr_fd(prefix, STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (prefix != NULL)
			ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		if (prefix != NULL)
			ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

int	env(int argc, char *argv[], t_vars *vars)
{
	(void) argc;
	(void) argv;
	print_env(NULL, vars->envp_list);
	return (0);
}
