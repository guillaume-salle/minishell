/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:45:25 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/21 09:42:12 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	free_and_nullify(char **pointer)
{
	if (pointer != NULL && *pointer != NULL)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

static void	free_commande(t_commande *head)
{
	int			i;
	t_commande	*next;

	while (head)
	{
		if (head->cmd)
			free_and_nullify(&head->cmd);
		if (head->cmds_split)
		{
			i = -1;
			while (head->cmds_split[++i] != NULL)
				free(head->cmds_split[i]);
			free(head->cmds_split);
			head->cmds_split = NULL;
		}
		if (head->heredoc)
			free_and_nullify(&head->heredoc);
		if (head->without_exp)
			free_and_nullify(&head->without_exp);
		next = head->next;
		free(head);
		head = next;
	}
}

void	free_partition(t_partition *head)
{
	t_partition	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->cmds != NULL)
		{
			free_commande(temp->cmds);
			temp->cmds = NULL;
		}
		free(temp);
	}
}

void	free_list2(t_list *head)
{
	t_list	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->name)
			free(temp->name);
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}

// Do not reset line and envp
void	reset_vars_zero(t_vars *vars)
{
	if (vars->old_line != NULL)
		free_and_nullify(&vars->old_line);
	if (vars->temp_line != NULL)
		free_and_nullify(&vars->temp_line);
	if (vars->parse_result != NULL)
	{
		free_partition(vars->parse_result);
		vars->parse_result = NULL;
	}
	vars->exist_pipe = false;
	vars->exist_children = false;
	vars->last_pid = 0;
	vars->last_exit_status = 0;
}
