/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:45:25 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/15 11:03:09 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	free_commande(t_commande *head)
{
	int			i;
	t_commande	*next;

	while (head)
	{
		if (head->cmd)
		{
			free(head->cmd);
			head->cmd = NULL;
		}
		if (head->cmds_split)
		{
			i = 0;
			while (head->cmds_split[i] != NULL)
			{
				free(head->cmds_split[i]);
				i++;
			}
			free(head->cmds_split);
			head->cmds_split = NULL;
		}
		if (head->heredoc)
		{
			free(head->heredoc);
			head->heredoc = NULL;
		}
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

void	free_vars(t_vars *vars)
{
	if (vars->envp_list != NULL)
	{
		free_list2(vars->envp_list);
		vars->envp_list = NULL;
	}
	if (vars->envp != NULL)
	{
		ft_free_split(vars->envp);
		vars->envp = NULL;
	}
	if (vars->parse_result != NULL)
	{
		free_partition(vars->parse_result);
		vars->parse_result = NULL;
	}
	if (vars->line != NULL)
	{
		free(vars->line);
		vars->line = NULL;
	}
}

void	display_error_and_exit(char *str, t_vars *vars)
{
	printf("in display_error_and_exit"); //DELETE
	perror(str);
	free_vars(vars);
	exit(errno);
}
