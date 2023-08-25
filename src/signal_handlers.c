/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:48:20 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/25 14:21:08 by gusalle          ###   ########.fr       */
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
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = sigint_handler;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = sigquit_handler;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("Error setting up SIGQUIT handler");
		exit(EXIT_FAILURE);
	}
}
