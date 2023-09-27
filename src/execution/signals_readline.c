/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:50:48 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/26 22:59:06 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Handle Ctrl-C
static void	sigint_handler_readline(int signo)
{
	g_signal_received = signo;
	close(STDIN_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

// Handle Ctrl-\.
static void	sigquit_handler_readline(int signo)
{
	(void) signo;
}

void	setup_signal_handlers_readline(t_vars *vars)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler_readline;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		display_error_and_exit("sigaction SIGINT", vars);
	sa_quit.sa_handler = sigquit_handler_readline;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		display_error_and_exit("sigaction SIGQUIT", vars);
}

void	setup_signal_handlers_default(t_vars *vars)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sa_default.sa_flags = SA_RESTART;
	sigemptyset(&sa_default.sa_mask);
	if (sigaction(SIGINT, &sa_default, NULL) == -1)
		display_error_and_exit("sigaction SIGINT", vars);
	if (sigaction(SIGQUIT, &sa_default, NULL) == -1)
		display_error_and_exit("sigaction SIGQUIT", vars);
	if (sigaction(SIGTERM, &sa_default, NULL) == -1)
		display_error_and_exit("sigaction SIGTERM", vars);
}

bool	stop_signal_readline(t_vars *vars)
{
	bool	stop;

	stop = signal_received(vars);
	if (stop == true)
		safe_dup2(vars->saved_stdin, STDIN_FILENO, vars);
	return (stop);
}
