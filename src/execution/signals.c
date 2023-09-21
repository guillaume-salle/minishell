/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:50:48 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/21 11:02:36 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Handle Ctrl-C
static void	sigint_handler_prompt(int signo)
{
	g_signal_received = signo;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

// Handle Ctrl-\.
static void	sigquit_handler_prompt(int signo)
{
	(void)signo;
}

void	setup_signal_handlers_prompt(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler_prompt;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error setting up SIGINT handler");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = sigquit_handler_prompt;
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

bool	signal_in_readline(t_vars *vars)
{
	char	*str;
	bool	stop;

	stop = false;
	if (g_signal_received == SIGINT)
	{
		str = ft_itoa(128 + g_signal_received);
		if (str == NULL)
			display_error_and_exit("ft_itoa", vars);
		my_putenv("?", str, vars);
		free(str);
		stop = true;
	}
	g_signal_received = 0;
	return (stop);
}
