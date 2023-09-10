/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:45:25 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/10 19:38:50 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	free_commande(t_commande *cmd)
{
	int			i;
	t_commande	*next;

	if (!cmd)
		return ;
	free(cmd->cmd);
	i = 0;
	while (cmd->cmds_split[i])
	{
		free(cmd->cmds_split[i]);
		i++;
	}
	free(cmd->cmds_split);
	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}

void	free_partition(t_partition *part)
{
	t_partition	*next;

	if (!part)
		return ;
	while (part)
	{
		free_commande(part->cmds);
		next = part->next;
		free(part);
		part = next;
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
	if (vars->envp_list)
		free_list2(vars->envp_list);
	if (vars->envp)
		ft_free_split(vars->envp);
}

void	display_error_and_exit(char *str, t_vars *vars)
{
	perror(str);
	free_vars(vars);
	exit(EXIT_FAILURE);
}
