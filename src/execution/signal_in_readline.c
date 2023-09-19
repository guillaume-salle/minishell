/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_in_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:26:14 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/19 18:22:10 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

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
