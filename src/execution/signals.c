/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:50:48 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/27 19:40:29 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Handle Ctrl-C for heredoc
static void	sigint_handler_heredoc(int signo)
{
	g_signal_received = signo;
	close(STDIN_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	setup_signal_handlers_heredoc(t_vars *vars)
{
	(void)vars;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler_heredoc);
}

static void	sigint_handler_prompt(int signo)
{
	g_signal_received = signo;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signal_handlers_prompt(t_vars *vars)
{
	(void)vars;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler_prompt);
}

void	setup_signal_handlers_default(t_vars *vars)
{
	(void)vars;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Handle Ctrl-\.
// static void	sigquit_handler_readline(int signo)
//{
//	(void) signo;
//}

// void	setup_signal_handlers_readline(t_vars *vars)
//{
//	struct sigaction	sa_int;
//	struct sigaction	sa_quit;
//
//	sa_int.sa_handler = sigint_handler_readline;
//	sa_int.sa_flags = SA_RESTART;
//	sigemptyset(&sa_int.sa_mask);
//	if (sigaction(SIGINT, &sa_int, NULL) == -1)
//		display_error_and_exit("sigaction SIGINT", vars);
//	sa_quit.sa_handler = sigquit_handler_readline;
//	sa_quit.sa_flags = 0;
//	sigemptyset(&sa_quit.sa_mask);
//	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
//		display_error_and_exit("sigaction SIGQUIT", vars);
//}

// void	setup_signal_handlers_default(t_vars *vars)
//{
//	struct sigaction	sa_default;
//
//	sa_default.sa_handler = SIG_DFL;
//	sa_default.sa_flags = SA_RESTART;
//	sigemptyset(&sa_default.sa_mask);
//	if (sigaction(SIGINT, &sa_default, NULL) == -1)
//		display_error_and_exit("sigaction SIGINT", vars);
//	if (sigaction(SIGQUIT, &sa_default, NULL) == -1)
//		display_error_and_exit("sigaction SIGQUIT", vars);
//	if (sigaction(SIGTERM, &sa_default, NULL) == -1)
//		display_error_and_exit("sigaction SIGTERM", vars);
//}
