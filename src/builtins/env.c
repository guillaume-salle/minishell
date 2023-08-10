/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:01:29 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/10 18:54:46 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list2 *head)
{
	t_list2	*current;

	current = head;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}
