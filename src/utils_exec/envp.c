/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:14:16 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/24 23:07:26 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	fill_envp(t_list *head, char **envp, int count, t_vars *vars)
{
	t_list	*temp;
	int		len;
	int		i;

	temp = head;
	i = 0;
	while (i < count)
	{
		len = ft_strlen(temp->name) + ft_strlen(temp->content) + 2;
		envp[i] = malloc(len);
		if (envp[i] == NULL)
			display_error_and_exit("malloc", vars);
		envp[i][0] = '\0';
		ft_strlcat(envp[i], temp->name, len);
		ft_strlcat(envp[i], "=", len);
		ft_strlcat(envp[i], temp->content, len);
		temp = temp->next;
		i++;
	}
	envp[count] = NULL;
}

static char	**linked_list_to_envp(t_list *head, t_vars *vars)
{
	t_list	*temp;
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
		display_error_and_exit("malloc", vars);
	fill_envp(head, envp, count, vars);
	return (envp);
}

void	update_envp(t_vars *vars)
{
	ft_free_split(vars->envp);
	vars->envp = linked_list_to_envp(vars->envp_list, vars);
}

void	increment_shlvl(t_vars *vars)
{
	char	*str;
	int		shlvl;

	str = my_getenv("SHLVL", vars);
	if (str == NULL)
	{
		my_putenv("SHLVL", "1", vars);
		return ;
	}
	shlvl = ft_atoi(str);
	shlvl++;
	str = ft_itoa(shlvl);
	if (str == NULL)
		display_error_and_exit("ft_itoa", vars);
	my_putenv("SHLVL", str, vars);
	free(str);
}
