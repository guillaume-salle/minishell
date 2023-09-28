/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:28:38 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/28 10:36:37 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// close fds ??
void	exit_minishell(int exit_status, t_vars *vars)
{
	free_vars(vars);
	exit(exit_status);
}

bool	str_isnum(const char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	my_exit(int argc, char *argv[], t_vars *vars)
{
	int	exit_status;

	exit_status = 0;
	if (isatty(STDIN_FILENO) && !(vars->exist_pipe))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (argc == 2 && str_isnum(argv[1]) == false)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_status = 2;
	}
	else if (argc == 2)
		exit_status = ft_atoi(argv[1]);
	else if (argc == 1)
		exit_status = ft_atoi(my_getenv("?", vars));
	exit_minishell(exit_status, vars);
	return (EXIT_FAILURE);
}
