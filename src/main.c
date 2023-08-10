/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/10 18:55:15 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_vars;

int	main(int argc, char *argv[], char *envp[])
{
	argc++;
	(void) argv;
	g_vars.envp_list = init_envp_list(envp);
	if (!g_vars.envp_list)
		return (-1);
	env(g_vars.envp_list);
	return (0);
}
