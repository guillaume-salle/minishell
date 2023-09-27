/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/27 21:08:37 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int	handle_all_redirections(t_commande *cmd_list, t_vars *vars)
{
	t_commande	*current;

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
	return (0);
}

// The return value exit_status is used only for builtins, 
// otherwise execve will exit
int	exec_command_list(t_commande *cmd_list, t_vars *vars, bool forking)
{
	int			exit_status;
	t_commande	*current;

	exit_status = 0;
	current = cmd_list;
	if (handle_all_redirections(cmd_list, vars) == 1)
		return (1);
	while (current != NULL)
	{
		if (current->id == WORD)
		{
			exit_status = exec_word(current, vars, forking);
			break ;
		}
		current = current->next;
	}
	if (forking == true)
	{
		free_vars(vars);
		exit(exit_status);
	}
	else
		return (exit_status);
}
