/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:48:20 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/29 12:54:42 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle Ctrl-C
static void	sigint_handler_main(int signo)
{
	(void) signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Handle Ctrl-\.
static void	sigquit_handler_main(int signo)
{
	(void) signo;
}

void	setup_signal_handlers_main(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = sigint_handler_main;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = sigquit_handler_main;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("Error setting up SIGQUIT handler");
		exit(EXIT_FAILURE);
	}
}
