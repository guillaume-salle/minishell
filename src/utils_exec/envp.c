/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:14:16 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/06 15:49:51 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	fill_envp(t_list2 *head, char **envp, int count)
{
	t_list2	*temp;
	int		len;
	int		i;

	temp = head;
	i = 0;
	while (i < count)
	{
		len = ft_strlen(temp->name) + ft_strlen(temp->content) + 2;
		envp[i] = malloc(len);
		if (envp[i] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		envp[i][0] = '\0';
		ft_strlcat(envp[i], temp->name, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i], temp->content, len);
		temp = temp->next;
		i++;
	}
	envp[count] = NULL;
}

static char	**linked_list_to_envp(t_list2 *head)
{
	t_list2	*temp;
	int		count;
	char	**envp;

	count = 0;
	temp = head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	envp = malloc((count + 1) * sizeof(char *));
	if (envp == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	fill_envp(head, envp, count);
	return (envp);
}

void	update_envp(t_vars *vars)
{
	ft_free_split(vars->envp);
	vars->envp = linked_list_to_envp(vars->envp_list);
}
