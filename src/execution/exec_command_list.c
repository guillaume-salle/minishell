/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 10:19:13 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// The return value exit_status is used only for builtins, when not forking,
// otherwise exec_word will call execve and the process will exit.
int	exec_command_list(t_commande *cmd_list, t_vars *vars, bool forking)
{
	t_commande	*current;
	int			exit_status;

	current = cmd_list;
	while (current != NULL)
	{
		if (current->id != WORD)
		{
			if (handle_redirection(current, vars) == -1)
				return (1);
		}
		current = current->next;
	}
	current = cmd_list;
	while (current != NULL)
	{
		if (current->id == WORD)
		{
			exit_status = exec_word(current, vars, forking);
			break ;
		}
		current = current->next;
	}
	return (exit_status);
}
