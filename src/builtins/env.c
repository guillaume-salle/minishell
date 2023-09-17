/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:01:29 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 10:17:12 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

//in an element of the env linked list, there is supposed to be a name
//but not necessary a content (ie content can be NULL),
//if there was a command like: export hello
void	print_env_export(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		if (current->content)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->content, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

void	print_env(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->content == NULL)
		{
			current = current->next;
			continue ;
		}
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

int	env(int argc, char *argv[], t_vars *vars)
{
	(void) argv;
	if (argc > 1)
		return (1);
	print_env(vars->envp_list);
	return (0);
}
