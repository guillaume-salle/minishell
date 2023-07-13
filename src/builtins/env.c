/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:01:29 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/13 18:25:43 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list2 *head)
{
	t_list2	*current;

	current = head;
	while (current != NULL)
	{
		ft_putstr_fd(current->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current->content, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}
