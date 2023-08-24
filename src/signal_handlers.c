/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:48:20 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/24 18:51:54 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle Ctrl-C
static void	sigint_handler(int signo)
{
	write(1, "\nmyshell> ", 10);
}

// Handle Ctrl-\.
static void	sigquit_handler(int signo)
{
}

void	setup_signal_handlers(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("Error setting up SIGINT handler");
	}
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		perror("Error setting up SIGQUIT handler");
	}
}
