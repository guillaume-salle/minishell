/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:45:25 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/24 18:24:20 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(t_heredoc *hd)
{
	if (!hd)
		return ;
	free(hd->filename);
	free(hd->file);
	free(hd);
}

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
	free_heredoc(cmd->hd);
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

void	free_list2(t_list2 **head)
{
	t_list2	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->name)
			free(temp->name);
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}
