/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:50:48 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 20:23:25 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	refresh_readline_sigint(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Handle Ctrl-C
static void	sigint_handler_main(int signo)
{
	g_signal_received = signo;
	write(STDOUT_FILENO, "\n", 1);
}

// Handle Ctrl-\.
static void	sigquit_handler_main(int signo)
{
	(void)signo;
}

void	setup_signal_handlers_main(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

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

void	set_default_handling_signals(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = 0;
	sigemptyset(&sa_default.sa_mask);
	if (sigaction(SIGINT, &sa_default, NULL) == -1)
	{
		perror("Error setting default SIGINT handler in child");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa_default, NULL) == -1)
	{
		perror("Error setting default SIGQUIT handler in child");
		exit(EXIT_FAILURE);
	}
}
