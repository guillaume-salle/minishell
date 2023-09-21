/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:41:55 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/21 19:57:30 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	sigint_handler_parent(int signo)
{
	g_signal_received = signo;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	setup_signal_handlers_parent(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = sigint_handler_parent;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
}
