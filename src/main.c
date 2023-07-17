/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/17 16:25:16 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_vars;

static t_list2	*init_envp_list(char **envp)
{
	t_list2	*head;
	char	*key;
	char	*value;

	head = NULL;
	while (*envp)
	{
		key = ft_strtok(*envp, "=");
		value = ft_strtok(NULL, "\0");
		add_node(&head, key, value);
		envp++;
	}
	return (head);
}

int	main(int argc, char *argv[], char *envp[])
{
	argc++;
	(void) argv;
	g_vars.envp_list = init_envp_list(envp);
	return (0);
}
