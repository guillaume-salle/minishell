/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:41:55 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/26 23:18:27 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	signal_handler_parent(int signo)
{
	(void) signo;
}

void	setup_signal_handlers_parent(t_vars *vars)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler_parent;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		display_error_and_exit("sigaction SIGINT", vars);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		display_error_and_exit("sigaction SIGQUIT", vars);
	if (sigaction(SIGTERM, &sa, NULL) == -1)
		display_error_and_exit("sigaction SIGTERM", vars);
}

//void	setup_signal_handlers_parent(t_vars *vars)
//{
//	(void) vars;
//	signal(SIGINT, signal_handler_parent);
//	signal(SIGQUIT, signal_handler_parent);
//	signal(SIGTERM, signal_handler_parent);
//}

bool	signal_received(t_vars *vars)
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
